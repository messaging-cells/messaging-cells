
#include "cell.hh"

#include "stabi.hh"

// DBG_COREDUMP

#define BJ_DBG_MAX_TIER 10


neurostate& 
nervenode::get_neurostate(net_side_t sd){
	EMU_CK(sd != side_invalid);

	neurostate* out_stt = &left_side;
	if(sd == side_right){
		out_stt = &right_side;
	}
	EMU_CK(out_stt != mc_null);
	return *out_stt;
}

netstate& 
nervenet::get_active_netstate(net_side_t sd){
	EMU_CK(sd != side_invalid);

	netstate* out_stt = &act_left_side;
	if(sd == side_right){
		out_stt = &act_right_side;
	}
	EMU_CK(out_stt != mc_null);
	return *out_stt;
}

void
synapse::send_transmitter(stabi_tok_t tok, net_side_t sd, bool dbg_is_forced){
	if(bj_nervenet->get_active_netstate(sd).sync_ending_propag){ return; }

	num_tier_t ti = owner->get_neurostate(sd).stabi_num_tier;

	MC_DBG(node_kind_t the_ki = owner->ki);
	MCK_CK((the_ki == nd_pos) || (the_ki == nd_neg) || (the_ki == nd_neu));
	EMU_CODE(nervenode* rem_nd = mate->owner);
	EMU_LOG("::send_transmitter %s %s [%s %ld ->> %s %s %ld k%d] wrk_TI=%d  \n", stabi_tok_to_str(tok), 
 		net_side_to_str(sd), node_kind_to_str(owner->ki), owner->id, 
		((dbg_is_forced)?("FORCED"):("")), node_kind_to_str(rem_nd->ki), rem_nd->id, 
		mc_id_to_nn(mc_addr_get_id(mate)), ti);

	transmitter* trm = transmitter::acquire();
	trm->src = this;
	trm->dst = mate;
	trm->tok = tok;
	trm->wrk_side = sd;
	trm->wrk_tier = ti;
	trm->send();
}

void 
polaron_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(polaron, stabi_handler, msv);
}

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
	OLD_SYNC_MTH(MCK_CALL_HANDLER(nervenet, stabi_nn_handler, msv));
	NEW_SYNC_MTH(MCK_CALL_HANDLER(nervenet, stabi_sync_handler, msv));
}

void
bj_stabi_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;

	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_polaron] = polaron_stabi_handler;
	hndlrs[idx_neuron] = neuron_stabi_handler;
	hndlrs[idx_synapse] = synapse_stabi_handler;
	hndlrs[idx_nervenet] = nervenet_stabi_handler;

	kernel::set_handlers(idx_total, bj_handlers);
}

/*
void 
synset::calc_stabi_arr_rec(num_syn_t cap, num_syn_t* arr, num_syn_t& ii) { // careful with stack usage
	set_stabi_arr(cap, arr, ii++, tot_syn);

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = (binder*)mck_as_loc_pt(grps);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		EMU_CK(sub_grp->parent == this);
		sub_grp->calc_stabi_arr_rec(cap, arr, ii);
	}

	//set_stabi_arr(cap, arr, ii++, tot_grp);
}

// mc_addr_is_local(addr)

void 
neurostate::calc_stabi_arr() {
	if(stabi_arr == mc_null){
		stabi_arr_cap = calc_stabi_arr_cap(stabi_active_set.tot_syn);
		stabi_arr = mc_malloc32(num_syn_t, stabi_arr_cap);
	}
	stabi_arr_sz = 0;
	stabi_active_set.calc_stabi_arr_rec(stabi_arr_cap, stabi_arr, stabi_arr_sz);
}
*/

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
polaron::stabi_handler(missive* msv){
}

