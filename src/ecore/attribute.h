
// attribute.h

#ifndef BJ_ATTRIBUTE_H
#define BJ_ATTRIBUTE_H

#ifdef __cplusplus
extern "C"
{
#endif

//======================================================================
// function attibutes

// Use with static when needed

#define bj_opt_sz_fn __attribute__((optimize("Os")))
#define bj_no_opt_fn __attribute__((optimize("O0")))
#define bj_inline_fn inline __attribute__((always_inline)) 
//define bj_naked_fn __attribute__((naked)) 
#define bj_isr_fn __attribute__((interrupt)) 
#define bj_asm __asm__ __volatile__
#define bj_section(sec) __attribute__ ((section (sec)))
#define bj_align(aa)	__attribute__ ((aligned (aa)))
	
#ifdef IS_CORE_CODE
	#define bj_code_dram bj_section("code_dram")
#else
	#define bj_code_dram 
#endif

	
#ifdef __cplusplus
}
#endif

#endif // BJ_ATTRIBUTE_H

