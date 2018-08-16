
#include "cell.hh"
#include "sornet.hh"

#define BJ_SORNET_TIER 0

//define BJ_SORNET_BIN_TEST
//define BJ_SORNET_NUM_TEST
#define BJ_SORNET_RANK_TEST

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

#ifdef BJ_SORNET_RANK_TEST
#define BJ_DBG_RANK_OUTS(prm) prm
#else
#define BJ_DBG_RANK_OUTS(prm) 
#endif

#define bj_sorout_idx(pt_sout) ((pt_sout != mc_null)?(pt_sout->idx):(-1))

void 
sorcell_sornet_handler(missive* msv){
	MCK_CALL_HANDLER(sorcell, sornet_handler, msv);
}

void 
sorout_sornet_handler(missive* msv){
	MCK_CALL_HANDLER(sorout, sornet_handler, msv);
}

void 
nervenet_sornet_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, sornet_handler, msv);
}


void bj_sornet_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_sorcell] = sorcell_sornet_handler;
	hndlrs[idx_sorout] = sorout_sornet_handler;
	hndlrs[idx_nervenet] = nervenet_sornet_handler;

	kernel::set_handlers(idx_total, hndlrs);
}


bj_cmp_obj_func_t
sornet_get_cmp_func(sorkind_t knd){
	bj_cmp_obj_func_t fn = mc_null;
	switch(knd){
		case sorkind_bin:
			BJ_DBG_SORBINS(fn = &bj_cmp_bin_objs);
		break;
		case sorkind_num:
			BJ_DBG_SORNUMS(fn = &bj_cmp_num_objs);
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
	sorkind_t tmt_knd = sn_tmt->knd;
	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);
	num_nod_t tmt_idx = sn_tmt->idx;
	void* tmt_obj = sn_tmt->obj;
	num_nod_t tmt_grp_idx = sn_tmt->grp_idx;

	bj_cmp_obj_func_t fn = sornet_get_cmp_func(tmt_knd);
	PTD_CK(fn != mc_null);

	if(tmt_idx == up_idx){
		PTD_CK(up_inp == mc_null);
		up_inp = tmt_obj;
		up_grp_idx = tmt_grp_idx;
	}
	if(tmt_idx == down_idx){
		PTD_CK(down_inp == mc_null);
		down_inp = tmt_obj;
		down_grp_idx = tmt_grp_idx;
	}

	cell* src = this;
	if((up_inp != mc_null) && (down_inp != mc_null)){
		//int cv = bj_cmp_bin_objs(up_inp, down_inp);
		int cv = (*fn)(up_inp, down_inp);
		if(cv < 0){
			bj_send_sornet_tmt(src, tmt_tok, tmt_knd, up_grp_idx, up_inp, up_out, up_idx);
			bj_send_sornet_tmt(src, tmt_tok, tmt_knd, down_grp_idx, down_inp, down_out, down_idx);
		} else {
			if(cv == 0){
				num_nod_t min_grp = mc_min(up_grp_idx, down_grp_idx);
				up_grp_idx = min_grp;
				down_grp_idx = min_grp;
			}
			bj_send_sornet_tmt(src, tmt_tok, tmt_knd, up_grp_idx, up_inp, down_out, down_idx);
			bj_send_sornet_tmt(src, tmt_tok, tmt_knd, down_grp_idx, down_inp, up_out, up_idx);
		}

		up_inp = mc_null;
		down_inp = mc_null;

		//PTD_LOG("SCELL %d(%d %d) fired\n", dbg_level, up_idx, down_idx);
	}
}


void
bj_send_sornet_tmt(cell* src, sornet_tok_t tok, sorkind_t knd, num_nod_t grp_idx,
				   void* obj, cell* dst, num_nod_t idx)
{
	PTD_CK(src != mc_null);
	PTD_CK_PRT(((knd == sorkind_rnk) || (obj != mc_null) || (tok == bj_tok_sornet_start)), 
			   "KIND=%d \n", knd);
	PTD_CK(knd != sorkind_invalid);

	sornet_transmitter* trm = sornet_transmitter::acquire();
	trm->wrk_side = side_left;

	trm->src = src;
	trm->dst = dst;
	trm->knd = knd;
	trm->tok = tok;
	trm->idx = idx;
	trm->obj = obj;
	trm->grp_idx = grp_idx;

	if(trm->dst == mc_null){
		nervenet* root_net = bj_nervenet->get_nervenet(mc_nn_to_id(0));
		trm->dst = root_net;
		switch(knd){
			case sorkind_bin:
			case sorkind_num:
				trm->tok = bj_tok_sornet_out;
				break;
			case sorkind_rnk:
				trm->tok = bj_tok_sornet_rank_out;
				break;
			default:
				mck_abort(1, mc_cstr("Invalid sorkind (bj_send_sornet_tmt)"));
				break;
		}
	}

	trm->send();
}