void
neuron::stabi_handler(missive* msv){
	cell* msv_src = msv->src;
	stabi_tok_t tok = (stabi_tok_t)msv->tok;
	MC_MARK_USED(msv_src);
	MC_MARK_USED(tok);

	//nervenet* my_net = bj_nervenet;
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
synapse::stabi_handler(missive* msv){
	propag_data dat;
	dat.trm = (transmitter*)msv;
	dat.snp = this;
	dat.tok = (stabi_tok_t)(dat.trm)->tok;
	dat.sd = (dat.trm)->wrk_side;
	dat.ti = (dat.trm)->wrk_tier;

	OLD_SYNC_MTH(EMU_CK(dat.ti != BJ_INVALID_NUM_TIER));

	//if(bj_nervenet->get_active_netstate(dat.sd).sync_ending_propag){ return; }

	owner->stabi_recv_transmitter(&dat);
}

void
nervenet::stabi_nn_handler(missive* msv){
	if(msv->tok == bj_tok_stabi_start){
		stabi_nervenet_start();
		return;
	}

	sync_transmitter* sy_tmt = (sync_transmitter*)msv;
	net_side_t tmt_sd = sy_tmt->wrk_side;
	num_tier_t tmt_ti = sy_tmt->wrk_tier;
	nervenode* tmt_cfl = sy_tmt->cfl_src;

	EMU_CK(tmt_ti != BJ_INVALID_NUM_TIER);
	EMU_CK(tmt_sd != side_invalid);

	netstate& nst = get_active_netstate(tmt_sd);
	tierdata& tdt = nst.get_tier(tmt_ti, 1);

	SYNC_LOG(" SYNC_RECV_%s_t%d_%s_ [%d <<- %d] (%d == (%d+%d+%d)) \n", 
		net_side_to_str(tmt_sd), tmt_ti, sync_tok_to_str((sync_tok_t)(msv->tok)), 
		kernel::get_core_nn(), mc_id_to_nn(mc_addr_get_id(msv->src)), bj_nervenet->sync_tot_children, 
		tdt.ety_chdn, tdt.alv_chdn, tdt.stl_chdn
	);

	switch(msv->tok){
		case bj_tok_sync_empty_child:
		{
			//tdt.ety_chdn++;
			nst.inc_ety_chdn(tmt_ti);
		}
		break;
		case bj_tok_sync_alive_child:
		{
			tdt.alv_chdn++;
		}
		break;
		case bj_tok_sync_still_child:
		{
			tdt.stl_chdn++;
		}
		break;
		case bj_tok_sync_confl_up_neu:
			nst.send_up_confl_tok(bj_tok_sync_confl_up_neu, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_confl_up_pol:
			nst.send_up_confl_tok(bj_tok_sync_confl_up_pol, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_confl_down_neu:
			nst.send_sync_to_children(bj_tok_sync_confl_down_neu, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_confl_down_pol:
			nst.send_sync_to_children(bj_tok_sync_confl_down_pol, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_to_children:
			nst.send_sync_to_children(bj_tok_sync_to_children, tmt_ti, mc_null);
		break;
		default:
			mck_abort(1, mc_cstr("BAD_STABI_TOK"));
		break;
	}

	nst.update_sync();
}

void
nervenet::stabi_nervenet_start(){
	EMU_LOG("stabi_nervenet_start \n");

	nervenet* my_net = this;

	binder * fst, * lst, * wrk;

	binder* pt_all_neu = &(all_neu);
	fst = (binder*)(pt_all_neu->bn_right);
	lst = (binder*)mck_as_loc_pt(pt_all_neu);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		neuron* my_neu = (neuron*)wrk;
		EMU_CK(my_neu->ki == nd_neu);
		my_net->send(my_neu, bj_tok_stabi_start);
	}

	EMU_CK(get_active_netstate(side_left).get_tier(0, 2).rcv_neus == 0);
	EMU_CK(get_active_netstate(side_right).get_tier(0, 3).rcv_neus == 0);

	EMU_LOG("end_stabi_nervenet_start \n");
}

void 
send_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd, bool from_rec){
	//MCK_CK(! mc_addr_has_id(nn_all_snp));
	EMU_CK(mth != mc_null);

	binder * fst, * lst, * wrk;

	fst = (binder*)(nn_all_snp->bn_right);
	lst = (binder*)mck_as_loc_pt(nn_all_snp);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synapse* my_snp = mc_null;
		if(sd == side_left){
			my_snp = (synapse*)wrk;
		} else {
			EMU_CK(sd == side_right);
			my_snp = bj_get_syn_of_rgt_handle(wrk);
		}
		//EMU_PRT("send_all_synapses cls=%s \n\n", my_snp->get_class_name());
		EMU_CK(my_snp != mc_null);
		EMU_CK(bj_is_synapse(my_snp));
		//EMU_PRT("send_all_synapses snp=%p \n\n", (void*)my_snp);
		MCK_CK(my_snp->owner->ki != nd_invalid);

		(my_snp->owner->*mth)(my_snp, sd, from_rec);
	}
}

void
synset::stabi_rec_send_all(bj_callee_t mth, net_side_t sd){
	MCK_CHECK_SP();
	//MCK_CK(! mc_addr_has_id(this));
	//MCK_CK(! mc_addr_has_id(&(all_syn)));
	//MCK_CK(! mc_addr_has_id(&(all_grp)));
	send_all_synapses(&(all_syn), mth, sd, true /* IS_FROM_REC */);

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = (binder*)mck_as_loc_pt(grps);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		EMU_CK(sub_grp->parent == this);
		sub_grp->stabi_rec_send_all(mth, sd);
	}
}

void
neuron::stabi_neuron_start(){
	EMU_CK(left_side.stabi_tiers.is_alone());
	EMU_CK(left_side.stabi_active_set.all_grp.is_alone());

	EMU_CK(right_side.stabi_tiers.is_alone());
	EMU_CK(right_side.stabi_active_set.all_syn.is_alone());
	EMU_CK(right_side.stabi_active_set.all_grp.is_alone());

	left_side.stabi_active_set.stabi_rec_send_all((bj_callee_t)(&nervenode::stabi_send_snp_propag), side_left);

	left_side.reset_complete();

	left_side.send_all_ti_done(this, side_left, BJ_INVALID_NUM_TIER);
}

void 
neuron::stabi_send_snp_propag(synapse* snp, net_side_t sd, bool from_rec){
	neurostate& stt = get_neurostate(sd);

	EMU_CK(snp != mc_null);
	EMU_CK(snp->owner == this);
	EMU_CK(! stt.stabi_active_set.is_synset_empty());
	if(stt.stabi_active_set.tot_syn == 1){
		EMU_LOG("FORCING %s %ld %s  TI=%d flags=%p flgs_pt=%p \n", node_kind_to_str(ki), id, 
			net_side_to_str(sd), get_neurostate(sd).stabi_num_tier /*undd*/, (void*)(uintptr_t)stt.stabi_flags,
			(void*)(&stt.stabi_flags));

		snp->send_transmitter(bj_tok_stabi_charge_all, sd, from_rec /*IS_FORCED*/);
	} else {
		snp->send_transmitter(bj_tok_stabi_ping, sd);
	}
}

void 
nervenode::stabi_send_snp_tier_done(synapse* snp, net_side_t sd, bool from_rec){
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_tier_done, sd);
}

void
neurostate::send_all_ti_done(nervenode* nd, net_side_t sd, num_tier_t dbg_ti){
	OLD_SYNC_MTH(EMU_CK(stabi_num_tier != BJ_INVALID_NUM_TIER));

	if(stabi_num_tier != BJ_INVALID_NUM_TIER){ 
		tierset* c_ti = get_tiset(stabi_num_tier);
		if(c_ti != mc_null){
			EMU_LOG("::send_all_ti_done WITH_PRV_TI %s %ld %s \n", node_kind_to_str(nd->ki), 
					nd->id, net_side_to_str(sd));
			send_all_synapses(&(c_ti->ti_all), (bj_callee_t)(&nervenode::stabi_send_snp_tier_done), sd);
		}
	}

	stabi_active_set.stabi_rec_send_all((bj_callee_t)(&nervenode::stabi_send_snp_tier_done), sd);

	EMU_CK((dbg_ti == BJ_INVALID_NUM_TIER) || (stabi_num_tier == BJ_INVALID_NUM_TIER) || 
				(nd->ki != nd_neu) || ((dbg_ti + 1) == stabi_num_tier /*undd*/));
	EMU_CK((dbg_ti == BJ_INVALID_NUM_TIER) || (stabi_num_tier == BJ_INVALID_NUM_TIER) || 
				(nd->ki == nd_neu) || (dbg_ti == stabi_num_tier /*undd*/));

	if(stabi_num_tier != BJ_INVALID_NUM_TIER){ 
		stabi_num_tier++;
	}

	EMU_LOG("INC_TIER %s %ld %s TI=%d \n", node_kind_to_str(nd->ki), nd->id, 
				net_side_to_str(sd), stabi_num_tier /*undd*/);
}

