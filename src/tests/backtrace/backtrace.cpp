
#include "actor.hh"

void func_1(int aa){
	bjk_abort((bj_addr_t)func_1, const_cast<char*>("Forced abort in backtrace test"));
}

void func_2(char bb, int aa){
	func_1(aa + 5);
}

void func_3(char* cc, int aa){
	func_2('x', aa * 7);
}

void bj_cores_main() {
	bjk_glb_init();

	bjk_slog2("BACKTRACE_TEST\n");	
	func_3(const_cast<char*>("calling func3"), 33);

	bjk_glb_finish();
}

