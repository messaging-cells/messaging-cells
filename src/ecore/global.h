
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

struct bjk_glb_sys_def { 
	bj_sys_sz_st 	sys_sz;
	bj_off_core_st* off_core_pt;
	bj_rrarray_st* 	write_rrarray;
	bj_in_core_st 	in_core_shd;
	uint8_t 		dbg_out_str[BJ_OUT_BUFF_MAX_OBJ_SZ];
};
typedef struct bjk_glb_sys_def bjk_glb_sys_st;

bjk_glb_sys_st*
bjk_get_glb_sys();

bj_in_core_st*
bjk_get_glb_in_core_shd();

//=====================================================================
// global funcs

void bj_inline_fn
bjk_set_finished(uint8_t val) {
	bj_off_core_st* off_core_pt = bjk_get_glb_sys()->off_core_pt; \
	bj_set_off_chip_var(off_core_pt->is_finished, val);
}

void 
bjk_init_global(void) bj_code_dram;

void 
abort(void) bj_code_dram;		// Needed when -Os flag is set

//======================================================================
// log messages

bj_code_dram void
bjk_aux_sout(char* msg, bj_out_type_t outt);

bj_inline_fn void
bjk_slog(char* msg){
	bjk_aux_sout(msg, BJ_OUT_LOG);
}

#define	bjk_slog2(msg) bjk_slog(as_pt_char(msg))

bj_inline_fn void
bjk_sprt(char* msg){
	bjk_aux_sout(msg, BJ_OUT_PRT);
}

#define	bjk_sprt2(msg) bjk_sprt(as_pt_char(msg))

bj_code_dram void
bjk_aux_iout(uint32_t vv, bj_out_type_t outt, bj_type_t tt);

bj_inline_fn void
bjk_ilog(int32_t vv){
	bjk_aux_iout(vv, BJ_OUT_LOG, BJ_I32);
}

bj_inline_fn void
bjk_ulog(uint32_t vv){
	bjk_aux_iout(vv, BJ_OUT_LOG, BJ_UI32);
}

bj_inline_fn void
bjk_xlog(uint32_t vv){
	bjk_aux_iout(vv, BJ_OUT_LOG, BJ_X32);
}

bj_inline_fn void
bjk_iprt(int32_t vv){
	bjk_aux_iout(vv, BJ_OUT_PRT, BJ_I32);
}

bj_inline_fn void
bjk_uprt(uint32_t vv){
	bjk_aux_iout(vv, BJ_OUT_PRT, BJ_UI32);
}

bj_inline_fn void
bjk_xprt(uint32_t vv){
	bjk_aux_iout(vv, BJ_OUT_PRT, BJ_X32);
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

