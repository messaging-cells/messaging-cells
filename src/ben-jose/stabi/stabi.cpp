
#include "cell.hh"
#include "stabi.hh"

#define BJ_DBG_STABI_MAX_TIER 10

void 
neuron_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(neuron, stabi_handler, msv);
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
	hndlrs[idx_neuron] = neuron_stabi_handler;
	hndlrs[idx_synapse] = synapse_stabi_handler;
	hndlrs[idx_nervenet] = nervenet_stabi_handler;

	kernel::set_handlers(idx_total, hndlrs);
}

void
synapse::stabi_handler(missive* msv){
	stabi_transmitter* sb_tmt = (stabi_transmitter*)msv;

	signal_data dat;
	dat.msv = msv;
	dat.snp = this;
	dat.tok = (stabi_tok_t)(sb_tmt->tok);
	dat.sd = sb_tmt->wrk_side;
	dat.ti = sb_tmt->wrk_tier;
	dat.id_arr_sz = sb_tmt->id_arr_sz;
	dat.id_arr = sb_tmt->id_arr;

	EMU_CK(dat.sd == side_left);
	EMU_CK(dat.ti != BJ_INVALID_NUM_TIER);
	EMU_CK(stabi_vessel != mc_null);

	//if(bj_nervenet->act_left_side.sync_is_ending){ return; }

	nervenode* owr = (nervenode*)(mck_as_loc_pt(owner));
	owr->stabi_recv_transmitter(&dat);
}

void 
synset::stabi_calc_arr_rec(num_syn_t cap, num_syn_t* arr, num_syn_t& ii) {
	MCK_CHECK_SP();

	EMU_CK_PRT((ii < cap), "DBG_INFO. ii=%d cap=%d\n", ii, cap);
	arr[ii] = tot_syn;
	ii++;

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = (binder*)mck_as_loc_pt(grps);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		//EMU_CK(sub_grp->parent == this);
		sub_grp->stabi_calc_arr_rec(cap, arr, ii);
	}

	//EMU_CK(ii < cap);
	//arr[ii] = tot_grp;
	//ii++;
}

// mc_addr_is_local(addr)

void 
neurostate::calc_stabi_arr(nervenode* dbg_nd, signal_data* dbg_dat) {
	bool was_nul = (stabi_arr == mc_null);
	EMU_DBG_CODE(
		num_tier_t dbg_ti = 0;
		if(dbg_dat != mc_null){ dbg_ti = dbg_dat->ti; }
	);

	mc_reset_flag(step_flags, bj_stt_stabi_intact_id_flag);

	num_syn_t	old_arr_sz = 0;
	num_syn_t*  old_arr = mc_null;
	if(! was_nul){
		EMU_CK(stabi_arr_sz < BJ_MAX_ID_ARR_SZ);

		old_arr_sz = stabi_arr_sz;
		old_arr = stabi_arr;

		stabi_arr_sz = 0;
		stabi_arr_cap = 0;
		stabi_arr = mc_null;
	}

	EMU_CK(stabi_arr_sz == 0);
	EMU_CK(stabi_arr == mc_null);

	if(step_active_set.is_synset_empty()){
		if(old_arr == mc_null){
			EMU_LOG(" CMP_IDS_both_empty_t%d_%s_%d_ \n", dbg_ti, dbg_nd->get_ki_str(), dbg_nd->id);
			mc_set_flag(step_flags, bj_stt_stabi_intact_id_flag);
		} else {
			mc_free32(old_arr);
		}
		return;
	}

	stabi_arr_cap = calc_cap_stabi_arr(step_active_set.tot_syn);
	stabi_arr = mc_malloc32(num_syn_t, stabi_arr_cap);

	EMU_LOG(" calc_stabi_arr new_cap=%d \n", stabi_arr_cap);
	EMU_CK(stabi_arr != mc_null);

	step_active_set.stabi_calc_arr_rec(stabi_arr_cap, stabi_arr, stabi_arr_sz);

	if(old_arr != mc_null){
		int cmp_arr = bj_cmp_stabi_id_arrs(old_arr_sz, old_arr, stabi_arr_sz, stabi_arr);

		EMU_LOG(" CMP_IDS_t%d_%s_%d_ \t (old=%s %s new=%s) \n", 
			dbg_ti, dbg_nd->get_ki_str(), dbg_nd->id,
			bj_dbg_stabi_id_arr_to_str(old_arr_sz, old_arr, BJ_DBG_STR_CAP, bj_nervenet->dbg_str1),
			((cmp_arr < 0)?("<"):((cmp_arr > 0)?(">"):("=="))),
			bj_dbg_stabi_id_arr_to_str(stabi_arr_sz, stabi_arr, BJ_DBG_STR_CAP, bj_nervenet->dbg_str2)
		);
		//EMU_DBG_CODE(mck_getchar());

		if(cmp_arr == 0){ 
			mc_set_flag(step_flags, bj_stt_stabi_intact_id_flag); 
		}
		mc_free32(old_arr);
	}
}

