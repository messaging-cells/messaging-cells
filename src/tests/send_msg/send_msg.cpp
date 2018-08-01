

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
/*! \file send_msg.cpp

\brief Simple send missive example.

\details 

\include send_msg.cpp

------------------------------------------------------------*/

#include "cell.hh"

/*! 
\brief This function will handle messages for a \ref cell when it has zero in 
\ref cell::handler_idx and \ref kernel::all_handlers has been set to \ref the_handlers 
with \ref kernel::set_handlers
*/
void recv_cell_handler(missive* msg);

void 
recv_cell_handler(missive* msg){
	PTD_CODE(
		PTD_CK(mc_addr_is_local(msg->dst));
		mc_core_id_t koid = kernel::get_core_id();
		MC_MARK_USED(koid);
		mc_core_nn_t konn = kernel::get_core_nn();
		MC_MARK_USED(konn);
		PTD_LOG("recv_cell_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", 
				koid, konn, msg->get_source(), msg->dst);
		PTD_PRT("recv_cell_handler. core_id=%lx core_nn=%d src=%p dst=%p \n", 
				koid, konn, msg->get_source(), msg->dst);
	)

	mck_slog2("GOT MISSIVE\n");
	
	mck_get_kernel()->set_idle_exit();
}

/*! 
\brief This will be \ref kernel::all_handlers when \ref kernel::set_handlers gets called.
*/
missive_handler_t the_handlers[] = {
	recv_cell_handler  // Index 0. Cells with zero in handler_idx will handle missives with this handler.
};

void mc_workerus_main() {
	kernel::init_sys();

	kernel::set_handlers(1, the_handlers);

	cell::separate(mc_out_num_cores);
	missive::separate(mc_out_num_cores);
	agent_ref::separate(mc_out_num_cores);
	agent_grp::separate(mc_out_num_cores);

	kernel* ker = mck_get_kernel();
	MC_MARK_USED(ker);

	if(mck_is_ro_co_core(0,0)){
		mck_slog2("CORE (0,0) started\n");

		// Next line is just to remaind that every single cell should have a valid handler_idx. It was already 0.
		kernel::get_core_cell()->handler_idx = 0;	// This is recv_cell_handler's index in the_handlers.

		kernel::run_sys();
	}
	if(mck_is_ro_co_core(0,1)){
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

	kernel::finish_sys();
}

