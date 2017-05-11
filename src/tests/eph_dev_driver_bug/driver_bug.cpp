
#include "actor.hh"

void bj_cores_main() {
	kernel::init_sys();

	actor::separate(bj_out_num_cores);
	missive::separate(bj_out_num_cores);
	agent_ref::separate(bj_out_num_cores);
	agent_grp::separate(bj_out_num_cores);

	kernel* ker = BJK_KERNEL;
	BJ_MARK_USED(ker);

	if(bjk_is_core(0,0)){
		bjk_slog2("CORE (0,0) started\n");
	}
	if(bjk_is_core(0,1)){
		bjk_slog2("CORE (0,1) started\n");
	}

	bjk_slog2("FINISHED !!\n");	
	kernel::finish_sys();
}

