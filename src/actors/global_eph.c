
#include "interruptions_eph.h"
#include "err_msgs.h"
#include "global.h"
#include "dyn_mem.h"

//======================================================================
// off chip shared memory

bj_off_sys_st bjk_external_host_data_obj bj_external_host_data_ram;

//=====================================================================
// global data

bjk_glb_sys_st*	bjk_glb_pt_sys_data;

unsigned bjk_original_ivt_0;

//=====================================================================
// global funcs

bjk_glb_sys_st*
bjk_get_first_glb_sys(){
	bjk_glb_pt_sys_data = bj_malloc32(bjk_glb_sys_st, 1);
	return bjk_glb_pt_sys_data;
}

void
abort(){	// Needed when optimizing for size
	BJK_CK(0);
	bjk_abort((bj_addr_t)abort, err_5);
	while(1);
}

void 
bjk_set_irq0_handler(){
	unsigned * ivt = 0x0;
	bjk_original_ivt_0 = *ivt;
	*ivt = ((((unsigned)bjk_sync_handler) >> 1) << 8) | BJ_B_OPCODE;
}

void 
bjk_abort(bj_addr_t err, char* msg) {
	int16_t sz_trace = -1;
	void** trace = bj_null;
	if(msg != bj_null){
		sz_trace = BJ_MAX_CALL_STACK_SZ;
		trace = BJK_GLB_SYS->bjk_dbg_call_stack_trace;
	}
	if((trace != bj_null) && (sz_trace > 0)){
		bjk_get_call_stack_trace(sz_trace, trace);
	}
	bjk_glb_sys_st* in_shd = BJK_GLB_SYS;
	in_shd->dbg_error_code = err;

	bj_off_core_st* off_core_pt = BJK_GLB_SYS->off_core_pt;
	if((off_core_pt != bj_null) && (off_core_pt->magic_id == BJ_MAGIC_ID)){
		bj_set_off_chip_var(off_core_pt->is_finished, BJ_FINISHED_VAL);
	}
	
	bj_asm("mov r62, %0" : : "r" (in_shd));
	bj_asm("mov r63, %0" : : "r" (err));
	bj_asm("gid");
	bj_asm("trap 0x3");
	bj_asm("movfs r0, pc");
	bj_asm("jalr r0");
}

void
bj_host_init(){
	// a core must never call this
	bjk_abort((bj_addr_t)bj_host_init, err_2);
}

void
bj_host_run(){
	// a core must never call this
	bjk_abort((bj_addr_t)bj_host_run, err_3);
}

void
bj_host_finish(){
	// a core must never call this
	bjk_abort((bj_addr_t)bj_host_finish, err_4);
}

bj_addr_t 
bjk_get_module_address(uint32_t modl_idx){
	uint32_t tot_modls = bjk_get_tot_modules();
	if(modl_idx >= tot_modls){
		return bj_null;
	}
	bj_addr_t mod_sz = BJ_VAL_CORE_MODULE_SIZE;
	uint8_t* pt_ext_mods = (uint8_t*)BJ_VAL_EXTERNAL_LOAD_ORIG;
	return ((bj_addr_t)(pt_ext_mods + (mod_sz * modl_idx)));
}

char* 
bjk_get_module_name(uint32_t modl_idx){
	uint32_t tot_modls = bjk_get_tot_modules();
	if(modl_idx >= tot_modls){
		return bj_null;
	}
	bj_addr_t mod_sz = BJ_VAL_CORE_MODULE_SIZE;
	uint8_t* pt_ext_mods = (uint8_t*)BJ_VAL_EXTERNAL_LOAD_ORIG;
	char** pt_mod_nams = (char**)(pt_ext_mods + (mod_sz * tot_modls));
	return pt_mod_nams[modl_idx];
}

void
bjk_fill_module_external_addresses(char** user_order, bj_addr_t* user_ext_addr){
	uint32_t tot_modls = bjk_get_tot_modules();
	for(uint32_t aa = 0; aa < tot_modls; aa++){
		char* usr_nam = user_order[aa];
		for(uint32_t bb = 0; bb < tot_modls; bb++){
			char* link_nam = bjk_get_module_name(bb);
			int cc = bj_strcmp(usr_nam, link_nam);
			if(cc == 0){
				user_ext_addr[aa] = bjk_get_module_address(bb);
				bb = tot_modls;
			}
		}
	}
}

bool
bjk_load_module(bj_addr_t ext_addr){
	uint8_t* pt_mod = (uint8_t*)ext_addr;
	if(pt_mod == bj_null){
		return false;
	}
	bjk_sprt("LOADING module idx____");
	bjk_sprt("addr____");
	bjk_xprt((bj_addr_t)pt_mod);
	bjk_sprt("____\n");

	bj_addr_t mod_sz = BJ_VAL_CORE_MODULE_SIZE;
	uint8_t* pt_mem_mod = (uint8_t*)BJ_VAL_CORE_MODULE_ORIG;
	bj_memcpy(pt_mem_mod, pt_mod, mod_sz);
	return true;
}

