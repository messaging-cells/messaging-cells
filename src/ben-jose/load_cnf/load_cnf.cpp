
#include "cell.hh"

#include "preload_cnf.hh"

void mc_cores_main() {
	kernel::init_sys();

	mck_slog2("LOAD_CNF\n");

	pre_load_cnf* pre_cnf = (pre_load_cnf*)(kernel::get_sys()->host_load_data);

	EMU_PRT("pre_cnf = %p \n", pre_cnf);

	long magic = pre_cnf->MAGIC;
	mck_ilog(magic);
	mck_slog2("\n");

	kernel::finish_sys();
}

