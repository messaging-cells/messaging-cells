

#ifdef BJ_IS_EMU_CODE
#include "stdio.h"
#endif

#include "attribute.h"
#include "actor.hh"

bool dbg_all_idle_prt[16];
bool dbg_all_full[16];

void prt_idle();
void prt_full();
void prt_all_philo();

class chopstick;
class philosopher;

#define MAX_BITES 10

#define PH_DBG EMU_PRT

enum philo_tok_t : uint8_t {
	tok_eat,
	tok_take,
	tok_taken,
	tok_not_taken,
	tok_drop,
	tok_droped,
	tok_not_droped, 
	tok_is_full,
	tok_yes_full,
	tok_not_full,
	tok_wait_full
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
	chopstick* right;

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
		right = bj_null;

		num_bites = 0;
		lft_ph_full = false;
		rgt_ph_full = false;
	}

	void handler(missive* msv);

	void send(actor* dst, philo_tok_t tok);

	void send_full();
};

// For global data. DO NOT USE GLOBAL VARIABLES IF YOU WANT THE EMULATOR (cores as threads) TO WORK.
class philo_core {
public:
	BJK_DECLARE_MEM_METHODS(philo_core)

	chopstick stick;
	philosopher philo;
	grip ava_chopstick;
	grip ava_philosopher;
};

BJK_DEFINE_ACQUIRE_ALLOC(philo_core, 32)	// defines philo_core::acquire_alloc

#define glb_philo_core ((philo_core*)(bjk_get_kernel()->user_data))

#define glb_stick &(glb_philo_core->stick)
#define glb_philo &(glb_philo_core->philo)
#define glb_ava_sticks (glb_philo_core->ava_chopstick)
#define glb_ava_philos (glb_philo_core->ava_philosopher)

philo_core* dbg_all_philo[16];

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
	BJ_MARK_USED(nn);
	BJ_MARK_USED(src_nn);

	if(req == tok_take){
		if(owner == bj_null){
			owner = msv_src;
			respond(msv, tok_taken);
			//PH_DBG("chopstick %d TAKEN by %d \n", nn, src_nn);
		} else {
			EMU_CK(owner != bj_null);
			respond(msv, tok_not_taken);
			//PH_DBG("chopstick %d NOT_taken by %d \n", nn, src_nn);
		}
	} else if(req == tok_drop){
		if(owner == msv_src){
			owner = bj_null;
			respond(msv, tok_droped);
			//PH_DBG("chopstick %d DROPED by %d \n", nn, src_nn);
		} else {
			respond(msv, tok_not_droped);
			//PH_DBG("chopstick %d NOT_droped by %d \n", nn, src_nn);
		}
	}
	
	//bjk_get_kernel()->set_idle_exit();
}

#define left_chp_nn(nn) (nn)
#define right_chp_nn(nn) ((nn == 15)?(0):(nn + 1))

#define left_phl_nn(nn) ((nn == 0)?(15):(nn - 1))
#define right_phl_nn(nn) ((nn == 15)?(0):(nn + 1))

#define get_stick(id) ((chopstick*)bj_addr_set_id(id, glb_stick))
#define get_philo(id) ((philosopher*)bj_addr_set_id(id, glb_philo))

void
philosopher::send(actor* dst, philo_tok_t tok){
	missive* msv = missive::acquire();
	msv->src = this;
	msv->dst = dst;
	msv->tok = tok;
	msv->send();
}

