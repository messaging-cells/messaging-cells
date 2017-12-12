
#include "cell.hh"

#include "stabi.hh"

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
synapse::send_transmitter(stabi_tok_t tok, net_side_t sd){
	if(bj_nervenet->get_active_netstate(sd).sync_ending_propag){ return; }

	EMU_CODE(nervenode* rem_nd = mate->owner);
	num_tier_t ti = owner->get_neurostate(sd).stabi_num_tier;
	EMU_LOG("::send_transmitter %s [%s %ld ->> %s %ld] %s wrk_TI=%d  \n", stabi_tok_to_str(tok), 
		node_kind_to_str(owner->ki), owner->id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
		net_side_to_str(sd), ti);
	

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
	MCK_CALL_HANDLER(nervenet, stabi_handler, msv);
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

void 
synset::calc_stabi_arr_rec(num_syn_t cap, num_syn_t* arr, num_syn_t& ii) { // careful with stack usage
	set_stabi_arr(cap, arr, ii++, tot_syn);

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = grps;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		EMU_CK(sub_grp->parent == this);
		sub_grp->calc_stabi_arr_rec(cap, arr, ii);
	}

	//set_stabi_arr(cap, arr, ii++, tot_grp);
}

void 
neurostate::calc_stabi_arr() {
	if(stabi_arr == mc_null){
		stabi_arr_cap = calc_stabi_arr_cap(stabi_active_set.tot_syn);
		stabi_arr = mc_malloc32(num_syn_t, stabi_arr_cap);
	}
	stabi_arr_sz = 0;
	stabi_active_set.calc_stabi_arr_rec(stabi_arr_cap, stabi_arr, stabi_arr_sz);
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

	EMU_CK(dat.ti != BJ_INVALID_NUM_TIER);

	//if(bj_nervenet->get_active_netstate(dat.sd).sync_ending_propag){ return; }

	owner->stabi_recv_transmitter(&dat);
}

void
netstate::reset_sync(num_tier_t rem_ti){
	EMU_CK(rem_ti != BJ_INVALID_NUM_TIER);

	sync_tier_in = rem_ti;

	sync_tot_stopping_children = 0;
}

void
nervenet::stabi_handler(missive* msv){
	if(msv->tok == bj_tok_stabi_start){
		stabi_nervenet_start();
		return;
	}

	transmitter* tmt = (transmitter*)msv;
	net_side_t tmt_sd = tmt->wrk_side;
	num_tier_t tmt_ti = tmt->wrk_tier;

	EMU_CK((tmt_ti != BJ_INVALID_NUM_TIER) || (msv->tok == bj_tok_sync_to_children));
	EMU_CK(tmt_sd != side_invalid);

	netstate& nst = get_active_netstate(tmt_sd);

	switch(msv->tok){
		case bj_tok_sync_empty_child:
		{
			//EMU_LOG("INC_EMPTY %ld %s \n", kernel::get_core_nn(), net_side_to_str(tmt_sd));

			nst.sync_tot_empty_children++;

			//EMU_LOG("SYNC_RCV_EMPTY %s tot_empty %d \n", net_side_to_str(tmt_sd), 
			//			nst.sync_tot_empty_children);
		}
		break;
		case bj_tok_sync_to_parent:
		{
			if((nst.sync_tier_in == BJ_INVALID_NUM_TIER) || (tmt_ti > nst.sync_tier_in)){
				nst.reset_sync(tmt_ti);
			}
			if(tmt_ti == nst.sync_tier_in){
				nst.sync_tot_stopping_children++;
			}
			/*EMU_LOG("SYNC_RCV_STOP [%d <<- %d] stpping=%d of %d "
					"tmt_sd=%s tmt_ti=%d in_ti=%d out_ti=%d \n", 
				kernel::get_core_nn(), mc_id_to_nn(mc_addr_get_id(msv->src)), 
				nst.sync_tot_stopping_children, sync_tot_children, 
				net_side_to_str(tmt_sd), tmt_ti, nst.sync_tier_in, nst.sync_tier_out);*/
		}
		break;
		case bj_tok_sync_to_children:
			nst.send_sync_to_children();
		break;
		default:
			mck_abort(1, mc_cstr("BAD_STABI_TOK"));
		break;
	}
}

