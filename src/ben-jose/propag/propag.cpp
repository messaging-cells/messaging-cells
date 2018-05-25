
#include "cell.hh"
#include "propag.hh"

#define BJ_DBG_PROPAG_MAX_TIER 10

void 
neuron_propag_handler(missive* msv){
	MCK_CALL_HANDLER(neuron, propag_handler, msv);
}

void 
synapse_propag_handler(missive* msv){
	MCK_CALL_HANDLER(synapse, propag_handler, msv);
}

void 
nervenet_propag_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, propag_handler, msv);
}

void
bj_propag_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;

	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_neuron] = neuron_propag_handler;
	hndlrs[idx_synapse] = synapse_propag_handler;
	hndlrs[idx_nervenet] = nervenet_propag_handler;

	kernel::set_handlers(idx_total, bj_handlers);
}

void
neuron::propag_handler(missive* msv){
	propag_tok_t tok = (propag_tok_t)msv->tok;

	switch(tok){
		case bj_tok_propag_start:
			propag_neuron_start();
		break;
		default:
			mck_abort(1, mc_cstr("BAD_PROPAG_TOK"));
		break;
	}
}

void
synapse::propag_handler(missive* msv){
	transmitter* tmt = (transmitter*)msv;

	signal_data dat;
	dat.msv = msv;
	dat.snp = this;
	dat.tok = (propag_tok_t)(tmt->tok);
	dat.sd = tmt->wrk_side;
	dat.ti = tmt->wrk_tier;

	EMU_CK(dat.ti != BJ_INVALID_NUM_TIER);

	//if(bj_nervenet->get_active_netstate(dat.sd).sync_is_ending){ return; }

	nervenode* owr = (nervenode*)(mck_as_loc_pt(owner));
	owr->propag_recv_transmitter(&dat);
}

void
synapse::propag_send_transmitter(propag_tok_t tok, net_side_t sd, bool dbg_is_forced){
	if(bj_nervenet->get_active_netstate(sd).sync_is_ending){ return; }

	num_tier_t ti = owner->get_neurostate(sd).propag_num_tier;

	EMU_CK(stabi_vessel == mc_null);
	MC_DBG(node_kind_t the_ki = owner->ki);
	MCK_CK((the_ki == nd_pos) || (the_ki == nd_neg) || (the_ki == nd_neu));
	EMU_CODE(nervenode* rem_nd = mate->owner);
	EMU_LOG("::propag_send_transmitter_%s_t%d_%s [%s %ld ->> %s %s %ld k%d] \n", net_side_to_str(sd), ti, 
		propag_tok_to_str(tok), node_kind_to_str(owner->ki), owner->id, 
		((dbg_is_forced)?("FORCED"):("")), node_kind_to_str(rem_nd->ki), rem_nd->id, 
		mc_id_to_nn(mc_addr_get_id(mate)));

	transmitter* trm = transmitter::acquire();
	trm->src = this;
	trm->dst = mate;
	trm->tok = tok;
	trm->wrk_side = sd;
	trm->wrk_tier = ti;
	trm->send();
}

void
nervenet::propag_nervenet_start(){
	EMU_LOG("propag_nervenet_start \n");

	send_all_neus(bj_tok_propag_start);

	EMU_DBG_CODE(
		netstate& lft = get_active_netstate(side_left);
		netstate& rgt = get_active_netstate(side_right);
	);
	EMU_CK(lft.get_tier(tiki_propag, lft.all_propag_tiers, 0, 2).rcv_neus == 0);
	EMU_CK(rgt.get_tier(tiki_propag, rgt.all_propag_tiers, 0, 3).rcv_neus == 0);

	EMU_LOG("end_propag_nervenet_start \n");
}

void
neuron::propag_neuron_start(){
	EMU_CK(left_side.propag_tiers.is_alone());
	EMU_CK(left_side.step_active_set.all_grp.is_alone());

	EMU_CK(right_side.propag_tiers.is_alone());
	EMU_CK(right_side.step_active_set.all_syn.is_alone());
	EMU_CK(right_side.step_active_set.all_grp.is_alone());

	EMU_CK(left_side.step_active_set.all_grp.is_alone());
	//left_side.step_active_set.reset_tree(side_left);

	left_side.step_active_set.transmitter_send_all_rec(&nervenode::propag_send_snp_propag, side_left);

	left_side.propag_send_all_ti_done(this, side_left, BJ_INVALID_NUM_TIER);
	left_side.step_reset_complete();
}

