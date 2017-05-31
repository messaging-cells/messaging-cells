
#include "actor.hh"

void bj_cores_main() {
	kernel::init_sys();

	actor::separate(bj_out_num_cores);
	missive::separate(bj_out_num_cores);
	agent_ref::separate(bj_out_num_cores);
	agent_grp::separate(bj_out_num_cores);

	kernel* ker = bjk_get_kernel();
	BJ_MARK_USED(ker);

	if(bjk_is_core(0,0)){
		bjk_slog2("CORE (0,0) started\n");

		missive_handler_t hndlers = bj_null;
		kernel::set_handlers(0, &hndlers);
		
		actor* act1 = kernel::get_core_actor();
		actor* act2 = kernel::get_host_actor();

		EMU_CK_PRT((bj_addr_get_id((bj_addr_t)act2) != 0), "act2 = %p\n", act2);

		missive* msv = missive::acquire();
		msv->src = act1;
		msv->dst = act2;

		EMU_PRT("SND_ACT1(SRC)=%p \n", act1);
		EMU_PRT("SND_ACT2(DST)=%p \n", act2);
		EMU_PRT("SND_MSV=%p \n", (void*)msv);

		msv->send_to_host();

		EMU_PRT("SND_SENT H MISSIVE\n");
		bjk_slog2("SENT HOST MISSIVE\n");

		ker->set_idle_exit();
		kernel::run_sys();
	}

	bjk_slog2("FINISHED SEND_HOST TEST\n");	
	//bjk_xlog((bj_addr_t)ker->host_kernel);
	//bjk_slog2(" is the HOST_KERNEL\n");	

	kernel::finish_sys();
}

