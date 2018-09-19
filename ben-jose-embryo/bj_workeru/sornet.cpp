
#include "cell.hh"
#include "sornet.hh"

#define BJ_SORNET_TIER 0

//define BJ_SORNET_BIN_TEST
//define BJ_SORNET_NUM_TEST
//define BJ_SORNET_RANK_TEST
#define BJ_SORNET_SRT_RNK_TEST

#ifdef BJ_SORNET_BIN_TEST
#define BJ_DBG_SORBINS(prm) prm
#else
#define BJ_DBG_SORBINS(prm) 
#endif

#ifdef BJ_SORNET_NUM_TEST
#define BJ_DBG_SORNUMS(prm) prm
#else
#define BJ_DBG_SORNUMS(prm) 
#endif

#define BJ_DBG_GRPS_SORNUMS(prm) prm

#ifdef BJ_SORNET_RANK_TEST
#define BJ_DBG_RANK_OUTS(prm) prm
#else
#define BJ_DBG_RANK_OUTS(prm) 
#endif

#define BJ_DBG_GRPS_RANK(prm) 

#ifdef BJ_SORNET_SRT_RNK_TEST
#define BJ_DBG_SRT_RNK(prm) prm
#else
#define BJ_DBG_SRT_RNK(prm) 
#endif

#define BJ_DBG_GRPS_SRT_RNK(prm) prm

#define bj_pt_obj_as_num(pt_oo) (*((num_nod_t*)(pt_oo)))

#define bj_idx_inside(idx, min, max) ((min <= idx) && (idx <= max))

#define bj_pt_to_num(pt) ((num_nod_t)pt)
#define bj_num_to_pt(num) ((void*)num)

void 
sorcell_sornet_handler(missive* msv){
	MCK_CALL_HANDLER(sorcell, sornet_handler, msv);
}

void 
endcell_sornet_handler(missive* msv){
	MCK_CALL_HANDLER(endcell, sornet_handler, msv);
}

void 
nervenet_sornet_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, sornet_handler, msv);
}


void bj_sornet_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_sorcell] = sorcell_sornet_handler;
	hndlrs[idx_endcell] = endcell_sornet_handler;
	hndlrs[idx_nervenet] = nervenet_sornet_handler;
	hndlrs[idx_last_invalid] = kernel::invalid_handler_func;

	kernel::set_tot_cell_subclasses(idx_total);
	kernel::set_cell_handlers(hndlrs);
}


bj_cmp_obj_func_t
sornet_get_cmp_func(sorkind_t knd){
	BJ_DBG_SORBINS(return &bj_cmp_bin_objs);
	BJ_DBG_SORNUMS(return &bj_cmp_num_objs);
	BJ_DBG_RANK_OUTS(return &bj_cmp_rnk_objs);
	
	bj_cmp_obj_func_t fn = mc_null;
	switch(knd){
		case sorkind_bin:
		break;
		case sorkind_num:
			BJ_DBG_SRT_RNK(fn = &bj_cmp_num_objs);
		break;
		case sorkind_rnk:
			BJ_DBG_SRT_RNK(fn = &bj_cmp_rnk_objs);
		break;
		default:
			mck_abort(1, mc_cstr("Invalid sornet_tok_t (sornet_get_cmp_func)"));
		break;
	}
	PTD_CK(fn != mc_null);
	return fn;
}

void
sorcell::sornet_handler(missive* msv){
	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	sorkind_t tmt_knd = sn_tmt->d.srt.knd;
	switch(tmt_knd){
		case sorkind_bin:
		case sorkind_num:
			sornet_srt_handler(sn_tmt);
			break;
		case sorkind_rnk:
			sornet_rnk_handler(sn_tmt);
			break;
		default:
			mck_abort(1, mc_cstr("Invalid sorkind (sorcell::sornet_handler)"));
		break;
	}
}

void
sorcell::calc_color(){
	num_nod_t min_col = mc_min(up_snp.min_col, down_snp.min_col);
	up_snp.min_col = min_col;
	down_snp.min_col = min_col;

	num_nod_t max_col = mc_max(up_snp.max_col, down_snp.max_col);
	up_snp.max_col = max_col;
	down_snp.max_col = max_col;
}

void
sornapse::reset(void* invalid_val){
	min_col = BJ_INVALID_SRT_GRP;
	max_col = BJ_INVALID_SRT_GRP;
	min_grp = BJ_INVALID_SRT_GRP;
	max_grp = BJ_INVALID_SRT_GRP;
	inp = invalid_val;
}
	
void
sorcell::sornet_reset(void* invalid_val){
	up_snp.reset(invalid_val);
	down_snp.reset(invalid_val);
}

void
sornapse::set_snp_fields(sornet_transmitter* sn_tmt, bool set_inp){
	PTD_CK(min_col == BJ_INVALID_SRT_GRP);
	PTD_CK(max_col == BJ_INVALID_SRT_GRP);
	PTD_CK(min_grp == BJ_INVALID_SRT_GRP);
	PTD_CK(max_grp == BJ_INVALID_SRT_GRP);
	
	if(set_inp){ inp = sn_tmt->d.srt.inp; }
	min_col = sn_tmt->d.srt.min_col;
	max_col = sn_tmt->d.srt.max_col;
	min_grp = sn_tmt->d.srt.min_grp;
	max_grp = sn_tmt->d.srt.max_grp;

	PTD_CK(min_col != BJ_INVALID_SRT_GRP);
	PTD_CK(max_col != BJ_INVALID_SRT_GRP);
	PTD_CK(min_grp != BJ_INVALID_SRT_GRP);
	PTD_CK(max_grp != BJ_INVALID_SRT_GRP);
}

void
sorcell::sornet_set_fields(sornet_transmitter* sn_tmt, void* invalid_val){
	num_nod_t tmt_idx = sn_tmt->d.srt.idx;
	PTD_CK(sn_tmt->d.srt.inp != invalid_val);

	if(tmt_idx == up_snp.idx){
		PTD_CK(up_snp.inp == invalid_val);
		up_snp.set_snp_fields(sn_tmt);
		PTD_CK(bj_idx_inside(up_snp.idx, up_snp.min_grp, up_snp.max_grp));
	}
	if(tmt_idx == down_snp.idx){
		PTD_CK(down_snp.inp == invalid_val);
		down_snp.set_snp_fields(sn_tmt);
		PTD_CK(bj_idx_inside(down_snp.idx, down_snp.min_grp, down_snp.max_grp));
	}
	
	PTD_CK((up_snp.inp != invalid_val) || (down_snp.inp != invalid_val));
}

