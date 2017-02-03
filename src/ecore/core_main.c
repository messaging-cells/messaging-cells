
#include <stdio.h>
#include <inttypes.h>

#include "global.h"
#include "trace.h"
#include "test1.h"


//uint16_t * bj_opt_sz_fn fun10();

int
fun9() {
	return 8;
}

uint16_t *
fun10() {
	register uint16_t *pt_jj asm("r40");
	register uint16_t *pt_jj2 asm("r41");
	//pt_jj = &aux_val;
	pt_jj = (uint16_t *)0xaaa;
	pt_jj2 = pt_jj;
	fun9();
	//pt_jj2++;
	//pt_jj += 0xaaa;
	return pt_jj2;
}

int main(void) {
	bjk_init_global();

	//BJK_CK(ck_01, (aa != aa2));
	
	bj_id_t koid = bjk_get_coreid();
	bj_consec_t num_core = bj_id_to_nn(koid);

	bjk_slog("HOLA JOSE desde kore ");
	bjk_xlog(koid);
	bjk_slog("\n");

	bj_in_core_shd.dbg_progress_flag = 0xeee;
	
	bjk_set_finished(BJ_FINISHED_VAL);
	return 0;
}