int bj_cmp_stabi_id_arrs(num_syn_t sz1, num_syn_t* arr1, num_syn_t sz2, num_syn_t* arr2){
	num_syn_t msz = mc_min(sz1, sz2);
	for(num_syn_t aa = 0; aa < msz; aa++){
		num_syn_t v1 = arr1[aa];
		num_syn_t v2 = arr2[aa];
		if(v1 < v2){ return -1; }
		if(v1 > v2){ return 1; }
	}
	if(sz1 < sz2){ return -1; }
	if(sz1 > sz2){ return 1; }
	return 0;
}

int bj_cmp_synapses(synapse* snp1, synapse* snp2, signal_data* dat){
	EMU_CK(snp1 != mc_null);
	EMU_CK(snp2 != mc_null);
	EMU_CK(snp1 != snp2);
	EMU_CK(snp1->owner == snp2->owner);

	num_syn_t sz1 = snp1->stabi_rcv_arr_sz;
	num_syn_t* arr1 = snp1->stabi_rcv_arr;

	num_syn_t sz2 = snp2->stabi_rcv_arr_sz;
	num_syn_t* arr2 = snp2->stabi_rcv_arr;

	int cmp_arr = bj_cmp_stabi_id_arrs(sz1, arr1, sz2, arr2);

	EMU_DBG_CODE(
		nervenode* ndw = snp1->owner;
		nervenode* nd1 = snp1->mate->owner;
		nervenode* nd2 = snp2->mate->owner;
	);
	EMU_LOG(" CMP_SNPS_t%d_%s_%d_ (%s_%d_%s %s %s_%d_%s) (%d %d %d) \n", 
		dat->ti, ndw->get_ki_str(), ndw->id, 
		nd1->get_ki_str(), nd1->id, bj_dbg_stabi_id_arr_to_str(sz1, arr1, BJ_DBG_STR_CAP, bj_nervenet->dbg_str1),
		((cmp_arr < 0)?("<"):((cmp_arr > 0)?(">"):("=="))),
		nd2->get_ki_str(), nd2->id, bj_dbg_stabi_id_arr_to_str(sz2, arr2, BJ_DBG_STR_CAP, bj_nervenet->dbg_str2),
		cmp_arr, sz1, sz2
	);
	return cmp_arr;
}

