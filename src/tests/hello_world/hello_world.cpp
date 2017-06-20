
#include "cell.hh"

void mc_cores_main() {
	kernel::init_sys();

	bjk_slog2("HELLO_WORLD\n");	

	kernel::finish_sys();
}

