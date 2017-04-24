
#include "global.h"

#include "thread_emu.hh"
#include "booter.h"

//=====================================================================
// global funcs

bjk_glb_sys_st*
bjk_get_glb_sys(){
	return &(bjk_get_thread_info()->bj_glb_sys_data);
}

void 
bjk_set_irq0_handler(){
}