void
nervenet::stabi_nervenet_start(){
	EMU_LOG("stabi_nervenet_start \n");

	nervenet* my_net = this;

	binder * fst, * lst, * wrk;

	binder* pt_all_neu = &(all_neu);
	fst = (binder*)(pt_all_neu->bn_right);
	lst = pt_all_neu;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		neuron* my_neu = (neuron*)wrk;
		EMU_CK(my_neu->ki == nd_neu);
		my_net->send(my_neu, bj_tok_stabi_start);
	}

	act_left_side.update_sync_ti_out();
	act_right_side.update_sync_ti_out();
}

void 
send_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd){
	EMU_CK(mth != mc_null);

	binder * fst, * lst, * wrk;

	fst = (binder*)(nn_all_snp->bn_right);
	lst = nn_all_snp;
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

		(my_snp->owner->*mth)(my_snp, sd);
	}
}

void
synset::stabi_rec_send_all(bj_callee_t mth, net_side_t sd){
	MCK_CHECK_SP();
	send_all_synapses(&(all_syn), mth, sd);

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = grps;
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

	bj_nervenet->act_left_side.update_sync_ti_out();

	left_side.reset_complete();

	left_side.send_all_ti_done(this, side_left);
}

void 
neuron::stabi_send_snp_propag(synapse* snp, net_side_t sd){
	synset& active = get_active_set(sd);

	EMU_CK(snp->owner == this);
	EMU_CK(active.tot_syn != 0);
	if(active.tot_syn == 1){
		snp->send_transmitter(bj_tok_stabi_charge_all, sd);
	} else {
		snp->send_transmitter(bj_tok_stabi_ping, sd);
	}
}

void 
nervenode::stabi_send_snp_tier_done(synapse* snp, net_side_t sd){
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_tier_done, sd);
}

void
neurostate::send_all_ti_done(nervenode* nd, net_side_t sd){
	tierset* c_ti = get_tiset(stabi_num_tier);
	if(c_ti != mc_null){
		EMU_LOG("::send_all_ti_done WITH_PRV_TI %s %ld %s \n", node_kind_to_str(nd->ki), 
				nd->id, net_side_to_str(sd));
		send_all_synapses(&(c_ti->ti_all), (bj_callee_t)(&nervenode::stabi_send_snp_tier_done), sd);
	}

	stabi_active_set.stabi_rec_send_all((bj_callee_t)(&nervenode::stabi_send_snp_tier_done), sd);

	stabi_num_tier++;

	EMU_LOG("INC_TIER %s %ld %s TI=%d \n", node_kind_to_str(nd->ki), nd->id, net_side_to_str(sd), stabi_num_tier);
}

void
nervenode::stabi_recv_transmitter(propag_data* dat){

	EMU_CODE(
		neurostate& stt = get_neurostate(dat->sd);
		
		bool ok_1 = ((dat->ti + 1) == stt.stabi_num_tier) || (dat->ti == stt.stabi_num_tier);
		EMU_CK_PRT(ok_1, "%s %s %ld %s (%d > %d)", stabi_tok_to_str(dat->tok),
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), (dat->ti + 1), stt.stabi_num_tier);

		EMU_CK(dat->ti < 5); // debug_purposes_only

		nervenode* rem_nd = dat->snp->mate->owner;
		EMU_LOG("::stabi_recv_transmitter %s [%s %ld <<- %s %ld] %s dat_TI=%d nod_TI=%d \n", 
			stabi_tok_to_str(dat->tok), node_kind_to_str(ki), id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
			net_side_to_str(dat->sd), dat->ti, stt.stabi_num_tier);
	);
	

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
	//if(! stabi_active_set.all_syn.is_alone()){
	if(! stabi_active_set.is_empty()){

		resp = true;
		tierset& ti_grp = add_tiset(dat->ti);
		ti_grp.ti_all.move_all_to_my_right(stabi_active_set.all_syn);

		stabi_active_set.tot_syn = 0;
		stabi_num_ping = 0;

		bj_nervenet->get_active_netstate(dat->sd).get_tier(dat->ti).inc_off(dat->sd, ki);
	}
	EMU_CK(stabi_active_set.is_empty());
	resp = (resp && ! stabi_tiers.is_alone()); 
	return resp;
}

