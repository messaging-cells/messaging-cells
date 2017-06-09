
#include "actor.hh"

void bj_cores_main() {
	//bjk_glb_init();
	kernel::init_sys();

	bjk_slog2("HELLO_WORLD\n");	

	kernel::finish_sys();
	//bjk_glb_finish();
}

