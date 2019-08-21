

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/signalfd.h>
#include <unistd.h>

#include "hgen_net.h"

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)


#define SIG_TEST_1 SIGRTMIN+1 
		
#define NUM_CHILD 10

struct sig_dat_t {
	long vv1 = 0;
	long vv2 = 0;
};

struct thd_data {
	pthread_t tid;
	pthread_attr_t attr;
	long idx = 0;
	bool inited = false;
	bool counted = false;
	sig_dat_t msg;
};

sig_dat_t comm_dat;

void*
thd_func(void* pm){
	thd_data* dat = (thd_data*)pm;
	sigset_t newmask, oldmask;
	sigemptyset(&newmask);
	//sigaddset(&newmask, SIGINT);
	sigaddset(&newmask, SIG_TEST_1);
	
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) == -1){
		handle_error("sigprocmask");
	}

	int sfd;
	struct signalfd_siginfo fdsi;
	ssize_t ss;
	
	sfd = signalfd(-1, &newmask, 0);
	if(sfd == -1){
		handle_error("signalfd");
	}
	
	long thd_idx = dat->idx;

	dat->inited = true;
	fprintf(stdout, "%ld INITED \n", thd_idx);
	
	for(;;){
		ss = read(sfd, &fdsi, sizeof(struct signalfd_siginfo));
		if(ss != sizeof(struct signalfd_siginfo)){
			handle_error("read");
		}

		if(fdsi.ssi_signo == (uint32_t)SIG_TEST_1) {
			//fprintf(stdout, "%ld got SIG_TEST_1\n", thd_idx);
			sig_dat_t* ptr_val = (sig_dat_t*)(fdsi.ssi_ptr);
			
			long rv1 = ptr_val->vv1 - 100;
			long rv2 = ptr_val->vv2 - 300;
			if(rv1 != thd_idx){
				fprintf(stdout, "%ld ERROR_1 !\n", thd_idx);
				exit(0);
			}
			if(rv2 != thd_idx){
				fprintf(stdout, "%ld ERROR_2 !\n", thd_idx);
				exit(0);
			}
			
			fprintf(stdout, "%ld {%ld %ld} \n", thd_idx, ptr_val->vv1 - 100, ptr_val->vv2 - 300);
			
			pthread_cancel(dat->tid);
			//exit(EXIT_SUCCESS);
		} else {
			fprintf(stdout, "%ld read unexpected signal\n", thd_idx);
		}
	}
}

int
test_pthread_simu(int argc, char *argv[]){

	thd_data all_dat[NUM_CHILD];

	for(long aa = 0; aa < NUM_CHILD; aa++){
		thd_data* pt_dat = &(all_dat[aa]);
		pthread_t* pt_tid = &(pt_dat->tid);
		pthread_attr_t* pt_att = &(pt_dat->attr);
		
		pt_dat->idx = aa;
		
		pthread_attr_init(pt_att);
		pthread_create(pt_tid, pt_att, thd_func, pt_dat);
	}
	
	long num_inited = 0;
	long fst_idx = 0;
	long lst_idx = NUM_CHILD;
	while(num_inited < NUM_CHILD){
		long fst_not_counted = -1;
		long lst_not_counted = fst_idx;
		for(long aa = fst_idx; aa < lst_idx; aa++){
			thd_data& tdat = all_dat[aa];
			if(tdat.inited && ! tdat.counted){
				tdat.counted = true;
				num_inited++;
			}
			if(! tdat.counted){
				if(fst_not_counted == -1){
					fst_not_counted = aa;
				}
				lst_not_counted = aa;
			}
		}
		if(fst_not_counted != -1){
			fst_idx = fst_not_counted;
		}
		lst_idx = lst_not_counted + 1;
		
		pthread_yield();
	}

	for(long aa = 0; aa < NUM_CHILD; aa++){
		thd_data* pt_dat = &(all_dat[aa]);
		sig_dat_t* pt_msg = &(pt_dat->msg);
		pt_msg->vv1 = 100 + aa;
		pt_msg->vv2 = 300 + aa;
		
		union sigval sval; 
		sval.sival_ptr = pt_msg;
		pthread_sigqueue(pt_dat->tid, SIG_TEST_1, sval);
	}
	
	for(long aa = 0; aa < NUM_CHILD; aa++){
		thd_data* pt_dat = &(all_dat[aa]);
		pthread_join(pt_dat->tid, NULL);
	}
	
	return 0;
}

int
main(int argc, char *argv[]){
	int resp = 0;
	//resp = test_m_to_n(argc, argv);
	//resp = test_bases(argc, argv);
	//resp = test_log(argc, argv);
	//resp = test_mod(argc, argv);
	//resp = test_num_io(argc, argv);
	//resp = test_get_target(argc, argv);
	resp = test_pthread_simu(argc, argv);
	
	printf("ENDING_TESTS______________________\n");
	return resp;
}

