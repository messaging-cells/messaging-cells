
#include <stdio.h>
#include "global.h"
#include "booter.h"

//======================================================================
// off chip shared memory

mc_off_sys_st* mcz_pt_external_host_data_obj = mc_null;

//=====================================================================
// global funcs

mck_glb_sys_st	mch_glb_sys_data;

void 
mck_abort(mc_addr_t err, char* msg) {
	char full_msg[200];
	snprintf(full_msg, 200, "ABORTED_ZNQ_HOST_MC_SYS. %s\n", msg);
	mch_abort_func(err, full_msg);
}

mck_glb_sys_st*
mck_get_glb_sys(){
	return &mch_glb_sys_data;
}

void 
mck_set_irq0_handler(){
}

