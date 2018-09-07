
#include "cell.hh"

#include "load_cnf.hh"
#include "preload.hh"

#define bj_get_loaded_of_pt(pt_cls, pt) (((pt_cls*)(pt))->loaded)

#define bj_wait_set_pt(nod_cls, nod, out_cls, out, reset) \
	if(nod != mc_null){ \
		while(bj_get_loaded_of_pt(nod_cls, nod) == mc_null){ \
			/* SPIN UNTIL SET (may be set by an other workeru) */ \
			PTD_CODE(sched_yield()); \
		} \
		PTD_CK(bj_get_loaded_of_pt(nod_cls, nod) != mc_null); \
		out = (out_cls*)bj_get_loaded_of_pt(nod_cls, nod); \
		if(reset){ nod = mc_null; } \
	} \

// end_macro

void
sorcell::sornet_dbg_prt(){
	bool up_end = mc_get_flag(edge_flags, bj_rnk_up_end_flag);
	MC_MARK_USED(up_end);
	bool down_end = mc_get_flag(edge_flags, bj_rnk_down_end_flag);
	MC_MARK_USED(down_end);
	PTD_PRINTF("lding_scll %ld[%ld %ld] f(%d,%d) \n", 
			   srt_sz, up_snp.idx, down_snp.idx, up_end, down_end);
}

void
sorcell::load_from(pre_sornode* nod){
	sorcell* scll = this;
	srt_sz = nod->srt_sz;
	
	edge_flags = nod->edge_flags;
	
	PTD_CK(up_snp.inp == mc_null);
	up_snp.idx = nod->up_pns.idx;
	if(nod->up_pns.out != mc_null){
		up_snp.inp = (void*)mc_manageru_pt_to_workeru_pt(nod->up_pns.out); // up_inp used as tmp
	}

	PTD_CK(down_snp.inp == mc_null);
	down_snp.idx = nod->down_pns.idx;
	if(nod->down_pns.out != mc_null){
		down_snp.inp = (void*)mc_manageru_pt_to_workeru_pt(nod->down_pns.out); // down_inp used as tmp
	}
	
	void* pt_up_axon = (void*)mc_manageru_pt_to_workeru_pt(nod->up_pns.axon);
	bj_wait_set_pt(pre_endnode, pt_up_axon, endcell, up_snp.axon, false);
	void* pt_down_axon = (void*)mc_manageru_pt_to_workeru_pt(nod->down_pns.axon);
	bj_wait_set_pt(pre_endnode, pt_down_axon, endcell, down_snp.axon, false);

	PTD_CK(nod->loaded == mc_null);
	nod->loaded = mck_as_glb_pt(scll);
}

void bj_load_shd_nods(num_nod_t tot_nods, binder* nn_all_endnods, binder* nn_all_ecells, 
					  binder* nn_all_nods, binder* nn_all_sclls)
{
	sorcell::separate(tot_nods);

	PTD_LOG("Separated_sorcells for NET %ld\n", tot_nods);

	binder * fst, * lst, * wrk;
	
	fst = (binder*)mc_manageru_pt_to_workeru_pt(nn_all_endnods->bn_right);
	lst = nn_all_endnods;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_manageru_pt_to_workeru_pt(wrk->bn_right)){
		pre_endnode* end_nd = (pre_endnode*)wrk;
		endcell* ecll = endcell::acquire();
		
		PTD_CK(end_nd->loaded == mc_null);
		end_nd->loaded = mck_as_glb_pt(ecll);
		
		nn_all_ecells->bind_to_my_left(*ecll);
	}

	fst = (binder*)mc_manageru_pt_to_workeru_pt(nn_all_nods->bn_right);
	lst = nn_all_nods;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_manageru_pt_to_workeru_pt(wrk->bn_right)){
		pre_sornode* nod = (pre_sornode*)wrk;
		sorcell* scll = sorcell::acquire();
		
		scll->load_from(nod);
		nn_all_sclls->bind_to_my_left(*scll);
	}

	fst = (binder*)(nn_all_sclls->bn_right);
	lst = nn_all_sclls;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		sorcell* scll = (sorcell*)wrk;

		bj_wait_set_pt(pre_sornode, scll->up_snp.inp, sorcell, scll->up_snp.out, true);
		bj_wait_set_pt(pre_sornode, scll->down_snp.inp, sorcell, scll->down_snp.out, true);

		PTD_CK(scll->up_snp.inp == mc_null);
		PTD_CK(scll->down_snp.inp == mc_null);
	};
}