bool
nervenet::sornet_check_order(bj_cmp_obj_func_t fn){
	//PTD_LOG("sornet_check_order_beg\n");

	num_nod_t aa;
	bool sor_ok = true;
	for(aa = 1; aa < tot_input_sorcells; aa++){
		void* o1 = all_output_sorobjs[aa - 1];
		void* o2 = all_output_sorobjs[aa];
		int cv = (*fn)(o1, o2);
		if(cv > 0){
			sor_ok = false;
			break;
		}
	}
	return sor_ok;
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

	kernel::set_handlers(1, bj_nil_handlers);
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
		mini_bit_arr_t max_cntr = (((mini_bit_arr_t)1) << BJ_DBG_TOT_INPUT_SORNODES) + 1;
		BJ_DBG_RANK_OUTS(max_cntr = BJ_DBG_TOT_OUTPUT_TESTS);
		
		my_net->dbg_sornet_max_cntr = max_cntr;
		sorkind_t knd = sorkind_invalid;
		BJ_DBG_SORBINS(knd = sorkind_bin);
		BJ_DBG_SORNUMS(knd = sorkind_num);
		BJ_DBG_RANK_OUTS(knd = sorkind_rnk);
		bj_send_sornet_tmt(my_net, bj_tok_sornet_start, knd, 0, mc_null, my_net, 0);

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
	sorkind_t tmt_knd = sn_tmt->knd;
	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);
	num_nod_t tmt_idx = sn_tmt->idx;
	void* tmt_obj = sn_tmt->obj;
	num_nod_t tmt_grp_idx = sn_tmt->grp_idx;

	if(tmt_tok == bj_tok_sornet_start){
		bool has_more = sornet_dbg_send_nxt_step(tmt_knd);
		if(! has_more){
			act_left_side.send_sync_to_children(bj_tok_sync_to_children, 
												BJ_SORNET_TIER, tiki_invalid, mc_null);
		}
	}
	if(tmt_tok == bj_tok_sornet_out){
		PTD_CK(tmt_idx < tot_input_sorcells);
		PTD_CK(all_output_sorobjs[tmt_idx] == mc_null);
		all_output_sorobjs[tmt_idx] = tmt_obj;
		PTD_CK(all_output_sorgrps[tmt_idx] == 0);
		all_output_sorgrps[tmt_idx] = tmt_grp_idx;

		dbg_tot_rcv_output_sorobjs++;
		if(dbg_tot_rcv_output_sorobjs == tot_input_sorcells){
			sornet_dbg_end_step(tmt_knd);
		}
	}
	if(tmt_tok == bj_tok_sornet_rank_out){
		PTD_CK(tmt_idx < tot_arr_sorouts);

		dbg_tot_rcv_output_sorobjs++;
		if(dbg_tot_rcv_output_sorobjs == tot_arr_sorouts){
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

	switch(knd){
		case sorkind_bin:
			BJ_DBG_SORBINS(sornet_dbg_bin_send_step()); 
		break;
		case sorkind_num:
			BJ_DBG_SORNUMS(sornet_dbg_num_send_step());
		break;
		case sorkind_rnk:
			BJ_DBG_RANK_OUTS(sornet_dbg_rnk_send_step());
		break;
		default:
			mck_abort(1, mc_cstr("Invalid sornet_tok_t (sornet_dbg_send_nxt_step)"));
		break;
	}

	PTD_LOG("sornet_send_nxt_end %lu\n", dbg_sornet_curr_cntr);

	return true;
}

void
nervenet::sornet_dbg_end_step(sorkind_t knd){
	PTD_CK(kernel::get_workeru_nn() == 0);
	
	if(knd != sorkind_rnk){
		bool srt_ok = sornet_check_order(sornet_get_cmp_func(knd));
		if(! srt_ok){
			mck_abort(__LINE__, MC_ABORT_MSG("SORNET_ERROR\n"));
		}
	}
	
	switch(knd){
		case sorkind_bin:
			BJ_DBG_SORBINS(sornet_dbg_bin_end_step()); 
		break;
		case sorkind_num:
			BJ_DBG_SORNUMS(sornet_dbg_num_end_step());
		break;
		case sorkind_rnk:
			BJ_DBG_RANK_OUTS(sornet_dbg_rnk_end_step());
		break;
		default:
			mck_abort(1, mc_cstr("Invalid sornet_tok_t (sornet_dbg_end_step)"));
		break;
	}
	
	mck_slog2("sorted_ok_arr_");
	mck_ilog(dbg_sornet_curr_cntr);
	mck_slog2("\n");
	mck_sprt2("sorted_ok_arr_");
	mck_iprt(dbg_sornet_curr_cntr);
	mck_sprt2("\n");
	
	mc_init_arr_vals(tot_input_sorcells, all_output_sorobjs, mc_null);
	mc_init_arr_vals(tot_input_sorcells, all_output_sorgrps, 0);
	dbg_tot_rcv_output_sorobjs = 0;

	nervenet* my_net = this;
	bj_send_sornet_tmt(my_net, bj_tok_sornet_start, knd, 0, mc_null, my_net, 0);
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

		bj_send_sornet_tmt(src, bj_tok_sornet_bin, sorkind_bin, aa, obj, srcll, aa);
	}
}

