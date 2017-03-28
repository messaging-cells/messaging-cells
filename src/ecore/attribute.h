
// attribute.h

#ifndef BJ_ATTRIBUTE_H
#define BJ_ATTRIBUTE_H

#define bj_c_decl extern "C"

#ifdef __cplusplus
bj_c_decl {
#endif

//======================================================================
// function attibutes

	//define bj_asm(code) 
	//define bj_asm	123

#ifdef IS_EMU_CODE
//---------------------------------------------------------------------------------------
	#define bj_opt_sz_fn 
	#define bj_no_opt_fn 
	// define bj_inline_fn inline 
	#define bj_inline_fn inline __attribute__((always_inline)) 
	#define bj_asm(code) 
	#define bj_section(sec)
	#define bj_align(aa)
	#define bj_naked_fn
	#define bj_isr_fn 
	#define bj_code_dram 
	#define bj_shared_dram
	#define bj_data_bank2

	#include <stdbool.h>

	bool bjm_call_assert(bool vv_ck, const char* file, int line, const char* ck_str, const char* msg);
	void bjm_printf(const char *format, ...);
	void bjm_log(const char *fmt, ...);

	#define EMU_CODE(cod) cod
	#define EMU_CK(vv) bjm_call_assert(vv, __FILE__, __LINE__, #vv, bj_null)
	#define EMU_PRT(...) bjm_printf(__VA_ARGS__)
	#define EMU_LOG(...) bjm_log(__VA_ARGS__)
	#define CORE_CODE(cod) 

#else //NOT  IS_EMU_CODE :
//---------------------------------------------------------------------------------------

	#define bj_opt_sz_fn __attribute__((optimize("Os")))
	#define bj_no_opt_fn __attribute__((optimize("O0")))
	#define bj_inline_fn inline __attribute__((always_inline)) 
	#define bj_asm __asm__ __volatile__
	#define bj_section(sec) __attribute__ ((section (sec)))
	#define bj_align(aa)	__attribute__ ((aligned (aa)))

	#ifdef IS_CORE_CODE
		#define bj_naked_fn __attribute__((naked)) 
		#define bj_isr_fn __attribute__((interrupt)) 
		#define bj_code_dram bj_section("code_dram")
		#define bj_shared_dram bj_section("shared_dram")
		#define bj_data_bank2 bj_section(".data_bank2")
		#define CORE_CODE(cod) cod
	#else
		#define bj_naked_fn
		#define bj_isr_fn 
		#define bj_code_dram 
		#define bj_shared_dram
		#define bj_data_bank2
		#define CORE_CODE(cod) 
	#endif

	#define EMU_CODE(cod) 
	#define EMU_CK(prm) 
	#define EMU_PRT(...) 
	#define EMU_LOG(...) 

//---------------------------------------------------------------------------------------
#endif	//NOT IS_EMU_CODE

#ifdef IS_ZNQ_CODE
	#define ZNQ_CODE(cod) cod
#else
	#define ZNQ_CODE(cod)
#endif	//IS_ZNQ_CODE


#define bj_aligned bj_align(8) 
	
#ifdef __cplusplus
}
#endif

#endif // BJ_ATTRIBUTE_H