void
nervenode::stabi_recv_transmitter(signal_data* dat){
	EMU_CK(dat->sd == side_left);
	EMU_CODE(
		neurostate& stt = left_side;
		EMU_CK(stt.stabi_num_tier != BJ_INVALID_NUM_TIER);

		bool ok_3 =  false;
		if(ki == nd_neu){
			ok_3 = ((dat->ti + 1) == stt.stabi_num_tier);
		} else {
			ok_3 = (dat->ti == stt.stabi_num_tier);
		}
		
		EMU_CK_PRT(ok_3, "%s %s %ld %s (%d > %d)", stabi_tok_to_str((stabi_tok_t)dat->tok),
			node_kind_to_str(ki), id, net_side_to_str(side_left), (dat->ti + 1), stt.stabi_num_tier);

		//EMU_CK(dat->ti < BJ_DBG_STABI_MAX_TIER); // debug_purposes_only
		EMU_CK(	(bj_nervenet->sync_parent_id != 0) ||
				bj_nervenet->act_left_side.sync_is_inactive ||
				(dat->ti < BJ_DBG_STABI_MAX_TIER)
		); // debug_purposes_only

		EMU_CK(dat->snp != mc_null);
		nervenode* rem_nd = dat->snp->mate->owner;
		EMU_LOG(" ::RECV_stabi_transmitter_%s_t%d_%s [%s %ld <<- %s %ld] #ti%d \n", 
			net_side_to_str(side_left), dat->ti, stabi_tok_to_str((stabi_tok_t)dat->tok), 
			node_kind_to_str(ki), id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
			stt.stabi_num_tier
		);
	);

	switch(dat->tok){
		case bj_tok_stabi_rank:
			stabi_recv_rank(dat);
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
	EMU_CK(pms.snp->owner == this);
	pms.snp->stabi_send_transmitter(bj_tok_stabi_tier_done);
}

void
neurostate::stabi_send_all_ti_done(nervenode* nd, num_tier_t dbg_ti){
	net_side_t sd = side_left;
	EMU_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);

	step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_tier_done, sd);

	EMU_CK((dbg_ti == BJ_INVALID_NUM_TIER) || (nd->ki != nd_neu) || ((dbg_ti + 1) == stabi_num_tier));
	EMU_CK((dbg_ti == BJ_INVALID_NUM_TIER) || (nd->ki == nd_neu) || (dbg_ti == stabi_num_tier));

	EMU_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);
	stabi_num_tier++;

	EMU_LOG("STABI_INC_TIER_%s_t%d_%s_%ld\n", net_side_to_str(sd), stabi_num_tier, 
			node_kind_to_str(nd->ki), nd->id);
}

void
nervenode::stabi_recv_ping(signal_data* dat){
	neurostate& stt = left_side;
	stt.step_num_ping++;

	synset* vssl = dat->snp->stabi_vessel;
	vssl->num_ss_ping++;

	EMU_LOG("STABI_INC_PINGS %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id, net_side_to_str(side_left), 
			stt.step_num_ping, dat->ti);
}

void
synapse::stabi_send_transmitter(stabi_tok_t tok, neurostate* src_nd, bool dbg_is_forced){
	net_side_t sd = side_left;

	if(bj_nervenet->act_left_side.sync_is_ending){ return; }

	num_tier_t ti = owner->left_side.stabi_num_tier;

	EMU_CK(stabi_vessel != mc_null);
	MC_DBG(node_kind_t the_ki = owner->ki);
	MCK_CK((the_ki == nd_pos) || (the_ki == nd_neg) || (the_ki == nd_neu));
	EMU_CODE(nervenode* rem_nd = mate->owner);
	EMU_LOG("::stabi_send_transmitter_%s_t%d_%s [%s %ld ->> %s %s %ld k%d] \n", net_side_to_str(sd), ti, 
		stabi_tok_to_str(tok), node_kind_to_str(owner->ki), owner->id, 
		((dbg_is_forced)?("FORCED"):("")), node_kind_to_str(rem_nd->ki), rem_nd->id, 
		mc_id_to_nn(mc_addr_get_id(mate)));

	stabi_transmitter* trm = stabi_transmitter::acquire();
	trm->src = this;
	trm->dst = mate;
	trm->tok = tok;
	trm->wrk_side = sd;
	trm->wrk_tier = ti;
	if(src_nd != mc_null){
		trm->id_arr_sz = src_nd->stabi_arr_sz;
		trm->id_arr = src_nd->stabi_arr;
		EPH_CODE(
			if(! mc_addr_is_local(mate)){
				trm->id_arr = (num_syn_t*)mck_as_glb_pt(src_nd->stabi_arr);
			}
		);
	}
	trm->send();
}

void
nervenet::stabi_nervenet_start(){
	EMU_LOG("stabi_nervenet_start \n");
	send_all_neus(bj_tok_stabi_start);
	EMU_LOG("end_stabi_nervenet_start \n");
}

void
neuron::stabi_handler(missive* msv){
	stabi_tok_t tok = (stabi_tok_t)msv->tok;

	switch(tok){
		case bj_tok_stabi_start:
			stabi_neuron_start();
		break;
		default:
			mck_abort(1, mc_cstr("BAD_STABI_TOK"));
		break;
	}
}

void
neuron::stabi_neuron_start(){
	EMU_CK(left_side.step_active_set.all_grp.is_alone());
	EMU_CK(right_side.step_active_set.all_grp.is_alone());

	left_side.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_id_arr, side_left);

	left_side.stabi_send_all_ti_done(this, BJ_INVALID_NUM_TIER);
	left_side.step_reset_complete();
}

