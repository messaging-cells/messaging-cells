
// trace.h

#ifndef BJK_TRACE_H
#define BJK_TRACE_H

#include <inttypes.h>
#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif
	
uint16_t
bjk_get_call_stack_trace(int16_t sz_trace, void** trace) bj_external_code_ram;

void 
bjk_wait_sync(uint32_t info, int16_t sz_trace, void** trace) bj_external_code_ram;
	

#ifdef __cplusplus
}
#endif

#endif // BJK_TRACE_H

