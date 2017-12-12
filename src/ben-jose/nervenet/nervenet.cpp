
#include "cell.hh"

#include "nervenet.hh"

missive_handler_t bj_nil_handlers[1] = { mc_null };

MCK_DEFINE_ACQUIRE_ALLOC(nervenet, 32);	// defines nervenet::acquire_alloc

MCK_DEFINE_MEM_METHODS(transmitter, 32, bj_ava_transmitters, 0)
MCK_DEFINE_MEM_METHODS(synset, 32, bj_ava_synsets, 0)
MCK_DEFINE_MEM_METHODS(tierset, 32, bj_ava_tiersets, bj_num_sep_tiersets)
MCK_DEFINE_MEM_METHODS(synapse, 32, bj_ava_synapses, 0)
MCK_DEFINE_MEM_METHODS(polaron, 32, bj_ava_polarons, 0)
MCK_DEFINE_MEM_METHODS(neuron, 32, bj_ava_neurons, 0)
MCK_DEFINE_MEM_METHODS(tierdata, 32, bj_ava_tierdatas, bj_num_sep_tierdatas)

BJ_DEFINE_GET_CLS_NAM(synset)
BJ_DEFINE_GET_CLS_NAM(tierset)
BJ_DEFINE_GET_CLS_NAM(transmitter)
BJ_DEFINE_GET_CLS_NAM(synapse)
BJ_DEFINE_GET_CLS_NAM(nervenode)
BJ_DEFINE_GET_CLS_NAM(neuron)
BJ_DEFINE_GET_CLS_NAM(polaron)
BJ_DEFINE_GET_CLS_NAM(tierdata)
BJ_DEFINE_GET_CLS_NAM(nervenet)

nervenet::nervenet(){
	MAGIC = MAGIC_VAL;

	tot_neus = 0;
	tot_vars = 0;
	tot_lits = 0;
	tot_rels = 0;

	num_sep_tiersets = 10;
	num_sep_tierdatas = 10;

	handler_idx = idx_nervenet;

	mc_init_arr_vals(idx_total, all_handlers, mc_null);

	shd_cnf = mc_null;

	tot_loading = 0;
	tot_loaded = 0;

	act_left_side.my_side = side_left;
	act_right_side.my_side = side_right;
}

nervenet::~nervenet(){} 

transmitter::transmitter(){
	//init_me();
} 

transmitter::~transmitter(){} 

void
transmitter::init_me(int caller){
	missive::init_me(caller);
	wrk_side = side_invalid;
	wrk_tier = BJ_INVALID_NUM_TIER;
}

synset::synset(){
	init_me();
} 

synset::~synset(){} 

void
synset::init_me(int caller){
	parent = mc_null;
	tot_syn = 0;
}

void 
synset::add_left_synapse(synapse* snp){
	EMU_CK(snp != mc_null);
	tot_syn++;
	all_syn.bind_to_my_left(*snp);
	snp->left_vessel = this;
}

void 
synset::add_right_synapse(synapse* snp){
	EMU_CK(snp != mc_null);
	tot_syn++;
	all_syn.bind_to_my_left(snp->right_handle);
	snp->right_vessel = this;
}

tierset::tierset(){
	init_me();
} 

tierset::~tierset(){} 

void
tierset::init_me(int caller){
	ti_id = BJ_INVALID_NUM_TIER;
}

synapse::synapse(){
	init_me();
} 

synapse::~synapse(){} 

void
synapse::init_me(int caller){
	handler_idx = idx_synapse;

	left_vessel = mc_null;
	right_vessel = mc_null;

	owner = mc_null;
	mate = mc_null;
}

neurostate::neurostate(){ 
	init_me();
} 

neurostate::~neurostate(){} 

void
neurostate::init_me(int caller){
	//side_kind = side_invalid;
	stabi_num_tier = 0;

	stabi_source = mc_null;

	prev_tot_active = 0;

	stabi_flags = 0;

	stabi_num_complete = 0;
	stabi_num_ping = 0;

	stabi_arr_cap = 0;
	stabi_arr_sz = 0;
	stabi_arr = mc_null;
}

nervenode::nervenode(){ 
	init_me();
} 

