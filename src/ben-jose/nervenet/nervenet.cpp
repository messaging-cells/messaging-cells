
#include "cell.hh"

#include "nervenet.hh"

missive_handler_t bj_nil_handlers[1] = { mc_null };

MCK_DEFINE_ACQUIRE_ALLOC(nervenet, 32);	// defines nervenet::acquire_alloc

MCK_DEFINE_MEM_METHODS(synset, 32, bj_ava_synsets)
MCK_DEFINE_MEM_METHODS(synapse, 32, bj_ava_synapses)
MCK_DEFINE_MEM_METHODS(neupole, 32, bj_ava_neupoles)
MCK_DEFINE_MEM_METHODS(neuron, 32, bj_ava_neurons)

BJ_DEFINE_nervenet_methods();

synset::synset(){
	handler_idx = idx_synset;
	parent = mc_null;
	set_sz = 0;
} 

synset::~synset(){} 

void 
synset::add_synapse(synapse* snp){
	EMU_CK(snp != mc_null);
	set_sz++;
	all_syn.bind_to_my_left(*snp);
	snp->vessel = this;
}

void 
synset::remove_synapse(synapse* snp){
	EMU_CK(snp != mc_null);
	set_sz--;
	snp->let_go();
	snp->vessel = mc_null;
}

synapse::synapse(){
	handler_idx = idx_synapse;
	owner = mc_null;
	mate = mc_null;
	vessel = mc_null;
} 

synapse::~synapse(){} 

nervenode::nervenode(){ 
	ki = nd_invalid; 
	id = 0; 
	sz = 0; 
} 

nervenode::~nervenode(){} 

neupole::neupole(){ 
	handler_idx = idx_neupole;
	opp = mc_null; 
} 

neupole::~neupole(){} 

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
		neupole* my_pol = (neupole*)wrk;
		EMU_CK(my_pol->ki == ki);

		binder* nn_all_snp = &(my_pol->all_conn.all_syn);

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

		binder* nn_all_snp = &(my_neu->all_conn.all_syn);

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
			neupole* my_pol = (neupole*)(mt_snp->owner);
			//neupole* my_pol = (neupole*)(my_snp->mate);
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