void
nervenode::stabi_recv_transmitter(propag_data* dat){

	EMU_CODE(
		neurostate& stt = get_neurostate(dat->sd);
		OLD_SYNC_MTH(EMU_CK(dat->ti != BJ_INVALID_NUM_TIER));
		OLD_SYNC_MTH(EMU_CK(stt.stabi_num_tier != BJ_INVALID_NUM_TIER));

		if((dat->ti != BJ_INVALID_NUM_TIER) && (stt.stabi_num_tier != BJ_INVALID_NUM_TIER)){
			bool ok_3 =  false;
			if(ki == nd_neu){
				ok_3 = ((dat->ti + 1) == stt.stabi_num_tier); /*undd*/
			} else {
				ok_3 = (dat->ti == stt.stabi_num_tier); /*undd*/
			}
			
			EMU_CK_PRT(ok_3, "%s %s %ld %s (%d > %d)", stabi_tok_to_str(dat->tok),
				node_kind_to_str(ki), id, net_side_to_str(dat->sd), (dat->ti + 1), stt.stabi_num_tier /*undd*/);

			//EMU_CK(dat->ti < BJ_DBG_MAX_TIER); // debug_purposes_only
			EMU_CK(	(bj_nervenet->sync_parent_id != 0) ||
					bj_nervenet->get_active_netstate(dat->sd).sync_is_inactive ||
					(dat->ti < BJ_DBG_MAX_TIER)
			); // debug_purposes_only
		}

		nervenode* rem_nd = dat->snp->mate->owner;
		EMU_LOG("::stabi_recv_transmitter %s [%s %ld <<- %s %ld] %s dat_TI=%d nod_TI=%d \n", 
			stabi_tok_to_str(dat->tok), node_kind_to_str(ki), id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
			net_side_to_str(dat->sd), dat->ti, stt.stabi_num_tier /*undd*/);
	);
	MC_DBG(
		if(kernel::get_core_nn() == 2){
			mck_slog2("::RECV ");mck_slog2(stabi_tok_to_str(dat->tok));
		}
	);

	restore_tiers(dat);

	switch(dat->tok){
		case bj_tok_stabi_charge_all:
			stabi_recv_charge_all(dat);
		break;
		case bj_tok_stabi_charge_src:
			stabi_recv_charge_src(dat);
		break;
		case bj_tok_stabi_ping:
			stabi_recv_ping(dat);
		break;
		case bj_tok_stabi_tier_done:
			stabi_recv_tier_done(dat);
		break;
		default:
			mck_abort(1, mc_cstr("nervenode::stabi_recv_propag. BAD_STABI_TOK"));
		break;
	}
}

void
synset::stabi_rec_reset(){
	MCK_CHECK_SP();
	while(! all_grp.is_alone()){
		synset* sub_grp = (synset*)(binder*)(all_grp.bn_right);
		EMU_CK(sub_grp->parent == this);
		sub_grp->stabi_rec_reset();

		EMU_CK(sub_grp->all_grp.is_alone());
		all_syn.move_all_to_my_right(sub_grp->all_syn);
		sub_grp->release();
	}
}

bool
neurostate::charge_all_active(propag_data* dat, node_kind_t ki){
	stabi_active_set.stabi_rec_reset();

	bool resp = false;
	if(! stabi_active_set.is_synset_empty()){

		resp = true;
		tierset& ti_grp = add_tiset(dat->ti);
		ti_grp.ti_all.move_all_to_my_right(stabi_active_set.all_syn);

		stabi_active_set.tot_syn = 0;
		stabi_num_ping = 0;

		if(ki == nd_neu){
			bj_nervenet->get_active_netstate(dat->sd).get_tier(dat->ti, 4).inc_off();
		}
	}
	EMU_CK(stabi_active_set.is_synset_empty());
	resp = (resp && ! stabi_tiers.is_alone()); 
	return resp;
}

bool
polaron::can_chg_all(){
	return true;
}

