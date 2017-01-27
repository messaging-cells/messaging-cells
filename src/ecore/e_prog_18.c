
#include <stdio.h>
#include <inttypes.h>

#include "global.h"
#include "trace.h"
#include "test1.h"

//=====================================================================

uint16_t aux_val; 

uint16_t * bj_opt_sz_fn fun10();
//uint16_t * fun10();

uint16_t *
fun10() {
	register uint16_t *pt_jj asm("r40");
	register uint16_t *pt_jj2 asm("r41");
	//pt_jj = &aux_val;
	pt_jj = (uint16_t *)0xaaa;
	pt_jj2 = pt_jj;
	//pt_jj2++;
	//pt_jj += 0xaaa;
	return pt_jj2;
}

/*
void fun1() {
	//bjk_wait_sync(0xfe01);
	bjk_get_call_stack_trace(BJ_MAX_CALL_STACK_SZ, bjk_dbg_call_stack_trace);
}
*/

int main(void) {
	bjk_init_global();

	int aa = 0xaa;
	int aa2 = 0xaa2;
	BJK_CK(ck_01, (aa != aa2));
	
	bj_id_t koid = bjk_get_coreid();
	bj_addr_t addr_r63 = bj_addr_with(koid, 0xf00fc);
	uint32_t* pt_reg = (uint32_t*)addr_r63;
	
	bj_in_core_shd.val_reg1 = 0xabe01;
	bj_in_core_shd.val_reg2 = 0xabe02;
	/*
	//uint32_t vreg = *pt_reg;
	//bj_in_core_shd.val_reg2 = vreg;

	bj_asm("mov r21, 0xaaaa");
	bj_asm("movt r21, 0xbbbb");
	bj_asm("mov r20, 0x00fc");
	bj_asm("movt r20, 0x000f");
	//bj_asm("ldr r21, [r20]");
	bj_asm("mov %0, r21" : "=r" (bj_in_core_shd.val_reg2));
	*/
	
	bj_in_core_shd.dbg_progress_flag = 0xeee;
	
	bjk_set_finished(BJ_FINISHED_VAL);
	return 0;
}

	