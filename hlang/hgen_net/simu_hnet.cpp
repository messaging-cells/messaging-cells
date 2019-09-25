

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/signalfd.h>
#include <unistd.h>

#include "hgen_net.h"

void gh_dbg_init_sources_and_sinks(vector<hnode_target*>& all_tgt);

struct thd_data {
	pthread_t tid;
	pthread_attr_t attr;
	long idx = 0;
	bool inited = false;
	bool counted = false;
	bool sent_all = false;
	bool end_it = false;
};

int
test_m_to_n(int argc, char *argv[]){
	if(argc < 3){
		printf("%s <num_in> <num_out>\n", argv[0]);
		return 1;
	}
	
	long mm = atol(argv[1]);
	long nn = atol(argv[2]);

	haddr_frame pnt_frm;
	pnt_frm.pow_base = 2;
	
	hnode_box* bx = gh_get_binnet_m_to_n(pnt_frm, mm, nn, gh_call_14);
	GH_MARK_USED(bx);
	
	bx->print_box(stdout, gh_full_prt);
	
	return 0;
}

int
test_bases(int argc, char *argv[]){
	if(argc < 2){
		printf("%s (0 | 1)\n", argv[0]);
		return 1;
	}
	
	long mm = atol(argv[1]);

	haddr_frame pnt_frm;
	hroute_box* bx = new hroute_box(pnt_frm);
	GH_MARK_USED(bx);
	switch(mm){
		case 0: 
			bx->init_as_2to3_route_box();
			break;
		case 1: 
			bx->init_as_3to2_route_box();
			break;
		default: 
			bx->init_as_2to2_route_box();
			break;
	}
	
	bx->print_box(stdout, gh_full_prt);
	delete bx;
	
	return 0;
}

int
test_log(int argc, char *argv[]){
	if(argc < 3){
		printf("%s <base> <num>\n", argv[0]);
		return 1;
	}
	
	long bb = atol(argv[1]);
	long nn = atol(argv[2]);
	
	double lbb = log2(bb);
	long lg = (long)(log2(nn)/lbb);
	fprintf(stdout, "LOG(%ld, %ld) = %ld\n", bb, nn, lg);
	return 0;
	
}

int
test_mod(int argc, char *argv[]){
	if(argc < 3){
		printf("%s <n1> <n2>\n", argv[0]);
		return 1;
	}
	
	long n1 = atol(argv[1]);
	long n2 = atol(argv[2]);
	long n3 = (n1 % n2);
	
	fprintf(stdout, "%ld mod %ld = %ld\n", n1, n2, n3);
	return 0;
}

int
test_num_io(int argc, char *argv[]){
	if(argc < 4){
		printf("%s <base> <length> <idx>\n", argv[0]);
		return 1;
	}
	
	long bb = atol(argv[1]);
	long ll = atol(argv[2]);
	long idx = atol(argv[3]);
	long nin = 0;
	long nout = 0;
	
	gh_calc_num_io(bb, ll, idx, nin, nout);
	fprintf(stdout, "base=%ld length=%ld idx=%ld num_in=%ld num_out=%ld\n", bb, ll, idx, nin, nout);
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
	resp = test_hlognet(argc, argv);
	
	printf("ENDING_TESTS______________________\n");
	return resp;
}

