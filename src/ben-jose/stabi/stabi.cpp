
#include "cell.hh"
#include "stabi.hh"

#define BJ_DBG_STABI_MAX_TIER 10

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

	bj_set_id_data(sb_tmt, &dat);

	EMU_CK(dat.sd == side_left);
	EMU_CK(dat.ti != BJ_INVALID_NUM_TIER);

	//if(bj_nervenet->get_active_netstate(dat.sd).sync_ending_propag){ return; }

	nervenode* owr = (nervenode*)(mck_as_loc_pt(owner));
	owr->stabi_recv_transmitter(&dat);
}

void 
synset::stabi_calc_arr_rec(num_syn_t cap, num_syn_t* arr, num_syn_t& ii) {
	MCK_CHECK_SP();

	EMU_CK(ii < cap);
	arr[ii] = tot_syn;
	ii++;

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = (binder*)mck_as_loc_pt(grps);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		EMU_CK(sub_grp->parent == this);
		sub_grp->stabi_calc_arr_rec(cap, arr, ii);
	}

	//EMU_CK(ii < cap);
	//arr[ii] = tot_grp;
	//ii++;
}

// mc_addr_is_local(addr)

void 
neurostate::calc_stabi_arr() {
	if(stabi_arr == mc_null){
		stabi_arr_cap = calc_stabi_arr_cap(step_active_set.tot_syn);
		stabi_arr = mc_malloc32(num_syn_t, stabi_arr_cap);
	}
	stabi_arr_sz = 0;
	step_active_set.stabi_calc_arr_rec(stabi_arr_cap, stabi_arr, stabi_arr_sz);
}

int cmp_neurostate(neurostate* nod1, neurostate* nod2){
	EMU_CK(nod1 != mc_null);
	EMU_CK(nod2 != mc_null);
	num_syn_t sz1 = nod1->stabi_arr_sz;
	num_syn_t sz2 = nod2->stabi_arr_sz;
	num_syn_t* arr1 = nod1->stabi_arr;
	num_syn_t* arr2 = nod2->stabi_arr;

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
	EMU_CK(((stabi_tok_t)msv->tok) == bj_tok_stabi_start);

	//stabi_nervenet();
	kernel::stop_sys(bj_tok_stabi_end);
}

void
nervenode::stabi_recv_transmitter(signal_data* dat){
	EMU_CODE(
		EMU_CK(dat->ti == side_left);
		neurostate& stt = get_neurostate(side_left);
		EMU_CK(stt.propag_num_tier != BJ_INVALID_NUM_TIER);

		bool ok_3 =  false;
		if(ki == nd_neu){
			ok_3 = ((dat->ti + 1) == stt.propag_num_tier);
		} else {
			ok_3 = (dat->ti == stt.propag_num_tier);
		}
		
		EMU_CK_PRT(ok_3, "%s %s %ld %s (%d > %d)", stabi_tok_to_str((stabi_tok_t)dat->tok),
			node_kind_to_str(ki), id, net_side_to_str(side_left), (dat->ti + 1), stt.propag_num_tier);

		//EMU_CK(dat->ti < BJ_DBG_STABI_MAX_TIER); // debug_purposes_only
		EMU_CK(	(bj_nervenet->sync_parent_id != 0) ||
				bj_nervenet->get_active_netstate(side_left).sync_is_inactive ||
				(dat->ti < BJ_DBG_STABI_MAX_TIER)
		); // debug_purposes_only

		EMU_CK(dat->snp != mc_null);
		nervenode* rem_nd = dat->snp->mate->owner;
		EMU_LOG(" ::RECV_stabi_transmitter_%s_t%d_%s [%s %ld <<- %s %ld] #ti%d \n", 
			net_side_to_str(side_left), dat->ti, stabi_tok_to_str((stabi_tok_t)dat->tok), 
			node_kind_to_str(ki), id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
			stt.propag_num_tier
		);
	);

	switch(dat->tok){
		case bj_tok_stabi_rank:
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
	EMU_CK(propag_num_tier != BJ_INVALID_NUM_TIER);

	step_active_set.transmitter_send_all_rec((bj_callee_t)(&nervenode::stabi_send_snp_tier_done), sd);

	EMU_CK((nd->ki != nd_neu) || ((dbg_ti + 1) == propag_num_tier));
	EMU_CK((nd->ki == nd_neu) || (dbg_ti == propag_num_tier));

	EMU_CK(propag_num_tier != BJ_INVALID_NUM_TIER);
	propag_num_tier++;

	EMU_LOG("STABI_INC_TIER_%s_t%d_%s_%ld\n", net_side_to_str(sd), propag_num_tier, 
			node_kind_to_str(nd->ki), nd->id);
}

void
nervenode::stabi_recv_ping(signal_data* dat){
	neurostate& stt = get_neurostate(dat->sd);
	stt.step_num_ping++;

	EMU_LOG("STABI_INC_PINGS %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.step_num_ping, dat->ti);
}

void
nervenode::stabi_recv_tier_done(signal_data* dat){

	neurostate& stt = get_neurostate(dat->sd);

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

	if(bj_nervenet->get_active_netstate(sd).sync_ending_propag){ return; }

	num_tier_t ti = owner->get_neurostate(sd).propag_num_tier;

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

void bj_set_id_data(stabi_transmitter* sb_tmt, signal_data* dat){
	long sz = sb_tmt->id_arr_sz;
	if(sz >= BJ_MAX_ID_ARR_SZ){
		mck_abort(1, mc_cstr("FAILED bj_set_id_data."));
	}

	dat->id_arr_sz = sb_tmt->id_arr_sz;
	dat->id_arr = sb_tmt->id_arr;
	EPH_CODE(
		if(mc_addr_has_id(dat->id_arr)){
			dat->id_arr = bj_nervenet->tmp_id_arr;
			bj_id_arr_copy(dat->id_arr, dat->id_arr_sz, sb_tmt->id_arr);
		}
	);
}

