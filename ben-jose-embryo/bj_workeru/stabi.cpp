
#include "cell.hh"
#include "stabi.hh"

#define BJ_DBG_STABI_MAX_TIER 10

void 
sorcell_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(sorcell, sornet_handler, msv);
}

void 
endcell_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(endcell, sornet_handler, msv);
}

void 
neuron_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(neuron, stabi_handler, msv);
}

void 
polaron_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(polaron, stabi_handler, msv);
}

void 
synapse_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(synapse, stabi_handler, msv);
}

void 
nervenet_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, stabi_handler, msv);
}


void bj_stabi_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_sorcell] = sorcell_stabi_handler;
	hndlrs[idx_endcell] = endcell_stabi_handler;
	hndlrs[idx_neuron] = neuron_stabi_handler;
	hndlrs[idx_polaron] = polaron_stabi_handler;
	hndlrs[idx_synapse] = synapse_stabi_handler;
	hndlrs[idx_nervenet] = nervenet_stabi_handler;
	hndlrs[idx_last_invalid] = kernel::invalid_handler_func;

	kernel::set_tot_cell_subclasses(idx_total);
	kernel::set_cell_handlers(hndlrs);
}

void
synapse::stabi_handler(missive* msv){
	stabi_transmitter* sb_tmt = (stabi_transmitter*)msv;

	signal_data dat;
	dat.msv = msv;
	dat.snp = this;
	dat.tok = (stabi_tok_t)(sb_tmt->tok);
	dat.sd = side_left;
	
	dat.ti = sb_tmt->d.stb.wrk_tier;
	dat.col_idx = sb_tmt->d.stb.col_idx;

	PTD_CK(dat.sd == side_left);
	PTD_CK(dat.ti != BJ_INVALID_NUM_TIER);

	//if(bj_nervenet->act_left_side.sync_is_ending){ return; }

	nervenode* owr = (nervenode*)(mck_as_loc_pt(owner));
	owr->stabi_recv_transmitter(&dat);
}

int bj_cmp_stabi_color_arrs(num_syn_t sz1, num_nod_t* arr1, num_syn_t sz2, num_nod_t* arr2){
	num_syn_t msz = mc_min(sz1, sz2);
	for(num_syn_t aa = 0; aa < msz; aa++){
		num_nod_t v1 = arr1[aa];
		num_nod_t v2 = arr2[aa];
		if(v1 < v2){ return -1; }
		if(v1 > v2){ return 1; }
	}
	if(sz1 < sz2){ return -1; }
	if(sz1 > sz2){ return 1; }
	return 0;
}

void
nervenode::stabi_recv_transmitter(signal_data* dat){
	//PTD_CK(dat->sd == side_left);
	PTD_CODE(
		//side_state& stt = left_side;
		PTD_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);

		bool ok_3 =  false;
		if(ki == nd_neu){
			ok_3 = ((dat->ti + 1) == stabi_num_tier);
		} else {
			ok_3 = (dat->ti == stabi_num_tier);
		}
		
		PTD_CK_PRT(ok_3, "%s %s %ld %s (%d > %d)", stabi_tok_to_str((stabi_tok_t)dat->tok),
			node_kind_to_str(ki), id, net_side_to_str(side_left), (dat->ti + 1), stabi_num_tier);

		//PTD_CK(dat->ti < BJ_DBG_STABI_MAX_TIER); // debug_purposes_only
		PTD_CK(	(bj_nervenet->sync_parent_id != 0) ||
				bj_nervenet->act_left_side.sync_is_inactive ||
				(dat->ti < BJ_DBG_STABI_MAX_TIER)
		); // debug_purposes_only

		PTD_CK(dat->snp != mc_null);
		nervenode* rem_nd = dat->snp->mate->owner;
		PTD_LOG(" ::RECV_stabi_transmitter_%s_t%d_%s [%s %ld <<- %s %ld] #ti%d \n", 
			net_side_to_str(side_left), dat->ti, stabi_tok_to_str((stabi_tok_t)dat->tok), 
			node_kind_to_str(ki), id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
			stabi_num_tier
		);
	);

	switch(dat->tok){
		case bj_tok_stabi_color:
			stabi_recv_color(dat);
		break;
		case bj_tok_stabi_ping:
			stabi_recv_ping(dat);
		break;
		case bj_tok_stabi_tier_done:
			stabi_recv_tier_done(dat);
		break;
		default:
			mck_abort(1, mc_cstr("nervenode::stabi_recv_transmitter. BAD_STABI_TOK"));
		break;
	}
}

