

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


		
#define GH_SG_REQ SIGRTMIN+1
#define GH_SG_ACK SIGRTMIN+2
#define GH_SG_END SIGRTMIN+3

#define SIG_TEST_1 SIGRTMIN+4
#define SIG_END_TEST SIGRTMIN+5

#define NUM_PTH_TEST 3
		
#define NUM_CHILD 1000

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
	bool end_it = false;
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
	sigaddset(&newmask, SIG_END_TEST);
	
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
	//fprintf(stdout, "%ld INITED \n", thd_idx);
	
	long num_tst = 0;
	
	for(;;){
		ss = read(sfd, &fdsi, sizeof(struct signalfd_siginfo));
		if(ss != sizeof(struct signalfd_siginfo)){
			handle_error("read");
		}

		int32_t sg_id = (int32_t)fdsi.ssi_signo;
		if(sg_id == SIG_TEST_1) {
			num_tst++;
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
			/*if(num_tst == 2){
				sleep(1);
			}
			pthread_yield();*/
			
			//fprintf(stdout, "%ld {%ld %ld} \n", thd_idx, rv1, rv2);
			
		} else if(sg_id == SIG_END_TEST) {
			if(num_tst != NUM_PTH_TEST){
				fprintf(stdout, "%ld ERROR_3 !\n", thd_idx);
				exit(0);
			}
			
			fprintf(stdout, "%ld ENDING %ld \n", thd_idx, num_tst);
			pthread_cancel(dat->tid);
		} else {
			fprintf(stdout, "%ld read unexpected signal\n", thd_idx);
		}
	}
	return gh_null;
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
	fprintf(stdout, "ALL_INITED \n");

	//for(long bb = 0; bb < NUM_PTH_TEST; bb++){
		for(long aa = 0; aa < NUM_CHILD; aa++){
			thd_data* pt_dat = &(all_dat[aa]);
			sig_dat_t* pt_msg = &(pt_dat->msg);
			pt_msg->vv1 = 100 + aa;
			pt_msg->vv2 = 300 + aa;
			
			union sigval sval; 
			sval.sival_ptr = pt_msg;
			for(long cc = 0; cc < NUM_PTH_TEST; cc++){
				pthread_sigqueue(pt_dat->tid, SIG_TEST_1, sval);
			}
			fprintf(stdout, "%ld all_sent \n", aa);
		}
	//}

	for(long aa = 0; aa < NUM_CHILD; aa++){
		thd_data* pt_dat = &(all_dat[aa]);
		
		union sigval sval; 
		sval.sival_ptr = NULL;
		pthread_sigqueue(pt_dat->tid, SIG_END_TEST, sval);
	}
	
	for(long aa = 0; aa < NUM_CHILD; aa++){
		thd_data* pt_dat = &(all_dat[aa]);
		pthread_join(pt_dat->tid, NULL);
	}
	
	return 0;
}

int
test_get_target(int argc, char *argv[]){
	if(argc < 4){
		printf("%s <base> <#in> <#out>\n", argv[0]);
		return 1;
	}
	
	long bb = atol(argv[1]);
	long nin = atol(argv[2]);
	long nout = atol(argv[3]);
	fprintf(stdout, "test_get_target base=%ld #in=%ld #out=%ld\n", bb, nin, nout);

	haddr_frame	pnt_frm;
	pnt_frm.pow_base = bb;
	
	htarget_box* bx = new htarget_box(pnt_frm);
	
	gh_dbg_calc_idx_and_sz(nin, nout, bx->get_frame());
	bx->get_frame().print_frame(stdout);
	
	bx->init_target_box(nin, nout);

	fprintf(stdout, "===========\n");
	
	GH_GLOBALS.CK_LINK_MODE = gh_valid_self_ck_mod;

	bx->calc_all_1to2_raddr(gh_null);
	bx->print_box(stdout, gh_full_pt_prt);
	
	/*if(GH_GLOBALS.watch_bx != gh_null){
		fprintf(stdout, "\nBEFORE_CALC_ADDR---------------------------------\n");
		GH_GLOBALS.watch_bx->print_box(stdout, gh_full_pt_prt);
		
		GH_GLOBALS.watch_bx->calc_all_1to2_raddr(GH_GLOBALS.ref_frm);
		
		fprintf(stdout, "\nAFTER_CALC_ADDR---------------------------------\n");
		GH_GLOBALS.watch_bx->print_box(stdout, gh_full_pt_prt);
	}*/
	
	delete bx;
		
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
	//resp = test_pthread_simu(argc, argv);
	resp = test_hlognet(argc, argv);
	
	printf("ENDING_TESTS______________________\n");
	return resp;
}

