
#include "cell.hh"

#include "preload_cnf.hh"


MCK_DEFINE_ACQUIRE_ALLOC(nervenet, 32);	// defines nervenet::acquire_alloc

MCK_DEFINE_MEM_METHODS(neupole, 32, bj_ava_neupoles)
MCK_DEFINE_MEM_METHODS(neuron, 32, bj_ava_neurons)

BJ_DEFINE_nervenet_methods();

nervenode::nervenode(){ 
	ki = nd_invalid; 
	id = 0; 
	sz = 0; 
} 

nervenode::~nervenode(){} 

void 
nervenode::init_with(pre_cnf_node* nod) { 
	ki = nod->ki; 
	id = nod->id; 
	sz = nod->sz; 
} 

neupole::neupole(){ 
	opp = mc_null; 
} 

neupole::~neupole(){} 

neuron::neuron(){} 

neuron::~neuron(){} 


void bj_load_main() {
	//kernel* ker = kernel::get_sys();
	kernel* ker = mck_get_kernel();
	mc_core_nn_t nn = kernel::get_core_nn();

	//EMU_PRT("bj_load_main 1 \n");

	//mck_slog2("LOAD_CNF\n");
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

	bj_print_loaded_cnf();

	mck_slog2("END_LOADING_CNF\n");
}

void bj_load_poles(grip& all_pol){
	binder * fst, * lst, * wrk;

	binder* pt_all_pol = &(all_pol);
	fst = (binder*)mc_host_pt_to_core_pt(pt_all_pol->bn_right);
	lst = pt_all_pol;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_host_pt_to_core_pt(wrk->bn_right)){
		pre_cnf_node* sh_pol = (pre_cnf_node*)wrk;
		while(sh_pol->loaded == mc_null){
			// SPIN UNTIL SET (may be set by an other core)
		}
		neupole* my_pol = (neupole*)mck_as_loc_pt(sh_pol->loaded);
		MCK_CK(my_pol != mc_null);

		binder* nn_all_snp = &(sh_pol->all_agts);

		binder * fst2, * lst2, * wrk2;
		fst2 = (binder*)mc_host_pt_to_core_pt(nn_all_snp->bn_right);
		lst2 = nn_all_snp;
		for(wrk2 = fst2; wrk2 != lst2; wrk2 = (binder*)mc_host_pt_to_core_pt(wrk2->bn_right)){
			agent_ref* sh_snp = (agent_ref*)wrk2;
			pre_cnf_node* sh_neu = (pre_cnf_node*)mc_host_pt_to_core_pt(sh_snp->glb_agent_ptr);
			while(sh_neu->loaded == mc_null){
				// SPIN UNTIL SET (may be set by an other core)
			}
			neuron* my_neu = (neuron*)(sh_neu->loaded);

			agent_ref* my_snp = agent_ref::acquire();

			my_snp->glb_agent_ptr = my_neu;
			MCK_CK(my_snp->glb_agent_ptr != mc_null);

			my_pol->all_agts.bind_to_my_left(*my_snp);
		}
	}
}

