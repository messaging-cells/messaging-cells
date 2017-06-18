
// attribute.h

#ifndef MC_BOOTER_H
#define MC_BOOTER_H

#include <stdio.h>

#include "debug.h"
#include "stdbool.h"

#include "global.h"

#ifdef __cplusplus
mc_c_decl {
#endif

#define KBY_SZ 1024
#define MBY_SZ 1048576

#define MC_STDERR stderr

#define MC_PURE_LOCAL_ADDR 3
#define MC_CORE_LOCAL_ADDR 4
#define MC_EXTE_LOCAL_ADDR 5


extern mc_link_syms_data_st 	bjh_external_ram_load_data;

#define bjh_disp_to_extnal_ram_pt(disp) (the_str)

extern bool BJH_LOAD_WITH_MEMCPY;

#define BJM_DLMALLOC_HEAP_SZ (10 * MBY_SZ)
extern uint8_t bjm_dlmalloc_heap[BJM_DLMALLOC_HEAP_SZ];

void 
bjh_abort_func(long val, const char* msg);

bool 
bjh_call_assert(bool vv_ck, const char* file, int line, const char* ck_str, const char* msg);

#define bjh_assert(vv) bjh_call_assert(vv, __FILE__, __LINE__, #vv, NULL)

bool
bjh_file_append(char* the_pth, char* the_data, long the_sz);

bool bjh_ck_sys_data(mc_sys_sz_st* sys1);

void
bjh_prt_exception(bjk_glb_sys_st* sh_dat);

int 
bjh_prt_in_core_shd_dat(bjk_glb_sys_st* sh_dat);

bool
bjh_rr_ck_zero(mc_rrarray_st* arr);

void
bjh_rr_print(mc_rrarray_st* arr);

int
bjh_type_sz(mc_type_t tt);

void
bjh_reset_log_file(char* f_nm);

void
bjh_print_out_buffer(mc_rrarray_st* arr, char* f_nm, mc_core_nn_t num_core);

uint8_t*
bjh_read_file(char* the_pth, off_t* size);

int
bjh_write_file(char* the_pth, uint8_t* the_data, long the_sz, int write_once);

int 
bjh_prt_core_call_stack(const char *elf_nm, int addrs_sz, void** stack_addrs);

void
bjh_get_enter(mc_core_co_t row, mc_core_co_t col);

void
bjh_ptr_call_stack_trace();

void
bjh_read_eph_link_syms(const char *executable, mc_link_syms_data_st* syms);

#define	BJH_DBG_COND_COMM(cond, comm)	\
	MC_DBG( \
		if(cond){ \
			comm; \
			printf("\n"); \
		} \
	) \

//--end_of_def

#define BJH_CK(prm) MC_DBG(bjh_assert(prm))

#define BJH_CK_2(prm, comms1) \
	BJH_DBG_COND_COMM((! (prm)), \
		comms1; \
		printf("\n"); \
		bjh_assert(prm); \
	) \
	
//--end_of_def


mc_addr_t
mc_znq_addr_to_eph_addr(mc_addr_t znq_addr);

mc_addr_t
mc_eph_addr_to_znq_addr(mc_addr_t eph_addr);

void
bjm_get_call_stack_trace(size_t trace_strs_sz, char** trace_strs);


#ifdef __cplusplus
}
#endif

#endif // MC_BOOTER_H