void 
neuron::propag_send_snp_propag(callee_prms& pms){
	neurostate& stt = get_neurostate(pms.sd);

	EMU_CK(pms.snp != mc_null);
	EMU_CK(pms.snp->owner == this);
	EMU_CK(! stt.step_active_set.is_synset_empty());
	if(stt.step_active_set.tot_syn == 1){
		EMU_LOG("FORCING %s %ld %s  TI=%d flags=%p flgs_pt=%p \n", node_kind_to_str(ki), id, 
			net_side_to_str(pms.sd), get_neurostate(pms.sd).propag_num_tier, (void*)(uintptr_t)stt.step_flags,
			(void*)(&stt.step_flags));

		pms.snp->propag_send_transmitter(bj_tok_propag_charge_all, pms.sd, pms.rec /*IS_FORCED*/);
	} else {
		pms.snp->propag_send_transmitter(bj_tok_propag_ping, pms.sd);
	}
}

void 
nervenode::propag_send_snp_tier_done(callee_prms& pms){
	EMU_CK(pms.snp->owner == this);
	pms.snp->propag_send_transmitter(bj_tok_propag_tier_done, pms.sd);
}

void
neurostate::propag_send_all_ti_done(nervenode* nd, net_side_t sd, num_tier_t dat_ti){
	if(dat_ti != BJ_INVALID_NUM_TIER){ 
		EMU_CK((nd->ki != nd_neu) || ((dat_ti + 1) == propag_num_tier));
		EMU_CK((nd->ki == nd_neu) || (dat_ti == propag_num_tier));

		tierset* c_ti = get_tiset(dat_ti);
		if(c_ti != mc_null){
			//EMU_CK((nd->ki != nd_neu) || ! mc_get_flag(step_flags, bj_stt_charge_all_flag));
			EMU_LOG("::propag_send_all_ti_done WITH_PRV_TI %s %ld %s \n", node_kind_to_str(nd->ki), 
					nd->id, net_side_to_str(sd));
			with_all_synapses(&(c_ti->ti_all), &nervenode::propag_send_snp_tier_done, sd);
		}
	}

	step_active_set.transmitter_send_all_rec(&nervenode::propag_send_snp_tier_done, sd);

	EMU_CK(propag_num_tier != BJ_INVALID_NUM_TIER);
	propag_num_tier++;

	EMU_LOG("PROPAG_INC_TIER_%s_t%d_%s_%ld\n", net_side_to_str(sd), propag_num_tier, 
			node_kind_to_str(nd->ki), nd->id);
}

void
nervenode::propag_recv_transmitter(signal_data* dat){

	EMU_CODE(
		neurostate& stt = get_neurostate(dat->sd);
		EMU_CK(dat->ti != BJ_INVALID_NUM_TIER);
		EMU_CK(stt.propag_num_tier != BJ_INVALID_NUM_TIER);

		bool ok_3 =  false;
		if(ki == nd_neu){
			ok_3 = ((dat->ti + 1) == stt.propag_num_tier);
		} else {
			ok_3 = (dat->ti == stt.propag_num_tier);
		}
		
		EMU_CK_PRT(ok_3, "%s %s %ld %s (%d > %d)", propag_tok_to_str((propag_tok_t)dat->tok),
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), (dat->ti + 1), stt.propag_num_tier);

		//EMU_CK(dat->ti < BJ_DBG_PROPAG_MAX_TIER); // debug_purposes_only
		EMU_CK(	(bj_nervenet->sync_parent_id != 0) ||
				bj_nervenet->get_active_netstate(dat->sd).sync_is_inactive ||
				(dat->ti < BJ_DBG_PROPAG_MAX_TIER)
		); // debug_purposes_only

		EMU_CK(dat->snp != mc_null);
		nervenode* rem_nd = dat->snp->mate->owner;
		EMU_LOG(" ::RECV_transmitter_%s_t%d_%s [%s %ld <<- %s %ld] #ti%d \n", 
			net_side_to_str(dat->sd), dat->ti, propag_tok_to_str((propag_tok_t)dat->tok), 
			node_kind_to_str(ki), id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
			stt.propag_num_tier
		);
	);

	switch(dat->tok){
		case bj_tok_propag_charge_all:
			propag_recv_charge_all(dat);
		break;
		case bj_tok_propag_charge_src:
			propag_recv_charge_src(dat);
		break;
		case bj_tok_propag_ping:
			propag_recv_ping(dat);
		break;
		case bj_tok_propag_tier_done:
			propag_recv_tier_done(dat);
		break;
		default:
			mck_abort(1, mc_cstr("nervenode::propag_recv_propag. BAD_PROPAG_TOK"));
		break;
	}
}