#endif
// END_OF_BIN_SORT_CODE
//----------------------------------------------------------------------------------


//================================================================================
//================================================================================
// BEGINING_OF_NUM_SORT_CODE

#ifdef BJ_SORNET_NUM_TEST

#define bj_pt_obj_as_num(pt_oo) (*((num_nod_t*)(pt_oo)))

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
	
	sornet_dbg_num_init_val_arr();

	PTD_CK(dbg_all_input_vals != mc_null);
	
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

		bj_send_sornet_tmt(src, bj_tok_sornet_num, sorkind_num, aa, obj, srcll, aa);
	}
}

void
nervenet::sornet_dbg_num_end_step(){
	PTD_CK(kernel::get_workeru_nn() == 0);

	PTD_CODE(
	printf("SORTED=[");
	num_nod_t aa;
	for(aa = 0; aa < tot_input_sorcells; aa++){
		void* obj = all_output_sorobjs[aa];
		num_nod_t vv = bj_pt_obj_as_num(obj);
		printf("%ld ", vv);
		if(aa > 0){
			void* obj_prv = all_output_sorobjs[aa-1];
			num_nod_t vv_prv = bj_pt_obj_as_num(obj_prv);
			num_nod_t grp_prv = all_output_sorgrps[aa-1];
			num_nod_t grp = all_output_sorgrps[aa];
			PTD_CK((aa == 0) || ((vv_prv == vv) ? (grp_prv == grp) : (grp_prv != grp)));
		}
	}
	printf("]\n");
	printf("GROUPS=[");
	for(aa = 0; aa < tot_input_sorcells; aa++){
		printf("%ld ", all_output_sorgrps[aa]);
	}
	printf("]\n");
	);
}

#endif
// END_OF_NUM_SORT_CODE
//----------------------------------------------------------------------------------


//================================================================================
//================================================================================
// BEGINING_OF_RANK_OUTS_CODE

#ifdef BJ_SORNET_RANK_TEST

num_nod_t
nervenet::sornet_dbg_rnk_get_nw_grp(){
	num_nod_t nxt_grp = 0;
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	tak_mak& gg = dbg_random_gen;
	bool ending = false;
	nxt_grp = (num_nod_t)gg.gen_rand_int32_ie(0, tot_arr_sorouts);
	while(true){
		sorout* srout = arr_sorouts[nxt_grp];
		PTD_CK(srout != mc_null);
		
		bool is_grp = mc_get_flag(srout->jump_flags, bj_sorout_dbg_is_grp_flag);
		if(! is_grp){
			break;
		}
		nxt_grp++;
		if(nxt_grp == tot_arr_sorouts){
			nxt_grp = 0;
			
			if(ending){ break; }
			ending = true;
		}
	}
	PTD_CK(nxt_grp >= 0);
	PTD_CK(nxt_grp < tot_arr_sorouts);
	PTD_CK(! mc_get_flag(arr_sorouts[nxt_grp]->jump_flags, bj_sorout_dbg_is_grp_flag));
	
	mc_set_flag(arr_sorouts[nxt_grp]->jump_flags, bj_sorout_dbg_is_grp_flag);
	
#endif
	return nxt_grp;
}

