
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

bool ck_sys_data(bj_sys_sz_st* sys1);

int prt_inko_shd_dat(bj_in_core_st* sh_dat);

bool
bj_rr_ck_zero(bj_rrarray_st* arr);

void
bj_rr_print(bj_rrarray_st* arr);

int
bj_type_sz(bj_type_t tt);

void
print_out_buffer(bj_rrarray_st* arr, char* f_nm, bj_core_nn_t num_core);

int
write_file(char* the_pth, char* the_data, long the_sz, int write_once);


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

#ifdef IS_EMU_CODE
	#define EMU_CODE(cod) cod
	#define ZNQ_CODE(cod) 
#else
	#define EMU_CODE(cod) 
	#define ZNQ_CODE(cod) cod
#endif

#ifdef __cplusplus
}
#endif

#endif // BJ_BOOTER_H

