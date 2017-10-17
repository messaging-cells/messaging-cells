
#include "cell.hh"

#include "preload_cnf.hh"

void 
nervenode::init_nervenode_with(pre_cnf_node* nod) { 
	ki = nod->ki; 
	id = nod->id; 
	sz = nod->pre_sz; 
} 

void 
polaron_handler(missive* msv){
	MCK_CALL_HANDLER(polaron, load_handler, msv);
}

void 
synapse_handler(missive* msv){
	MCK_CALL_HANDLER(synapse, load_handler, msv);
}

void
bj_load_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_polaron] = polaron_handler;
	hndlrs[idx_synapse] = synapse_handler;

	kernel::set_handlers(idx_total, hndlrs);
}

void
nervenet::init_nervenet_with(nervenet* nvnet){
	tot_neus = nvnet->tot_neus;
	tot_vars = nvnet->tot_vars;
	tot_lits = nvnet->tot_lits;
	tot_rels = nvnet->tot_rels;
}

void bj_load_shd_cnf(){
	nervenet* my_net = bj_nervenet;
	nervenet* nn_cnf = bj_nervenet->shd_cnf;

	my_net->init_nervenet_with(nn_cnf);

	long num_neus = my_net->tot_neus;
	long num_vars = my_net->tot_vars;
	long num_rels = my_net->tot_rels;

	if(num_neus == 0){
		return;
	}

	//EMU_PRT("tot_lits=%ld tot_vars=%ld tot_neus=%ld TOT_RELS=%ld \n", 
	//		my_net->tot_lits, my_net->tot_vars, my_net->tot_neus, my_net->tot_rels);

	long sep_msvs = 3 * num_rels;	// almost (lft + rgt)
	long sep_ssts = 2 * num_rels;	// lft + rgt
	long sep_tsts = (num_vars >> 3);
	long sep_snps = 2 * num_rels;	// lft + rgt
	long sep_pols = 2 * num_vars;
	long sep_neus = num_neus;

	if(sep_tsts > my_net->num_sep_tiersets){
		my_net->num_sep_tiersets = sep_tsts;
	}

	transmitter::separate(sep_msvs);
	synset::separate(sep_ssts);
	tierset::separate(-1);
	synapse::separate(sep_snps);
	polaron::separate(sep_pols);
	neuron::separate(sep_neus);

	EMU_PRT("Separated polarons %ld \n", sep_pols);

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

		polaron* pos_nod = polaron::acquire();
		polaron* neg_nod = polaron::acquire();

		pos_nod->init_nervenode_with(nod);
		neg_nod->init_nervenode_with(opp);

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

		neuron* my_glb_neu = (neuron*)mck_as_glb_pt(my_neu);

		my_neu->init_nervenode_with(sh_neu);
		sh_neu->loaded = my_glb_neu;

		//mck_slog2("[");

		binder* nn_all_snp = &(sh_neu->all_agts);

		binder * fst2, * lst2, * wrk2;
		fst2 = (binder*)mc_host_pt_to_core_pt(nn_all_snp->bn_right);
		lst2 = nn_all_snp;
		for(wrk2 = fst2; wrk2 != lst2; wrk2 = (binder*)mc_host_pt_to_core_pt(wrk2->bn_right)){
			agent_ref* sh_snp = (agent_ref*)wrk2;
			pre_cnf_node* pol = (pre_cnf_node*)mc_host_pt_to_core_pt(sh_snp->glb_agent_ptr);

			//EMU_CK(pol->loaded != mc_null);
			while(pol->loaded == mc_null){
				// SPIN UNTIL SET (may be set by an other core)
				EMU_CODE(sched_yield());
			}
			EMU_CK(pol->loaded != mc_null);
			polaron* my_pol = (polaron*)(pol->loaded);
			
			MCK_CK(my_pol->id == pol->id);

			synapse* my_snp = synapse::acquire();

			my_snp->owner = my_glb_neu;
			//my_snp->mate = my_pol;
			//MCK_CK(my_snp->mate != mc_null);

			my_neu->left_side.stabi_active_set.add_left_synapse(my_snp);

			transmitter* msv = transmitter::acquire();
			EMU_CK(msv->wrk_side == side_invalid);
			msv->src = my_snp;
			msv->dst = my_pol;
			msv->tok = tok_nw_syn;
			msv->send();

			/*
			long& tot_ld = bj_nervenet->tot_loading;
			tot_ld++;
			if(tot_ld == my_net->tot_lits){
				EMU_PRT("SENT LAST------------------------ \n");
			}
			EMU_PRT("SND to pole %d msv from neu %d \n", my_pol->id, my_neu->id);
			*/

			//mck_ilog(my_pol->id);
			//mck_slog2(" ");
		}
		
		//mck_slog2("]\n");
	}
}

