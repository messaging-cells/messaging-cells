
#include "actor.hh"

#include "resp_conf.h"

void recv_core_handler(missive* msg);

void 
recv_core_handler(missive* msg){
	EMU_CK(bj_addr_is_local(msg->dst));

	bjk_sprt2("CORE_GOT_RESPONSE\n");
	EMU_PRT("RCV_RESPONSE. src=%p dst=%p \n", msg->get_source(), msg->dst);
	
	bjk_get_kernel()->set_idle_exit();
}

missive_handler_t core_handlers[] = {
	recv_core_handler
};

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

		//missive_handler_t hndlers = bj_null;
		//kernel::set_handlers(0, &hndlers);
		kernel::set_handlers(1, core_handlers);

		actor* act1 = kernel::get_core_actor();
		actor* act2 = kernel::get_host_actor();

		EMU_CK_PRT((bj_addr_get_id((bj_addr_t)act2) != 0), "act2 = %p\n", act2);

		missive* msv = missive::acquire();
		msv->src = act1;
		msv->dst = act2;
		msv->tok = 432;

		bjk_sprt2("SND_act2___");
		bjk_xprt((bj_addr_t)(act2));
		bjk_sprt2("___\n");

		BJK_CK(act2 != bj_null);

		msv->send_to_host();

		EMU_PRT("SND_SENT H MISSIVE\n");

		#ifndef WITH_RESPONSE
			ker->set_idle_exit();
		#endif

		kernel::run_sys();
	}

	bjk_slog2("FINISHED SEND_HOST TEST\n");	

	kernel::finish_sys();
}

