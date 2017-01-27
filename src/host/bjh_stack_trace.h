
/*------------------------------------------------------------

stack_trace.h

func to print a stack trace.

--------------------------------------------------------------*/

#ifndef STACK_TRACE_H
#define STACK_TRACE_H

#include "bj_string.h"

bj_string	get_stack_trace( const bj_string & file, int line );

#define STACK_STR get_stack_trace(__FILE__, __LINE__)


#endif		// STACK_TRACE_H