nervenode::~nervenode(){} 

void
nervenode::init_me(int caller){
	ki = nd_invalid; 
	id = 0; 
	sz = 0;
	creat_tier = 0;

	//left_side.side_kind = side_left;
	//right_side.side_kind = side_right;
}

polaron::polaron(){ 
	init_me();
} 

polaron::~polaron(){} 

void
polaron::init_me(int caller){
	handler_idx = idx_polaron;
	opp = mc_null; 
}

neuron::neuron(){
	init_me();
} 

neuron::~neuron(){} 

void
neuron::init_me(int caller){
	handler_idx = idx_neuron;
}

void bj_print_loaded_poles(grip& all_pol, node_kind_t ki) {
	binder * fst, * lst, * wrk;

	binder* pt_all_pol = &(all_pol);
	fst = (binder*)(pt_all_pol->bn_right);
	lst = pt_all_pol;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		polaron* my_pol = (polaron*)wrk;
		EMU_CK(my_pol->ki == ki);

		binder* nn_all_snp = &(my_pol->left_side.stabi_active_set.all_syn);

		//mck_slog2("lst2__________");
		//mck_xlog((mc_addr_t)nn_all_snp);
		//mck_slog2("__________\n");

		mck_ilog(my_pol->id);
		mck_slog2("{");

		binder * fst2, * lst2, * wrk2;
		fst2 = (binder*)(nn_all_snp->bn_right);
		lst2 = nn_all_snp;
		for(wrk2 = fst2; wrk2 != lst2; wrk2 = (binder*)(wrk2->bn_right)){
			synapse* my_snp = (synapse*)wrk2;
			MCK_CK(my_snp->mate != mc_null);

			synapse* mt_snp = (synapse*)(my_snp->mate);
			neuron* my_neu = (neuron*)(mt_snp->owner);
			MCK_CK(my_neu->ki == nd_neu);

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
		EMU_CK(my_neu->ki == nd_neu);

		binder* nn_all_snp = &(my_neu->left_side.stabi_active_set.all_syn);

		mck_slog2("n");
		mck_ilog(my_neu->id);
		mck_slog2("[");

		binder * fst2, * lst2, * wrk2;
		fst2 = (binder*)(nn_all_snp->bn_right);
		lst2 = nn_all_snp;
		for(wrk2 = fst2; wrk2 != lst2; wrk2 = (binder*)(wrk2->bn_right)){
			synapse* my_snp = (synapse*)wrk2;
			MCK_CK(my_snp->mate != mc_null);

			synapse* mt_snp = (synapse*)(my_snp->mate);
			polaron* my_pol = (polaron*)(mt_snp->owner);
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

char* net_side_to_str(net_side_t sd){
	char* resp = mc_null;
	switch(sd){
	case side_invalid:
		resp = mc_cstr("side_invalid");
	break;
	case side_left:
		resp = mc_cstr("side_left");
	break;
	case side_right:
		resp = mc_cstr("side_right");
	break;
	}
	return resp;
}

char* node_kind_to_str(node_kind_t ki){
	char* resp = mc_cstr("UNDEFINED_NODE_KIND !!!");
	switch(ki){
	case nd_invalid:
		resp = mc_cstr("nd_invalid");
	break;
	case nd_pos:
		resp = mc_cstr("nd_pos");
	break;
	case nd_neg:
		resp = mc_cstr("nd_neg");
	break;
	case nd_neu:
		resp = mc_cstr("nd_neu");
	break;
	}
	return resp;
}

char* sync_tok_to_str(sync_tok_t tok){
	char* resp = mc_cstr("UNKNOWN_SYNC_TOK");
	
	switch(tok){
	case bj_tok_sync_invalid:
		resp = mc_cstr("bj_tok_sync_invalid");
	break;
	case bj_tok_sync_empty_child:
		resp = mc_cstr("bj_tok_sync_empty_child");
	break;
	case bj_tok_sync_to_parent:
		resp = mc_cstr("bj_tok_sync_to_parent");
	break;
	case bj_tok_sync_to_children:
		resp = mc_cstr("bj_tok_sync_to_children");
	break;
	case bj_tok_sync_end:
		resp = mc_cstr("bj_tok_sync_end");
	break;
	}
	return resp;
}

char* load_tok_to_str(load_tok_t tok){
	char* resp = mc_cstr("UNKNOWN_LOAD_TOK");
	
	switch(tok){
	case bj_tok_load_invalid:
		resp = mc_cstr("bj_tok_load_invalid");
	break;
	case bj_tok_load_nw_syn:
		resp = mc_cstr("bj_tok_load_nw_syn");
	break;
	case bj_tok_load_no_lits:
		resp = mc_cstr("bj_tok_load_no_lits");
	break;
	case bj_tok_load_end:
		resp = mc_cstr("bj_tok_load_end");
	break;
	}
	return resp;
}

char* stabi_tok_to_str(stabi_tok_t tok){
	char* resp = mc_cstr("UNKNOWN_STABI_TOK");

	switch(tok){
	case bj_tok_stabi_invalid:
		resp = mc_cstr("bj_tok_stabi_invalid");
	break;
	case bj_tok_stabi_start:
		resp = mc_cstr("bj_tok_stabi_start");
	break;
	case bj_tok_stabi_ping:
		resp = mc_cstr("bj_tok_stabi_ping");
	break;
	case bj_tok_stabi_charge_all:
		resp = mc_cstr("bj_tok_stabi_charge_all");
	break;
	case bj_tok_stabi_charge_src:
		resp = mc_cstr("bj_tok_stabi_charge_src");
	break;
	case bj_tok_stabi_tier_done:
		resp = mc_cstr("bj_tok_stabi_tier_done");
	break;
	case bj_tok_stabi_conflict:
		resp = mc_cstr("bj_tok_stabi_conflict");
	break;
	case bj_tok_stabi_end_forward:
		resp = mc_cstr("bj_tok_stabi_end_forward");
	break;
	case bj_tok_stabi_end:
		resp = mc_cstr("bj_tok_stabi_end");
	break;
	}
	return resp;
}

netstate::netstate(){ 
	init_me();
} 

netstate::~netstate(){} 

void
netstate::init_me(int caller){
	my_side = side_invalid;

	curr_ti_still_neus = 0;

	sync_sent_tier_empty = BJ_INVALID_NUM_TIER;
	sync_tot_empty_children = 0;
	sync_sent_ti_empty = false;

	sync_tier_out = BJ_INVALID_NUM_TIER;
	sync_tier_in = BJ_INVALID_NUM_TIER;

	sync_tot_stopping_children = 0;
	sync_sent_stop_to_parent = false;

	sync_ending_propag = false;

	//EMU_PRT("SYNC_INIT_DATA TOT_CHLD=%d STOPPING=%d \n", 
	//			sync_tot_children, sync_tot_stopping_children);
}

tierdata::tierdata(){
	init_me();
} 

tierdata::~tierdata(){} 

void
tierdata::init_me(int caller){
	tdt_id = BJ_INVALID_NUM_TIER;

	inp_neus = BJ_INVALID_NUM_NODE;
	off_neus = 0;
	rcv_neus = 0;
}

void
nervenet::stabi_init_sync(){
	sync_tot_children = mc_map_get_tot_children();
	sync_parent_id = mc_map_get_parent_core_id();
	sync_map = mc_map_get_loaded();
}

void 
emu_prt_tok_codes(){
	for(mck_token_t aa = bj_tok_sync_invalid; aa <= bj_tok_stabi_end; aa++){
		if(is_sync_tok(aa)){
			EMU_PRT("%d: %s \n", aa, sync_tok_to_str((sync_tok_t)aa));
		}
		else if(is_load_tok(aa)){
			EMU_PRT("%d: %s \n", aa, load_tok_to_str((load_tok_t)aa));
		}
		else if(is_stabi_tok(aa)){
			EMU_PRT("%d: %s \n", aa, stabi_tok_to_str((stabi_tok_t)aa));
		}
	}
}

tierset*
neurostate::dbg_get_tiset(num_tier_t nti){
	if(stabi_tiers.is_alone()){
		return mc_null;
	}

	if(nti == BJ_INVALID_NUM_TIER){
		return mc_null;
	}

	if(nti == BJ_LAST_TIER){
		EMU_CK(((tierset*)stabi_tiers.bn_left)->ti_id != BJ_INVALID_NUM_TIER);
		return (tierset*)stabi_tiers.bn_left;
	}

	tierset* dat = mc_null;
	binder * fst, * lst, * wrk;

	binder* tis = &(stabi_tiers);
	fst = (binder*)(tis->bn_left);
	lst = tis;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_left)){
		tierset* tidat = (tierset*)wrk;
		if(tidat->ti_id >= nti){
			dat = tidat;
		}
		if(tidat->ti_id < nti){
			break;
		}
	}

	return dat;
}

void 
dbg_call_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd){
	EMU_CK(mth != mc_null);

	binder * fst, * lst, * wrk;

	fst = (binder*)(nn_all_snp->bn_right);
	lst = nn_all_snp;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synapse* my_snp = mc_null;
		if(sd == side_left){
			my_snp = (synapse*)wrk;
		} else {
			EMU_CK(sd == side_right);
			my_snp = bj_get_syn_of_rgt_handle(wrk);
		}
		EMU_CK(my_snp != mc_null);
		EMU_CK(bj_is_synapse(my_snp));

		(my_snp->owner->*mth)(my_snp, sd);
	}
}

