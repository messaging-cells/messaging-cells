
// global.h

#ifndef BJ_GLOBAL_H
#define BJ_GLOBAL_H

#include "debug.h"
#include "err_msgs.h"
#include "shared.h"
#include "loader.h"
#include "trace.h"

#ifdef __cplusplus
bj_c_decl {
#endif

//=====================================================================
// in ekore shared memory

//define BJ_MAX_STR_SZ 80
// WHEN TESTING LOGS USE
#define BJ_MAX_STR_SZ BJ_OUT_BUFF_SZ	

struct bj_aligned bjk_glb_sys_def { 
	uint32_t 	magic_id;
	void** 		dbg_stack_trace;
	
	bj_addr_t 	dbg_min_sp;
	bj_addr_t 	dbg_error_code;
	uint32_t 	dbg_progress_flag;

	bj_addr_t	znq_shd_mem_base;
	bj_addr_t	eph_shd_mem_base;

	bj_core_id_t the_core_id;
	bj_core_nn_t the_core_nn;
	bj_core_co_t the_core_ro;
	bj_core_co_t the_core_co;

	bj_core_id_t		inited_core;
	bjk_exception_t 	exception_code;
	
	uint16_t 	binder_sz;
	uint16_t 	kernel_sz;
	uint16_t 	agent_sz;
	uint16_t 	actor_sz;
	uint16_t 	missive_sz;
	uint16_t 	agent_grp_sz;
	uint16_t 	agent_ref_sz;

	uint16_t 	bjk_glb_sys_st_sz;

	uint32_t 	magic_end;

	bj_off_core_st* off_core_pt;
	bj_rrarray_st* 	write_rrarray;
	uint8_t 		dbg_out_str[BJ_MAX_STR_SZ];

	void*			pt_core_kernel;

	EPH_CODE(
		void* 		bjk_dbg_call_stack_trace[BJ_MAX_CALL_STACK_SZ];
		uint16_t 	bjk_trace_err;
	)
	EMU_CODE(
		uint8_t 	bjk_sync_signal;
		char* 		bjk_dbg_call_nams_stack_trace[BJ_MAX_CALL_STACK_SZ];
	)
};
typedef struct bjk_glb_sys_def bjk_glb_sys_st;

//if defined(BJ_IS_EPH_CODE) && !defined(IS_EMU_COD) 

#ifdef BJ_IS_EPH_CODE
	bjk_glb_sys_st*
	bjk_get_first_glb_sys() bj_external_code_ram;

	extern bjk_glb_sys_st*	bjk_glb_pt_sys_data;
	#define BJK_FIRST_GLB_SYS bjk_get_first_glb_sys()
	#define BJK_GLB_SYS (bjk_glb_pt_sys_data)
#else
	bjk_glb_sys_st*
	bjk_get_glb_sys();

	#define BJK_FIRST_GLB_SYS bjk_get_glb_sys()
	#define BJK_GLB_SYS bjk_get_glb_sys()
#endif

#ifdef BJ_IS_EPH_CODE
	extern bj_off_sys_st bjk_external_host_data_obj;
	#define BJK_PT_EXTERNAL_HOST_DATA (&bjk_external_host_data_obj)
#endif

#ifdef BJ_IS_ZNQ_CODE
	extern bj_off_sys_st* bjz_pt_external_host_data_obj;
	#define BJK_PT_EXTERNAL_HOST_DATA bjz_pt_external_host_data_obj
#endif

#ifdef BJ_IS_EMU_CODE
	extern bj_off_sys_st bjm_external_host_data_obj;
	#define BJK_PT_EXTERNAL_HOST_DATA (&bjm_external_host_data_obj)
#endif


//=====================================================================
// global funcs

void 
bjk_abort(bj_addr_t err, char* msg) bj_external_code_ram;

void bj_inline_fn
bjk_set_finished(uint8_t val) {
	bj_off_core_st* off_core_pt = BJK_GLB_SYS->off_core_pt; 
	if(off_core_pt != bj_null){
		bj_set_off_chip_var(off_core_pt->is_finished, val);
	}
}

void 
bjk_glb_init() bj_external_code_ram;

void 
bjk_glb_finish() bj_external_code_ram;

#ifndef BJ_IS_EMU_CODE
void 
abort(void) bj_external_code_ram;		// Needed when -Os flag is set
#endif

#define BJ_B_OPCODE 0x000000e8 // OpCode of the B<*> instruction

void 
bjk_set_irq0_handler() bj_external_code_ram;

//======================================================================
// bj_asserts

#define BJK_INCORE_ASSERT(cond) BJ_DBG(if(! (cond)){ bjk_abort((bj_addr_t)(void*)err_11, err_11); } )

// end_of_macro

#ifdef BJ_IS_EPH_CODE
	#define BJK_CK(cond) BJK_INCORE_ASSERT(cond)
#endif

#ifdef BJ_IS_EMU_CODE
	#define BJK_CK(cond) EMU_CK(cond)
#endif

#ifdef BJ_IS_ZNQ_CODE
	#include "booter.h"
	#define BJK_CK(cond) BJH_CK(cond)
#endif

#define BJK_MARK_PLACE(nam) BJ_DBG(bj_asm(#nam ":")) 

//======================================================================
// naked inside normal func (insted of naked attribute)

#define BJK_START_NAKED_FUNC(nam) \
	bj_asm( \
		".section .text \n\t" \
		".balign 4 \n\t" \
		".global " #nam " \n" \
	#nam ": \n\t" \
	); \

// end_of_macro

#define BJK_END_NAKED_FUNC() \
	bj_asm( \
		"trap 0x3 \n\t" \
		".previous \n\t" \
	); \

// end_of_macro

//define DBG_CODE_SHD_SZ 20
//extern uint16_t DBG_CODE_SHD_1[DBG_CODE_SHD_SZ];

void test_link_shd_code() bj_external_code_ram;

void ck_shd_code();

#ifdef BJ_IS_EPH_CODE
	bj_inline_fn uint16_t*
	bjk_get_stack_pointer() {
		uint16_t* sp_val = 0;
		bj_asm("mov %0, sp" : "=r" (sp_val));
		return sp_val;
	}

	bj_inline_fn void
	bjk_update_min_stack_pointer() {
		bj_addr_t curr_sp = (bj_addr_t)bjk_get_stack_pointer();
		bj_addr_t min_sp = BJK_GLB_SYS->dbg_min_sp;
		if((min_sp == 0) || (curr_sp < min_sp)){
			BJK_GLB_SYS->dbg_min_sp = curr_sp;
		}
	}
	#define BJK_UPDATE_MIN_SP() BJ_DBG(bjk_update_min_stack_pointer())
#else
	#define BJK_UPDATE_MIN_SP() 
#endif

void bj_host_init() bj_external_code_ram;
void bj_host_run() bj_external_code_ram;
void bj_host_finish() bj_external_code_ram;


#ifdef __cplusplus
}
#endif

#endif // BJ_GLOBAL_H