void 
nervenode::stabi_send_snp_tier_done(callee_prms& pms){
	PTD_CK(pms.snp->owner == this);
	pms.snp->stabi_send_transmitter(bj_tok_stabi_tier_done);
}

void
nervenode::stabi_send_all_ti_done(nervenode* nd, num_tier_t dbg_ti){
	side_state& sst = left_side;
	net_side_t sd = side_left;
	
	PTD_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);
	//PTD_CK(&(nd->left_side) == this);

	sst.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_tier_done, sd);

	PTD_CK((dbg_ti == BJ_INVALID_NUM_TIER) || (nd->ki != nd_neu) || ((dbg_ti + 1) == stabi_num_tier));
	PTD_CK((dbg_ti == BJ_INVALID_NUM_TIER) || (nd->ki == nd_neu) || (dbg_ti == stabi_num_tier));

	PTD_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);
	stabi_num_tier++;

	PTD_LOG("STABI_INC_TIER_%s_t%d_%s_%ld\n", net_side_to_str(sd), stabi_num_tier, 
			node_kind_to_str(nd->ki), nd->id);
}

void
nervenode::stabi_recv_ping(signal_data* dat){
	side_state& stt = left_side;
	stt.step_num_ping++;

	PTD_LOG("STABI_INC_PINGS %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id,
			net_side_to_str(side_left), stt.step_num_ping, dat->ti);
}

void
synapse::stabi_send_transmitter(stabi_tok_t tok, nervenode* src_nd, bool dbg_is_forced){
	//net_side_t sd = side_left;

	if(bj_nervenet->act_left_side.sync_is_ending){ return; }

	num_tier_t ti = owner->stabi_num_tier;

	MC_DBG(node_kind_t the_ki = owner->ki);
	MCK_CK((the_ki == nd_pos) || (the_ki == nd_neg) || (the_ki == nd_neu));
	PTD_CODE(nervenode* rem_nd = mate->owner);
	PTD_LOG("::stabi_send_transmitter_%s_t%d_%s [%s %ld ->> %s %s %ld k%d] \n", 
			net_side_to_str(side_left), ti, stabi_tok_to_str(tok), node_kind_to_str(owner->ki), owner->id, 
		((dbg_is_forced)?("FORCED"):("")), node_kind_to_str(rem_nd->ki), rem_nd->id, 
		mc_id_to_nn(mc_addr_get_id(mate)));

	stabi_transmitter* trm = bj_stabi_transmitter_acquire();
	trm->d.stb.wrk_tier = BJ_INVALID_NUM_TIER;
	trm->d.stb.col_idx = BJ_INVALID_IDX;
	
	trm->src = this;
	trm->dst = mate;
	trm->tok = tok;
	
	trm->d.stb.wrk_tier = ti;
	if(src_nd != mc_null){
		trm->d.stb.col_idx = src_nd->stabi_col.min_idx;
	}
	trm->send();
}

void
neuron::stabi_neuron_start(){
	PTD_CK(left_side.step_active_set.all_grp.is_alone());
	PTD_CK(right_side.step_active_set.all_grp.is_alone());

	left_side.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_color, side_left);

	stabi_send_all_ti_done(this, BJ_INVALID_NUM_TIER);
	left_side.step_reset_complete();
	stabi_reset_complete();
}

