
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

