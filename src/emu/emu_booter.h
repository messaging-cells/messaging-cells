
// attribute.h

#ifndef BJ_BOOTER_H
#define BJ_BOOTER_H

#include <stdio.h>

#include "debug.h"
#include "stdbool.h"

#include "shared.h"

#ifdef __cplusplus
bj_c_decl {
#endif

#define bj_as_pt_char(the_str) (the_str)

void 
bjh_abort_func(long val, const char* msg);

bool 
bjh_call_assert(bool vv_ck, const char* file, int line, const char* ck_str, const char* msg);

bool
bjh_file_append(char* the_pth, char* the_data, long the_sz);


#define bjh_assert(vv) \
	bjh_call_assert(vv, bj_as_pt_char(__FILE__), __LINE__, bj_as_pt_char(#vv), NULL)

	
#define	BJH_DBG_COND_COMM(cond, comm)	\
	BJ_DBG( \
		if(cond){ \
			comm; \
			printf("\n"); \
		} \
	) \

//--end_of_def

#define BJH_CK(prm) BJ_DBG(bjh_assert(prm))

#define BJH_CK_2(prm, comms1) \
	BJH_DBG_COND_COMM((! (prm)), \
		comms1; \
		printf("\n"); \
		bjh_assert(prm); \
	) \
	
//--end_of_def



#ifdef __cplusplus
}
#endif

#endif // BJ_BOOTER_H