void
bj_send_sornet_tmt(cell* src, sornet_tok_t tok, sorkind_t knd, num_nod_t min_col, num_nod_t max_col, 
				   num_nod_t min_grp, num_nod_t max_grp,
				   void* obj, cell* dst, num_nod_t idx, endcell* ecll)
{
	PTD_CK(src != mc_null);
	PTD_CK_PRT(((knd == sorkind_rnk) || (obj != mc_null) || (tok == bj_tok_sornet_start)), 
			   "KIND=%d \n", knd);
	PTD_CK(knd != sorkind_invalid);

	sornet_transmitter* sn_tmt = sornet_transmitter::acquire();
	sn_tmt->init_sornet_transmitter();
	//sn_tmt->wrk_side = side_left;

	sn_tmt->src = src;
	sn_tmt->dst = dst;
	sn_tmt->tok = tok;
	
	sn_tmt->d.srt.knd = knd;
	sn_tmt->d.srt.idx = idx;
	sn_tmt->d.srt.inp = obj;
	sn_tmt->d.srt.min_col = min_col;
	sn_tmt->d.srt.max_col = max_col;
	sn_tmt->d.srt.min_grp = min_grp;
	sn_tmt->d.srt.max_grp = max_grp;

	if(sn_tmt->dst == mc_null){
		switch(knd){
			case sorkind_bin:
			case sorkind_num:
				tok = bj_tok_sornet_out;
				break;
			case sorkind_rnk:
				tok = bj_tok_sornet_rank_out;
				break;
			default:
				mck_abort(1, mc_cstr("Invalid sorkind (bj_send_sornet_tmt)"));
				break;
		}
		//nervenet* root_net = bj_nervenet->get_nervenet(mc_nn_to_id(0));
		//sn_tmt->dst = root_net;
		
		PTD_CK(ecll != mc_null);
		sn_tmt->dst = ecll;
		sn_tmt->tok = tok;

		bool send_root_dbg_out = false;
		MC_MARK_USED(send_root_dbg_out);
		BJ_DBG_SORBINS(send_root_dbg_out = true);
		BJ_DBG_SORNUMS(send_root_dbg_out = true);
		BJ_DBG_RANK_OUTS(send_root_dbg_out = true);
		BJ_DBG_SRT_RNK(
			if(knd == sorkind_rnk){ send_root_dbg_out = true; }
		);
		
		MC_DBG(
			if(send_root_dbg_out){
				nervenet* root_net = bj_nervenet->get_nervenet(mc_nn_to_id(0));
				sornet_transmitter* dbg_sn_tmt = sornet_transmitter::acquire();
				dbg_sn_tmt->init_sornet_transmitter();
				
				dbg_sn_tmt->copy_sornet_transmitter(*sn_tmt);
				dbg_sn_tmt->dst = root_net;
				dbg_sn_tmt->send();
			}
		);
	}

	sn_tmt->send();
}

void
sornet_transmitter::copy_sornet_transmitter(sornet_transmitter& orig){
	// this func is necessary so that code fits in CODE area for parallella
	//wrk_side = orig.wrk_side;

	src = orig.src;
	dst = orig.dst;
	tok = orig.tok;
	
	d.srt.knd = orig.d.srt.knd;
	d.srt.idx = orig.d.srt.idx;
	d.srt.inp = orig.d.srt.inp;
	d.srt.min_col = orig.d.srt.min_col;
	d.srt.max_col = orig.d.srt.max_col;
	d.srt.min_grp = orig.d.srt.min_grp;
	d.srt.max_grp = orig.d.srt.max_grp;
}

void bj_sornet_kernel_func(){
	nervenet* my_net = bj_nervenet;
	if(my_net->act_left_side.sync_is_ending){
		kernel::stop_sys(bj_tok_sornet_end);
	}
}

void
nervenet::sornet_handler(missive* msv){
	mck_token_t tmt_tok = msv->tok;
	if(bj_tok_sync_to_children == tmt_tok){
		act_left_side.send_sync_to_children(bj_tok_sync_to_children, BJ_SORNET_TIER, tiki_invalid, mc_null);
		return;
	}

	MC_DBG(sornet_dbg_tests_handler(msv));
}

void bj_sornet_main() {
	mc_workeru_nn_t nn = kernel::get_workeru_nn();
	
	MCK_CK(sizeof(void*) >= sizeof(num_nod_t));

	bj_sornet_init_handlers();

	PTD_LOG("SORNET___ %d \n", nn);

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_sornet_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->init_sync_cycle();

	sornet_transmitter::separate(my_net->tot_sorcells * 2);

	mck_slog2("__dbg2.sornet\n");

	//bj_print_active_cnf(side_left, tiki_invalid, mc_cstr("snt_before"), 3, 0, 
	//	bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	if(nn == 0){
		mini_bit_arr_t max_cntr = 0;
		BJ_DBG_SORBINS(max_cntr = ((((mini_bit_arr_t)1) << BJ_DBG_TOT_INPUT_SORNODES) + 1));
		BJ_DBG_SORNUMS(max_cntr = BJ_DBG_TOT_NUM_TESTS);
		BJ_DBG_RANK_OUTS(max_cntr = BJ_DBG_TOT_RNK_TESTS);
		BJ_DBG_SRT_RNK(max_cntr = BJ_DBG_TOT_SRT_RNK_TESTS);
		
		my_net->dbg_sornet_max_cntr = max_cntr;
		sorkind_t knd = sorkind_invalid;
		BJ_DBG_SORBINS(knd = sorkind_bin);
		BJ_DBG_SORNUMS(knd = sorkind_num);
		BJ_DBG_RANK_OUTS(knd = sorkind_rnk);
		BJ_DBG_SRT_RNK(knd = sorkind_num);
		bj_send_sornet_tmt(my_net, bj_tok_sornet_start, knd, 0, 0, 0, 0, mc_null, my_net, 0);

		PTD_PRT("dbg_sornet_max_cntr=%d\n", max_cntr);
		PTD_LOG("dbg_sornet_max_cntr=%d\n", max_cntr);
	}
	kernel::run_sys();

	//bj_print_active_cnf(side_left, tiki_invalid, mc_cstr("snt_after"), 3, 0, 
	//	bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	PTD_PRT("...............................END_SORNET\n");
	mck_slog2("END_SORNET___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");
	mck_sprt2("dbg2.sornet.end\n");

}

//================================================================================
//================================================================================
// BEGINING_OF_DBG_SORT_CODE
#ifdef FULL_DEBUG
void
nervenet::sornet_dbg_tests_handler(missive* msv){
	PTD_CK(kernel::get_workeru_nn() == 0);
	//PTD_LOG("sornet_dbg_tests_handler 1\n");

	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	sorkind_t tmt_knd = sn_tmt->d.srt.knd;
	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);
	num_nod_t tmt_idx = sn_tmt->d.srt.idx;
	void* tmt_inp = sn_tmt->d.srt.inp;
	num_nod_t tmt_min_col = sn_tmt->d.srt.min_col;
	num_nod_t tmt_max_col = sn_tmt->d.srt.max_col;
	//num_nod_t tmt_min_grp = sn_tmt->d.srt.min_grp;
	//num_nod_t tmt_max_grp = sn_tmt->d.srt.max_grp;

	if(tmt_tok == bj_tok_sornet_start){
		PTD_CK(all_input_sorcells != mc_null);
		bool has_more = sornet_dbg_send_nxt_step(tmt_knd);
		if(! has_more){
			act_left_side.send_sync_to_children(bj_tok_sync_to_children, 
												BJ_SORNET_TIER, tiki_invalid, mc_null);
		}
	}
	if(tmt_tok == bj_tok_sornet_out){
		BJ_DBG_SRT_RNK(PTD_CK(false));
		PTD_CK(tmt_idx < tot_input_sorcells);
		PTD_CK(all_output_sorobjs[tmt_idx] == mc_null);
		all_output_sorobjs[tmt_idx] = tmt_inp;
		PTD_CK(all_output_sorcols[tmt_idx] == 0);
		all_output_sorcols[tmt_idx] = tmt_min_col;

		dbg_tot_rcv_output_sorobjs++;
		if(dbg_tot_rcv_output_sorobjs == tot_input_sorcells){
			sornet_dbg_end_step(tmt_knd);
		}
	}
	if(tmt_tok == bj_tok_sornet_rank_out){
		PTD_CK(tmt_idx < tot_input_rnkcells);

		PTD_CK(all_output_rnk_min_cols[tmt_idx] == BJ_INVALID_SRT_GRP);
		all_output_rnk_min_cols[tmt_idx] = tmt_min_col;
		PTD_CK(all_output_rnk_max_cols[tmt_idx] == BJ_INVALID_SRT_GRP);
		all_output_rnk_max_cols[tmt_idx] = tmt_max_col;
		
		dbg_tot_rcv_output_sorobjs++;
		if(dbg_tot_rcv_output_sorobjs == tot_input_rnkcells){
			sornet_dbg_end_step(tmt_knd);
		}
	}
}