void*
run_node_simu(void* pm){
	hnode* the_nd = (hnode*)pm;
	
	GH_CK(the_nd->simu_data != gh_null);
	thd_data* dat = (thd_data*)(the_nd->simu_data);
	
	dat->inited = true;
	
	if(the_nd->is_1to2()){
		hnode_1to2* th_nd = (hnode_1to2*)the_nd;
		th_nd->run_1to2_simu();
	} else 
	if(the_nd->is_2to1()){
		hnode_2to1* th_nd = (hnode_2to1*)the_nd;
		th_nd->run_2to1_simu();
	} else {
		GH_CK(the_nd->is_1to1());
		hnode_1to1* th_nd = (hnode_1to1*)the_nd;
		th_nd->run_1to1_simu();
	}
	
	return gh_null;
}

void
hnode_1to1::run_1to1_simu(){
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);
	
	hnode_1to1* nod = this;
	hmessage* in_msg0 = in0->get_message_of(nod);
	GH_CK(in_msg0 != gh_null);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		if(ireq(*in0) && (! ack0)){
			bool rdy_out0 = ((! req0) && (! oack(*out0)));
			if(rdy_out0){
				in_msg0->copy_mg_to(msg0);
				req0 = true;
				ack0 = true;
			} 
		} 
		
		if((! ireq(*in0)) && ack0){
			ack0 = false;
		}
		if(req0 && oack(*out0)){
			req0 = false;
		}
		
		pthread_yield();
	}
}

void
hnode_1to2::run_1to2_simu(){
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);
	//long thd_idx = dat->idx;
	
	hnode_1to2* nod = this;
	hmessage* in_msg0 = in0->get_message_of(nod);
	GH_CK(in_msg0 != gh_null);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		if(ireq(*in0) && (! ack0)){
			gh_addr_t dst_addr = in_msg0->mg_dst;
			bool in_rng0 = msg0.in_range(dst_addr);
			bool in_rng1 = msg1.in_range(dst_addr);
			GH_CK(in_rng0 != in_rng1);
			
			if(in_rng0){
				bool rdy_out0 = ((! req0) && (! oack(*out0)));
				if(rdy_out0){
					in_msg0->copy_mg_to(msg0);
					req0 = true;
					ack0 = true;
				} 
			} 
			
			if(in_rng1){
				bool rdy_out1 = ((! req1) && (! oack(*out1)));
				if(rdy_out1){
					in_msg0->copy_mg_to(msg1);
					req1 = true;
					ack0 = true;
				} 
			} 
		} 
		
		if((! ireq(*in0)) && ack0){
			ack0 = false;
		}
		if(req0 && oack(*out0)){
			req0 = false;
		}
		if(req1 && oack(*out1)){
			req1 = false;
		}
		
		pthread_yield();
	}
}

void
hnode_2to1::run_2to1_simu(){
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);
	//long thd_idx = dat->idx;
	
	hnode_2to1* nod = this;
	hmessage* in_msg0 = in0->get_message_of(nod);
	hmessage* in_msg1 = in1->get_message_of(nod);
	GH_CK(in_msg0 != gh_null);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		bool rdy_out0 = ((! req0) && (! oack(*out0)));
		if(rdy_out0){
			bool in0_rq = (ireq(*in0) && (! ack0));
			bool in1_rq = (ireq(*in1) && (! ack1));
			if(in0_rq && in1_rq){
				if(choose0){
					choose0 = false;
					in_msg0->copy_mg_to(msg0);
					req0 = true;
					ack0 = true;
				} else {
					choose0 = true;
					in_msg1->copy_mg_to(msg0);
					req0 = true;
					ack1 = true;
				}
			}
			if(in0_rq && ! in1_rq){
				in_msg0->copy_mg_to(msg0);
				req0 = true;
				ack0 = true;
			} 
			if(! in0_rq && in1_rq){
				in_msg1->copy_mg_to(msg0);
				req0 = true;
				ack1 = true;
			} 
		}
		
		if((! ireq(*in0)) && ack0){
			ack0 = false;
		}
		if((! ireq(*in1)) && ack1){
			ack1 = false;
		}
		if(req0 && oack(*out0)){
			req0 = false;
		}
		
		pthread_yield();
	}
}

