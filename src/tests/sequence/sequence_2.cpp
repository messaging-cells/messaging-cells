

#ifdef BJ_IS_EMU_CODE
#include "stdio.h"
#endif

#include "attribute.h"
#include "actor.hh"

class sequence;

#define MAX_MSVS 5000

#define PH_DBG EMU_PRT

typedef uint32_t seq_tok_t;

class sequence : public actor {
public:
	BJK_DECLARE_MEM_METHODS(sequence)

	seq_tok_t last_sent;
	seq_tok_t last_recv;

	sequence(){
		init_sequence();
	}

	~sequence(){}

	void init_sequence(){
		handler_idx = 1;

		last_sent = 0;
		last_recv = 0;
	}

	void handler(missive* msv);
	void send(actor* dst, seq_tok_t tok);
};

// For global data. DO NOT USE GLOBAL VARIABLES IF YOU WANT THE EMULATOR (cores as threads) TO WORK.
class seq_core {
public:
	BJK_DECLARE_MEM_METHODS(seq_core)

	sequence my_seq;
	grip ava_seq;
};

BJK_DEFINE_ACQUIRE_ALLOC(seq_core, 32)	// defines seq_core::acquire_alloc

#define glb_seq_core ((seq_core*)(bjk_get_kernel()->user_data))
#define glb_my_seq &(glb_seq_core->my_seq)

#define get_my_seq(id) ((sequence*)bj_addr_set_id(id, glb_my_seq))

#define glb_sender get_my_seq(bj_nn_to_id(1))
#define glb_receiver get_my_seq(bj_nn_to_id(0))
#define glb_ava_seq (glb_seq_core->ava_seq)

void 
sequence_handler(missive* msv){
	BJK_CALL_HANDLER(sequence, handler, msv);
}

missive_handler_t the_handlers[] = {
	bj_null,
	sequence_handler
};

void
sequence::handler(missive* msv){
	actor* msv_src = msv->src;
	seq_tok_t tok = (seq_tok_t)msv->tok;
	BJ_MARK_USED(msv_src);
	BJ_MARK_USED(tok);

	kernel* ker = bjk_get_kernel();
	bj_core_nn_t nn = ker->get_core_nn();

	bool is_sender = (nn == 1);

	PH_DBG("is_sender=%d tok=%d last_recv=%d\n", is_sender, tok, last_recv);
	EMU_CK(tok == (last_recv + 1));
	last_recv = tok;

	if(is_sender){
		EMU_CK(msv_src == glb_receiver);
		EMU_CK(last_recv == last_sent);
		last_sent += 1;
	} else {
		EMU_CK(msv_src == glb_sender);
		last_sent = last_recv;
	}

	bool is_last = (last_sent == MAX_MSVS);
	if(! is_sender && is_last){
		bjk_get_kernel()->set_idle_exit();
		return;
	}

	respond(msv, last_sent);

	if(is_sender && is_last){
		bjk_get_kernel()->set_idle_exit();
	}
}

void
sequence::send(actor* dst, seq_tok_t tok){
	last_sent = tok;
	missive* msv = missive::acquire();
	msv->src = this;
	msv->dst = dst;
	msv->tok = tok;
	msv->send();
}

BJK_DEFINE_MEM_METHODS(sequence, 32, glb_ava_seq)

void ker_func(){
	kernel* ker = bjk_get_kernel();
	bj_core_nn_t nn = ker->get_core_nn();
	BJ_MARK_USED(ker);
	BJ_MARK_USED(nn);
}

void bj_cores_main() {
	kernel::init_sys();
	kernel* ker = bjk_get_kernel();
	BJ_MARK_USED(ker);

	bj_core_nn_t nn = ker->get_core_nn();
	
	if((nn != 0) && (nn != 1)){
		PH_DBG("SKIP\n");
		kernel::finish_sys();
		return;
	}

	seq_core* core_dat = seq_core::acquire_alloc();
	ker->user_data = core_dat;
	ker->user_func = ker_func;

	kernel::set_handlers(2, the_handlers);

	missive::separate(bj_out_num_cores);
	agent_ref::separate(bj_out_num_cores);
	agent_grp::separate(bj_out_num_cores);

	PH_DBG("started\n");
	if(nn == 1){
		glb_sender->send(glb_receiver, 1);
	}

	kernel::run_sys();

	PH_DBG("SEQ_2 finished\n");
	bjk_slog2("SEQUENCE 2 FINISHED !!\n");	

	kernel::finish_sys();
}

