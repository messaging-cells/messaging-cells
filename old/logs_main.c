
#include <stdio.h>
#include <inttypes.h>

#include "global.h"
#include "trace.h"
#include "test_align.h"
#include "test_logs.h"
#include "cell.h"

//	register uint16_t pt_jj asm("r40");

int main(void) {
	mck_init_global();

	mc_core_id_t koid = mck_get_core_id();
	mc_core_nn_t num_core = mc_id_to_nn(koid);

	char** john = (char**)(all_tests[num_core]);
	long john_sz = all_tests_sz[num_core];
	long ii;
	for(ii = 0; ii < john_sz; ii++){
		mck_slog(john[ii]);
	}

	mc_in_core_shd.dbg_progress_flag = 0xeee;	
	mck_set_finished(MC_FINISHED_VAL);
	return 0;
}


