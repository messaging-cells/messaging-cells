
#include <new>
#include "attribute.h"
#include "actor.hh"

#ifdef BJ_IS_EMU_CODE
#define PHILO_WITH_DBG
#endif

#ifdef PHILO_WITH_DBG
	#include "stdio.h"

	bool dbg_all_idle_prt[16] bj_external_code_ram = {
		false, false, false, false, 
		false, false, false, false, 
		false, false, false, false, 
		false, false, false, false
	};
	bool dbg_all_full[16] bj_external_code_ram = {
		false, false, false, false, 
		false, false, false, false, 
		false, false, false, false, 
		false, false, false, false
	};

	void prt_idle() bj_external_code_ram;
	void prt_full() bj_external_code_ram;
	void prt_all_philo() bj_external_code_ram;

	bool prt_recv_msgs bj_external_code_ram = false;
	bool prt_send_msgs bj_external_code_ram = false;

	#define PH_DBG_COD(prm) prm
#else
	#define PH_DBG_COD(prm) 
#endif

class chopstick;
class philosopher;

#define MAX_BITES 10

#define PH_DBG EMU_PRT

enum philo_tok_t : uint8_t {
	tok_invalid,
	tok_eat,
	tok_take,
	tok_taken,
	tok_not_taken,
	tok_drop,
	tok_droped,
	tok_not_droped, 
	tok_yes_full
};

#ifdef PHILO_WITH_DBG
	char*
	tok_to_str(philo_tok_t tok) bj_external_code_ram;

	char*
	tok_to_str(philo_tok_t tok){
		switch(tok){
		case tok_invalid:
			return const_cast<char*>("invalid");
		break;
		case tok_eat:
			return const_cast<char*>("eat");
		break;
		case tok_take:
			return const_cast<char*>("take");
		break;
		case tok_taken:
			return const_cast<char*>("taken");
		break;
		case tok_not_taken:
			return const_cast<char*>("not_taken");
		break;
		case tok_drop:
			return const_cast<char*>("drop");
		break;
		case tok_droped:
			return const_cast<char*>("droped");
		break;
		case tok_not_droped:
			return const_cast<char*>("not_droped");
		break;
		case tok_yes_full:
			return const_cast<char*>("yes_fll");
		break;
		default:
			bjk_abort(1, const_cast<char*>("BAD_PHILO_TOK"));
		break;
		}
		return const_cast<char*>("NO_TOK");
	}
#endif

class chopstick : public actor {
public:
	BJK_DECLARE_MEM_METHODS(chopstick)

	actor* owner;

	actor* last_src;
	philo_tok_t last_sent;
	philo_tok_t last_recv;

	chopstick(){
		init_chopstick();
	}

	~chopstick(){}

	void init_chopstick(){
		handler_idx = 1;
		owner = bj_null;

		last_src = bj_null;
		last_sent = tok_invalid;
		last_recv = tok_invalid;
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

	bj_core_id_t	lft_stk_id;
	bj_core_id_t	rgt_stk_id;
	chopstick*		lft_stick;
	chopstick*		rgt_stick;
	bj_core_id_t	lft_phi_id;
	bj_core_id_t	rgt_phi_id;
	philosopher*	lft_philo;
	philosopher*	rgt_philo;

	philo_tok_t last_sent;
	philo_tok_t last_sent_lft;
	philo_tok_t last_sent_rgt;
	philo_tok_t last_recv;
	philo_tok_t last_recv_lft;
	philo_tok_t last_recv_rgt;

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

		lft_stk_id = ~0;
		rgt_stk_id = ~0;
		lft_stick = bj_null;
		rgt_stick = bj_null;
		lft_phi_id = ~0;
		rgt_phi_id = ~0;
		lft_philo = bj_null;
		rgt_philo = bj_null;

		last_sent = tok_invalid;
		last_sent_lft = tok_invalid;
		last_sent_rgt = tok_invalid;
		last_recv = tok_invalid;
		last_recv_lft = tok_invalid;
		last_recv_rgt = tok_invalid;
	}

	void handler(missive* msv);

	void send(actor* dst, philo_tok_t tok);

	void send_full();

	bool can_exit(){
		return ((left == bj_null) && (right == bj_null) && (num_bites == MAX_BITES) && rgt_ph_full && lft_ph_full);
	}
};

// For global data. DO NOT USE GLOBAL VARIABLES IF YOU WANT THE EMULATOR (cores as threads) TO WORK.
class philo_core {
public:
	BJK_DECLARE_MEM_METHODS(philo_core)

