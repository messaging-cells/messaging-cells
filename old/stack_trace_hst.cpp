

/*------------------------------------------------------------

mch_stack_trace.cpp  

stack_trace funcs.

--------------------------------------------------------------*/

#include <sstream>
#include <execinfo.h>
#include <cstdlib>

//include "mc_stream.h"
#include "string_hst.h"
#include "stack_trace_hst.h"

bool
mch_print_backtrace( const mch_string_t & file, int line ){
	mch_out << mch_get_stack_trace(file, line) << "\n";
	return true;
}

// USE:        mc_out << get_stack_trace( __FILE__, __LINE__ ) << mc_eol;

mch_string_t 
mch_get_stack_trace( const mch_string_t & file, int line ){
	mch_ostr_stream_t result;
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
	std::free( stack_strings );

	return result.str();
}


