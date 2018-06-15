

/*************************************************************

This file is part of messaging-cells.

messaging-cells is free software: you can redistribute it and/or modify
it under the terms of the version 3 of the GNU General Public 
License as published by the Free Software Foundation.

messaging-cells is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with messaging-cells.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------------

Copyright (C) 2017-2018. QUIROGA BELTRAN, Jose Luis.
Id (cedula): 79523732 de Bogota - Colombia.
See https://messaging-cells.github.io/

messaging-cells is free software thanks to The Glory of Our Lord 
	Yashua Melej Hamashiaj.
Our Resurrected and Living, both in Body and Spirit, 
	Prince of Peace.

------------------------------------------------------------*/


#include <stdio.h>

#include "booter.h"
#include "cell.hh"

#include "resp_conf.h"

char* mch_epiphany_elf_path = (mc_cstr("the_epiphany_executable.elf"));

void recv_host_handler(missive* msg);

void 
recv_host_handler(missive* msg){
	EMU_PRT("RCV_MSV=%p \n", msg);
	EMU_PRT("RCV_msv=%p SRC=%p DST=%p \n", (void*)msg, msg->src, msg->dst);
	EMU_PRT("RCV_CORE_ID=%x \n", mc_addr_get_id(msg->dst));
	EMU_PRT("RCV_GLB_CORE_ID=%x \n", MC_CORE_INFO->the_core_id);
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
	mc_null,
	recv_host_handler
};

void
send_host_main(){
	kernel::init_host_sys();

	kernel::set_handlers(2, host_handlers);

	cell::separate(mc_out_num_cores);
	missive::separate(mc_out_num_cores);
	agent_ref::separate(mc_out_num_cores);
	agent_grp::separate(mc_out_num_cores);

	//mck_slog2("HOST started\n");
	kernel::get_core_cell()->handler_idx = 1;

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
		MCH_LOAD_WITH_MEMCPY = true;
	}

	send_host_main();

	return 0;
}