/* 
SOURCE
	begin
		if((! r_req) && (! i_ack)) begin
			if(r_addr == MAX_ADDR) begin
				r_addr <= MIN_ADDR;
				r_dat <= r_dat + 1;
			end
			else begin
				r_addr <= r_addr + 1;
			end
			r_req <= `ON;
		end 
		else
		if(r_req && i_ack) begin
			r_req <= `OFF;
		end
	end
	
DEST
	begin
		if(i_addr == LOCAL_ADDR) begin
			if(i_req && (! r_ack)) begin
				if((i_dat > 0) && ((r_dat + 1) != i_dat)) begin
					r_err <= `ON;
				end
				r_dat <= i_dat;
				r_ack <= `ON;
			end
			else
			if((! i_req) && r_ack) begin
				r_ack <= `OFF;
			end
		end
	end

*/

void
hnode_target::run_source_simu(){
	//hnode_target* nod = this;
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		bool rdy_out0 = ((! req0) && (! oack(*out0)));
		if(rdy_out0){
			hnode_target* tg = choose_target();
			
			msg0.mg_val++;
			msg0.mg_src = addr;
			msg0.mg_dst = tg->addr;
			
			req0 = true;
		} 
		
		if(req0 && oack(*out0)){
			req0 = false;
		}
		
		pthread_yield();
	}
}

void
hnode_target::run_sink_simu(){
	//hnode_target* nod = this;
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		if(ireq(*in0) && (! ack0)){
			ack0 = true;
		} 
		
		if((! ireq(*in0)) && ack0){
			ack0 = false;
		}
		
		pthread_yield();
	}
}

hnode_target* 
hnode_target::choose_target(){
	vector<hnode_target*>& all_tg = GH_GLOBALS.all_sink_simu;
	long sz = (long)all_tg.size();
	GH_CK(sz > 0);
	hnode_target* tg = all_tg[sz - 1];
	GH_CK(tg != gh_null);
	GH_CK(tg->kk != gh_src_tgt_kind);
	
	return tg;
}

thd_data*
hnode::create_thread_simu(){
	thd_data* pt_dat = new thd_data;
	GH_GLOBALS.all_thread_data_simu.push_back(pt_dat);
	
	simu_data = pt_dat;

	pthread_t* pt_tid = &(pt_dat->tid);
	pthread_attr_t* pt_att = &(pt_dat->attr);
	
	pthread_attr_init(pt_att);
	pthread_create(pt_tid, pt_att, run_node_simu, pt_dat);
	
	return pt_dat;
}

void
hlognet_box::wait_all_inited_simu(){
	vector<thd_data*>& all_dat = GH_GLOBALS.all_thread_data_simu;
	long tot_child = GH_GLOBALS.all_thread_data_simu.size();
	long num_inited = 0;
	long fst_idx = 0;
	long lst_idx = tot_child;
	while(num_inited < tot_child){
		long fst_not_counted = -1;
		long lst_not_counted = fst_idx;
		for(long aa = fst_idx; aa < lst_idx; aa++){
			GH_CK(all_dat[aa] != gh_null);
			thd_data& tdat = *(all_dat[aa]);
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
	fprintf(stdout, "ALL_NODE_THREADS_INITED \n");
}

void
hlognet_box::init_hlognet_simu(){
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		hnode* nod = all_nodes[ii];
		GH_CK(nod != gh_null);
		
		thd_data* pt_dat = nod->create_thread_simu();
		pt_dat->idx = ii;
	}
	
	long tot_tg = (long)all_targets.size();
	for(long ii = 0; ii < (tot_tg - 1); ii++){
		hnode* tgt = all_targets[ii];
		GH_CK(tgt != gh_null);
	}
	
	wait_all_inited_simu();
}

int
test_hlognet(int argc, char *argv[]){
	if(argc < 3){
		printf("%s <base> <#tgt>\n", argv[0]);
		return 1;
	}
	long bb = atol(argv[1]);
	long ntg = atol(argv[2]);

	fprintf(stdout, "test_hlognet base=%ld #ntg=%ld \n", bb, ntg);
	
	haddr_frame	pnt_frm;
	pnt_frm.pow_base = bb;
	
	hlognet_box* bx = new hlognet_box(pnt_frm);
	bx->get_frame().kind = gh_top_lognet_frm;
	bx->init_length(ntg);
	bx->get_frame().print_frame(stdout);
	fprintf(stdout, "height=%ld \n", bx->height);
	fprintf(stdout, "===========\n");
	
	bx->init_lognet_box(ntg);
	
	GH_GLOBALS.CK_LINK_MODE = gh_valid_self_ck_mod;

	bx->calc_all_1to2_raddr(gh_null);
	bx->print_box(stdout, gh_full_pt_prt);
	
	//init_hlognet_simu();

	delete bx;
		
	return 0;
}

