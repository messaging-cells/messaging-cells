
#include "global.h"

#include "thread_emu.hh"
#include "booter.h"

//=====================================================================
// global funcs

bjk_glb_sys_st	bjh_glb_sys_data;

void 
bjk_abort(bj_addr_t err, int16_t sz_trace, void** trace) {
	bjh_abort_func(err, "ABORTED HOST THREAD \n");
}

bjk_glb_sys_st*
bjk_get_glb_sys(){
	return &bjh_glb_sys_data;
}

void 
bjk_set_irq0_handler(){
}
