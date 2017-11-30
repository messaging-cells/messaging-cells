
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
	EMU_CODE(nervenode* rem_nd = mate->owner);
	EMU_LOG("::send_transmitter %s [%s %ld ->> %s %ld] %s nod_TI=%d  \n", stabi_tok_to_str(tok), 
		node_kind_to_str(owner->ki), owner->id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
		net_side_to_str(sd), owner->get_neurostate(sd).stabi_num_tier);

	transmitter* trm = transmitter::acquire();
	trm->src = this;
	trm->dst = mate;
	trm->tok = tok;
	trm->wrk_side = sd;
	trm->wrk_tier = owner->get_neurostate(sd).stabi_num_tier;
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

	owner->stabi_recv_transmitter(&dat);
}

void
nervenet::reset_sync(net_side_t	rem_sd, num_tier_t rem_ti){
	EMU_CK(rem_sd != side_invalid);
	EMU_CK(rem_ti != BJ_INVALID_NUM_TIER);
	//EMU_CK((sync_side_in == side_invalid) || 
	//	(sync_tot_stopping_children >= get_active_netstate(sync_side_in).sync_tot_empty_children));

	sync_side_in = rem_sd;
	sync_tier_in = rem_ti;

	sync_tot_stopping_children = 0;
	//sync_tot_stopping_children = get_active_netstate(sync_side_in).sync_tot_empty_children;
}

