
#ifndef BJ_INTERRUPTIONS_H
#define BJ_INTERRUPTIONS_H

#include <inttypes.h>
#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif

void bj_opt_sz_fn bj_isr_fn 
bjk_sync_handler(void); // IVT_RESET

void bj_opt_sz_fn bj_isr_fn 
bjk_software_exception_handler(void); // ivt_entry_software_exception

void bj_opt_sz_fn bj_isr_fn 
bjk_page_miss_handler(void); // ivt_entry_page_miss

void bj_opt_sz_fn bj_isr_fn 
bjk_timer0_handler(void); // ivt_entry_timer0

#ifdef IS_CORE_CODE

	void bj_inline_fn
	bjk_enable_all_irq() {
		bj_asm("mov r0, #0x0"); 
		bj_asm("movts imask, r0");
	}

	void bj_inline_fn
	bjk_disable_all_irq() {
		bj_asm("mov r0, #0x3ff"); 
		bj_asm("movts imask, r0");
	}

	void bj_inline_fn
	bjk_global_irq_disable() {
		bj_asm("gid"); 
	}

	void bj_inline_fn
	bjk_global_irq_enable() {
		bj_asm("gie"); 
	}

	#define bjk_simple_abort(func, excode) \
		bj_in_core_st* in_core_pt = BJK_GLB_IN_CORE_SHD; \
		in_core_pt->exception_code = excode; \
		in_core_pt->dbg_error_code = (bj_addr_t)(func); \
		bj_off_core_st* off_core_pt = BJK_GLB_SYS->off_core_pt; \
		if((off_core_pt != bj_null) && (off_core_pt->magic_id == BJ_MAGIC_ID)){ \
			off_core_pt->is_finished = BJ_FINISHED_VAL; \
		} \
		bj_asm("trap 0x3"); \

	// end_macro

#else 

	void bj_inline_fn
	bjk_enable_all_irq() {
	}

	void bj_inline_fn
	bjk_disable_all_irq() {
	}

	void bj_inline_fn
	bjk_global_irq_disable() {
	}

	void bj_inline_fn
	bjk_global_irq_enable() {
	}

#endif	// IS_CORE_CODE

#ifdef __cplusplus
}
#endif

#endif // BJ_INTERRUPTIONS_H
