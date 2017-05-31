
#include <stdio.h>

#include "booter.h"
#include "actor.hh"

char* bjh_epiphany_elf_path = (const_cast<char*>("the_epiphany_executable.elf"));

void recv_actor_handler(missive* msg);

void 
recv_actor_handler(missive* msg){
	BJK_UPDATE_MIN_SP();
	EMU_PRT("RCV_MSV=%p \n", msg);
	EMU_PRT("RCV_msv=%p SRC=%p DST=%p \n", (void*)msg, msg->src, msg->dst);
	EMU_PRT("RCV_CORE_ID=%x \n", bj_addr_get_id(msg->dst));
	EMU_PRT("RCV_GLB_CORE_ID=%x \n", BJK_GLB_SYS->the_core_id);

	EMU_CK(bj_addr_is_local(msg->dst));
	bj_core_id_t koid = kernel::get_core_id();
	BJ_MARK_USED(koid);
	bj_core_nn_t konn = kernel::get_core_nn();
	BJ_MARK_USED(konn);
	bjk_slog2("HOST GOT MISSIVE\n");
	EMU_LOG("recv_actor_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	EMU_PRT("RCV_MSV. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	
	bjk_get_kernel()->set_idle_exit();
}

missive_handler_t the_handlers[] = {
	recv_actor_handler
};


int bj_host_main(int argc, char *argv[])
{
	if(argc > 1){
		bjh_epiphany_elf_path = argv[1];
		printf("Using core executable: %s \n", bjh_epiphany_elf_path);
	}
	if(argc > 2){
		printf("LOADING WITH MEMCPY \n");
		BJH_LOAD_WITH_MEMCPY = true;
	}

	kernel::init_host_sys();

	kernel::set_handlers(1, the_handlers);

	actor::separate(bj_out_num_cores);
	missive::separate(bj_out_num_cores);
	agent_ref::separate(bj_out_num_cores);
	agent_grp::separate(bj_out_num_cores);

	//bjk_slog2("HOST started\n");
	kernel::get_core_actor()->handler_idx = 0;	// was 0 but it should be inited for every actors's subclass.

	kernel::run_host_sys();
	kernel::finish_host_sys();

	printf("ALL FINISHED ==================================== \n");

	return 0;
}


