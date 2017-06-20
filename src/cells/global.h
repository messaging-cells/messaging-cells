
// global.h

#ifndef MC_GLOBAL_H
#define MC_GLOBAL_H

#include "debug.h"
#include "err_msgs.h"
#include "shared.h"
#include "loader.h"
#include "trace.h"

#ifdef __cplusplus
mc_c_decl {
#endif

//=====================================================================
// in ekore shared memory

extern unsigned mck_original_ivt_0;

//define MC_MAX_STR_SZ 80
// WHEN TESTING LOGS USE
#define MC_MAX_STR_SZ MC_OUT_BUFF_SZ	

struct mc_aligned mck_glb_sys_def { 
	uint32_t 	magic_id;
	void** 		dbg_stack_trace;
	
	mc_addr_t 	dbg_min_sp;
	mc_addr_t 	dbg_error_code;
	uint32_t 	dbg_progress_flag;

	mc_addr_t	znq_shd_mem_base;
	mc_addr_t	eph_shd_mem_base;

	mc_core_id_t the_core_id;
	mc_core_nn_t the_core_nn;
	mc_core_co_t the_core_ro;
	mc_core_co_t the_core_co;

	mc_core_id_t		inited_core;
	mck_exception_t 	exception_code;
	
	uint16_t 	binder_sz;
	uint16_t 	kernel_sz;
	uint16_t 	agent_sz;
	uint16_t 	cell_sz;
	uint16_t 	missive_sz;
	uint16_t 	agent_grp_sz;
	uint16_t 	agent_ref_sz;

	uint16_t 	mck_glb_sys_st_sz;

	uint32_t 	magic_end;

	mc_off_core_st* off_core_pt;
	mc_rrarray_st* 	write_rrarray;
	uint8_t 		dbg_out_str[MC_MAX_STR_SZ];

	void*			pt_core_kernel;

	EPH_CODE(
		void* 		mck_dbg_call_stack_trace[MC_MAX_CALL_STACK_SZ];
		uint16_t 	mck_trace_err;
	)
	EMU_CODE(
		uint8_t 	mck_sync_signal;
		char* 		mck_dbg_call_nams_stack_trace[MC_MAX_CALL_STACK_SZ];
	)
};
typedef struct mck_glb_sys_def mck_glb_sys_st;

//if defined(MC_IS_EPH_CODE) && !defined(IS_EMU_COD) 

#ifdef MC_IS_EPH_CODE
	mck_glb_sys_st*
	mck_get_first_glb_sys() mc_external_code_ram;

	extern mck_glb_sys_st*	mck_glb_pt_sys_data;
	#define BJK_FIRST_GLB_SYS mck_get_first_glb_sys()
	#define BJK_GLB_SYS (mck_glb_pt_sys_data)
#else
	mck_glb_sys_st*
	mck_get_glb_sys();

	#define BJK_FIRST_GLB_SYS mck_get_glb_sys()
	#define BJK_GLB_SYS mck_get_glb_sys()
#endif

#ifdef MC_IS_EPH_CODE
	extern mc_off_sys_st mck_external_host_data_obj;
	#define BJK_PT_EXTERNAL_HOST_DATA (&mck_external_host_data_obj)
#endif

#ifdef MC_IS_ZNQ_CODE
	extern mc_off_sys_st* mcz_pt_external_host_data_obj;
	#define BJK_PT_EXTERNAL_HOST_DATA mcz_pt_external_host_data_obj
#endif

#ifdef MC_IS_EMU_CODE
	extern mc_off_sys_st mcm_external_host_data_obj;
	#define BJK_PT_EXTERNAL_HOST_DATA (&mcm_external_host_data_obj)
#endif


//=====================================================================
// global funcs

void 
mck_abort(mc_addr_t err, char* msg) mc_external_code_ram;

void mc_inline_fn
mck_set_finished(uint8_t val) {
	mc_off_core_st* off_core_pt = BJK_GLB_SYS->off_core_pt; 
	if(off_core_pt != mc_null){
		mc_set_off_chip_var(off_core_pt->is_finished, val);
	}
}

void 
mck_glb_init() mc_external_code_ram;

void 
mck_glb_finish() mc_external_code_ram;

#ifndef MC_IS_EMU_CODE
void 
abort(void) mc_external_code_ram;		// Needed when -Os flag is set
#endif

#define MC_B_OPCODE 0x000000e8 // OpCode of the B<*> instruction

void 
mck_set_irq0_handler() mc_external_code_ram;

//======================================================================
// mc_asserts

#define BJK_INCORE_ASSERT(cond) MC_DBG(if(! (cond)){ mck_abort((mc_addr_t)(void*)err_11, err_11); } )

// end_of_macro

#ifdef MC_IS_EPH_CODE
	#define BJK_CK(cond) BJK_INCORE_ASSERT(cond)
#endif

#ifdef MC_IS_EMU_CODE
	#define BJK_CK(cond) EMU_CK(cond)
#endif

#ifdef MC_IS_ZNQ_CODE
	#include "booter.h"
	#define BJK_CK(cond) BJH_CK(cond)
#endif

#define BJK_MARK_PLACE(nam) MC_DBG(mc_asm(#nam ":")) 

//======================================================================
// naked inside normal func (insted of naked attribute)

#define BJK_START_NAKED_FUNC(nam) \
	mc_asm( \
		".section .text \n\t" \
		".balign 4 \n\t" \
		".global " #nam " \n" \
	#nam ": \n\t" \
	); \

// end_of_macro

#define BJK_END_NAKED_FUNC() \
	mc_asm( \
		"trap 0x3 \n\t" \
		".previous \n\t" \
	); \

// end_of_macro

//define DBG_CODE_SHD_SZ 20
//extern uint16_t DBG_CODE_SHD_1[DBG_CODE_SHD_SZ];

void test_link_shd_code() mc_external_code_ram;

void ck_shd_code();

#ifdef MC_IS_EPH_CODE
	mc_inline_fn uint16_t*
	mck_get_stack_pointer() {
		uint16_t* sp_val = 0;
		mc_asm("mov %0, sp" : "=r" (sp_val));
		return sp_val;
	}

	mc_inline_fn void
	mck_update_min_stack_pointer() {
		mc_addr_t curr_sp = (mc_addr_t)mck_get_stack_pointer();
		mc_addr_t min_sp = BJK_GLB_SYS->dbg_min_sp;
		if((min_sp == 0) || (curr_sp < min_sp)){
			BJK_GLB_SYS->dbg_min_sp = curr_sp;
		}
	}
	#define BJK_UPDATE_MIN_SP() MC_DBG(mck_update_min_stack_pointer())
#else
	#define BJK_UPDATE_MIN_SP() 
#endif

mc_inline_fn 
uint32_t 
mck_get_tot_modules(){
	return BJK_PT_EXTERNAL_HOST_DATA->tot_modules;
}

mc_addr_t 
mck_get_module_address(uint32_t modl_idx) mc_external_code_ram;

char* 
mck_get_module_name(uint32_t modl_idx) mc_external_code_ram;

void
mck_fill_module_external_addresses(char** user_order, mc_addr_t* user_ext_addr) mc_external_code_ram;

bool
mck_load_module(mc_addr_t ext_addr) mc_external_code_ram;

void mc_host_init() mc_external_code_ram;
void mc_host_run() mc_external_code_ram;
void mc_host_finish() mc_external_code_ram;

extern mc_core_nn_t mch_first_load_core_nn;
extern char* mch_epiphany_elf_path;
extern mc_load_map_st* mck_first_load_map mc_external_data_ram;
extern void mc_cores_main() mc_external_code_ram;
extern int mc_host_main(int argc, char *argv[]) mc_external_code_ram;


#ifdef __cplusplus
}
#endif

#endif // MC_GLOBAL_H