void
nervenode::stabi_recv_charge_all(propag_data* dat){
	EMU_CK(dat != mc_null);
	EMU_CK(dat->sd != side_invalid);

	neurostate& stt = get_neurostate(dat->sd);

	mck_slog2("dbg1.chg_all\n");
	EMU_LOG("nervenode::stabi_recv_charge_all %s %ld %s stb_src=%p \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), stt.stabi_source);

	if(stt.stabi_source != mc_null){
		return;
	}

	if(bj_is_pol(ki) && stt.stabi_active_set.is_synset_empty()){
		EMU_CODE(neurostate& ott = ((polaron*)this)->opp->get_neurostate(dat->sd));
		EMU_CK((ott.stabi_source != mc_null) && ott.stabi_active_set.is_synset_empty());
		return;
	}

	EMU_CODE(nervenode* stb_src = dat->snp->mate->owner);
	EMU_CK(stb_src != mc_null);

	EMU_LOG("SET_STB_SRC %s %ld %s stb_src: %s %ld \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			node_kind_to_str(stb_src->ki), stb_src->id);

	EMU_CK_LOG(! stt.stabi_active_set.is_synset_empty(), 
		"::stabi_recv_charge_all EMPTY_ACTIVE !!! stb_src: %s %ld \n", 
		node_kind_to_str(stb_src->ki), stb_src->id);

	mc_set_flag(stt.stabi_flags, bj_stt_charge_all_flag);
	stt.stabi_source = dat->snp;	

	mck_slog2("dbg1.chg_all2\n");
}

binder&
synapse::get_side_binder(net_side_t sd){
	if(sd == side_right){
		return right_handle;
	}
	return *((binder*)this);
}

void
nervenode::stabi_recv_charge_src(propag_data* dat){
	EMU_CK(dat != mc_null);
	EMU_CK(dat->sd != side_invalid);

	neurostate& stt = get_neurostate(dat->sd);

	stt.stabi_active_set.stabi_rec_reset();

	if(! stt.stabi_active_set.is_synset_empty()){

		tierset& ti_grp = stt.add_tiset(dat->ti);

		binder& bdr = dat->snp->get_side_binder(dat->sd);
		bdr.let_go();
		ti_grp.ti_all.bind_to_my_left(bdr);

		stt.stabi_active_set.tot_syn--;

		if(stt.stabi_active_set.is_synset_empty()){
			stt.stabi_num_ping = 0;
			if(ki == nd_neu){
				bj_nervenet->get_active_netstate(dat->sd).get_tier(dat->ti, 5).inc_off();
			}
		}
	}
}

void
nervenode::stabi_recv_ping(propag_data* dat){
	neurostate& stt = get_neurostate(dat->sd);
	stt.stabi_num_ping++;

	mck_slog2("dbg1.inc_ping\n");
	EMU_LOG("INC_PINGS %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.stabi_num_ping, dat->ti);
}

bool
nervenode::is_tier_complete(propag_data* dat){
	neurostate& stt = get_neurostate(dat->sd);
	return stt.is_full();
}

bool
polaron::is_tier_complete(propag_data* dat){
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);

	bool both_full = pol_stt.is_full() && opp_stt.is_full();
	return both_full;
}

void
nervenode::stabi_recv_tier_done(propag_data* dat){

	neurostate& stt = get_neurostate(dat->sd);

	stt.stabi_num_complete++;

	EMU_LOG("ADD_TIER_END %s %ld %s compl(%d of %d) TI=%d \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.stabi_num_complete, stt.prev_tot_active, dat->ti);

	if(is_tier_complete(dat)){
		// order of this is important:
		if((ki == nd_neu)){
			OLD_SYNC_MTH(neu_update_net_tier_counters(dat));
			NEW_SYNC_MTH(neu_update_tier_counters(dat));
		}

		EMU_LOG("TIER_COMPLETE %s %ld %s TI=%d \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), dat->ti);

		stabi_start_nxt_tier(dat);
	}
}

void
nervenode::neu_update_net_tier_counters(propag_data* dat){
	EMU_CK(ki == nd_neu);
	neurostate& stt = get_neurostate(dat->sd);
	bool all_png = stt.all_ping();

	EMU_CK((dat->ti + 1) == stt.stabi_num_tier /*undd*/);

	tierdata& tda = bj_nervenet->get_active_netstate(dat->sd).get_tier(dat->ti, 6);
	if(all_png){
		tda.stl_neus++;
	} else {
		tda.inc_rcv();
	}

	EMU_COND_LOG(tda.got_all_neus(), " GOT_ALL__%s_t%d_ #stl_ne=%d \n", 
		net_side_to_str(dat->sd), dat->ti, tda.stl_neus);
}

void 
nervenode::stabi_send_snp_charge_src(synapse* snp, net_side_t sd, bool from_rec){
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_charge_src, sd);
}

void 
nervenode::stabi_send_snp_propag(synapse* snp, net_side_t sd, bool from_rec){
	EMU_CK(snp != mc_null);
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_ping, sd);
}

void 
polaron::stabi_send_snp_charge_all(synapse* snp, net_side_t sd, bool from_rec){
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_charge_all, sd);
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
nervenode::stabi_start_nxt_tier(propag_data* dat){
	mck_abort(1, mc_cstr("nervenode::stabi_start_nxt_tier"));
}

void
neurostate::reset_complete(){
	EMU_LOG("::reset_complete flags=%p flgs_pt=%p \n", (void*)(uintptr_t)stabi_flags, 
			(void*)(&stabi_flags));

	//stabi_flags = 0;
	mc_reset_flag(stabi_flags, bj_stt_charge_all_flag);

	stabi_num_complete = 0;
	stabi_num_ping = 0;
	prev_tot_active = stabi_active_set.tot_syn;
}

tierset*
neurostate::get_tiset(num_tier_t nti){
	EMU_CK(nti != BJ_INVALID_NUM_TIER);
	if(stabi_tiers.is_alone()){
		return mc_null;
	}
	tierset* tis = (tierset*)stabi_tiers.bn_left;
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
		stabi_tiers.bind_to_my_left(*tis);
	}
	return *tis;
}

bool
neurostate::is_mono(num_tier_t nti){
	return (stabi_active_set.is_synset_empty() && (stabi_source == mc_null) && (get_tiset(nti) != mc_null));
}

void
neurostate::send_all_propag(nervenode* nd, propag_data* dat){
	tierset* c_ti = get_tiset(dat->ti);
	if(c_ti != mc_null){
		send_all_synapses(&(c_ti->ti_all), (bj_callee_t)(&nervenode::stabi_send_snp_propag), dat->sd);
	}

	stabi_active_set.stabi_rec_send_all((bj_callee_t)(&nervenode::stabi_send_snp_propag), dat->sd);
}

void
polaron::stabi_start_nxt_tier(propag_data* dat){
	polaron* pol = this;
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);

	EMU_CK(pol_stt.is_full());
	EMU_CK(opp_stt.is_full());
	if(! opp_stt.is_full()){
		EMU_LOG("OPP_INCOMPLETE %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
		return;
	}
	EMU_LOG("OPP_COMPLETE %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));

	bool pol_chg = mc_get_flag(pol_stt.stabi_flags, bj_stt_charge_all_flag);
	bool opp_chg = mc_get_flag(opp_stt.stabi_flags, bj_stt_charge_all_flag);

	EMU_CK(! pol_chg || (pol_stt.stabi_source != mc_null));
	EMU_CK(! opp_chg || (opp_stt.stabi_source != mc_null));

	if(pol_chg && opp_chg){
		EMU_LOG("POL_CONFLICT %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
		EMU_CODE(dbg_prt_nod(dat->sd, mc_cstr("POL_CONFLICT__"), 7, dat->ti));
		//EMU_CK(false && "POL_CONFLIT_CASE"); // CODE_THIS_CASE
		// conflict. continue propag.
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
			EMU_LOG("MONO CASE %s %ld %s \n", node_kind_to_str(opp->ki), opp->id, net_side_to_str(dat->sd));
			opp->charge_all_and_start_nxt_ti(dat);
		} else 
		if(! pol_mono && opp_mono){
			EMU_LOG("MONO CASE %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
			pol->charge_all_and_start_nxt_ti(dat);
		} else {
			pol_stt.send_all_propag(pol, dat);
			opp_stt.send_all_propag(opp, dat);
		}
	} 

	if(pol_stt.all_ping() && opp_stt.all_ping()){
		NEW_SYNC_MTH(
			EMU_PRT("POL_ALL_PING\n");
			pol_stt.stabi_num_tier = BJ_INVALID_NUM_TIER;
			opp_stt.stabi_num_tier = BJ_INVALID_NUM_TIER;
		);
	}

	pol_stt.reset_complete();
	opp_stt.reset_complete();

	pol_stt.send_all_ti_done(pol, dat->sd, dat->ti);
	opp_stt.send_all_ti_done(opp, dat->sd, dat->ti);
}

void 
netstate::send_up_confl_tok(sync_tok_t the_tok, num_tier_t the_ti, nervenode* the_cfl)
{
	EMU_CK((the_tok == bj_tok_sync_confl_up_neu) || (the_tok == bj_tok_sync_confl_up_pol));

	mc_core_id_t pnt_id = bj_nervenet->sync_parent_id;
	nervenet* pnt_net = bj_nervenet->get_nervenet(pnt_id);
	if(pnt_id != 0){
		send_sync_transmitter(pnt_net, the_tok, the_ti, the_cfl);
	} else {
		if(the_tok == bj_tok_sync_confl_up_neu){
			the_tok = bj_tok_sync_confl_down_neu;
		}
		if(the_tok == bj_tok_sync_confl_up_pol){
			the_tok = bj_tok_sync_confl_down_pol;
		}
		send_sync_to_children(the_tok, the_ti, the_cfl);
	}
}

void
nervenode::send_confl_tok(propag_data* dat, sync_tok_t the_tok){
	netstate& nstt = bj_nervenet->get_active_netstate(dat->sd);
	nstt.send_up_confl_tok(the_tok, dat->ti, this);
}

void
polaron::charge_all_confl_and_start_nxt_ti(propag_data* dat){
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);

	pol_stt.charge_all_active(dat, ki); 
	tierset* ti_grp = pol_stt.get_tiset(dat->ti);
	if(ti_grp != mc_null){
		send_all_synapses(&(ti_grp->ti_all), (bj_callee_t)(&nervenode::stabi_send_snp_charge_src), 
						dat->sd);
	}

	opp_stt.charge_all_active(dat, opp->ki);	// set opp too
	tierset* opp_ti_grp = opp_stt.get_tiset(dat->ti);
	if(opp_ti_grp != mc_null){
		send_all_synapses(&(opp_ti_grp->ti_all), (bj_callee_t)(&nervenode::stabi_send_snp_charge_src), 
						dat->sd);
	}
}

void
polaron::charge_all_and_start_nxt_ti(propag_data* dat){
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);

	pol_stt.charge_all_active(dat, ki); 
	tierset* ti_grp = pol_stt.get_tiset(dat->ti);
	if(ti_grp != mc_null){
		send_all_synapses(&(ti_grp->ti_all), (bj_callee_t)(&polaron::stabi_send_snp_charge_all), dat->sd);
	}

	opp_stt.charge_all_active(dat, opp->ki);	// set opp too
	tierset* opp_ti_grp = opp_stt.get_tiset(dat->ti);
	if(opp_ti_grp != mc_null){
		send_all_synapses(&(opp_ti_grp->ti_all), (bj_callee_t)(&nervenode::stabi_send_snp_charge_src), 
						dat->sd);
	}
}

void
neuron::stabi_start_nxt_tier(propag_data* dat){
	neurostate& stt = get_neurostate(dat->sd);

	bool chgd_all = mc_get_flag(stt.stabi_flags, bj_stt_charge_all_flag);
	if(chgd_all){
		EMU_CK(stt.stabi_source != mc_null);
		stt.charge_all_active(dat, ki);
		tierset* ti_grp = stt.get_tiset(dat->ti);
		if(ti_grp != mc_null){
			send_all_synapses(&(ti_grp->ti_all), (bj_callee_t)(&nervenode::stabi_send_snp_charge_src), dat->sd);
		}
	} else {
		if(stt.stabi_active_set.is_synset_empty() && (stt.stabi_source == mc_null)){
			EMU_LOG("NEU_CONFLICT %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
			EMU_CODE(dbg_prt_nod(dat->sd, mc_cstr("NEU_CONFLICT__"), 7, dat->ti));
			//EMU_CK(false && "NEU_CONFLIT_CASE");
			send_confl_tok(dat, bj_tok_sync_confl_up_neu);
		} else {
			stt.send_all_propag(this, dat);
		}
	}

	EMU_LOG("RESETING %s %ld %s  TI=%d \n", node_kind_to_str(ki), id, 
				net_side_to_str(dat->sd), dat->ti);

	if(stt.all_ping()){
		NEW_SYNC_MTH(
			EMU_PRT("NEU_ALL_PING\n");
			stt.stabi_num_tier = BJ_INVALID_NUM_TIER;
		);
	}

	stt.reset_complete();
	stt.send_all_ti_done(this, dat->sd, dat->ti);

	EMU_CODE(dbg_prt_nod(dat->sd, mc_cstr("TIER__"), 7, dat->ti));
	mck_slog2("dbg1.reset\n");

	netstate& nst = bj_nervenet->get_active_netstate(dat->sd);
	OLD_SYNC_MTH(nst.update_sync());
	NEW_SYNC_MTH(nst.update_prop_sync());
}

void 
nervenet::dbg_stabi_stop_sys(propag_data* dat, nervenode* nod){	
}

void bj_stabi_main() {
	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_stabi_init_handlers();

	EMU_LOG("STABI___ %d \n", nn);

	bj_print_loaded_cnf();
	bj_print_active_cnf(side_left, mc_cstr("LOADED "), 3, 0);

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->stabi_init_sync();

	EMU_CODE(if(kernel::get_core_nn() == 0){ emu_prt_tok_codes(); });

	mck_ilog(sizeof(mck_glb_sys_st));
	mck_slog2("__dbg1.stabi\n");

	my_net->send(my_net, bj_tok_stabi_start);
	kernel::run_sys();

	bj_print_active_cnf(side_left, mc_cstr("REDUCED "), 5, 0);
	bj_print_active_cnf(side_left, mc_null, 7, BJ_INVALID_NUM_TIER);

	EMU_PRT("...............................END_STABI\n");
	mck_slog2("END_STABI___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");
	mck_sprt2("dbg1.stabi.end\n");

}

tierdata&
netstate::get_tier(num_tier_t nti, int dbg_caller){
	EMU_CK(! all_tiers.is_alone());
	EMU_CK(nti != BJ_INVALID_NUM_TIER);

	tierdata* dat = mc_null;
	binder * fst, * lst, * wrk;

	binder* tis = &(all_tiers);
	if(nti == BJ_LAST_TIER){
		dat = (tierdata*)(binder*)(tis->bn_left);
	}

	if(dat == mc_null){
		fst = (binder*)(tis->bn_left);
		lst = (binder*)mck_as_loc_pt(tis);
		for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_left)){
			tierdata* tidat = (tierdata*)wrk;
			if(tidat->tdt_id == nti){
				dat = tidat;
				break;
			}
			if(tidat->tdt_id < nti){
				break;
			}
		}
	}

	if(dat == mc_null){
		mck_slog2("CALC_TIER__");
		mck_ilog(dbg_caller);
		mck_slog2("__\n");
		while(get_last_tier().tdt_id < nti){
			inc_tier(dbg_caller);
		}
		dat = (tierdata*)(all_tiers.bn_left);
	}

	EMU_CK(dat != mc_null);
	EMU_CK_PRT((dat->tdt_id == nti), "(%d == %d)",  dat->tdt_id, nti);

	dat->update_tidat();
	return *dat;
}

