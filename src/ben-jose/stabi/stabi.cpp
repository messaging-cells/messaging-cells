
#include "cell.hh"

#include "stabi.hh"

void bj_stabi_main() {
	//kernel* ker = mck_get_kernel();
	mc_core_nn_t nn = kernel::get_core_nn();
	mck_slog2("STABI___");
	mck_ilog(nn);
	mck_slog2("___\n");
}

