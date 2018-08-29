
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

void bj_load_shd_sornet(){
	nervenet* my_net = bj_nervenet;
	pre_cnf_net* nn_cnf = bj_nervenet->shd_cnf;

	num_nod_t tot_sclls = nn_cnf->tot_pre_sornods;

	my_net->tot_sorcells = tot_sclls;

	sorcell::separate(tot_sclls);

	PTD_LOG("Separated_sorcells for SORNET %ld\n", tot_sclls);

	binder * fst, * lst, * wrk;

	binder* nn_all_nods = &(nn_cnf->all_pre_sornods); // nn_cnf is already workeru_pt so nn_all_nods is workeru_pt
	fst = (binder*)mc_manageru_pt_to_workeru_pt(nn_all_nods->bn_right);
	lst = nn_all_nods;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_manageru_pt_to_workeru_pt(wrk->bn_right)){
		pre_sornode* nod = (pre_sornode*)wrk;

		sorcell* scll = sorcell::acquire();

		scll->dbg_level = nod->level;

		scll->srt_sz = nod->srt_sz;
		
		PTD_CK(scll->up_inp == mc_null);
		scll->up_idx = nod->up_idx;
		if(nod->out_up != mc_null){
			scll->up_inp = (void*)mc_manageru_pt_to_workeru_pt(nod->out_up);	// up_inp used as tmp
		}

		PTD_CK(scll->down_inp == mc_null);
		scll->down_idx = nod->down_idx;
		if(nod->out_down != mc_null){
			scll->down_inp = (void*)mc_manageru_pt_to_workeru_pt(nod->out_down);	// down_inp used as tmp
		}

		my_net->all_sorcells.bind_to_my_left(*scll);

		PTD_CK(nod->loaded == mc_null);
		nod->loaded = mck_as_glb_pt(scll);
	}

	binder* nn_all_sclls = &(my_net->all_sorcells); // nn_cnf is already workeru_pt so nn_all_sclls is workeru_pt
	fst = (binder*)(nn_all_sclls->bn_right);
	lst = nn_all_sclls;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		sorcell* scll = (sorcell*)wrk;

		bj_wait_set_pt(pre_sornode, scll->up_inp, sorcell, scll->up_out, true);
		bj_wait_set_pt(pre_sornode, scll->down_inp, sorcell, scll->down_out, true);

		PTD_CK(scll->up_inp == mc_null);
		PTD_CK(scll->down_inp == mc_null);
	};

	kernel* ker = mck_get_kernel();
	mc_workeru_nn_t nn = kernel::get_workeru_nn();

	if(nn == 0){
		pre_load_cnf* pre_cnf = (pre_load_cnf*)(ker->manageru_load_data);
		pre_sornode** all_input = 
			(pre_sornode**)mc_manageru_addr_to_workeru_addr((mc_addr_t)(pre_cnf->all_pre_sorinput_nod));

		num_nod_t tot_sorinp = pre_cnf->tot_pre_sorinput_nod;
		//PTD_LOG("TOT_INPUT_SORCELLS=%ld \n", tot_sorinp);
		mck_slog2("TOT_INPUT_SORCELLS=");
		mck_ilog(tot_sorinp);	
		mck_slog2("\n");

		my_net->tot_input_sorcells = tot_sorinp;
		my_net->all_input_sorcells = mc_malloc32(sorcell*, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_input_sorcells, mc_null);
		my_net->all_input_srt_min_grps = mc_malloc32(num_nod_t, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_input_srt_min_grps, BJ_INVALID_SORCELL_NUM_GRP);
		my_net->all_input_srt_max_grps = mc_malloc32(num_nod_t, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_input_srt_max_grps, BJ_INVALID_SORCELL_NUM_GRP);

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

	num_nod_t tot_sclls = nn_cnf->tot_pre_rnknods;

	my_net->tot_rnkcells = tot_sclls;

	sorcell::separate(tot_sclls);

	PTD_LOG("Separated_sorcells for RNKNET %ld\n", tot_sclls);

	binder * fst, * lst, * wrk;

	binder* nn_all_nods = &(nn_cnf->all_pre_rnknods); // nn_cnf is already workeru_pt so nn_all_nods is workeru_pt
	fst = (binder*)mc_manageru_pt_to_workeru_pt(nn_all_nods->bn_right);
	lst = nn_all_nods;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_manageru_pt_to_workeru_pt(wrk->bn_right)){
		pre_sornode* nod = (pre_sornode*)wrk;

		sorcell* scll = sorcell::acquire();

		scll->dbg_level = nod->level;

		scll->srt_sz = nod->srt_sz;
		
		PTD_CK(scll->up_inp == mc_null);
		scll->up_idx = nod->up_idx;
		if(nod->out_up != mc_null){
			scll->up_inp = (void*)mc_manageru_pt_to_workeru_pt(nod->out_up);	// up_inp used as tmp
		}

		PTD_CK(scll->down_inp == mc_null);
		scll->down_idx = nod->down_idx;
		if(nod->out_down != mc_null){
			scll->down_inp = (void*)mc_manageru_pt_to_workeru_pt(nod->out_down);	// down_inp used as tmp
		}

		my_net->all_rnkcells.bind_to_my_left(*scll);

		PTD_CK(nod->loaded == mc_null);
		nod->loaded = mck_as_glb_pt(scll);
	}

	binder* nn_all_sclls = &(my_net->all_rnkcells); // nn_cnf is already workeru_pt so nn_all_sclls is workeru_pt
	fst = (binder*)(nn_all_sclls->bn_right);
	lst = nn_all_sclls;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		sorcell* scll = (sorcell*)wrk;

		bj_wait_set_pt(pre_sornode, scll->up_inp, sorcell, scll->up_out, true);
		bj_wait_set_pt(pre_sornode, scll->down_inp, sorcell, scll->down_out, true);

		PTD_CK(scll->up_inp == mc_null);
		PTD_CK(scll->down_inp == mc_null);
	};

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
		mc_init_arr_vals(tot_rnkinp, my_net->all_input_rnkgrps, BJ_INVALID_SORCELL_NUM_GRP);
		my_net->all_output_rnk_min_grps = mc_malloc32(num_nod_t, tot_rnkinp);
		mc_init_arr_vals(tot_rnkinp, my_net->all_output_rnk_min_grps, BJ_INVALID_SORCELL_NUM_GRP);
		my_net->all_output_rnk_max_grps = mc_malloc32(num_nod_t, tot_rnkinp);
		mc_init_arr_vals(tot_rnkinp, my_net->all_output_rnk_max_grps, BJ_INVALID_SORCELL_NUM_GRP);
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

