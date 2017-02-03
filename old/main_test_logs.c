#include "test_logs.h"


	char** john = (char**)(all_tests[num_core]);
	long john_sz = all_tests_sz[num_core];
	long ii;
	for(ii = 0; ii < john_sz; ii++){
		uint16_t oln = bj_strlen(john[ii]) + 1;
		uint16_t ow = bj_rr_write_obj(bj_write_rrarray, oln, (uint8_t*)john[ii]);
		if(ow == 0){
			bjk_wait_sync(BJ_WAITING_BUFFER, 0, NULL);
		}
	}

