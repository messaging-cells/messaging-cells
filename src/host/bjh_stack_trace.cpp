

/*------------------------------------------------------------

stack_trace.cpp  

stack_trace funcs.

--------------------------------------------------------------*/

#include <sstream>
#include <execinfo.h>
#include <cstdlib>

#include "bj_stream.h"
#include "ch_string.h"
#include "bjh_stack_trace.h"

bool
print_backtrace( const ch_string & file, int line ){
	bj_out << get_stack_trace(file, line) << bj_eol;
	return true;
}

// USE:        bj_out << get_stack_trace( __FILE__, __LINE__ ) << bj_eol;

ch_string 
get_stack_trace( const ch_string & file, int line ){
	bj_ostr_stream result;
	result << "Call Stack from " << file << ":" << line << "\n";
	const size_t k_max_depth = 100;
	void *stack_addrs[k_max_depth];
	size_t stack_depth;
	char **stack_strings;

	stack_depth = backtrace( stack_addrs, k_max_depth );
	stack_strings = backtrace_symbols( stack_addrs, stack_depth );
	for( size_t i = 1; i < stack_depth; ++i ) {
		//result << "   " << demangle_cxx_name( stack_strings[i] ) << "\n";
		result << "   " << stack_strings[i] << bj_eol;
	}
	result << "(to see full call names link with -rdynamic option)" << bj_eol;
	std::free( stack_strings );

	return result.str();
}


