
#include "cell.hh"

void recv_cell_handler(missive* msg);
void cell_handler(missive* msg);

void
wait_inited_state(mc_core_id_t dst_id){
	bjk_glb_sys_st* in_shd = BJK_GLB_SYS;
	uint8_t* loc_st = &(in_shd->the_core_state);
	uint8_t* rmt_st = (uint8_t*)mc_addr_set_id(dst_id, loc_st);
	while(*rmt_st != bjk_inited_state);
}

void 
recv_cell_handler(missive* msg){
	BJK_UPDATE_MIN_SP();
	EMU_CK(mc_addr_is_local(msg->dst));
	mc_core_id_t koid = kernel::get_core_id();
	MC_MARK_USED(koid);
	mc_core_nn_t konn = kernel::get_core_nn();
	MC_MARK_USED(konn);
	bjk_slog2("GOT MISSIVE\n");
	EMU_LOG("recv_cell_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	EMU_PRT("recv_cell_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	msg->dst->flags = 1;
}

void mc_cores_main() {
	kernel::init_sys();

	kernel::set_handler(recv_cell_handler, bjk_handler_idx(cell));

	cell::separate(mc_out_num_cores);
	missive::separate(mc_out_num_cores);
	agent_ref::separate(mc_out_num_cores);
	agent_grp::separate(mc_out_num_cores);

	kernel* ker = BJK_KERNEL;
	MC_MARK_USED(ker);

	if(bjk_is_core(0,0)){
		bjk_slog2("CORE (0,0) started\n");
		mc_core_id_t dst = mc_ro_co_to_id(0, 1);
		wait_inited_state(dst);
		bjk_slog2("CORE (0,0) SAW core (0,1) INITED\n");

		cell* act1 = kernel::get_core_cell();
		MC_MARK_USED(act1);
		while(! act1->flags){
			ker->handle_missives();
		}
	}
	if(bjk_is_core(0,1)){
		bjk_slog2("CORE (0,1) started\n");
		mc_core_id_t dst = mc_ro_co_to_id(0, 0);
		wait_inited_state(dst);
		bjk_slog2("CORE (0,1) SAW core (0,0) INITED\n");

		
		cell* act1 = kernel::get_core_cell();
		cell* act2 = kernel::get_core_cell(dst);

		missive* msv = missive::acquire();
		msv->set_source(act1);
		msv->dst = act2;
		msv->send();

		ker->handle_missives();

		bjk_slog2("SENT MISSIVE\n");
	}

	bjk_slog2("FINISHED !!\n");	
	//bjk_xlog((mc_addr_t)ker->host_kernel);
	//bjk_slog2(" is the HOST_KERNEL\n");	

	kernel::finish_sys();
}

