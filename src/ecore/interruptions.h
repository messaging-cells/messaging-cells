
#ifndef BJ_INTERRUPTIONS_H
#define BJ_INTERRUPTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "attribute.h"

void bj_opt_sz_fn bj_isr_fn 
bjk_irq0_handler(void); // IVT_RESET

void bj_opt_sz_fn bj_isr_fn 
bjk_irq1_handler(void); // ivt_entry_software_exception

void bj_opt_sz_fn bj_isr_fn 
bjk_irq2_handler(void); // ivt_entry_page_miss

void bj_opt_sz_fn bj_isr_fn 
bjk_irq3_handler(void); // ivt_entry_timer0

void bj_opt_sz_fn bj_isr_fn 
bjk_irq4_handler(void); // ivt_entry_timer1

void bj_opt_sz_fn bj_isr_fn 
bjk_irq5_handler(void); // ivt_entry_message

void bj_opt_sz_fn bj_isr_fn 
bjk_irq6_handler(void); // ivt_entry_dma0

void bj_opt_sz_fn bj_isr_fn 
bjk_irq7_handler(void); // ivt_entry_dma1

void bj_opt_sz_fn bj_isr_fn 
bjk_irq8_handler(void); // ivt_entry_wand

void bj_opt_sz_fn bj_isr_fn
bjk_irq9_handler(void); // ivt_entry_user

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

#ifdef __cplusplus
}
#endif

#endif // BJ_INTERRUPTIONS_H
