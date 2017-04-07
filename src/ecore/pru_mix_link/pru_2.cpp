
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


void func_2a_shd() bj_code_dram;
void func_2a_shd(){
	bjk_slog2("func_2a_shd \n");		
}

void func_2b_shd() bj_code_dram;
void func_2b_shd(){
	bjk_slog2("func_2b_shd \n");		
}

void func_2_core(){
	bjk_slog2("func_2_core \n");		
}


void pru_main_2() {
	bjk_glb_init();
	bjk_slog2("STARTED pru_main_2 !!\n");	

	func_2a_shd();
	func_2_core();
	func_2b_shd();

	bjk_slog2("FINISHED pru_main_2 !!\n");	
	bjk_glb_finish();
}

