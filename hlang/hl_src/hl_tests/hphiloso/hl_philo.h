

#ifndef HL_PHILO_H
#define HL_PHILO_H

#include "hlang.hh"

class chopstick;
class philosopher;

#define MAX_BITES 10

hdeclare_token(pr_tok_eat);
hdeclare_token(pr_tok_take);
hdeclare_token(pr_tok_taken);
hdeclare_token(pr_tok_not_taken);
hdeclare_token(pr_tok_drop);
hdeclare_token(pr_tok_droped);
hdeclare_token(pr_tok_not_droped);
hdeclare_token(pr_tok_yes_full);

#define hl_philo_tok(nam) hlong(nam)

class chopstick : public hcell {
public:
	hcell_class(chopstick);
	
	hreference(hcell, owner);
	hreference(hcell, last_src);

	hl_philo_tok(last_sent);
	hl_philo_tok(last_recv);

	chopstick(){
		init_chopstick();
	}

	~chopstick(){}

	void init_chopstick(){
		/*
		handler_idx = idx_chopstick;
		owner = mc_null;

		last_src = mc_null;
		last_sent = tok_invalid;
		last_recv = tok_invalid;
		*/
	}

	hnucleus(chopstick_nucl);
};

class philosopher : public hcell {
public:
	hcell_class(philosopher);

	hreference(chopstick, left);
	hreference(chopstick, right);

	hint(num_bites);
	hbool(lft_ph_full);
	hbool(rgt_ph_full);

	hreference(chopstick, lft_stick);
	hreference(chopstick, rgt_stick);

	hreference(philosopher, lft_philo);
	hreference(philosopher, rgt_philo);

	hl_philo_tok(last_sent);
	hl_philo_tok(last_sent_lft);
	hl_philo_tok(last_sent_rgt);
	hl_philo_tok(last_recv);
	hl_philo_tok(last_recv_lft);
	hl_philo_tok(last_recv_rgt);
	
	philosopher(){
		init_philosopher();
	}

	~philosopher(){}

	void init_philosopher(){
		/*
		handler_idx = idx_philosopher;

		left = mc_null;
		right = mc_null;

		num_bites = 0;
		lft_ph_full = false;
		rgt_ph_full = false;

		lft_stick = mc_null;
		rgt_stick = mc_null;
		lft_philo = mc_null;
		rgt_philo = mc_null;

		last_sent = tok_invalid;
		last_sent_lft = tok_invalid;
		last_sent_rgt = tok_invalid;
		last_recv = tok_invalid;
		last_recv_lft = tok_invalid;
		last_recv_rgt = tok_invalid;
		*/
	}

	hnucleus(philosopher_nucl);

	hmethod(send_full);
	hmethod(call_exit);
	
	/*
	void send(cell* dst, philo_tok_t tok);

	bool can_exit(){
		return ((left == mc_null) && (right == mc_null) && (num_bites == MAX_BITES) && rgt_ph_full && lft_ph_full);
	}
	*/
};


void hl_philo_main(int argc, char *argv[]);

#endif		// HL_PHILO_H

