

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
	void send(actor* dst, seq_tok_t tok);
};

// For global data. DO NOT USE GLOBAL VARIABLES IF YOU WANT THE EMULATOR (cores as threads) TO WORK.
class seq_core {
public:
	BJK_DECLARE_MEM_METHODS(seq_core)

	sequence sender;
	sequence receiver;
	grip ava_seq;
};

BJK_DEFINE_ACQUIRE_ALLOC(seq_core, 32)	// defines seq_core::acquire_alloc

#define glb_seq_core ((seq_core*)(bjk_get_kernel()->user_data))
#define glb_sender (&(glb_seq_core->sender))
#define glb_receiver (&(glb_seq_core->receiver))
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

	PH_DBG("is_sender=%d tok=%d last_recv=%d\n", is_sender, tok, last_recv);
	EMU_CK(tok == (last_recv + 1));
	last_recv = tok;

	if(is_sender){
		EMU_CK(msv_src == glb_receiver);
		EMU_CK(last_recv == last_sent);
		last_sent += 1;
		if(last_sent == MAX_MSVS){
			bjk_get_kernel()->set_idle_exit();
			return;
		}
	} else {
		EMU_CK(msv_src == glb_sender);
		last_sent = last_recv;
	}
	respond(msv, last_sent);
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

	if(! bjk_is_core(0,0)){
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
	glb_sender->is_sender = true;
	glb_sender->send(glb_receiver, 1);

	kernel::run_sys();

	PH_DBG("SEQ_1 finished\n");
	bjk_slog2("SEQUENCE 1 FINISHED !!\n");	

	kernel::finish_sys();
}

