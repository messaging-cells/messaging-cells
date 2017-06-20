
// common.h

#ifndef COMMON_H
#define COMMON_H

#include "attribute.h"

#ifdef __cplusplus
mc_c_decl {
#endif

#define prts(ss) mck_slog2(ss)

//define prts(ss) comm_prt(as_pt_char(ss))

class comm_cla {
public:
	int aa;
	long bb;

	comm_cla() mc_comm_cod;

	~comm_cla() mc_comm_cod;

	void init_comm_cla() mc_comm_cod;

	void method1() mc_comm_cod;
};

void comm_prt(char* val) mc_comm_cod;

void comm_f1_core() mc_comm_cod;
void comm_f2_core() mc_comm_cod;

#ifdef __cplusplus
}
#endif

#endif // COMMON_H

