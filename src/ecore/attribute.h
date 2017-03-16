
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
	#define bj_isr_fn 
	#define bj_asm(code) 
	#define bj_section(sec)
	#define bj_align(aa)
	#define bj_code_dram 
	#define bj_shared_dram
	#define bj_data_bank2

#else //NOT  IS_EMU_CODE :
//---------------------------------------------------------------------------------------

#define bj_opt_sz_fn __attribute__((optimize("Os")))
#define bj_no_opt_fn __attribute__((optimize("O0")))
#define bj_inline_fn inline __attribute__((always_inline)) 

#ifdef IS_CORE_CODE
	#define bj_isr_fn __attribute__((interrupt)) 
#else
	#define bj_isr_fn 
#endif

#define bj_asm __asm__ __volatile__

#define bj_section(sec) __attribute__ ((section (sec)))
#define bj_align(aa)	__attribute__ ((aligned (aa)))
	
#ifdef IS_CORE_CODE
	#define bj_code_dram bj_section("code_dram")
#else
	#define bj_code_dram 
#endif

#ifdef IS_CORE_CODE
	#define bj_shared_dram bj_section("shared_dram")
#else
	#define bj_shared_dram
#endif

#ifdef IS_CORE_CODE
	#define bj_data_bank2 bj_section(".data_bank2")
#else
	#define bj_data_bank2
#endif

//---------------------------------------------------------------------------------------
#endif	//NOT IS_EMU_CODE

#ifdef IS_EMU_CODE
	#include <stdbool.h>

	bool bje_call_assert(bool vv_ck, const char* file, int line, const char* ck_str, const char* msg);
	void bje_printf(const char *format, ...);
	void bje_log(const char *fmt, ...);

	#define EMU_CODE(cod) cod
	#define ZNQ_CODE(cod) 
	#define EMU_CK(vv) bje_call_assert(vv, __FILE__, __LINE__, #vv, NULL)
	#define EMU_PRT(...) bje_printf(__VA_ARGS__)
	#define EMU_LOG(...) bje_log(__VA_ARGS__)
#else
	#define EMU_CODE(cod) 
	#define ZNQ_CODE(cod) cod
	#define EMU_CK(prm) 
	#define EMU_PRT(...) 
	#define EMU_LOG(...) 
#endif

	
#ifdef __cplusplus
}
#endif

#endif // BJ_ATTRIBUTE_H

