

#include <stdio.h>

#include "hlang.hh"
#include "hl_philo.h"

hdefine_const(MAX_BITES, 0x10);

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
	owner = hnull,

	last_src = hnull,
	last_sent = pr_tok_invalid,
	last_recv = pr_tok_invalid
));

hnucleus_def(chopstick, chopstick_nucl, (
	hswitch(hmsg_tok_as(long)) >> (
		hcase(pr_tok_take) >> (
			HCK("owner != hg_msg_src"),
			hif(owner == hnull) >> (
				owner = hmsg_src_as(philosopher),
				last_sent = pr_tok_taken,
				hsend(hmsg_src, pr_tok_taken, hlit(0))
			),
			helse >> (
				HCK("owner != hg_null"),
				last_sent = pr_tok_not_taken,
				hsend(hmsg_src, pr_tok_not_taken, hlit(0))
			)
		),
		hcase(pr_tok_drop) >> (
			HCK("owner == hg_msg_src"),
			owner = hnull,
			last_sent = pr_tok_droped,
			hsend(hmsg_src, pr_tok_droped, hlit(0))
		)
		//default:
		//	mck_abort(1, mc_cstr("BAD_STICK_TOK"));
	),
	hreturn
));



hmethod_def(philosopher, init_philosopher, (
	left = hnull,
	right = hnull,

	num_bites = hlit(0),
	lft_ph_full = hlit(false),
	rgt_ph_full = hlit(false),

	lft_stick = hnull,
	rgt_stick = hnull,

	lft_philo = hnull,
	rgt_philo = hnull,

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
	(	(left == hnull) && (right == hnull) && \
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
			HCK("hg_msg_src == this"),
			HCK("left == hg_null"),
			HCK("right == hg_null"),
			HCK("num_bites < MAX_BITES"),
			philosopher_send(lft_stick, pr_tok_take)
		),
		hcase(pr_tok_taken) >> (
			HCK("(hg_msg_src == lft_stick) || (hg_msg_src == rgt_stick)"),
			hif(hmsg_src == lft_stick) >> (
				HCK("left == hg_null"),
				HCK("right == hg_null"),
				left = lft_stick,
				philosopher_send(rgt_stick, pr_tok_take)
			),
			hif(hmsg_src == rgt_stick) >> (
				HCK("left == lft_stick"),
				HCK("right == hg_null"),
				right = rgt_stick,

				HCK("left != hg_null"),
				HCK("right != hg_null"),
				HCK("num_bites < MAX_BITES"),
				//num_bites = (num_bites << 1),
				num_bites++,
				HPRT(R"("#BITES %d \n", num_bites)"),
				//HLOG(R"("#BITES %d \n", num_bites)"),

				philosopher_send(lft_stick, pr_tok_drop),
				philosopher_send(rgt_stick, pr_tok_drop)
			)
		),
		hcase(pr_tok_not_taken) >> (
			HCK("(hg_msg_src == lft_stick) || (hg_msg_src == rgt_stick)"),
			hif(hmsg_src == lft_stick) >> (
				HCK("left == hg_null"),
				HCK("right == hg_null"),
				philosopher_send(hthis, pr_tok_eat)
			),
			hif(hmsg_src == rgt_stick) >> (
				HCK("left == lft_stick"),
				HCK("right == hg_null"),
				philosopher_send(lft_stick, pr_tok_drop)
			)
		),
		hcase(pr_tok_droped) >> (
			HCK("(hg_msg_src == lft_stick) || (hg_msg_src == rgt_stick)"),
			hif(hmsg_src_as(chopstick) == lft_stick) >> (
				HCK("left == lft_stick"),
				left = hnull
			),
			hif(hmsg_src_as(chopstick) == rgt_stick) >> (
				HCK_PRT(R"(right == rgt_stick, "right = %p", (void*)right)"),
				right = hnull
			),
			hif((left == hnull) && (right == hnull)) >> (
				hif(num_bites == MAX_BITES) >> (
					HPRT(R"("I AM FULL \n")"),
					HLOG(R"("I AM FULL \n")"),
	
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
			HCK("(hg_msg_src == lft_philo) || (hg_msg_src == rgt_philo)"),
			hif(hmsg_src_as(philosopher) == lft_philo) >> ( 
				HCK("! lft_ph_full"),
				lft_ph_full = hlit(true)
			),
			hif(hmsg_src_as(philosopher) == rgt_philo) >> ( 
				HCK("! rgt_ph_full"),
				rgt_ph_full = hlit(true)
			),
			hif(philosopher_can_exit()) >> (
				call_exit()
			)
		)
		//default
		//	mck_abort(1, mc_cstr("BAD_PHILO_TOK")),
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

	