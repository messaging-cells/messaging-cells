
#include "cell.hh"

#include "load_cnf.hh"
#include "preload_cnf.hh"

void 
nervenode::init_nervenode_with(pre_cnf_node* nod) { 
	ki = nod->ki; 
	id = nod->id; 
	sz = nod->pre_sz; 
} 

void 
nervenet_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, load_handler, msv);
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
	hndlrs[idx_nervenet] = nervenet_handler;
	hndlrs[idx_polaron] = polaron_handler;
	hndlrs[idx_synapse] = synapse_handler;

	kernel::set_handlers(idx_total, hndlrs);
}

void
nervenet::init_nervenet_with(pre_cnf_net* pre_net){
	tot_neus = pre_net->tot_pre_neus;
	tot_vars = pre_net->tot_pre_vars;
	tot_lits = pre_net->tot_pre_lits;
	tot_rels = pre_net->tot_pre_rels;
}

void
neurostate::update_prev_tot_active(){
	prev_tot_active = stabi_active_set.tot_syn;
}

void bj_load_shd_cnf(){
	nervenet* my_net = bj_nervenet;
	pre_cnf_net* nn_cnf = bj_nervenet->shd_cnf;

	my_net->init_nervenet_with(nn_cnf);
	nervenet& tots = *my_net;

	//EMU_PRT("%ld local tot_vars\n", my_net->tot_vars);

	long num_neus = tots.tot_neus;
	long num_vars = tots.tot_vars;
	long num_rels = tots.tot_rels;

	/*if(num_neus == 0){
		return;
	}*/

	//EMU_PRT("tot_lits=%ld tot_vars=%ld tot_neus=%ld TOT_RELS=%ld \n", 
	//		tots.tot_lits, tots.tot_vars, tots.tot_neus, tots.tot_rels);

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

	EMU_PRT("Separated polarons %ld\n", sep_pols);

	binder * fst, * lst, * wrk;

	binder* nn_all_pos = &(nn_cnf->all_pre_pos);
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

	binder* nn_all_neu = &(nn_cnf->all_pre_neu);
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

			MCK_CK(my_neu->left_side.stabi_active_set.parent == mc_null);
			my_neu->left_side.stabi_active_set.add_left_synapse(my_snp);
			my_neu->left_side.update_prev_tot_active();

			transmitter* msv = transmitter::acquire();
			EMU_CK(msv->wrk_side == side_invalid);
			msv->src = my_snp;
			msv->dst = my_pol;
			msv->tok = bj_tok_load_nw_syn;
			msv->send();

			/*
			long& tot_ld = bj_nervenet->tot_loading;
			tot_ld++;
			if(tot_ld == tots.tot_lits){
				EMU_PRT("SENT LAST------------------------ \n");
			}
			EMU_PRT("SND to pole %d msv from neu %d \n", my_pol->id, my_neu->id);
			*/

			//mck_ilog(my_pol->id);
			//mck_slog2(" ");
		}
		
		//mck_slog2("]\n");
	}

	if(tots.tot_lits == 0){
		transmitter* msv = transmitter::acquire();
		EMU_CK(msv->wrk_side == side_invalid);
		msv->src = my_net;
		msv->dst = my_net;
		msv->tok = bj_tok_load_no_lits;
		msv->send();
	}
}

void
nervenet::load_handler(missive* msv){
	load_tok_t tok = (load_tok_t)msv->tok;
	MC_MARK_USED(tok);
	MCK_CK(tok == bj_tok_load_no_lits);

	EMU_CODE(mc_core_nn_t nn = mck_get_kernel()->get_core_nn());
	EMU_PRT("ENDING_CNF_LOAD %d --------------- PARENT=%x \n", nn, mc_map_get_parent_core_id());
	kernel::stop_sys(bj_tok_load_end);
}

