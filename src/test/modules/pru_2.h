
// pru_2.h

#ifndef PRU_2_H
#define PRU_2_H

#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif

void m2_f1_shd() bj_external_code_ram;
void m2_f2_shd() bj_external_code_ram;

void m2_f3_core() bj_mod2_cod;
void m2_main() bj_mod2_cod;

#ifdef __cplusplus
}
#endif

#endif // PRU_2_H