void
synset::dbg_rec_call_all(bj_callee_t mth, net_side_t sd){
	MCK_CHECK_SP();
	dbg_call_all_synapses(&(all_syn), mth, sd);

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = grps;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		EMU_CK(sub_grp->parent == this);
		sub_grp->dbg_rec_call_all(mth, sd);
	}
}

void
nervenode::dbg_prt_syn(synapse* my_snp, net_side_t sd){
	MCK_CK(my_snp->mate != mc_null);

	synapse* mt_snp = (synapse*)(my_snp->mate);
	nervenode* the_nod = mt_snp->owner;

	mck_ilog(the_nod->id);
	mck_slog2(" ");
}

void
nervenode::dbg_prt_nod(net_side_t sd, dbg_consec_t prt_id, num_pulse_t num_pul, num_tier_t num_ti){
	bj_callee_t mth = &nervenode::dbg_prt_syn;

	neurostate& ne_stt = get_neurostate(sd);
	tierset* all_ti = ne_stt.dbg_get_tiset(num_ti);

	bool is_mpty = ((all_ti == mc_null) && ne_stt.stabi_active_set.is_empty());

	if(is_mpty){
		return;
	}

	mck_slog2("i");
	mck_ilog(prt_id);
	mck_slog2("p");
	mck_ilog(num_pul);
	mck_slog2("n");
	mck_ilog(id);
	mck_slog2(" [");

	if(all_ti != mc_null){
		binder * fst_2, * lst_2, * wrk_2;

		binder* tis = &(ne_stt.stabi_tiers);
		fst_2 = (binder*)(all_ti);
		lst_2 = tis;
		for(wrk_2 = fst_2; wrk_2 != lst_2; wrk_2 = (binder*)(wrk_2->bn_right)){
			tierset* tidat = (tierset*)wrk_2;
			dbg_call_all_synapses(&(tidat->ti_all), mth, sd);
			mck_slog2("+ ");
		}
	}

	ne_stt.stabi_active_set.dbg_rec_call_all(mth, sd);

	mck_slog2("]\n");
}

//	left_side.stabi_active_set.stabi_rec_send_all((bj_callee_t)(&nervenode::stabi_send_snp_propag), side_left);

void 
bj_print_active_cnf(net_side_t sd, dbg_consec_t prt_id, num_pulse_t num_pul, num_tier_t num_ti){
	nervenet* my_net = bj_nervenet;

	binder * fst, * lst, * wrk;

	binder* pt_all_neu = &(my_net->all_neu);
	fst = (binder*)(pt_all_neu->bn_right);
	lst = pt_all_neu;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		neuron* my_neu = (neuron*)wrk;
		EMU_CK(my_neu->ki == nd_neu);

		my_neu->dbg_prt_nod(sd, prt_id, num_pul, num_ti);
	}
}