
#include "cell.hh"

void recv_cell_handler(missive* msg);
void cell_handler(missive* msg);


void 
recv_cell_handler(missive* msg){
	BJK_UPDATE_MIN_SP();
	EMU_CK(mc_addr_is_local(msg->dst));
	mc_core_id_t koid = kernel::get_core_id();
	MC_MARK_USED(koid);
	mc_core_nn_t konn = kernel::get_core_nn();
	MC_MARK_USED(konn);
	mck_slog2("GOT MISSIVE\n");
	EMU_LOG("recv_cell_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	EMU_PRT("recv_cell_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	
	mck_get_kernel()->set_idle_exit();
}

missive_handler_t the_handlers[] = {
	recv_cell_handler
};

void mc_cores_main() {
	kernel::init_sys();

	kernel::set_handlers(1, the_handlers);

	cell::separate(mc_out_num_cores);
	missive::separate(mc_out_num_cores);
	agent_ref::separate(mc_out_num_cores);
	agent_grp::separate(mc_out_num_cores);

	kernel* ker = mck_get_kernel();
	MC_MARK_USED(ker);

	if(mck_is_core(0,0)){
		mck_slog2("CORE (0,0) started\n");
		kernel::get_core_cell()->handler_idx = 0;	// was 0 but it should be inited for every cells's subclass.

		kernel::run_sys();
	}
	if(mck_is_core(0,1)){
		mck_slog2("CORE (0,1) started\n");
		mc_core_id_t dst = mc_ro_co_to_id(0, 0);
		
		cell* act1 = kernel::get_core_cell();
		cell* act2 = kernel::get_core_cell(dst);

		missive* msv = missive::acquire();
		msv->src = act1;
		msv->dst = act2;
		msv->send();
		mck_slog2("SENT MISSIVE\n");

		ker->set_idle_exit();
		kernel::run_sys();
	}

	mck_slog2("FINISHED !!\n");	
	//mck_xlog((mc_addr_t)ker->host_kernel);
	//mck_slog2(" is the HOST_KERNEL\n");	

	kernel::finish_sys();
}

