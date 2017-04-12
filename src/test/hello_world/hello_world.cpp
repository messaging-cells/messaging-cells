
#include "hello_world.hh"

int main() {
	hello_world();
	return 0;
}

void hello_world() {
	bjk_glb_init();
	bjk_slog2("HELLO_WORLD\n");	
	bjk_glb_finish();
}


