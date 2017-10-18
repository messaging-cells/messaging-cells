
#include "cell.hh"

void func_1(int aa){
	mck_abort((mc_addr_t)func_1, mc_cstr("Forced abort in backtrace test"));
}

void func_2(char bb, int aa){
	func_1(aa + 5);
}

void func_3(char* cc, int aa){
	func_2('x', aa * 7);
}

void mc_cores_main() {
	mck_glb_init(false);

	mck_slog2("BACKTRACE_TEST\n");	
	func_3(mc_cstr("calling func3"), 33);

	mck_glb_finish();
}

