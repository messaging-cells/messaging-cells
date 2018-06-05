
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
bj_stabi_reset_all_tiers(grip& dst_grp, grip& src_grp){
	while(! src_grp.is_alone()){
		tierset* tis = (tierset*)(binder*)(src_grp.bn_right);
		dst_grp.move_all_to_my_right(*tis);
		tis->release(111);
	}
}

void
nervenode::mirrow_sides(net_side_t src_sd){
	EMU_LOG("mirrow_nod \n");

	nervenode* nd = this;

	binder * fst, * lst, * wrk, * src;

	net_side_t dst_sd = side_left;
	if(dst_sd == src_sd){ dst_sd = side_right; }

	neurostate& src_st = get_neurostate(src_sd);
	neurostate& dst_st = get_neurostate(dst_sd);

	// mirrow active_sets

	synset& src_set = src_st.step_active_set;
	synset& dst_set = dst_st.step_active_set;

	EMU_CK(src_set.all_grp.is_alone());
	EMU_CK(dst_set.all_grp.is_alone());

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

	bj_stabi_reset_all_tiers(tmp_ti, dst_st.propag_tiers);

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

	// set all vessels

	neurostate& lft_st = left_side;
	lft_st.step_active_set.reset_vessels(true);
	lft_st.calc_stabi_arr(nd, mc_null);
	lft_st.stabi_num_tier = 0;

	EMU_LOG("MIRROW_ID_ARR_%s_%d_%s \n", get_ki_str(), id,
		bj_dbg_stabi_id_arr_to_str(lft_st.stabi_arr_sz, lft_st.stabi_arr, BJ_DBG_STR_CAP, bj_nervenet->dbg_str1));

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
		EMU_DBG_CODE(my_nod->dbg_prt_active_synset(side_left, tiki_stabi, mc_cstr("START"), 0));
	}
}

void 
nervenet::mirrow_nervenet(){
	EMU_LOG("mirrow_nervenet_start \n");

	net_side_t sd = side_left;

	netstate& lst_nst = get_active_netstate(side_left);
	netstate& rgt_nst = get_active_netstate(side_right);
	
	tierdata& lft = get_last_tier(lst_nst.all_propag_tiers);
	tierdata& rgt = get_last_tier(rgt_nst.all_propag_tiers);

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
	mck_set_sub_module_id(BJ_STABI_SUB_MODULE_MIRROW);

	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_mirrow_init_handlers();

	EMU_LOG("MIRROW___ %d \n", nn);

	kernel* ker = mck_get_kernel();
	ker->user_func = mc_null;

	nervenet* my_net = bj_nervenet;
	my_net->init_sync_cycle();

	mck_slog2("__dbg1.mirrow\n");

	my_net->send(my_net, bj_tok_mirrow_start);
	kernel::run_sys();

	my_net->act_left_side.init_stabi_tiers(*my_net);

	bj_print_active_cnf(side_left, tiki_propag, mc_cstr("MIRROWED_"), 5, 0);
	bj_print_active_cnf(side_right, tiki_propag, mc_cstr("MIRROWED_"), 5, 0);

	EMU_PRT("...............................END_MIRROW\n");
	mck_slog2("END_MIRROW___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");
	mck_sprt2("dbg1.mirrow.end\n");

}

void
synset::reset_vessels(bool set_vessel){
	EMU_CK(all_grp.is_alone());

	binder* nn_all_snp = &all_syn;
	binder * fst, * lst, * wrk;

	fst = (binder*)(nn_all_snp->bn_right);
	lst = (binder*)mck_as_loc_pt(nn_all_snp);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synapse* my_snp = get_synapse_from_binder(side_left, wrk);
		synset* val = mc_null;
		if(set_vessel){ val = this; }
		my_snp->stabi_vessel = val;
	}
}

void
netstate::init_stabi_tiers(nervenet& my_net){
	tierdata* ti_dat = tierdata::acquire();
	tierdata& lti_prop = get_last_tier(all_propag_tiers);

	EMU_CK(lti_prop.got_all_neus());
	EMU_CK(lti_prop.all_delayed.is_alone());

	ti_dat->tdt_id = 0;

	EMU_CK(ti_dat->tdt_flags == 0);
	EMU_CK(ti_dat->all_delayed.is_alone());
	EMU_CK(ti_dat->num_inert_chdn == 0);

	ti_dat->inp_neus = lti_prop.inp_neus - lti_prop.off_neus;
	EMU_CK(ti_dat->inp_neus != BJ_INVALID_NUM_NODE);

	EMU_CK(all_stabi_tiers.is_alone());
	all_stabi_tiers.bind_to_my_left(*ti_dat);
}