void 
tierdata::update_tidat(){
	if(tdt_id == 0){
		return;
	}
	tierdata* prv = (tierdata*)(bn_left);
	if((inp_neus == BJ_INVALID_NUM_NODE) && prv->got_all_neus()){
		EMU_CK(prv->inp_neus != BJ_INVALID_NUM_NODE);
		inp_neus = prv->inp_neus - prv->off_neus;
		EMU_CK(inp_neus != BJ_INVALID_NUM_NODE);
	}
}

void
netstate::inc_tier(int dbg_caller){
	tierdata& lti = get_last_tier();

	tierdata* ti_dat = tierdata::acquire();
	ti_dat->tdt_id = lti.tdt_id + 1;

	NEW_SYNC_MTH(
		ti_dat->stl_neus = lti.stl_neus;
	);
	EMU_CK(ti_dat->stl_neus >= 0);

	all_tiers.bind_to_my_left(*ti_dat);

	ti_dat->ety_chdn = lti.ety_chdn;

	EMU_LOG("INC_NET_TIER_%d(%d) %s stl=%d \n", ti_dat->tdt_id, dbg_caller, net_side_to_str(my_side), 
			ti_dat->stl_neus);

	mck_slog2("inc_tier__");
	mck_ilog(ti_dat->tdt_id);
	mck_slog2("__\n");

	ti_dat->update_tidat();
}

nervenet*
nervenet::get_nervenet(mc_core_id_t id){
	nervenet* rem_net = (nervenet*)mc_addr_set_id(id, this);
	return rem_net;
}

void
netstate::inc_ety_chdn(num_tier_t nti){
	tierdata& dat = get_tier(nti, 8);

	binder * fst, * lst, * wrk;

	binder* tis = &(all_tiers);
	fst = (binder*)(&dat);
	lst = (binder*)mck_as_loc_pt(tis);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		tierdata* tidat = (tierdata*)wrk;
		tidat->ety_chdn++;
	}

	SYNC_LOG(" SYNC_RCV_EMPTY_%s_t%d_ #ety=%d \n", net_side_to_str(my_side), nti, dat.ety_chdn);
}

