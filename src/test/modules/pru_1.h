
// pru_1.h

#ifndef PRU_1_H
#define PRU_1_H

#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif

void m1_f1_shd() bj_code_dram;
void m1_f2_shd() bj_code_dram;

void m1_f3_core() bj_mod1_cod;
void m1_main() bj_mod1_cod;

#ifdef __cplusplus
}
#endif

#endif // PRU_1_H

