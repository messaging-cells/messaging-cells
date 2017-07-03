
#include "cell.hh"

void mc_cores_main() {
	kernel::init_sys();

	mck_slog2("HELLO_WORLD\n");	

	kernel::finish_sys();
}

