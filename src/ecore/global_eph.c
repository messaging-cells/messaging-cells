
#include "interruptions.h"
#include "global.h"

//=====================================================================
// global data

bjk_glb_sys_st	bj_glb_sys_data;

//=====================================================================
// global funcs

void
abort(){	// Needed when optimizing for size
	BJK_CK2(ck2_abort, 0);
	bjk_abort((bj_addr_t)abort, 0, bj_null);
	while(1);
}

bjk_glb_sys_st*
bjk_get_glb_sys(){
	return &bj_glb_sys_data;
}

void 
bjk_set_irq0_handler(){
	unsigned * ivt = 0x0;
	*ivt = ((((unsigned)bjk_sync_handler) >> 1) << 8) | BJ_B_OPCODE;
}

