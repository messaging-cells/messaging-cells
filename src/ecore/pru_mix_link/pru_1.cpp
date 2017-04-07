
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


void func_1a_shd() bj_code_dram;
void func_1a_shd(){
	bjk_slog2("func_1a_shd \n");		
}

void func_1b_shd() bj_code_dram;
void func_1b_shd(){
	bjk_slog2("func_1b_shd \n");		
}

void func_1_core(){
	bjk_slog2("func_1_core \n");		
}


void pru_main_1() {
	bjk_glb_init();
	bjk_slog2("STARTED pru_main_1 !!\n");	

	func_1a_shd();
	func_1_core();
	func_1b_shd();

	bjk_slog2("FINISHED pru_main_1 !!\n");	
	bjk_glb_finish();
}

