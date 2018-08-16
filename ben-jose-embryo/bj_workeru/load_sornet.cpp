
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

	PTD_LOG("Separated_sorcells %ld\n", tot_sclls);

	binder * fst, * lst, * wrk;

	binder* nn_all_nods = &(nn_cnf->all_pre_sornods); // nn_cnf is already workeru_pt so nn_all_nods is workeru_pt
	fst = (binder*)mc_manageru_pt_to_workeru_pt(nn_all_nods->bn_right);
	lst = nn_all_nods;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_manageru_pt_to_workeru_pt(wrk->bn_right)){
		pre_sornode* nod = (pre_sornode*)wrk;

		sorcell* scll = sorcell::acquire();

		scll->dbg_level = nod->level;

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

		my_net->all_output_sorobjs = mc_malloc32(void*, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_output_sorobjs, mc_null);
		my_net->all_output_sorgrps = mc_malloc32(num_nod_t, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_output_sorgrps, 0);

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
	kernel* ker = mck_get_kernel();
	nervenet* my_net = bj_nervenet;
	pre_cnf_net* nn_cnf = bj_nervenet->shd_cnf;
	pre_load_cnf* pre_cnf = (pre_load_cnf*)(ker->manageru_load_data);

	num_nod_t tot_loc_outs = nn_cnf->tot_pre_sorouts;
	num_nod_t tot_glb_outs = pre_cnf->tot_pre_soroutput_nod;

	my_net->tot_sorouts = tot_loc_outs;

	sorout::separate(tot_loc_outs);

	PTD_LOG("Separated_sorouts %ld\n", tot_loc_outs);

	binder * fst, * lst, * wrk;

	binder* nn_all_outs = &(nn_cnf->all_pre_sorouts); // nn_cnf is already workeru_pt so nn_all_outs is workeru_pt
	fst = (binder*)mc_manageru_pt_to_workeru_pt(nn_all_outs->bn_right);
	lst = nn_all_outs;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_manageru_pt_to_workeru_pt(wrk->bn_right)){
		pre_sorout* nod = (pre_sorout*)wrk;

		sorout* srout = sorout::acquire();

		PTD_CK(srout->obj == mc_null);
		srout->idx = nod->idx;
		if(tot_glb_outs == (srout->idx + 1)){
			PTD_LOG("LAST_IS %ld %ld\n", srout->idx, tot_glb_outs);
			mc_set_flag(srout->jump_flags, bj_sorout_is_last_flag);
		}
		if(nod->prv != mc_null){
			srout->obj = (void*)mc_manageru_pt_to_workeru_pt(nod->prv);	// obj used as tmp
		}

		my_net->all_sorouts.bind_to_my_left(*srout);

		PTD_CK(nod->loaded == mc_null);
		nod->loaded = mck_as_glb_pt(srout);
	}

	binder* nn_all_srouts = &(my_net->all_sorouts); 
	fst = (binder*)(nn_all_srouts->bn_right);
	lst = nn_all_srouts;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		sorout* srout = (sorout*)wrk;

		bj_wait_set_pt(pre_sorout, srout->obj, sorout, srout->prv, true);
		PTD_CK(srout->obj == mc_null);
	};

	mc_workeru_nn_t nn = kernel::get_workeru_nn();

	if(nn == 0){
		pre_sorout** all_outs = 
			(pre_sorout**)mc_manageru_addr_to_workeru_addr((mc_addr_t)(pre_cnf->all_pre_soroutput_nod));

		//PTD_LOG("TOT_ARR_SOROUTS=%ld \n", tot_glb_outs);
		mck_slog2("TOT_ARR_SOROUTS=");
		mck_ilog(tot_glb_outs);	
		mck_slog2("\n");

		my_net->tot_arr_sorouts = tot_glb_outs;
		my_net->arr_sorouts = mc_malloc32(sorout*, tot_glb_outs);
		mc_init_arr_vals(tot_glb_outs, my_net->arr_sorouts, mc_null);

		sorout** arr_sorouts = my_net->arr_sorouts;
		
		num_nod_t aa;
		for(aa = 0; aa < tot_glb_outs; aa++){
			sorout* out_aa = (sorout*)mc_manageru_addr_to_workeru_addr((mc_addr_t)(all_outs[aa]));
			bj_wait_set_pt(pre_sorout, out_aa, sorout, arr_sorouts[aa], false);
		}
	}

	//mck_slog2("end_of_bj_load_shd_sornet  \n");
}

