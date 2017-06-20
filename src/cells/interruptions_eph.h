
#ifndef MC_INTERRUPTIONS_H
#define MC_INTERRUPTIONS_H

#include <inttypes.h>
#include "attribute.h"

#ifdef __cplusplus
mc_c_decl {
#endif

void mc_opt_sz_fn mc_isr_fn 
mck_sync_handler(void); // IVT_RESET

void mc_opt_sz_fn mc_isr_fn 
mck_software_exception_handler(void); // ivt_entry_software_exception

void mc_opt_sz_fn mc_isr_fn 
mck_page_miss_handler(void); // ivt_entry_page_miss

void mc_opt_sz_fn mc_isr_fn 
mck_timer0_handler(void); // ivt_entry_timer0

#ifdef MC_IS_EPH_CODE

	void mc_inline_fn
	mck_enable_all_irq() {
		mc_asm("mov r0, #0x0"); 
		mc_asm("movts imask, r0");
	}

	void mc_inline_fn
	mck_disable_all_irq() {
		mc_asm("mov r0, #0x3ff"); 
		mc_asm("movts imask, r0");
	}

	void mc_inline_fn
	mck_global_irq_disable() {
		mc_asm("gid"); 
	}

	void mc_inline_fn
	mck_global_irq_enable() {
		mc_asm("gie"); 
	}

	#define mck_simple_abort(func, excode) \
		mck_glb_sys_st* in_core_pt = BJK_GLB_SYS; \
		in_core_pt->exception_code = excode; \
		in_core_pt->dbg_error_code = (mc_addr_t)(func); \
		mc_off_core_st* off_core_pt = BJK_GLB_SYS->off_core_pt; \
		if((off_core_pt != mc_null) && (off_core_pt->magic_id == MC_MAGIC_ID)){ \
			off_core_pt->is_finished = MC_FINISHED_VAL; \
		} \
		mc_asm("trap 0x3"); \

	// end_macro

#else 

	void mc_inline_fn
	mck_enable_all_irq() {
	}

	void mc_inline_fn
	mck_disable_all_irq() {
	}

	void mc_inline_fn
	mck_global_irq_disable() {
	}

	void mc_inline_fn
	mck_global_irq_enable() {
	}

#endif	// MC_IS_EPH_CODE

#ifdef __cplusplus
}
#endif

#endif // MC_INTERRUPTIONS_H