void
nervenet::sornet_dbg_rnk_init_grp_arr(){
#if defined(MC_IS_PTD_CODE) && defined(FULL_DEBUG)
	PTD_CK(kernel::get_workeru_nn() == 0);
	
	tak_mak& gg = dbg_random_gen;
	
	unsigned long max_val = tot_arr_sorouts - 1;

	num_nod_t grp_ii = 0;
	num_nod_t grp_sz = 0;
	num_nod_t grp_id = 0;
	
	PTD_CK(arr_sorouts != mc_null);

	for(num_nod_t aa = 0; aa < tot_arr_sorouts; aa++){
		sorout* srout = arr_sorouts[aa];
		mc_reset_flag(srout->jump_flags, bj_sorout_dbg_is_grp_flag);
	}
	
	for(num_nod_t aa = 0; aa < tot_arr_sorouts; aa++){
		if(grp_ii == grp_sz){
			grp_ii = 0;
			grp_sz = (num_nod_t)gg.gen_rand_int32_ie(1, max_val / 2);
			grp_id = sornet_dbg_rnk_get_nw_grp();
		}
		grp_ii++;

		sorout* srout = arr_sorouts[aa];
		srout->grp_idx = grp_id;
	}

	for(num_nod_t aa = 0; aa < tot_arr_sorouts; aa++){
		sorout* srout = arr_sorouts[aa];
		mc_reset_flag(srout->jump_flags, bj_sorout_dbg_is_grp_flag);
	}
#endif
}

void
nervenet::sornet_dbg_rnk_send_step(){
	PTD_CK(kernel::get_workeru_nn() == 0);
	cell* src = this;

	PTD_LOG("send_cntr counter=%d tot_outs=%d \n", dbg_sornet_curr_cntr, tot_arr_sorouts);
	
	sornet_dbg_rnk_init_grp_arr();

	PTD_CK(arr_sorouts != mc_null);
	
	num_nod_t aa;
	for(aa = 0; aa < tot_arr_sorouts; aa++){
		sorout* srout = arr_sorouts[aa];
		PTD_CK(srout != mc_null);
		PTD_CK(srout->idx == aa);
		
		num_nod_t tmt_grp_idx = srout->grp_idx;
		bj_send_sornet_tmt(src, bj_tok_sornet_rank_start, sorkind_rnk, tmt_grp_idx, mc_null, srout, aa);
	}

}

void
nervenet::sornet_dbg_rnk_end_step(){
	PTD_CK(kernel::get_workeru_nn() == 0);

	PTD_PRINTF("IDXS=[");
	num_nod_t aa;
	for(aa = 0; aa < tot_arr_sorouts; aa++){
		PTD_PRINTF("%ld ", arr_sorouts[aa]->idx);
		if(aa > 0){
			//num_nod_t col_0 = arr_sorouts[aa-1]->color;
			//num_nod_t col_1 = arr_sorouts[aa]->color;
			//PTD_CK(col_0 < col_1);
		}
	}
	PTD_PRINTF("]\n");
	PTD_PRINTF("GRPS=[");
	for(aa = 0; aa < tot_arr_sorouts; aa++){
		PTD_PRINTF("%ld ", arr_sorouts[aa]->grp_idx);
	}
	PTD_PRINTF("]\n");
	PTD_PRINTF("COLS=[");
	for(aa = 0; aa < tot_arr_sorouts; aa++){
		PTD_PRINTF("%ld ", arr_sorouts[aa]->color);
	}
	PTD_PRINTF("]\n");
	
}

#endif
// END_OF_RANK_OUTS_CODE
//----------------------------------------------------------------------------------

bool
sorout::is_head(){
	return mc_get_flag(jump_flags, bj_sorout_is_head_flag);
}

bool
sorout::is_tail(){
	return mc_get_flag(jump_flags, bj_sorout_is_tail_flag);
}

