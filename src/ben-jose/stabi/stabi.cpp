
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

	//if(bj_nervenet->act_left_side.sync_ending_propag){ return; }

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
neurostate::calc_stabi_arr() {
	stabi_arr_sz = 0;
	stabi_arr_cap = 0;
	if(stabi_arr != mc_null){
		mc_free32(stabi_arr);
		stabi_arr = mc_null;
	}

	if(step_active_set.is_synset_empty()){
		return;
	}

	EMU_CK(stabi_arr == mc_null);

	stabi_arr_cap = calc_stabi_arr_cap(step_active_set.tot_syn);
	stabi_arr = mc_malloc32(num_syn_t, stabi_arr_cap);

	EMU_LOG(" calc_stabi_arr new_cap=%d \n", stabi_arr_cap);
	EMU_CK(stabi_arr != mc_null);

	step_active_set.stabi_calc_arr_rec(stabi_arr_cap, stabi_arr, stabi_arr_sz);
}

int cmp_synapses(synapse* snp1, synapse* snp2){
	EMU_CK(snp1 != mc_null);
	EMU_CK(snp2 != mc_null);
	num_syn_t sz1 = snp1->stabi_rcv_arr_sz;
	num_syn_t sz2 = snp2->stabi_rcv_arr_sz;
	num_syn_t* arr1 = snp1->stabi_rcv_arr;
	num_syn_t* arr2 = snp2->stabi_rcv_arr;

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

void
nervenet::stabi_handler(missive* msv){
	mck_token_t msv_tok = msv->tok;
	if(msv_tok == bj_tok_stabi_start){
		//stabi_nervenet_start();
		kernel::stop_sys(bj_tok_stabi_end);
		return;
	}

}

void
nervenode::stabi_recv_transmitter(signal_data* dat){
	EMU_CODE(
		EMU_CK(dat->sd == side_left);
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
			mck_abort(1, mc_cstr("nervenode::propag_recv_propag. BAD_PROPAG_TOK"));
		break;
	}
}

void 
nervenode::stabi_send_snp_tier_done(synapse* snp, bool from_rec){
	EMU_CK(snp->owner == this);
	snp->stabi_send_transmitter(bj_tok_stabi_tier_done);
}

void
neurostate::stabi_send_all_ti_done(nervenode* nd, num_tier_t dbg_ti){
	net_side_t sd = side_left;
	EMU_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);

	step_active_set.transmitter_send_all_rec((bj_callee_t)(&nervenode::stabi_send_snp_tier_done), sd);

	EMU_CK((nd->ki != nd_neu) || ((dbg_ti + 1) == stabi_num_tier));
	EMU_CK((nd->ki == nd_neu) || (dbg_ti == stabi_num_tier));

	EMU_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);
	stabi_num_tier++;

	EMU_LOG("STABI_INC_TIER_%s_t%d_%s_%ld\n", net_side_to_str(sd), stabi_num_tier, 
			node_kind_to_str(nd->ki), nd->id);
}

void
nervenode::stabi_recv_ping(signal_data* dat){
	EMU_CK(dat->sd == side_left);
	neurostate& stt = left_side;
	stt.step_num_ping++;

	synset* vssl = dat->snp->stabi_vessel;
	vssl->num_ss_ping++;

	EMU_LOG("STABI_INC_PINGS %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.step_num_ping, dat->ti);
}

void
nervenode::stabi_recv_tier_done(signal_data* dat){

	EMU_CK(dat->sd == side_left);
	neurostate& stt = left_side;

	stt.step_num_complete++;

	EMU_LOG("STABI_ADD_TIER_END %s %ld %s compl(%d of %d) TI=%d \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.step_num_complete, stt.step_prev_tot_active, dat->ti);

	if(is_tier_complete(dat)){
		if((ki == nd_neu)){
		}

		EMU_LOG("STABI_TIER_COMPLETE_%s_t%d_%s_%ld \n", net_side_to_str(dat->sd), dat->ti, 
					node_kind_to_str(ki), id);
	}
}

void
synapse::stabi_send_transmitter(stabi_tok_t tok, neurostate* src_nd, bool dbg_is_forced){
	net_side_t sd = side_left;

	if(bj_nervenet->act_left_side.sync_ending_propag){ return; }

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
	EMU_CK(left_side.propag_tiers.is_alone());
	EMU_CK(left_side.step_active_set.all_grp.is_alone());

	EMU_CK(right_side.propag_tiers.is_alone());
	EMU_CK(right_side.step_active_set.all_syn.is_alone());
	EMU_CK(right_side.step_active_set.all_grp.is_alone());

	EMU_CK(left_side.step_active_set.all_grp.is_alone());

	left_side.step_active_set.transmitter_send_all_rec(
			(bj_callee_t)(&nervenode::stabi_send_snp_id_arr), side_left);

	left_side.stabi_send_all_ti_done(this, BJ_INVALID_NUM_TIER);
	left_side.step_reset_complete();
}

void 
nervenode::stabi_send_snp_id_arr(callee_prms& pms){
	EMU_CK(pms.snp != mc_null);
	EMU_CK(pms.snp->owner == this);
	pms.snp->stabi_send_transmitter(bj_tok_stabi_rank, &left_side);
}

void
nervenode::stabi_recv_rank(signal_data* dat){
	EMU_CK(dat->sd == side_left);
	neurostate& stt = left_side;
	MC_MARK_USED(stt);

	synset* vssl = dat->snp->stabi_vessel;

	dat->snp->stabi_set_rcv_arr(dat);

	vssl->num_ss_recv++;
	if((vssl->num_ss_recv + vssl->num_ss_ping) == vssl->tot_syn){
		vssl->stabi_rank_all_snp();
	}

	EMU_LOG("STABI_INC_RCV %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.step_num_ping, dat->ti);
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
			bj_id_arr_copy(stabi_rcv_arr, stabi_rcv_arr_sz, dat->id_arr);
		}
	);
}

synapse*
synset::get_first_snp(net_side_t sd){
	if(all_syn.is_alone()){
		return mc_null;
	}
	binder* fst = (binder*)(all_syn.bn_right);
	synapse* snp = get_synapse_from_binder(sd, fst);
	return snp;
}

synset*
synset::stabi_get_subset_of(synapse* add_snp){
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

		int vc = cmp_synapses(add_snp, snp);
		if(vc == 0){
			sset = ss;
			break;
		}
		if(vc == -1){
			break;
		}
		if(vc == 1){
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
synset::stabi_rank_all_snp(){
	EMU_CK(! all_syn.is_alone());
	EMU_CK(all_grp.is_alone());

	if(all_syn.is_single()){
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

		synset* sset = stabi_get_subset_of(my_snp);
		sset->add_left_synapse(my_snp, true);
		EMU_CK(my_snp->stabi_vessel == sset);
	}
	EMU_CK(all_syn.is_alone());

	if(all_grp.is_single()){
		fst = (binder*)(all_grp.bn_right);
		fst->let_go();
		EMU_CK(all_grp.is_alone());

		bind_to_my_right(*fst);
		release();
	}
}

