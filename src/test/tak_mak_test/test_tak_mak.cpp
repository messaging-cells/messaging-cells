
#include "test_tak_mak.hh"

int main() {
	test_tak_mak();
	return 0;
}

extern bj_addr_t LD_CORE_STACK_TOP;	// defined in linker script

void test_tak_mak() {
	bjk_glb_init();

	tak_mak gen;

	bjk_slog2("HELLO_WORLD\n");	
	CORE_CODE(
		uint32_t stk_top = (uint32_t)(&LD_CORE_STACK_TOP);
		bjk_xlog(stk_top);
		bjk_slog2("\n");	
	);

	bjk_glb_finish();
}