void
nervenode::stabi_recv_tier_done(signal_data* dat){
	net_side_t sd = side_left;
	nervenode* nd = this;
	side_state& stt = left_side;

	stt.step_num_complete++;

	PTD_LOG("STABI_ADD_TIER_END %s %ld %s compl(%d of %d) TI=%d \n", 
			node_kind_to_str(ki), id, net_side_to_str(sd), 
			stt.step_num_complete, stt.step_prev_tot_active, dat->ti);

	if(is_tier_complete(dat)){
		stabi_recalc_intact();

		MC_DBG(dbg_prt_tier_done(dat));

		bool to_dly = false;
		netstate& nstt = bj_nervenet->get_active_netstate(sd);
		grip& all_ti = nstt.all_stabi_tiers;
		num_tier_t the_ti = stabi_num_tier;
		
		if((ki == nd_neu)){
			PTD_CK(dat->ti == (the_ti - 1));
			to_dly = ((neuron*)nd)->is_to_delay(tiki_propag, dat->sd, the_ti, all_ti);
			if(! to_dly){
				nstt.inc_tier_rcv(nd, tiki_stabi, the_ti, all_ti);
			} else {
				tierdata& lti = get_last_tier(all_ti);
				lti.delay_binder(stt, 3);
			}
		}

		char* ts = bj_dbg_tier_kind_to_str(tiki_stabi);
		MC_MARK_USED(ts);
		PTD_LOG("STABI_TIER_COMPLETE_t%d_%s_%ld %s_%s ((%d > 0) && (%d == %d) && (%d < %d)) %s \n", dat->ti, 
					node_kind_to_str(ki), id, ts, ((to_dly)?("TO_DELAY"):("")), 
			stt.step_prev_tot_active, stt.step_num_ping, stt.step_prev_tot_active, 
			get_last_tier(all_ti).tdt_id, (the_ti - 1),
			(mc_get_flag(stt.step_flags, bj_stt_stabi_intact_col_idx_flag))?("intact"):("")
		);

		if(! to_dly){
			stabi_start_nxt_tier(dat);
		}
	}
}

void
nervenode::stabi_start_nxt_tier(signal_data* dat){
	PTD_CK(! mc_get_flag(stabi_flags, bj_stabi_ti_done_flag));
	PTD_CK(stabi_tmp_tier == BJ_INVALID_NUM_TIER);
	
	mc_set_flag(stabi_flags, bj_stabi_ti_done_flag);
	stabi_tmp_tier = dat->ti;
	
	PTD_CK(stabi_tmp_tier != BJ_INVALID_NUM_TIER);
	
	stabi_send_start_srt();
}

void
nervenode::stabi_send_start_srt(){
	bool f1 = mc_get_flag(stabi_flags, bj_stabi_ti_done_flag);
	bool f2 = mc_get_flag(stabi_flags, bj_stabi_srt_rdy_flag);
	bool f3 = mc_get_flag(stabi_flags, bj_stabi_srt_always_rdy_flag);
	
	if(f1 && (f2 || f3)){
		nervenode* src = this;
		cell* srcll = stabi_out;
	
		mc_reset_flag(stabi_flags, bj_stabi_ti_done_flag);
		mc_reset_flag(stabi_flags, bj_stabi_srt_rdy_flag);

		bj_send_sornet_tmt(src, bj_tok_sornet_num, sorkind_cll, 
				stabi_idx, stabi_idx, stabi_col.min_idx, stabi_col.max_idx, src, srcll, stabi_idx);
	}
}

void
nervenode::stabi_send_nxt_tier_color(){
	mck_abort(1, mc_cstr("nervenode::stabi_send_nxt_tier_color"));
}

void
nervenode::stabi_recalc_intact(){
	if(bj_is_pol(ki)){
		return;
	}
	PTD_CK(stabi_prv_arr_dat != mc_null);
	
	side_state& sst = left_side;
	mc_reset_flag(sst.step_flags, bj_stt_stabi_intact_col_idx_flag);
	int rr = bj_cmp_stabi_color_arrs(stabi_arr_sz, stabi_arr_dat, stabi_prv_arr_sz, stabi_prv_arr_dat);
	if(rr == 0){
		mc_set_flag(sst.step_flags, bj_stt_stabi_intact_col_idx_flag);
	}
}

