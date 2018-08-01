

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


#include "cell.hh"

#include "resp_conf.h"

void recv_workeru_handler(missive* msg);

void 
recv_workeru_handler(missive* msg){
	PTD_CK(mc_addr_is_local(msg->dst));

	mck_sprt2("WORKERUNI_GOT_RESPONSE\n");
	PTD_PRT("RCV_RESPONSE. src=%p dst=%p \n", msg->get_source(), msg->dst);
	
	mck_get_kernel()->set_idle_exit();
}

missive_handler_t workeruni_handlers[] = {
	mc_null,
	recv_workeru_handler
};

void mc_workerus_main() {
	kernel::init_sys();

	cell::separate(mc_out_num_workerunis);
	missive::separate(mc_out_num_workerunis);
	agent_ref::separate(mc_out_num_workerunis);
	agent_grp::separate(mc_out_num_workerunis);

	kernel::get_workeru_cell()->handler_idx = 1;

	kernel* ker = mck_get_kernel();
	MC_MARK_USED(ker);

	if(mck_is_ro_co_workeruni(0,0)){
		mck_slog2("WORKERUNI (0,0) started\n");

		kernel::set_handlers(2, workeruni_handlers);

		cell* act1 = kernel::get_workeru_cell();
		cell* act2 = kernel::get_manageru_cell();

		PTD_CK_PRT((mc_addr_get_id((mc_addr_t)act2) != 0), "act2 = %p\n", act2);

		missive* msv = missive::acquire();
		msv->src = act1;
		msv->dst = act2;
		msv->tok = 432;

		mck_sprt2("SND_act2___");
		mck_xprt((mc_addr_t)(act2));
		mck_sprt2("___\n");

		MCK_CK(act2 != mc_null);

		msv->send_to_manageru();

		PTD_PRT("SND_SENT H MISSIVE\n");

		#ifndef WITH_RESPONSE
			ker->set_idle_exit();
		#endif

		kernel::run_sys();
	}

	mck_slog2("FINISHED SEND_MANAGERU TEST\n");	

	kernel::finish_sys();
}

