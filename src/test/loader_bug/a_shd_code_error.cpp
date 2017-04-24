
#include "actor.hh"

/*

// --------------------------------------

#ifdef IS_CORE_CODE
extern bjk_glb_sys_st	bj_glb_sys_data;
#endif

//bj_naked_fn  bj_code_dram
void test_link_shd_code() bj_code_dram;
void test_link_shd_code() {
#ifdef IS_CORE_CODE
	bj_glb_sys_data.in_core_shd.dbg_progress_flag = 0xdeadbeaf;
#endif
}

// --------------------------------------

void bj_naked_fn test_link_shd_code() bj_code_dram;
void test_link_shd_code() {
#ifdef IS_CORE_CODE
	bj_asm("rts");
#endif
}

// --------------------------------------

void test_link_shd_code() {
	// IF LINKED LAST THIS CODE WONT GET EXECUTED AND THE CORE HANGS !!!
	//BJK_GLB_IN_CORE_SHD->dbg_progress_flag = 0xbadbadba;
	bjk_slog2("test_link_shd_code called OK\n");
	//bjk_xlog((bj_addr_t)(void*)test_link_shd_code);
}
*/


#ifdef IS_CORE_CODE
extern bjk_glb_sys_st	bj_glb_sys_data;
#endif

//bj_naked_fn  bj_code_dram
void test_link_shd_code() {
#ifdef IS_CORE_CODE
	bj_glb_sys_data.in_core_shd.dbg_progress_flag = 0xdeadbeaf;
#endif
}
