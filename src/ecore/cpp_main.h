
// cpp_main.h

#ifndef CPP_MAIN_H
#define CPP_MAIN_H

#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif

void 
init_cpp_main() bj_code_dram;

bj_opt_sz_fn 
void
cpp_main() bj_code_dram;

#ifdef __cplusplus
}
#endif

#endif // CPP_MAIN_H