void
nervenode::stabi_recv_rank(signal_data* dat){
	EMU_CK(dat->sd == side_left);
	nervenode* nd = this;
	netstate& nst = bj_nervenet->act_left_side;
	nst.get_tier(tiki_stabi, nst.all_stabi_tiers, dat->ti, ((ki == nd_neu)?(9):(10)));

	dat->snp->stabi_set_rcv_arr(dat);

	// left_side.stabi_num_tier
	EMU_DBG_CODE(dat->snp->mate->owner->dbg_prt_nod(side_left, tiki_stabi, mc_cstr("stb_RANK"), 8, dat->ti));
	EMU_LOG("stb_RANK_lft_t%d_%s_%d_ stabi_rcv_arr=%s \n", 
		dat->ti, nd->get_ki_str(), nd->id,
		bj_dbg_stabi_id_arr_to_str(dat->snp->stabi_rcv_arr_sz, dat->snp->stabi_rcv_arr, 
			BJ_DBG_STR_CAP, bj_nervenet->dbg_str1)
	);

	synset* vssl = dat->snp->stabi_vessel;
	vssl->num_ss_recv++;
	if((vssl->num_ss_recv + vssl->num_ss_ping) == vssl->tot_syn){
		EMU_DBG_CODE(! mc_get_flag(vssl->ss_flags, bj_ss_ranked_snps_flag));
		vssl->stabi_rank_all_snp(dat, nd);
		EMU_DBG_CODE(mc_set_flag(vssl->ss_flags, bj_ss_ranked_snps_flag));
	}

	//EMU_LOG("STABI_INC_RCV %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id, net_side_to_str(side_left), 
	//		stt.step_num_ping, dat->ti);
}

void
synapse::stabi_set_rcv_arr(signal_data* dat){
	long sz = dat->id_arr_sz;
	if(sz >= BJ_MAX_ID_ARR_SZ){
		mck_abort(1, mc_cstr("FAILED bj_set_id_data."));
	}

	stabi_rcv_arr_sz = dat->id_arr_sz;
	stabi_rcv_arr = dat->id_arr;
	EPH_CODE(
		if(mc_addr_has_id(stabi_rcv_arr)){
			//bj_id_arr_copy(stabi_rcv_arr, stabi_rcv_arr_sz, dat->id_arr);
		}
	);
}

synset*
synset::stabi_get_subset_of(synapse* add_snp, signal_data* dat){
	net_side_t sd = side_left;
	binder * fst, * lst, * wrk, * nxt;
	binder * nn_grp = &all_grp;

	synset* sset = mc_null;
	binder* lft = &all_grp;

	fst = (binder*)(nn_grp->bn_right);
	lst = (binder*)mck_as_loc_pt(nn_grp);
	for(wrk = fst; wrk != lst; wrk = nxt){
		nxt = (binder*)(wrk->bn_right);
		synset* ss = (synset*)wrk;
	
		synapse* snp = ss->get_first_snp(sd);
		EMU_CK(snp != mc_null);

		int vc = bj_cmp_synapses(add_snp, snp, dat);
		if(vc == 0){
			sset = ss;
			break;
		}
		if(vc < 0){
			break;
		}
		if(vc > 0){
			lft = (binder*)ss;
			continue;
		}
	}
	if(sset == mc_null){
		sset = synset::acquire();
		lft->bind_to_my_right(*sset);
	}

	EMU_CK(sset != mc_null);
	return sset;
}