bool
sorout::has_sent_jump(){
	bool hh = mc_get_flag(jump_flags, bj_sorout_sent_jump_flag);
	if(is_tail()){ hh = true; }
	return hh;
}

bool
sorout::has_received_jump(){
	bool hh = mc_get_flag(jump_flags, bj_sorout_received_jump_flag);
	if(is_head()){ hh = true; }
	return hh;
}

bool
sorout::has_received_request(){
	bool hh = (req != mc_null);
	if(is_tail()){ hh = true; }
	return hh;
}

bool
sorout::has_received_step(){
	bool hh = mc_get_flag(jump_flags, bj_sorout_received_step_flag);
	if(is_head()){ hh = true; }
	return hh;
}

bool
sorout::has_sent_step(){
	bool hh = mc_get_flag(jump_flags, bj_sorout_sent_step_flag);
	//if(is_tail()){ hh = true; }
	return hh;
}

void
sorout::reset_flags(){
	bool is_lst = mc_get_flag(jump_flags, bj_sorout_is_last_flag);
	jump_flags = 0;
	if(is_lst){
		mc_set_flag(jump_flags, bj_sorout_is_last_flag);
		mc_set_flag(jump_flags, bj_sorout_is_tail_flag);
	}
}

void
sorout::reset_jump(){
	cell* src = this;
	if(req == src){
		mc_set_flag(jump_flags, bj_sorout_is_tail_flag);
		PTD_LOG("%ld_RNK_%ld_BECOMES_TAIL \n", num_step, idx);
	}
	if(nxt_jump == mc_null){
		mc_set_flag(jump_flags, bj_sorout_is_head_flag);
		PTD_LOG("%ld_RNK_%ld_BECOMES_HEAD \n", num_step, idx);
	}
	
	mc_reset_flag(jump_flags, bj_sorout_received_jump_flag);
	mc_reset_flag(jump_flags, bj_sorout_sent_jump_flag);
	
	req = mc_null;
	last_jump = nxt_jump;
}

void
sorout::send_next_jump(){
	cell* src = this;

	num_step++;

	mc_reset_flag(jump_flags, bj_sorout_sent_step_flag);
	mc_reset_flag(jump_flags, bj_sorout_received_step_flag);
	
	bool has_jump = (nxt_jump != mc_null);
	bool is_finished = mc_get_flag(jump_flags, bj_sorout_is_finished_flag);
	if(has_jump || ! is_finished){
		if(! is_finished && ! has_jump){
			mc_set_flag(jump_flags, bj_sorout_is_finished_flag);
			PTD_LOG("%ld_RNK_%ld_BECOMES_FINISHED \n", num_step, idx);
		}
		
		bj_send_sornet_tmt(src, bj_tok_sornet_rank_jump, sorkind_rnk, grp_idx, mc_null, nxt_jump, idx);
		PTD_LOG("%ld_RNK_%ld_>%ld_ASK_JMP \n", num_step, idx, bj_sorout_idx(nxt_jump));
		
		if(is_tail() && has_jump){
			PTD_CK(idx > nxt_jump->idx);
			bj_send_sornet_tmt(src, bj_tok_sornet_rank_step, sorkind_rnk, 
								grp_idx, nxt_jump, nxt_jump, idx);
			PTD_LOG("%ld_RNK_%ld_>%ld_SND_REQ_%ld \n", num_step, idx, nxt_jump->idx, nxt_jump->idx);
		}
	}
	
}

