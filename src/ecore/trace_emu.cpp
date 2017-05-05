
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "trace.h"

#include "booter.h"
#include "thread_emu.hh"

//=====================================================================

uint16_t
bjk_get_call_stack_trace(int16_t, void**) {
	bjk_glb_sys_st* glb = BJK_GLB_SYS;
	void* 		trace[BJ_MAX_CALL_STACK_SZ];

	bj_memset((uint8_t*)trace, 0, BJ_MAX_CALL_STACK_SZ * sizeof(void*));
	bj_memset((uint8_t*)glb->bjk_dbg_call_nams_stack_trace, 0, BJ_MAX_CALL_STACK_SZ * sizeof(char*));

	size_t trace_sz = backtrace(trace, BJ_MAX_CALL_STACK_SZ);
	char **stack_strings = backtrace_symbols(trace, trace_sz);
	for( size_t ii = 1; ii < trace_sz; ii++ ) {
		if(ii >= BJ_MAX_CALL_STACK_SZ){ break; }
		glb->bjk_dbg_call_nams_stack_trace[ii] = stack_strings[ii];
	}
	//result << "(to see full call names link with -rdynamic option)" << "\n";
	free( stack_strings );
	return 0;
}

void 
bjk_wait_sync(uint32_t info, int16_t sz_trace, void** trace){
	bj_off_core_st* off_core_pt = BJK_GLB_SYS->off_core_pt;
	if(off_core_pt == bj_null){
		return;
	}
	if((sz_trace > 0) && (trace != bj_null)){
		bjk_get_call_stack_trace(sz_trace, trace);
	}
	if(info == BJ_NOT_WAITING){
		info = BJ_WAITING_ENTER;
	}
	bj_set_off_chip_var(off_core_pt->is_waiting, info);

	uint8_t& sync_sg = BJK_GLB_SYS->bjk_sync_signal;
	while(sync_sg == 0){
		sched_yield();
	}

	bj_set_off_chip_var(off_core_pt->is_waiting, BJ_NOT_WAITING);
	sync_sg = 0;
}

