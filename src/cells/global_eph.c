
#include "interruptions_eph.h"
#include "err_msgs.h"
#include "global.h"
#include "dyn_mem.h"

//======================================================================
// off chip shared memory

mc_off_sys_st mck_external_host_data_obj mc_external_host_data_ram;

//=====================================================================
// global data

mck_glb_sys_st*	mck_glb_pt_sys_data;

unsigned mck_original_ivt_0;

//=====================================================================
// global funcs

mck_glb_sys_st*
mck_get_first_glb_sys(){
	mck_glb_pt_sys_data = mc_malloc32(mck_glb_sys_st, 1);
	return mck_glb_pt_sys_data;
}

void
abort(){	// Needed when optimizing for size
	MCK_CK(0);
	mck_abort((mc_addr_t)abort, err_5);
	while(1);
}

void 
mck_set_irq0_handler(){
	unsigned * ivt = 0x0;
	mck_original_ivt_0 = *ivt;
	*ivt = ((((unsigned)mck_sync_handler) >> 1) << 8) | MC_B_OPCODE;
}

/*! 
This function aborts execution. It saves the stack trace and the host will print it after aborting.
*/
void 
mck_abort(mc_addr_t err, char* msg) {
	int16_t sz_trace = -1;
	void** trace = mc_null;
	if(msg != mc_null){
		sz_trace = MC_MAX_CALL_STACK_SZ;
		trace = MC_CORE_INFO->mck_dbg_call_stack_trace;
	}
	if((trace != mc_null) && (sz_trace > 0)){
		mck_get_call_stack_trace(sz_trace, trace);
	}
	mck_glb_sys_st* in_shd = MC_CORE_INFO;
	in_shd->dbg_error_code = err;

	mc_off_core_st* off_core_pt = MC_CORE_INFO->off_core_pt;
	if((off_core_pt != mc_null) && (off_core_pt->magic_id == MC_MAGIC_ID)){
		mc_set_off_chip_var(off_core_pt->is_finished, MC_FINISHED_VAL);
	}
	
	mc_asm("mov r62, %0" : : "r" (in_shd));
	mc_asm("mov r63, %0" : : "r" (err));
	mc_asm("gid");
	mc_asm("trap 0x3");
	mc_asm("movfs r0, pc");
	mc_asm("jalr r0");
}

void
mc_host_init(){
	// a core must never call this
	mck_abort((mc_addr_t)mc_host_init, err_2);
}

void
mc_host_run(){
	// a core must never call this
	mck_abort((mc_addr_t)mc_host_run, err_3);
}

void
mc_host_finish(){
	// a core must never call this
	mck_abort((mc_addr_t)mc_host_finish, err_4);
}

mc_addr_t 
mck_get_module_address(uint32_t modl_idx){
	uint32_t tot_modls = mck_get_tot_modules();
	if(modl_idx >= tot_modls){
		return mc_null;
	}
	mc_addr_t mod_sz = MC_VAL_CORE_MODULE_SIZE;
	uint8_t* pt_ext_mods = (uint8_t*)MC_VAL_EXTERNAL_LOAD_ORIG;
	return ((mc_addr_t)(pt_ext_mods + (mod_sz * modl_idx)));
}

char* 
mck_get_module_name(uint32_t modl_idx){
	uint32_t tot_modls = mck_get_tot_modules();
	if(modl_idx >= tot_modls){
		return mc_null;
	}
	mc_addr_t mod_sz = MC_VAL_CORE_MODULE_SIZE;
	uint8_t* pt_ext_mods = (uint8_t*)MC_VAL_EXTERNAL_LOAD_ORIG;
	char** pt_mod_nams = (char**)(pt_ext_mods + (mod_sz * tot_modls));
	return pt_mod_nams[modl_idx];
}

void
mck_fill_module_external_addresses(char** user_order, mc_addr_t* user_ext_addr){
	uint32_t tot_modls = mck_get_tot_modules();
	for(uint32_t aa = 0; aa < tot_modls; aa++){
		char* usr_nam = user_order[aa];
		for(uint32_t bb = 0; bb < tot_modls; bb++){
			char* link_nam = mck_get_module_name(bb);
			int cc = mc_strcmp(usr_nam, link_nam);
			if(cc == 0){
				user_ext_addr[aa] = mck_get_module_address(bb);
				bb = tot_modls;
			}
		}
	}
}

bool
mck_load_module(mc_addr_t ext_addr){
	uint8_t* pt_mod = (uint8_t*)ext_addr;
	if(pt_mod == mc_null){
		return false;
	}
	mck_sprt("LOADING module idx____");
	mck_sprt("addr____");
	mck_xprt((mc_addr_t)pt_mod);
	mck_sprt("____\n");

	mc_addr_t mod_sz = MC_VAL_CORE_MODULE_SIZE;
	uint8_t* pt_mem_mod = (uint8_t*)MC_VAL_CORE_MODULE_ORIG;
	mc_memcpy(pt_mem_mod, pt_mod, mod_sz);
	return true;
}

