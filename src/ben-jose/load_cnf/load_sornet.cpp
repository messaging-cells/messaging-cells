
#include "cell.hh"

#include "load_cnf.hh"
#include "preload.hh"

#define bj_get_loaded_of_sornode(pt) (((pre_sornode*)(pt))->loaded)

#define bj_set_sorcell_pt(nod, out, reset) \
	if(nod != mc_null){ \
		while(bj_get_loaded_of_sornode(nod) == mc_null){ \
			/* SPIN UNTIL SET (may be set by an other core) */ \
			EMU_CODE(sched_yield()); \
		} \
		EMU_CK(bj_get_loaded_of_sornode(nod) != mc_null); \
		out = (sorcell*)bj_get_loaded_of_sornode(nod); \
		if(reset){ nod = mc_null; } \
	} \

// end_macro

void bj_load_shd_sornet(){
	nervenet* my_net = bj_nervenet;
	pre_cnf_net* nn_cnf = bj_nervenet->shd_cnf;

	num_nod_t tot_sclls = nn_cnf->tot_pre_sornods;

	my_net->tot_sorcells = tot_sclls;

	sorcell::separate(tot_sclls);

	EMU_LOG("Separated_sorcells %ld\n", tot_sclls);

	//num_nod_t tot_pre_sornods;
	//grip	all_pre_sornods;

	binder * fst, * lst, * wrk;

	binder* nn_all_nods = &(nn_cnf->all_pre_sornods); // nn_cnf is already core_pt so nn_all_nods is core_pt
	fst = (binder*)mc_host_pt_to_core_pt(nn_all_nods->bn_right);
	lst = nn_all_nods;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_host_pt_to_core_pt(wrk->bn_right)){
		pre_sornode* nod = (pre_sornode*)wrk;

		sorcell* scll = sorcell::acquire();

		scll->dbg_level = nod->level;

		EMU_CK(scll->up_inp == mc_null);
		scll->up_idx = nod->up_idx;
		if(nod->out_up != mc_null){
			scll->up_inp = (void*)mc_host_pt_to_core_pt(nod->out_up);	// up_inp used as tmp
		}

		EMU_CK(scll->down_inp == mc_null);
		scll->down_idx = nod->down_idx;
		if(nod->out_down != mc_null){
			scll->down_inp = (void*)mc_host_pt_to_core_pt(nod->out_down);	// down_inp used as tmp
		}

		my_net->all_sorcells.bind_to_my_left(*scll);

		EMU_CK(nod->loaded == mc_null);
		nod->loaded = mck_as_glb_pt(scll);
	}

	binder* nn_all_sclls = &(my_net->all_sorcells); // nn_cnf is already core_pt so nn_all_sclls is core_pt
	fst = (binder*)(nn_all_sclls->bn_right);
	lst = nn_all_sclls;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		sorcell* scll = (sorcell*)wrk;

		bj_set_sorcell_pt(scll->up_inp, scll->up_out, true);
		bj_set_sorcell_pt(scll->down_inp, scll->down_out, true);

		EMU_CK(scll->up_inp == mc_null);
		EMU_CK(scll->down_inp == mc_null);
	};

	kernel* ker = mck_get_kernel();
	mc_core_nn_t nn = kernel::get_core_nn();

	if(nn == 0){
		pre_load_cnf* pre_cnf = (pre_load_cnf*)(ker->host_load_data);
		pre_sornode** all_input = 
			(pre_sornode**)mc_host_addr_to_core_addr((mc_addr_t)(pre_cnf->all_pre_sorinput_nod));

		num_nod_t tot_sorinp = pre_cnf->tot_pre_sorinput_nod;
		//EMU_LOG("TOT_INPUT_SORCELLS=%ld \n", tot_sorinp);
		mck_slog2("TOT_INPUT_SORCELLS=");
		mck_ilog(tot_sorinp);	
		mck_slog2("\n");

		my_net->tot_input_sorcells = tot_sorinp;
		my_net->all_input_sorcells = mc_malloc32(sorcell*, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_input_sorcells, mc_null);

		my_net->all_output_sorobjs = mc_malloc32(void*, tot_sorinp);
		mc_init_arr_vals(tot_sorinp, my_net->all_output_sorobjs, mc_null);

		sorcell** all_sorcell = my_net->all_input_sorcells;
		
		num_nod_t aa;
		for(aa = 0; aa < tot_sorinp; aa++){
			sorcell* inp_aa = (sorcell*)mc_host_addr_to_core_addr((mc_addr_t)(all_input[aa]));
			bj_set_sorcell_pt(inp_aa, all_sorcell[aa], false);
		}
	}

	//mck_slog2("end_of_bj_load_shd_sornet  \n");	
}