void
synset::stabi_rank_all_snp(signal_data* dat, nervenode* dbg_nd){
	EMU_CK(! all_syn.is_alone());
	EMU_CK(all_grp.is_alone());

	if(all_syn.is_single()){
		EMU_DBG_CODE(dbg_nd->dbg_prt_nod(dat->sd, tiki_stabi, mc_cstr("stb_skip_rnk_single"), 8, dat->ti));
		return;
	}

	net_side_t sd = side_left;
	binder * fst, * lst, * wrk, * nxt;
	binder* nn_all_snp = &all_syn;

	fst = (binder*)(nn_all_snp->bn_right);
	lst = (binder*)mck_as_loc_pt(nn_all_snp);
	for(wrk = fst; wrk != lst; wrk = nxt){
		nxt = (binder*)(wrk->bn_right);

		synapse* my_snp = get_synapse_from_binder(sd, wrk);
		my_snp->let_go();

		synset* sset = stabi_get_subset_of(my_snp, dat);
		sset->add_left_synapse(my_snp, true);
		EMU_CK(my_snp->stabi_vessel == sset);
	}
	EMU_CK(all_syn.is_alone());

	if(all_grp.is_single()){
		fst = (binder*)(all_grp.bn_right);
		fst->let_go();
		EMU_CK(all_grp.is_alone());

		EMU_CODE(synset* sub_grp = (synset*)fst);
		EMU_CK(sub_grp->num_ss_recv == 0);
		EMU_CK(sub_grp->num_ss_ping == 0);
		EMU_CK(sub_grp->tot_syn == tot_syn);
		EMU_CK(sub_grp->all_grp.is_alone());

		bind_to_my_right(*fst);
		release();
	}
}

void
nervenode::stabi_recv_tier_done(signal_data* dat){
	net_side_t sd = side_left;
	nervenode* nd = this;
	neurostate& stt = left_side;

	stt.step_num_complete++;

	EMU_LOG("STABI_ADD_TIER_END %s %ld %s compl(%d of %d) TI=%d \n", 
			node_kind_to_str(ki), id, net_side_to_str(sd), 
			stt.step_num_complete, stt.step_prev_tot_active, dat->ti);

	if(is_tier_complete(dat)){
		recalc_stabi(dat);

		MC_DBG(dbg_prt_tier_done(dat));

		bool to_dly = false;
		netstate& nstt = bj_nervenet->get_active_netstate(sd);
		if((ki == nd_neu)){
			EMU_CK(dat->ti == (stt.stabi_num_tier - 1));
			to_dly = stt.neu_is_to_delay(nstt, nd, tiki_stabi, stt.stabi_num_tier, nstt.all_stabi_tiers, 3);
		}

		char* ts = bj_dbg_tier_kind_to_str(tiki_stabi);
		MC_MARK_USED(ts);
		EMU_LOG("STABI_TIER_COMPLETE_t%d_%s_%ld %s_%s ((%d > 0) && (%d == %d) && (%d < %d)) %s \n", dat->ti, 
					node_kind_to_str(ki), id, ts, ((to_dly)?("TO_DELAY"):("")), 
			stt.step_prev_tot_active, stt.step_num_ping, stt.step_prev_tot_active, 
			get_last_tier(nstt.all_stabi_tiers).tdt_id, (stt.stabi_num_tier - 1),
			(mc_get_flag(stt.step_flags, bj_stt_stabi_intact_id_flag))?("intact"):("")
		);

		if(! to_dly){
			stabi_start_nxt_tier(dat);
		}
	}
}

void
nervenode::stabi_start_nxt_tier(signal_data* dat){
	mck_abort(1, mc_cstr("nervenode::stabi_start_nxt_tier"));
}

void
nervenode::recalc_stabi(signal_data* dat){
	nervenode* nd = this;
	neurostate& stt = nd->get_neurostate(dat->sd);
	stt.calc_stabi_arr(nd, dat);
}

void
polaron::recalc_stabi(signal_data* dat){
	polaron* pol = this;

	neurostate& pol_stt = pol->get_neurostate(dat->sd);
	pol_stt.calc_stabi_arr(pol, dat);

	neurostate& opp_stt = opp->get_neurostate(dat->sd);
	opp_stt.calc_stabi_arr(opp, dat);
}

void
polaron::stabi_start_nxt_tier(signal_data* dat){
	net_side_t sd = side_left;
	polaron* pol = this;
	neurostate& pol_stt = get_neurostate(sd);
	neurostate& opp_stt = opp->get_neurostate(sd);

	EMU_CK(pol_stt.is_full());
	EMU_CK(opp_stt.is_full());

	//MC_DBG(pol->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	//MC_DBG(opp->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));

	//pol_stt.calc_stabi_arr(pol);
	//opp_stt.calc_stabi_arr(opp);

	pol_stt.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_id_arr, side_left);
	opp_stt.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_id_arr, side_left);

	pol_stt.stabi_send_all_ti_done(pol, dat->ti);
	opp_stt.stabi_send_all_ti_done(opp, dat->ti);

	pol_stt.step_reset_complete();
	opp_stt.step_reset_complete();
}