bool
nervenet::sornet_dbg_send_nxt_step(sorkind_t knd){
	PTD_CK(kernel::get_workeru_nn() == 0);
	PTD_CK(all_input_sorcells != mc_null);
	
	dbg_sornet_curr_cntr++;

	if(dbg_sornet_curr_cntr >= dbg_sornet_max_cntr){
		return false;
	}

	BJ_DBG_SORBINS(sornet_dbg_bin_send_step()); 
	BJ_DBG_SORNUMS(sornet_dbg_num_send_step());
	BJ_DBG_RANK_OUTS(sornet_dbg_rnk_send_step());
	BJ_DBG_SRT_RNK(sornet_dbg_num_send_step());

	PTD_LOG("sornet_send_nxt_end %lu\n", dbg_sornet_curr_cntr);

	return true;
}

bool
nervenet::sornet_check_order(sorkind_t knd){
	//PTD_LOG("sornet_check_order_beg\n");
	
	bj_cmp_obj_func_t fn = sornet_get_cmp_func(knd);

	num_nod_t* all_min_grps = all_input_srt_min_grps;
	num_nod_t* all_max_grps = all_input_srt_max_grps;
	
	bool by_grp = false;
	if(knd == sorkind_num){
		PTD_CK(tot_input_sorcells > 0);
		by_grp = (all_min_grps[0] != BJ_INVALID_SRT_GRP);
	}
	
	num_nod_t aa;
	bool sor_ok = true;
	for(aa = 1; aa < tot_input_sorcells; aa++){
		void* o1 = all_output_sorobjs[aa - 1];
		void* o2 = all_output_sorobjs[aa];
		if(by_grp){
			num_nod_t min_0 = all_min_grps[aa - 1];
			MC_MARK_USED(min_0);
			num_nod_t max_0 = all_max_grps[aa - 1];
			MC_MARK_USED(max_0);
			num_nod_t min_1 = all_min_grps[aa];
			MC_MARK_USED(min_1);
			num_nod_t max_1 = all_max_grps[aa];
			MC_MARK_USED(max_1);
			PTD_CK(min_0 <= max_0);
			PTD_CK(min_1 <= max_1);
			if(min_0 != min_1){
				PTD_CK(min_0 < min_1);
				PTD_CK(max_0 < max_1);
				PTD_CK((max_0 + 1) == min_1);
				
				PTD_CK(min_0 == all_min_grps[min_0]);
				PTD_CK(max_0 == (aa - 1));
				PTD_CK(min_1 == aa);
				PTD_CK_PRT((max_1 == all_max_grps[max_1]), "%ld, (%ld == %ld)", 
						   aa, max_1, all_max_grps[max_1]);
				continue;
			}
			PTD_CK(max_0 == max_1);
		}
		int cv = (*fn)(o1, o2);
		if(cv > 0){
			sor_ok = false;
			break;
		}
	}
	return sor_ok;
}

void
nervenet::sornet_dbg_end_step(sorkind_t knd){
	PTD_CK(kernel::get_workeru_nn() == 0);
	
	if(knd != sorkind_rnk){
		bool srt_ok = sornet_check_order(knd);
		if(! srt_ok){
			mck_abort(__LINE__, MC_ABORT_MSG("SORNET_ERROR\n"));
		}
	}
	
	BJ_DBG_SORBINS(sornet_dbg_bin_end_step()); 
	BJ_DBG_SORNUMS(sornet_dbg_num_end_step());
	BJ_DBG_RANK_OUTS(sornet_dbg_rnk_end_step());
	BJ_DBG_SRT_RNK(sornet_dbg_rnk_end_step());
	
	mck_slog2("sorted_ok_arr_");
	mck_ilog(dbg_sornet_curr_cntr);
	mck_slog2("\n");
	mck_sprt2("sorted_ok_arr_");
	mck_iprt(dbg_sornet_curr_cntr);
	mck_sprt2("\n");
	
	mc_init_arr_vals(tot_input_sorcells, all_output_sorobjs, mc_null);
	mc_init_arr_vals(tot_input_sorcells, all_output_sorcols, 0);
	dbg_tot_rcv_output_sorobjs = 0;

	nervenet* my_net = this;
	bj_send_sornet_tmt(my_net, bj_tok_sornet_start, knd, 0, 0, 0, 0, mc_null, my_net, 0);
}

num_nod_t
bj_dbg_sornet_get_nw_grp(ini_grps_prms& prms){
	num_nod_t nxt_grp = 0;
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	num_nod_t tot_inp_objs = prms.tot_input_objs;
	bool* is_inp_grp = prms.is_input_grp;
	
	PTD_CK(is_inp_grp != mc_null);

	tak_mak& gg = *(prms.num_gen);
	bool ending = false;
	nxt_grp = (num_nod_t)gg.gen_rand_int32_ie(0, tot_inp_objs);
	while(true){
		bool is_grp = is_inp_grp[nxt_grp];
		if(! is_grp){
			break;
		}
		nxt_grp++;
		if(nxt_grp == tot_inp_objs){
			nxt_grp = 0;
			
			if(ending){ break; }
			ending = true;
		}
	}
	PTD_CK(nxt_grp >= 0);
	PTD_CK(nxt_grp < tot_inp_objs);
	is_inp_grp[nxt_grp] = true;
	
#endif
	return nxt_grp;
}

