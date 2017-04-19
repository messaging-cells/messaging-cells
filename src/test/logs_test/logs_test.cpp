
#include "data_logs.h"
#include "logs_test.hh"

int main() {
	logs_test();
	return 0;
}

void logs_test() {
	bjk_glb_init();

	bj_core_id_t koid = bjk_get_core_id();
	bj_core_nn_t num_core = bj_id_to_nn(koid);

	char** john = (char**)(all_log_tests[num_core]);
	long john_sz = all_log_tests_sz[num_core];
	long ii;
	for(ii = 0; ii < john_sz; ii++){
		bjk_slog(john[ii]);
	}

	bjk_glb_finish();
}


