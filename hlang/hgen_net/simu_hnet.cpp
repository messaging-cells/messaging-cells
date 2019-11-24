

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/signalfd.h>
#include <unistd.h>

#include "hgen_net.h"

int test_m_to_n(int argc, char *argv[]);


void gh_dbg_init_simu();

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
test_bases(int argc, char *argv[]){
	if(argc < 2){
		printf("%s (0 | 1)\n", argv[0]);
		return 1;
	}
	
	long mm = atol(argv[1]);

	hroute_box* bx = new hroute_box(GH_BASE_TWO);
	GH_MARK_USED(bx);
	switch(mm){
		case 0: 
			bx->init_as_2to3_route_box(GH_NULL_OUT_ADDR, gh_null);
			break;
		case 1: 
			bx->init_as_3to2_route_box(GH_NULL_OUT_ADDR, gh_null);
			break;
		default: 
			bx->init_as_2to2_route_box(GH_NULL_OUT_ADDR, gh_null);
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

void 
gh_dbg_calc_idx_and_sz(long num_in, long num_out, long bs, long& tg_idx, long& tgs_sz){
	GH_CK(bs > 1);
	long mx = gh_max(num_in, num_out);
	GH_CK(mx > 0);
	double pp = pow(bs, mx);
	if((pp + 1) > LONG_MAX){
		gh_abort("**** power too big 1. choose less inputs or less outputs **** \n");
	}
	tg_idx = pp + 1;
	if((tg_idx + pp + 1) > LONG_MAX){
		gh_abort("**** power too big 2. choose less inputs or less outputs **** \n");
	}
	tgs_sz = tg_idx + pp + 1;
	GH_CK_PRT((tg_idx >= 0), "%ld %ld %ld \n", bs, mx, tg_idx);
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

	htarget_box* bx = new htarget_box(bb);
	
	long tg_idx = 0;
	long tgs_sz = 0;
	gh_dbg_calc_idx_and_sz(nin, nout, bb, tg_idx, tgs_sz);
	
	slice_vec all_addr;
	bx->init_target_box(tg_idx, nin, nout, all_addr, tgs_sz);

	fprintf(stdout, "===========\n");
	
	GH_GLOBALS.CK_LINK_MODE = gh_valid_self_ck_mod;

	bx->print_box(stdout, gh_full_pt_prt);
	
	delete bx;
		
	return 0;
}

void
prt_int_vec(vector<int>& vc){
	fprintf(stdout, "{");
	for(long aa = 0; aa < (long)vc.size(); aa++){
		fprintf(stdout, "%d ", vc[aa]);
	}
	fprintf(stdout, "}\n");
}

int
test_copy_arr(int argc, char *argv[]){
	
	vector<int> v1 = { 1, 2, 3 ,4 , 5, 6};
	vector<int> v2 = v1;
	v2.back() = 20;
	v1[2] = 321;
	v1.resize(30, 0);
	v1.insert(v1.begin(), v2.begin(), v2.end());
	
	prt_int_vec(v1);
	prt_int_vec(v2);
	return 0;
}

int
main(int argc, char *argv[]){
	int resp = 0;
	//resp = test_copy_arr(argc, argv);
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
		th_nd->run_1to2_simu();
	} else 
	if(the_nd->is_2to1()){
		hnode_2to1* th_nd = (hnode_2to1*)the_nd;
		th_nd->run_2to1_simu();
	} else {
		GH_CK(the_nd->is_1to1());
		hnode_1to1* th_nd = (hnode_1to1*)the_nd;
		gh_1t1_kind_t k1t1 = th_nd->get_1t1_kind();
		GH_CK(k1t1 == gh_target_1t1);
		
		hnode_target* tg = (hnode_target*)the_nd;
		tg->run_target_simu();
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

	//bool is_itv = get_flag(gh_is_interval);
	
	hnode_1to2* nod = this;
	hmessage* in_msg0 = in0->get_message_of(nod);
	GH_CK(in_msg0 != gh_null);
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		if(ireq(*in0) && (! ack0)){
			gh_addr_t dst_addr = in_msg0->mg_dst;
			bool go_down = in_interval(dst_addr);
			
			if(go_down){
				bool rdy_out0 = ((! req0) && (! oack(*out0)));
				if(rdy_out0){
					in_msg0->copy_mg_to(msg0, in0, nod);
					req0 = true;
					ack0 = true;
				} 
			} else {
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

bool
hnode_2to1::ck_out_interval(char dbg_in){
	if(! get_flag(gh_is_lognet_io)){ return true; }
	if(! in_interval(msg0.mg_dst)){
		fprintf(stdout, "BAD_RANGE with mg_dst=%ld in=%c\n", msg0.mg_dst, dbg_in);
		fprintf(stdout, "\t");
		print_node(stdout, gh_full_pt_prt);
		fprintf(stdout, "\t");
		msg0.print_message(stdout);
		fprintf(stdout, "\n");
		//return false;
	}
	return true;
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
					GH_CK(ck_out_interval('0'));
					
					req0 = true;
					ack0 = true;
				} else {
					choose0 = true;
					in_msg1->copy_mg_to(msg0, in1, nod);
					GH_CK(ck_out_interval('1'));
					
					req0 = true;
					ack1 = true;
				}
			}
			if(in0_rq && ! in1_rq){
				in_msg0->copy_mg_to(msg0, in0, nod);
				GH_CK(ck_out_interval('0'));
					
				req0 = true;
				ack0 = true;
			} 
			if(! in0_rq && in1_rq){
				in_msg1->copy_mg_to(msg0, in1, nod);
				GH_CK(ck_out_interval('1'));
					
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
			bool is_src = tg->is_source_simu;
			
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
		tot_msg_snt += tg->num_msg_snt_simu;
	}
	
	long ck_tot_rcv = -1;
	while(true){
		long tot_msg_rcv = 0;
		for(long aa = 0; aa < (long)all_targets.size(); aa++){
			hnode_target* tg = all_targets[aa];
			tot_msg_rcv += tg->num_msg_rcv_simu;
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

void gh_dbg_init_context(slice_vec& ctx_addrs);
void gh_dbg_post_test_prints(hlognet_box* bx);

int
test_hlognet(int argc, char *argv[]){
	
	bool go_on = GH_GLOBALS.get_args(argc, argv);
	
	if(! go_on){
		return 0;
	}
	
	if(GH_GLOBALS.dbg_run_m2n){
		gh_run_m_to_n(GH_GLOBALS.dbg_dag_mm, GH_GLOBALS.dbg_dag_nn, GH_GLOBALS.dbg_has_zr);
		return 0;
	}
	
	if(GH_GLOBALS.dbg_run_ini_slices){
		addr_vec_t all_rel_pos;
		
		all_rel_pos.resize(0);
		slice_vec sub_slices;
		gh_init_rel_pos(all_rel_pos, GH_GLOBALS.dbg_slices_sz, GH_BASE_TWO, GH_GLOBALS.dbg_slices_sd, GH_GLOBALS.dbg_has_zr);
		sub_slices.init_slice_vec_with(GH_GLOBALS.dbg_slices_idx, all_rel_pos);
		sub_slices.print_slice_vec(stdout);
		sub_slices.print_all_intervals(stdout);

		all_rel_pos.resize(0);
		slice_vec sub_2_slices;
		gh_init_rel_pos(all_rel_pos, 3, GH_BASE_TWO, gh_right_side, false);
		sub_2_slices.init_sub_slices_with(4, sub_slices, all_rel_pos);
		sub_2_slices.print_slice_vec(stdout);
		sub_2_slices.print_all_intervals(stdout);
		return 0;
	}
	
	bool add_ctx = GH_GLOBALS.add_ctx_simu;
	
	slice_vec out_addr;
	if(add_ctx){
		gh_dbg_init_context(out_addr);
		if(! out_addr.empty()){
			out_addr.print_slice_vec(stdout, "CONTEXT=");
			GH_GLOBALS.num_target_simu = (long)out_addr.size();
		}
	}
	
	long bb = GH_GLOBALS.base_simu;
	long ntg = GH_GLOBALS.num_target_simu;
	long ctx_idx = GH_GLOBALS.context_idx_simu;
	
	const char* add_str = (add_ctx)?("ADD"):("");

	fprintf(stdout, "test_hlognet base=%ld #ntg=%ld TEST=%ld ctx=%ld %s \n", 
			bb, ntg, GH_GLOBALS.idx_test_simu, ctx_idx, add_str);
	
	hlognet_box* bx = new hlognet_box(bb);
	bx->init_length(ntg);
	fprintf(stdout, "max_lgnet_height=%ld \n", bx->height + 1);
	fprintf(stdout, "===========\n");
	
	bx->init_lognet_box(ntg, out_addr);
	
	GH_GLOBALS.CK_LINK_MODE = gh_valid_self_ck_mod;

	fprintf(stdout, "=========== CALC_RANGES ===================\n");
	
	GH_GLOBALS.all_tgt_simu = &(bx->all_targets);
	
	gh_dbg_init_simu();

	if(GH_GLOBALS.dbg_box_prt){
		if(GH_GLOBALS.pointer_prt_simu){ 
			fprintf(stdout, "=========== PRINTING_NET_WITH_POINTERS ===================\n");
			bx->print_box(stdout, gh_full_pt_prt);
		} else {
			fprintf(stdout, "=========== PRETTY_PRINTING ===================\n");
			bx->print_box(stdout, gh_full_prt);
		}
	}

	fprintf(stdout, "=========== RUNNING_SIMU ===================\n");
	
	if(GH_GLOBALS.dbg_ck_path_simu){
		bx->ck_lognet_path(GH_GLOBALS.dbg_src_addr_simu, GH_GLOBALS.dbg_dst_addr_simu, true);
	} else 
	if(GH_GLOBALS.dbg_ck_all_path_from_simu){
		bx->ck_lognet_all_paths_from(GH_GLOBALS.dbg_src_addr_simu, true);
	} else 
	if(GH_GLOBALS.dbg_ck_all_path_simu){
		bx->ck_lognet_all_paths(true);
	} else 
	if(GH_GLOBALS.do_run_simu){
		bx->run_hlognet_simu();
	}
	
	gh_dbg_post_test_prints(bx);

	delete bx;
		
	return 0;
}

void
hnode_target::run_target_simu(){
	GH_CK(simu_data != gh_null);
	thd_data* dat = (thd_data*)(simu_data);
	
	hnode_target* nod = this;
	hmessage* in_msg0 = in0->get_message_of(nod);
	
	GH_CK(GH_GLOBALS.tot_src_msg_simu > 0);
	GH_CK(msg0.mg_val == 0);
	
	GH_CK(get_flag(gh_is_interval));
	
	for(;;){
		if(dat->end_it){
			break;
		}
		
		if(ireq(*in0) && (! ack0)){
			//bool dst_ok = (addr == in_msg0->mg_dst);
			bool dst_ok = in_interval(in_msg0->mg_dst);
			GH_CK_PRT(dst_ok, "ERROR: %ld.%s RCV <%ld>%ld -> %ld val=%ld i(%p) %s \n",
				addr, get_selector_str().c_str(), in_msg0->mg_sra, in_msg0->mg_src, in_msg0->mg_dst, in_msg0->mg_val, in0,
				get_selector_str().c_str()
			);
			fprintf(stdout, "%ld.%s RCV <%ld>%ld -> %ld val=%ld i(%p) ", addr, get_selector_str().c_str(), 
					in_msg0->mg_sra, in_msg0->mg_src, in_msg0->mg_dst, in_msg0->mg_val, in0);
			print_selector_info(stdout);
			fprintf(stdout, "\n");
			
			num_msg_rcv_simu++;
			
			ack0 = true;
		} 
		
		bool rdy_out0 = ((! req0) && (! oack(*out0)));
		if(is_source_simu && rdy_out0 && ! dat->sent_all){
			
			if(msg0.mg_val >= GH_GLOBALS.tot_src_msg_simu){
				dat->sent_all = true;
				continue;
			}
			
			gh_addr_t src_adr = GH_INVALID_ADDR;
			gh_addr_t dst_adr = GH_INVALID_ADDR;
			
			dbg_choose_msg_src_dst_simu(src_adr, dst_adr);
			if(src_adr == GH_INVALID_ADDR){
				GH_CK(dst_adr == GH_INVALID_ADDR);
				dat->sent_all = true;
				continue;
			}
			msg0.mg_val++;
				
			msg0.mg_sra = addr;
			msg0.mg_src = src_adr;
			msg0.mg_dst = dst_adr;
			
			fprintf(stdout, "%ld.%s SND <%ld>%ld -> %ld val=%ld o(%p) \n", addr, get_selector_str().c_str(), 
					msg0.mg_sra, msg0.mg_src, msg0.mg_dst, msg0.mg_val, out0);
			num_msg_snt_simu++;
			
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
		if((GH_GLOBALS.dbg_src_idx_simu == mg_sra) && (GH_GLOBALS.dbg_src_addr_simu == mg_src)){ 
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
	mg.mg_sra = mg_sra;
	mg.mg_src = mg_src;
	mg.mg_dst = mg_dst;
}

// ==================================================================================
// ALL TESTS

bool
hnode_target::dbg_inc_tgt_simu(){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tg = *GH_GLOBALS.all_tgt_simu;
	
	if(curr_dest_simu == GH_INVALID_ADDR){
		curr_dest_simu = 0;
	} else {
		if(inc_st_simu()){
			curr_dest_simu++;
		}
	}
	GH_CK(curr_dest_simu >= 0);
	
	long all_sz = (long)all_tg.size();
	GH_CK(all_sz > 0);
	if(curr_dest_simu == all_sz){
		return false;
	}
	
	GH_CK(curr_dest_simu < all_sz);
	if(all_tg[curr_dest_simu] == this){
		curr_dest_simu++;
		curr_st_simu = gh_min_min_dbg_st;
		if(curr_dest_simu == all_sz){
			return false;
		}
	}
	GH_CK(curr_dest_simu < all_sz);
	return true;
}

void
hnode_target::dbg_nxt_src_dst_simu(gh_addr_t& src, gh_addr_t& dst){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tg = *GH_GLOBALS.all_tgt_simu;
	
	GH_CK(curr_dest_simu < (long)all_tg.size());
	hnode_target* tg = all_tg[curr_dest_simu];
	GH_CK(tg != gh_null);

	switch(curr_st_simu){
		case gh_min_min_dbg_st:
			src = get_min_simu();
			dst = tg->get_min_simu();
			break;
		case gh_min_max_dbg_st:
			src = get_min_simu();
			dst = tg->get_max_simu();
			break;
		case gh_max_min_dbg_st:
			src = get_max_simu();
			dst = tg->get_min_simu();
			break;
		case gh_max_max_dbg_st:
			src = get_max_simu();
			dst = tg->get_max_simu();
			break;
	}

	GH_CK_PRT((in_interval(src)), "%d src=%ld %s \n", print_node(stdout, gh_full_prt), src,
		gh_dbg_st_case_str(curr_st_simu)
	);
	GH_CK(tg->in_interval(dst)); 
	
	if(GH_GLOBALS.dbg_prt_choo_simu){
		fprintf(stdout, "%ld.%s CHOO %ld -> %ld %s \n", addr, get_selector_str().c_str(), 
			src, dst, gh_dbg_st_case_str(curr_st_simu));
	}
	
	GH_CK(src != GH_INVALID_ADDR);
	GH_CK(dst != GH_INVALID_ADDR);
}

void
hnode_target::dbg_calc_src_dst_simu(gh_addr_t& src, gh_addr_t& dst){
	bool go_on = dbg_inc_tgt_simu();
	if(! go_on){
		src = GH_INVALID_ADDR;
		dst = GH_INVALID_ADDR;
		return;
	}
	
	dbg_nxt_src_dst_simu(src, dst);
}

void
hnode_target::dbg_choose_msg_src_dst_simu(gh_addr_t& src, gh_addr_t& dst){
	GH_CK(GH_GLOBALS.idx_test_simu >= 0);
	switch(GH_GLOBALS.idx_test_simu){
		case 0:
			test0_choose_msg_src_dst_simu(src, dst);
			break;
		case 1:
			test1_choose_msg_src_dst_simu(src, dst);
			break;
		case 2:
			test2_choose_msg_src_dst_simu(src, dst);
			break;
		case 3:
			test3_choose_msg_src_dst_simu(src, dst);
			break;
		case 4:
			test4_choose_msg_src_dst_simu(src, dst);
			break;
		case 5:
			test5_choose_msg_src_dst_simu(src, dst);
			break;
	}
}

void gh_dbg_init_test0_simu();
void gh_dbg_init_test1_simu();
void gh_dbg_init_test2_simu();
void gh_dbg_init_test3_simu();
void gh_dbg_init_test4_simu();
void gh_dbg_init_test5_simu();

void
gh_dbg_init_simu(){
	GH_CK(GH_GLOBALS.idx_test_simu >= 0);
	switch(GH_GLOBALS.idx_test_simu){
		case 0:
			gh_dbg_init_test0_simu();
			return;
		case 1:
			gh_dbg_init_test1_simu();
			return;
		case 2:
			gh_dbg_init_test2_simu();
			return;
		case 3:
			gh_dbg_init_test3_simu();
			return;
		case 4:
			gh_dbg_init_test4_simu();
			return;
		case 5:
			gh_dbg_init_test5_simu();
			return;
	}
	GH_CK(false);
}

// -----------------
// TEST0

void
hnode_target::test0_choose_msg_src_dst_simu(gh_addr_t& src, gh_addr_t& dst){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tg = *GH_GLOBALS.all_tgt_simu;
	
	long sz = (long)all_tg.size();
	GH_CK(sz > 0);
	
	curr_dest_simu = (sz - 1);
	dbg_nxt_src_dst_simu(src, dst);
	inc_st_simu();
}

void
gh_dbg_init_test0_simu(){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tgt = *GH_GLOBALS.all_tgt_simu;
	
	long tot_tg = (long)all_tgt.size();
	long lst_tg = tot_tg - 1;
	GH_CK(tot_tg > 0);

	GH_GLOBALS.tot_src_msg_simu = 3;
	
	for(long ii = 0; ii < lst_tg; ii++){
		hnode_target* tgt = all_tgt[ii];
		GH_CK(tgt != gh_null);
		tgt->is_source_simu = true;
	}
}

// -----------------
// TEST1

void
hnode_target::test1_choose_msg_src_dst_simu(gh_addr_t& src, gh_addr_t& dst){
	curr_dest_simu = 0;
	dbg_nxt_src_dst_simu(src, dst);
	inc_st_simu();	
}

void
gh_dbg_init_test1_simu(){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tgt = *GH_GLOBALS.all_tgt_simu;
	
	long tot_tg = (long)all_tgt.size();
	GH_CK(tot_tg > 0);

	GH_GLOBALS.tot_src_msg_simu = 4;
	
	for(long ii = 1; ii < tot_tg; ii++){
		hnode_target* tgt = all_tgt[ii];
		GH_CK(tgt != gh_null);
		tgt->is_source_simu = true;
	}
}

// TEST2

void
hnode_target::test2_choose_msg_src_dst_simu(gh_addr_t& src, gh_addr_t& dst){
	dbg_calc_src_dst_simu(src, dst);
}

void
gh_dbg_init_test2_simu(){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tgt = *GH_GLOBALS.all_tgt_simu;
	
	long tot_tg = (long)all_tgt.size();
	GH_CK(tot_tg > 0);

	GH_GLOBALS.tot_src_msg_simu = tot_tg;
	
	hnode_target* tgt = all_tgt[0];
	GH_CK(tgt != gh_null);
	tgt->is_source_simu = true;
}

// TEST3

void
hnode_target::test3_choose_msg_src_dst_simu(gh_addr_t& src, gh_addr_t& dst){
	dbg_calc_src_dst_simu(src, dst);
}

void
gh_dbg_init_test3_simu(){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tgt = *GH_GLOBALS.all_tgt_simu;
	
	long tot_tg = (long)all_tgt.size();
	GH_CK(tot_tg > 0);
	
	long lst_tg = tot_tg - 1;

	GH_GLOBALS.tot_src_msg_simu = tot_tg;
	
	hnode_target* tgt = all_tgt[lst_tg];
	GH_CK(tgt != gh_null);
	tgt->is_source_simu = true;
	
	/*for(long ii = 0; ii < tot_tg; ii++){
		hnode_target* tgt = all_tgt[ii];
		GH_CK(tgt != gh_null);
		tgt->is_source_simu = true;
	}*/
}

// TEST4

void
hnode_target::test4_choose_msg_src_dst_simu(gh_addr_t& src, gh_addr_t& dst){
	dbg_calc_src_dst_simu(src, dst);
}

void
gh_dbg_init_test4_simu(){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tgt = *GH_GLOBALS.all_tgt_simu;
	
	long tot_tg = (long)all_tgt.size();
	GH_CK(tot_tg > 0);
	
	GH_GLOBALS.tot_src_msg_simu = tot_tg;
	
	for(long ii = 0; ii < tot_tg; ii++){
		hnode_target* tgt = all_tgt[ii];
		GH_CK(tgt != gh_null);
		tgt->is_source_simu = true;
	}
}

// TEST5

void
hnode_target::test5_choose_msg_src_dst_simu(gh_addr_t& src, gh_addr_t& dst){
	src = GH_GLOBALS.dbg_src_addr_simu;
	dst = GH_GLOBALS.dbg_dst_addr_simu;
	
	GH_CK(src != GH_INVALID_ADDR);
	GH_CK(dst != GH_INVALID_ADDR);
}

void
gh_dbg_init_test5_simu(){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tgt = *GH_GLOBALS.all_tgt_simu;
	
	if(GH_GLOBALS.dbg_src_addr_simu == GH_INVALID_ADDR){
		fprintf(stdout, "\n\n\n\n\n\n\n\nMUST use -src option for test 5 to work !!!! \n\n\n\n\n\n\n\n");
		GH_GLOBALS.do_run_simu = false;
		return;
	}
	if(GH_GLOBALS.dbg_dst_addr_simu == GH_INVALID_ADDR){
		fprintf(stdout, "\n\n\n\n\n\n\n\nMUST use -dst option for test 5 to work !!!! \n\n\n\n\n\n\n\n");
		GH_GLOBALS.do_run_simu = false;
		return;
	}

	long idx = GH_GLOBALS.dbg_src_idx_simu;	// SOURCE ONE_PAIR
	
	long tot_tg = (long)all_tgt.size();
	GH_CK(tot_tg > 0);
	GH_CK(idx < tot_tg);
	
	GH_GLOBALS.tot_src_msg_simu = 1;

	hnode_target* tgt = all_tgt[idx];
	GH_CK(tgt != gh_null);
	tgt->is_source_simu = true;
}

// END_TESTS

void
gh_dbg_prt_node(hlognet_box* bx, gh_addr_t adr){
	GH_CK(bx != gh_null);
	vector<hnode*>& nods = bx->all_nodes;
	
	gh_addr_t sz = nods.size();
	
	if(sz > (long)adr){
		hnode* nd = nods[adr];
		if(nd->is_1to2()){
			hnode_1to2& nd2 = *((hnode_1to2*)nd);
			fprintf(stdout, "%ld:", nd2.addr);
			nd2.print_node(stdout, gh_full_pt_prt);
		}
	}
}

void
gh_dbg_post_test_prints(hlognet_box* bx){
	vector<gh_addr_t>& dbg_nods = GH_GLOBALS.dbg_nodes_prt_simu;
	
	fprintf(stdout, "=========== POST_PRINTS ===================\n");
	
	for(long aa = 0; aa < (long)dbg_nods.size(); aa++){
		gh_addr_t idx = dbg_nods[aa];
		gh_dbg_prt_node(bx, idx);
	}
	
}

bool
hnode_target::inc_st_simu(){
	GH_CK(GH_GLOBALS.all_tgt_simu != gh_null);
	vector<hnode_target*>& all_tg = *GH_GLOBALS.all_tgt_simu;
	GH_CK(curr_dest_simu >= 0);
	GH_CK(curr_dest_simu < (long)all_tg.size());
	hnode_target* tg = all_tg[curr_dest_simu];
	
	bool one_src = (get_diff_simu() <= 1);
	bool one_dst = (tg->get_diff_simu() <= 1);
	
	if(one_src && one_dst){
		return true;
	}
	bool inc_tg = false;
	if(one_src && ! one_dst){
		switch(curr_st_simu){
			case gh_min_min_dbg_st:
				curr_st_simu = gh_min_max_dbg_st;
				break;
			case gh_min_max_dbg_st:
				curr_st_simu = gh_min_min_dbg_st;
				inc_tg = true;
				break;
			default:
				GH_CK(false);
				break;
		}
		return inc_tg;
	}
	if(! one_src && one_dst){
		switch(curr_st_simu){
			case gh_min_min_dbg_st:
				curr_st_simu = gh_max_min_dbg_st;
				break;
			case gh_max_min_dbg_st:
				curr_st_simu = gh_min_min_dbg_st;
				inc_tg = true;
				break;
			default:
				GH_CK(false);
				break;
		}
		return inc_tg;
	}
	GH_CK(! one_src && ! one_dst);
	
	if(curr_st_simu == gh_max_max_dbg_st){
		curr_st_simu = gh_min_min_dbg_st;
		return true;
	}
	int vv = (int)curr_st_simu;
	vv++;
	curr_st_simu = (gh_dbg_st_t)vv;
	return false;
}

void
hgen_globals::print_help(const char* prg){
	fprintf(stdout, "%s <base> <#target> [-pp] [-cho] [-no_run] [-no_prt] [-prt_tgt] [-t <test_id>] [-ctx <context_id>] ", prg);
	fprintf(stdout, "[-dbg_prt] {[-n <dbg_nod_adr>]}* [-idx <src_idx>] [-src <src_addr>] [-dst <dst_addr>] ");
	fprintf(stdout, "[-disp <ptr_adr_disp>] [-m2n] [-ini_slices] [-zr] [-rgt] [-ck_pth] [-ck_all_pth_from] [-ck_all_pth]");
	//fprintf(stdout, "[-dn <dbg_nod>] ");
	fprintf(stdout, "\n");
}

bool
hgen_globals::get_args(int argc, char** argv){
	
	const char* prg_nm = argv[0];
	
	if(argc < 3){
		print_help(prg_nm);
		return false;
	}
	
	base_simu = atol(argv[1]);
	num_target_simu = atol(argv[2]);
	
	long first_pm = 3;
	
	idx_test_simu = 0;
	context_idx_simu = 0;
	
	bool prt_help = false;
	
	for(long ii = first_pm; ii < argc; ii++){
		std::string the_arg = argv[ii];
		if(the_arg == "-h"){
			prt_help = true;
		} else if(the_arg == "-pp"){
			pointer_prt_simu = true;
		} else if(the_arg == "-no_run"){
			do_run_simu = false;
		} else if(the_arg == "-no_prt"){
			dbg_box_prt = false;
		} else if(the_arg == "-prt_tgt"){
			prt_tgt_info = true;
		} else if(the_arg == "-dbg_prt"){
			dbg_prt_gen_info = true;
		} else if(the_arg == "-cho"){
			dbg_prt_choo_simu = true;
		} else if(the_arg == "-zr"){
			dbg_has_zr = true;
		} else if(the_arg == "-rgt"){
			dbg_slices_sd = gh_right_side;
		} else if(the_arg == "-ck_pth"){
			dbg_ck_path_simu = true;
		} else if(the_arg == "-ck_all_pth_from"){
			dbg_ck_all_path_from_simu = true;
		} else if(the_arg == "-ck_all_pth"){
			dbg_ck_all_path_simu = true;
		} else if(the_arg == "-m2n"){
			dbg_run_m2n = true;
			dbg_dag_mm = base_simu;
			dbg_dag_nn = num_target_simu;
		} else if(the_arg == "-ini_slices"){
			dbg_run_ini_slices = true;
			dbg_slices_sz = base_simu;
			dbg_slices_idx = num_target_simu;
		} else if((the_arg == "-t") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			idx_test_simu = atol(argv[kk_idx]);
		} else if((the_arg == "-ctx") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			add_ctx_simu = true;
			context_idx_simu = atol(argv[kk_idx]);
		} else if((the_arg == "-n") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			gh_addr_t adr = atol(argv[kk_idx]);
			dbg_nodes_prt_simu.push_back(adr);			
		} else if((the_arg == "-disp") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			dbg_prt_disp_all_addr_simu = atol(argv[kk_idx]);
		} else if((the_arg == "-idx") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			dbg_src_idx_simu = atol(argv[kk_idx]);
		} else if((the_arg == "-src") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			dbg_src_addr_simu = atol(argv[kk_idx]);
		} else if((the_arg == "-dst") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			dbg_dst_addr_simu = atol(argv[kk_idx]);
		} else {
			fprintf(stdout, "Unknown option %s \n", the_arg.c_str());
			
			prt_help = true;
		}
	}
	
	if(prt_help){
		print_help(prg_nm);
		return false;
	}

	return true;
}

gh_addr_t
hnode::get_diff_simu(){
	GH_CK(get_flag(gh_is_interval));
	return selector.dbg_get_num_test_in();
}

gh_addr_t
hnode::get_min_simu(){
	GH_CK(get_flag(gh_is_interval));
	return selector.dbg_get_min_in();
}

gh_addr_t
hnode::get_max_simu(){
	GH_CK(get_flag(gh_is_interval));
	return selector.dbg_get_max_in();
}

void
gh_run_m_to_n(long mm, long nn, bool has_zr){
	slice_vec tgt_addrs;
	slice_vec all_addrs;
	all_addrs.init_slice_vec(0, tgt_addrs, nn, 
					 GH_BASE_TWO, gh_left_side, has_zr, "all_addrs");
	
	all_addrs.print_slice_vec(stdout, "all_addrs=\n");
	fprintf(stdout, "\n\n ===================\n");
	
	hnode_box* bx = gh_get_binnet_m_to_n(mm, nn, &all_addrs, gh_null, gh_call_14);
	GH_MARK_USED(bx);
	
	bx->print_box(stdout, gh_full_prt);
}

int
test_m_to_n(int argc, char *argv[]){
	if(argc < 3){
		printf("%s <num_in> <num_out> [-z]\n", argv[0]);
		return 1;
	}
	
	long mm = atol(argv[1]);
	long nn = atol(argv[2]);
	
	bool has_zr = false;
	if(argc > 3){
		has_zr = true;
	}
	
	gh_run_m_to_n(mm, nn, has_zr);

	/*
	slice_set tgt_addrs;
	slice_set all_addrs;
	all_addrs.init_slice_set(0, tgt_addrs, nn, 
					 GH_BASE_TWO, gh_left_side, has_zr, "all_addrs");
	
	fprintf(stdout, "all_addrs=\n"); 
	for(long aa = 0; aa < (long)all_addrs.size(); aa++){ fprintf(stdout, " %ld", all_addrs.get_addr(aa)); }
	fprintf(stdout, "\n\n ===================\n");
	
	hnode_box* bx = gh_get_binnet_m_to_n(mm, nn, &all_addrs, gh_null, gh_call_14);
	GH_MARK_USED(bx);
	
	bx->print_box(stdout, gh_full_prt);
	*/
	
	return 0;
}

void
gh_dbg_init_context(slice_vec& ctx_addrs){
	long ctx_idx = GH_GLOBALS.context_idx_simu;
	if(ctx_idx == 1){
		//ctx_addrs.sls_orig = gh_inc_slc;
		//ctx_addrs.sls_all = {8, 7, 6, 4, 0};
	}
	if(ctx_idx == 2){
		//ctx_addrs.sls_orig = gh_dec_slc;
		//ctx_addrs.sls_all = {8, 7, 6, 4, 0};
	}
}

gh_addr_t
edge::get_first_addr_in(){
	GH_CK(! is_undef());
	if(is_eq()){
		return slc_edge;
	}
	if(is_gt()){
		return slc_edge + 1;
	}
	return slc_edge - 1;
}

long
interval::dbg_get_num_test_in(){
	if(lft.is_undef()){
		return 1;
	}
	if(rgt.is_undef()){
		return 1;
	}
	gh_addr_t lin = lft.get_first_addr_in();
	gh_addr_t rin = rgt.get_first_addr_in();
	
	if(lin < rin){ return (rin - lin); } 
	return (lin - rin);
}

gh_addr_t
interval::dbg_get_min_in(){
	if(lft.is_undef()){
		GH_CK(! rgt.is_undef());
		return rgt.get_first_addr_in();
	}
	if(rgt.is_undef()){
		GH_CK(! lft.is_undef());
		return lft.get_first_addr_in();
	}
	gh_addr_t lin = lft.get_first_addr_in();
	return lin;
}

gh_addr_t
interval::dbg_get_max_in(){
	if(lft.is_undef()){
		GH_CK(! rgt.is_undef());
		return rgt.get_first_addr_in();
	}
	if(rgt.is_undef()){
		GH_CK(! lft.is_undef());
		return lft.get_first_addr_in();
	}
	gh_addr_t rin = rgt.get_first_addr_in();
	return rin;
}

bool
hnode::in_interval(gh_addr_t addr){
	bool is_itv = get_flag(gh_is_interval);
	if(! is_itv){
		GH_CK(! selector.lft.is_undef());
		return selector.lft.in_edge(addr);
	}
	return selector.in_interval(addr);
}

bool
interval::in_interval(gh_addr_t addr){
	GH_CK(! lft.is_undef() || ! rgt.is_undef());
	bool in_l = lft.in_edge(addr);
	bool in_r = rgt.in_edge(addr);
	return (in_l && in_r);
}

bool
edge::in_edge(gh_addr_t addr){
	if(is_undef()){
		return true;
	}
	if(is_gt()){
		if(is_eq()){
			return (addr >= slc_edge);
		}
		return (addr > slc_edge);
	}
	if(is_eq()){
		return (addr <= slc_edge);
	}
	return (addr < slc_edge);
}

bool
hlognet_box::ck_lognet_path(gh_addr_t src_addr, gh_addr_t dst_addr, bool dbg_prt){
	if(dbg_prt){
		fprintf(stdout, "==============================\n");
		fprintf(stdout, "CHECKING_PATH FROM src=%ld TO dst=%ld \nUse -src and -dst to set them.\n", src_addr, dst_addr);
		fprintf(stdout, "----------------\n");
	}

	GH_CK(src_addr >= 0);
	GH_CK(src_addr < (long)all_targets.size());
	GH_CK(dst_addr >= 0);
	GH_CK(dst_addr < (long)all_targets.size());
	
	hnode_target* src_tgt = all_targets[src_addr];
	GH_CK(src_tgt != gh_null);
	
	if(dbg_prt){
		src_tgt->print_node(stdout, gh_full_prt);
	}
	
	hnode* curr_nd = src_tgt->out0;
	GH_CK(curr_nd != gh_null);
	while(! curr_nd->is_1to1()){
		if(dbg_prt){
			curr_nd->print_node(stdout, gh_full_prt);
		}
		if(curr_nd->is_1to2()){
			hnode_1to2* th_nd = (hnode_1to2*)curr_nd;
			bool go_down = th_nd->in_interval(dst_addr);
			if(go_down){
				curr_nd = th_nd->out0;
			} else {
				curr_nd = th_nd->out1;
			}
		} else {
			GH_CK(curr_nd->is_2to1());
			hnode_2to1* th_nd = (hnode_2to1*)curr_nd;
			if(th_nd->get_flag(gh_is_lognet_io)){
				GH_CK(th_nd->in_interval(dst_addr));
			}
			curr_nd = th_nd->out0;
		}
		GH_CK(curr_nd != gh_null);
	}
	if(dbg_prt){
		curr_nd->print_node(stdout, gh_full_prt);
	}
	
	GH_CK_PRT((curr_nd == all_targets[dst_addr]), "%ld -> %ld FAILED !!!\n", src_addr, dst_addr);
	GH_CK(all_targets[dst_addr]->bx_idx == dst_addr);

	if(dbg_prt){
		fprintf(stdout, "PATH_OK.\n");
	}
	
	return true;
}

bool
hlognet_box::ck_lognet_all_paths_from(gh_addr_t src_addr, bool dbg_prt){
	if(dbg_prt){
		fprintf(stdout, "==============================\n");
		fprintf(stdout, "CHECKING_ALL_PATHS FROM src=%ld \nUse -src to set it.\n", src_addr);
		fprintf(stdout, "----------------\n");
	}
	for(long aa = 0; aa < (long)all_targets.size(); aa++){
		if(aa == src_addr){ continue; }
		ck_lognet_path(src_addr, aa, false);
		if(dbg_prt){
			fprintf(stdout, "%ld -> %ld OK\n", src_addr, aa);
		}
	}
	if(dbg_prt){
		fprintf(stdout, "all_pth from src=%ld OK\n", src_addr);
	}
	return true;
}

bool
hlognet_box::ck_lognet_all_paths(bool dbg_prt){
	if(dbg_prt){
		fprintf(stdout, "==============================\n");
		fprintf(stdout, "CHECKING_ALL_PATHS\n");
		fprintf(stdout, "----------------\n");
	}
	for(long aa = 0; aa < (long)all_targets.size(); aa++){
		ck_lognet_all_paths_from(aa, false);
		if(dbg_prt){
			fprintf(stdout, "%ld -> ALL ok.\n", aa);
		}
	}
	if(dbg_prt){
		fprintf(stdout, "ALL_PATHS_OK\n");
	}
	return true;
}