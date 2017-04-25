
#include "interruptions.h"
#include "global.h"
#include "dyn_mem.h"

//=====================================================================
// global data

bjk_glb_sys_st*	bjk_glb_pt_sys_data;

//=====================================================================
// global funcs

bjk_glb_sys_st*
bjk_get_first_glb_sys(){
	bjk_glb_pt_sys_data = (bjk_glb_sys_st*)a32_malloc(sizeof(bjk_glb_sys_st));
	return bjk_glb_pt_sys_data;
}

void
abort(){	// Needed when optimizing for size
	BJK_CK2(ck2_abort, 0);
	bjk_abort((bj_addr_t)abort, 0, bj_null);
	while(1);
}

void 
bjk_set_irq0_handler(){
	unsigned * ivt = 0x0;
	*ivt = ((((unsigned)bjk_sync_handler) >> 1) << 8) | BJ_B_OPCODE;
}