num_nod_t
bj_dbg_rnk_get_grp_max(num_nod_t min_idx, num_nod_t grp_sz, ini_grps_prms& prms){
	num_nod_t curr_idx = BJ_INVALID_SRT_GRP;
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	num_nod_t tot_inp_objs = prms.tot_input_objs;
	num_nod_t* all_rnk_grps = prms.all_rnk_grps;
	PTD_CK(prms.is_input_grp == mc_null);
	
	PTD_CK(grp_sz > 0);
	PTD_CK(min_idx >= 0);
	PTD_CK(min_idx < tot_inp_objs);
	PTD_CK(tot_inp_objs > 0);
	
	curr_idx = min_idx;
	num_nod_t num_grp = 0;
	num_nod_t curr_grp = all_rnk_grps[curr_idx];
	for(; curr_idx < tot_inp_objs; curr_idx++){
		if(curr_grp != all_rnk_grps[curr_idx]){
			curr_grp = all_rnk_grps[curr_idx];
			num_grp++;
			if(num_grp >= grp_sz){
				break;
			}
		}
	}
	
	if(curr_idx >= tot_inp_objs){
		curr_idx = tot_inp_objs - 1;
	} else {
		curr_idx--;
	}
	PTD_CK(curr_idx != BJ_INVALID_SRT_GRP);
#endif
	return curr_idx;
}

void
bj_dbg_sornet_init_grp_arr(ini_grps_prms& prms, bool just_ones){
#ifndef MC_IS_PTD_CODE
	mck_abort(1, mc_cstr("Undefined func: bj_dbg_sornet_init_grp_arr"));
#endif
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	PTD_CK(kernel::get_workeru_nn() == 0);
	
	num_nod_t tot_inp_objs = prms.tot_input_objs;
	num_nod_t* all_min_grps = prms.all_min_grps;
	num_nod_t* all_max_grps = prms.all_max_grps;
	num_nod_t* all_rnk_grps = prms.all_rnk_grps;
	bool* is_inp_grp = prms.is_input_grp;
	
	PTD_CK(all_min_grps != mc_null);
	
	tak_mak& gg = *(prms.num_gen);
	
	//unsigned long max_val = tot_inp_objs - 1;
	unsigned long max_grp_sz = BJ_DBG_MAX_GRP_SZ;

	num_nod_t grp_ii = 0;
	num_nod_t grp_sz = 0;
	num_nod_t grp_mn_idx = 0;
	num_nod_t grp_mx_idx = 0;
	
	if(is_inp_grp != mc_null){
		mc_init_arr_vals(tot_inp_objs, is_inp_grp, false);
	}
	
	if(just_ones){
		PTD_CK(tot_inp_objs > 0);
		mc_init_arr_vals(tot_inp_objs, all_min_grps, 1);
		all_min_grps[0] = 0;
		return;
	}

	mc_init_arr_vals(tot_inp_objs, all_min_grps, BJ_INVALID_SRT_GRP);
	if(all_max_grps != mc_null){
		mc_init_arr_vals(tot_inp_objs, all_max_grps, BJ_INVALID_SRT_GRP);
	}
	
	for(num_nod_t aa = 0; aa < tot_inp_objs; aa++){
		if(grp_ii == grp_sz){
			grp_ii = 0;
			grp_sz = (num_nod_t)gg.gen_rand_int32_ie(1, max_grp_sz);
			if(all_max_grps == mc_null){
				grp_mn_idx = bj_dbg_sornet_get_nw_grp(prms);
			} else {
				grp_mn_idx = aa;
				if(all_rnk_grps == mc_null){
					grp_mx_idx = (grp_mn_idx + grp_sz - 1);
					if(grp_mx_idx >= tot_inp_objs){
						grp_mx_idx = (tot_inp_objs - 1);
					}
				} else {
					grp_mx_idx = bj_dbg_rnk_get_grp_max(grp_mn_idx, grp_sz, prms);
					grp_sz = (grp_mx_idx - grp_mn_idx + 1);
				}
				PTD_CK(grp_mn_idx <= grp_mx_idx);
				PTD_CK(grp_mn_idx >= 0);
				PTD_CK(grp_mx_idx >= 0);
				PTD_CK(grp_mn_idx < tot_inp_objs);
				PTD_CK_PRT((grp_mx_idx < tot_inp_objs), "%ld (%ld < %ld)", aa, grp_mx_idx, tot_inp_objs);
			}
		}
		grp_ii++;
		PTD_CK(grp_mn_idx != BJ_INVALID_SRT_GRP);
		all_min_grps[aa] = grp_mn_idx;
		
		if(all_max_grps != mc_null){
			PTD_CK((grp_ii < grp_sz) || (aa == grp_mx_idx));
			all_max_grps[aa] = grp_mx_idx;
		}
	}

#endif
}

#endif
// END_OF_DBG_SORT_CODE
//----------------------------------------------------------------------------------


//================================================================================
//================================================================================
// BEGINING_OF_BIN_SORT_CODE

#ifdef BJ_SORNET_BIN_TEST

#define bj_pt_obj_as_bin(pt_oo) (*((binval_t*)(pt_oo)))

int
bj_cmp_bin_objs(void* obj1, void* obj2){
	binval_t v1 = bj_pt_obj_as_bin(obj1);
	binval_t v2 = bj_pt_obj_as_bin(obj2);
	if(v1 < v2){ return -1; }
	if(v1 > v2){ return 1;}
	return 0;
}

mini_bit_arr_t
nervenet::sornet_dbg_bin_get_mini_sorted_arr(){
	mini_bit_arr_t min_arr = 0;

	PTD_CK(((mini_bit_arr_t)(sizeof(mini_bit_arr_t) * 8)) > ((mini_bit_arr_t)tot_input_sorcells));

	num_nod_t aa;
	for(aa = 0; aa < tot_input_sorcells; aa++){
		void* obj = all_output_sorobjs[aa];
		binval_t vv = bj_pt_obj_as_bin(obj);
		if(vv == binval_top){
			mc_set_bit(&min_arr, aa);
		}
	}
	return min_arr;
}


#if BJ_DBG_TOT_INPUT_SORNODES < 9
#define BJ_SORTED_PATTERN mc_byte_to_binary_pattern
#define BJ_SORTED_DATA mc_byte_to_binary(pt_arr[0])
#else
#define BJ_SORTED_PATTERN mc_byte_to_binary_pattern mc_byte_to_binary_pattern
#define BJ_SORTED_DATA mc_byte_to_binary(pt_arr[1]), mc_byte_to_binary(pt_arr[0])
#endif

void
nervenet::sornet_dbg_bin_end_step(){
	PTD_CK(kernel::get_workeru_nn() == 0);

	mini_bit_arr_t min_arr = sornet_dbg_bin_get_mini_sorted_arr();
	char* pt_arr = (char*)(&min_arr);
	MC_MARK_USED(pt_arr);
	PTD_PRT("SORTED_OK_ARR_%d_" BJ_SORTED_PATTERN "\n", dbg_sornet_curr_cntr, BJ_SORTED_DATA);
	PTD_LOG("SORTED_OK_ARR_%d_" BJ_SORTED_PATTERN "\n", dbg_sornet_curr_cntr, BJ_SORTED_DATA);
}

