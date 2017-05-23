
#include "attribute.h"
#include "actor.hh"

class chopstick;
class philosopher;

#define MAX_BITES 10

chopstick* stick;
philosopher* philo;

enum philo_tok_t : uint8_t {
	tok_eat,
	tok_take,
	tok_taken,
	tok_not_taken,
	tok_drop,
	tok_droped,
	tok_not_droped, 
	tok_full,
	tok_not_full
};

class chopstick : public actor {
public:
	BJK_DECLARE_MEM_METHODS(chopstick)

	actor* owner;

	chopstick(){
		init_chopstick();
	}

	~chopstick(){}

	void init_chopstick(){
		handler_idx = 1;
		owner = bj_null;
	}

	void handler(missive* msv);
};

class philosopher : public actor {
public:
	BJK_DECLARE_MEM_METHODS(philosopher)

	chopstick* left;
	int	num_bites;
	bool lft_ph_full;
	bool rgt_ph_full;

	philosopher(){
		init_philosopher();
	}

	~philosopher(){}

	void init_philosopher(){
		handler_idx = 2;
		left = bj_null;
		num_bites = 0;
		lft_ph_full = false;
		rgt_ph_full = false;
	}

	void handler(missive* msv);

	void send(actor* dst, philo_tok_t tok);

	void send_full();
};

void 
philosopher_handler(missive* msv){
	BJK_CALL_HANDLER(philosopher, handler, msv);
}

void 
chopstick_handler(missive* msv){
	BJK_CALL_HANDLER(chopstick, handler, msv);
}

missive_handler_t the_handlers[] = {
	bj_null,
	chopstick_handler,
	philosopher_handler
};

void
chopstick::handler(missive* msv){
	actor* msv_src = msv->src;
	philo_tok_t req = (philo_tok_t)msv->tok;

	EMU_CODE(
		bj_core_nn_t nn = bjk_get_kernel()->get_core_nn();
		bj_core_nn_t src_nn = bj_id_to_nn(bj_addr_get_id(msv_src));
	);

	if(req == tok_take){
		if(owner == bj_null){
			owner = msv_src;
			respond(msv, tok_taken);
			EMU_LOG("chopstick %d TAKEN by %d \n", nn, src_nn);
		} else {
			EMU_CK(owner != bj_null);
			respond(msv, tok_not_taken);
			EMU_LOG("chopstick %d NOT_taken by %d \n", nn, src_nn);
		}
	} else if(req == tok_drop){
		if(owner == msv_src){
			owner = bj_null;
			respond(msv, tok_droped);
			EMU_LOG("chopstick %d DROPED by %d \n", nn, src_nn);
		} else {
			respond(msv, tok_not_droped);
			EMU_LOG("chopstick %d NOT_droped by %d \n", nn, src_nn);
		}
	}
	
	//bjk_get_kernel()->set_idle_exit();
}

#define left_chp_nn(nn) (nn)
#define right_chp_nn(nn) ((nn == 15)?(0):(nn + 1))

#define left_phl_nn(nn) ((nn == 0)?(15):(nn - 1))
#define right_phl_nn(nn) ((nn == 15)?(0):(nn + 1))

#define get_stick(id) ((chopstick*)bj_addr_set_id(id, stick))
#define get_philo(id) ((philosopher*)bj_addr_set_id(id, philo))

void
philosopher::send(actor* dst, philo_tok_t tok){
	missive* msv = missive::acquire();
	msv->src = this;
	msv->dst = dst;
	msv->tok = tok;
	msv->send();
}

void
philosopher::send_full(){
	bj_core_nn_t nn = bjk_get_kernel()->get_core_nn();
	if(! lft_ph_full){
		philosopher* lft_phl = get_philo(bj_nn_to_id(left_phl_nn(nn)));
		send(lft_phl, tok_full);
	}
	if(! rgt_ph_full){
		philosopher* rgt_phl = get_philo(bj_nn_to_id(right_phl_nn(nn)));
		send(rgt_phl, tok_full);
	}
}

void
philosopher::handler(missive* msv){
	actor* msv_src = msv->src;
	philo_tok_t tok = (philo_tok_t)msv->tok;
	bj_core_nn_t nn = bjk_get_kernel()->get_core_nn();

	EMU_CODE(
		bj_core_nn_t src_nn = bj_id_to_nn(bj_addr_get_id(msv_src));
	);
	EMU_LOG("philosopher %d GOT ANSWER from chopstick %d \n", nn, src_nn);

	bj_core_id_t lft_id = bj_nn_to_id(left_chp_nn(nn));
	bj_core_id_t rgt_id = bj_nn_to_id(right_chp_nn(nn));

	chopstick* lft = get_stick(lft_id);
	chopstick* rgt = get_stick(rgt_id);

	switch(tok){
		case tok_eat:
			EMU_CK(num_bites < MAX_BITES);
			if((msv_src == this) && (left == bj_null)){
				send(lft, tok_take);
			}
		break;
		case tok_taken:
			if((left == bj_null) && (msv_src == lft)){
				EMU_LOG("philosopher %d TOOK LEFT \n", nn);
				left = lft;
				send(rgt, tok_take);
			}
			if((left == lft) && (msv_src == rgt)){
				EMU_LOG("philosopher %d TOOK RIGHT and EATING bite %d \n", nn, num_bites);
				send(lft, tok_drop);
				send(rgt, tok_drop);
			}
		break;
		case tok_not_taken:
			if((left == bj_null) && (msv_src == lft)){
				send(this, tok_eat);
			}
			if((left == lft) && (msv_src == rgt)){
				send(lft, tok_drop);
			}
		break;
		case tok_droped:
			num_bites++;
			if(num_bites == MAX_BITES){
				send_full();
			}
		break;
		case tok_full:
			if(msv_src == rgt){ rgt_ph_full = true; }
			if(msv_src == lft){ lft_ph_full = true; }
			if(num_bites == MAX_BITES){
				send(msv_src, tok_full);
			} else {
				send(msv_src, tok_not_full);
			}
			if(rgt_ph_full && lft_ph_full){
				bjk_get_kernel()->set_idle_exit();
			}
		break;
		case tok_not_full:
			send_full();
		break;
		default:
			bjk_abort(1, const_cast<char*>("BAD_PHILO_TOK"));
		break;
	} 
	
}

grip ava_chopstick;
grip ava_philosopher;

BJK_DEFINE_MEM_METHODS(chopstick, 32, ava_chopstick)
BJK_DEFINE_MEM_METHODS(philosopher, 32, ava_philosopher)

void bj_cores_main() {
	kernel::init_sys();

	kernel::set_handlers(3, the_handlers);

	missive::separate(bj_out_num_cores);
	agent_ref::separate(bj_out_num_cores);
	agent_grp::separate(bj_out_num_cores);

	chopstick::separate(1);
	philosopher::separate(1);

	kernel* ker = bjk_get_kernel();
	BJ_MARK_USED(ker);

	stick = chopstick::acquire();
	philo = philosopher::acquire();

	EMU_PRT("PHILOSOPHERS CORE (%d,%d) started\n", ker->get_core_ro(), ker->get_core_co());

	missive* msv = missive::acquire();
	msv->src = philo;
	msv->dst = philo;
	msv->tok = tok_eat;
	msv->send();
	//philo->send
	//kernel::run_sys();

	EMU_LOG("PHILOSOPHERS CORE (%d,%d) finished\n", ker->get_core_ro(), ker->get_core_co());
	bjk_slog2("PHILOSOPHERS FINISHED !!\n");	

	kernel::finish_sys();
}

