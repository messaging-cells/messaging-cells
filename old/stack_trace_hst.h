
/*------------------------------------------------------------

bjh_stack_trace.h

func to print a stack trace.

--------------------------------------------------------------*/

#ifndef BJ_STACK_TRACE_H
#define BJ_STACK_TRACE_H

#include "string_hst.h"

bjh_string_t	bjh_get_stack_trace( const bjh_string_t & file, int line );

#define STACK_STR bjh_get_stack_trace(__FILE__, __LINE__)


#endif		// BJ_STACK_TRACE_H


