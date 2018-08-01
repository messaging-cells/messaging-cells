

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


#ifdef MC_IS_PTD_CODE
#include "stdio.h"
#endif

#include "attribute.h"
#include "cell.hh"

class sequence;

#define MAX_MSVS 5000

#define PH_DBG PTD_PRT

typedef uint32_t seq_tok_t;

class sequence : public cell {
public:
	MCK_DECLARE_MEM_METHODS(sequence, mc_mod0_cod)

	bool is_sender;

	seq_tok_t last_sent;
	seq_tok_t last_recv;

	sequence(){
		init_sequence();
	}

	~sequence(){}

	void init_sequence(){
		handler_idx = 1;

		is_sender = false;
		last_sent = 0;
		last_recv = 0;
	}

	void handler(missive* msv);
	void send(cell* dst, seq_tok_t tok);

	virtual 
	grip&	get_available();
};

// For global data. DO NOT USE GLOBAL VARIABLES IF YOU WANT THE PTD (workerunis as threads) TO WORK.
class seq_workeruni {
public:
	MCK_DECLARE_MEM_METHODS(seq_workeruni, mc_mod0_cod)

	sequence sender;
	sequence receiver;
	grip ava_seq;
};

MCK_DEFINE_ACQUIRE_ALLOC(seq_workeruni, 32)	// defines seq_workeruni::acquire_alloc

#define glb_seq_workeruni ((seq_workeruni*)(mck_get_kernel()->user_data))
#define glb_sender (&(glb_seq_workeruni->sender))
#define glb_receiver (&(glb_seq_workeruni->receiver))
#define glb_ava_seq (glb_seq_workeruni->ava_seq)

void 
sequence_handler(missive* msv){
	MCK_CALL_HANDLER(sequence, handler, msv);
}

missive_handler_t the_handlers[] = {
	mc_null,
	sequence_handler
};

void
sequence::handler(missive* msv){
	cell* msv_src = msv->src;
	seq_tok_t tok = (seq_tok_t)msv->tok;
	MC_MARK_USED(msv_src);
	MC_MARK_USED(tok);

	PH_DBG("is_sender=%d tok=%d last_recv=%d\n", is_sender, tok, last_recv);
	PTD_CK(tok == (last_recv + 1));
	last_recv = tok;

	if(is_sender){
		PTD_CK(msv_src == glb_receiver);
		PTD_CK(last_recv == last_sent);
		last_sent += 1;
		if(last_sent == MAX_MSVS){
			mck_get_kernel()->set_idle_exit();
			return;
		}
	} else {
		PTD_CK(msv_src == glb_sender);
		last_sent = last_recv;
	}
	respond(msv, last_sent);
}

void
sequence::send(cell* dst, seq_tok_t tok){
	last_sent = tok;
	missive* msv = missive::acquire();
	msv->src = this;
	msv->dst = dst;
	msv->tok = tok;
	msv->send();
}

MCK_DEFINE_MEM_METHODS(sequence, 32, glb_ava_seq, 0)

grip&
sequence::get_available(){
	return glb_ava_seq;
}

void ker_func(){
	kernel* ker = mck_get_kernel();
	mc_workeru_nn_t nn = ker->get_workeru_nn();
	MC_MARK_USED(ker);
	MC_MARK_USED(nn);
}

void mc_workerus_main() {
	kernel::init_sys();
	kernel* ker = mck_get_kernel();
	MC_MARK_USED(ker);

	if(! mck_is_ro_co_workeruni(0,0)){
		PH_DBG("SKIP\n");
		kernel::finish_sys();
		return;
	}

	seq_workeruni* workeruni_dat = seq_workeruni::acquire_alloc();
	ker->user_data = workeruni_dat;
	ker->user_func = ker_func;

	kernel::set_handlers(2, the_handlers);

	missive::separate(mc_out_num_workerunis);
	agent_ref::separate(mc_out_num_workerunis);
	agent_grp::separate(mc_out_num_workerunis);

	PH_DBG("started\n");
	glb_sender->is_sender = true;
	glb_sender->send(glb_receiver, 1);

	kernel::run_sys();

	PH_DBG("SEQ_1 finished\n");
	mck_slog2("SEQUENCE 1 FINISHED !!\n");	

	kernel::finish_sys();
}

