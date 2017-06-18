
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

	bjm_get_call_stack_trace(MC_MAX_CALL_STACK_SZ, glb->bjk_dbg_call_nams_stack_trace);
	return 0;
}

void 
bjk_wait_sync(uint32_t info, int16_t sz_trace, void** trace){
	mc_off_core_st* off_core_pt = BJK_GLB_SYS->off_core_pt;
	if(off_core_pt == mc_null){
		return;
	}
	if((sz_trace > 0) && (trace != mc_null)){
		bjk_get_call_stack_trace(sz_trace, trace);
	}
	if(info == MC_NOT_WAITING){
		info = MC_WAITING_ENTER;
	}
	mc_set_off_chip_var(off_core_pt->is_waiting, info);

	uint8_t& sync_sg = BJK_GLB_SYS->bjk_sync_signal;
	while(sync_sg == 0){
		sched_yield();
	}

	mc_set_off_chip_var(off_core_pt->is_waiting, MC_NOT_WAITING);
	sync_sg = 0;
}