void
netstate::inc_bsy_chdn(num_tier_t nti, mc_core_nn_t num_bsy_chdn){
	tierdata& dat = get_tier(nti, 8);

	binder * fst, * lst, * wrk;

	binder* tis = &(all_tiers);
	fst = (binder*)(&dat);
	lst = (binder*)mck_as_loc_pt(tis);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		tierdata* tidat = (tierdata*)wrk;
		bool rfrsh = mc_get_flag(tidat->tdt_flags, bj_refreshed_flag);
		if(! rfrsh){
			tidat->inc_bsy_chdn += num_bsy_chdn;
		}
	}

	SYNC_LOG(" SYNC_INC_BSY_%s_t%d_ #inc=%d \n", net_side_to_str(my_side), nti, dat.inc_bsy_chdn);
}

void
netstate::send_sync_transmitter(nervenet* the_dst, sync_tok_t the_tok, num_tier_t the_ti, 
			nervenode* the_cfl_src, mc_core_nn_t the_num_chdn)
{
	sync_transmitter* trm = sync_transmitter::acquire();
	trm->src = bj_nervenet;
	trm->dst = the_dst;
	trm->tok = the_tok;

	trm->wrk_side = my_side;
	trm->wrk_tier = the_ti;

	trm->cfl_src = the_cfl_src;
	trm->num_chdn = the_num_chdn;

	trm->send();

	SYNC_CODE_2(mc_core_nn_t dbg_dst_nn = mc_id_to_nn(mc_addr_get_id(the_dst)));
	SYNC_LOG_2(" SYNC_send_transmitter_%s_t%d_%s_ [%ld ->> %ld] \n", 
		net_side_to_str(my_side), the_ti, sync_tok_to_str(the_tok), kernel::get_core_nn(), dbg_dst_nn);
	EMU_CK(the_ti != BJ_INVALID_NUM_TIER);
}

void 
netstate::send_sync_to_children(sync_tok_t the_tok, num_tier_t the_ti, nervenode* the_cfl)
{
	SYNC_LOG(" SYNC_STOP_CHILDREN %s CORE=%d out_ti=%d \n", net_side_to_str(my_side), kernel::get_core_nn(), 
			sync_tier_out);

	EMU_CK(the_ti != BJ_INVALID_NUM_TIER);

	if(the_cfl != mc_null){
		EMU_CK((the_tok == bj_tok_sync_confl_down_neu) || (the_tok == bj_tok_sync_confl_down_pol));
		tok_confl = the_tok;
		nod_confl = the_cfl;
		ti_confl = the_ti;

		EMU_LOG(" SYNC_CONFLICT_%s_t%d_%s confl_pt=%p \n", 
				net_side_to_str(my_side), ti_confl, 
				sync_tok_to_str(bj_tok_sync_confl_down_pol), (void*)nod_confl);
	}

	mc_load_map_st** my_children = bj_nervenet->sync_map->childs;
	if(my_children != mc_null){ 
		int aa = 0;
		mc_load_map_st* ch_map = (my_children)[aa];
		while(ch_map != mc_null){
			mc_core_nn_t chd_nn = ch_map->num_core;
			nervenet* ch_net = bj_nervenet->get_nervenet(mc_nn_to_id(chd_nn));
			send_sync_transmitter(ch_net, the_tok, the_ti, the_cfl);
			//EMU_PRT_STACK(true, "%s CORE=%d \n", _to_str_,  get_core_nn());

			aa++;
			ch_map = (my_children)[aa];
		}
	}

	if(the_tok == bj_tok_sync_to_children){
		SYNC_LOG_2(" SYNC_END_%s CORE=%d out_ti=%d tmt_TI=%d \n", 
				net_side_to_str(my_side), kernel::get_core_nn(), sync_tier_out, the_ti);

		sync_ending_propag = true;
		sync_is_inactive = true;
	}
}

void bj_kernel_func(){
	nervenet* my_net = bj_nervenet;
	my_net->handle_sync();
}

void 
nervenet::handle_sync(){
	//send_parent_tok_empty_child(side_left);
	//send_parent_tok_empty_child(side_right);

	act_left_side.handle_my_sync();
	act_right_side.handle_my_sync();

	if(act_left_side.sync_ending_propag && act_right_side.sync_ending_propag){
		//mck_get_kernel()->set_idle_exit();
		kernel::stop_sys(bj_tok_stabi_end);
	}
}

void
netstate::handle_my_sync(){
	OLD_SYNC_MTH(update_sync());
	NEW_SYNC_MTH(update_prop_sync());
}

void
nervenode::restore_tiers(propag_data* dat){
	EMU_CK(ki == nd_neu);
	neurostate& stt = get_neurostate(dat->sd);

	if((stt.stabi_num_tier == BJ_INVALID_NUM_TIER) && (dat->ti != BJ_INVALID_NUM_TIER)){
		stt.stabi_num_tier = dat->ti + 1;
	}
	if((dat->ti == BJ_INVALID_NUM_TIER) && (stt.stabi_num_tier != BJ_INVALID_NUM_TIER)){
		dat->ti = stt.stabi_num_tier - 1;
		EMU_CK(dat->ti >= 0);
	}
}

void
polaron::restore_tiers(propag_data* dat){
	EMU_CK(ki != nd_neu);
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);

	if(dat->ti != BJ_INVALID_NUM_TIER){
		if(pol_stt.stabi_num_tier == BJ_INVALID_NUM_TIER){
			pol_stt.stabi_num_tier = dat->ti;
		}
		if(opp_stt.stabi_num_tier == BJ_INVALID_NUM_TIER){
			opp_stt.stabi_num_tier = dat->ti;
		}
	}
	if(pol_stt.stabi_num_tier != BJ_INVALID_NUM_TIER){
		if(dat->ti == BJ_INVALID_NUM_TIER){
			dat->ti = pol_stt.stabi_num_tier;
		}
		if(opp_stt.stabi_num_tier == BJ_INVALID_NUM_TIER){
			opp_stt.stabi_num_tier = pol_stt.stabi_num_tier;
		}
	}
	if(opp_stt.stabi_num_tier != BJ_INVALID_NUM_TIER){
		if(dat->ti == BJ_INVALID_NUM_TIER){
			dat->ti = opp_stt.stabi_num_tier;
		}
		if(pol_stt.stabi_num_tier == BJ_INVALID_NUM_TIER){
			pol_stt.stabi_num_tier = opp_stt.stabi_num_tier;
		}
	}
}

