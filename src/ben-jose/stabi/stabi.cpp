
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

	owner->stabi_recv_propag(&dat);
}

void
nervenet::stabi_handler(missive* msv){
	cell* msv_src = msv->src;
	mck_token_t tok = (mck_token_t)msv->tok;
	MC_MARK_USED(msv_src);
	MC_MARK_USED(tok);

	//nervenet* my_net = bj_nervenet;
	switch(tok){
		case bj_tok_stabi_start:
			stabi_nervenet_start();
		break;
		case bj_tok_sync_to_parent:
		{
			nervenet* rem_net = (nervenet*)(msv->src);
			mck_token_t rem_ti = rem_net->sync_tier;
			if(rem_ti > sync_tier){
				sync_tier = rem_ti;
				sync_sent_stop_to_parent = false;
				sync_tot_stopping_child = 1;
			}
			if(rem_ti == sync_tier){
				sync_tot_stopping_child++;
			}
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

	dbg_stabi_stop_sys(mc_null, mc_null);
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

	left_side.stabi_active_set.stabi_rec_send_all((bj_callee_t)(&neuron::stabi_send_propag), side_left);
	left_side.stabi_active_set.stabi_rec_send_all((bj_callee_t)(&neuron::stabi_send_tier_end), side_left);

	bj_nervenet->dbg_stabi_stop_sys(mc_null, this);
}

void 
neuron::stabi_send_propag(synapse* snp, net_side_t sd){
	synset& active = get_active_set(sd);
	EMU_CK(active.tot_syn != 0);
	if(active.tot_syn == 1){
		snp->send_transmitter(bj_tok_stabi_charge_all, sd);
	} else {
		snp->send_transmitter(bj_tok_stabi_propag, sd);
	}
}

void 
neuron::stabi_send_tier_end(synapse* snp, net_side_t sd){
	snp->send_transmitter(bj_tok_stabi_tier_end, sd);
}

void
nervenode::stabi_recv_propag(propag_data* dat){

	if(dat->tok != bj_tok_stabi_tier_end){
		neurostate& stt = get_neurostate(dat->sd);
		EMU_CODE(bool ok_1 = ((dat->ti + 1) == stt.stabi_num_tier) || (dat->ti == stt.stabi_num_tier));
		EMU_CK_PRT(ok_1, "%s %s %ld %s (%d > %d)", stabi_tok_to_str(dat->tok),
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), (dat->ti + 1), stt.stabi_num_tier);

		stt.stabi_num_tier = dat->ti + 1;

		EMU_PRT("SET_NUM_TIER %s %s %ld %s TI=%d  \n", stabi_tok_to_str(dat->tok),
			node_kind_to_str(ki), id, net_side_to_str(dat->sd), stt.stabi_num_tier);
	}

	switch(dat->tok){
		case bj_tok_stabi_charge_all:
			stabi_charge_all(dat);
		break;
		case bj_tok_stabi_charge_src:
			stabi_charge_src(dat);
		break;
		case bj_tok_stabi_propag:
			stabi_propag(dat);
		break;
		case bj_tok_stabi_tier_end:
			stabi_tier_end(dat);
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
neurostate::charge_all(){
	stabi_active_set.stabi_rec_reset();

	bool resp = false;
	if(! stabi_active_set.all_syn.is_alone()){
		resp = true;
		tierset* ti_grp = tierset::acquire();
		EMU_CK(ti_grp->ti_all.is_alone());
		ti_grp->ti_id = stabi_num_tier;
		ti_grp->ti_all.move_all_to_my_right(stabi_active_set.all_syn);

		stabi_active_set.tot_syn = 0;
		
		stabi_tiers.bind_to_my_left(*ti_grp);
	}
	EMU_CK(stabi_active_set.is_empty());
	return resp;
}

void
nervenode::stabi_charge_all(propag_data* dat){
	EMU_CK(dat != mc_null);
	EMU_CK(dat->sd != side_invalid);

	neurostate& stt = get_neurostate(dat->sd);

	EMU_PRT("CHARGE_ALL %s %ld %s src=%p\n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), stt.stabi_source);

	if(stt.stabi_source == mc_null){
		nervenode* src = dat->snp->mate->owner;

		stt.stabi_source = src;
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
nervenode::stabi_charge_src(propag_data* dat){
	EMU_CK(dat != mc_null);
	EMU_CK(dat->sd != side_invalid);

	neurostate& stt = get_neurostate(dat->sd);
	num_tier_t chg_tier = dat->ti + 1;
	tierset* ti_grp = mc_null;

	stt.stabi_active_set.stabi_rec_reset();
	mc_set_flag(stt.stabi_flags, bj_stt_charge_src_flag);

	if(! stt.stabi_tiers.is_alone()){
		ti_grp = (tierset*)(binder*)(stt.stabi_tiers.bn_right);
		if(ti_grp->ti_id != chg_tier){
			ti_grp = mc_null;
		}
	}
	if(ti_grp == mc_null){
		ti_grp = tierset::acquire();
		EMU_CK(ti_grp->ti_all.is_alone());
		stt.stabi_tiers.bind_to_my_left(*ti_grp);
	}

	binder& bdr = dat->snp->get_side_binder(dat->sd);
	bdr.let_go();
	ti_grp->ti_all.bind_to_my_left(bdr);

	stt.stabi_active_set.tot_syn--;
}

void
nervenode::stabi_propag(propag_data* dat){
	EMU_PRT("PROPAG %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
	// normal stab
}

void
nervenode::stabi_tier_end(propag_data* dat){

	neurostate& stt = get_neurostate(dat->sd);
	EMU_CK_PRT(((dat->ti + 1) == stt.stabi_num_tier), "%s %ld %s (%d == %d)",
		node_kind_to_str(ki), id, net_side_to_str(dat->sd), (dat->ti + 1), stt.stabi_num_tier);

	stt.stabi_num_complete++;

	EMU_LOG("ADD_TIER_END %s %ld %s (%d==%d)?\n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
			stt.stabi_num_complete, stt.prev_tot_active);

	if(stt.stabi_num_complete == stt.prev_tot_active){
		EMU_LOG("TIER_END %s %ld %s tot=%ld \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
				stt.stabi_num_complete);
		EMU_PRT("TIER_END TI=%d %s %ld %s tot=%ld \n", dat->ti, node_kind_to_str(ki), id, net_side_to_str(dat->sd), 
				stt.stabi_num_complete);
		//bj_nervenet->get_active_netstate(dat->sd).get_tier().inc_rcv(ki);

		bj_nervenet->get_active_netstate(dat->sd).get_tier(dat->ti).inc_rcv(ki);
		bj_nervenet->dbg_stabi_stop_sys(dat, this);
	
		//stabi_end_tier(dat);

		stt.stabi_num_complete = 0;
		stt.stabi_num_still = 0;
		stt.prev_tot_active = stt.stabi_active_set.tot_syn;
	}
}

void 
nervenode::stabi_send_charge_src(synapse* snp, net_side_t sd){
	snp->send_transmitter(bj_tok_stabi_charge_src, sd);
}

void 
nervenode::stabi_send_conflict(synapse* snp, net_side_t sd){
	snp->send_transmitter(bj_tok_stabi_conflict, sd);
}

void 
nervenode::stabi_send_end_forward(synapse* snp, net_side_t sd){
	snp->send_transmitter(bj_tok_stabi_end_forward, sd);
}

void 
polaron::stabi_send_charge_all(synapse* snp, net_side_t sd){
	snp->send_transmitter(bj_tok_stabi_charge_all, sd);
}

void 
polaron::stabi_send_propag(synapse* snp, net_side_t sd){
	snp->send_transmitter(bj_tok_stabi_propag, sd);
}

bool
synset::is_empty(){
	if(tot_syn == 0){
		EMU_CK(all_syn.is_alone());
		EMU_CK(all_grp.is_alone());
		return true;
	}
	EMU_CK(! all_syn.is_alone() || ! all_grp.is_alone());
	return false;
}

void
nervenode::stabi_end_tier(propag_data* dat){
	mck_abort(1, mc_cstr("nervenode::stabi_end_tier"));
}

void
polaron::stabi_end_tier(propag_data* dat){
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);
	bool pol_chg = (pol_stt.stabi_source != mc_null);
	bool opp_chg = (opp_stt.stabi_source != mc_null);

	if(pol_chg && opp_chg){
		EMU_LOG("POL CONFLICT %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
		// conflict. start backpropag.
		bool ok = pol_stt.charge_all();	// set opp too
		if(ok){
			//tierset* ti_grp = (tierset*)pol_stt.stabi_tiers.bn_left;
			//send_all_synapses(&(ti_grp->ti_all), (bj_callee_t)(&nervenode::stabi_send_conflict), dat->sd);
		}
	}
	if(pol_chg){
		pol_stt.charge_all();

		EMU_CK(! pol_stt.stabi_tiers.is_alone());
		EMU_CK(pol_stt.stabi_active_set.is_empty());

		bool ok = opp_stt.charge_all();	// set opp too
		if(ok){
			tierset* opp_ti_grp = (tierset*)opp_stt.stabi_tiers.bn_left;
			send_all_synapses(&(opp_ti_grp->ti_all), (bj_callee_t)(&nervenode::stabi_send_charge_src), dat->sd);
		}

		tierset* ti_grp = (tierset*)pol_stt.stabi_tiers.bn_left;
		send_all_synapses(&(ti_grp->ti_all), (bj_callee_t)(&polaron::stabi_send_charge_all), dat->sd);
	} else {
		if(! opp_chg){
			if(pol_stt.stabi_active_set.is_empty()){
				// mono case
				bool ok = opp_stt.charge_all();
				if(ok){
					tierset* opp_ti_grp = (tierset*)opp_stt.stabi_tiers.bn_left;
					send_all_synapses(&(opp_ti_grp->ti_all), (bj_callee_t)(&polaron::stabi_send_charge_all), 
									dat->sd);
				}
			} else {
				pol_stt.stabi_active_set.stabi_rec_send_all((bj_callee_t)(&polaron::stabi_send_propag), dat->sd);
			}
		}
	}
	pol_stt.stabi_flags = 0;

}

void
neuron::stabi_end_tier(propag_data* dat){
	neurostate& stt = get_neurostate(dat->sd);
	bool chgd_all = (stt.stabi_source != mc_null);
	if(chgd_all){
		EMU_CK(! stt.stabi_tiers.is_alone());
		EMU_CK(stt.stabi_active_set.is_empty());

		tierset* ti_grp = (tierset*)stt.stabi_tiers.bn_left;
		send_all_synapses(&(ti_grp->ti_all), (bj_callee_t)(&nervenode::stabi_send_charge_src), dat->sd);
	} else {
		if(stt.stabi_active_set.is_empty()){
			EMU_LOG("NEU CONFLICT %s %ld %s \n", node_kind_to_str(ki), id, net_side_to_str(dat->sd));
		} else {
			stt.stabi_active_set.stabi_rec_send_all((bj_callee_t)(&neuron::stabi_send_propag), dat->sd);
		}
	}
}

void 
nervenet::dbg_stabi_stop_sys(propag_data* dat, nervenode* nod){
	tierdata& tda = act_left_side.get_tier();
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

	mck_slog2("STABI___\n");

	bj_print_loaded_cnf();

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->stabi_init_sync();

	my_net->send(my_net, bj_tok_stabi_start);
	kernel::run_sys();

	EMU_PRT("...............................END_STABI\n");
	mck_slog2("END_STABI___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");

}

tierdata&
netstate::get_tier(num_tier_t id){
	EMU_CK(! all_tiers.is_alone());

	tierdata* dat = mc_null;
	binder * fst, * lst, * wrk;

	binder* tis = &(all_tiers);
	fst = (binder*)(tis->bn_left);
	lst = tis;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_left)){
		tierdata* tidat = (tierdata*)wrk;
		if(tidat->ti_id == id){
			dat = tidat;
			break;
		}
		if(tidat->ti_id < id){
			break;
		}
	}
	if(dat == mc_null){
		while(get_tier().ti_id < id){
			inc_tier();
		}
		dat = (tierdata*)(all_tiers.bn_left);
	}
	EMU_CK(dat != mc_null);
	EMU_CK_PRT((dat->ti_id == id), "(%d == %d)",  dat->ti_id, id);

	dat->update();
	return *dat;
}

void 
tierdata::update(){
	if(ti_id == 0){
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
	}
}

void
netstate::inc_tier(){
	tierdata& lti = get_tier();

	tierdata* ti_dat = tierdata::acquire();
	ti_dat->ti_id = lti.ti_id + 1;
	all_tiers.bind_to_my_left(*ti_dat);

	ti_dat->update();
}

nervenet*
nervenet::get_nervenet(mc_core_id_t id){
	nervenet* rem_net = (nervenet*)mc_addr_set_id(id, this);
	return rem_net;
}

void 
nervenet::send_sync_to_children(){
	//EMU_PRT("STOP_CHILDREN CORE=%d \n", get_core_nn());

	if(sync_map->childs != mc_null){ 
		int aa = 0;
		mc_load_map_st* ch_map = (sync_map->childs)[aa];
		while(ch_map != mc_null){
			//EMU_PRT("send_stop to CHILD=%d \n", ch_map->num_core);
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

	kernel::stop_sys(bj_tok_stabi_end);
}

void bj_kernel_func(){
	nervenet* my_net = bj_nervenet;
	my_net->handle_sync();
}

void 
nervenet::handle_sync(){
	if(sync_tier == 0){
		return;
	}

	if(! sync_sent_stop_to_parent && (sync_tot_stopping_child == sync_tot_child)){
		EMU_PRT("SENDING STOP TO PARENT CORE=%d TOT_CHLD=%d \n", kernel::get_core_nn(), sync_tot_child);
		sync_sent_stop_to_parent = true;

		if(sync_parent_id != 0){
			nervenet* pnt_net = get_nervenet(sync_parent_id);

			missive* msv = missive::acquire();
			msv->src = this;
			msv->dst = pnt_net;
			msv->tok = bj_tok_sync_to_parent;
			msv->send();
		} else {
			send_sync_to_children();
		}
	}
}
