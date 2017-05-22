
#include "attribute.h"
#include "actor.hh"

class chopstick;
class philosopher;

chopstick* stick;
philosopher* philo;

enum chopstick_req_t : uint8_t {
	tok_eat,
	tok_take,
	tok_taken,
	tok_not_taken,
	tok_drop,
	tok_droped,
	tok_not_droped
};

class chopstick : actor {
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

class philosopher : actor {
public:
	BJK_DECLARE_MEM_METHODS(philosopher)

	chopstick* left;
	chopstick* right;

	philosopher(){
		init_philosopher();
	}

	~philosopher(){}

	void init_philosopher(){
		handler_idx = 2;
		left = bj_null;
		right = bj_null;
	}

	void handler(missive* msv);
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
	chopstick_req_t req = (chopstick_req_t)msv->tok;

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

void
philosopher::handler(missive* msv){
	actor* msv_src = msv->src;
	chopstick_req_t tok = (chopstick_req_t)msv->tok;

	EMU_CODE(
		bj_core_nn_t nn = bjk_get_kernel()->get_core_nn();
		bj_core_nn_t src_nn = bj_id_to_nn(bj_addr_get_id(msv_src));
	);
	EMU_LOG("philosopher %d GOT ANSWER from chopstick %d \n", nn, src_nn);

	switch(tok){
		case tok_eat:
		break;
		case tok_taken:
		break;
		case tok_not_taken:
		break;
		case tok_droped:
		break;
		case tok_not_droped:
		break;
		default:
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

	kernel::run_sys();

	bjk_slog2("FINISHED !!\n");	

	kernel::finish_sys();
}