bool
neurostate::charge_all_active(signal_data* dat, node_kind_t ki){
	EMU_CK(step_active_set.all_grp.is_alone());
	//step_active_set.reset_tree(dat->sd);

	bool resp = false;
	if(! step_active_set.is_synset_empty()){

		resp = true;
		tierset& ti_grp = add_tiset(dat->ti);
		ti_grp.ti_all.move_all_to_my_right(step_active_set.all_syn);

		step_active_set.tot_syn = 0;
		step_num_ping = 0;

		if(ki == nd_neu){
			netstate& nst = bj_nervenet->get_active_netstate(dat->sd);
			nst.get_tier(tiki_propag, nst.all_propag_tiers, dat->ti, 4).inc_off();
		}
	}
	EMU_CK(step_active_set.is_synset_empty());
	resp = (resp && ! propag_tiers.is_alone()); 
	return resp;
}

void
nervenode::propag_recv_charge_all(signal_data* dat){
	EMU_CK(dat != mc_null);
	EMU_CK(dat->sd != side_invalid);

	netstate& nst = bj_nervenet->get_active_netstate(dat->sd);
	nst.get_tier(tiki_propag, nst.all_propag_tiers, dat->ti, 5);

	neurostate& stt = get_neurostate(dat->sd);

	EMU_LOG("nervenode::propag_recv_charge_all %s %ld %s stb_src=%p \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), stt.propag_source);

	if(stt.propag_source != mc_null){
		return;
	}

	if(bj_is_pol(ki) && stt.step_active_set.is_synset_empty()){
		EMU_CODE(neurostate& ott = ((polaron*)this)->opp->get_neurostate(dat->sd));
		EMU_CK((ott.propag_source != mc_null) && ott.step_active_set.is_synset_empty());
		return;
	}

	EMU_CK(dat->snp != mc_null);
	EMU_CODE(nervenode* stb_src = dat->snp->mate->owner);
	EMU_CK(stb_src != mc_null);

	EMU_LOG("SET_STB_SRC %s %ld %s stb_src: %s %ld \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			node_kind_to_str(stb_src->ki), stb_src->id);

	EMU_CK_LOG(! stt.step_active_set.is_synset_empty(), 
		"::propag_recv_charge_all EMPTY_ACTIVE !!! stb_src: %s %ld \n", 
		node_kind_to_str(stb_src->ki), stb_src->id);

	mc_set_flag(stt.step_flags, bj_stt_charge_all_flag);
	stt.propag_source = dat->snp;	
}

binder&
synapse::get_side_binder(net_side_t sd){
	if(sd == side_right){
		return right_handle;
	}
	return *((binder*)this);
}

void
nervenode::propag_recv_charge_src(signal_data* dat){
	EMU_CK(dat != mc_null);
	EMU_CK(dat->sd != side_invalid);

	netstate& nst = bj_nervenet->get_active_netstate(dat->sd);
	nst.get_tier(tiki_propag, nst.all_propag_tiers, dat->ti, ((ki == nd_neu)?(6):(7)));

	neurostate& stt = get_neurostate(dat->sd);

	EMU_CK(stt.step_active_set.all_grp.is_alone());
	//stt.step_active_set.reset_tree(dat->sd);

	if(stt.step_active_set.is_synset_empty()){
		return;
	}

	tierset& ti_grp = stt.add_tiset(dat->ti);

	EMU_CK(dat->snp != mc_null);
	binder& bdr = dat->snp->get_side_binder(dat->sd);
	bdr.let_go();
	ti_grp.ti_all.bind_to_my_left(bdr);

	stt.step_active_set.tot_syn--;

	if(stt.step_active_set.is_synset_empty()){
		stt.step_num_ping = 0;
		if(ki == nd_neu){
			nst.get_tier(tiki_propag, nst.all_propag_tiers, dat->ti, 8).inc_off();
		}
	}
	
}

void
nervenode::propag_recv_ping(signal_data* dat){
	neurostate& stt = get_neurostate(dat->sd);
	stt.step_num_ping++;

	EMU_LOG("INC_PINGS %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.step_num_ping, dat->ti);
}

void
nervenode::propag_recv_tier_done(signal_data* dat){

	nervenode* nd = this;
	neurostate& stt = get_neurostate(dat->sd);

	stt.step_num_complete++;

	EMU_LOG("ADD_TIER_END %s %ld %s compl(%d of %d) TI=%d \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.step_num_complete, stt.step_prev_tot_active, dat->ti);

	if(is_tier_complete(dat)){
		bool to_dly = false;
		netstate& nstt = bj_nervenet->get_active_netstate(dat->sd);
		if((ki == nd_neu)){
			EMU_CK(dat->ti == (stt.propag_num_tier - 1));
			to_dly = stt.neu_is_to_delay(nstt, nd, tiki_propag, stt.propag_num_tier, nstt.all_propag_tiers, 2);
		}

		char* ts = bj_dbg_tier_kind_to_str(tiki_propag);
		MC_MARK_USED(ts);
		EMU_LOG("PROPAG_TIER_COMPLETE_%s_t%d_%s_%ld %s_%s ((%d > 1) && (%d == %d) && (%d < %d)) \n", 
			net_side_to_str(dat->sd), dat->ti, node_kind_to_str(ki), id, ts, ((to_dly)?("TO_DELAY"):("")), 
			stt.step_prev_tot_active, stt.step_num_ping, stt.step_prev_tot_active, 
			get_last_tier(nstt.all_propag_tiers).tdt_id, (stt.propag_num_tier - 1)
		);

		if(! to_dly){
			propag_start_nxt_tier(dat);
		}
	}
}

void 
nervenode::propag_send_snp_charge_src(callee_prms& pms){
	EMU_CK(pms.snp->owner == this);
	pms.snp->propag_send_transmitter(bj_tok_propag_charge_src, pms.sd);
}

void 
nervenode::propag_send_snp_propag(callee_prms& pms){
	EMU_CK(pms.snp != mc_null);
	EMU_CK(pms.snp->owner == this);
	pms.snp->propag_send_transmitter(bj_tok_propag_ping, pms.sd);
}

void 
polaron::propag_send_snp_charge_all(callee_prms& pms){
	EMU_CK(pms.snp->owner == this);
	pms.snp->propag_send_transmitter(bj_tok_propag_charge_all, pms.sd);
}

bool
synset::is_synset_empty(){
	if(tot_syn == 0){
		EMU_CK(all_syn.is_alone());
		EMU_CK(all_grp.is_alone());
		return true;
	}
	EMU_CK(! (all_syn.is_alone() && all_grp.is_alone()) || (tot_syn == 0));
	EMU_CK(! all_syn.is_alone() || ! all_grp.is_alone());
	return false;
}

void
nervenode::propag_start_nxt_tier(signal_data* dat){
	mck_abort(1, mc_cstr("nervenode::propag_start_nxt_tier"));
}

tierset*
neurostate::get_tiset(num_tier_t nti){
	if(nti == BJ_INVALID_NUM_TIER){ return mc_null; }
	EMU_CK(nti != BJ_INVALID_NUM_TIER);
	if(propag_tiers.is_alone()){
		return mc_null;
	}
	tierset* tis = (tierset*)propag_tiers.bn_left;
	EMU_CK(tis->ti_id != BJ_INVALID_NUM_TIER);
	if(nti == BJ_LAST_TIER){
		return tis;
	}
	if(tis->ti_id != nti){
		EMU_CK_PRT(tis->ti_id < nti, "(%d < %d)", tis->ti_id, nti);
		return mc_null;
	}
	return tis;
}

tierset&
neurostate::add_tiset(num_tier_t nti){
	EMU_CK(nti != BJ_INVALID_NUM_TIER);

	tierset* tis = get_tiset(nti);
	if(tis == mc_null){
		tis = tierset::acquire();
		EMU_CK(tis->ti_all.is_alone());

		tis->ti_id = nti;
		propag_tiers.bind_to_my_left(*tis);
	}
	return *tis;
}

bool
neurostate::is_mono(num_tier_t nti){
	//EMU_LOG("MO_VALS_t%d_ %d %d %d \n", nti, step_active_set.is_synset_empty(), 
	//		(propag_source == mc_null), (get_tiset(nti) != mc_null));
	//bool mo = (step_active_set.is_synset_empty() && (propag_source == mc_null) && (get_tiset(nti) != mc_null));
	bool mo = (step_active_set.is_synset_empty() && (propag_source == mc_null));
	//bool mo = false;
	return mo;
}

void
neurostate::send_all_propag(nervenode* nd, signal_data* dat){
	tierset* c_ti = get_tiset(dat->ti);
	if(c_ti != mc_null){
		with_all_synapses(&(c_ti->ti_all), &nervenode::propag_send_snp_propag, dat->sd);
	}

	//mck_slog2("dbg1.bef_rec_send_3 \n");
	step_active_set.transmitter_send_all_rec(&nervenode::propag_send_snp_propag, dat->sd);
	//mck_slog2("dbg1.aft_rec_send_3 \n");
}

void
polaron::propag_start_nxt_tier(signal_data* dat){
	polaron* pol = this;
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);

	EMU_CK(pol_stt.is_full());
	EMU_CK(opp_stt.is_full());

	bool pol_chg = mc_get_flag(pol_stt.step_flags, bj_stt_charge_all_flag);
	bool opp_chg = mc_get_flag(opp_stt.step_flags, bj_stt_charge_all_flag);

	EMU_CK(! pol_chg || (pol_stt.propag_source != mc_null));
	EMU_CK(! opp_chg || (opp_stt.propag_source != mc_null));

	if(pol_chg && opp_chg){
		EMU_LOG("POL_CONFLICT %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
		EMU_CODE(dbg_prt_nod(dat->sd, tiki_propag, mc_cstr("POL_CONFLICT__"), 7, dat->ti));

		send_confl_tok(dat, bj_tok_sync_confl_up_pol);
		charge_all_confl_and_start_nxt_ti(dat);

	} else 
	if(pol_chg && ! opp_chg){
		pol->charge_all_and_start_nxt_ti(dat);
	} else
	if(! pol_chg && opp_chg){
		opp->charge_all_and_start_nxt_ti(dat);
	} else 
	if(! pol_chg && ! opp_chg){
		bool pol_mono = pol_stt.is_mono(dat->ti);
		bool opp_mono = opp_stt.is_mono(dat->ti);

		if(pol_mono && ! opp_mono){
			EMU_LOG("MONO_CASE_%s_t%d_ %s %ld \n", net_side_to_str(dat->sd), dat->ti, 
				node_kind_to_str(opp->ki), opp->id);
			EMU_CK(opp_stt.propag_source == mc_null);
			opp->charge_all_and_start_nxt_ti(dat);
		} else 
		if(! pol_mono && opp_mono){
			EMU_LOG("MONO_CASE_%s_t%d_ %s %ld \n", net_side_to_str(dat->sd), dat->ti, 
				node_kind_to_str(pol->ki), pol->id);
			EMU_CK(pol_stt.propag_source == mc_null);
			pol->charge_all_and_start_nxt_ti(dat);
		} else {
			pol_stt.send_all_propag(pol, dat);
			opp_stt.send_all_propag(opp, dat);
		}
	} 

	/*SYNC_LOG("ALL_PING_DATA_p%d_n%d.POL.prv_act=%d,(%d==%d).OPP.prv_act=%d,(%d==%d)\n", 
			pol_stt.propag_num_tier, opp_stt.propag_num_tier,
			pol_stt.step_prev_tot_active, pol_stt.step_num_ping, pol_stt.step_active_set.tot_syn,
			opp_stt.step_prev_tot_active, opp_stt.step_num_ping, opp_stt.step_active_set.tot_syn
	);*/

	pol_stt.propag_send_all_ti_done(pol, dat->sd, dat->ti);
	opp_stt.propag_send_all_ti_done(opp, dat->sd, dat->ti);

	pol_stt.step_reset_complete();
	opp_stt.step_reset_complete();
}

void 
netstate::send_up_confl_tok(sync_tok_t the_tok, num_tier_t the_ti, nervenode* the_cfl)
{
	EMU_CK((the_tok == bj_tok_sync_confl_up_neu) || (the_tok == bj_tok_sync_confl_up_pol));

	mc_core_id_t pnt_id = bj_nervenet->sync_parent_id;
	if(pnt_id != 0){
		nervenet* pnt_net = bj_nervenet->get_nervenet(pnt_id);
		send_sync_transmitter(tiki_propag, pnt_net, the_tok, the_ti, the_cfl);
	} else {
		if(the_tok == bj_tok_sync_confl_up_neu){
			the_tok = bj_tok_sync_confl_down_neu;
		}
		if(the_tok == bj_tok_sync_confl_up_pol){
			the_tok = bj_tok_sync_confl_down_pol;
		}
		send_sync_to_children(the_tok, the_ti, tiki_propag, the_cfl);
	}
}

void
nervenode::send_confl_tok(signal_data* dat, sync_tok_t the_tok){
	netstate& nstt = bj_nervenet->get_active_netstate(dat->sd);
	nstt.send_up_confl_tok(the_tok, dat->ti, this);
}

void
polaron::charge_all_confl_and_start_nxt_ti(signal_data* dat){
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);

	pol_stt.charge_all_active(dat, ki); 
	tierset* ti_grp = pol_stt.get_tiset(dat->ti);
	if(ti_grp != mc_null){
		with_all_synapses(&(ti_grp->ti_all), &nervenode::propag_send_snp_charge_src, dat->sd);
	}

	opp_stt.charge_all_active(dat, opp->ki);	// set opp too
	tierset* opp_ti_grp = opp_stt.get_tiset(dat->ti);
	if(opp_ti_grp != mc_null){
		with_all_synapses(&(opp_ti_grp->ti_all), &nervenode::propag_send_snp_charge_src, dat->sd);
	}
}

void
polaron::charge_all_and_start_nxt_ti(signal_data* dat){
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);

	pol_stt.charge_all_active(dat, ki); 
	tierset* ti_grp = pol_stt.get_tiset(dat->ti);
	if(ti_grp != mc_null){
		with_all_synapses(&(ti_grp->ti_all), (bj_callee_t)(&polaron::propag_send_snp_charge_all), dat->sd);
	}

	opp_stt.charge_all_active(dat, opp->ki);	// set opp too
	tierset* opp_ti_grp = opp_stt.get_tiset(dat->ti);
	if(opp_ti_grp != mc_null){
		with_all_synapses(&(opp_ti_grp->ti_all), &nervenode::propag_send_snp_charge_src, dat->sd);
	}
}

void
neuron::propag_start_nxt_tier(signal_data* dat){
	neurostate& stt = get_neurostate(dat->sd);

	bool chgd_all = mc_get_flag(stt.step_flags, bj_stt_charge_all_flag);
	if(chgd_all){
		EMU_CK(stt.propag_source != mc_null);
		stt.charge_all_active(dat, ki);
		tierset* ti_grp = stt.get_tiset(dat->ti);
		if(ti_grp != mc_null){
			EMU_LOG("dbg1.charged_all_t%d pti=%d \n", dat->ti, stt.propag_num_tier);
			with_all_synapses(&(ti_grp->ti_all), &nervenode::propag_send_snp_charge_src, dat->sd);
			EMU_LOG("dbg1.sent_snp_chg_t%d pti=%d \n", dat->ti, stt.propag_num_tier);
		}
	} else {
		if(stt.step_active_set.is_synset_empty() && (stt.propag_source == mc_null)){
			EMU_LOG("NEU_CONFLICT %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
			EMU_CODE(dbg_prt_nod(dat->sd, tiki_propag, mc_cstr("NEU_CONFLICT__"), 7, dat->ti));

			send_confl_tok(dat, bj_tok_sync_confl_up_neu);
		} else {
			stt.send_all_propag(this, dat);
		}
	}

	EMU_LOG("nxt_ti_%s_t%d_%s_%ld \n", net_side_to_str(dat->sd), dat->ti, node_kind_to_str(ki), id);

	netstate& nst = bj_nervenet->get_active_netstate(dat->sd);

	MC_DBG(dbg_prt_nod(dat->sd, tiki_propag, mc_cstr("TIER__"), 7, dat->ti));

	stt.propag_send_all_ti_done(this, dat->sd, dat->ti);
	stt.step_reset_complete();

	mck_slog2("dbg1.reset\n");

	nst.update_sync_inert(tiki_propag);
}

void bj_propag_main() {
	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_propag_init_handlers();

	EMU_LOG("PROPAG___ %d \n", nn);

	bj_print_loaded_cnf();
	bj_print_active_cnf(side_left, tiki_propag, mc_cstr("LOADED "), 3, 0, true);

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_propag_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->init_sync_cycle();

	EMU_CODE(if(kernel::get_core_nn() == 0){ emu_prt_tok_codes(); });

	mck_ilog(sizeof(mck_glb_sys_st));
	mck_slog2("__dbg1.propag\n");

	my_net->send(my_net, bj_tok_propag_start);
	kernel::run_sys();

	bj_print_active_cnf(side_left, tiki_propag, mc_cstr("REDUCED "), 5, 0);
	bj_print_active_cnf(side_left, tiki_propag, mc_null, 7, BJ_INVALID_NUM_TIER);

	EMU_PRT("...............................END_PROPAG\n");
	mck_slog2("END_PROPAG___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");
	mck_sprt2("dbg1.propag.end\n");

}

void bj_propag_kernel_func(){
	nervenet* my_net = bj_nervenet;
	my_net->propag_handle_sync();
}

void 
nervenet::propag_handle_sync(){
	act_left_side.propag_handle_my_sync();
	act_right_side.propag_handle_my_sync();

	if(act_left_side.sync_is_ending && act_right_side.sync_is_ending){
		//mck_get_kernel()->set_idle_exit();
		tierdata& lti_lft = get_last_tier(act_left_side.all_propag_tiers);
		lti_lft.proc_delayed(tiki_propag, act_left_side.all_propag_tiers, side_left, false);

		tierdata& lti_rgt = get_last_tier(act_right_side.all_propag_tiers);
		lti_rgt.proc_delayed(tiki_propag, act_right_side.all_propag_tiers, side_left, false);

		kernel::stop_sys(bj_tok_propag_end);
	}
}

void
netstate::propag_handle_my_sync(){
	update_sync_inert(tiki_propag);
}

/*
bool
netstate::dbg_prt_all_propag_tiers(){
	binder * fst, * lst, * wrk;

	EMU_PRT("all_tier=[\n");

	binder* tis = &(all_propag_tiers);
	fst = (binder*)(tis->bn_left);
	lst = (binder*)mck_as_loc_pt(tis);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_left)){
		tierdata* tda = (tierdata*)wrk;
		MC_MARK_USED(tda);
		EMU_PRT("ti%d__ [%d,%d,%d,%d] \n", tda->tdt_id, 
			tda->inp_neus, tda->off_neus, tda->rcv_neus, tda->stl_neus
		);
	}

	EMU_PRT("all_tier=[\n");
	return true;
}*/

void
nervenet::propag_handler(missive* msv){
	mck_token_t msv_tok = msv->tok;
	if(msv_tok == bj_tok_propag_start){
		propag_nervenet_start();
		return;
	}

	sync_handler(tiki_propag, msv);
}