void
nervenode::dbg_prt_tier_done(signal_data* dat){
	net_side_t sd = side_left;
	MC_DBG(dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	EMU_DBG_CODE(dbg_prt_active_synset(sd, tiki_stabi, mc_cstr("ACTi"), dat->ti));
}

void
polaron::dbg_prt_tier_done(signal_data* dat){
	net_side_t sd = side_left;
	polaron* pol = this;
	MC_DBG(pol->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	MC_DBG(opp->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	EMU_DBG_CODE(pol->dbg_prt_active_synset(sd, tiki_stabi, mc_cstr("ACTi"), dat->ti));
	EMU_DBG_CODE(opp->dbg_prt_active_synset(sd, tiki_stabi, mc_cstr("ACTi"), dat->ti));
}

void
neuron::stabi_start_nxt_tier(signal_data* dat){
	neuron* neu = this;
	net_side_t sd = side_left;
	neurostate& stt = get_neurostate(sd);
	netstate& nst = bj_nervenet->get_active_netstate(sd);

	//MC_DBG(dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));

	//stt.calc_stabi_arr(neu);

	stt.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_id_arr, side_left);

	stt.stabi_send_all_ti_done(neu, dat->ti);
	stt.step_reset_complete();

	mck_slog2("dbg2.reset\n");

	nst.update_sync_inert(tiki_stabi, true);
}

void 
nervenode::stabi_send_snp_id_arr(callee_prms& pms){
	EMU_CK(pms.snp != mc_null);
	EMU_CK(pms.snp->owner == this);

	bool snd_png = false;
	if(ki == nd_neu){
		bool is_itct = mc_get_flag(left_side.step_flags, bj_stt_stabi_intact_id_flag);
		snd_png = is_itct;
	} else {
		EMU_CK(bj_is_pol(ki));
		bool all_png = left_side.neu_all_ping(tiki_stabi);
		snd_png = all_png;
	}
	if(snd_png){
		//EMU_CK(! bj_is_pol(ki));
		pms.snp->stabi_send_transmitter(bj_tok_stabi_ping, &left_side);
	} else {
		pms.snp->stabi_send_transmitter(bj_tok_stabi_rank, &left_side);
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
		SYNC_LOG(" SYNCR_STOPPING_CORE_%s \n", net_side_to_str(my_side));
		//mck_get_kernel()->set_idle_exit();
		kernel::stop_sys(bj_tok_propag_end);
	}
}

void
nervenet::stabi_handler(missive* msv){
	mck_token_t msv_tok = msv->tok;
	if(msv_tok == bj_tok_stabi_start){
		stabi_nervenet_start();
		//kernel::stop_sys(bj_tok_stabi_end); // DEBUG purposes only
		return;
	}

	sync_handler(tiki_stabi, msv);
}

void bj_stabi_main() {
	mck_set_sub_module_id(BJ_STABI_SUB_MODULE_STABI);

	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_stabi_init_handlers();

	EMU_LOG("STABI___ %d \n", nn);

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_stabi_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->init_sync_cycle();

	mck_slog2("__dbg2.stabi\n");

	bj_print_active_cnf(side_left, tiki_stabi, mc_cstr("stb_before"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	my_net->send(my_net, bj_tok_stabi_start);
	kernel::run_sys();

	bj_print_active_cnf(side_left, tiki_stabi, mc_cstr("stb_after"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	EMU_PRT("...............................END_STABI\n");
	mck_slog2("END_STABI___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");
	mck_sprt2("dbg2.stabi.end\n");

}

void
synset::stabi_insert_sort(){
	binder * fst, * lst, * wrk;
	grip sorted;
	while(! all_grp.is_alone()){
		synset* add_ss = (synset*)(all_grp.bn_right);
		add_ss->let_go();

		binder* left = &sorted;

		binder* grps = &(sorted);
		fst = (binder*)(grps->bn_right);
		lst = (binder*)mck_as_loc_pt(grps);
		for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
			synset* sub_grp = (synset*)wrk;
			int vc = bj_cmp_num_syn(add_ss->tot_syn, sub_grp->tot_syn);
			if(vc <= 0){ 
				break; 
			} 
			left = (binder*)sub_grp;
		}
		left->bind_to_my_right(*add_ss);
	}
	all_grp.move_all_to_my_right(sorted);
}
