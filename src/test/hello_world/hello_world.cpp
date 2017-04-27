
#include "hello_world.hh"

int main() {
	hello_world();
	return 0;
}

extern bj_addr_t ALLOC_SIZE;	// defined in linker script

void hello_world() {
	bjk_glb_init();

	bjk_slog2("HELLO_WORLD\n");	
	CORE_CODE(
		bj_addr_t val = (bj_addr_t)(&ALLOC_SIZE);
		bjk_slog2("ALLOC_SIZE=");	
		bjk_xlog(val);
		bjk_slog2("\n");	
	);

	bjk_glb_finish();
}


