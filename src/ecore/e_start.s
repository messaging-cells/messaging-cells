	.file	"e_start.s"
	.section IVT_RESET, "ax",@progbits
	.balign 4
	.global	_start ;irq0_entry
_start:
	b normal_start
;
	.section ivt_entry_software_exception, "ax",@progbits
	.balign 4
	.global	irq1_entry
irq1_entry:
	b bjk_irq1_handler
;
	.section ivt_entry_page_miss, "ax",@progbits
	.balign 4
	.global	irq2_entry
irq2_entry:
	b bjk_irq2_handler
;
	.section ivt_entry_timer0, "ax",@progbits
	.balign 4
	.global	irq3_entry
irq3_entry:
	b bjk_irq3_handler
;
	.section ivt_entry_timer1, "ax",@progbits
	.balign 4
	.global	irq4_entry
irq4_entry:
	b bjk_irq4_handler
;
	.section ivt_entry_message, "ax",@progbits
	.balign 4
	.global	irq5_entry
irq5_entry:
	b bjk_irq5_handler
;
	.section ivt_entry_dma0, "ax",@progbits
	.balign 4
	.global	irq6_entry
irq6_entry:
	b bjk_irq6_handler
;
	.section ivt_entry_dma1, "ax",@progbits
	.balign 4
	.global	irq7_entry
irq7_entry:
	b bjk_irq7_handler
;
	.section ivt_entry_wand, "ax",@progbits
	.balign 4
	.global	irq8_entry
irq8_entry:
	b bjk_irq8_handler
;
	.section ivt_entry_user, "ax",@progbits
	.balign 4
	.global	irq9_entry
irq9_entry:
	b bjk_irq9_handler
;
	.section .text
	.balign 4
	.global	normal_start
normal_start:
	mov sp,0x7ff0
	movt sp,0x0
	mov fp,0x0
	mov r0, #0x3ff
	movts imask, r0
	mov r0, %low(main_caller)
	movt r0, %high(main_caller)
	movts iret, r0
	rti
	.balign 4
	.global	main_caller
main_caller:
	mov r0, %low(main)
	movt r0, %high(main)
	jalr r0
	nop
	mov r0, #0x3ff
	movts imask, r0
	gid
	trap 0x3
	nop
infn_loop:
	b infn_loop
	nop
	rts
	rti
