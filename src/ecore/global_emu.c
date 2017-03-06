
#include "global.h"

//=====================================================================
// global data

bjk_glb_sys_st	bj_glb_sys_data;

//=====================================================================
// global funcs

bjk_glb_sys_st*
bjk_get_glb_sys(){
	return &bj_glb_sys_data;
}

bj_sys_sz_st*
bj_get_glb_sys_sz(){
	return &(bjk_get_glb_sys()->sys_sz);
}

void 
bjk_set_irq0_handler(){
}

