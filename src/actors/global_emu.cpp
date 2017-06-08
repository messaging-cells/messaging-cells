
#include "global.h"

#include "thread_emu.hh"
#include "booter.h"

//======================================================================
// off chip shared memory

bj_off_sys_st bjm_external_host_data_obj;

//=====================================================================
// global funcs

void 
bjk_abort(bj_addr_t err, char* orig_msg) {
	char msg[300];
	emu_info_t* inf = bjk_get_emu_info();
	snprintf(msg, 300, "ABORTED THREAD=%ld \t CORE_ID=%x MSG=%s\n", inf->emu_id, inf->emu_core_id, orig_msg);
	bjh_abort_func(err, msg);
}

bjk_glb_sys_st*
bjk_get_glb_sys(){
	return &(bjk_get_emu_info()->emu_glb_sys_data);
}

void 
bjk_set_irq0_handler(){
}