void
nervenode::stabi_recv_charge_all(propag_data* dat){
	EMU_CK(dat != mc_null);
	EMU_CK(dat->sd != side_invalid);

	neurostate& stt = get_neurostate(dat->sd);

	EMU_LOG("nervenode::stabi_recv_charge_all %s %ld %s stb_src=%p \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), stt.stabi_source);

	if(stt.stabi_source == mc_null){
		EMU_CODE(nervenode* stb_src = dat->snp->mate->owner);
		EMU_CK(stb_src != mc_null);

		EMU_LOG("SET_STB_SRC %s %ld %s stb_src: %s %ld \n", 
				node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
				node_kind_to_str(stb_src->ki), stb_src->id);

		EMU_CK_PRT(! stt.stabi_active_set.is_empty(), "::stabi_recv_charge_all EMPTY_ACTIVE !!!");

		mc_set_flag(stt.stabi_flags, bj_stt_charge_all_flag);
		stt.stabi_source = dat->snp;
	}
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
	mc_set_flag(stt.stabi_flags, bj_stt_charge_src_flag);

	if(! stt.stabi_active_set.is_empty()){

		tierset& ti_grp = stt.add_tiset(dat->ti);

		binder& bdr = dat->snp->get_side_binder(dat->sd);
		bdr.let_go();
		ti_grp.ti_all.bind_to_my_left(bdr);

		stt.stabi_active_set.tot_syn--;

		if(stt.stabi_active_set.tot_syn == 0){
			stt.stabi_num_ping = 0;
			bj_nervenet->get_active_netstate(dat->sd).get_tier(dat->ti).inc_off(dat->sd, ki);
		}
	}
}

void
nervenode::stabi_recv_ping(propag_data* dat){
	neurostate& stt = get_neurostate(dat->sd);
	stt.stabi_num_ping++;

	EMU_LOG("INC_PINGS %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.stabi_num_ping, dat->ti);
}

void
nervenode::stabi_recv_tier_done(propag_data* dat){

	neurostate& stt = get_neurostate(dat->sd);

	stt.stabi_num_complete++;

	EMU_LOG("ADD_TIER_END %s %ld %s compl(%d of %d) TI=%d \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.stabi_num_complete, stt.prev_tot_active, dat->ti);

	if(stt.stabi_num_complete == stt.prev_tot_active){
		// order of this is important:
		netstate& nst = bj_nervenet->get_active_netstate(dat->sd);
		nst.get_tier(dat->ti).inc_rcv(ki);

		EMU_CK(nst.get_ti_id() >= dat->ti);
		EMU_LOG("TIER_COMPLETE %s %ld %s TI=%d net_ti=%d \n", 
				node_kind_to_str(ki), id, net_side_to_str(dat->sd), dat->ti, nst.get_ti_id());

		stabi_start_nxt_tier(dat);
	}
}

void
neurostate::update_stills(nervenode* nd, propag_data* dat){
	EMU_LOG("update_stills %s %ld %s still(%ld == %ld) TI=%d \n", 
			node_kind_to_str(nd->ki), nd->id, net_side_to_str(dat->sd), 
			stabi_num_ping, stabi_active_set.tot_syn, dat->ti);

	EMU_CK(bj_nervenet->get_active_netstate(dat->sd).get_last_tier().tdt_id == dat->ti);

	if((prev_tot_active > 0) && (stabi_num_ping == stabi_active_set.tot_syn)){
		EMU_LOG("INC_STILL %s %ld %s  TI=%d \n", node_kind_to_str(nd->ki), nd->id, 
				net_side_to_str(dat->sd), dat->ti);
		bj_nervenet->get_active_netstate(dat->sd).inc_still(nd->ki);
	}
}

void 
nervenode::stabi_send_snp_charge_src(synapse* snp, net_side_t sd){
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_charge_src, sd);
}

void 
nervenode::stabi_send_snp_conflict(synapse* snp, net_side_t sd){
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_conflict, sd);
}

void 
nervenode::stabi_send_snp_end_forward(synapse* snp, net_side_t sd){
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_end_forward, sd);
}

void 
nervenode::stabi_send_snp_propag(synapse* snp, net_side_t sd){
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_ping, sd);
}

void 
polaron::stabi_send_snp_charge_all(synapse* snp, net_side_t sd){
	EMU_CK(snp->owner == this);
	snp->send_transmitter(bj_tok_stabi_charge_all, sd);
}

