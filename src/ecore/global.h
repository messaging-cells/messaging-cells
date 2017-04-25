
// global.h

#ifndef BJ_GLOBAL_H
#define BJ_GLOBAL_H

#include "debug.h"
#include "shared.h"
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
	bj_off_core_st* off_core_pt;
	bj_rrarray_st* 	write_rrarray;
	bj_in_core_st 	in_core_shd;
	uint8_t 		dbg_out_str[BJ_MAX_STR_SZ];

	CORE_CODE(
		void* 		bjk_dbg_call_stack_trace[BJ_MAX_CALL_STACK_SZ];
		uint16_t 	bjk_trace_err;
		bj_addr_t 	bjk_min_sp;
	)
	EMU_CODE(
		uint8_t 	bjk_sync_signal;
		char* 		bjk_dbg_call_nams_stack_trace[BJ_MAX_CALL_STACK_SZ];
	)
};
typedef struct bjk_glb_sys_def bjk_glb_sys_st;

#if defined(IS_CORE_CODE) && !defined(IS_EMU_COD) 
	bjk_glb_sys_st*
	bjk_get_first_glb_sys() bj_code_dram;

	extern bjk_glb_sys_st*	bjk_glb_pt_sys_data;
	#define BJK_FIRST_GLB_SYS bjk_get_first_glb_sys()
	#define BJK_GLB_SYS (bjk_glb_pt_sys_data)
	#define BJK_GLB_IN_CORE_SHD (&(bjk_glb_pt_sys_data->in_core_shd))
#else
	bjk_glb_sys_st*
	bjk_get_glb_sys();

	bj_inline_fn bj_in_core_st* 
	bjk_get_glb_in_core_shd(){
		return &(bjk_get_glb_sys()->in_core_shd);
	}

	#define BJK_FIRST_GLB_SYS bjk_get_glb_sys()
	#define BJK_GLB_SYS bjk_get_glb_sys()
	#define BJK_GLB_IN_CORE_SHD bjk_get_glb_in_core_shd()
#endif


//=====================================================================
// global funcs

void bj_inline_fn
bjk_set_finished(uint8_t val) {
	bj_off_core_st* off_core_pt = BJK_GLB_SYS->off_core_pt; 
	if(off_core_pt != bj_null){
		bj_set_off_chip_var(off_core_pt->is_finished, val);
	}
}

void 
bjk_glb_init() bj_code_dram;

void 
bjk_glb_finish() bj_code_dram;

#ifndef IS_EMU_CODE
void 
abort(void) bj_code_dram;		// Needed when -Os flag is set
#endif

#define BJ_B_OPCODE 0x000000e8 // OpCode of the B<*> instruction

void 
bjk_set_irq0_handler() bj_code_dram;

//======================================================================
// bj_asserts

#define BJK_OFFCHIP_ASSERT(nam, sec, cond) \
	BJ_DBG( \
	{ \
		bj_asm( \
			"gid \n\t" \
			"mov r62, lr \n\t" \
			"mov r61, %low(" #nam ") \n\t" \
			"movt r61, %high(" #nam ") \n\t" \
			"jalr r61 \n\t" \
			".section " #sec " \n\t" \
			".balign 4 \n\t" \
			".global " #nam " \n" \
			#nam ": \n\t" \
		); \
		if(! (cond)){ \
			bj_addr_t nm_addr; \
			bj_asm( \
				"mov r61, %low(" #nam ") \n\t" \
				"movt r61, %high(" #nam ") \n\t" \
			); \
			bj_asm("mov %0, r61" : "=r" (nm_addr)); \
			bjk_abort(nm_addr, 0, bj_null); \
		} \
		bj_asm( \
			"mov r61, %low(end_" #nam ") \n\t" \
			"movt r61, %high(end_" #nam ") \n\t" \
			"jalr r61 \n\t" \
			"trap 0x3 \n\t" \
			"rts \n\t" \
			".previous \n\t" \
			".balign 4 \n\t" \
			".global end_" #nam " \n" \
			"end_" #nam ": \n\t" \
			"mov lr, r62 \n\t" \
			"gie \n\t" \
		); \
	} \
	) \
	
// end_of_macro

#define BJK_INCORE_ASSERT(nam, cond) \
	BJ_DBG( \
	if(! (cond)){ \
		bj_addr_t nm_addr; \
		bj_asm( \
			".global " #nam " \n" \
			#nam ": \n\t" \
			"mov r61, %low(" #nam ") \n\t" \
			"movt r61, %high(" #nam ") \n\t" \
		); \
		bj_asm("mov %0, r61" : "=r" (nm_addr)); \
		bjk_abort(nm_addr, 0, bj_null); \
	} \
	) \

// end_of_macro

#ifdef IS_EMU_CODE
#define BJK_CK(nam, cond) 
#define BJK_CK2(nam, cond) 
#else 
//define BJK_CK(nam, cond) BJK_OFFCHIP_ASSERT(nam, code_dram, cond)
#define BJK_CK(nam, cond) BJK_INCORE_ASSERT(nam, cond)
#define BJK_CK2(nam, cond) BJK_INCORE_ASSERT(nam, cond)
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

void test_link_shd_code() bj_code_dram;	// bj_code_dram

void ck_shd_code();

#ifdef IS_CORE_CODE
	bj_inline_fn uint16_t*
	bjk_get_stack_pointer() {
		uint16_t* sp_val = 0;
		bj_asm("mov %0, sp" : "=r" (sp_val));
		return sp_val;
	}

	bj_inline_fn void
	bjk_update_min_stack_pointer() {
		bj_addr_t curr_sp = (bj_addr_t)bjk_get_stack_pointer();
		bj_addr_t min_sp = BJK_GLB_SYS->bjk_min_sp;
		if((min_sp == 0) || (curr_sp < min_sp)){
			BJK_GLB_SYS->bjk_min_sp = curr_sp;
		}
	}
	#define BJK_UPDATE_MIN_SP() BJ_DBG(bjk_update_min_stack_pointer())
#else
	#define BJK_UPDATE_MIN_SP() 
#endif


#ifdef __cplusplus
}
#endif

#endif // BJ_GLOBAL_H

