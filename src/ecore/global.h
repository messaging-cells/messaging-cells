
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

struct bjk_glb_sys_def { 
	bj_sys_sz_st 	sys_sz;
	bj_off_core_st* off_core_pt;
	bj_rrarray_st* 	write_rrarray;
	bj_in_core_st 	in_core_shd;
	uint8_t 		dbg_out_str[BJ_MAX_STR_SZ];
};
typedef struct bjk_glb_sys_def bjk_glb_sys_st;

bjk_glb_sys_st*
bjk_get_glb_sys();

bj_inline_fn bj_in_core_st* 
bjk_get_glb_in_core_shd(){
	return &(bjk_get_glb_sys()->in_core_shd);
}

//=====================================================================
// global funcs

void bj_inline_fn
bjk_set_finished(uint8_t val) {
	bj_off_core_st* off_core_pt = bjk_get_glb_sys()->off_core_pt; 
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
#define BJK_CK(nam, cond) BJK_OFFCHIP_ASSERT(nam, code_dram, cond)
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


#ifdef __cplusplus
}
#endif

#endif // BJ_GLOBAL_H