void
nervenet::sornet_dbg_bin_send_step(){
	mini_bit_arr_t tmp_num = dbg_sornet_curr_cntr;

	cell* src = this;

	PTD_CK(((mini_bit_arr_t)(sizeof(mini_bit_arr_t) * 8)) > ((mini_bit_arr_t)tot_input_sorcells));
	PTD_LOG("send_cntr counter=%d tot_inp=%d sizeof(mini_bit_arr_t)=%d \n", 
			tmp_num, tot_input_sorcells, sizeof(mini_bit_arr_t));

	num_nod_t mn_idx = 0;
	num_nod_t mx_idx = tot_input_sorcells - 1;
	
	num_nod_t aa;
	for(aa = 0; aa < tot_input_sorcells; aa++){
		bool vv = mc_get_bit(&tmp_num, aa);
		//PTD_LOG("send_cntr vv=%d \n", vv);

		sorcell* srcll = all_input_sorcells[aa];
		PTD_CK(srcll != mc_null);

		void* obj = mc_null;
		if(vv){
			obj = mck_as_glb_pt(&net_top);
		} else {
			obj = mck_as_glb_pt(&net_bottom);
		}
		PTD_CK(obj != mc_null);
		PTD_CK(srcll != mc_null);
		PTD_CK(src != mc_null);

		bj_send_sornet_tmt(src, bj_tok_sornet_bin, sorkind_bin, aa, aa, mn_idx, mx_idx, obj, srcll, aa);
	}
}

#endif
// END_OF_BIN_SORT_CODE
//----------------------------------------------------------------------------------



//================================================================================
//================================================================================
// BEGINING_OF_RANK_OUTS_CODE

#if (defined(BJ_SORNET_RANK_TEST) || defined(BJ_SORNET_SRT_RNK_TEST))

void
nervenet::sornet_dbg_rnk_send_step(){
	//act_left_side.send_sync_to_children(bj_tok_sync_to_children, 
	//									BJ_SORNET_TIER, tiki_invalid, mc_null);
	//PTD_LOG("_RNK_RECODING_THIS_FUNC () \n");
	
	PTD_CK(kernel::get_workeru_nn() == 0);
	cell* src = this;

	PTD_LOG("send_cntr counter=%d tot_outs=%d \n", dbg_sornet_curr_cntr, tot_input_rnkcells);
	
	PTD_CK(all_input_rnkcells != mc_null);
	
	mc_init_arr_vals(tot_input_rnkcells, all_output_rnk_min_cols, BJ_INVALID_SRT_GRP);
	mc_init_arr_vals(tot_input_rnkcells, all_output_rnk_max_cols, BJ_INVALID_SRT_GRP);
	
	ini_grps_prms prms;
	PTD_DBG_CODE(prms.num_gen = &dbg_random_gen);
	prms.tot_input_objs = tot_input_rnkcells;
	prms.all_min_grps = all_input_rnkgrps;
	prms.all_max_grps = mc_null;
	prms.is_input_grp = dbg_is_input_rnkgrps;
	
	bj_dbg_sornet_init_grp_arr(prms, false);

	BJ_DBG_GRPS_RANK(
		PTD_DBG_CODE(prms.num_gen = &dbg_random_gen);
		prms.tot_input_objs = tot_input_rnkcells;
		prms.all_min_grps = all_input_rnk_min_grps;
		prms.all_max_grps = all_input_rnk_max_grps;
		prms.all_rnk_grps = all_input_rnkgrps;
		prms.is_input_grp = mc_null;
		
		bj_dbg_sornet_init_grp_arr(prms, false);
		
		PTD_CK(tot_input_rnkcells > 0);
		PTD_CK(all_input_rnk_min_grps[0] != BJ_INVALID_SRT_GRP);
		
		sornet_dbg_rnk_print_input();
	);
	
	num_nod_t mn_idx = 0;
	num_nod_t mx_idx = tot_input_rnkcells - 1;
	
	num_nod_t aa;
	for(aa = 0; aa < tot_input_rnkcells; aa++){
		sorcell* srout = all_input_rnkcells[aa];
		PTD_CK(srout != mc_null);

		//void* obj = (void*)(&(all_input_rnkgrps[aa]));
		void* obj = bj_num_to_pt(all_input_rnkgrps[aa]);	// RNK_OBJ_NUM
		PTD_CK(obj != BJ_INVALID_RNK_OBJ);
		
		BJ_DBG_GRPS_RANK(
			mn_idx = all_input_rnk_min_grps[aa];
			mx_idx = all_input_rnk_max_grps[aa];
		);
		
		bj_send_sornet_tmt(src, bj_tok_sornet_rank_start, 
						   sorkind_rnk, aa, aa, mn_idx, mx_idx, obj, srout, aa);
	}
}

void
nervenet::sornet_dbg_rnk_end_step(){
#ifndef MC_IS_PTD_CODE
	mck_abort(1, mc_cstr("Undefined func: nervenet::sornet_dbg_rnk_end_step"));
#endif
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	PTD_CK(kernel::get_workeru_nn() == 0);

	PTD_PRINTF("IDXS=[");
	num_nod_t aa;
	for(aa = 0; aa < tot_input_rnkcells; aa++){
		PTD_PRINTF("%ld ", aa);
		if(aa > 0){
			BJ_DBG_RANK_OUTS(num_nod_t grp_0 = all_input_rnkgrps[aa - 1]);
			BJ_DBG_RANK_OUTS(num_nod_t grp_1 = all_input_rnkgrps[aa]);
			BJ_DBG_SRT_RNK(PTD_CK(all_srt_endcells[aa - 1] != mc_null));
			BJ_DBG_SRT_RNK(PTD_CK(all_srt_endcells[aa] != mc_null));
			BJ_DBG_SRT_RNK(num_nod_t grp_0 = all_srt_endcells[aa - 1]->end_snp.min_grp);
			BJ_DBG_SRT_RNK(num_nod_t grp_1 = all_srt_endcells[aa]->end_snp.min_grp);
			num_nod_t min_0 = all_output_rnk_min_cols[aa - 1];
			num_nod_t min_1 = all_output_rnk_min_cols[aa];
			num_nod_t max_0 = all_output_rnk_max_cols[aa - 1];
			num_nod_t max_1 = all_output_rnk_max_cols[aa];

			PTD_CK(min_0 <= max_0);
			PTD_CK(min_1 <= max_1);
			if(grp_0 == grp_1){
				PTD_CK(min_0 == min_1);
				PTD_CK(max_0 == max_1);
			} else {
				PTD_CK(min_0 < min_1);
				PTD_CK(max_0 < max_1);
				PTD_CK((max_0 + 1) == min_1);
				
				PTD_CK(min_0 == all_output_rnk_min_cols[min_0]);
				PTD_CK(max_0 == (aa - 1));
				PTD_CK(min_1 == aa);
				PTD_CK(max_1 == all_output_rnk_max_cols[max_1]);
			}
		}
	}
	PTD_PRINTF("]\n");
	PTD_PRINTF("GRPS=[");
	for(aa = 0; aa < tot_input_rnkcells; aa++){
		PTD_PRINTF("%ld ", all_input_rnkgrps[aa]);
	}
	PTD_PRINTF("]\n");
	
	PTD_PRINTF("MINS=[");
	for(aa = 0; aa < tot_input_rnkcells; aa++){
		PTD_PRINTF("%ld ", all_output_rnk_min_cols[aa]);
	}
	PTD_PRINTF("]\n");
	PTD_PRINTF("MAXS=[");
	for(aa = 0; aa < tot_input_rnkcells; aa++){
		PTD_PRINTF("%ld ", all_output_rnk_max_cols[aa]);
	}
	PTD_PRINTF("]\n");
#endif
}

