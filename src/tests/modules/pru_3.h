
// pru_3.h

#ifndef PRU_3_H
#define PRU_3_H

#include "attribute.h"

#ifdef __cplusplus
mc_c_decl {
#endif

void m3_f1_shd() mc_external_code_ram;
void m3_f2_shd() mc_external_code_ram;

void m3_f3_core() mc_mod3_cod;
void m3_main() mc_mod3_cod;

#ifdef __cplusplus
}
#endif

#endif // PRU_3_H

