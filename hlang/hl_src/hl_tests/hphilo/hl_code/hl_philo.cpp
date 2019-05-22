

#include <stdio.h>

#include "hlang.hh"
#include "hl_philo.h"

hdefine_const(MAX_BITES, 10);

hdefine_token(pr_tok_invalid);
hdefine_token(pr_tok_eat);
hdefine_token(pr_tok_take);
hdefine_token(pr_tok_taken);
hdefine_token(pr_tok_not_taken);
hdefine_token(pr_tok_drop);
hdefine_token(pr_tok_droped);
hdefine_token(pr_tok_not_droped);
hdefine_token(pr_tok_yes_full);

hcell_class_def(chopstick);
hcell_class_def(philosopher);

hmethod_def(chopstick, init_chopstick, (
	owner = hlit(mc_null),

	last_src = hlit(mc_null),
	last_sent = pr_tok_invalid,
	last_recv = pr_tok_invalid
));

hnucleus_def(chopstick, chopstick_nucl, (
	hswitch(hmsg_tok_as(long)) >> (
		hcase(pr_tok_take) >> (
			//PTD_CK(owner != msv_src);
			hif(owner == hlit(mc_null)) >> (
				owner = hmsg_src_as(philosopher),
				last_sent = pr_tok_taken,
				hsend(hmsg_src, pr_tok_taken, hlit(0))
			),
			helse >> (
				//PTD_CK(owner != mc_null);
				last_sent = pr_tok_not_taken,
				hsend(hmsg_src, pr_tok_not_taken, hlit(0))
			)
		),
		hcase(pr_tok_drop) >> (
			//PTD_CK(owner == msv_src);
			owner = hlit(mc_null),
			last_sent = pr_tok_droped,
			hsend(hmsg_src, pr_tok_droped, hlit(0))
		)
		//default:
		//	mck_abort(1, mc_cstr("BAD_STICK_TOK"));
	),
	hreturn
));



hmethod_def(philosopher, init_philosopher, (
	left = hlit(mc_null),
	right = hlit(mc_null),

	num_bites = hlit(0),
	lft_ph_full = hlit(false),
	rgt_ph_full = hlit(false),

	lft_stick = hlit(mc_null),
	rgt_stick = hlit(mc_null),

	lft_philo = hlit(mc_null),
	rgt_philo = hlit(mc_null),

	last_sent = pr_tok_invalid,
	last_sent_lft = pr_tok_invalid,
	last_sent_rgt = pr_tok_invalid,
	last_recv = pr_tok_invalid,
	last_recv_lft = pr_tok_invalid,
	last_recv_rgt = pr_tok_invalid
));

#define philosopher_send(dst, tok) \
	last_sent = tok, \
	hif(hcast(chopstick*, dst) == lft_stick) >> (last_sent_lft = tok), \
	hif(hcast(chopstick*, dst) == rgt_stick) >> (last_sent_rgt = tok), \
	hsend(dst, tok, hlit(0)) \
	
	
	
#define philosopher_can_exit() \
	(	(left == hlit(mc_null)) && (right == hlit(mc_null)) && \
		(num_bites == MAX_BITES) && rgt_ph_full && lft_ph_full) \
		
		
	

