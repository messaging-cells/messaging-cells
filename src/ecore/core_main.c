
#include <stdio.h>
#include <inttypes.h>

#include "global.h"
#include "trace.h"
#include "test_align.h"
//include "test_logs.h"
#include "cpp_main.h"

//	register uint16_t pt_jj asm("r40");

int main(void) {
	bjk_init_global();

	cpp_main();

	bj_in_core_shd.dbg_progress_flag = 0xeee;	
	bjk_set_finished(BJ_FINISHED_VAL);
	return 0;
}


