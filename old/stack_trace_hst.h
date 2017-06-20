
/*------------------------------------------------------------

mch_stack_trace.h

func to print a stack trace.

--------------------------------------------------------------*/

#ifndef MC_STACK_TRACE_H
#define MC_STACK_TRACE_H

#include "string_hst.h"

mch_string_t	mch_get_stack_trace( const mch_string_t & file, int line );

#define STACK_STR mch_get_stack_trace(__FILE__, __LINE__)


#endif		// MC_STACK_TRACE_H