void
polaron::load_handler(missive* msv){
	cell* syn_src = msv->src;
	load_tok_t tok = (load_tok_t)msv->tok;
	MC_MARK_USED(syn_src);
	MC_MARK_USED(tok);
	MCK_CK(tok == bj_tok_load_nw_syn);

	synapse* mt_snp = (synapse*)syn_src;
	synapse* my_snp = synapse::acquire();

	//EMU_PRT("RCV msv pole %d from neu %d \n", id, mt_snp->owner->id);
	//EMU_PRT("polaron::load_handler got snp=%p %s \n", (void*)mt_snp, mt_snp->get_class_name());
	//EMU_CK(syn_src->get_class_name() == synapse_cls_nam);
	EMU_CK(bj_is_synapse(syn_src));

	polaron* my_glb_pol = (polaron*)mck_as_glb_pt(this);

	my_snp->owner = my_glb_pol;
	my_snp->mate = mt_snp;
	MCK_CK(my_snp->mate != mc_null);

	MCK_CK(left_side.stabi_active_set.parent == mc_null);
	left_side.stabi_active_set.add_left_synapse(my_snp);
	left_side.update_prev_tot_active();

	transmitter* msv2 = transmitter::acquire();
	EMU_CK(msv2->wrk_side == side_invalid);
	msv2->src = my_snp;
	msv2->dst = mt_snp;
	msv2->tok = bj_tok_load_nw_syn;
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
	EMU_CK_PRT(tok == bj_tok_load_nw_syn, "BAD_TOK= %s (%d) (%s)\n\n", load_tok_to_str(tok), tok, 
			stabi_tok_to_str((stabi_tok_t)(msv->tok)));

	synapse* mt_snp = (synapse*)syn_src;

	//EMU_PRT("synapse::load_handler got snp=%p %s \n", (void*)mt_snp, mt_snp->get_class_name());
	//EMU_CK(syn_src->get_class_name() == synapse_cls_nam);
	EMU_CK(bj_is_synapse(syn_src));

	mate = mt_snp;
	EMU_CK(mate != mc_null);

	nervenet* my_net = bj_nervenet;
	long& tot_ld = my_net->tot_loaded;
	tot_ld++;
	if(tot_ld == my_net->tot_lits){
		//mck_slog2("ENDING_CNF_LOAD \n");
		EMU_CODE(mc_core_nn_t nn = mck_get_kernel()->get_core_nn());
		EMU_PRT("ENDING_CNF_LOAD %d --------------- PARENT=%x \n", nn, mc_map_get_parent_core_id());
		//print_childs();
		//mck_get_kernel()->set_idle_exit();
		kernel::stop_sys(bj_tok_load_end);
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

	pre_cnf_net* nn_cnf = (pre_cnf_net*)mc_host_addr_to_core_addr((mc_addr_t)(pre_cnf->all_cnf + nn));
	bj_nervenet->shd_cnf = nn_cnf;
	
	//mck_slog2("bj_nervenet_MAGIC_____");
	//mck_ilog(bj_nervenet->MAGIC);
	//mck_slog2("_____\n");

	bj_load_shd_cnf();

	bj_load_init_handlers();

	//EMU_PRT("END_LOAD:SHD \n");

	kernel::run_sys();

	my_net->act_left_side.init_tiers(*my_net);
	my_net->act_right_side.init_tiers(*my_net);

	EMU_CODE(
		tierdata& dat = my_net->act_left_side.get_last_tier();
		num_nod_t n1 = dat.inp_neus;
		num_nod_t p1 = dat.inp_pols;
	);
	EMU_LOG("\n=========================================================================\n");
	EMU_LOG("inp_neu=%ld inp_pol=%ld \n", n1, p1);

	//bj_print_loaded_cnf();

	//mck_slog2("END_LOADING_CNF_____________________________\n");
}

void
tierdata::add_all_inp_from(grip& grp, net_side_t sd){
	binder * fst, * lst, * wrk;

	binder* pt_grp = &(grp);
	fst = (binder*)(pt_grp->bn_right);
	lst = pt_grp;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		nervenode* my_nod = (nervenode*)wrk;
		neurostate& stt = my_nod->get_neurostate(sd);
		num_syn_t tsn = stt.stabi_active_set.tot_syn;
		//EMU_LOG("ADD_NOD %s %ld tot_syn=%ld\n", node_kind_to_str(my_nod->ki), my_nod->id, tsn);
		if(tsn > 0){
			if(my_nod->ki == nd_neu){
				inp_neus++;
			} else {
				EMU_CK(bj_is_pol(my_nod->ki));
				inp_pols++;
			}
		}
	}
}

void
netstate::init_tiers(nervenet& my_net){
	tierdata* ti_dat = tierdata::acquire();

	ti_dat->tdt_id = 0;
	ti_dat->inp_neus = 0;
	ti_dat->inp_pols = 0;

	ti_dat->add_all_inp_from(my_net.all_neu, my_side);
	ti_dat->add_all_inp_from(my_net.all_pos, my_side);
	ti_dat->add_all_inp_from(my_net.all_neg, my_side);

	//EMU_CK((my_side != side_right) || (ti_dat->inp_neus == 0));

	all_tiers.bind_to_my_left(*ti_dat);
}