void
polaron::load_handler(missive* msv){
	cell* syn_src = msv->src;
	load_tok_t tok = (load_tok_t)msv->tok;
	MC_MARK_USED(syn_src);
	MC_MARK_USED(tok);
	MCK_CK(tok == tok_nw_syn);

	synapse* mt_snp = (synapse*)syn_src;
	synapse* my_snp = synapse::acquire();

	//EMU_PRT("RCV msv pole %d from neu %d \n", id, mt_snp->owner->id);

	polaron* my_glb_pol = (polaron*)mck_as_glb_pt(this);

	my_snp->owner = my_glb_pol;
	my_snp->mate = mt_snp;
	MCK_CK(my_snp->mate != mc_null);

	left_side.stabi_active_set.add_left_synapse(my_snp);

	transmitter* msv2 = transmitter::acquire();
	EMU_CK(msv2->wrk_side == side_invalid);
	msv2->src = my_snp;
	msv2->dst = mt_snp;
	msv2->tok = tok_nw_syn;
	msv2->send();
}

void
print_childs(){
	mc_load_map_st* mp = mc_map_get_loaded();

	mck_slog2("NUM_CORE=");
	mck_ilog(mp->num_core);
	mck_slog2("___\n");

	//EMU_PRT("NUM_CORE=%d \n", mp->num_core);

	if(mp->childs == mc_null){ 
		mck_slog2("NULL_CHILDS\n");
		return; 
	}

	int aa = 0;
	mc_load_map_st* ch_map = (mp->childs)[aa];
	while(ch_map != mc_null){
		//EMU_PRT("CHILD=%d \n", ch_map->num_core);
		mck_slog2("CHILD=");
		mck_ilog(ch_map->num_core);
		mck_slog2("___\n");

		aa++;
		ch_map = (mp->childs)[aa];
	}
	mck_slog2("END_PRT_CHILDS\n");
}

void
synapse::load_handler(missive* msv){
	cell* syn_src = msv->src;
	load_tok_t tok = (load_tok_t)msv->tok;
	MC_MARK_USED(syn_src);
	MC_MARK_USED(tok);
	MCK_CK(tok == tok_nw_syn);

	synapse* mt_snp = (synapse*)syn_src;

	mate = mt_snp;
	MCK_CK(mate != mc_null);

	nervenet* my_net = bj_nervenet;
	long& tot_ld = my_net->tot_loaded;
	tot_ld++;
	if(tot_ld == my_net->tot_lits){
		//mck_slog2("ENDING_CNF_LOAD \n");
		//EMU_PRT("RCV_LAST------------------------ PARENT=%x \n", mc_map_get_parent_core_id());
		//print_childs();
		//mck_get_kernel()->set_idle_exit();
		kernel::stop_sys(tok_end_load);
	}
	EMU_PRT("RCV5 msv neu %d from pole %d LOADED=(%ld/%ld) \n", 
		owner->id, mt_snp->owner->id, tot_ld, my_net->tot_lits);
}

void bj_load_main() {
	/*
	mc_core_id_t p_koid = mc_map_get_parent_core_id();
	mck_slog2("PARENT___");
	if(p_koid == 0){
		mck_slog2("_IS_NULL_");
	} else {
		mck_ilog(mc_id_to_nn(p_koid));
	}
	mck_slog2("___\n");
	*/
	//print_childs();

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

	bj_load_init_handlers();

	//EMU_PRT("END_LOAD:SHD \n");

	kernel::run_sys();

	//bj_print_loaded_cnf();

	//mck_slog2("END_LOADING_CNF_____________________________\n");
}

