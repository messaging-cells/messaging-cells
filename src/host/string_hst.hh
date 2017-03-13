

/*************************************************************

string_hst.hh

Wrapper for string class.

--------------------------------------------------------------*/


#ifndef BJ_STRING_H
#define BJ_STRING_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>	// used for bj_ofstream

typedef std::string bjh_string_t;
typedef std::ostream bjh_ostream_t;
typedef std::ostringstream bjh_ostr_stream_t;
typedef std::ofstream bjh_ofstream_t;

#define bjh_out std::cout
#define bjh_err std::cerr

#define bjh_eol std::endl

#endif // BJ_STRING_H