void
polaron::stabi_send_nxt_tier_color(){
	net_side_t sd = side_left;
	polaron* pol = this;
	side_state& pol_stt = get_side_state(sd);
	side_state& opp_stt = opp->get_side_state(sd);

	PTD_CK(pol_stt.is_full());
	PTD_CK(opp_stt.is_full());

	pol_stt.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_color, side_left);
	opp_stt.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_color, side_left);

	PTD_CK(stabi_tmp_tier != BJ_INVALID_NUM_TIER);
	
	pol->stabi_send_all_ti_done(pol, stabi_tmp_tier);
	opp->stabi_send_all_ti_done(opp, stabi_tmp_tier);

	pol_stt.step_reset_complete();
	opp_stt.step_reset_complete();
	
	pol->stabi_reset_complete();
	opp->stabi_reset_complete();
}

void
nervenode::stabi_reset_complete(){
	PTD_CK(stabi_flags == 0);
	stabi_tmp_tier = BJ_INVALID_NUM_TIER;
	
	if(bj_is_pol(ki)){
		PTD_CK(stabi_prv_arr_dat == mc_null);
		stabi_arr_sz = 0;
		return;
	}
	PTD_CK(stabi_prv_arr_dat != mc_null);
	
	num_nod_t*  tmp_dat = stabi_prv_arr_dat;
	stabi_prv_arr_dat = stabi_arr_dat;
	stabi_prv_arr_sz = stabi_arr_sz;
	
	stabi_arr_sz = 0;
	stabi_arr_dat = tmp_dat;
}

