
// common.h

#ifndef COMMON_H
#define COMMON_H

#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif

//define prts bjk_slog2

#define prts(ss) comm_prt(as_pt_char(ss))

class comm_cla {
public:
	int aa;
	long bb;

	comm_cla() bj_comm_cod;

	~comm_cla() bj_comm_cod;

	void init_comm_cla() bj_comm_cod;

	void method1() bj_comm_cod;
};

void comm_prt(char* val) bj_comm_cod;

void comm_f1_core() bj_comm_cod;
void comm_f2_core() bj_comm_cod;

#ifdef __cplusplus
}
#endif

#endif // COMMON_H