void bj_load_shd_cnf(){
	nervenet* my_net = bj_nervenet;
	nervenet* nn_cnf = bj_nervenet->shd_cnf;

	long num_neus = nn_cnf->tot_neus;
	long num_vars = nn_cnf->tot_vars;
	long num_lits = nn_cnf->tot_lits;

	if(num_neus == 0){
		return;
	}

	EMU_PRT("tot_lits=%ld tot_vars=%ld tot_neus=%ld \n", 
			nn_cnf->tot_lits, nn_cnf->tot_vars, nn_cnf->tot_neus);


	agent_ref::separate(2 * num_lits);
	neupole::separate(2 * num_vars);
	neuron::separate(num_neus);

	EMU_PRT("Separated neupoles %ld \n", (3 * num_vars));

	binder * fst, * lst, * wrk;

	binder* nn_all_pos = &(nn_cnf->all_pos);
	fst = (binder*)mc_host_pt_to_core_pt(nn_all_pos->bn_right);
	lst = nn_all_pos;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_host_pt_to_core_pt(wrk->bn_right)){
		pre_cnf_node* nod = (pre_cnf_node*)wrk;

		EMU_CK(nod->ki == nd_pos);
		EMU_CK(nod->opp_nod != mc_null);

		pre_cnf_node* opp = (pre_cnf_node*)mc_host_pt_to_core_pt(nod->opp_nod);
		EMU_CK(opp->ki == nd_neg);
		EMU_CK(nod->id == -(opp->id));
		//pre_cnf_node* opp = nod->opp_nod;

		neupole* pos_nod = neupole::acquire();
		neupole* neg_nod = neupole::acquire();

		pos_nod->init_with(nod);
		neg_nod->init_with(opp);

		pos_nod->opp = neg_nod;
		neg_nod->opp = pos_nod;

		my_net->all_pos.bind_to_my_left(*pos_nod);
		my_net->all_neg.bind_to_my_left(*neg_nod);

		//EMU_PRT("[k%d id%ld sz%ld] \n", nod->ki, nod->id, nod->sz);
		//EMU_PRT("[k%d id%ld sz%ld] \n", opp->ki, opp->id, opp->sz);
		//EMU_PRT("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");

		EMU_CK(nod->loaded == mc_null);
		EMU_CK(opp->loaded == mc_null);

		nod->loaded = mck_as_glb_pt(pos_nod);
		opp->loaded = mck_as_glb_pt(neg_nod);
	}

	binder* nn_all_neu = &(nn_cnf->all_neu);
	fst = (binder*)mc_host_pt_to_core_pt(nn_all_neu->bn_right);
	lst = nn_all_neu;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_host_pt_to_core_pt(wrk->bn_right)){
		pre_cnf_node* sh_neu = (pre_cnf_node*)wrk;

		neuron* my_neu = neuron::acquire();
		my_net->all_neu.bind_to_my_left(*my_neu);

		my_neu->init_with(sh_neu);
		sh_neu->loaded = mck_as_glb_pt(my_neu);

		//mck_slog2("[");

		binder* nn_all_snp = &(sh_neu->all_agts);

		binder * fst2, * lst2, * wrk2;
		fst2 = (binder*)mc_host_pt_to_core_pt(nn_all_snp->bn_right);
		lst2 = nn_all_snp;
		for(wrk2 = fst2; wrk2 != lst2; wrk2 = (binder*)mc_host_pt_to_core_pt(wrk2->bn_right)){
			agent_ref* sh_snp = (agent_ref*)wrk2;
			pre_cnf_node* pol = (pre_cnf_node*)mc_host_pt_to_core_pt(sh_snp->glb_agent_ptr);

			while(pol->loaded == mc_null){
				// SPIN UNTIL SET (may be set by an other core)
			}
			neupole* my_pol = (neupole*)(pol->loaded);
			
			MCK_CK(my_pol->id == pol->id);

			agent_ref* my_snp = agent_ref::acquire();

			my_snp->glb_agent_ptr = my_pol;
			MCK_CK(my_snp->glb_agent_ptr != mc_null);

			my_neu->all_agts.bind_to_my_left(*my_snp);

			//mck_ilog(my_pol->id);
			//mck_slog2(" ");
		}
		
		//mck_slog2("]\n");
	}
	
	bj_load_poles(nn_cnf->all_pos);
	bj_load_poles(nn_cnf->all_neg);
}

void bj_print_loaded_poles(grip& all_pol, node_kind_t ki) {
	binder * fst, * lst, * wrk;

	binder* pt_all_pol = &(all_pol);
	fst = (binder*)(pt_all_pol->bn_right);
	lst = pt_all_pol;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		neupole* my_pol = (neupole*)wrk;
		EMU_CK(my_pol->ki == ki);

		binder* nn_all_snp = &(my_pol->all_agts);

		//mck_slog2("lst2__________");
		//mck_xlog((mc_addr_t)nn_all_snp);
		//mck_slog2("__________\n");

		mck_ilog(my_pol->id);
		mck_slog2("{");

		binder * fst2, * lst2, * wrk2;
		fst2 = (binder*)(nn_all_snp->bn_right);
		lst2 = nn_all_snp;
		for(wrk2 = fst2; wrk2 != lst2; wrk2 = (binder*)(wrk2->bn_right)){
			agent_ref* my_snp = (agent_ref*)wrk2;
			MCK_CK(my_snp->glb_agent_ptr != mc_null);

			neuron* my_neu = (neuron*)(my_snp->glb_agent_ptr);
			MCK_CK(my_neu->ki == nd_ccl);

			mck_ilog(my_neu->id);
			mck_slog2(" ");

			//mck_slog2("nxt2__________");
			//mck_xlog((mc_addr_t)(wrk2->bn_right));
			//mck_slog2("__________\n");
		}

		mck_slog2("}\n");
	}
}

void 
bj_print_loaded_cnf() {
	nervenet* my_net = bj_nervenet;

	binder * fst, * lst, * wrk;

	binder* pt_all_neu = &(my_net->all_neu);
	fst = (binder*)(pt_all_neu->bn_right);
	lst = pt_all_neu;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		neuron* my_neu = (neuron*)wrk;
		EMU_CK(my_neu->ki == nd_ccl);

		binder* nn_all_snp = &(my_neu->all_agts);

		mck_slog2("n");
		mck_ilog(my_neu->id);
		mck_slog2("[");

		binder * fst2, * lst2, * wrk2;
		fst2 = (binder*)(nn_all_snp->bn_right);
		lst2 = nn_all_snp;
		for(wrk2 = fst2; wrk2 != lst2; wrk2 = (binder*)(wrk2->bn_right)){
			agent_ref* my_snp = (agent_ref*)wrk2;
			MCK_CK(my_snp->glb_agent_ptr != mc_null);

			neupole* my_pol = (neupole*)(my_snp->glb_agent_ptr);
			MCK_CK((my_pol->id <= 0) || (my_pol->ki == nd_pos));
			MCK_CK((my_pol->id >= 0) || (my_pol->ki == nd_neg));

			mck_ilog(my_pol->id);
			mck_slog2(" ");
		}

		mck_slog2("]\n");
	}

	bj_print_loaded_poles(my_net->all_pos, nd_pos);
	bj_print_loaded_poles(my_net->all_neg, nd_neg);
}