void
sorout::sornet_handler(missive* msv){
	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	//sorkind_t tmt_knd = sn_tmt->knd;
	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);
	num_nod_t tmt_idx = sn_tmt->idx;
	void* tmt_obj = sn_tmt->obj;
	num_nod_t tmt_grp_idx = sn_tmt->grp_idx;

	sorout* src = this;

	if(tmt_tok == bj_tok_sornet_rank_start){
		num_step = 0;
		
		grp_idx = tmt_grp_idx;
		idx = tmt_idx;
		obj = tmt_obj;

		color = 0;
		nxt_jump = prv;		
		req = mc_null;
		
		PTD_LOG("%ld_RNK_%ld_START \n", num_step, idx);
		
		reset_flags();
		reset_jump();
		send_next_jump();
		return;
	}

	bool dbg_ha_ok = false;
	MC_MARK_USED(dbg_ha_ok);
	
	sorout* tmt_src = (sorout*)(sn_tmt->src);
	PTD_CK(tmt_src != mc_null);
	
	if(tmt_tok == bj_tok_sornet_rank_jump){
		if(tmt_src == nxt_jump){
			PTD_CK(tmt_idx < idx);
			//PTD_CK(tmt_obj != mc_null);
			PTD_CK(! has_received_jump());
			
			mc_set_flag(jump_flags, bj_sorout_received_jump_flag);
			nxt_jump = (sorout*)tmt_obj;
			
			PTD_LOG("%ld_RNK_%ld_<%ld_RCV_JMP_%ld_ \n", num_step, idx, tmt_src->idx, 
					bj_sorout_idx(nxt_jump));
			dbg_ha_ok = true;
			PTD_CK(has_received_jump());
		} else {
			PTD_CK(tmt_idx > idx);
			PTD_CK(tmt_obj == mc_null);
			PTD_CK_PRT((! has_sent_jump()), "%ld_RNK_%ld_>%ld_ALREADY_SENT_%ld \n", 
					   num_step, idx, tmt_src->idx, bj_sorout_idx(last_jump));
			
			mc_set_flag(jump_flags, bj_sorout_sent_jump_flag);
			bj_send_sornet_tmt(src, bj_tok_sornet_rank_jump, sorkind_rnk, grp_idx, last_jump, tmt_src, idx);
			PTD_LOG("%ld_RNK_%ld_>%ld_ANS_JMP_%ld_ \n", num_step, idx, tmt_src->idx, 
					bj_sorout_idx(last_jump));

			if(last_jump != mc_null){
				PTD_CK(idx > last_jump->idx);
				bj_send_sornet_tmt(src, bj_tok_sornet_rank_step, sorkind_rnk, 
								   grp_idx, tmt_src, last_jump, idx);
				PTD_LOG("%ld_RNK_%ld_>%ld_SND_REQ_%ld \n", num_step, idx, last_jump->idx, tmt_src->idx);
			}
			dbg_ha_ok = true;
			PTD_CK(has_sent_jump());
		}
	}

	if(tmt_tok == bj_tok_sornet_rank_step){
		PTD_CK(tmt_idx != idx);
		if(tmt_idx > idx){
			PTD_CK(tmt_obj != mc_null);
			PTD_CK_PRT((! has_received_request()), 
					   "%ld_RNK_%ld_<%ld_RCV_REQ", num_step, idx, tmt_src->idx);
			req = (sorout*)tmt_obj;
			PTD_LOG("%ld_RNK_%ld_<%ld_RCV_REQ_%ld \n", num_step, idx, tmt_src->idx, req->idx);
			dbg_ha_ok = true;
			PTD_CK(has_received_request());
		} else {
			PTD_CK(tmt_idx < idx);
			PTD_CK(tmt_obj == src);
			PTD_CK(! has_received_step());
			mc_set_flag(jump_flags, bj_sorout_received_step_flag);
			PTD_LOG("%ld_RNK_%ld_<%ld_RCV_STP \n", num_step, idx, tmt_src->idx);
			dbg_ha_ok = true;
			PTD_CK(has_received_step());
		}
	}
	
	PTD_CK(dbg_ha_ok);
	
	if(has_received_jump() && has_sent_jump() && has_received_request()){
		sorout* tgt = req;
		PTD_CK((tgt != mc_null) || is_tail());
		
		reset_jump();

		PTD_CK(! has_sent_step());
		mc_set_flag(jump_flags, bj_sorout_sent_step_flag);
		
		if(! is_tail()){
			PTD_CK(tgt != src);
			PTD_CK(idx < tgt->idx);
			bj_send_sornet_tmt(src, bj_tok_sornet_rank_step, sorkind_rnk, grp_idx, tgt, tgt, idx);
			PTD_LOG("%ld_RNK_%ld_>%ld_SND_STP \n", num_step, idx, tgt->idx);
		} else {
			PTD_LOG("%ld_RNK_%ld_IS_TAIL_NOT_snding_stp \n", num_step, idx);
		}
	}
	
	if(has_received_step() && has_sent_step()){
		send_next_jump();
	}
}

