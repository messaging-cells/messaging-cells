

/*------------------------------------------------------------

bjh_stack_trace.cpp  

stack_trace funcs.

--------------------------------------------------------------*/

#include <sstream>
#include <execinfo.h>
#include <cstdlib>

//include "bj_stream.h"
#include "string_hst.h"
#include "stack_trace_hst.h"

bool
bjh_print_backtrace( const bjh_string_t & file, int line ){
	bjh_out << bjh_get_stack_trace(file, line) << "\n";
	return true;
}

// USE:        bj_out << get_stack_trace( __FILE__, __LINE__ ) << bj_eol;

bjh_string_t 
bjh_get_stack_trace( const bjh_string_t & file, int line ){
	bjh_ostr_stream_t result;
	result << "Call Stack from " << file << ":" << line << "\n";
	const size_t k_max_depth = 100;
	void *stack_addrs[k_max_depth];
	size_t stack_depth;
	char **stack_strings;

	stack_depth = backtrace( stack_addrs, k_max_depth );
	stack_strings = backtrace_symbols( stack_addrs, stack_depth );
	for( size_t i = 1; i < stack_depth; ++i ) {
		//result << "   " << demangle_cxx_name( stack_strings[i] ) << "\n";
		result << "   " << stack_strings[i] << "\n";
	}
	result << "(to see full call names link with -rdynamic option)" << "\n";
	std::free( stack_strings );

	return result.str();
}


