
// global.h

#ifndef BJ_GLOBAL_H
#define BJ_GLOBAL_H

#include "shared_data.h"
#include "trace.h"

#ifdef __cplusplus
extern "C" {
#endif

//=====================================================================
// in ekore shared memory

extern void* 	bjk_dbg_call_stack_trace[BJ_MAX_CALL_STACK_SZ];

extern bj_off_core_st* bj_off_core_pt;
extern bj_in_core_st bj_in_core_shd;

extern uint16_t bjk_trace_err;

//=====================================================================
// global funcs

#define bj_outlink bj_section("code_dram")

#define bj_outlink_global bj_outlink
//define bj_outlink_global ;

void 
bj_memset(uint8_t* bytes, uint8_t val, uint32_t sz);

void bj_inline_fn
bjk_set_finished(uint8_t val) {
	set_off_chip_var(bj_off_core_pt->is_finished, val);
}

void 
bjk_init_global(void) bj_outlink_global;

void 
abort(void) bj_outlink_global;		// Needed when -Os flag is set

//======================================================================
// bj_asserts

#define BJ_OFFCHIP_ASSERT(nam, sec, cond) \
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
	
// end_of_macro

#define BJ_INCORE_ASSERT(nam, cond) \
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

// end_of_macro

#define BJ_CK(nam, cond) BJ_OFFCHIP_ASSERT(nam, code_dram, cond)

#define BJ_CK2(nam, cond) BJ_INCORE_ASSERT(nam, cond)


//======================================================================
// naked inside normal func (insted of naked attribute)

#define START_NAKED_FUNC(nam) \
	bj_asm( \
		".section .text \n\t" \
		".balign 4 \n\t" \
		".global " #nam " \n" \
	#nam ": \n\t" \
	); \

// end_of_macro

#define END_NAKED_FUNC() \
	bj_asm( \
		"trap 0x3 \n\t" \
		".previous \n\t" \
	); \

// end_of_macro

#ifdef __cplusplus
}
#endif

#endif // BJ_GLOBAL_H

