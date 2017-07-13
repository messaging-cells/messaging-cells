
#include "cell.hh"

#include "preload_cnf.hh"


MCK_DEFINE_ACQUIRE_ALLOC(nervenet, 32);	// defines nervenet::acquire_alloc

MCK_DEFINE_MEM_METHODS(neupole, 32, bj_ava_neupoles)
MCK_DEFINE_MEM_METHODS(neuron, 32, bj_ava_neurons)

BJ_DEFINE_LOAD_CNF_FUNCS();

void bj_load_main() {
	//kernel* ker = kernel::get_sys();
	kernel* ker = mck_get_kernel();
	mc_core_nn_t nn = kernel::get_core_nn();

	//EMU_PRT("bj_load_main 1 \n");

	mck_slog2("LOAD_CNF\n");
	if(ker->magic_id != MC_MAGIC_ID){
		mck_slog2("BAD_MAGIC\n");
	}
	
	nervenet* my_net = nervenet::acquire_alloc();
	if(my_net == mc_null){
		mck_abort(1, mc_cstr("CAN NOT INIT GLB CORE DATA"));
	}
	ker->user_data = my_net;

	pre_load_cnf* pre_cnf = (pre_load_cnf*)(ker->host_load_data);

	nervenet* nn_cnf = (nervenet*)mc_host_addr_to_core_addr((mc_addr_t)(pre_cnf->all_cnf + nn));
	bj_nervenet->shd_cnf = nn_cnf;
	
	//mck_slog2("bj_nervenet_MAGIC_____");
	//mck_ilog(bj_nervenet->MAGIC);
	//mck_slog2("_____\n");

	bj_load_shd_cnf();

	mck_slog2("END_LOADING_CNF\n");
}

/*

	binder * fst, * lst, * wrk;
	binder* all_msvs = &(host_mgrp->all_agts);

	fst = (binder*)mc_host_pt_to_core_pt(all_msvs->bn_right);
	lst = all_msvs;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_host_pt_to_core_pt(wrk->bn_right)){
		missive* remote_msv = (missive*)wrk;

		cell* hdlr_dst = (remote_msv)->dst;
		EMU_CK(hdlr_dst != mc_null);

		mck_handle_missive_base(remote_msv, hdlr_dst->handler_idx);
	}

*/

void bj_load_shd_cnf(){
	nervenet* my_net = bj_nervenet;
	nervenet* nn_cnf = bj_nervenet->shd_cnf;

	long num_ccls = nn_cnf->tot_ccls;
	long num_vars = nn_cnf->tot_vars;
	long num_lits = nn_cnf->tot_lits;

	if(num_ccls == 0){
		return;
	}

	EMU_PRT("tot_lits=%ld tot_vars=%ld tot_ccls=%ld \n", 
			nn_cnf->tot_lits, nn_cnf->tot_vars, nn_cnf->tot_ccls);


	agent_ref::separate(2 * num_lits);
	neupole::separate(2 * num_vars);
	neuron::separate(num_ccls);

	EMU_PRT("Separated neupoles %ld \n", (3 * num_vars));

	binder * fst, * lst, * wrk;

	binder* nn_all_pos = &(nn_cnf->all_pos);
	fst = (binder*)mc_host_pt_to_core_pt(nn_all_pos->bn_right);
	lst = nn_all_pos;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_host_pt_to_core_pt(wrk->bn_right)){
		pre_cnf_node* nod = (pre_cnf_node*)wrk;
		EMU_CK(nod->opp_nod != mc_null);
		pre_cnf_node* opp = (pre_cnf_node*)mc_host_pt_to_core_pt(nod->opp_nod);
		//pre_cnf_node* opp = nod->opp_nod;

		neupole* pos_nod = neupole::acquire();
		neupole* neg_nod = neupole::acquire();

		pos_nod->opp = neg_nod;
		neg_nod->opp = pos_nod;

		my_net->all_pos.bind_to_my_left(*pos_nod);
		my_net->all_neg.bind_to_my_left(*neg_nod);

		EMU_PRT("[k%d id%ld sz%ld] \n", nod->ki, nod->id, nod->sz);
		EMU_PRT("[k%d id%ld sz%ld] \n", opp->ki, opp->id, opp->sz);
		EMU_PRT("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");

		EMU_CK(nod->loaded == mc_null);
		EMU_CK(opp->loaded == mc_null);

		nod->loaded = pos_nod;
		opp->loaded = neg_nod;
	}
	
}