void*
run_node_simu(void* pm){
	hnode* the_nd = (hnode*)pm;
	
	GH_CK(the_nd->simu_data != gh_null);
	thd_data* dat = (thd_data*)(the_nd->simu_data);
	
	GH_CK(! dat->inited);
	dat->inited = true;
	
	while(! GH_GLOBALS.all_thread_inited_simu){
		pthread_yield();
	}
	
	if(the_nd->is_1to2()){
		hnode_1to2* th_nd = (hnode_1to2*)the_nd;
		if(th_nd->get_flag(gh_is_trichotomy)){
			th_nd->run_trichotomy_simu();
		} else
		if(th_nd->get_flag(gh_is_dichotomy)){
			th_nd->run_dichotomy_simu();
		} else
		if(th_nd->one_range != gh_null) {
			th_nd->run_one_range_simu();
		} else {
			th_nd->run_1to2_simu();
		}
	} else 
	if(the_nd->is_2to1()){
		hnode_2to1* th_nd = (hnode_2to1*)the_nd;
		th_nd->run_2to1_simu();
	} else {
		GH_CK(the_nd->is_1to1());
		hnode_1to1* th_nd = (hnode_1to1*)the_nd;
		gh_1t1_kind_t k1t1 = th_nd->get_1t1_kind();
		GH_CK(k1t1 == gh_target_1t1);
		if(k1t1 == gh_target_1t1){
			hnode_target* tg = (hnode_target*)the_nd;
			tg->run_target_simu();
		} else {
			th_nd->run_1to1_simu();
		}
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
				in_msg0->copy_mg_to(msg0, in0, nod);
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
			GH_CK_PRT((in_rng0 != in_rng1), "%s (%p -> %p) %ld %d==(%ld,%ld) %d==(%ld,%ld) [%ld -> %ld val=%ld]", 
						gh_dbg_get_rou_kind_str(rou_kind), in0, nod, dst_addr, 
						in_rng0, msg0.rng.min, msg0.rng.max, in_rng1, msg1.rng.min, msg1.rng.max,
						in_msg0->mg_src, in_msg0->mg_dst, in_msg0->mg_val
			);
			
			if(in_rng0){
				bool rdy_out0 = ((! req0) && (! oack(*out0)));
				if(rdy_out0){
					in_msg0->copy_mg_to(msg0, in0, nod);
					req0 = true;
					ack0 = true;
				} 
			} 
			
			if(in_rng1){
				bool rdy_out1 = ((! req1) && (! oack(*out1)));
				if(rdy_out1){
					in_msg0->copy_mg_to(msg1, in0, nod);
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
					in_msg0->copy_mg_to(msg0, in0, nod);
					req0 = true;
					ack0 = true;
				} else {
					choose0 = true;
					in_msg1->copy_mg_to(msg0, in1, nod);
					req0 = true;
					ack1 = true;
				}
			}
			if(in0_rq && ! in1_rq){
				in_msg0->copy_mg_to(msg0, in0, nod);
				req0 = true;
				ack0 = true;
			} 
			if(! in0_rq && in1_rq){
				in_msg1->copy_mg_to(msg0, in1, nod);
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

void
hnode::create_thread_simu(long idx){
	hnode* the_nd = this;
	thd_data* pt_dat = new thd_data;
	GH_GLOBALS.all_thread_data_simu.push_back(pt_dat);
	
	simu_data = pt_dat;
	pt_dat->idx = idx;

	pthread_t* pt_tid = &(pt_dat->tid);
	pthread_attr_t* pt_att = &(pt_dat->attr);
	
	pthread_attr_init(pt_att);
	pthread_create(pt_tid, pt_att, run_node_simu, the_nd);
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
	
	GH_GLOBALS.all_thread_inited_simu = true;
	
	fprintf(stdout, "ALL_NODE_THREADS_INITED %ld \n", tot_child);
}

void
hlognet_box::wait_all_threads_ended_simu(){

	while(true){
		long tot_src = 0;
		long tot_ok = 0;
		for(long aa = 0; aa < (long)all_targets.size(); aa++){
			hnode_target* tg = all_targets[aa];
			GH_CK(tg != gh_null);
			
			thd_data* pt_dat = (thd_data*)(tg->simu_data);
			bool is_src = tg->is_source;
			
			if(is_src){
				tot_src++;
			}
			if(is_src && pt_dat->sent_all){
				tot_ok++;
			}
			pthread_yield();
		}
		if(tot_ok == tot_src){
			break;
		}
		pthread_yield();
	}
	fprintf(stdout, "ALL_SOURCE_THREADS_FINISHED \n");
	
	long tot_msg_snt = 0;
	for(long aa = 0; aa < (long)all_targets.size(); aa++){
		hnode_target* tg = all_targets[aa];
		tot_msg_snt += tg->num_msg_snt;
	}
	
	long ck_tot_rcv = -1;
	while(true){
		long tot_msg_rcv = 0;
		for(long aa = 0; aa < (long)all_targets.size(); aa++){
			hnode_target* tg = all_targets[aa];
			tot_msg_rcv += tg->num_msg_rcv;
			pthread_yield();
		}
		if(tot_msg_rcv > ck_tot_rcv){
			fprintf(stdout, "GOT %ld of %ld \n", tot_msg_rcv, tot_msg_snt);
			ck_tot_rcv = tot_msg_rcv;
		}
		if(tot_msg_rcv == tot_msg_snt){
			break;
		}
		pthread_yield();
	}
	
	vector<thd_data*>& all_dat = GH_GLOBALS.all_thread_data_simu;
	for(long aa = 0; aa < (long)all_dat.size(); aa++){
		thd_data* pt_dat = all_dat[aa];
		if(! pt_dat->end_it){
			pt_dat->end_it = true;
			pthread_join(pt_dat->tid, NULL);
		}
	}
}

void
hlognet_box::run_hlognet_simu(){
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		hnode* nod = all_nodes[ii];
		GH_CK(nod != gh_null);
		
		nod->create_thread_simu(ii);
	}
	
	for(long ii = 0; ii < (long)all_targets.size(); ii++){
		hnode_target* tgt = all_targets[ii];
		GH_CK(tgt != gh_null);
		
		tgt->create_thread_simu(ii);
	}
	
	wait_all_inited_simu();
	wait_all_threads_ended_simu();
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
	
	gh_dbg_init_sources_and_sinks(bx->all_targets);
	
	bx->print_box(stdout, gh_full_pt_prt);
	//bx->print_box(stdout, gh_full_prt);

	fprintf(stdout, "=========== RUNNING_SIMU ===================\n");
	
	bx->run_hlognet_simu();

	delete bx;
		
	return 0;
}

void
hnode_1to2::run_one_range_simu(){
	GH_CK(one_range != gh_null);
	GH_CK((one_range == &(msg0)) || (one_range == &(msg1)));
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);
	//long thd_idx = dat->idx;

	bool is_rg0 = (one_range == &(msg0));
	bool is_rg1 = (one_range == &(msg1));
	
	hnode_1to2* nod = this;
	hmessage* in_msg0 = in0->get_message_of(nod);
	GH_CK(in_msg0 != gh_null);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		if(ireq(*in0) && (! ack0)){
			gh_addr_t dst_addr = in_msg0->mg_dst;
			bool in_rng = one_range->in_range(dst_addr);
			bool in_rng0 = ((is_rg0 && in_rng) || (! is_rg0 && ! in_rng));
			bool in_rng1 = ((is_rg1 && in_rng) || (! is_rg1 && ! in_rng));
			
			GH_CK_PRT((in_rng0 != in_rng1), "(%p) %ld %d==(%ld,%ld) %d==(%ld,%ld) ", (void*)nod,
					  dst_addr, in_rng0, msg0.rng.min, msg0.rng.max, in_rng1, msg1.rng.min, msg1.rng.max);
			
			if(in_rng0){
				bool rdy_out0 = ((! req0) && (! oack(*out0)));
				if(rdy_out0){
					in_msg0->copy_mg_to(msg0, in0, nod);
					req0 = true;
					ack0 = true;
				} 
			} 
			
			if(in_rng1){
				bool rdy_out1 = ((! req1) && (! oack(*out1)));
				if(rdy_out1){
					in_msg0->copy_mg_to(msg1, in0, nod);
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
hnode_1to2::run_trichotomy_simu(){
	GH_CK(get_flag(gh_is_trichotomy));
	GH_CK(one_range == &(msg0));
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);
	//long thd_idx = dat->idx;

	GH_CK(msg0.rng.min == msg0.rng.max);
	gh_addr_t tricho_val = msg0.rng.min;
	
	hnode_1to2* nod = this;
	hmessage* in_msg0 = in0->get_message_of(nod);
	GH_CK(in_msg0 != gh_null);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		if(ireq(*in0) && (! ack0)){
			gh_addr_t dst_addr = in_msg0->mg_dst;
			GH_CK(dst_addr != tricho_val);
			bool in_rng0 = (dst_addr > tricho_val);
			bool in_rng1 = (dst_addr < tricho_val);
			
			GH_CK_PRT((in_rng0 != in_rng1), "(%p) %ld %d==(%ld,%ld) %d==(%ld,%ld) ", (void*)nod,
					  dst_addr, in_rng0, msg0.rng.min, msg0.rng.max, in_rng1, msg1.rng.min, msg1.rng.max);
			
			if(in_rng0){
				bool rdy_out0 = ((! req0) && (! oack(*out0)));
				if(rdy_out0){
					in_msg0->copy_mg_to(msg0, in0, nod);
					req0 = true;
					ack0 = true;
				} 
			} 
			
			if(in_rng1){
				bool rdy_out1 = ((! req1) && (! oack(*out1)));
				if(rdy_out1){
					in_msg0->copy_mg_to(msg1, in0, nod);
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
hnode_1to2::run_dichotomy_simu(){
	GH_CK(get_flag(gh_is_dichotomy));
	GH_CK(one_range == &(msg0));
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);

	GH_CK(msg0.rng.min == msg0.rng.max);
	gh_addr_t dicho_val = msg0.rng.min;
	
	hnode_1to2* nod = this;
	hmessage* in_msg0 = in0->get_message_of(nod);
	GH_CK(in_msg0 != gh_null);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		if(ireq(*in0) && (! ack0)){
			gh_addr_t dst_addr = in_msg0->mg_dst;
			bool in_rng0 = (dst_addr >= dicho_val);
			bool in_rng1 = ! in_rng0;
			
			GH_CK_PRT((in_rng0 != in_rng1), "(%p) %ld %d==(%ld,%ld) %d==(%ld,%ld) ", (void*)nod,
					  dst_addr, in_rng0, msg0.rng.min, msg0.rng.max, in_rng1, msg1.rng.min, msg1.rng.max);
			
			if(in_rng0){
				bool rdy_out0 = ((! req0) && (! oack(*out0)));
				if(rdy_out0){
					in_msg0->copy_mg_to(msg0, in0, nod);
					req0 = true;
					ack0 = true;
				} 
			} 
			
			if(in_rng1){
				bool rdy_out1 = ((! req1) && (! oack(*out1)));
				if(rdy_out1){
					in_msg0->copy_mg_to(msg1, in0, nod);
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
hnode_target::run_target_simu(){
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);
	
	hnode_target* nod = this;
	hmessage* in_msg0 = in0->get_message_of(nod);
	
	GH_CK(GH_GLOBALS.tot_src_msg_simu > 0);
	GH_CK(msg0.mg_val == 0);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		if(ireq(*in0) && (! ack0)){
			GH_CK(addr == in_msg0->mg_dst);
			fprintf(stdout, "%ld RCV %ld -> %ld val=%ld i(%p) \n", addr, in_msg0->mg_src, in_msg0->mg_dst, in_msg0->mg_val,
				in0);
			num_msg_rcv++;
			
			ack0 = true;
		} 
		
		bool rdy_out0 = ((! req0) && (! oack(*out0)));
		if(is_source && rdy_out0 && ! dat->sent_all){
			
			if(msg0.mg_val >= GH_GLOBALS.tot_src_msg_simu){
				dat->sent_all = true;
				continue;
			}
			
			hnode_target* tg = choose_target();
			
			msg0.mg_val++;
				
			msg0.mg_src = addr;
			msg0.mg_dst = tg->addr;
			
			fprintf(stdout, "%ld SND %ld -> %ld val=%ld o(%p) \n", addr, msg0.mg_src, msg0.mg_dst, msg0.mg_val, 
					out0);
			num_msg_snt++;
			
			req0 = true;
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
hmessage::copy_mg_to(hmessage& mg, hnode* dbg_src_nod, hnode* dbg_dst_nod){
	GH_DBG_CODE(
		if(GH_GLOBALS.dbg_src_simu == mg_src){ 
			fprintf(stdout, "dbg ");
			print_message(stdout);
			fprintf(stdout, " (%p) -> (%p) ----\n", dbg_src_nod, dbg_dst_nod);
			//dbg_dst_nod->print_node(stdout, gh_full_pt_prt);
			//fprintf(stdout, " ");
			//fprintf(stdout, "\n-----------------\n");
			fflush(stdout);
		}
	);
	mg.mg_val = mg_val;
	mg.mg_src = mg_src;
	mg.mg_dst = mg_dst;
}

hnode_target* 
hnode_target::choose_target(){
	vector<hnode_target*>& all_tg = *GH_GLOBALS.all_tgt_simu;
	long sz = (long)all_tg.size();
	GH_CK(sz > 0);
	hnode_target* tg = all_tg[sz - 1];
	GH_CK(tg != gh_null);
	
	return tg;
}

void
gh_dbg_init_sources_and_sinks(vector<hnode_target*>& all_tgt){
	long tot_tg = (long)all_tgt.size();
	long lst_tg = tot_tg - 1;
	GH_CK(tot_tg > 0);

	GH_GLOBALS.tot_src_msg_simu = 3;
	GH_GLOBALS.dbg_src_simu = GH_INVALID_ADDR;
	GH_GLOBALS.all_tgt_simu = &all_tgt;
	
	for(long ii = 0; ii < lst_tg; ii++){
		hnode_target* tgt = all_tgt[ii];
		GH_CK(tgt != gh_null);
		tgt->is_source = true;
	}
}

