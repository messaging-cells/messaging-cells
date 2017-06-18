
// pru_1.h

#ifndef PRU_1_H
#define PRU_1_H

#include "attribute.h"

#ifdef __cplusplus
mc_c_decl {
#endif

void m1_f1_shd() mc_external_code_ram;
void m1_f2_shd() mc_external_code_ram;

void m1_f3_core() mc_mod1_cod;
void m1_main() mc_mod1_cod;

#ifdef __cplusplus
}
#endif

#endif // PRU_1_H

