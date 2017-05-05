
#include "global.h"

#include "thread_emu.hh"
#include "booter.h"

//=====================================================================
// global funcs

bjk_glb_sys_st	bjm_glb_sys_data;

void 
bjk_abort(bj_addr_t err, int16_t sz_trace, void** trace) {
	if(bj_is_host_thread()){
		bjh_abort_func(err, "ABORTED HOST THREAD \n");
		return;
	}
	thread_info_t* inf = bjk_get_thread_info();
	char msg[200];
	sprintf(msg, "ABORTED THREAD=%ld \t CORE_ID=%x\n", inf->thread_id, inf->bjk_core_id);
	bjh_abort_func(err, msg);
}

bjk_glb_sys_st*
bjk_get_glb_sys(){
	if(bj_is_host_thread()){
		return &bjm_glb_sys_data;
	}
	return &(bjk_get_thread_info()->bjk_glb_sys_data);
}

void 
bjk_set_irq0_handler(){
}