void
nervenet::stabi_handler(missive* msv){
	cell* msv_src = msv->src;
	mck_token_t tok = (mck_token_t)msv->tok;
	MC_MARK_USED(msv_src);
	MC_MARK_USED(tok);

	switch(tok){
		case bj_tok_stabi_start:
			stabi_nervenet_start();
		break;
		case bj_tok_sync_empty_child:
		{
			transmitter* tmt = (transmitter*)msv;
			net_side_t	rem_sd = tmt->wrk_side;
			EMU_LOG("INC_EMPTY %ld %s \n", kernel::get_core_nn(), net_side_to_str(rem_sd));

			EMU_CK(rem_sd != side_invalid);
			get_active_netstate(rem_sd).sync_tot_empty_children++;

			EMU_LOG("SYNC_RCV_EMPTY %s tot_empty %d \n", net_side_to_str(rem_sd), 
						get_active_netstate(rem_sd).sync_tot_empty_children);
		}
		break;
		case bj_tok_sync_to_parent:
		{
			transmitter* tmt = (transmitter*)msv;
			net_side_t	rem_sd = tmt->wrk_side;
			num_tier_t rem_ti = tmt->wrk_tier;

			if((sync_tier_in == BJ_INVALID_NUM_TIER) || (rem_ti > sync_tier_in)){
				reset_sync(rem_sd, rem_ti);
			}
			if(rem_ti == sync_tier_in){
				if((rem_sd == side_left) && (sync_side_in == side_right)){
					reset_sync(rem_sd, rem_ti);
				} else {
					sync_tot_stopping_children++;
				}
			}
			EMU_LOG("SYNC_RCV_STOP [%d <<- %d] stpping=%d of %d "
					"tmt_sd=%s in_sd=%s out_sd=%s tmt_ti=%d in_ti=%d out_ti=%d \n", 
				kernel::get_core_nn(), mc_id_to_nn(mc_addr_get_id(msv->src)), 
				sync_tot_stopping_children, sync_tot_children, 
				net_side_to_str(rem_sd), net_side_to_str(sync_side_in), net_side_to_str(sync_side_out), 
				rem_ti, sync_tier_in, sync_tier_out);
		}
		break;
		case bj_tok_sync_to_children:
			send_sync_to_children();
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

	update_sync_ti_out();
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

	bj_nervenet->update_sync_ti_out();

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

	EMU_LOG("nervenode::stabi_charge_all %s %ld %s stb_src=%p \n", 
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), stt.stabi_source);

	if(stt.stabi_source == mc_null){
		EMU_CODE(nervenode* stb_src = dat->snp->mate->owner);
		EMU_CK(stb_src != mc_null);
		EMU_CK(! stt.stabi_active_set.is_empty());

		EMU_LOG("SET_STB_SRC %s %ld %s stb_src: %s %ld \n", 
				node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
				node_kind_to_str(stb_src->ki), stb_src->id);

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
	switch(kk){
		case nd_neu:
			rcv_neus++;
		break;
		case nd_pos:
		case nd_neg:
			rcv_pols++;
		break;
		default:
		break;
	}
}

void
tierdata::inc_off(net_side_t sd, node_kind_t kk){
	switch(kk){
		case nd_neu:
			off_neus++;
		break;
		case nd_pos:
		case nd_neg:
			off_pols++;
		break;
		default:
		break;
	}
	update_parent_num_empty(sd);
}

void 
netstate::inc_still(node_kind_t kk){
	switch(kk){
		case nd_neu:
			curr_ti_still_neus++;
		break;
		case nd_pos:
		case nd_neg:
			curr_ti_still_pols++;
		break;
		default:
		break;
	}
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

	bj_nervenet->update_sync_ti_out();

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

	bj_nervenet->update_sync_ti_out();

	stt.reset_complete();
	stt.send_all_ti_done(this, dat->sd);
}

void 
nervenet::dbg_stabi_stop_sys(propag_data* dat, nervenode* nod){
	
	tierdata& tda = act_left_side.get_last_tier();
	EMU_CK((dat == mc_null) || (dat->sd == side_left));
	if(tda.got_all_pols()){
		EMU_LOG("STOP_SYS(pols) (%d==%d)\n", tda.inp_pols, tda.rcv_pols);
		kernel::stop_sys(bj_tok_stabi_end);
	}
}

void bj_stabi_main() {
	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_stabi_init_handlers();

	EMU_LOG("STABI___ %d \n", nn);

	bj_print_loaded_cnf();

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->stabi_init_sync();

	EMU_CODE(if(kernel::get_core_nn() == 0){ emu_prt_tok_codes(); });

	my_net->send(my_net, bj_tok_stabi_start);
	kernel::run_sys();

	EMU_PRT("...............................END_STABI\n");
	mck_slog2("END_STABI___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");

}

tierdata&
netstate::get_tier(num_tier_t nti){
	EMU_CK(! all_tiers.is_alone());

	if(nti == BJ_INVALID_NUM_TIER){
		return get_last_tier();
	}

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
		EMU_CK(inp_pols != BJ_INVALID_NUM_NODE);
		return;
	}
	tierdata* prv = (tierdata*)(bn_left);
	if(prv->got_all()){
		inp_neus = prv->inp_neus - prv->off_neus;
		inp_pols = prv->inp_pols - prv->off_pols;
		EMU_CK(inp_neus != BJ_INVALID_NUM_NODE);
		EMU_CK(inp_pols != BJ_INVALID_NUM_NODE);
		EMU_CK((inp_neus + inp_pols) > 0);
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
	curr_ti_still_pols = 0;

	ti_dat->update_tidat();
}

nervenet*
nervenet::get_nervenet(mc_core_id_t id){
	nervenet* rem_net = (nervenet*)mc_addr_set_id(id, this);
	return rem_net;
}

void 
nervenet::send_sync_to_children(){
	EMU_LOG("SYNC_STOP_CHILDREN CORE=%d \n", kernel::get_core_nn());

	if(sync_map->childs != mc_null){ 
		int aa = 0;
		mc_load_map_st* ch_map = (sync_map->childs)[aa];
		while(ch_map != mc_null){
			EMU_LOG("send_stop to CHILD=%d \n", ch_map->num_core);
			mc_core_nn_t chd_nn = ch_map->num_core;
			nervenet* ch_net = get_nervenet(mc_nn_to_id(chd_nn));

			//EMU_PRT_STACK(true, "bj_tok_sync_to_children CORE=%d \n", get_core_nn());

			missive* msv = missive::acquire();
			msv->src = this;
			msv->dst = ch_net;
			msv->tok = bj_tok_sync_to_children;
			msv->send();

			aa++;
			ch_map = (sync_map->childs)[aa];
		}
	}

	EMU_PRT("SYNC_SET_IDLE CORE=%d \n", kernel::get_core_nn());

	mck_get_kernel()->set_idle_exit();
	//kernel::stop_sys(bj_tok_stabi_end);
}

void bj_kernel_func(){
	nervenet* my_net = bj_nervenet;
	my_net->handle_sync();
}

bool
nervenet::has_work_children(){
	bool has_left_chldn = ((sync_tot_children - get_active_netstate(side_left).sync_tot_empty_children) != 0);
	bool has_right_chldn = ((sync_tot_children - get_active_netstate(side_right).sync_tot_empty_children) != 0);

	bool has_childs = (has_left_chldn || has_right_chldn);
	return has_childs;
}

void 
nervenet::handle_sync(){
	if(sync_tier_out == BJ_INVALID_NUM_TIER){
		return;
	}

	bool has_childs = has_work_children();

	if(has_childs && (sync_tier_out != sync_tier_in)){
		EMU_LOG("NO_sync_to_parent (out_ti=%d) != (in_ti=%d) \n", sync_tier_out, sync_tier_in);
		return;
	}
	if(has_childs && (sync_side_out != sync_side_in)){
		EMU_LOG("NO_sync_to_parent (out_sd=%s) != (in_sd=%s) \n", 
			net_side_to_str(sync_side_out), net_side_to_str(sync_side_in));
		return;
	}
	if(sync_sent_stop_to_parent){
		//EMU_LOG("NO_sync_to_parent sent_stop \n");
		return;
	}
	EMU_CK((sync_side_out == side_left) || (sync_side_out == side_right));

	netstate& nst = get_active_netstate(sync_side_out);
	mc_core_nn_t tot_chdn = sync_tot_children;
	if(nst.get_last_tier().tdt_id != sync_tier_out){
		tot_chdn -= nst.sync_tot_empty_children;
	}

	if(sync_tot_stopping_children == tot_chdn){
		EMU_LOG("SYNC_SEND_STOP_TO_PNT ETYme=%d CORE=%d #chd=%d #ETYchd=%d out_sd=%s out_ti=%d \n", 
			is_nervnet_empty(), mc_id_to_nn(sync_parent_id), tot_chdn, nst.sync_tot_empty_children, 
			net_side_to_str(sync_side_out), sync_tier_out);

		sync_sent_stop_to_parent = true;

		if(sync_parent_id != 0){
			nervenet* pnt_net = get_nervenet(sync_parent_id);

			transmitter* trm = transmitter::acquire();
			trm->src = this;
			trm->dst = pnt_net;
			trm->tok = bj_tok_sync_to_parent;

			trm->wrk_side = sync_side_out;
			trm->wrk_tier = sync_tier_out;

			trm->send();
		} else {
			send_sync_to_children();
		}
	}
}

void
tierdata::update_parent_num_empty(net_side_t sd){
	if(is_tidat_empty()){
		EMU_LOG("CORE_GOT_EMPTY send_to_pnt_empty_chld %ld %s \n", kernel::get_core_nn(), net_side_to_str(sd));
		bj_nervenet->send_parent_tok_empty_child(sd);
	}
}

void
nervenet::send_parent_tok_empty_child(net_side_t sd){
	netstate& nst = get_active_netstate(sd);
	num_tier_t ti_curr = nst.get_last_tier().tdt_id;
	num_tier_t ti_sent = nst.sync_sent_tier_empty;

	if((ti_sent != BJ_INVALID_NUM_TIER) && (ti_curr <= ti_sent)){
		return;
	}

	EMU_CK(sd != side_invalid);

	if(sync_parent_id != 0){
		nervenet* pnt_net = get_nervenet(sync_parent_id);

		transmitter* trm = transmitter::acquire();
		trm->src = this;
		trm->dst = pnt_net;
		trm->tok = bj_tok_sync_empty_child;

		trm->wrk_side = sd;
		trm->wrk_tier = ti_curr;

		trm->send();

		nst.sync_sent_tier_empty = ti_curr;

		EMU_LOG("SEND_EMPTY [%ld ->> %ld] %s net_ti=%d  \n", 
			kernel::get_core_nn(), mc_id_to_nn(sync_parent_id), 
			net_side_to_str(sd), trm->wrk_tier);
	} 
}

bool
netstate::is_propag_over(){
	tierdata& cti = get_last_tier();

	if(! cti.got_all()){ return false; }

	//cti.update_parent_num_empty(my_side);

	//if((cti.inp_neus == 0) && (cti.inp_pols != 0) && (cti.tdt_id == 0)){ return false; }

	bool all_neus_still = ((cti.inp_neus != BJ_INVALID_NUM_NODE) && (curr_ti_still_neus == cti.inp_neus));
	bool all_pols_still = ((cti.inp_pols != BJ_INVALID_NUM_NODE) && (curr_ti_still_pols == cti.inp_pols));
	bool all_over = (all_neus_still && all_pols_still);

	if(all_over){
		cti.update_parent_num_empty(my_side);
	}

	EMU_LOG("IS_NET_PROPAG_OVER %s %d == ((%d == %d) && (%d == %d)) net_ti=%d \n", 
		net_side_to_str(my_side), all_over, 
		curr_ti_still_neus, cti.inp_neus, 
		curr_ti_still_pols, cti.inp_pols, cti.tdt_id);

	return all_over;
}

void 
nervenet::update_sync_ti_out(){

	if(act_left_side.is_propag_over() && act_right_side.is_propag_over())
	{
		tierdata& lft = act_left_side.get_last_tier();
		tierdata& rgt = act_right_side.get_last_tier();
		//tierdata& lft = act_left_side.get_sync_tier();
		//tierdata& rgt = act_right_side.get_sync_tier();

		sync_sent_stop_to_parent = false;
		if(rgt.tdt_id > lft.tdt_id){
			sync_side_out = side_right;
			sync_tier_out = rgt.tdt_id;
		} else {
			sync_side_out = side_left;
			sync_tier_out = lft.tdt_id;
		}

		EMU_CK(sync_side_out != side_invalid);
		EMU_CK(sync_tier_out != BJ_INVALID_NUM_TIER);

		EMU_CODE(netstate& nst = get_active_netstate(sync_side_out));
		//EMU_PRT("SYNC_SET STOP sd=%s tier=%d stopping=%d of %d \n", net_side_to_str(sync_side_out), 
		//			sync_tier_out, sync_tot_stopping_children, sync_tot_children);
		EMU_LOG("SYNC_STARTING_STOP %s IS_EMPTY=%d TOT_CHDN=%d empty_chdn=%d stopping=%d " 
				"out_ti=%d in_ti=%d net_ti=%d pnt_nn=%d \n", 
			net_side_to_str(sync_side_out), is_nervnet_empty(),
			sync_tot_children, nst.sync_tot_empty_children, sync_tot_stopping_children, 
			sync_tier_out, sync_tier_in, 
			nst.get_ti_id(), mc_id_to_nn(sync_parent_id));
	}
}

tierdata&
netstate::get_sync_tier(){
	tierdata& cti = get_last_tier();
	if((cti.inp_neus == 0) && (cti.inp_pols != 0)){
		EMU_CK(cti.tdt_id > 0);
		EMU_CK(cti.bn_left != &all_tiers);
		EMU_LOG("SYNC_ONLY_POLS \n");
		return *((tierdata*)(cti.bn_left));
	}
	return cti;
}

// sync_tot_stopping_children