
#include "cell.hh"

#include "nervenet.hh"

missive_handler_t bj_nil_handlers[1] = { mc_null };

MCK_DEFINE_ACQUIRE_ALLOC(nervenet, 32);	// defines nervenet::acquire_alloc

MCK_DEFINE_MEM_METHODS(transmitter, 32, bj_ava_transmitters)
MCK_DEFINE_MEM_METHODS(synset, 32, bj_ava_synsets)
MCK_DEFINE_MEM_METHODS(tierset, 32, bj_ava_tiersets)
MCK_DEFINE_MEM_METHODS(synapse, 32, bj_ava_synapses)
MCK_DEFINE_MEM_METHODS(polaron, 32, bj_ava_polarons)
MCK_DEFINE_MEM_METHODS(neuron, 32, bj_ava_neurons)

BJ_DEFINE_nervenet_methods();

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
	//handler_idx = idx_synset;
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
	synset::init_me(caller);
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

