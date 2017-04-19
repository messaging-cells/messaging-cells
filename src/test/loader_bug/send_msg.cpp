
#include "send_msg.hh"

#ifdef IS_CORE_CODE
int main() {
	pru_send_msg();
	return 0;
}
#endif

void 
recv_actor_handler(missive* msg){
	EMU_CK(bjk_addr_is_local(msg->dst));
	bj_core_id_t koid = kernel::get_core_id();
	BJ_MARK_USED(koid);
	bj_core_nn_t konn = kernel::get_core_nn();
	BJ_MARK_USED(konn);
	bjk_slog2("GOT MISSIVE\n");
	EMU_LOG("recv_actor_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	EMU_PRT("recv_actor_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	msg->dst->flags = 1;
}

void pru_send_msg() {
	kernel::init_sys();

	kernel::set_handler(recv_actor_handler, bjk_handler_idx(actor));

	actor::separate(bj_out_num_cores);
	missive::separate(bj_out_num_cores);
	agent_ref::separate(bj_out_num_cores);
	agent_grp::separate(bj_out_num_cores);

	kernel* ker = kernel::get_sys();
	BJ_MARK_USED(ker);

	if(bjk_is_core(0,0)){
		bjk_slog2("CORE (0,0) started\n");
		bj_core_id_t dst = bj_ro_co_to_id(0, 1);
		wait_inited_state(dst);
		bjk_slog2("CORE (0,0) SAW core (0,1) INITED\n");

		actor* act1 = kernel::get_core_actor();
		BJ_MARK_USED(act1);
		while(! act1->flags){
			ker->handle_missives();
		}
	}
	if(bjk_is_core(0,1)){
		bjk_slog2("CORE (0,1) started\n");
		bj_core_id_t dst = bj_ro_co_to_id(0, 0);
		wait_inited_state(dst);
		bjk_slog2("CORE (0,1) SAW core (0,0) INITED\n");

		
		actor* act1 = kernel::get_core_actor();
		actor* act2 = kernel::get_core_actor(dst);

		missive* msv = missive::acquire();
		msv->set_source(act1);
		msv->dst = act2;
		msv->send();

		ker->handle_missives();

		bjk_slog2("SENT MISSIVE\n");
	}

	bjk_slog2("FINISHED !!\n");	
	kernel::finish_sys();
}

