
#include <stdio.h>
#include <inttypes.h>

#include "global.h"
#include "trace.h"
//include "test_align.h"
#include "test_logs.h"
#include "cpp_main.h"

//	register uint16_t pt_jj asm("r40");

int core_main() {
	bjk_init_global();

	cpp_main();

	bjk_slog("FINISHED !!\n");

	bjk_get_glb_in_core_shd()->dbg_progress_flag = 0xeee;	
	bjk_set_finished(BJ_FINISHED_VAL);
	return 0;
}

int test_logs_main() {
	bjk_init_global();

	bj_core_id_t koid = bjk_get_core_id();
	bj_core_nn_t num_core = bj_id_to_nn(koid);

	char** john = (char**)(all_tests[num_core]);
	long john_sz = all_tests_sz[num_core];
	long ii;
	for(ii = 0; ii < john_sz; ii++){
		bjk_slog(john[ii]);
	}

	bjk_get_glb_in_core_shd()->dbg_progress_flag = 0xeee;	
	bjk_set_finished(BJ_FINISHED_VAL);
	return 0;
}

int main() {
	//test_logs_main();
	//core_main();
	printf("HOLA JOSE LUIS\n");
}


