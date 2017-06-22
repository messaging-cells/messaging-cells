
#include "cell.hh"

#include "resp_conf.h"

void recv_core_handler(missive* msg);

void 
recv_core_handler(missive* msg){
	EMU_CK(mc_addr_is_local(msg->dst));

	mck_sprt2("CORE_GOT_RESPONSE\n");
	EMU_PRT("RCV_RESPONSE. src=%p dst=%p \n", msg->get_source(), msg->dst);
	
	mck_get_kernel()->set_idle_exit();
}

missive_handler_t core_handlers[] = {
	recv_core_handler
};

void mc_cores_main() {
	kernel::init_sys();

	cell::separate(mc_out_num_cores);
	missive::separate(mc_out_num_cores);
	agent_ref::separate(mc_out_num_cores);
	agent_grp::separate(mc_out_num_cores);

	kernel* ker = mck_get_kernel();
	MC_MARK_USED(ker);

	if(mck_is_ro_co_core(0,0)){
		mck_slog2("CORE (0,0) started\n");

		//missive_handler_t hndlers = mc_null;
		//kernel::set_handlers(0, &hndlers);
		kernel::set_handlers(1, core_handlers);

		cell* act1 = kernel::get_core_cell();
		cell* act2 = kernel::get_host_cell();

		EMU_CK_PRT((mc_addr_get_id((mc_addr_t)act2) != 0), "act2 = %p\n", act2);

		missive* msv = missive::acquire();
		msv->src = act1;
		msv->dst = act2;
		msv->tok = 432;

		mck_sprt2("SND_act2___");
		mck_xprt((mc_addr_t)(act2));
		mck_sprt2("___\n");

		MCK_CK(act2 != mc_null);

		msv->send_to_host();

		EMU_PRT("SND_SENT H MISSIVE\n");

		#ifndef WITH_RESPONSE
			ker->set_idle_exit();
		#endif

		kernel::run_sys();
	}

	mck_slog2("FINISHED SEND_HOST TEST\n");	

	kernel::finish_sys();
}

