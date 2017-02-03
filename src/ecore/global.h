
// global.h

#ifndef BJ_GLOBAL_H
#define BJ_GLOBAL_H

#include "debug.h"
#include "shared.h"
#include "trace.h"

#ifdef __cplusplus
extern "C" {
#endif

//=====================================================================
// in ekore shared memory

extern void* 	bjk_dbg_call_stack_trace[BJ_MAX_CALL_STACK_SZ];

extern bj_off_core_st* bj_off_core_pt;
extern bj_rrarray_st* bj_write_rrarray;
extern bj_in_core_st bj_in_core_shd;

extern uint16_t bjk_trace_err;

#define BJ_LOG_MSG_MAX_SZ 100

extern char bj_log_msg[BJ_LOG_MSG_MAX_SZ];

//=====================================================================
// global funcs

#define bj_global_code_dram bj_code_dram
//define bj_global_code_dram 

void bj_inline_fn
bjk_set_finished(uint8_t val) {
	bj_set_off_chip_var(bj_off_core_pt->is_finished, val);
}

void 
bjk_init_global(void) bj_global_code_dram;

void 
abort(void) bj_global_code_dram;		// Needed when -Os flag is set

//======================================================================
// log messages

bj_code_dram void
bjk_aux_slog(char* msg);

#define bjk_slog(str) bjk_aux_slog("01" str)

bj_code_dram void
bjk_aux_ilog(uint32_t vv, bj_type_t tt);

bj_inline_fn void
bjk_ilog(int32_t vv){
	bjk_aux_ilog(vv, BJ_I32);
}

bj_inline_fn void
bjk_ulog(uint32_t vv){
	bjk_aux_ilog(vv, BJ_UI32);
}

bj_inline_fn void
bjk_xlog(uint32_t vv){
	bjk_aux_ilog(vv, BJ_X32);
}


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
			bjk_abort(nm_addr, 0, 0x0); \
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
		bjk_abort(nm_addr, BJ_MAX_CALL_STACK_SZ, bjk_dbg_call_stack_trace); \
	} \
	) \

// end_of_macro

#define BJK_CK(nam, cond) BJK_OFFCHIP_ASSERT(nam, code_dram, cond)

#define BJK_CK2(nam, cond) BJK_INCORE_ASSERT(nam, cond)


//======================================================================
// naked inside normal func (insted of naked attribute)

#define BJ_START_NAKED_FUNC(nam) \
	bj_asm( \
		".section .text \n\t" \
		".balign 4 \n\t" \
		".global " #nam " \n" \
	#nam ": \n\t" \
	); \

// end_of_macro

#define BJ_END_NAKED_FUNC() \
	bj_asm( \
		"trap 0x3 \n\t" \
		".previous \n\t" \
	); \

// end_of_macro

#ifdef __cplusplus
}
#endif

#endif // BJ_GLOBAL_H