void
nervenet::sornet_dbg_rnk_print_input(){
#ifndef MC_IS_PTD_CODE
	mck_abort(1, mc_cstr("Undefined func: nervenet::sornet_dbg_rnk_print_input"));
#endif
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	num_nod_t aa;
	printf("GRPS=[");
	for(aa = 0; aa < tot_input_rnkcells; aa++){
		printf("%ld ", all_input_rnkgrps[aa]);
	}
	printf("]\n");
	printf("MINS=[");
	for(aa = 0; aa < tot_input_rnkcells; aa++){
		printf("%ld ", all_input_rnk_min_grps[aa]);
	}
	printf("]\n");
	printf("MAXS=[");
	for(aa = 0; aa < tot_input_rnkcells; aa++){
		printf("%ld ", all_input_rnk_max_grps[aa]);
	}
	printf("]\n");
	printf("SIZE=%ld \n", tot_input_rnkcells);
#endif
}

#endif
// END_OF_RANK_OUTS_CODE
//----------------------------------------------------------------------------------

//================================================================================
//================================================================================
// BEGINING_OF_NUM_SORT_CODE

#if (defined(BJ_SORNET_NUM_TEST) || defined(BJ_SORNET_SRT_RNK_TEST))

int
bj_cmp_num_objs(void* obj1, void* obj2){
	num_nod_t v1 = bj_pt_obj_as_num(obj1);
	num_nod_t v2 = bj_pt_obj_as_num(obj2);
	if(v1 < v2){ return -1; }
	if(v1 > v2){ return 1;}
	return 0;
}

void
nervenet::sornet_dbg_num_init_val_arr(){
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	//unsigned long init_val = 10;
	//tak_mak gg(init_val);
	tak_mak& gg = dbg_random_gen;
	
	if(dbg_sornet_curr_cntr == 1){
		PTD_CK(dbg_all_input_vals == mc_null);
		dbg_all_input_vals = mc_malloc32(num_nod_t, tot_input_sorcells);
	}
	
	unsigned long max_val = 2 * tot_input_sorcells;
	
	PTD_CK(dbg_all_input_vals != mc_null);
	mc_init_arr_vals(tot_input_sorcells, dbg_all_input_vals, 0);

	for(num_nod_t aa = 0; aa < tot_input_sorcells; aa++){
		num_nod_t val = (num_nod_t)gg.gen_rand_int32_ie(1, max_val);
		dbg_all_input_vals[aa] = val;
		
		if((aa + 1) == tot_input_sorcells){ continue; }
		
		num_nod_t num_rep = (num_nod_t)gg.gen_rand_int32_ie(0, 10);
		for(num_nod_t bb = 0; bb < num_rep; bb++){
			num_nod_t pos = (num_nod_t)gg.gen_rand_int32_ie(aa + 1, tot_input_sorcells);
			PTD_CK_PRT((pos < tot_input_sorcells), "%ld  < %ld \n", pos, tot_input_sorcells);
			val = (num_nod_t)gg.gen_rand_int32_ie(1, max_val);
			if(dbg_all_input_vals[pos] != 0){
				continue;
			}
			dbg_all_input_vals[pos] = val;
		}
	}
#endif
}

void
nervenet::sornet_dbg_num_send_step(){
	cell* src = this;

	PTD_LOG("send_cntr counter=%d tot_inp=%d \n", dbg_sornet_curr_cntr, tot_input_sorcells);
	
	BJ_DBG_SRT_RNK(PTD_CK(tot_input_rnkcells == tot_input_sorcells));
	BJ_DBG_SRT_RNK(mc_init_arr_vals(tot_input_rnkcells, all_output_rnk_min_cols, BJ_INVALID_SRT_GRP));
	BJ_DBG_SRT_RNK(mc_init_arr_vals(tot_input_rnkcells, all_output_rnk_max_cols, BJ_INVALID_SRT_GRP));

	sornet_dbg_num_init_val_arr();
	
	BJ_DBG_GRPS_SORNUMS(
		ini_grps_prms prms;
		PTD_DBG_CODE(prms.num_gen = &dbg_random_gen);
		prms.tot_input_objs = tot_input_sorcells;
		prms.all_min_grps = all_input_srt_min_grps;
		prms.all_max_grps = all_input_srt_max_grps;
		prms.is_input_grp = mc_null;
		
		bj_dbg_sornet_init_grp_arr(prms, false);
		
		PTD_CK(tot_input_sorcells > 0);
		PTD_CK(all_input_srt_min_grps[0] != BJ_INVALID_SRT_GRP);
		
		sornet_dbg_num_print_input();
	);

	PTD_CK(dbg_all_input_vals != mc_null);
	
	num_nod_t mn_idx = 0;
	num_nod_t mx_idx = tot_input_sorcells - 1;
	
	num_nod_t aa;
	for(aa = 0; aa < tot_input_sorcells; aa++){
		//PTD_LOG("send_cntr vv=%d \n", vv);
		PTD_CK(dbg_all_input_vals[aa] != 0);

		sorcell* srcll = all_input_sorcells[aa];
		PTD_CK(srcll != mc_null);

		void* obj = (void*)(&(dbg_all_input_vals[aa]));
		PTD_CK(obj != mc_null);
		PTD_CK(srcll != mc_null);
		PTD_CK(src != mc_null);

		BJ_DBG_GRPS_SORNUMS(
			mn_idx = all_input_srt_min_grps[aa];
			mx_idx = all_input_srt_max_grps[aa];
		);
		
		bj_send_sornet_tmt(src, bj_tok_sornet_num, sorkind_num, aa, aa, mn_idx, mx_idx, obj, srcll, aa);
	}
}

void
nervenet::sornet_dbg_num_print_input(){
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	printf("INPUT=[");
	num_nod_t aa;
	for(aa = 0; aa < tot_input_sorcells; aa++){
		num_nod_t vv = dbg_all_input_vals[aa];
		printf("%ld ", vv);
	}
	printf("]\n");
	printf("MINS=[");
	for(aa = 0; aa < tot_input_sorcells; aa++){
		printf("%ld ", all_input_srt_min_grps[aa]);
	}
	printf("]\n");
	printf("MAXS=[");
	for(aa = 0; aa < tot_input_sorcells; aa++){
		printf("%ld ", all_input_srt_max_grps[aa]);
	}
	printf("]\n");
	printf("SIZE=%ld \n", tot_input_sorcells);
#endif
}