bool
synset::is_empty(){
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

/*
net_side_t
opp_side_of(net_side_t sd){
	net_side_t opp = side_invalid;
	switch(sd){
	case side_left:
		opp = side_right;
	break;
	case side_right:
		opp = side_left;
	break;
	default:
	break;
	}
	EMU_CK(opp != side_invalid);
	return opp;
}*/

char*
tierdata::to_str(){
	char* resp = mc_cstr("[NOT_EMU tierdata::to_str]");
	/*EMU_CODE(
		char buff[100];
		sprintf(buff, "hola %d \n", 100);
	);*/
	return resp;
}

synset& 
nervenode::get_active_set(net_side_t sd){
	EMU_CK(sd != side_invalid);

	synset* out_set = &left_side.stabi_active_set;
	if(sd == side_right){
		out_set = &right_side.stabi_active_set;
	}
	EMU_CK(out_set != mc_null);
	return *out_set;
}

void 
tierdata::inc_rcv(node_kind_t kk){
	if(kk == nd_neu){ rcv_neus++; }
}

void
tierdata::inc_off(net_side_t sd, node_kind_t kk){
	if(kk == nd_neu){ off_neus++; }
	update_parent_num_empty(sd);
}

void 
netstate::inc_still(node_kind_t kk){
	if(kk == nd_neu){ curr_ti_still_neus++; }
}

void
neurostate::reset_complete(){
	stabi_flags = 0;
	stabi_num_complete = 0;
	stabi_num_ping = 0;
	prev_tot_active = stabi_active_set.tot_syn;
}

tierset*
neurostate::get_tiset(num_tier_t nti){
	if(stabi_tiers.is_alone()){
		return mc_null;
	}
	tierset* tis = (tierset*)stabi_tiers.bn_left;
	EMU_CK(tis->ti_id != BJ_INVALID_NUM_TIER);
	if(nti == BJ_INVALID_NUM_TIER){
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
	return (stabi_active_set.is_empty() && (stabi_source == mc_null) && (get_tiset(nti) != mc_null));
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

	if(opp_stt.stabi_num_complete != opp_stt.prev_tot_active){
		EMU_LOG("OPP_INCOMPLETE %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
		return;
	}
	EMU_LOG("OPP_COMPLETE %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));

	bool pol_chg = mc_get_flag(pol_stt.stabi_flags, bj_stt_charge_all_flag);
	bool opp_chg = mc_get_flag(opp_stt.stabi_flags, bj_stt_charge_all_flag);

	EMU_CK(! pol_chg || (pol_stt.stabi_source != mc_null));
	EMU_CK(! opp_chg || (opp_stt.stabi_source != mc_null));

	if(pol_chg && opp_chg){
		EMU_LOG("POL CONFLICT %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
		EMU_CK(false && "POL_CONFLIT_CASE"); // CODE_THIS_CASE
		// conflict. start backpropag.
		pol_stt.charge_all_active(dat, ki);
		opp_stt.charge_all_active(dat, opp->ki);

		tierset* ti_grp = pol_stt.get_tiset(dat->ti);
		if(ti_grp != mc_null){
			//send_all_synapses(&(ti_grp->ti_all), (bj_callee_t)(&nervenode::stabi_send_snp_conflict), dat->sd);
		}
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

	pol_stt.update_stills(pol, dat);
	opp_stt.update_stills(opp, dat);

	bj_nervenet->get_active_netstate(dat->sd).update_sync_ti_out();

	pol_stt.reset_complete();
	opp_stt.reset_complete();

	pol_stt.send_all_ti_done(pol, dat->sd);
	opp_stt.send_all_ti_done(opp, dat->sd);
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
		if(stt.stabi_active_set.is_empty() && (stt.stabi_source == mc_null)){
			EMU_LOG("NEU CONFLICT %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
			EMU_CK(false && "NEU_CONFLIT_CASE");
		} else {
			stt.send_all_propag(this, dat);
		}
	}

	stt.update_stills(this, dat);

	bj_nervenet->get_active_netstate(dat->sd).update_sync_ti_out();

	stt.reset_complete();
	stt.send_all_ti_done(this, dat->sd);
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
	mck_slog2("LOADED_CNF___\n");
	bj_print_active_cnf(side_left, 1, 2, 0);

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->stabi_init_sync();

	EMU_CODE(if(kernel::get_core_nn() == 0){ emu_prt_tok_codes(); });

	my_net->send(my_net, bj_tok_stabi_start);
	kernel::run_sys();

	mck_slog2("REDUCED_CNF___\n");
	bj_print_active_cnf(side_left, 1, 3, 0);
	bj_print_active_cnf(side_left, 1, 4, BJ_INVALID_NUM_TIER);

	EMU_PRT("...............................END_STABI\n");
	mck_slog2("END_STABI___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");

}

tierdata&
netstate::get_tier(num_tier_t nti){
	EMU_CK(! all_tiers.is_alone());
	EMU_CK(nti != BJ_INVALID_NUM_TIER);

	tierdata* dat = mc_null;
	binder * fst, * lst, * wrk;

	binder* tis = &(all_tiers);
	fst = (binder*)(tis->bn_left);
	lst = tis;
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
	if(dat == mc_null){
		while(get_last_tier().tdt_id < nti){
			inc_tier();
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
	if(inp_neus != BJ_INVALID_NUM_NODE){
		return;
	}
	tierdata* prv = (tierdata*)(bn_left);
	if(prv->got_all()){
		inp_neus = prv->inp_neus - prv->off_neus;
		EMU_CK(inp_neus != BJ_INVALID_NUM_NODE);
		//EMU_CK(inp_neus > 0);
	}
}

void
netstate::inc_tier(){
	tierdata& lti = get_last_tier();

	tierdata* ti_dat = tierdata::acquire();
	ti_dat->tdt_id = lti.tdt_id + 1;
	all_tiers.bind_to_my_left(*ti_dat);

	EMU_LOG("INC_NET_TIER %d %s nw_ti=%d \n", kernel::get_core_nn(), net_side_to_str(my_side), ti_dat->tdt_id);

	curr_ti_still_neus = 0;

	ti_dat->update_tidat();
}

nervenet*
nervenet::get_nervenet(mc_core_id_t id){
	nervenet* rem_net = (nervenet*)mc_addr_set_id(id, this);
	return rem_net;
}

void
netstate::send_sync_transmitter(nervenet* the_dst, sync_tok_t the_tok, num_tier_t the_ti, 
		mc_core_nn_t dbg_dst_nn)
{

	transmitter* trm = transmitter::acquire();
	trm->src = bj_nervenet;
	trm->dst = the_dst;
	trm->tok = the_tok;

	trm->wrk_side = my_side;
	trm->wrk_tier = the_ti;

	trm->send();

	EMU_LOG("::send_sync_transmitter %s [%ld ->> %ld] %s net_ti=%d  \n", 
		sync_tok_to_str(the_tok), kernel::get_core_nn(), dbg_dst_nn, 
		net_side_to_str(my_side), the_ti);
}

void 
netstate::send_sync_to_children(){
	//EMU_LOG("SYNC_STOP_CHILDREN CORE=%d %s \n", kernel::get_core_nn(), net_side_to_str(my_side));

	mc_load_map_st** my_children = bj_nervenet->sync_map->childs;
	if(my_children != mc_null){ 
		int aa = 0;
		mc_load_map_st* ch_map = (my_children)[aa];
		while(ch_map != mc_null){
			mc_core_nn_t chd_nn = ch_map->num_core;
			nervenet* ch_net = bj_nervenet->get_nervenet(mc_nn_to_id(chd_nn));
			send_sync_transmitter(ch_net, bj_tok_sync_to_children, BJ_INVALID_NUM_TIER, chd_nn);
			//EMU_PRT_STACK(true, "bj_tok_sync_to_children CORE=%d \n", get_core_nn());

			aa++;
			ch_map = (my_children)[aa];
		}
	}

	//EMU_LOG("SYNC_ENDING_PROPAG CORE=%d %s \n", kernel::get_core_nn(), net_side_to_str(my_side));

	sync_ending_propag = true;
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
tierdata::update_parent_num_empty(net_side_t sd){
	if(is_tidat_empty()){
		bj_nervenet->start_send_empty_child(sd);
	}
}

void
nervenet::start_send_empty_child(net_side_t sd){
	netstate& nst = get_active_netstate(sd);
	num_tier_t ti_curr = nst.get_last_tier().tdt_id;

	if(nst.sync_sent_tier_empty != BJ_INVALID_NUM_TIER){
		return;
	}
	EMU_CK(ti_curr != BJ_INVALID_NUM_TIER);

	nst.sync_sent_tier_empty = ti_curr;

	EMU_LOG("GOT_EMPTY [%ld ->> %ld] %s net_ti=%d  \n", 
		kernel::get_core_nn(), mc_id_to_nn(sync_parent_id), 
		net_side_to_str(sd), ti_curr);
}

/*
void
nervenet::send_parent_tok_empty_child(net_side_t sd){
	EMU_CK(sd != side_invalid);

	netstate& nst = get_active_netstate(sd);
	if(nst.sync_tot_empty_children < sync_tot_children){
		return;
	}
	if(nst.sync_sent_tier_empty == BJ_INVALID_NUM_TIER){
		return;
	}
	if(nst.sync_sent_ti_empty){
		return;
	}
	nst.sync_sent_ti_empty = true;

	if(sync_parent_id != 0){
		nervenet* pnt_net = get_nervenet(sync_parent_id);
		nst.send_sync_transmitter(pnt_net, bj_tok_sync_empty_child, nst.sync_sent_tier_empty,
				mc_id_to_nn(sync_parent_id));
	} 
}*/

bool
netstate::is_propag_over(){
	tierdata& cti = get_last_tier();

	if(! cti.got_all()){ return false; }

	bool all_over = ((cti.inp_neus != BJ_INVALID_NUM_NODE) && (curr_ti_still_neus == cti.inp_neus));

	if(all_over){
		cti.update_parent_num_empty(my_side);
	}

	return all_over;
}

bool
netstate::has_work_children(){
	mc_core_nn_t tot_chdn = bj_nervenet->sync_tot_children - sync_tot_empty_children;
	bool has_chldn = (tot_chdn != 0);
	EMU_CK(! has_chldn || (tot_chdn > 0));
	return has_chldn;
}

void 
netstate::update_sync_ti_out(){
}

void
netstate::handle_my_sync(){
	if(sync_sent_ti_empty){
		return;
	}
	if(! is_propag_over()){
		return;
	}

	tierdata& last_tdt = get_last_tier();
	bool has_chdn = has_work_children();

	if(! has_chdn){ sync_tier_in = last_tdt.tdt_id; }

	if(sync_tier_in == BJ_INVALID_NUM_TIER){
		EMU_LOG("NO_sync_to_parent in_ti=%d \n", sync_tier_in);
		return;
	}

	if(! last_tdt.is_tidat_empty() && (sync_tier_in != last_tdt.tdt_id)){
		EMU_LOG("NO_sync_to_parent (in_ti=%d) != (lst_ti=%d) \n", sync_tier_in, last_tdt.tdt_id);
		return;
	}

	mc_core_nn_t act_chdn = bj_nervenet->sync_tot_children - sync_tot_empty_children;
	if(sync_tot_stopping_children != act_chdn){
		EMU_LOG("NO_sync_to_parent ((#stping_chdn=%d) != (#act_chdn=%d)) (%d - %d) \n", 
			sync_tot_stopping_children, act_chdn, bj_nervenet->sync_tot_children, sync_tot_empty_children);
		return;
	}

	if(sync_tier_out == sync_tier_in){
		//EMU_LOG("NO_sync_to_parent sent_stop \n");
		return;
	}
	sync_tier_out = sync_tier_in;

	mc_core_id_t pnt_id = bj_nervenet->sync_parent_id;
	/*EMU_LOG("SYNC_SEND_STOP_TO_PNT %s ETYme=%d CORE=%d #chd=%d #ETYchd=%d last_ti=%d out_ti=%d \n", 
		net_side_to_str(my_side), is_last_empty(), mc_id_to_nn(pnt_id), act_chdn, 
		sync_tot_empty_children, get_last_tier().tdt_id, sync_tier_out);*/

	if(pnt_id != 0){
		nervenet* pnt_net = bj_nervenet->get_nervenet(pnt_id);
		mc_core_nn_t pnt_nn = mc_id_to_nn(pnt_id);
		if((act_chdn == 0) && last_tdt.is_tidat_empty()){
			send_sync_transmitter(pnt_net, bj_tok_sync_empty_child, sync_tier_out, pnt_nn);
			sync_sent_ti_empty = true;
		} else {
			send_sync_transmitter(pnt_net, bj_tok_sync_to_parent, sync_tier_out, pnt_nn);
		}
	} else {
		send_sync_to_children();
	}
	
}