void
nervenode::dbg_prt_tier_done(signal_data* dat){
	net_side_t sd = side_left;
	MC_DBG(dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	PTD_DBG_CODE(dbg_prt_active_synset(sd, tiki_stabi, mc_cstr("ACTi"), dat->ti));
}

void
polaron::dbg_prt_tier_done(signal_data* dat){
	net_side_t sd = side_left;
	polaron* pol = this;
	MC_DBG(pol->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	MC_DBG(opp->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	PTD_DBG_CODE(pol->dbg_prt_active_synset(sd, tiki_stabi, mc_cstr("ACTi"), dat->ti));
	PTD_DBG_CODE(opp->dbg_prt_active_synset(sd, tiki_stabi, mc_cstr("ACTi"), dat->ti));
}

void
neuron::stabi_send_nxt_tier_color(){
	neuron* neu = this;
	net_side_t sd = side_left;
	side_state& stt = get_side_state(sd);
	netstate& nst = bj_nervenet->get_active_netstate(sd);

	//MC_DBG(dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, stabi_tmp_tier));

	stt.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_color, side_left);

	PTD_CK(stabi_tmp_tier != BJ_INVALID_NUM_TIER);
	
	stabi_send_all_ti_done(neu, stabi_tmp_tier);
	stt.step_reset_complete();
	stabi_reset_complete();

	//mck_slog2("dbg2.reset\n");

	nst.update_sync_inert(tiki_stabi, true);
}

void 
nervenode::stabi_send_snp_color(callee_prms& pms){
	PTD_CK(pms.snp != mc_null);
	PTD_CK(pms.snp->owner == this);
	nervenode* nd = this;

	bool snd_png = false;
	if(ki == nd_neu){
		bool is_itct = mc_get_flag(left_side.step_flags, bj_stt_stabi_intact_col_idx_flag);
		snd_png = is_itct;
	} else {
		PTD_CK(bj_is_pol(ki));
		bool all_png = left_side.neu_all_ping(tiki_stabi);
		snd_png = all_png;
	}
	if(snd_png){
		//PTD_CK(! bj_is_pol(ki));
		pms.snp->stabi_send_transmitter(bj_tok_stabi_ping, nd);
	} else {
		pms.snp->stabi_send_transmitter(bj_tok_stabi_color, nd);
	}
}

void bj_stabi_kernel_func(){
	nervenet* my_net = bj_nervenet;
	my_net->act_left_side.stabi_handle_my_sync();
}

void 
netstate::stabi_handle_my_sync(){
	update_sync_inert(tiki_stabi, true);
	
	if(sync_is_ending){
		SYNC_LOG(" SYNCR_STOPPING_WORKERU_%s \n", net_side_to_str(my_side));
		//mck_get_kernel()->set_idle_exit();
		//kernel::stop_sys(bj_tok_propag_end);
		kernel::stop_sys(bj_tok_stabi_end);
	}
}

void
nervenet::stabi_handler(missive* msv){
	mck_token_t msv_tok = msv->tok;
	
	PTD_CK(msv_tok != bj_tok_sornet_sep_out);
	PTD_CK(msv_tok != bj_tok_sornet_cll_out);
	PTD_CK(msv_tok != bj_tok_sornet_num_out);
	PTD_CK(msv_tok != bj_tok_sornet_rank_out);
	
	if(msv_tok == bj_tok_stabi_start){
		stabi_nervenet_start();
		//kernel::stop_sys(bj_tok_stabi_end); // DEBUG purposes only
		return;
	}
	if(msv_tok == bj_tok_stabi_range_bcast){
		stabi_set_ranges(msv);
		return;
	}
	
	/*if(bj_tok_sync_to_children == tmt_tok){
		act_left_side.send_sync_to_children(bj_tok_sync_to_children, BJ_SORNET_TIER, tiki_invalid, mc_null);
		return;
	}*/ // sornet_handler

	sync_handler(tiki_stabi, msv);
}

void bj_stabi_main() {
	mck_set_sub_module_id(BJ_STABI_SUB_MODULE_STABI);

	mc_workeru_nn_t nn = kernel::get_workeru_nn();

	bj_stabi_init_handlers();

	PTD_LOG("STABI___ %d \n", nn);

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_stabi_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->init_sync_cycle();

	mck_slog2("__dbg2.stabi\n");

	bj_print_active_cnf(side_left, tiki_stabi, mc_cstr("stb_before"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	my_net->send(my_net, bj_tok_stabi_start);
	//kernel::run_sys();

	bj_print_active_cnf(side_left, tiki_stabi, mc_cstr("stb_after"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	PTD_PRT("...............................END_STABI\n");
	mck_slog2("END_STABI___");
	mck_ilog(nn);
	//mck_slog2("_________________________\n");
	mck_sprt2("dbg2.stabi.end\n");

}

void
nervenode::stabi_insert_color(num_nod_t col_idx){
	num_nod_t* arr = stabi_arr_dat;
	num_nod_t ii = ((num_nod_t)stabi_arr_sz) - 1;
	PTD_CK((ii + 1) < sz);
	while((ii >= 0) && (arr[ii] > col_idx)){
		arr[ii + 1] = arr[ii];
		ii--;
	}
	PTD_CK((ii + 1) >= 0);
	arr[ii + 1] = col_idx;
	
	stabi_arr_sz++;
	PTD_CK(stabi_arr_sz <= sz);
}

void
nervenode::stabi_recv_color(signal_data* dat){
	stabi_insert_color(dat->col_idx);
}

int bj_cmp_cell_objs(void* obj1, void* obj2){
	nervenode* n1 = (nervenode*)obj1;
	nervenode* n2 = (nervenode*)obj2;
	int c_val = bj_cmp_stabi_color_arrs(n1->stabi_arr_sz, n1->stabi_arr_dat, 
										n2->stabi_arr_sz, n2->stabi_arr_dat);
	return c_val;
}

void
neuron::stabi_handler(missive* msv){
	mck_token_t tok = msv->tok;

	switch(tok){
		case bj_tok_stabi_start:
			stabi_neuron_start();
		break;
		case bj_tok_sornet_rank_rdy:
		{
			PTD_CK(! mc_get_flag(stabi_flags, bj_stabi_srt_rdy_flag));
			mc_set_flag(stabi_flags, bj_stabi_srt_rdy_flag);
			stabi_send_start_srt();
		}
		break;
		case bj_tok_sornet_rank_sep:
			stabi_recv_rnk_sep(msv);
		break;
		case bj_tok_sornet_rank_cll:
			stabi_recv_rnk_cll(msv);
		break;
		default:
			mck_abort(1, mc_cstr("BAD_STABI_TOK"));
		break;
	}
}

void
polaron::stabi_handler(missive* msv){
	mck_token_t tok = msv->tok;

	switch(tok){
		case bj_tok_sornet_rank_rdy:
		{
			PTD_CK(! mc_get_flag(stabi_flags, bj_stabi_srt_rdy_flag));
			mc_set_flag(stabi_flags, bj_stabi_srt_rdy_flag);
			stabi_send_start_srt();
		}
		break;
		case bj_tok_sornet_rank_sep:
			stabi_recv_rnk_sep(msv);
		break;
		case bj_tok_sornet_rank_cll:
			stabi_recv_rnk_cll(msv);
		break;
		default:
			mck_abort(1, mc_cstr("BAD_STABI_TOK"));
		break;
	}
}

int bj_cmp_sep_objs(void* obj1, void* obj2){
	nervenode* n1 = (nervenode*)obj1;
	nervenode* n2 = (nervenode*)obj2;
	
	bool a1 = n1->stabi_is_active();
	bool a2 = n2->stabi_is_active();
	
	if(a1 && ! a2){ return -1; }
	if(! a1 && a2){ return 1; }
	
	return 0;
}

void
nervenet::stabi_nervenet_start(){
	PTD_LOG("stabi_nervenet_start \n");
	stabi_wu_num_rcv_sep = 0;
	stabi_wu_tot_nod_sep = 0;
	with_all_nervenodes(&all_wu_active_neu, &nervenode::stabi_send_sep, mc_null);
	PTD_LOG("end_stabi_nervenet_start \n");
}

void
nervenode::stabi_send_sep(void* pms){
	nervenode* src = this;
	cell* srcll = stabi_out;

	bj_send_sornet_tmt(src, bj_tok_sornet_num, sorkind_sep, 
			stabi_idx, stabi_idx, stabi_col.min_idx, stabi_col.max_idx, src, srcll, stabi_idx);
	
	bj_nervenet->stabi_wu_tot_nod_sep++;
}

void
nervenode::stabi_set_color(sornet_transmitter* sn_tmt){
	num_nod_t mn_idx = sn_tmt->d.srt.min_col;
	num_nod_t mx_idx = sn_tmt->d.srt.max_col;
	
	PTD_CK(bj_sornet_idx_inside(mn_idx, stabi_col.min_idx, stabi_col.max_idx));
	PTD_CK(bj_sornet_idx_inside(mx_idx, stabi_col.min_idx, stabi_col.max_idx));
	PTD_CK(bj_sornet_idx_inside(stabi_idx, stabi_col.min_idx, stabi_col.max_idx));
	
	stabi_col.min_idx = mn_idx;
	stabi_col.max_idx = mx_idx;
	stabi_idx = sn_tmt->d.srt.idx;
	stabi_out = (sorcell*)(sn_tmt->d.srt.inp);
	
	PTD_CK(bj_sornet_idx_inside(stabi_idx, mn_idx, mx_idx));
	
	PTD_CK(stabi_out != mc_null);
	PTD_CK((stabi_out->up_snp.idx == stabi_idx) || (stabi_out->down_snp.idx == stabi_idx));
}

void
nervenode::stabi_set_inactive(grip& all_inac){
	nervenode* nod = this;
	let_go();
	all_inac.bind_to_my_left(*nod);	
}

void
nervenode::stabi_set_nxt_rng(bool is_act){
	if(is_act){
		if(! bj_nervenet->stabi_nxt_active_rng.has_value()){
			bj_nervenet->stabi_nxt_active_rng = stabi_col;
		}
	} else {
		if(! bj_nervenet->stabi_nxt_inactive_rng.has_value()){
			bj_nervenet->stabi_nxt_inactive_rng = stabi_col;
		}
	}
}

void
neuron::stabi_recv_rnk_sep(missive* msv){
	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	stabi_set_color(sn_tmt);

	bool is_act = stabi_is_active();
	if(! is_act){
		layerdata& ly_dat = bj_nervenet->get_last_layer();
		stabi_set_inactive(ly_dat.all_inactive_neu);
	}
	stabi_set_nxt_rng(is_act);
	bj_nervenet->stabi_inc_rcv_sep(ki);
}

void
polaron::stabi_recv_rnk_sep(missive* msv){
	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	stabi_set_color(sn_tmt);

	mc_set_flag(stabi_flags, bj_stabi_srt_rdy_flag);
	
	bool is_act = stabi_is_active();
	if(! is_act){
		layerdata& ly_dat = bj_nervenet->get_last_layer();
		stabi_set_inactive(ly_dat.all_inactive_pol);
	}
	stabi_set_nxt_rng(is_act);
	bj_nervenet->stabi_inc_rcv_sep(ki);
}

void
nervenet::stabi_inc_rcv_sep(node_kind_t nod_ki){
	stabi_wu_num_rcv_sep++;
	if(stabi_wu_num_rcv_sep == stabi_wu_tot_nod_sep){
		layerdata& ly_dat = get_last_layer();
		
		if(nod_ki == nd_neu){
			active_neus_col = stabi_nxt_active_rng;
			ly_dat.inactive_neus_col = stabi_nxt_inactive_rng;
			
			stabi_nxt_active_rng.init_me();
			stabi_nxt_inactive_rng.init_me();
			
			stabi_wu_num_rcv_sep = 0;
			stabi_wu_tot_nod_sep = 0;
			with_all_nervenodes(&all_wu_active_pos, &nervenode::stabi_send_sep, mc_null);
			with_all_nervenodes(&all_wu_active_neg, &nervenode::stabi_send_sep, mc_null);
		} else {
			active_pols_col = stabi_nxt_active_rng;
			ly_dat.inactive_pols_col = stabi_nxt_inactive_rng;
			
			stabi_nxt_active_rng.init_me();
			stabi_nxt_inactive_rng.init_me();
			
			PTD_CK(bj_is_pol(nod_ki));
			
			stabi_begin_subgrouping();
		}
	}
}

void
nervenode::stabi_recv_rnk_cll(missive* msv){
	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	stabi_set_color(sn_tmt);
	stabi_send_nxt_tier_color();
}

void
nervenet::stabi_broadcast_range(rangekind_t knd, sornet_range active, sornet_range inactive){
	sornet_transmitter sn_tmt;
	sn_tmt.tok = bj_tok_stabi_range_bcast;
	sn_tmt.d.srt.knd = (sorkind_t)knd;
	sn_tmt.d.srt.min_col = active.min_idx;
	sn_tmt.d.srt.max_col = active.max_idx;
	sn_tmt.d.srt.min_grp = inactive.min_idx;
	sn_tmt.d.srt.max_grp = inactive.max_idx;
	
	mc_workeru_id_t pnt_id = bj_nervenet->sync_parent_id;
	if(pnt_id != 0){
		nervenet* src = this;
		nervenet* pnt_net = bj_nervenet->get_nervenet(pnt_id);
		
		base_transmitter* tmt = sn_tmt.clone_transmitter();
		tmt->src = src;
		tmt->dst = pnt_net;
		
		tmt->send();
	} 
	send_all_children(sn_tmt);
}

void
nervenet::stabi_broadcast_all_ranges(){
	layerdata& ly_dat = get_last_layer();
	bool n1 = active_neus_col.has_value();
	bool n2 = ly_dat.inactive_neus_col.has_value();
	PTD_CK(n1 == n2);
	if(n1){
		stabi_broadcast_range(rangekind_neus, active_neus_col, ly_dat.inactive_neus_col);
	}
	
	bool p1 = active_pols_col.has_value();
	bool p2 = ly_dat.inactive_pols_col.has_value();
	PTD_CK(p1 == p2);
	if(p1){
		stabi_broadcast_range(rangekind_pols, active_pols_col, ly_dat.inactive_pols_col);
	}
}

bool
nervenet::stabi_has_all_ranges(){
	layerdata& ly_dat = get_last_layer();
	bool n1 = active_neus_col.has_value();
	bool n2 = ly_dat.inactive_neus_col.has_value();
	PTD_CK(n1 == n2);
	bool p1 = active_pols_col.has_value();
	bool p2 = ly_dat.inactive_pols_col.has_value();
	PTD_CK(p1 == p2);
	
	bool all_ok = (n1 && p1);
	return all_ok;
}

void
nervenet::stabi_set_ranges(missive* msv){
	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	rangekind_t knd = (rangekind_t)(sn_tmt->d.srt.knd);

	sornet_range active;
	sornet_range inactive;
	active.min_idx = sn_tmt->d.srt.min_col;
	active.max_idx = sn_tmt->d.srt.max_col;
	inactive.min_idx = sn_tmt->d.srt.min_grp;
	inactive.max_idx = sn_tmt->d.srt.max_grp;
	
	bool added_some = false;
	
	layerdata& ly_dat = get_last_layer();
	if(knd == rangekind_neus){
		bool n1 = active_neus_col.has_value();
		bool n2 = ly_dat.inactive_neus_col.has_value();
		PTD_CK(n1 == n2);
		if(! n1){
			active_neus_col = active;
			ly_dat.inactive_neus_col = inactive;
			added_some = true;
		}
	} else {
		PTD_CK(knd == rangekind_pols);
		bool p1 = active_pols_col.has_value();
		bool p2 = ly_dat.inactive_pols_col.has_value();
		PTD_CK(p1 == p2);
		if(! p1){
			active_pols_col = active;
			ly_dat.inactive_pols_col = inactive;
			added_some = true;
		}
	}

	if(added_some){
		stabi_begin_subgrouping();
	}
}

void
nervenet::stabi_begin_subgrouping(){
	stabi_broadcast_all_ranges();
	if(stabi_has_all_ranges()){
		if(stabi_has_single_quas()){
			stabi_mark_all_single(active_neus_col, all_wu_active_pos);
			stabi_mark_all_single(active_neus_col, all_wu_active_neg);
		}
		if(stabi_has_single_neus()){
			stabi_mark_all_single(active_pols_col, all_wu_active_neu);
		}
		
		send_all_neus(bj_tok_stabi_start);
	}
}

bool
nervenet::stabi_has_single_quas(){
	PTD_CK(active_neus_col.min_idx == 0);
	PTD_CK(active_pols_col.min_idx == 0);
	num_nod_t num_act = active_pols_col.max_idx;
	bool has_sgl = ((num_act > 0) && (num_act > active_neus_col.max_idx));
	return has_sgl;
}

bool
nervenet::stabi_has_single_neus(){
	PTD_CK(active_neus_col.min_idx == 0);
	PTD_CK(active_pols_col.min_idx == 0);
	num_nod_t num_act = active_neus_col.max_idx;
	bool has_sgl = ((num_act > 0) && (num_act > active_pols_col.max_idx));
	return has_sgl;
}

void
nervenet::stabi_mark_all_single(sornet_range mates_rng, grip all_act){
	binder * fst, * lst, * wrk;

	binder* pt_all_nod = &(all_act);
	fst = (binder*)(pt_all_nod->bn_right);
	lst = (binder*)mck_as_loc_pt(pt_all_nod);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		nervenode* my_nod = (nervenode*)wrk;
		if(my_nod->stabi_idx > mates_rng.max_idx){
			mc_set_flag(my_nod->stabi_flags, bj_stabi_srt_always_rdy_flag);
		}
	}
}