void
nervenet::sornet_dbg_num_end_step(){
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	PTD_CK(kernel::get_workeru_nn() == 0);

	printf("SORTED=[");
	num_nod_t aa;
	for(aa = 0; aa < tot_input_sorcells; aa++){
		void* obj = all_output_sorobjs[aa];
		num_nod_t vv = bj_pt_obj_as_num(obj);
		printf("%ld ", vv);
		if(aa > 0){
			void* obj_prv = all_output_sorobjs[aa - 1];
			num_nod_t vv_prv = bj_pt_obj_as_num(obj_prv);
			num_nod_t col_0 = all_output_sorcols[aa - 1];
			num_nod_t col_1 = all_output_sorcols[aa];
			num_nod_t grp_0 = all_input_srt_min_grps[aa - 1];
			num_nod_t grp_1 = all_input_srt_min_grps[aa];

			PTD_CK_PRT(((aa == 0) || (((vv_prv == vv) && (grp_0 == grp_1)) ? 
										(col_0 == col_1) : (col_0 != col_1))),
				"(%ld == %ld)? %ld %ld \n", vv_prv, vv, col_0, col_1);
		}
	}
	printf("]\n");
	printf("COLORS=[");
	for(aa = 0; aa < tot_input_sorcells; aa++){
		printf("%ld ", all_output_sorcols[aa]);
	}
	printf("]\n");
#endif
}

#endif
// END_OF_NUM_SORT_CODE
//----------------------------------------------------------------------------------


int
bj_cmp_rnk_objs(void* obj1, void* obj2){
	//num_nod_t v1 = bj_pt_obj_as_num(obj1);
	//num_nod_t v2 = bj_pt_obj_as_num(obj2);
	num_nod_t v1 = bj_pt_to_num(obj1); // RNK_OBJ_NUM
	num_nod_t v2 = bj_pt_to_num(obj2); // RNK_OBJ_NUM
	if(v1 < v2){ return -1; }
	if(v1 > v2){ return 1;}
	return 0;
}

bool
sorcell::is_up_direct(void* invalid_val){
	if((up_snp.inp != invalid_val) && ! bj_idx_inside(down_snp.idx, up_snp.min_grp, up_snp.max_grp)){
		PTD_CK(down_snp.inp == invalid_val);
		return true;
	}
	return false;
}

bool
sorcell::is_down_direct(void* invalid_val){
	if((down_snp.inp != invalid_val) && ! bj_idx_inside(up_snp.idx, down_snp.min_grp, down_snp.max_grp)){
		PTD_CK(up_snp.inp == invalid_val);
		return true;
	}
	return false;
}

void
sorcell::sornet_handle_direct(sornet_transmitter* sn_tmt, void* invalid_val){
	sorkind_t tmt_knd = sn_tmt->d.srt.knd;
	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);

	sorcell* src = this;
	sorcell* up_dst = up_snp.out;
	sorcell* down_dst = down_snp.out;
	
	if(is_up_direct(invalid_val)){
		bool is_end = mc_get_flag(edge_flags, bj_rnk_up_end_flag);
		if(up_snp.jump_to_end(tmt_knd, srt_sz, is_end)){
			up_dst = mc_null; 
		}
		
		bj_send_sornet_tmt(src, tmt_tok, tmt_knd, up_snp.min_col, up_snp.max_col, 
						   up_snp.min_grp, up_snp.max_grp, 
							up_snp.inp, up_dst, up_snp.idx, up_snp.axon); // can_be_end
		sornet_reset(invalid_val);
		return;
	}

	if(is_down_direct(invalid_val)){
		bool is_end = mc_get_flag(edge_flags, bj_rnk_down_end_flag);
		if(down_snp.jump_to_end(tmt_knd, srt_sz, is_end)){
			down_dst = mc_null; 
		}
		
		bj_send_sornet_tmt(src, tmt_tok, tmt_knd, down_snp.min_col, down_snp.max_col, 
						   down_snp.min_grp, down_snp.max_grp, 
							down_snp.inp, down_dst, down_snp.idx, down_snp.axon); // can_be_end
		sornet_reset(invalid_val);
		return;
	}	
}

void
sorcell::sornet_srt_handler(sornet_transmitter* sn_tmt){
	sorkind_t tmt_knd = sn_tmt->d.srt.knd;
	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);
	void* invalid_val = BJ_INVALID_SRT_OBJ;
	
	sornet_set_fields(sn_tmt, invalid_val);
	sornet_handle_direct(sn_tmt, invalid_val);
	
	sorcell* src = this;
	sorcell* up_dst = up_snp.out;
	sorcell* down_dst = down_snp.out;
	
	bj_cmp_obj_func_t fn = sornet_get_cmp_func(tmt_knd);
	PTD_CK(fn != mc_null);

	if((up_snp.inp != invalid_val) && (down_snp.inp != invalid_val)){
		PTD_CK(up_snp.min_grp == down_snp.min_grp);
		PTD_CK(up_snp.max_grp == down_snp.max_grp);
		
		if(up_snp.jump_to_srt_end(srt_sz)){
			up_dst = mc_null;
			down_dst = mc_null;
		}
		
		int cv = (*fn)(up_snp.inp, down_snp.inp);
		if(cv < 0){
			bj_send_sornet_tmt(src, tmt_tok, tmt_knd, up_snp.min_col, up_snp.max_col, 
							   up_snp.min_grp, up_snp.max_grp, 
							   up_snp.inp, up_dst, up_snp.idx, up_snp.axon); // can_be_end
			bj_send_sornet_tmt(src, tmt_tok, tmt_knd, down_snp.min_col, down_snp.max_col, 
							   down_snp.min_grp, down_snp.max_grp, 
							   down_snp.inp, down_dst, down_snp.idx, down_snp.axon); // can_be_end
		} else {
			if(cv == 0){
				calc_color();
			}
			bj_send_sornet_tmt(src, tmt_tok, tmt_knd, up_snp.min_col, up_snp.max_col, 
							   up_snp.min_grp, up_snp.max_grp, 
							   up_snp.inp, down_dst, down_snp.idx, down_snp.axon); // can_be_end
			bj_send_sornet_tmt(src, tmt_tok, tmt_knd, down_snp.min_col, down_snp.max_col, 
							   down_snp.min_grp, down_snp.max_grp, 
							   down_snp.inp, up_dst, up_snp.idx, up_snp.axon); // can_be_end
		}

		sornet_reset(invalid_val);
		//PTD_LOG("SCELL (%d %d) fired\n", up_snp.idx, down_snp.idx);
	}
}

void
sorcell::sornet_rnk_handler(sornet_transmitter* sn_tmt){
	sorkind_t tmt_knd = sn_tmt->d.srt.knd;
	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);
	void* invalid_val = BJ_INVALID_RNK_OBJ;

	sornet_set_fields(sn_tmt, invalid_val);
	sornet_handle_direct(sn_tmt, invalid_val);
	
	sorcell* src = this;
	sorcell* up_dst = up_snp.out;
	sorcell* down_dst = down_snp.out;
	
	if((up_snp.inp != invalid_val) && (down_snp.inp != invalid_val)){
		PTD_CK(up_snp.min_grp == down_snp.min_grp);
		PTD_CK(up_snp.max_grp == down_snp.max_grp);
		
		bool is_up_end = mc_get_flag(edge_flags, bj_rnk_up_end_flag);
		if(up_snp.jump_to_rnk_end(srt_sz, is_up_end)){
			up_dst = mc_null;
		}
		bool is_dw_end = mc_get_flag(edge_flags, bj_rnk_down_end_flag);
		if(down_snp.jump_to_rnk_end(srt_sz, is_dw_end)){
			down_dst = mc_null;
		}
		
		int cv = bj_cmp_rnk_objs(up_snp.inp, down_snp.inp);
		if(cv == 0){
			calc_color();
		}
		
		bj_send_sornet_tmt(src, tmt_tok, tmt_knd, up_snp.min_col, up_snp.max_col, 
						   up_snp.min_grp, up_snp.max_grp, 
						   up_snp.inp, up_dst, up_snp.idx, up_snp.axon); // can_be_end
		bj_send_sornet_tmt(src, tmt_tok, tmt_knd, down_snp.min_col, down_snp.max_col, 
						   down_snp.min_grp, down_snp.max_grp, 
						   down_snp.inp, down_dst, down_snp.idx, down_snp.axon); // can_be_end

		sornet_reset(invalid_val);
		//PTD_LOG("SCELL (%d %d) fired\n", up_snp.idx, down_snp.idx);
	}
}

