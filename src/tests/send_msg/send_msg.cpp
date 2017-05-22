
#include "actor.hh"

void recv_actor_handler(missive* msg);
void actor_handler(missive* msg);


void 
recv_actor_handler(missive* msg){
	BJK_UPDATE_MIN_SP();
	EMU_CK(bj_addr_is_local(msg->dst));
	bj_core_id_t koid = kernel::get_core_id();
	BJ_MARK_USED(koid);
	bj_core_nn_t konn = kernel::get_core_nn();
	BJ_MARK_USED(konn);
	bjk_slog2("GOT MISSIVE\n");
	EMU_LOG("recv_actor_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	EMU_PRT("recv_actor_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	
	bjk_get_kernel()->set_idle_exit();
}

missive_handler_t the_handlers[] = {
	recv_actor_handler
};

void bj_cores_main() {
	kernel::init_sys();

	kernel::set_handlers(1, the_handlers);

	actor::separate(bj_out_num_cores);
	missive::separate(bj_out_num_cores);
	agent_ref::separate(bj_out_num_cores);
	agent_grp::separate(bj_out_num_cores);

	kernel* ker = bjk_get_kernel();
	BJ_MARK_USED(ker);

	if(bjk_is_core(0,0)){
		bjk_slog2("CORE (0,0) started\n");
		kernel::get_core_actor()->handler_idx = 0;	// was 0 but it should be inited for every actors's subclass.

		kernel::run_sys();
	}
	if(bjk_is_core(0,1)){
		bjk_slog2("CORE (0,1) started\n");
		bj_core_id_t dst = bj_ro_co_to_id(0, 0);
		
		actor* act1 = kernel::get_core_actor();
		actor* act2 = kernel::get_core_actor(dst);

		missive* msv = missive::acquire();
		msv->src = act1;
		msv->dst = act2;
		msv->send();
		bjk_slog2("SENT MISSIVE\n");

		ker->set_idle_exit();
		kernel::run_sys();
	}

	bjk_slog2("FINISHED !!\n");	
	//bjk_xlog((bj_addr_t)ker->host_kernel);
	//bjk_slog2(" is the HOST_KERNEL\n");	

	kernel::finish_sys();
}

