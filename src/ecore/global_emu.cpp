
#include "global.h"

#include "thread_emu.hh"
#include "booter.h"

//=====================================================================
// global funcs

bjk_glb_sys_st	bjm_glb_sys_data;

void 
bjk_abort(bj_addr_t err, char* orig_msg) {
	char msg[300];
	if(bj_is_host_thread()){
		snprintf(msg, 300, "ABORTED_EMU_HOST_THREAD MSG=%s\n", orig_msg);
		bjh_abort_func(err, msg);
		return;
	}
	thread_info_t* inf = bjk_get_thread_info();
	snprintf(msg, 300, "ABORTED THREAD=%ld \t CORE_ID=%x MSG=%s\n", inf->thread_id, inf->bjk_core_id, orig_msg);
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

