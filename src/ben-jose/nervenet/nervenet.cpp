
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
	stabi_num_still = 0;

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
	char* resp = mc_null;
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
	case bj_tok_stabi_propag:
		resp = mc_cstr("bj_tok_stabi_propag");
	break;
	case bj_tok_stabi_charge_all:
		resp = mc_cstr("bj_tok_stabi_charge_all");
	break;
	case bj_tok_stabi_charge_src:
		resp = mc_cstr("bj_tok_stabi_charge_src");
	break;
	case bj_tok_stabi_tier_end:
		resp = mc_cstr("bj_tok_stabi_tier_end");
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
	curr_ti_still_neus = 0;
	curr_ti_still_pols = 0;
}

tierdata::tierdata(){
	init_me();
} 

tierdata::~tierdata(){} 

void
tierdata::init_me(int caller){
	tdt_id = BJ_INVALID_NUM_TIER;

	inp_neus = BJ_INVALID_NUM_NODE;
	inp_pols = BJ_INVALID_NUM_NODE;

	off_neus = 0;
	off_pols = 0;

	rcv_neus = 0;
	rcv_pols = 0;
}

void
nervenet::stabi_init_sync(){
	sync_tot_child = mc_map_get_tot_children();
	sync_parent_id = mc_map_get_parent_core_id();
	sync_map = mc_map_get_loaded();

	sync_side_out = side_invalid;
	sync_tier_out = BJ_INVALID_NUM_TIER;
	sync_side_in = side_invalid;
	sync_tier_in = BJ_INVALID_NUM_TIER;

	sync_tot_stopping_child = 0;
	sync_sent_stop_to_parent = false;

	//EMU_PRT("SYNC_INIT_DATA TOT_CHLD=%d STOPPING=%d \n", sync_tot_child, sync_tot_stopping_child);
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