void
philosopher::handler(missive* msv){
	actor* msv_src = msv->src;
	philo_tok_t tok = (philo_tok_t)msv->tok;
	bj_core_nn_t nn = bjk_get_kernel()->get_core_nn();

	EMU_CODE(
		bj_core_nn_t src_nn = bj_id_to_nn(bj_addr_get_id(msv_src));
	);
	BJ_MARK_USED(src_nn);
	//PH_DBG("philosopher %d GOT ANSWER from chopstick %d \n", nn, src_nn);

	bj_core_id_t lft_id = bj_nn_to_id(left_chp_nn(nn));
	bj_core_id_t rgt_id = bj_nn_to_id(right_chp_nn(nn));

	chopstick* lft = get_stick(lft_id);
	chopstick* rgt = get_stick(rgt_id);

	philosopher* lft_phl = get_philo(bj_nn_to_id(left_phl_nn(nn)));
	philosopher* rgt_phl = get_philo(bj_nn_to_id(right_phl_nn(nn)));

	switch(tok){
		case tok_eat:
			EMU_CK(msv_src == this);
			EMU_CK(left == bj_null);
			EMU_CK(right == bj_null);
			EMU_CK(num_bites < MAX_BITES);
			send(lft, tok_take);
		break;
		case tok_taken:
			EMU_CK((msv_src == lft) || (msv_src == rgt));
			if(msv_src == lft){
				EMU_CK(left == bj_null);
				EMU_CK(right == bj_null);
				//PH_DBG("philosopher %d TOOK LEFT \n", nn);
				left = lft;
				send(rgt, tok_take);
			}
			if(msv_src == rgt){
				EMU_CK(left == lft);
				EMU_CK(right == bj_null);
				right = rgt;
				//PH_DBG("philosopher %d TOOK RIGHT \n", nn);
				send(lft, tok_drop);
				send(rgt, tok_drop);
			}
		break;
		case tok_not_taken:
			EMU_CK((msv_src == lft) || (msv_src == rgt));
			if(msv_src == lft){
				EMU_CK(left == bj_null);
				EMU_CK(right == bj_null);
				send(this, tok_eat);
			}
			if(msv_src == rgt){
				EMU_CK(left == lft);
				EMU_CK(right == bj_null);
				send(lft, tok_drop);
			}
		break;
		case tok_droped:
			EMU_CK((msv_src == lft) || (msv_src == rgt));
			if(msv_src == lft){
				left = bj_null;
			}
			if(msv_src == rgt){
				right = bj_null;
			}
			if((left == bj_null) && (right == bj_null)){
				EMU_CK(num_bites < MAX_BITES);
				num_bites++;
				PH_DBG("NUM_BITES %d \n", num_bites);
				if(num_bites == MAX_BITES){
					PH_DBG("I AM FULL \n");
					dbg_all_full[nn] = true;
					prt_idle();
					prt_full();
					prt_all_philo();
					if(! lft_ph_full){ send(lft_phl, tok_is_full); }
					if(! rgt_ph_full){ send(rgt_phl, tok_is_full); }
					send(lft_phl, tok_yes_full);
					send(rgt_phl, tok_yes_full);
				} else {
					send(this, tok_eat);
				}
			}
		break;
		case tok_is_full:
			EMU_CK((msv_src == lft_phl) || (msv_src == rgt_phl));
			if(num_bites == MAX_BITES){
				send(msv_src, tok_yes_full);
			} else {
				send(msv_src, tok_not_full);
			}
		break;
		case tok_yes_full:
			EMU_CK((msv_src == lft_phl) || (msv_src == rgt_phl));
			if(msv_src == lft_phl){ 
				//EMU_CK(! lft_ph_full);
				lft_ph_full = true; 
			}
			if(msv_src == rgt_phl){ 
				//EMU_CK(! rgt_ph_full);
				rgt_ph_full = true; 
			}
			if((num_bites == MAX_BITES) && rgt_ph_full && lft_ph_full){
				//bjk_get_kernel()->set_idle_exit();
			} 
		break;
		case tok_not_full:
			EMU_CK(! (rgt_ph_full && lft_ph_full));
			if(num_bites == MAX_BITES){
				send(this, tok_wait_full); 
			}
		break;
		case tok_wait_full:
			//EMU_CK(msv_src == this);
			send(this, tok_wait_full); 
		break;
		default:
			bjk_abort(1, const_cast<char*>("BAD_PHILO_TOK"));
		break;
	} 
	
}

BJK_DEFINE_MEM_METHODS(chopstick, 32, glb_ava_sticks)
BJK_DEFINE_MEM_METHODS(philosopher, 32, glb_ava_philos)

