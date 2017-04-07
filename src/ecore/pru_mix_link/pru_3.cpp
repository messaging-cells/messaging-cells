
#include <cstdlib>
#include <new>

#ifdef IS_EMU_CODE
	#include "booter.h"
#endif

#include "interruptions.h"
#include "global.h"
#include "trace.h"
//include "test_logs.h"

#include "core_main.h"
#include "dyn_mem.hh"
#include "actor.hh"


void func_3a_shd() bj_code_dram;
void func_3a_shd(){
	bjk_slog2("func_3a_shd \n");		
}

void func_3b_shd() bj_code_dram;
void func_3b_shd(){
	bjk_slog2("func_3b_shd \n");		
}

void func_3_core(){
	bjk_slog2("func_3_core \n");		
}


void pru_main_3() {
	bjk_glb_init();
	bjk_slog2("STARTED pru_main_3 !!\n");	

	func_3a_shd();
	func_3_core();
	func_3b_shd();

	bjk_slog2("FINISHED pru_main_3 !!\n");	
	bjk_glb_finish();
}

