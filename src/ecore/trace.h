
// trace.h

#ifndef BJK_TRACE_H
#define BJK_TRACE_H

#include <inttypes.h>
#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif
	
#define bj_trace_code_dram bj_code_dram
//define bj_trace_code_dram 

uint16_t
bjk_get_call_stack_trace(int16_t sz_trace, void** trace) bj_trace_code_dram;

void 
bjk_abort(bj_addr_t err, int16_t sz_trace, void** trace) bj_trace_code_dram;
	
void 
bjk_wait_sync(uint32_t info, int16_t sz_trace, void** trace) bj_trace_code_dram;
	

#ifdef __cplusplus
}
#endif

#endif // BJK_TRACE_H