void
nervenode::neu_update_tier_counters(propag_data* dat){ // new_sync.
	EMU_CK(ki == nd_neu);
	neurostate& stt = get_neurostate(dat->sd);
	bool all_png = stt.all_ping();
	bool was_all_png = mc_get_flag(stt.stabi_flags, bj_stt_all_ping_flag);

	if(! (was_all_png && all_png)){
		netstate& nstt = bj_nervenet->get_active_netstate(dat->sd);
		tierdata& tda = nstt.get_tier(dat->ti, 6);
		if(was_all_png && ! all_png){
			mc_reset_flag(stt.stabi_flags, bj_stt_all_ping_flag);
			EMU_CK(! mc_get_flag(stt.stabi_flags, bj_stt_all_ping_flag));
			tda.stl_neus--;
			EMU_LOG(" DEC_STL__n%d_%s_t%d_ #stl_ne=%d \n", id, net_side_to_str(dat->sd), dat->ti, tda.stl_neus);
		}
		if(! was_all_png && all_png){
			mc_set_flag(stt.stabi_flags, bj_stt_all_ping_flag);
			EMU_CK(mc_get_flag(stt.stabi_flags, bj_stt_all_ping_flag));
			tda.stl_neus++;
			EMU_LOG(" INC_STL__n%d_%s_t%d_ #stl_ne=%d \n", id, net_side_to_str(dat->sd), dat->ti, tda.stl_neus);
		}

		EMU_DBG_CODE(	
			bool ok_1 = (tda.stl_neus >= 0);
			if(! ok_1){ nstt.dbg_prt_all_tiers(); }
			EMU_CK_PRT(ok_1, "n%d__ inp=%d, off=%d, rcv=%d, stl=%d \n", id, 
						tda.inp_neus, tda.off_neus, tda.rcv_neus, tda.stl_neus);
		);
		if(! all_png){
			tda.inc_rcv();
		}
		EMU_COND_LOG(tda.got_all_neus(), " GOT_ALL__%s_t%d_ #stl_ne=%d \n", 
			net_side_to_str(dat->sd), dat->ti, tda.stl_neus);
	}
}

bool
netstate::dbg_prt_all_tiers(){
	//tierdata* dat = mc_null;
	binder * fst, * lst, * wrk;

	EMU_PRT("all_tier=[\n");

	binder* tis = &(all_tiers);
	fst = (binder*)(tis->bn_left);
	lst = (binder*)mck_as_loc_pt(tis);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_left)){
		tierdata* tda = (tierdata*)wrk;
		MC_MARK_USED(tda);
		EMU_PRT("ti%d__ inp=%d, off=%d, rcv=%d, stl=%d \n", tda->tdt_id, 
					tda->inp_neus, tda->off_neus, tda->rcv_neus, tda->stl_neus);
	}

	EMU_PRT("all_tier=[\n");
	return true;
}

void
netstate::update_sync(){ // old_sync.
	if(sync_is_inactive){
		return;
	}

	tierdata& wt_tdt = get_tier(sync_wait_tier, 9);
	EMU_CK(wt_tdt.tdt_id == sync_wait_tier);
	EMU_CK(wt_tdt.tdt_id >= 0);

	if(! wt_tdt.got_all_neus()){ 
		SYNC_LOG(" SYNC_NO_snd_to_pnt_%s_t%d_not_got_all_neu (%d != (%d + %d))\n", 
			net_side_to_str(my_side), sync_wait_tier, wt_tdt.inp_neus, wt_tdt.rcv_neus, wt_tdt.stl_neus);
		return; 
	}
	EMU_CK(wt_tdt.inp_neus != BJ_INVALID_NUM_NODE);

	mc_core_nn_t tot_chdn = bj_nervenet->sync_tot_children;
	bool got_all_chdn = (tot_chdn == wt_tdt.tot_rcv_chdn());

	if(! got_all_chdn){
		SYNC_LOG(" SYNC_NO_snd_to_pnt_%s_t%d_not_all_chdn ((#tot_ch=%d)!=(#rcv_ch=%d)) (%d+%d+%d) \n", 
			net_side_to_str(my_side), sync_wait_tier, tot_chdn, wt_tdt.tot_rcv_chdn(), 
			wt_tdt.ety_chdn, wt_tdt.alv_chdn, wt_tdt.stl_chdn);
		return;
	}

	mc_core_id_t pnt_id = bj_nervenet->sync_parent_id;

	if((pnt_id != 0) && (tot_chdn == wt_tdt.ety_chdn) && wt_tdt.is_tidat_empty()){
		nervenet* pnt_net = bj_nervenet->get_nervenet(pnt_id);
		send_sync_transmitter(pnt_net, bj_tok_sync_empty_child, wt_tdt.tdt_id);
		sync_is_inactive = true;
		return;
	}

	if((pnt_id == 0) && (wt_tdt.alv_chdn == 0) && wt_tdt.all_neu_still()){
		sync_tier_out = wt_tdt.tdt_id;
		send_sync_to_children(bj_tok_sync_to_children, sync_tier_out, mc_null);
		return;
	}

	EMU_CK((tot_chdn != wt_tdt.ety_chdn) || ! wt_tdt.is_tidat_empty());

	if(pnt_id == 0){
		SYNC_LOG(" SYNC_NO_snd_to_pnt_%s_t%d_ROOT_INC_WT_TI wt_ti=%d #stl_ne=%d \n", 
				net_side_to_str(my_side), sync_wait_tier, wt_tdt.tdt_id, wt_tdt.stl_neus);

		sync_wait_tier++;
		return;
	}

	EMU_CK(pnt_id != 0);
	EMU_CK(wt_tdt.tdt_id >= 0);
	EMU_CK(sync_wait_tier >= 0);

	if(sync_tier_out == wt_tdt.tdt_id){
		SYNC_LOG(" SYNC_NO_snd_to_pnt_%s_t%d__CHILD_INC_WT_TI (ti_out == wt_ti (%d)) \n", 
			net_side_to_str(my_side), sync_wait_tier, wt_tdt.tdt_id);

		sync_wait_tier++;
		return;
	}

	sync_tier_out = wt_tdt.tdt_id;

	sync_tok_t sy_tok = bj_tok_sync_alive_child;

	bool is_stl = ((wt_tdt.alv_chdn == 0) && wt_tdt.all_neu_still());
	if(is_stl){
		EMU_CK(wt_tdt.stl_chdn == (tot_chdn - wt_tdt.ety_chdn));
		sy_tok = bj_tok_sync_still_child;
	}

	nervenet* pnt_net = bj_nervenet->get_nervenet(pnt_id);
	send_sync_transmitter(pnt_net, sy_tok, sync_tier_out);
	
	/*SYNC_LOG(" SYNC_SEND_PNT_%s_t%d_ wt_ety=%d CORE=%d #TOTchd=%d " 
		"#ETYchd=%d wt_ti=%d #LST_inp_ne=%d, #stl_ne=%d \n", 
		net_side_to_str(my_side), sync_tier_out, wt_tdt.is_tidat_empty(), mc_id_to_nn(pnt_id), 
		tot_chdn, wt_tdt.ety_chdn, wt_tdt.tdt_id, 
		wt_tdt.inp_neus, wt_tdt.stl_neus);*/
}