	philo_core(){		// NEED THIS SO THAT no memset func call
		init_philo_core();
	}		
	~philo_core(){}		// NEED THIS SO THAT no memset func call

	chopstick stick;
	philosopher philo;
	grip ava_chopstick;
	grip ava_philosopher;

	bj_size_t from_host_work_sz;
	bj_size_t to_host_work_sz;
	bj_size_t in_work_sz;
	bj_size_t local_work_sz;
	bj_size_t out_work_sz;
	bj_size_t sent_work_sz;
	bj_size_t cls_available_actor_sz;
	bj_size_t cls_available_missive_sz;
	bj_size_t cls_available_agent_ref_sz;
	bj_size_t cls_available_agent_grp_sz;

	void init_philo_core(){
		from_host_work_sz = 0;
		to_host_work_sz = 0;
		in_work_sz = 0;
		local_work_sz = 0;
		out_work_sz = 0;
		sent_work_sz = 0;
		cls_available_actor_sz = 0;
		cls_available_missive_sz = 0;
		cls_available_agent_ref_sz = 0;
		cls_available_agent_grp_sz = 0;
	}
};

BJK_DEFINE_ACQUIRE_ALLOC(philo_core, 32)	// defines philo_core::acquire_alloc

#define glb_philo_core ((philo_core*)(bjk_get_kernel()->user_data))

#define glb_stick (&(glb_philo_core->stick))
#define glb_philo (&(glb_philo_core->philo))

#define glb_ava_sticks (glb_philo_core->ava_chopstick)
#define glb_ava_philos (glb_philo_core->ava_philosopher)

#define left_chp_nn(nn) (nn)
#define right_chp_nn(nn) ((nn == 15)?(0):(nn + 1))

#define left_phl_nn(nn) ((nn == 0)?(15):(nn - 1))
#define right_phl_nn(nn) ((nn == 15)?(0):(nn + 1))

#define get_stick(id) ((chopstick*)bj_addr_set_id(id, glb_stick))
#define get_philo(id) ((philosopher*)bj_addr_set_id(id, glb_philo))

BJK_DEFINE_MEM_METHODS(chopstick, 32, glb_ava_sticks)
BJK_DEFINE_MEM_METHODS(philosopher, 32, glb_ava_philos)


#ifdef PHILO_WITH_DBG
philo_core* 
dbg_all_philo[16] bj_external_code_ram = {
	bj_null, bj_null, bj_null, bj_null, 
	bj_null, bj_null, bj_null, bj_null, 
	bj_null, bj_null, bj_null, bj_null, 
	bj_null, bj_null, bj_null, bj_null
};
#endif

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
	philo_tok_t tok = (philo_tok_t)msv->tok;

	last_src = msv_src;
	last_recv = tok;

	PH_DBG_COD(
		bj_core_nn_t nn = bjk_get_kernel()->get_core_nn();
		if(prt_recv_msgs){
			PH_DBG("CHOP %d RECV %s \n", nn, tok_to_str(tok));
		}
	)

	switch(tok){
		case tok_take:
			EMU_CK(owner != msv_src);
			if(owner == bj_null){
				owner = msv_src;
				last_sent = tok_taken;
				respond(msv, tok_taken);
			} else {
				EMU_CK(owner != bj_null);
				last_sent = tok_not_taken;
				respond(msv, tok_not_taken);
			}
		break;
		case tok_drop:
			EMU_CK(owner == msv_src);
			owner = bj_null;
			last_sent = tok_droped;
			respond(msv, tok_droped);
		break;
		default:
			bjk_abort(1, const_cast<char*>("BAD_STICK_TOK"));
		break;
	}
	
	//bjk_get_kernel()->set_idle_exit();
}

