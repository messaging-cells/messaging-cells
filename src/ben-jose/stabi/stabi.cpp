
#include "cell.hh"

#include "stabi.hh"

synset& 
nervenode::get_charged_set(net_side_t sd){
	EMU_CK(sd != side_invalid);

	synset* out_set = &left_side.stabi_charged_set;
	if(sd == side_right){
		out_set = &right_side.stabi_charged_set;
	}
	EMU_CK(out_set != mc_null);
	return *out_set;
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

void
synapse::send_transmitter(stabi_tok_t tok, net_side_t sd){
	transmitter* trm = transmitter::acquire();
	trm->src = this;
	trm->dst = mate;
	trm->tok = tok;
	trm->wrk_side = sd;
	trm->wrk_tier = owner->get_neurostate(sd).stabi_tier;
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

void bj_stabi_main() {
	//kernel* ker = mck_get_kernel();
	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_stabi_init_handlers();

	//kernel::run_sys();

	mck_slog2("STABI___\n");

	bj_print_loaded_cnf();

	mck_slog2("END_STABI___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");

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
		case tok_stabi_start:
			stabi_neuron_start();
		break;
		default:
			mck_abort(1, const_cast<char*>("BAD_STABI_TOK"));
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

	if(owner->ki == nd_neu){
		neuron* neu = (neuron*)owner;
		neu->stabi_recv_propag(&dat);
	} else {
		EMU_CK(owner->ki != nd_invalid);
		polaron* pol = (polaron*)owner;
		pol->stabi_recv_propag(&dat);
	}
}

void
nervenet::stabi_handler(missive* msv){
	cell* msv_src = msv->src;
	stabi_tok_t tok = (stabi_tok_t)msv->tok;
	MC_MARK_USED(msv_src);
	MC_MARK_USED(tok);

	//nervenet* my_net = bj_nervenet;
	switch(tok){
		case tok_stabi_start:
			stabi_nervenet_start();
		break;
		default:
			mck_abort(1, const_cast<char*>("BAD_STABI_TOK"));
		break;
	}
}

void
nervenet::stabi_nervenet_start(){
	nervenet* my_net = this;

	binder * fst, * lst, * wrk;

	binder* pt_all_neu = &(all_neu);
	fst = (binder*)(pt_all_neu->bn_right);
	lst = pt_all_neu;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		neuron* my_neu = (neuron*)wrk;
		EMU_CK(my_neu->ki == nd_neu);
		my_net->send(my_neu, tok_stabi_start);
	}
}

void
synset::stabi_send_snps(bj_callee_t mth, net_side_t sd){
	EMU_CK(mth != mc_null);
	binder* nn_all_snp = &(all_syn);

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
	stabi_send_snps(mth, sd);

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
	EMU_CK(left_side.stabi_charged_set.all_syn.is_alone());
	EMU_CK(left_side.stabi_charged_set.all_grp.is_alone());
	EMU_CK(left_side.stabi_active_set.all_grp.is_alone());

	EMU_CK(right_side.stabi_charged_set.all_syn.is_alone());
	EMU_CK(right_side.stabi_charged_set.all_grp.is_alone());
	EMU_CK(right_side.stabi_active_set.all_syn.is_alone());
	EMU_CK(right_side.stabi_active_set.all_grp.is_alone());

	left_side.stabi_active_set.stabi_rec_send_all((bj_callee_t)(&neuron::stabi_send_propag), side_left);
	left_side.stabi_active_set.stabi_rec_send_all((bj_callee_t)(&neuron::stabi_send_tier_propag), side_left);
}

void 
neuron::stabi_send_propag(synapse* snp, net_side_t sd){
	synset& active = get_active_set(sd);
	EMU_CK(active.tot_syn != 0);
	if(active.tot_syn == 1){
		snp->send_transmitter(tok_stabi_charge_all, sd);
	} else {
		snp->send_transmitter(tok_stabi_propag, sd);
	}
}

void 
neuron::stabi_send_tier_propag(synapse* snp, net_side_t sd){
	snp->send_transmitter(tok_stabi_tier_propag, sd);
}

void
nervenode::stabi_recv_propag(propag_data* dat){
	//nervenet* my_net = bj_nervenet;
	//neurostate& stt = get_neurostate(sd);
	switch(dat->tok){
		case tok_stabi_charge_all:
			stabi_charge_all(dat);
		break;
		case tok_stabi_propag:
			stabi_propag(dat);
		break;
		case tok_stabi_tier_propag:
			stabi_tier_propag(dat);
		break;
		default:
			mck_abort(1, const_cast<char*>("nervenode::stabi_recv_propag. BAD_STABI_TOK"));
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

void
nervenode::stabi_charge_all(propag_data* dat){
	EMU_CK(dat != mc_null);
	EMU_CK(dat->sd != side_invalid);
	neurostate& stt = get_neurostate(dat->sd);

	if(stt.stabi_source == mc_null){
		neuron* neu = (neuron*)(dat->snp->mate->owner);

		EMU_CK(dat->ti > stt.stabi_tier);
		stt.stabi_tier = dat->ti + 1;
		stt.stabi_source = neu;

		stt.stabi_active_set.stabi_rec_reset();

		synset* sub_grp = synset::acquire();
		EMU_CK(sub_grp->all_syn.is_alone());
		sub_grp->all_syn.move_all_to_my_right(stt.stabi_active_set.all_syn);
		
		stt.stabi_charged_set.all_grp.bind_to_my_left(*sub_grp);
	}
}

void
nervenode::stabi_propag(propag_data* dat){
}

void
nervenode::stabi_tier_propag(propag_data* dat){
}
