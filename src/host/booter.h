
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

// TODO: replace with platform data
#define BJL_EMEM_SIZE (0x02000000)

extern bj_sys_sz_st bj_glb_host_sys;

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

uint8_t*
read_file(char* the_pth, off_t* size);

int
write_file(char* the_pth, uint8_t* the_data, long the_sz, int write_once);

int 
bjh_prt_core_call_stack(const char *elf_nm, int addrs_sz, void** stack_addrs);

void
get_enter(bj_core_co_t row, bj_core_co_t col);

void
bjh_ptr_call_stack_trace();

#define BJH_STR_EXTERNAL_CODE_SIZE "EXTERNAL_CODE_SIZE"
#define BJH_STR_EXTERNAL_LOAD_SIZE "EXTERNAL_LOAD_SIZE"
#define BJH_STR_EXTERNAL_DATA_SIZE "EXTERNAL_DATA_SIZE"
#define BJH_STR_EXTERNAL_ALLOC_SIZE "EXTERNAL_ALLOC_SIZE"

#define BJH_STR_EXTERNAL_ORIG "EXTERNAL_ORIG"
#define BJH_STR_EXTERNAL_CODE_ORIG "EXTERNAL_CODE_ORIG"
#define BJH_STR_EXTERNAL_LOAD_ORIG "EXTERNAL_LOAD_ORIG"
#define BJH_STR_EXTERNAL_DATA_ORIG "EXTERNAL_DATA_ORIG"
#define BJH_STR_EXTERNAL_ALLOC_ORIG "EXTERNAL_ALLOC_ORIG"

#define BJH_TOT_LOAD_SYMS 9

void*
bjh_find_link_script_addr(const char* nam, int addrs_sz, void** syms_addrs);

int 
bjh_read_eph_elf_syms(const char *elf_nm, int addrs_sz, void** syms_addrs);

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