bool
sornapse::jump_to_end(sorkind_t knd, num_nod_t srt_sz, bool is_end){
	bool rsp = false;
	switch(knd){
		case sorkind_bin:
		case sorkind_num:
			rsp = jump_to_srt_end(srt_sz);
		break;
		case sorkind_rnk:
			rsp = jump_to_rnk_end(srt_sz, is_end);
		break;
		default:
			mck_abort(1, mc_cstr("Invalid sornet_tok_t (sornapse::jump_to_end)"));
		break;
	}
	return rsp;
}

bool
sornapse::jump_to_srt_end(num_nod_t srt_sz){
	PTD_CK(min_grp >= 0);
	PTD_CK(max_grp >= 0);
	u_num_nod_t mn = min_grp;
	u_num_nod_t mx = max_grp;
	u_num_nod_t bi_xor = mn ^ mx;
	u_num_nod_t num_bits = sizeof(u_num_nod_t) * 8;
	bool got_zero = false;
	num_nod_t aa = 0;
	for(aa = num_bits - 1; aa >= 0; aa--){
		bool is_zero = (bi_xor >> aa);
		if(is_zero){
			PTD_CK(mc_get_bit(&bi_xor, aa));
			got_zero = true;
			break;
		}
		PTD_CK(! mc_get_bit(&bi_xor, aa));
	}
	u_num_nod_t out_sz = 2;
	if(got_zero && (aa >= 0) && (aa < ((num_nod_t)(num_bits - 1)) )){
		out_sz = 0;
		out_sz = mc_set_bit(&out_sz, aa + 1);
	} 
	bool rsp = (((num_nod_t)out_sz) == srt_sz);
	return rsp;
}

bool
sornapse::jump_to_rnk_end(num_nod_t srt_sz, bool is_end){
	if(is_end){
		num_nod_t nxt_jmp_sz = srt_sz * 2;
		PTD_CK(idx >= 0);
		PTD_CK(nxt_jmp_sz > 0);
		PTD_CK(min_grp >= 0);
		PTD_CK(max_grp >= 0);
		PTD_CK(min_grp <= max_grp);
		
		bool up_in = bj_idx_inside(idx + nxt_jmp_sz, min_grp, max_grp);
		bool down_in = bj_idx_inside(idx - nxt_jmp_sz, min_grp, max_grp);
		if(! up_in && ! down_in){
			return true;
		}
	}
	return false;
}

void
endcell::sornet_handler(missive* msv){
	BJ_DBG_SORBINS(return);
	BJ_DBG_SORNUMS(return);
	BJ_DBG_RANK_OUTS(return);
	
	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	sorkind_t tmt_knd = sn_tmt->d.srt.knd;
	switch(tmt_knd){
		case sorkind_bin:
		case sorkind_num:
			sornet_srt_handler(sn_tmt);
			break;
		case sorkind_rnk:
			sornet_rnk_handler(sn_tmt);
			break;
		default:
			mck_abort(1, mc_cstr("Invalid sorkind (endcell::sornet_handler)"));
		break;
	}
	//PTD_LOG("ECLL_%d RCV\n", end_snp.idx);
}

void
endcell::sornet_srt_handler(sornet_transmitter* sn_tmt){
	PTD_CK(((sornet_tok_t)(sn_tmt->tok)) == bj_tok_sornet_out);
	PTD_CK(sn_tmt->d.srt.idx == end_snp.idx);

	PTD_CK(end_snp.min_col == BJ_INVALID_SRT_GRP);
	PTD_CK(end_snp.max_col == BJ_INVALID_SRT_GRP);
	//PTD_CK(end_snp.min_grp == BJ_INVALID_SRT_GRP);
	PTD_CK(end_snp.max_grp == BJ_INVALID_SRT_GRP);
	
	cell* src = this;
	PTD_CK(end_snp.axon != mc_null);
	bj_send_sornet_tmt(src, bj_tok_sornet_rank_obj, sorkind_rnk, BJ_INVALID_SRT_GRP, BJ_INVALID_SRT_GRP, 
					BJ_INVALID_SRT_GRP, BJ_INVALID_SRT_GRP, 
					sn_tmt->d.srt.inp, end_snp.axon, end_snp.idx);
	
	num_nod_t obj_val = sn_tmt->d.srt.min_col;
	
	end_snp.min_grp = obj_val;

	PTD_CK(obj_val != BJ_INVALID_SRT_GRP);
	void* obj = bj_num_to_pt(obj_val);
	PTD_CK(obj != BJ_INVALID_RNK_OBJ);
	
	num_nod_t aa = end_snp.idx;
	
	PTD_CK(end_snp.out != mc_null);
	bj_send_sornet_tmt(src, bj_tok_sornet_rank_start, 
					sorkind_rnk, aa, aa, sn_tmt->d.srt.min_grp, sn_tmt->d.srt.max_grp, 
					obj, end_snp.out, aa); 
	
}

void
endcell::sornet_rnk_handler(sornet_transmitter* sn_tmt){
	BJ_DBG_SRT_RNK(return);

	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);
	
	PTD_CK(sn_tmt->d.srt.idx == end_snp.idx);
	switch(tmt_tok){
		case bj_tok_sornet_rank_out:
			PTD_CK(sn_tmt->d.srt.inp == mc_null);
			end_snp.set_snp_fields(sn_tmt, false);
		break;
		case bj_tok_sornet_rank_obj:
		{
			void* tmt_inp = sn_tmt->d.srt.inp;
			PTD_CK(end_snp.inp == mc_null);
			PTD_CK(tmt_inp != mc_null);
			end_snp.inp = tmt_inp;
		}
		break;
		default:
			mck_abort(1, mc_cstr("Invalid sorkind (endcell::sornet_rnk_handler)"));
		break;
	}
	
	if((end_snp.inp != mc_null) && (end_snp.min_col != BJ_INVALID_SRT_GRP)){
		cell* src = this;
		cell* dst = (cell*)(end_snp.inp);
		// send end_snp out, idx, col and grp fields to inp.
		bj_send_sornet_tmt(src, bj_tok_sornet_rank_out, sorkind_rnk, end_snp.min_col, end_snp.max_col, 
						end_snp.min_grp, end_snp.max_grp, 
						end_snp.out, dst, end_snp.idx);
		end_snp.reset(mc_null);
	}
}