void prt_idle(){
	char full_str[500];
	char* pt = full_str;
	pt += sprintf(pt, "ALL_IDLE=[");
	for(int aa = 0; aa < 16; aa++){
		bool idl = dbg_all_idle_prt[aa];
		if(idl){
			pt += sprintf(pt, "%d,", aa);
		}
	}
	pt += sprintf(pt, "]\n");
	PH_DBG("%s", full_str);
}

void prt_full(){
	char full_str[500];
	char* pt = full_str;
	pt += sprintf(pt, "ALL_FULL=[");
	for(int aa = 0; aa < 16; aa++){
		bool fll = dbg_all_full[aa];
		if(fll){
			pt += sprintf(pt, "%d,", aa);
		}
	}
	pt += sprintf(pt, "]\n");
	PH_DBG("%s", full_str);
}

void prt_ph(int aa, philosopher* ph){
	char full_str[500];
	char* pt = full_str;
	bool is_fll = (ph->num_bites == MAX_BITES);
	bool to_exit = is_fll && ph->lft_ph_full && ph->rgt_ph_full;
	pt += sprintf(pt, "PHILO %d=[", aa);
	pt += sprintf(pt, "FULL=%d ", is_fll);
	pt += sprintf(pt, "TO_EXIT=%d ", to_exit);
	pt += sprintf(pt, "left=%d ", (ph->left != bj_null)?(1):(0));
	pt += sprintf(pt, "right=%d ", (ph->right != bj_null)?(1):(0));
	pt += sprintf(pt, "num_bites=%d ", ph->num_bites);
	pt += sprintf(pt, "lft_ph_full=%d ", ph->lft_ph_full);
	pt += sprintf(pt, "rgt_ph_full=%d ", ph->rgt_ph_full);
	pt += sprintf(pt, "]\n");
	PH_DBG("%s", full_str);
}

void prt_all_philo(){
	for(int aa = 0; aa < 16; aa++){
		philo_core* phl = dbg_all_philo[aa];
		prt_ph(aa, &(phl->philo));
	}
}

void ker_func(){
	kernel* ker = bjk_get_kernel();
	bj_core_nn_t nn = ker->get_core_nn();
	if(! ker->did_work && ! dbg_all_idle_prt[nn]){
		dbg_all_idle_prt[nn] = true;
		PH_DBG("IDLE\n");
		prt_idle();
		prt_full();
	}
	if(ker->did_work && dbg_all_idle_prt[nn]){
		dbg_all_idle_prt[nn] = false;
		//PH_DBG("PHILOSOPHERS ACTIVE CORE (%d,%d)\n", ker->get_core_ro(), ker->get_core_co());
	}
}

void bj_cores_main() {
	kernel::init_sys();
	kernel* ker = bjk_get_kernel();
	BJ_MARK_USED(ker);

	bj_core_nn_t nn = ker->get_core_nn();

	dbg_all_idle_prt[nn] = false;
	dbg_all_full[nn] = false;

	//PH_DBG("PHILOSOPHERS CORE (%d,%d) starting\n", ker->get_core_ro(), ker->get_core_co());

	philo_core* core_dat = philo_core::acquire_alloc();
	ker->user_data = core_dat;
	ker->user_func = ker_func;

	dbg_all_philo[nn] = core_dat;

	if(ker->user_data == bj_null){
		bjk_abort(1, const_cast<char*>("CAN NOT INIT GLB CORE DATA"));
	}

	kernel::set_handlers(3, the_handlers);

	missive::separate(bj_out_num_cores);
	agent_ref::separate(bj_out_num_cores);
	agent_grp::separate(bj_out_num_cores);

	chopstick::separate(1);
	philosopher::separate(1);

	PH_DBG("started\n");

	missive* msv = missive::acquire();
	msv->src = glb_philo;
	msv->dst = glb_philo;
	msv->tok = tok_eat;
	msv->send();
	//philo->send
	kernel::run_sys();

	PH_DBG("finished\n");
	bjk_slog2("PHILOSOPHERS FINISHED !!\n");	

	kernel::finish_sys();
}

