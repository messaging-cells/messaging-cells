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
	b bjk_software_exception_handler
;
	.section ivt_entry_page_miss, "ax",@progbits
	.balign 4
	.global	irq2_entry
irq2_entry:
	b bjk_page_miss_handler
;
	.section ivt_entry_timer0, "ax",@progbits
	.balign 4
	.global	irq3_entry
irq3_entry:
	b bjk_timer0_handler
;
	.section .text
	.balign 4
	.global	normal_start
normal_start:
; WARNING !!!!! Your .text code MUST be as small as possible. 
; WARNING !!!!! ALWAYS use modules for incore funcs. 
; WARNING !!!!! ALWAYS have LOW STACK consuming functions (use pointers to dynamic allocated structs). 
; WARNING !!!!! Kernel already uses about 5k !!!! So you have about 3k of stack. THAT IS IT.
; WARNING !!!!! TOP of STACK at addr ~8k NOT at addr ~32k !!!
	mov sp,0x1FF0
;	mov sp,0x7ff0
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