void
philosopher::send(actor* dst, philo_tok_t tok){
	PH_DBG_COD(
		if(prt_send_msgs){
			PH_DBG("PHIL SEND %d \n", tok);
		}
	)

	last_sent = tok;
	if(dst == lft_stick){ last_sent_lft = tok; }
	if(dst == rgt_stick){ last_sent_rgt = tok; }

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
	BJ_MARK_USED(nn);

	PH_DBG_COD(
		if(prt_recv_msgs){
			PH_DBG("PHIL %d RECV %s \n", nn, tok_to_str(tok));
		}
	)

	last_recv = tok;

	if(msv_src == lft_stick){ last_recv_lft = tok; }
	if(msv_src == rgt_stick){ last_recv_rgt = tok; }

	switch(tok){
		case tok_eat:
			EMU_CK(msv_src == this);
			EMU_CK(left == bj_null);
			EMU_CK(right == bj_null);
			EMU_CK(num_bites < MAX_BITES);
			send(lft_stick, tok_take);
		break;
		case tok_taken:
			EMU_CK((msv_src == lft_stick) || (msv_src == rgt_stick));
			if(msv_src == lft_stick){
				EMU_CK(left == bj_null);
				EMU_CK(right == bj_null);
				left = lft_stick;
				send(rgt_stick, tok_take);
			}
			if(msv_src == rgt_stick){
				EMU_CK(left == lft_stick);
				EMU_CK(right == bj_null);
				right = rgt_stick;

				EMU_CK(left != bj_null);
				EMU_CK(right != bj_null);
				EMU_CK(num_bites < MAX_BITES);
				num_bites++;
				PH_DBG("NUM_BITES %d \n", num_bites);
				EMU_LOG("NUM_BITES %d \n", num_bites);

				send(lft_stick, tok_drop);
				send(rgt_stick, tok_drop);
			}
		break;
		case tok_not_taken:
			EMU_CK((msv_src == lft_stick) || (msv_src == rgt_stick));
			if(msv_src == lft_stick){
				EMU_CK(left == bj_null);
				EMU_CK(right == bj_null);
				send(this, tok_eat);
			}
			if(msv_src == rgt_stick){
				EMU_CK(left == lft_stick);
				EMU_CK(right == bj_null);
				send(lft_stick, tok_drop);
			}
		break;
		case tok_droped:
			EMU_CK((msv_src == lft_stick) || (msv_src == rgt_stick));
			if(msv_src == lft_stick){
				EMU_CK(left == lft_stick);
				left = bj_null;
			}
			if(msv_src == rgt_stick){
				EMU_CK(right == rgt_stick);
				right = bj_null;
			}
			if((left == bj_null) && (right == bj_null)){
				if(num_bites == MAX_BITES){
					PH_DBG("I AM FULL \n");
					EMU_LOG("I AM FULL \n");

					PH_DBG_COD(bj_set_off_chip_var(dbg_all_full[nn], true);)

					send(lft_philo, tok_yes_full);
					send(rgt_philo, tok_yes_full);

					if(can_exit()){
						PH_DBG_COD(
							prt_idle();
							prt_full();
							prt_all_philo();
						)
						EMU_LOG("FINISHING \n");
						bjk_get_kernel()->set_idle_exit();
					}
				} else {
					send(this, tok_eat);
				}
			}
		break;
		case tok_yes_full:
			EMU_CK((msv_src == lft_philo) || (msv_src == rgt_philo));
			if(msv_src == lft_philo){ 
				EMU_CK(! lft_ph_full);
				lft_ph_full = true; 
			}
			if(msv_src == rgt_philo){ 
				EMU_CK(! rgt_ph_full);
				rgt_ph_full = true; 
			}
			if(can_exit()){
				PH_DBG_COD(
					prt_idle();
					prt_full();
					prt_all_philo();
				)
				EMU_LOG("FINISHING \n");
				bjk_get_kernel()->set_idle_exit();
			}
		break;
		default:
			bjk_abort(1, const_cast<char*>("BAD_PHILO_TOK"));
		break;
	} 
	
}

#ifdef PHILO_WITH_DBG
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
	bool to_exit = ph->can_exit();
	pt += sprintf(pt, "PHILO (%p) %d=[", ph, aa);
	pt += sprintf(pt, "F%d ", is_fll);
	pt += sprintf(pt, "X%d ", to_exit);
	pt += sprintf(pt, "L%d ", (ph->left != bj_null)?(1):(0));
	pt += sprintf(pt, "R%d ", (ph->right != bj_null)?(1):(0));
	pt += sprintf(pt, "N%d ", ph->num_bites);
	pt += sprintf(pt, "LF%d ", ph->lft_ph_full);
	pt += sprintf(pt, "RF%d ", ph->rgt_ph_full);
	pt += sprintf(pt, "Lsnt=%s ", tok_to_str(ph->last_sent_lft));
	pt += sprintf(pt, "Lrcv=%s ", tok_to_str(ph->last_recv_lft));
	pt += sprintf(pt, "Rsnt=%s ", tok_to_str(ph->last_sent_rgt));
	pt += sprintf(pt, "Rrcv=%s ", tok_to_str(ph->last_recv_rgt));
	pt += sprintf(pt, "]\n");
	PH_DBG("%s", full_str);
}

