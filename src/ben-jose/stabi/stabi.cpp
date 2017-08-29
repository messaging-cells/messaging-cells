
#include "cell.hh"

#include "stabi.hh"

void 
polaron_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(polaron, stabi_handler, msv);
}

void 
neuron_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(neuron, stabi_handler, msv);
}

void 
synapse_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(synapse, stabi_handler, msv);
}

void 
nervenet_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, stabi_handler, msv);
}

void
bj_stabi_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;

	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_polaron] = polaron_stabi_handler;
	hndlrs[idx_neuron] = neuron_stabi_handler;
	hndlrs[idx_synapse] = synapse_stabi_handler;
	hndlrs[idx_nervenet] = nervenet_stabi_handler;

	kernel::set_handlers(idx_total, bj_handlers);
}

void bj_stabi_main() {
	//kernel* ker = mck_get_kernel();
	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_stabi_init_handlers();

	//kernel::run_sys();

	mck_slog2("STABI___\n");

	bj_print_loaded_cnf();

	mck_slog2("END_STABI___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");

}

void 
synset::calc_stabi_arr_rec(num_syn_t cap, num_syn_t* arr, num_syn_t& ii) { // careful with stack usage
	set_stabi_arr(cap, arr, ii++, tot_syn);

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = grps;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		EMU_CK(sub_grp->parent == this);
		sub_grp->calc_stabi_arr_rec(cap, arr, ii);
	}

	//set_stabi_arr(cap, arr, ii++, tot_grp);
}

void 
neurostate::calc_stabi_arr() {
	if(stabi_arr == mc_null){
		stabi_arr_cap = calc_stabi_arr_cap(stabi_set.tot_syn);
		stabi_arr = mc_malloc32(num_syn_t, stabi_arr_cap);
	}
	stabi_arr_sz = 0;
	stabi_set.calc_stabi_arr_rec(stabi_arr_cap, stabi_arr, stabi_arr_sz);
}

int cmp_neurostate(neurostate* nod1, neurostate* nod2){
	EMU_CK(nod1 != mc_null);
	EMU_CK(nod2 != mc_null);
	num_syn_t sz1 = nod1->stabi_arr_sz;
	num_syn_t sz2 = nod2->stabi_arr_sz;
	num_syn_t* arr1 = nod1->stabi_arr;
	num_syn_t* arr2 = nod2->stabi_arr;

	num_syn_t msz = mc_min(sz1, sz2);
	for(num_syn_t aa = 0; aa < msz; aa++){
		num_syn_t v1 = arr1[aa];
		num_syn_t v2 = arr2[aa];
		if(v1 < v2){ return -1; }
		if(v1 > v2){ return 1; }
	}
	if(sz1 < sz2){ return -1; }
	if(sz1 > sz2){ return 1; }
	return 0;
}

void
polaron::stabi_handler(missive* msv){
}

void
neuron::stabi_handler(missive* msv){
	cell* msv_src = msv->src;
	stabi_tok_t tok = (stabi_tok_t)msv->tok;
	MC_MARK_USED(msv_src);
	MC_MARK_USED(tok);

	//nervenet* my_net = bj_nervenet;
	switch(tok){
		case tok_stabi_start:
			stabi_neuron_start();
		break;
		default:
			mck_abort(1, const_cast<char*>("BAD_STABI_TOK"));
		break;
	}
}

void
synapse::stabi_handler(missive* msv){
}

void
nervenet::stabi_handler(missive* msv){
	cell* msv_src = msv->src;
	stabi_tok_t tok = (stabi_tok_t)msv->tok;
	MC_MARK_USED(msv_src);
	MC_MARK_USED(tok);

	//nervenet* my_net = bj_nervenet;
	switch(tok){
		case tok_stabi_start:
			stabi_nervenet_start();
		break;
		default:
			mck_abort(1, const_cast<char*>("BAD_STABI_TOK"));
		break;
	}
}

void
nervenet::stabi_nervenet_start(){
	nervenet* my_net = this;

	binder * fst, * lst, * wrk;

	binder* pt_all_neu = &(all_neu);
	fst = (binder*)(pt_all_neu->bn_right);
	lst = pt_all_neu;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		neuron* my_neu = (neuron*)wrk;
		EMU_CK(my_neu->ki == nd_ccl);
		my_net->send(my_neu, tok_stabi_start);
	}
}

void
neuron::stabi_neuron_start(){
}

neurostate& 
nervenode::get_side(net_side_t sd){
	EMU_CK(sd != side_invalid);
	if(sd == side_left){
		return left_side;
	}
	return right_side;
}

void
synset::stabi_send_snps(mck_token_t tok){
	binder* nn_all_snp = &(all_syn);

	binder * fst, * lst, * wrk;

	fst = (binder*)(nn_all_snp->bn_right);
	lst = nn_all_snp;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synapse* my_snp = (synapse*)wrk;
		my_snp->send(my_snp->mate, tok);
	}
}

void
synset::stabi_rec_send_all(mck_token_t tok){
	stabi_send_snps(tok);

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = grps;
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		EMU_CK(sub_grp->parent == this);
		sub_grp->stabi_rec_send_all(tok);
	}
}

