
#include <stdio.h>
#include <inttypes.h>

#include "global.h"
#include "trace.h"
//include "test_align.h"
#include "test_logs.h"
#include "cpp_main.h"

//	register uint16_t pt_jj asm("r40");

void core_main() {
	bjk_glb_init();

	cpp_main();

	bjk_slog("FINISHED !!\n");

	bjk_glb_finish();
}

void test_logs_main() {
	bjk_glb_init();

	bj_core_id_t koid = bjk_get_core_id();
	bj_core_nn_t num_core = bj_id_to_nn(koid);

	char** john = (char**)(all_tests[num_core]);
	long john_sz = all_tests_sz[num_core];
	long ii;
	for(ii = 0; ii < john_sz; ii++){
		bjk_slog(john[ii]);
	}

	bjk_glb_finish();
}

int main() {
	//test_logs_main();
	core_main();
	return 0;
}


