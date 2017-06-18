
// attribute.h

#ifndef MC_ATTRIBUTE_H
#define MC_ATTRIBUTE_H

#include "debug.h"

#ifdef __cplusplus
mc_c_decl {
#endif

#define MC_PLL_LOADING

#define BJK_LINK_SCRIPT_SYM_VAL(xx) ((mc_addr_t)(&xx))

#define MC_STRFY(prm) #prm

//======================================================================
// function attibutes

	//define mc_asm(code) 
	//define mc_asm	123

#ifdef MC_IS_EMU_CODE
//---------------------------------------------------------------------------------------
	#define mc_opt_sz_fn 
	#define mc_no_opt_fn 
	// define mc_inline_fn inline 
	#define mc_inline_fn inline __attribute__((always_inline)) 
	#define mc_asm(code) 
	#define mc_section(sec)
	#define mc_align(aa)
	#define mc_naked_fn
	#define mc_isr_fn 

	#include <stdbool.h>

	bool bjm_call_assert(bool is_assert, bool vv_ck, const char* file, int line, const char* ck_str, 
							const char* fmt, ...);
	void bjm_printf(const char *format, ...);
	void bjm_log(const char *fmt, ...);

	#define EMU_CODE(cod) cod
	#define EMU_DBG_CODE(cod) MC_DBG(cod)
	#define EMU_CK(vv) bjm_call_assert(true, vv, __FILE__, __LINE__, #vv, mc_null)
	#define EMU_CK_PRT(vv, ...) bjm_call_assert(true, vv, __FILE__, __LINE__, #vv, __VA_ARGS__)
	#define EMU_COND_PRT(cond, ...) bjm_call_assert(false, cond, __FILE__, __LINE__, #cond, __VA_ARGS__)
	#define EMU_PRT(...) bjm_printf(__VA_ARGS__)
	#define EMU_LOG(...) bjm_log(__VA_ARGS__)
	#define EPH_CODE(cod) 

#else //NOT  MC_IS_EMU_CODE :
//---------------------------------------------------------------------------------------

	#define mc_opt_sz_fn __attribute__((optimize("Os")))
	#define mc_no_opt_fn __attribute__((optimize("O0")))
	#define mc_inline_fn inline __attribute__((always_inline)) 
	#define mc_asm __asm__ __volatile__
	#define mc_align(aa)	__attribute__ ((aligned (aa)))

	#ifdef MC_IS_EPH_CODE
		#define mc_naked_fn __attribute__((naked)) 
		#define mc_isr_fn __attribute__((interrupt)) 
		#define mc_section(sec) __attribute__ ((section (sec)))
		#define EPH_CODE(cod) cod
	#else
		#define mc_naked_fn
		#define mc_isr_fn 
		#define mc_section(sec) 
		#define EPH_CODE(cod) 
	#endif

	#define EMU_CODE(cod) 
	#define EMU_DBG_CODE(cod) 
	#define EMU_CK(prm) 
	#define EMU_CK_PRT(vv, ...) 
	#define EMU_COND_PRT(cond, ...)
	#define EMU_PRT(...) 
	#define EMU_LOG(...) 

//---------------------------------------------------------------------------------------
#endif	//NOT MC_IS_EMU_CODE

#ifdef MC_IS_ZNQ_CODE
	#define ZNQ_CODE(cod) cod
#else
	#define ZNQ_CODE(cod)
#endif	//MC_IS_ZNQ_CODE

#define mc_lk_syms_section_nm "link_symbols_data"


#define mc_aligned mc_align(8) 

#define mc_external_code_ram mc_section("external_code_ram")
#define mc_external_data_ram mc_section("external_data_ram")
#define mc_external_host_data_ram mc_section("external_host_data_ram")
#define mc_alloc_ram mc_section("alloc_ram")

#define mc_lk_syms_dat mc_section(mc_lk_syms_section_nm)

#define mc_comm_cod mc_section("common_code")
#define mc_comm_dat mc_section("common_data")

#define mc_mod1_cod mc_section("module1_code")
#define mc_mod2_cod mc_section("module2_code")
#define mc_mod3_cod mc_section("module3_code")
#define mc_mod4_cod mc_section("module4_code")
#define mc_mod5_cod mc_section("module5_code")
#define mc_mod6_cod mc_section("module6_code")
#define mc_mod7_cod mc_section("module7_code")
#define mc_mod8_cod mc_section("module8_code")
#define mc_mod9_cod mc_section("module9_code")

#define mc_mod1_dat mc_section("module1_data")
#define mc_mod2_dat mc_section("module2_data")
#define mc_mod3_dat mc_section("module3_data")
#define mc_mod4_dat mc_section("module4_data")
#define mc_mod5_dat mc_section("module5_data")
#define mc_mod6_dat mc_section("module6_data")
#define mc_mod7_dat mc_section("module7_data")
#define mc_mod8_dat mc_section("module8_data")
#define mc_mod9_dat mc_section("module9_data")
	
#ifdef __cplusplus
}
#endif

#endif // MC_ATTRIBUTE_H

