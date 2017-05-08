
// attribute.h

#ifndef BJ_ATTRIBUTE_H
#define BJ_ATTRIBUTE_H

#define bj_c_decl extern "C"

#ifdef __cplusplus
bj_c_decl {
#endif

#define BJK_LINK_SCRIPT_SYM_VAL(xx) ((bj_addr_t)(&xx))

#define BJ_STRFY(prm) #prm

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
	#define bj_align(aa)	__attribute__ ((aligned (aa)))

	#ifdef IS_CORE_CODE
		#define bj_naked_fn __attribute__((naked)) 
		#define bj_isr_fn __attribute__((interrupt)) 
		#define bj_section(sec) __attribute__ ((section (sec)))
		#define CORE_CODE(cod) cod
	#else
		#define bj_naked_fn
		#define bj_isr_fn 
		#define bj_section(sec) 
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

#define bj_lk_syms_section_nm "link_symbols_data"


#define bj_aligned bj_align(8) 

#define bj_external_code_ram bj_section("external_code_ram")
#define bj_external_data_ram bj_section("external_data_ram")
#define bj_alloc_ram bj_section("alloc_ram")

#define bj_lk_syms_dat bj_section(bj_lk_syms_section_nm)

#define bj_comm_cod bj_section("common_code")
#define bj_comm_dat bj_section("common_data")

#define bj_mod1_cod bj_section("module1_code")
#define bj_mod2_cod bj_section("module2_code")
#define bj_mod3_cod bj_section("module3_code")
#define bj_mod4_cod bj_section("module4_code")
#define bj_mod5_cod bj_section("module5_code")
#define bj_mod6_cod bj_section("module6_code")
#define bj_mod7_cod bj_section("module7_code")
#define bj_mod8_cod bj_section("module8_code")
#define bj_mod9_cod bj_section("module9_code")

#define bj_mod1_dat bj_section("module1_data")
#define bj_mod2_dat bj_section("module2_data")
#define bj_mod3_dat bj_section("module3_data")
#define bj_mod4_dat bj_section("module4_data")
#define bj_mod5_dat bj_section("module5_data")
#define bj_mod6_dat bj_section("module6_data")
#define bj_mod7_dat bj_section("module7_data")
#define bj_mod8_dat bj_section("module8_data")
#define bj_mod9_dat bj_section("module9_data")
	
#ifdef __cplusplus
}
#endif

#endif // BJ_ATTRIBUTE_H