void bj_load_shd_sornet(){
	nervenet* my_net = bj_nervenet;
	pre_cnf_net* nn_cnf = bj_nervenet->shd_cnf;

	binder* nn_all_endnods = &(nn_cnf->all_pre_srt_endnods); // nn_cnf is already workeru_pt 
	binder* nn_all_eclls = &(my_net->all_endcells); // nn_cnf is already workeru_pt 
	binder* nn_all_nods = &(nn_cnf->all_pre_sornods); // nn_cnf is already workeru_pt 
	binder* nn_all_sclls = &(my_net->all_sorcells); // nn_cnf is already workeru_pt 
	bj_load_shd_nods(nn_cnf->tot_pre_sornods, nn_all_endnods, nn_all_eclls, nn_all_nods, nn_all_sclls);
	
	kernel* ker = mck_get_kernel();
	mc_workeru_nn_t nn = kernel::get_workeru_nn();

	if(nn == 0){
		pre_load_cnf* pre_cnf = (pre_load_cnf*)(ker->manageru_load_data);
		pre_sornode** all_input = 
			(pre_sornode**)mc_manageru_addr_to_workeru_addr((mc_addr_t)(pre_cnf->all_pre_sorinput_nod));

		num_nod_t tot_sorinp = pre_cnf->tot_pre_sorinput_nod;
		mck_slog2("TOT_INPUT_SORCELLS=");
		mck_ilog(tot_sorinp);	
		mck_slog2("\n");

		my_net->tot_input_sorcells = tot_sorinp;
		my_net->all_input_sorcells = mc_malloc32(sorcell*, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_input_sorcells, mc_null);
		my_net->all_input_srt_min_grps = mc_malloc32(num_nod_t, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_input_srt_min_grps, BJ_INVALID_SRT_GRP);
		my_net->all_input_srt_max_grps = mc_malloc32(num_nod_t, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_input_srt_max_grps, BJ_INVALID_SRT_GRP);

		my_net->all_output_sorobjs = mc_malloc32(void*, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_output_sorobjs, mc_null);
		my_net->all_output_sorcols = mc_malloc32(num_nod_t, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_output_sorcols, 0);

		sorcell** all_sorcell = my_net->all_input_sorcells;
		
		num_nod_t aa;
		for(aa = 0; aa < tot_sorinp; aa++){
			sorcell* inp_aa = (sorcell*)mc_manageru_addr_to_workeru_addr((mc_addr_t)(all_input[aa]));
			bj_wait_set_pt(pre_sornode, inp_aa, sorcell, all_sorcell[aa], false);
		}
	}

	//mck_slog2("end_of_bj_load_shd_sornet  \n");	
}

void bj_load_shd_ranknet(){
	nervenet* my_net = bj_nervenet;
	pre_cnf_net* nn_cnf = bj_nervenet->shd_cnf;

	binder* nn_all_endnods = &(nn_cnf->all_pre_rnk_endnods); // nn_cnf is already workeru_pt 
	binder* nn_all_eclls = &(my_net->all_endcells); // nn_cnf is already workeru_pt 
	binder* nn_all_nods = &(nn_cnf->all_pre_rnknods); // nn_cnf is already workeru_pt
	binder* nn_all_sclls = &(my_net->all_rnkcells); // nn_cnf is already workeru_pt
	bj_load_shd_nods(nn_cnf->tot_pre_rnknods, nn_all_endnods, nn_all_eclls, nn_all_nods, nn_all_sclls);

	kernel* ker = mck_get_kernel();
	mc_workeru_nn_t nn = kernel::get_workeru_nn();

	if(nn == 0){
		pre_load_cnf* pre_cnf = (pre_load_cnf*)(ker->manageru_load_data);
		pre_sornode** all_input = 
			(pre_sornode**)mc_manageru_addr_to_workeru_addr((mc_addr_t)(pre_cnf->all_pre_rank_in_nod));

		num_nod_t tot_rnkinp = pre_cnf->tot_pre_rank_in_nod;
		mck_slog2("TOT_INPUT_RNKCELLS=");
		mck_ilog(tot_rnkinp);	
		mck_slog2("\n");

		my_net->tot_input_rnkcells = tot_rnkinp;
		my_net->all_input_rnkcells = mc_malloc32(sorcell*, tot_rnkinp);
		mc_init_arr_vals(tot_rnkinp, my_net->all_input_rnkcells, mc_null);

		my_net->all_input_rnkgrps = mc_malloc32(num_nod_t, tot_rnkinp);
		mc_init_arr_vals(tot_rnkinp, my_net->all_input_rnkgrps, BJ_INVALID_SRT_GRP);
		my_net->all_input_rnk_min_grps = mc_malloc32(num_nod_t, tot_rnkinp);
		mc_init_arr_vals(tot_rnkinp, my_net->all_input_rnk_min_grps, BJ_INVALID_SRT_GRP);
		my_net->all_input_rnk_max_grps = mc_malloc32(num_nod_t, tot_rnkinp);
		mc_init_arr_vals(tot_rnkinp, my_net->all_input_rnk_max_grps, BJ_INVALID_SRT_GRP);
		my_net->all_output_rnk_min_cols = mc_malloc32(num_nod_t, tot_rnkinp);
		mc_init_arr_vals(tot_rnkinp, my_net->all_output_rnk_min_cols, BJ_INVALID_SRT_GRP);
		my_net->all_output_rnk_max_cols = mc_malloc32(num_nod_t, tot_rnkinp);
		mc_init_arr_vals(tot_rnkinp, my_net->all_output_rnk_max_cols, BJ_INVALID_SRT_GRP);
		my_net->dbg_is_input_rnkgrps = mc_malloc32(bool, tot_rnkinp);
		mc_init_arr_vals(tot_rnkinp, my_net->dbg_is_input_rnkgrps, false);

		sorcell** all_rnkcell = my_net->all_input_rnkcells;
		
		num_nod_t aa;
		for(aa = 0; aa < tot_rnkinp; aa++){
			sorcell* inp_aa = (sorcell*)mc_manageru_addr_to_workeru_addr((mc_addr_t)(all_input[aa]));
			bj_wait_set_pt(pre_sornode, inp_aa, sorcell, all_rnkcell[aa], false);
		}
	}

	//mck_slog2("end_of_bj_load_shd_sornet  \n");	
}

