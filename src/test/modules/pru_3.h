
// pru_3.h

#ifndef PRU_3_H
#define PRU_3_H

#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif

void m3_f1_shd() bj_code_dram;
void m3_f2_shd() bj_code_dram;

void m3_f3_core() bj_mod3_cod;
void m3_main() bj_mod3_cod;

#ifdef __cplusplus
}
#endif

#endif // PRU_3_H