hmethod_def(philosopher, call_exit, (
	hreturn
));

	
hnucleus_def(philosopher, philosopher_nucl, (
	last_recv = hmsg_tok,

	hif(hmsg_src_as(chopstick) == lft_stick) >> ( last_recv_lft = hmsg_tok ),
	hif(hmsg_src_as(chopstick) == rgt_stick) >> ( last_recv_rgt = hmsg_tok ),

	hswitch(hmsg_tok_as(long)) >> (
		hcase(pr_tok_eat) >> (
			//PTD_CK(msv_src == hthis);
			//PTD_CK(left == mc_null);
			//PTD_CK(right == mc_null);
			//PTD_CK(num_bites < MAX_BITES);
			philosopher_send(lft_stick, pr_tok_take)
		),
		hcase(pr_tok_taken) >> (
			//PTD_CK((msv_src == lft_stick) || (msv_src == rgt_stick));
			hif(hmsg_src == lft_stick) >> (
				//PTD_CK(left == mc_null);
				//PTD_CK(right == mc_null);
				left = lft_stick,
				philosopher_send(rgt_stick, pr_tok_take)
			),
			hif(hmsg_src == rgt_stick) >> (
				//PTD_CK(left == lft_stick);
				//PTD_CK(right == mc_null);
				right = rgt_stick,

				//PTD_CK(left != mc_null);
				//PTD_CK(right != mc_null);
				//PTD_CK(num_bites < MAX_BITES);
				num_bites++,
				//PH_DBG("#BITES %d \n", num_bites);
				//PTD_LOG("#BITES %d \n", num_bites);

				philosopher_send(lft_stick, pr_tok_drop),
				philosopher_send(rgt_stick, pr_tok_drop)
			)
		),
		hcase(pr_tok_not_taken) >> (
			//PTD_CK((msv_src == lft_stick) || (msv_src == rgt_stick));
			hif(hmsg_src == lft_stick) >> (
				//PTD_CK(left == mc_null);
				//PTD_CK(right == mc_null);
				philosopher_send(hthis, pr_tok_eat)
			),
			hif(hmsg_src == rgt_stick) >> (
				//PTD_CK(left == lft_stick);
				//PTD_CK(right == mc_null);
				philosopher_send(lft_stick, pr_tok_drop)
			)
		),
		hcase(pr_tok_droped) >> (
			//PTD_CK((msv_src == lft_stick) || (msv_src == rgt_stick));
			hif(hmsg_src_as(chopstick) == lft_stick) >> (
				//PTD_CK(left == lft_stick);
				left = hlit(mc_null)
			),
			hif(hmsg_src_as(chopstick) == rgt_stick) >> (
				//PTD_CK(right == rgt_stick);
				right = hlit(mc_null)
			),
			hif((left == hlit(mc_null)) && (right == hlit(mc_null))) >> (
				hif(num_bites == MAX_BITES) >> (
					//PH_DBG("I AM FULL \n");
					//PTD_LOG("I AM FULL \n");

					//PH_DBG_COD(mc_loop_set_var(dbg_all_full[nn], true);)

					philosopher_send(lft_philo, pr_tok_yes_full),
					philosopher_send(rgt_philo, pr_tok_yes_full),

					hif(philosopher_can_exit()) >> (
						call_exit()
					)
				),
				helse  >> (
					philosopher_send(hthis, pr_tok_eat)
				)
			)
		),
		hcase(pr_tok_yes_full) >> (
			//PTD_CK((msv_src == lft_philo) || (msv_src == rgt_philo));
			hif(hmsg_src_as(philosopher) == lft_philo) >> ( 
				//PTD_CK(! lft_ph_full);
				lft_ph_full = hlit(true)
			),
			hif(hmsg_src_as(philosopher) == rgt_philo) >> ( 
				//PTD_CK(! rgt_ph_full);
				rgt_ph_full = hlit(true)
			),
			hif(philosopher_can_exit()) >> (
				call_exit()
			)
		)
		//default
		//	mck_abort(1, mc_cstr("BAD_PHILO_TOK"));
	), 

	hreturn
));

int main(int argc, char *argv[]){
	int rr = 0;
	printf("HGENERATION_STARTING: hl_philo ==================================== \n");
	
	fprintf(stdout, "######################################################\n");

	HLANG_SYS().init_sys();
	
	fprintf(stdout, "RUNNING PATH= %s \n", path_get_running_path().c_str());

	HLANG_SYS().generate_cpp_code();

	printf("HGENERATION_FINISHED: hl_philo ==================================== \n");
	return rr;
}

	