void
tierdata::update_refresh(net_side_t sd, bool going_down){ // new_sync.
	EMU_CK(! mc_get_flag(tdt_flags, bj_refreshed_flag));

	nervenet* the_net = bj_nervenet;
	mc_core_nn_t tot_chdn = the_net->sync_tot_children;
	if(num_rfsh_chdn == tot_chdn){
		mc_set_flag(tdt_flags, bj_refreshed_flag);

		if(is_busy()){
			tot_bsy_rfsh_chdn++;
		}

		init_busy();
		prv_bsy_chdn = tot_bsy_rfsh_chdn;

		netstate& nst = the_net->get_active_netstate(sd);
		mc_core_id_t pnt_id = the_net->sync_parent_id;
		if(pnt_id != 0){
			nervenet* pnt_net = the_net->get_nervenet(pnt_id);
			nst.send_sync_transmitter(pnt_net, bj_tok_sync2_refresh_up_bsy_chdn, 
					tdt_id, mc_null, prv_bsy_chdn);
		} else {
			if(prv_bsy_chdn == 0){
				nst.send_sync_to_children(bj_tok_sync_to_children, tdt_id, mc_null);
			}
		}
	}
}

void
nervenet::stabi_sync_handler(missive* msv){ // new_sync. replaces  stabi_nn_handler
	if(msv->tok == bj_tok_stabi_start){
		stabi_nervenet_start();
		return;
	}

	sync_transmitter* sy_tmt = (sync_transmitter*)msv;
	net_side_t tmt_sd = sy_tmt->wrk_side;
	num_tier_t tmt_ti = sy_tmt->wrk_tier;
	nervenode* tmt_cfl = sy_tmt->cfl_src;
	mc_core_nn_t tmt_chdn = sy_tmt->num_chdn;

	EMU_CK(tmt_ti != BJ_INVALID_NUM_TIER);
	EMU_CK(tmt_sd != side_invalid);

	netstate& nst = get_active_netstate(tmt_sd);
	tierdata& tdt = nst.get_tier(tmt_ti, 1);

	SYNC_LOG(" SYNC2_RECV_%s_t%d_%s_ [%d <<- %d] (%d == (%d+%d+%d)) \n", 
		net_side_to_str(tmt_sd), tmt_ti, sync_tok_to_str((sync_tok_t)(msv->tok)), 
		kernel::get_core_nn(), mc_id_to_nn(mc_addr_get_id(msv->src)), bj_nervenet->sync_tot_children, 
		tdt.ety_chdn, tdt.alv_chdn, tdt.stl_chdn
	);

	switch(msv->tok){
		case bj_tok_sync2_inc_bsy_chdn:
		{
			nst.inc_bsy_chdn(tmt_ti, tmt_chdn);
			mc_core_id_t pnt_id = bj_nervenet->sync_parent_id;
			nervenet* pnt_net = bj_nervenet->get_nervenet(pnt_id);
			nst.send_sync_transmitter(pnt_net, bj_tok_sync2_inc_bsy_chdn, tmt_ti, mc_null, tmt_chdn);
		}
		break;
		case bj_tok_sync2_dec_bsy_chdn:
			EMU_CK(! mc_get_flag(tdt.tdt_flags, bj_sent_got_bsy_flag));
			tdt.dec_bsy_chdn += tmt_chdn;
		break;
		case bj_tok_sync2_got_bsy_chdn:
			EMU_CK(! mc_get_flag(tdt.tdt_flags, bj_sent_got_bsy_flag));
			tdt.rcv_bsy_chdn += tmt_chdn;
		break;
		case bj_tok_sync2_refresh_up_bsy_chdn:
		{
			EMU_CK(! mc_get_flag(tdt.tdt_flags, bj_refreshed_flag));
			tdt.num_rfsh_chdn++;
			tdt.tot_bsy_rfsh_chdn += tmt_chdn;
		}
		break;
		case bj_tok_sync2_refresh_down_bsy_chdn:
			EMU_CK(! mc_get_flag(tdt.tdt_flags, bj_refreshed_flag));
			EMU_CK(sync_parent_id != 0);
			nst.send_sync_to_children(bj_tok_sync2_refresh_down_bsy_chdn, tmt_ti, mc_null);
		break;

		case bj_tok_sync_confl_up_neu:
			nst.send_up_confl_tok(bj_tok_sync_confl_up_neu, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_confl_up_pol:
			nst.send_up_confl_tok(bj_tok_sync_confl_up_pol, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_confl_down_neu:
			nst.send_sync_to_children(bj_tok_sync_confl_down_neu, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_confl_down_pol:
			nst.send_sync_to_children(bj_tok_sync_confl_down_pol, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_to_children:
			nst.send_sync_to_children(bj_tok_sync_to_children, tmt_ti, mc_null);
		break;
		default:
			mck_abort(1, mc_cstr("BAD_STABI_TOK"));
		break;
	}

	nst.update_prop_sync();
}

void
netstate::update_prop_sync(){ // new_sync. replaces update_sync
	if(sync_is_inactive){
		return;
	}

	tierdata& wt_tdt = get_tier(sync_wait_tier, 9);
	EMU_CK(wt_tdt.tdt_id == sync_wait_tier);
	EMU_CK(wt_tdt.tdt_id >= 0);

	if(! wt_tdt.got_all_neus()){ 
		SYNC_LOG(" SYNC2_NO_snd_to_pnt_%s_t%d_not_got_all_neu (%d != (%d + %d))\n", 
			net_side_to_str(my_side), wt_tdt.tdt_id, wt_tdt.inp_neus, wt_tdt.rcv_neus, wt_tdt.stl_neus);
		return; 
	}
	EMU_CK(wt_tdt.inp_neus != BJ_INVALID_NUM_NODE);

	bool got_all_bsy_chdn = (wt_tdt.prv_bsy_chdn == (wt_tdt.rcv_bsy_chdn + wt_tdt.dec_bsy_chdn));
	if(! got_all_bsy_chdn){
		SYNC_LOG(" SYNC2_NO_snd_to_pnt_%s_t%d_not_all_bsy_chdn (%d != (%d+%d)) \n", 
			net_side_to_str(my_side), wt_tdt.tdt_id, 
			wt_tdt.prv_bsy_chdn, wt_tdt.rcv_bsy_chdn, wt_tdt.dec_bsy_chdn);
		return;
	}

	/*bool sent_bsy = mc_get_flag(wt_tdt.tdt_flags, bj_sent_got_bsy_flag);
	if(sent_bsy){
		return;
	}*/

	nervenet* the_net = bj_nervenet;
	mc_core_id_t pnt_id = the_net->sync_parent_id;
	if(pnt_id == 0){
		if(wt_tdt.rcv_bsy_chdn == 0){
			EMU_CK(wt_tdt.prv_bsy_chdn == wt_tdt.dec_bsy_chdn);
			wt_tdt.update_refresh(my_side, false); // in case it has no children
			send_sync_to_children(bj_tok_sync2_refresh_down_bsy_chdn, wt_tdt.tdt_id, mc_null);
		}
		return;
	}


}

