
#include "cell.hh"
#include "mirrow.hh"

void 
nervenode_mirrow_handler(missive* msv){
	MCK_CALL_HANDLER(nervenode, mirrow_handler, msv);
}

void 
nervenet_mirrow_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, mirrow_handler, msv);
}


void bj_mirrow_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_polaron] = nervenode_mirrow_handler;
	hndlrs[idx_neuron] = nervenode_mirrow_handler;
	hndlrs[idx_nervenet] = nervenet_mirrow_handler;

	kernel::set_handlers(idx_total, hndlrs);
}

void bj_mirrow_main() {
	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_mirrow_init_handlers();

	EMU_LOG("MIRROW___ %d \n", nn);

	//kernel* ker = mck_get_kernel();
	//ker->user_func = bj_kernel_func;

	//nervenet* my_net = bj_nervenet;
	//my_net->mirrow_init_sync();

	mck_slog2("__dbg1.mirrow\n");

	//my_net->send(my_net, bj_tok_mirrow_start);
	//kernel::run_sys();

	bj_print_active_cnf(side_left, mc_cstr("MIRROWED_"), 5, 0);

	EMU_PRT("...............................END_MIRROW\n");
	mck_slog2("END_MIRROW___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");
	mck_sprt2("dbg1.mirrow.end\n");

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
		stabi_arr_cap = calc_stabi_arr_cap(propag_active_set.tot_syn);
		stabi_arr = mc_malloc32(num_syn_t, stabi_arr_cap);
	}
	stabi_arr_sz = 0;
	propag_active_set.calc_stabi_arr_rec(stabi_arr_cap, stabi_arr, stabi_arr_sz);
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
*/

void
neurostate::reset_all_tiers(grip& tmp_ti){
	while(! propag_tiers.is_alone()){
		tierset* tis = (tierset*)(binder*)(propag_tiers.bn_right);
		tmp_ti.move_all_to_my_right(*tis);
		tis->release(111);
	}
}

void
nervenode::mirrow_sides(net_side_t src_sd){
	binder * fst, * lst, * wrk, * src;

	net_side_t dst_sd = side_left;
	if(dst_sd == src_sd){ dst_sd = side_right; }

	neurostate& src_st = get_neurostate(src_sd);
	neurostate& dst_st = get_neurostate(dst_sd);

	// mirrow active_sets

	synset& src_set = src_st.propag_active_set;
	synset& dst_set = dst_st.propag_active_set;

	src_set.propag_rec_reset();
	dst_set.propag_rec_reset();

	src = &(src_set.all_syn);

	fst = (binder*)(src->bn_right);
	lst = (binder*)mck_as_loc_pt(src);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synapse* snp = get_synapse_from_binder(src_sd, wrk);

		if(src_sd == side_left){
			snp->right_handle.let_go();
			dst_set.add_right_synapse(snp);
		} else {
			EMU_CK(src_sd == side_right);
			snp->let_go();
			dst_set.add_left_synapse(snp);
		}
	}

	// mirrow ti and src

	dst_st.propag_num_tier = src_st.propag_num_tier;
	dst_st.propag_source = src_st.propag_source;

	// mirrow tiers

	grip tmp_ti;

	dst_st.reset_all_tiers(tmp_ti);

	src = &(src_st.propag_tiers);

	fst = (binder*)(src->bn_right);
	lst = (binder*)mck_as_loc_pt(src);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		tierset* src_tis = (tierset*)wrk;
		tierset* dst_tis = tierset::acquire();
		
		dst_tis->ti_id = src_tis->ti_id;
		dst_st.propag_tiers.bind_to_my_left(*dst_tis);
		
		dst_tis->mirrow_tiset(*src_tis, src_sd);
	}

	// mirrow others

	dst_st.prev_tot_active = src_st.prev_tot_active;

	dst_st.propag_flags = src_st.propag_flags;
	dst_st.propag_num_complete = src_st.propag_num_complete;
	dst_st.propag_num_ping = src_st.propag_num_ping;

	dst_st.stabi_arr_sz = 0;

}

void
tierset::mirrow_tiset(tierset& src_tis, net_side_t src_sd){
	binder * fst, * lst, * wrk;

	binder* snps = &(src_tis.ti_all);

	fst = (binder*)(snps->bn_right);
	lst = (binder*)mck_as_loc_pt(snps);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synapse* snp = get_synapse_from_binder(src_sd, wrk);
		MC_MARK_USED(snp);

		if(src_sd == side_left){
			snp->right_handle.let_go();
			bind_to_my_left(snp->right_handle);
		} else {
			EMU_CK(src_sd == side_right);
			snp->let_go();
			bind_to_my_left(*snp);
		}
	}
}

void
nervenet::mirrow_start_all_nods(grip& all_nod, net_side_t sd){
	nervenet* my_net = this;

	binder * fst, * lst, * wrk;

	binder* pt_all_nod = &(all_nod);
	fst = (binder*)(pt_all_nod->bn_right);
	lst = (binder*)mck_as_loc_pt(pt_all_nod);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		nervenode* my_nod = (nervenode*)wrk;

		transmitter* trm = transmitter::acquire();
		trm->src = my_net;
		trm->dst = my_nod;
		trm->tok = bj_tok_mirrow_start;
		trm->wrk_side = sd;
		trm->wrk_tier = BJ_INVALID_NUM_TIER;
		trm->send();
	}
}

void 
nervenet::mirrow_nervenet_start(){
	EMU_LOG("propag_nervenet_start \n");

	net_side_t sd = side_left;

	mirrow_start_all_nods(all_neu, sd);
	mirrow_start_all_nods(all_pos, sd);
	mirrow_start_all_nods(all_neg, sd);

	EMU_LOG("end_mirrow_nervenet_start \n");
}

void
nervenode::mirrow_handler(missive* msv){
	mirrow_tok_t tok = (mirrow_tok_t)msv->tok;
	net_side_t sd = ((transmitter*)msv)->wrk_side;

	switch(tok){
		case bj_tok_mirrow_start:
			mirrow_sides(sd);
		break;
		default:
			mck_abort(1, mc_cstr("BAD_MIRROW_TOK"));
		break;
	}
}

void
nervenet::mirrow_handler(missive* msv){
	mirrow_tok_t tok = (mirrow_tok_t)msv->tok;

	switch(tok){
		case bj_tok_mirrow_start:
			mirrow_nervenet_start();
		break;
		default:
			mck_abort(1, mc_cstr("BAD_MIRROW_TOK"));
		break;
	}
}

