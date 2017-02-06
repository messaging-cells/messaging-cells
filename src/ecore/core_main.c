
#include <stdio.h>
#include <inttypes.h>

#include "global.h"
#include "trace.h"
#include "test1.h"
#include "test_logs.h"

//	register uint16_t pt_jj asm("r40");

void 
prt_aligns(void* ptr){
	int8_t alg = bj_get_aligment(ptr);
	bjk_ilog(alg); 
}

pru_st	arr[tot_objs] bj_align(8);

int main(void)
{
	bjk_init_global();

	bj_id_t koid = bjk_get_coreid();
	bj_consec_t num_core = bj_id_to_nn(koid);

	char** john = (char**)(all_tests[num_core]);
	long john_sz = all_tests_sz[num_core];
	long ii;
	for(ii = 0; ii < john_sz; ii++){
		bjk_slog(john[ii]);
	}

	bj_in_core_shd.dbg_progress_flag = 0xeee;	
	bjk_set_finished(BJ_FINISHED_VAL);
	return 0;
}

int main2(void)
{
	bjk_init_global();

	int kk;
	for(kk = 0; kk < tot_objs; kk++){
		pru_st* obj1 = &(arr[kk]);

		prt_aligns((void*)(obj1)); bjk_slog(".pt_obj1\n"); 
		prt_aligns((void*)(&(obj1->aa))); bjk_slog(".pt_aa\n"); 
		prt_aligns((void*)(&(obj1->bb))); bjk_slog(".pt_bb\n"); 
		prt_aligns((void*)(&(obj1->cc))); bjk_slog(".pt_cc\n"); 

		obj1->bb = 0x11223344;
		bjk_slog(".val_bb = "); bjk_xlog(obj1->bb); bjk_slog(" \n");

		bjk_slog("---------------\n");

	}
	bjk_slog("sizeof(pru_st) = "); bjk_ulog(sizeof(pru_st)); bjk_slog(" \n");

	bj_in_core_shd.dbg_progress_flag = 0xeee;	
	bjk_set_finished(BJ_FINISHED_VAL);
	return 0;
}


int main1(void) {
	bjk_init_global();

	//BJK_CK(ck_01, (aa != aa2));
	
	bj_id_t koid = bjk_get_coreid();
	//bj_consec_t num_core = bj_id_to_nn(koid);

	bjk_slog("HOLA JOSE desde kore ");

	bjk_xlog(koid);
	bjk_slog("\n");

	bj_in_core_shd.dbg_progress_flag = 0xeee;	
	bjk_set_finished(BJ_FINISHED_VAL);
	return 0;
}


