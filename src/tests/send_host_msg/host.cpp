
#include <stdio.h>

#include "booter.h"
#include "cell.hh"

#include "resp_conf.h"

char* mch_epiphany_elf_path = (const_cast<char*>("the_epiphany_executable.elf"));

void recv_host_handler(missive* msg);

void 
recv_host_handler(missive* msg){
	BJK_UPDATE_MIN_SP();
	EMU_PRT("RCV_MSV=%p \n", msg);
	EMU_PRT("RCV_msv=%p SRC=%p DST=%p \n", (void*)msg, msg->src, msg->dst);
	EMU_PRT("RCV_CORE_ID=%x \n", mc_addr_get_id(msg->dst));
	EMU_PRT("RCV_GLB_CORE_ID=%x \n", BJK_GLB_SYS->the_core_id);
	printf("HOST_RECEIVED_MSV !!!\n");

	EMU_CK(mc_addr_is_local(msg->dst));
	mc_core_id_t koid = kernel::get_core_id();
	MC_MARK_USED(koid);
	mc_core_nn_t konn = kernel::get_core_nn();
	MC_MARK_USED(konn);


	EMU_LOG("recv_host_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);
	EMU_PRT("RCV_MSV. core_id=%lx core_nn=%d src=%p dst=%p \n", koid, konn, msg->get_source(), msg->dst);

	#ifdef WITH_RESPONSE
		msg->dst->respond(msg, (msg->tok + 10)); 
		printf("HOST_RESPONDED\n");
	#endif 


	mck_get_kernel()->set_idle_exit();
}

missive_handler_t host_handlers[] = {
	recv_host_handler
};

void
send_host_main(){
	kernel::init_host_sys();

	kernel::set_handlers(1, host_handlers);

	cell::separate(mc_out_num_cores);
	missive::separate(mc_out_num_cores);
	agent_ref::separate(mc_out_num_cores);
	agent_grp::separate(mc_out_num_cores);

	//mck_slog2("HOST started\n");
	kernel::get_core_cell()->handler_idx = 0;	// was 0 but it should be inited for every cells's subclass.

	mc_size_t off_all_agts = mc_offsetof(&missive_grp_t::all_agts);
	MC_MARK_USED(off_all_agts);

	printf("HOST STARTING ==================================== \n");
	ZNQ_CODE(printf("off_all_agts=%d \n", off_all_agts));

	kernel::run_host_sys();
	kernel::finish_host_sys();

	printf("ALL FINISHED ==================================== \n");
}

int mc_host_main(int argc, char *argv[])
{
	if(argc > 1){
		mch_epiphany_elf_path = argv[1];
		printf("Using core executable: %s \n", mch_epiphany_elf_path);
	}
	if(argc > 2){
		printf("LOADING WITH MEMCPY \n");
		BJH_LOAD_WITH_MEMCPY = true;
	}

	send_host_main();

	return 0;
}


