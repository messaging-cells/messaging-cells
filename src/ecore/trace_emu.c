
#include "global.h"
#include "trace.h"

void* 		bjk_dbg_call_stack_trace[BJ_MAX_CALL_STACK_SZ];
uint16_t 	bjk_trace_err;

//=====================================================================

void 
bjk_abort(bj_addr_t err, int16_t sz_trace, void** trace) {
}

uint16_t
bjk_get_call_stack_trace(int16_t sz, void** trace) {
	return 0;
}

void 
bjk_wait_sync(uint32_t info, int16_t sz_trace, void** trace){
}

