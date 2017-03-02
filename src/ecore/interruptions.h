
#ifndef BJ_INTERRUPTIONS_H
#define BJ_INTERRUPTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include "attribute.h"

void bj_opt_sz_fn bj_isr_fn 
bjk_sync_handler(void); // IVT_RESET

void bj_opt_sz_fn bj_isr_fn 
bjk_software_exception_handler(void); // ivt_entry_software_exception

void bj_opt_sz_fn bj_isr_fn 
bjk_page_miss_handler(void); // ivt_entry_page_miss

void bj_opt_sz_fn bj_isr_fn 
bjk_timer0_handler(void); // ivt_entry_timer0

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

extern uint32_t test_send_irq2;

#ifdef __cplusplus
}
#endif

#endif // BJ_INTERRUPTIONS_H
