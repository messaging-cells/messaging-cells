
#include "cell.hh"
#include "stabi.hh"

void 
nervenet_mirrow_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, mirrow_handler, msv);
}


void bj_mirrow_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_nervenet] = nervenet_mirrow_handler;

	kernel::set_handlers(idx_total, hndlrs);
}

void
nervenet::mirrow_handler(missive* msv){
	EMU_CK(((mirrow_tok_t)msv->tok) == bj_tok_mirrow_start);

	mirrow_nervenet();
	kernel::stop_sys(bj_tok_mirrow_end);
}

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
	EMU_LOG("mirrow_nod \n");

	binder * fst, * lst, * wrk, * src;

	net_side_t dst_sd = side_left;
	if(dst_sd == src_sd){ dst_sd = side_right; }

	neurostate& src_st = get_neurostate(src_sd);
	neurostate& dst_st = get_neurostate(dst_sd);

	// mirrow active_sets

	synset& src_set = src_st.step_active_set;
	synset& dst_set = dst_st.step_active_set;

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

	EMU_LOG("mirrow_nod_act \n");

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

	EMU_CK(tmp_ti.is_alone());

	EMU_LOG("mirrow_nod_tis \n");

	// mirrow others

	dst_st.step_prev_tot_active = src_st.step_prev_tot_active;

	dst_st.step_flags = src_st.step_flags;
	dst_st.step_num_complete = src_st.step_num_complete;
	dst_st.step_num_ping = src_st.step_num_ping;

	dst_st.stabi_arr_sz = 0;

	EMU_LOG("mirrow_nod_end \n");
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
			ti_all.bind_to_my_left(snp->right_handle);
		} else {
			EMU_CK(src_sd == side_right);
			snp->let_go();
			ti_all.bind_to_my_left(*snp);
		}
	}

	ti_id = src_tis.ti_id;
}

void
nervenet::mirrow_start_all_nods(grip& all_nod, net_side_t sd){
	binder * fst, * lst, * wrk;

	binder* pt_all_nod = &(all_nod);
	fst = (binder*)(pt_all_nod->bn_right);
	lst = (binder*)mck_as_loc_pt(pt_all_nod);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		nervenode* my_nod = (nervenode*)wrk;
		my_nod->mirrow_sides(sd);
	}
}

void 
nervenet::mirrow_nervenet(){
	EMU_LOG("mirrow_nervenet_start \n");

	net_side_t sd = side_left;

	netstate& lst_nst = get_active_netstate(side_left);
	netstate& rgt_nst = get_active_netstate(side_right);
	
	tierdata& lft = lst_nst.get_last_tier();
	tierdata& rgt = rgt_nst.get_last_tier();

	if(rgt.tdt_id > lft.tdt_id){
		sd = side_right;
	}

	EMU_LOG("mirrow_nervenet_nods %s \n", net_side_to_str(sd));

	mirrow_start_all_nods(all_neu, sd);
	mirrow_start_all_nods(all_pos, sd);
	mirrow_start_all_nods(all_neg, sd);

	EMU_LOG("end_mirrow_nervenet \n");
}

void bj_mirrow_main() {
	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_mirrow_init_handlers();

	EMU_LOG("MIRROW___ %d \n", nn);

	kernel* ker = mck_get_kernel();
	ker->user_func = mc_null;

	nervenet* my_net = bj_nervenet;
	my_net->propag_init_sync();

	mck_slog2("__dbg1.mirrow\n");

	my_net->send(my_net, bj_tok_mirrow_start);
	kernel::run_sys();

	bj_print_active_cnf(side_left, mc_cstr("MIRROWED_"), 5, 0);
	bj_print_active_cnf(side_right, mc_cstr("MIRROWED_"), 5, 0);

	EMU_PRT("...............................END_MIRROW\n");
	mck_slog2("END_MIRROW___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");
	mck_sprt2("dbg1.mirrow.end\n");

}

void bj_stabi_main() {
	bj_mirrow_main();
}
