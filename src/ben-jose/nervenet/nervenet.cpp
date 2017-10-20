
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

nervenet::nervenet(){
	MAGIC = MAGIC_VAL;

	num_sep_tiersets = 10;

	handler_idx = idx_nervenet;

	mc_init_arr_vals(idx_total, all_handlers, mc_null);

	shd_cnf = mc_null;

	tot_loading = 0;
	tot_loaded = 0;
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
	wrk_tier = BJ_INVALID_TIER;
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
	num_tier = BJ_INVALID_TIER;
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
	stabi_tier = 0;
	stabi_source = mc_null;
	stabi_num_complete = 0;
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
	handler_idx = idx_neuron;
} 

neuron::~neuron(){} 

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
			//neuron* my_neu = (neuron*)(my_snp->mate);
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
			/*while(my_snp->mate == mc_null){
				// SPIN UNTIL SET (may be set by an other core) // LOCKS_HERE ?
			}*/
			MCK_CK(my_snp->mate != mc_null);

			synapse* mt_snp = (synapse*)(my_snp->mate);
			polaron* my_pol = (polaron*)(mt_snp->owner);
			//polaron* my_pol = (polaron*)(my_snp->mate);
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

char* stabi_tok_to_str(stabi_tok_t tok){
	char* resp = mc_null;
	switch(tok){
	case tok_stabi_invalid:
		resp = mc_cstr("tok_stabi_invalid");
	break;
	case tok_stabi_start:
		resp = mc_cstr("tok_stabi_start");
	break;
	case tok_stabi_propag:
		resp = mc_cstr("tok_stabi_propag");
	break;
	case tok_stabi_charge_all:
		resp = mc_cstr("tok_stabi_charge_all");
	break;
	case tok_stabi_charge_src:
		resp = mc_cstr("tok_stabi_charge_src");
	break;
	case tok_stabi_tier_end:
		resp = mc_cstr("tok_stabi_tier_end");
	break;
	case tok_end_stabi:
		resp = mc_cstr("tok_end_stabi");
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
	tot_neus = 0;
	tot_vars = 0;
	tot_lits = 0;
	tot_rels = 0;

	tot_rcv_pol = 0;

	dbg_num_neu = 0;
	dbg_num_pol = 0;
}

void
netstate::init_with(netstate& stt){
	tot_neus = stt.tot_neus;
	tot_vars = stt.tot_vars;
	tot_lits = stt.tot_lits;
	tot_rels = stt.tot_rels;

	tot_rcv_pol = stt.tot_rcv_pol;
}

