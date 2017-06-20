

/*************************************************************

string_hst.hh

Wrapper for string class.

--------------------------------------------------------------*/


#ifndef MC_STRING_H
#define MC_STRING_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>	// used for mc_ofstream

typedef std::string mch_string_t;
typedef std::ostream mch_ostream_t;
typedef std::ostringstream mch_ostr_stream_t;
typedef std::ofstream mch_ofstream_t;

#define mch_out std::cout
#define mch_err std::cerr

#define mch_eol std::endl

#endif // MC_STRING_H