void prt_ch(int aa, chopstick* ch){
	char full_str[500];
	char* pt = full_str;
	pt += sprintf(pt, "STICK (%p) %d=[", ch, aa);
	pt += sprintf(pt, "lst_sent=%s ", tok_to_str(ch->last_sent));
	pt += sprintf(pt, "lst_recv=%s ", tok_to_str(ch->last_recv));
	pt += sprintf(pt, "lst_src=%p ", ch->last_src);
	pt += sprintf(pt, "]\n");
	PH_DBG(full_str);
}

void prt_pc(int aa, philo_core* pc){
	char full_str[500];
	char* pt = full_str;
	pt += sprintf(pt, "CORE %d=[", aa);
	EMU_CODE(
		pt += sprintf(pt, "out_work_sz=%ld ", pc->out_work_sz);
		pt += sprintf(pt, "sent_work_sz=%ld ", pc->sent_work_sz);
	)
	EPH_CODE(
		pt += sprintf(pt, "out_work_sz=%d ", pc->out_work_sz);
		pt += sprintf(pt, "sent_work_sz=%d ", pc->sent_work_sz);
	)
	pt += sprintf(pt, "]\n");
	PH_DBG(full_str);
}

void prt_all_philo(){
	for(int aa = 0; aa < 16; aa++){
		philo_core* phl = dbg_all_philo[aa];
		if(phl != bj_null){
			prt_ch(aa, &(phl->stick));
			prt_ph(aa, &(phl->philo));
			prt_pc(aa, phl);
		}
	}
}

void ker_func(){
	kernel* ker = bjk_get_kernel();
	bj_core_nn_t nn = ker->get_core_nn();
	if(! ker->did_work && ! dbg_all_idle_prt[nn]){
		bj_set_off_chip_var(dbg_all_idle_prt[nn], true);
	}
	if(ker->did_work && dbg_all_idle_prt[nn]){
		bj_set_off_chip_var(dbg_all_idle_prt[nn], false);
	}
	philo_core* phl = dbg_all_philo[nn];

	phl->to_host_work_sz = ker->to_host_work.calc_size();
	phl->in_work_sz = ker->in_work.calc_size();
	phl->local_work_sz = ker->local_work.calc_size();
	phl->out_work_sz = ker->out_work.calc_size();
	phl->sent_work_sz = ker->sent_work.calc_size();
	phl->cls_available_actor_sz = ker->cls_available_actor.calc_size();
	phl->cls_available_missive_sz = ker->cls_available_missive.calc_size();
	phl->cls_available_agent_ref_sz = ker->cls_available_agent_ref.calc_size();
	phl->cls_available_agent_grp_sz = ker->cls_available_agent_grp.calc_size();
}
#endif

void bj_cores_main() {
	kernel::init_sys();
	kernel* ker = bjk_get_kernel();
	BJ_MARK_USED(ker);

	bj_core_nn_t nn = ker->get_core_nn();

	PH_DBG_COD(
		bj_set_off_chip_var(dbg_all_idle_prt[nn], false);
		bj_set_off_chip_var(dbg_all_full[nn], false);
	)

	philo_core* core_dat = philo_core::acquire_alloc();
	if(core_dat == bj_null){
		bjk_abort(1, const_cast<char*>("CAN NOT INIT GLB CORE DATA"));
	}

	ker->user_data = core_dat;

	PH_DBG_COD(
		ker->user_func = ker_func;
		dbg_all_philo[nn] = core_dat;
	)

	glb_philo->lft_stk_id = bj_nn_to_id(left_chp_nn(nn));
	glb_philo->rgt_stk_id = bj_nn_to_id(right_chp_nn(nn));
	glb_philo->lft_stick = get_stick(glb_philo->lft_stk_id);
	glb_philo->rgt_stick = get_stick(glb_philo->rgt_stk_id);
	glb_philo->lft_phi_id = bj_nn_to_id(left_phl_nn(nn));
	glb_philo->rgt_phi_id = bj_nn_to_id(right_phl_nn(nn));
	glb_philo->lft_philo = get_philo(glb_philo->lft_phi_id);
	glb_philo->rgt_philo = get_philo(glb_philo->rgt_phi_id);

	kernel::set_handlers(3, the_handlers);

	missive::separate(bj_out_num_cores);
	agent_ref::separate(bj_out_num_cores);
	agent_grp::separate(bj_out_num_cores);

	chopstick::separate(1);
	philosopher::separate(1);

	PH_DBG("started\n");

	glb_philo->send(glb_philo, tok_eat);
	kernel::run_sys();

	PH_DBG("finished\n");
	EMU_LOG("PHILOSOPHER %d FINISHED !!\n", nn);
	bjk_slog2("PHILOSOPHERS FINISHED !!\n");	

	kernel::finish_sys();
}

