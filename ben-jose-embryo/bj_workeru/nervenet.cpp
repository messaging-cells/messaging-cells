
#include "cell.hh"
#include "nervenet.hh"

/*
-------------------------------------------------------------
PLLA class_sizes:
synset__40__
tierset__32__
transmitter__32__
stabi_transmitter__40__
sync_transmitter__40__
synapse__48__
neurostate__104__
nervenode__240__
neuron__240__
polaron__248__
sorcell__56__
tierdata__56__
netstate__48__
dbg_stats__32__
nervenet__360__
void_pt__4__
binder__8__
num_syn_t__1__
grip__8__
num_tier_t__4__
mc_flags_t__1__
kernel__328__
agent__16__
cell__24__
missive__32__
agent_ref__24__
agent_grp__32__
test_cls__8__
-------------------------------------------------------------
*/

missive_handler_t bj_nil_handlers[1] = { mc_null };

MCK_DEFINE_ACQUIRE_ALLOC(nervenet, 32);	// defines nervenet::acquire_alloc

MCK_DEFINE_MEM_METHODS_AND_GET_AVA(transmitter, 32, bj_ava_transmitters, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(sornet_transmitter, 32, bj_ava_sornet_transmitters, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(stabi_transmitter, 32, bj_ava_stabi_transmitters, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(sync_transmitter, 32, bj_ava_sync_transmitters, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(synset, 32, bj_ava_synsets, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(tierset, 32, bj_ava_tiersets, bj_num_sep_tiersets)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(synapse, 32, bj_ava_synapses, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(neuron, 32, bj_ava_neurons, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(polaron, 32, bj_ava_polarons, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(sorcell, 32, bj_ava_sorcells, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(tierdata, 32, bj_ava_tierdatas, bj_num_sep_tierdatas)

BJ_DEFINE_GET_CLS_NAM(synset)
BJ_DEFINE_GET_CLS_NAM(tierset)
BJ_DEFINE_GET_CLS_NAM(transmitter)
BJ_DEFINE_GET_CLS_NAM(sornet_transmitter)
BJ_DEFINE_GET_CLS_NAM(stabi_transmitter)
BJ_DEFINE_GET_CLS_NAM(sync_transmitter)
BJ_DEFINE_GET_CLS_NAM(synapse)
BJ_DEFINE_GET_CLS_NAM(nervenode)
BJ_DEFINE_GET_CLS_NAM(neuron)
BJ_DEFINE_GET_CLS_NAM(polaron)
BJ_DEFINE_GET_CLS_NAM(sorcell)
BJ_DEFINE_GET_CLS_NAM(tierdata)
BJ_DEFINE_GET_CLS_NAM(nervenet)


//===================================================================================================
#ifdef MC_IS_PTD_CODE

#define BJ_AUX_STR_MIN_SZ 3

#define bj_aux_stabi_append_str(str, num_prt, pt_str, nxt_sz, ...) \
	num_prt = snprintf(pt_str, nxt_sz, __VA_ARGS__); \
	if(num_prt > (nxt_sz - BJ_AUX_STR_MIN_SZ)){ \
		return str; \
	} \
	pt_str = strchr(pt_str, '\0'); \
	nxt_sz -= num_prt; \

// end_of_macro

char* bj_dbg_stabi_id_arr_to_str(num_syn_t sz1, num_syn_t* arr1, int sz_str, char* str){
	PTD_CK(str != mc_null);
	PTD_CK(sz_str > BJ_AUX_STR_MIN_SZ);

	memset(str, 0, sz_str);
	str[sz_str - 1] = '\0';

	char* pt_str = str;
	int num_prt = 0;
	int nxt_sz = sz_str;

	bj_aux_stabi_append_str(str, num_prt, pt_str, nxt_sz, "[");

	if(arr1 != mc_null){
		for(num_syn_t aa = 0; (aa < sz1); aa++){
			bj_aux_stabi_append_str(str, num_prt, pt_str, nxt_sz, "%d ", arr1[aa]);
		}
	}

	bj_aux_stabi_append_str(str, num_prt, pt_str, nxt_sz, "]");

	return str;
}

void
nervenode::dbg_prt_snp_id(callee_prms& pms){
	bj_dbg_str_stream* out = (bj_dbg_str_stream*)(pms.aux);
	*out << get_ki_str() << id;
}

void 
synset::dbg_rec_prt_synset(net_side_t sd, bj_dbg_str_stream& out){
	out << '(';
	out << (int)tot_syn;

	synapse* snp = get_first_snp(sd);
	if(snp != mc_null){
		nervenode* nd = snp->mate->owner;
		if(snp->stabi_rcv_arr != mc_null){
			bj_dbg_stabi_id_arr_to_str(snp->stabi_rcv_arr_sz, snp->stabi_rcv_arr, 
					BJ_DBG_STR_CAP, bj_nervenet->dbg_str1);
			out << bj_nervenet->dbg_str1;
		} else {
			bj_dbg_stabi_id_arr_to_str(nd->left_side.stabi_arr_sz, nd->left_side.stabi_arr, 
					BJ_DBG_STR_CAP, bj_nervenet->dbg_str1);
			out << "." << bj_nervenet->dbg_str1;
		}
	}
	bj_dbg_str_stream* pt_out = &out;
	with_all_synapses(&(all_syn), &nervenode::dbg_prt_snp_id, sd, true, true, pt_out);

	//out << ' ';


	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = (binder*)mck_as_loc_pt(grps);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		//PTD_CK(sub_grp->parent == this);
		sub_grp->dbg_rec_prt_synset(sd, out);
	}
	out << ')';
}

void
nervenode::dbg_prt_active_synset(net_side_t sd, tier_kind_t tiki, char* prefix, num_tier_t num_ti){
	char* ts = bj_dbg_tier_kind_to_str(tiki);
	neurostate& nst = get_neurostate(sd);

	bj_dbg_str_stream out;
	nst.step_active_set.dbg_rec_prt_synset(sd, out);
	PTD_LOG(" %s_%s_t%d_%s_%d_%s \n", ts, prefix, num_ti, get_ki_str(), id, out.str().c_str());
}


#endif
//---------------------------------------------------------------------------------------------------

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

	tot_sorcells = 0;

	dbg_sornet_curr_cntr = 0;

	net_top = binval_top;
	net_bottom = binval_bottom;

	tot_input_sorcells = 0;
	all_input_sorcells = mc_null;
	tot_rcv_output_sorobjs = 0;
	all_output_sorobjs = mc_null;
}

nervenet::~nervenet(){} 

transmitter::transmitter(){
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_transmitter ++);
	mck_slog2("alloc__transmitter\n");
	//init_me();
} 

transmitter::~transmitter(){} 

void
transmitter::init_me(int caller){
	missive::init_me(caller);
	wrk_side = side_invalid;
	wrk_tier = BJ_INVALID_NUM_TIER;
	//PTD_LOG_STACK((kernel::get_workeru_nn() == 15), "INIT_TRANSMITTER (%p) \n", (void*)this); 
}

//--------------

sornet_transmitter::sornet_transmitter(){
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_sornet_transmitter ++);
	mck_slog2("alloc__sornet_transmitter\n");
	//init_me();
} 

sornet_transmitter::~sornet_transmitter(){} 

void
sornet_transmitter::init_me(int caller){
	transmitter::init_me(caller);
	idx = 0;
	obj = mc_null;
}

//--------------

stabi_transmitter::stabi_transmitter(){
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_stabi_transmitter ++);
	mck_slog2("alloc__stabi_transmitter\n");
	//init_me();
} 

stabi_transmitter::~stabi_transmitter(){} 

void
stabi_transmitter::init_me(int caller){
	transmitter::init_me(caller);
	id_arr_sz = 0;
	id_arr = mc_null;
}

//--------------

sync_transmitter::sync_transmitter(){
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_sync_transmitter ++);
	mck_slog2("alloc__sync_transmitter\n");
	//init_me();
} 

sync_transmitter::~sync_transmitter(){} 

void
sync_transmitter::init_me(int caller){
	transmitter::init_me(caller);
	cfl_src = mc_null;
}

synset::synset(){
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_synset ++);
	mck_slog2("alloc__synset\n");
	init_me();
} 

synset::~synset(){} 

void
synset::init_me(int caller){
	PTD_DBG_CODE(ss_flags = 0);

	num_ss_recv = 0;
	num_ss_ping = 0;

	tot_syn = 0;
}

void 
synset::add_left_synapse(synapse* snp, bool set_vessel){
	PTD_CK(snp != mc_null);
	tot_syn++;
	all_syn.bind_to_my_left(*snp);
	if(set_vessel){
		snp->stabi_vessel = this;
	} else {
		snp->stabi_vessel = mc_null;
	}
}

void 
synset::add_right_synapse(synapse* snp, bool set_vessel){
	PTD_CK(snp != mc_null);
	tot_syn++;
	all_syn.bind_to_my_left(snp->right_handle);
}

tierset::tierset(){
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_tierset ++);
	mck_slog2("alloc__tierset\n");
	init_me();
} 

tierset::~tierset(){} 

void
tierset::init_me(int caller){
	ti_id = BJ_INVALID_NUM_TIER;
}

synapse::synapse(){
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_synapse ++);
	mck_slog2("alloc__synapse\n");
	init_me();
} 

synapse::~synapse(){} 

void
synapse::init_me(int caller){
	handler_idx = idx_synapse;

	stabi_vessel = mc_null;
	stabi_rcv_arr_sz = 0;
	stabi_rcv_arr = mc_null;

	owner = mc_null;
	mate = mc_null;
}

neurostate::neurostate(){ 
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_neurostate ++);
	mck_slog2("alloc__neurostate\n");
	init_me();
} 

neurostate::~neurostate(){} 

void
neurostate::init_me(int caller){
	//side_kind = side_invalid;
	propag_num_tier = 0;

	propag_source = mc_null;

	step_prev_tot_active = 0;

	step_flags = 0;

	step_num_complete = 0;
	step_num_ping = 0;

	stabi_num_tier = 0;
	stabi_arr_cap = 0;
	stabi_arr_sz = 0;
	stabi_arr = mc_null;
}

nervenode::nervenode(){ 
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_nervenode ++);
	mck_slog2("alloc__nervenode\n");
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

neuron::neuron(){
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_neuron ++);
	mck_slog2("alloc__neuron\n");
	init_me();
} 

neuron::~neuron(){} 

void
neuron::init_me(int caller){
	handler_idx = idx_neuron;
}

polaron::polaron(){ 
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_polaron ++);
	mck_slog2("alloc__polaron\n");
	init_me();
} 

polaron::~polaron(){} 

void
polaron::init_me(int caller){
	handler_idx = idx_polaron;
	opp = mc_null; 
}

sorcell::sorcell(){ 
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_sorcell ++);
	mck_slog2("alloc__sorcell\n");
	init_me();
} 

sorcell::~sorcell(){} 

void
sorcell::init_me(int caller){
	handler_idx = idx_sorcell;

	color = 0;

	dbg_level = 0;

	up_idx = 0;
	up_inp = mc_null;
	up_out = mc_null;

	down_idx = 0;
	down_inp = mc_null;
	down_out = mc_null;
}

void bj_print_loaded_poles(grip& all_pol, node_kind_t ki) {
	binder * fst, * lst, * wrk;

	binder* pt_all_pol = &(all_pol);
	fst = (binder*)(pt_all_pol->bn_right);
	lst = (binder*)mck_as_loc_pt(pt_all_pol);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		polaron* my_pol = (polaron*)wrk;
		PTD_CK(my_pol->ki == ki);

		binder* nn_all_snp = &(my_pol->left_side.step_active_set.all_syn);

		mck_slog2("LDPOL.");
		mck_ilog(my_pol->id);
		mck_slog2("{");

		binder * fst2, * lst2, * wrk2;
		fst2 = (binder*)(nn_all_snp->bn_right);
		lst2 = (binder*)mck_as_loc_pt(nn_all_snp);
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
	lst = (binder*)mck_as_loc_pt(pt_all_neu);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		neuron* my_neu = (neuron*)wrk;
		PTD_CK(my_neu->ki == nd_neu);

		binder* nn_all_snp = &(my_neu->left_side.step_active_set.all_syn);

		mck_slog2("n");
		mck_ilog(my_neu->id);
		mck_slog2("[");

		binder * fst2, * lst2, * wrk2;
		fst2 = (binder*)(nn_all_snp->bn_right);
		lst2 = (binder*)mck_as_loc_pt(nn_all_snp);
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

	mck_lock_log();
	mck_slog2("LD_POLARONS={\n");
	bj_print_loaded_poles(my_net->all_pos, nd_pos);
	bj_print_loaded_poles(my_net->all_neg, nd_neg);
	mck_slog2("\n}\n");
	mck_unlock_log();
}

char* net_side_to_str(net_side_t sd){
	char* resp = mc_null;
	switch(sd){
	case side_invalid:
		resp = mc_cstr("side_invalid");
	break;
	case side_left:
		resp = mc_cstr("lft");
	break;
	case side_right:
		resp = mc_cstr("rgt");
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
	case bj_tok_sync_add_tier:
		resp = mc_cstr("bj_tok_sync_add_tier");
	break;
	case bj_tok_sync_inert_child:
		resp = mc_cstr("bj_tok_sync_inert_child");
	break;
	case bj_tok_sync_confl_up_neu:
		resp = mc_cstr("bj_tok_sync_confl_up_neu");
	break;
	case bj_tok_sync_confl_up_pol:
		resp = mc_cstr("bj_tok_sync_confl_up_pol");
	break;
	case bj_tok_sync_confl_down_neu:
		resp = mc_cstr("bj_tok_sync_confl_down_neu");
	break;
	case bj_tok_sync_confl_down_pol:
		resp = mc_cstr("bj_tok_sync_confl_down_pol");
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

char* propag_tok_to_str(propag_tok_t tok){
	char* resp = mc_cstr("UNKNOWN_PROPAG_TOK");

	switch(tok){
	case bj_tok_propag_invalid:
		resp = mc_cstr("bj_tok_propag_invalid");
	break;
	case bj_tok_propag_start:
		resp = mc_cstr("bj_tok_propag_start");
	break;
	case bj_tok_propag_ping:
		resp = mc_cstr("bj_tok_propag_ping");
	break;
	case bj_tok_propag_charge_all:
		resp = mc_cstr("bj_tok_propag_charge_all");
	break;
	case bj_tok_propag_charge_src:
		resp = mc_cstr("bj_tok_propag_charge_src");
	break;
	case bj_tok_propag_tier_done:
		resp = mc_cstr("bj_tok_propag_tier_done");
	break;
	case bj_tok_propag_end:
		resp = mc_cstr("bj_tok_propag_end");
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
	case bj_tok_stabi_rank:
		resp = mc_cstr("bj_tok_stabi_rank");
	break;
	case bj_tok_stabi_tier_done:
		resp = mc_cstr("bj_tok_stabi_tier_done");
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

	init_sync();

	tok_confl = bj_tok_sync_invalid;
	nod_confl = mc_null;
	ti_confl = BJ_INVALID_NUM_TIER;

	//PTD_PRT("SYNC_INIT_DATA TOT_CHLD=%d \n", sync_tot_children);
}

void
netstate::init_sync(){
	sync_is_inactive = false;
	sync_wait_tier = 0;
	sync_is_ending = false;
}

tierdata::tierdata(){
	PTD_CK(bj_nervenet != mc_null);
	PTD_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_tot_new_tierdata ++);
	mck_slog2("alloc__tierdata\n");
	init_me();
} 

tierdata::~tierdata(){} 

void
tierdata::init_me(int caller){
	tdt_id = BJ_INVALID_NUM_TIER;
	tdt_flags = 0;

	num_inert_chdn = 0;

	inp_neus = BJ_INVALID_NUM_NODE;
	off_neus = 0;
	rcv_neus = 0;
	stl_neus = 0;
	dly_neus = 0;
}

void
nervenet::init_sync_cycle(){
	sync_tot_children = mc_map_get_tot_children();
	sync_parent_id = mc_map_get_parent_workeru_id();
	sync_map = mc_map_get_loaded();

	act_left_side.init_sync();
	act_right_side.init_sync();
}

void 
ptd_prt_tok_codes(){
	for(mck_token_t aa = bj_tok_sync_invalid; aa <= bj_tok_propag_end; aa++){
		if(is_sync_tok(aa)){
			PTD_PRT("%d: %s \n", aa, sync_tok_to_str((sync_tok_t)aa));
		}
		else if(is_load_tok(aa)){
			PTD_PRT("%d: %s \n", aa, load_tok_to_str((load_tok_t)aa));
		}
		else if(is_propag_tok(aa)){
			PTD_PRT("%d: %s \n", aa, propag_tok_to_str((propag_tok_t)aa));
		}
		else if(is_stabi_tok(aa)){
			PTD_PRT("%d: %s \n", aa, stabi_tok_to_str((stabi_tok_t)aa));
		}
	}
}

tierset*
neurostate::dbg_get_tiset(grip& all_ti, num_tier_t nti){
	if(all_ti.is_alone()){
		return mc_null;
	}

	if(nti == BJ_INVALID_NUM_TIER){
		return mc_null;
	}

	if(nti == BJ_LAST_TIER){
		PTD_CK(((tierset*)all_ti.bn_left)->ti_id != BJ_INVALID_NUM_TIER);
		return (tierset*)all_ti.bn_left;
	}

	tierset* dat = mc_null;
	binder * fst, * lst, * wrk;

	binder* tis = &(all_ti);
	fst = (binder*)(tis->bn_left);
	lst = (binder*)mck_as_loc_pt(tis);
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
dbg_call_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd, bool from_rec){
	PTD_CK(mth != mc_null);

	binder * fst, * lst, * wrk;

	fst = (binder*)(nn_all_snp->bn_right);
	lst = (binder*)mck_as_loc_pt(nn_all_snp);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synapse* my_snp = mc_null;
		if(sd == side_left){
			my_snp = (synapse*)wrk;
		} else {
			PTD_CK(sd == side_right);
			my_snp = bj_get_syn_of_rgt_handle(wrk);
		}
		PTD_CK(my_snp != mc_null);
		PTD_CK(bj_ck_is_synapse(my_snp));

		callee_prms pms;
		pms.snp = my_snp;
		pms.sd = sd;
		pms.rec = from_rec;

		(my_snp->owner->*mth)(pms);
		//(my_snp->owner->*mth)(my_snp, sd, from_rec);
	}
}

void
synset::dbg_rec_call_all(bj_callee_t mth, net_side_t sd){
	MCK_CHECK_SP();
	dbg_call_all_synapses(&(all_syn), mth, sd, true);

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = (binder*)mck_as_loc_pt(grps);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		//PTD_CK(sub_grp->parent == this);
		sub_grp->dbg_rec_call_all(mth, sd);
	}
}

void
nervenode::dbg_prt_syn(callee_prms& pms){
	MCK_CK(pms.snp->mate != mc_null);

	synapse* mt_snp = (synapse*)(pms.snp->mate);
	nervenode* the_nod = mt_snp->owner;

	mck_ilog(the_nod->id);
	mck_slog2(" ");
}

void
netstate::dbg_prt_all_tiers(tier_kind_t tiki, char* prefix, num_tier_t num_ti){
	//tierdata* dat = mc_null;
	char* ts = bj_dbg_tier_kind_to_str(tiki);
	binder * fst, * lst, * wrk;

	grip& all_tiers = get_all_tiers(tiki);

	mck_lock_log();

	mck_slog2(ts);
	mck_slog2("_");
	if(prefix != mc_null){
		mck_slog2(prefix);
	}
	mck_slog2("_t");
	mck_ilog(num_ti);
	mck_slog2("_");
	mck_slog2(net_side_to_str(my_side));
	mck_slog2("_all_tier=[ ");

	binder* tis = &(all_tiers);
	fst = (binder*)(tis->bn_left);
	lst = (binder*)mck_as_loc_pt(tis);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_left)){
		tierdata* tda = (tierdata*)wrk;
		MC_MARK_USED(tda);
		mck_slog2("_t");
		mck_ilog(tda->tdt_id);
		mck_slog2("_[");
		mck_ilog(tda->inp_neus);
		mck_slog2(",");
		mck_ilog(tda->off_neus);
		mck_slog2(",");
		mck_ilog(tda->rcv_neus);
		mck_slog2(",");
		mck_ilog(tda->stl_neus);
		mck_slog2(",");
		mck_ilog(tda->dly_neus);
		mck_slog2("] ");
	}

	mck_slog2("] \n");

	mck_unlock_log();
}

void
nervenode::dbg_prt_nod(net_side_t sd, tier_kind_t tiki, char* prefix, num_pulse_t num_pul, num_tier_t num_ti){
	if(num_ti == BJ_INVALID_NUM_TIER){
		return;
	}

	bj_callee_t mth = &nervenode::dbg_prt_syn;

	neurostate& ne_stt = get_neurostate(sd);
	tierset* all_ti = ne_stt.dbg_get_tiset(ne_stt.propag_tiers, num_ti);
	
	bool is_mpty = ((all_ti == mc_null) && ne_stt.step_active_set.is_synset_empty());

	if(is_mpty){
		return;
	}

	mck_lock_log();

	if(prefix != mc_null){
		mck_slog2(prefix);
		mck_slog2("_");
	}

	mck_slog2(net_side_to_str(sd));
	mck_slog2("_t");
	mck_ilog(num_ti);
	mck_slog2("_p");
	mck_ilog(num_pul);
	if(ki == nd_neu){
		mck_slog2("n");
	} else {
		mck_slog2("p");
	}
	mck_ilog(id);
	mck_slog2("_");

	if(ki == nd_neu){
		mck_slog2("[");
	} else {
		mck_slog2("{");
	}

	if(all_ti != mc_null){
		binder * fst_2, * lst_2, * wrk_2;

		binder* tis = &(ne_stt.propag_tiers);
		fst_2 = (binder*)(all_ti);
		lst_2 = (binder*)mck_as_loc_pt(tis);
		for(wrk_2 = fst_2; wrk_2 != lst_2; wrk_2 = (binder*)(wrk_2->bn_right)){
			tierset* tidat = (tierset*)wrk_2;
			dbg_call_all_synapses(&(tidat->ti_all), mth, sd, false);
			mck_slog2("+ ");
		}
	}

	ne_stt.step_active_set.dbg_rec_call_all(mth, sd);

	if(ki == nd_neu){
		mck_slog2("]");
	} else {
		mck_slog2("}");
	}

	if((tiki != tiki_invalid) && (ki == nd_neu) && ne_stt.neu_all_ping(tiki)){
		mck_slog2("*");
	}

	if(left_side.stabi_arr != mc_null){
		PTD_DBG_CODE(
			mck_slog2(" id=");
			bj_dbg_stabi_id_arr_to_str(left_side.stabi_arr_sz, left_side.stabi_arr, 
				BJ_DBG_STR_CAP, bj_nervenet->dbg_str1);
			mck_slog(bj_nervenet->dbg_str1);
		);
	}

	mck_slog2("\n");

	mck_unlock_log();
}

void 
bj_print_active_cnf(net_side_t sd, tier_kind_t tiki, char* prefix, num_pulse_t num_pul, num_tier_t num_ti,
		mc_flags_t prt_flgs)
{
	nervenet* my_net = bj_nervenet;

	binder * fst, * lst, * wrk;

	bool with_neus = mc_get_flag(prt_flgs, bj_dbg_prt_nd_neu_flag);
	if(with_neus){ 
		binder* pt_all_neu = &(my_net->all_neu);
		fst = (binder*)(pt_all_neu->bn_right);
		lst = (binder*)mck_as_loc_pt(pt_all_neu);
		for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
			neuron* my_neu = (neuron*)wrk;
			PTD_CK(my_neu->ki == nd_neu);

			my_neu->dbg_prt_nod(sd, tiki, prefix, num_pul, num_ti);
		}
	}

	bool with_pols = mc_get_flag(prt_flgs, bj_dbg_prt_nd_pol_flag);
	if(with_pols){ 
		binder* pt_all_pos = &(my_net->all_pos);
		fst = (binder*)(pt_all_pos->bn_right);
		lst = (binder*)mck_as_loc_pt(pt_all_pos);
		for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
			nervenode* my_nd = (nervenode*)wrk;
			PTD_CK(my_nd->ki == nd_pos);

			my_nd->dbg_prt_nod(sd, tiki, prefix, num_pul, num_ti);
		}

		binder* pt_all_neg = &(my_net->all_neg);
		fst = (binder*)(pt_all_neg->bn_right);
		lst = (binder*)mck_as_loc_pt(pt_all_neg);
		for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
			nervenode* my_nd = (nervenode*)wrk;
			PTD_CK(my_nd->ki == nd_neg);

			my_nd->dbg_prt_nod(sd, tiki, prefix, num_pul, num_ti);
		}
	}

	bool with_pol_ids = mc_get_flag(prt_flgs, bj_dbg_prt_id_pol_flag);
	if(with_pol_ids){ 
		mck_lock_log();
		if(prefix != mc_null){
			mck_slog2(prefix);
		}
		mck_slog2("_ALL_POL={");

		binder* pt_all_pol = &(my_net->all_pos);
		fst = (binder*)(pt_all_pol->bn_right);
		lst = (binder*)mck_as_loc_pt(pt_all_pol);
		for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
			polaron* my_pos = (polaron*)wrk;
			PTD_CK(my_pos->ki == nd_pos);

			mck_ilog(my_pos->id);
			mck_slog2(" ");
		}

		pt_all_pol = &(my_net->all_neg);
		fst = (binder*)(pt_all_pol->bn_right);
		lst = (binder*)mck_as_loc_pt(pt_all_pol);
		for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
			polaron* my_neg = (polaron*)wrk;
			PTD_CK(my_neg->ki == nd_neg);

			mck_ilog(my_neg->id);
			mck_slog2(" ");
		}

		mck_slog2("}\n");
		mck_unlock_log();
	}
}

dbg_stats::dbg_stats(){
	init_me();
}

dbg_stats::~dbg_stats(){}

void
dbg_stats::init_me(int caller){
	dbg_tot_new_synset = 0;
	dbg_tot_new_tierset = 0;
	dbg_tot_new_transmitter = 0;
	dbg_tot_new_stabi_transmitter = 0;
	dbg_tot_new_sync_transmitter = 0;
	dbg_tot_new_synapse = 0;
	dbg_tot_new_neurostate = 0;
	dbg_tot_new_nervenode = 0;
	dbg_tot_new_neuron = 0;
	dbg_tot_new_polaron = 0;
	dbg_tot_new_sorcell = 0;
	dbg_tot_new_tierdata = 0;
}

void
dbg_stats::dbg_prt_all(){
	PTD_LOG("dbg_tot_new_synset = %d \n", dbg_tot_new_synset);
	PTD_LOG("dbg_tot_new_tierset = %d \n", dbg_tot_new_tierset);
	PTD_LOG("dbg_tot_new_transmitter = %d \n", dbg_tot_new_transmitter);
	PTD_LOG("dbg_tot_new_stabi_transmitter = %d \n", dbg_tot_new_stabi_transmitter);
	PTD_LOG("dbg_tot_new_sync_transmitter = %d \n", dbg_tot_new_sync_transmitter);
	PTD_LOG("dbg_tot_new_synapse = %d \n", dbg_tot_new_synapse);
	PTD_LOG("dbg_tot_new_neurostate = %d \n", dbg_tot_new_neurostate);
	PTD_LOG("dbg_tot_new_nervenode = %d \n", dbg_tot_new_nervenode);
	PTD_LOG("dbg_tot_new_neuron = %d \n", dbg_tot_new_neuron);
	PTD_LOG("dbg_tot_new_polaron = %d \n", dbg_tot_new_polaron);
	PTD_LOG("dbg_tot_new_sorcell = %d \n", dbg_tot_new_sorcell);
	PTD_LOG("dbg_tot_new_tierdata = %d \n", dbg_tot_new_tierdata);
}

class mc_aligned test_cls {
public:
	num_syn_t		field_1;

	test_cls(){};
	~test_cls(){};
};

void bj_print_class_szs(){
	if(kernel::get_workeru_nn() == 0){
		mck_slog2("-------------------------------------------------------------\n");
		mck_slog2("class_sizes:\n");
		mck_slog2("synset__");
		mck_ilog(sizeof(synset));
		mck_slog2("__\n");
		mck_slog2("tierset__");
		mck_ilog(sizeof(tierset));
		mck_slog2("__\n");
		mck_slog2("transmitter__");
		mck_ilog(sizeof(transmitter));
		mck_slog2("__\n");
		mck_slog2("stabi_transmitter__");
		mck_ilog(sizeof(stabi_transmitter));
		mck_slog2("__\n");
		mck_slog2("sync_transmitter__");
		mck_ilog(sizeof(sync_transmitter));
		mck_slog2("__\n");
		mck_slog2("synapse__");
		mck_ilog(sizeof(synapse));
		mck_slog2("__\n");
		mck_slog2("neurostate__");
		mck_ilog(sizeof(neurostate));
		mck_slog2("__\n");
		mck_slog2("nervenode__");
		mck_ilog(sizeof(nervenode));
		mck_slog2("__\n");
		mck_slog2("neuron__");
		mck_ilog(sizeof(neuron));
		mck_slog2("__\n");
		mck_slog2("polaron__");
		mck_ilog(sizeof(polaron));
		mck_slog2("__\n");
		mck_slog2("sorcell__");
		mck_ilog(sizeof(sorcell));
		mck_slog2("__\n");
		mck_slog2("tierdata__");
		mck_ilog(sizeof(tierdata));
		mck_slog2("__\n");
		mck_slog2("netstate__");
		mck_ilog(sizeof(netstate));
		mck_slog2("__\n");
		mck_slog2("dbg_stats__");
		mck_ilog(sizeof(dbg_stats));
		mck_slog2("__\n");
		mck_slog2("nervenet__");
		mck_ilog(sizeof(nervenet));
		mck_slog2("__\n");
		mck_slog2("void_pt__");
		mck_ilog(sizeof(void*));
		mck_slog2("__\n");
		mck_slog2("binder__");
		mck_ilog(sizeof(binder));
		mck_slog2("__\n");
		mck_slog2("num_syn_t__");
		mck_ilog(sizeof(num_syn_t));
		mck_slog2("__\n");
		mck_slog2("grip__");
		mck_ilog(sizeof(grip));
		mck_slog2("__\n");
		mck_slog2("num_tier_t__");
		mck_ilog(sizeof(num_tier_t));
		mck_slog2("__\n");
		mck_slog2("mc_flags_t__");
		mck_ilog(sizeof(mc_flags_t));
		mck_slog2("__\n");
		mck_slog2("kernel__");
		mck_ilog(sizeof(kernel));
		mck_slog2("__\n");
		mck_slog2("agent__");
		mck_ilog(sizeof(agent));
		mck_slog2("__\n");
		mck_slog2("cell__");
		mck_ilog(sizeof(cell));
		mck_slog2("__\n");
		mck_slog2("missive__");
		mck_ilog(sizeof(missive));
		mck_slog2("__\n");
		mck_slog2("agent_ref__");
		mck_ilog(sizeof(agent_ref));
		mck_slog2("__\n");
		mck_slog2("agent_grp__");
		mck_ilog(sizeof(agent_grp));
		mck_slog2("__\n");
		mck_slog2("test_cls__");
		mck_ilog(sizeof(test_cls));
		mck_slog2("__\n");

		mck_slog2("-------------------------------------------------------------\n");
	}
}

netstate& 
nervenet::get_active_netstate(net_side_t sd){
	PTD_CK(sd != side_invalid);

	netstate* out_stt = &act_left_side;
	if(sd == side_right){
		out_stt = &act_right_side;
	}
	PTD_CK(out_stt != mc_null);
	return *out_stt;
}

neurostate& 
nervenode::get_neurostate(net_side_t sd){
	PTD_CK(sd != side_invalid);

	neurostate* out_stt = &left_side;
	if(sd == side_right){
		out_stt = &right_side;
	}
	PTD_CK(out_stt != mc_null);
	return *out_stt;
}

synapse*
get_synapse_from_binder(net_side_t sd, binder* bdr){
	EPH_CODE(MCK_CK(! mc_addr_has_id(bdr)));
	synapse* my_snp = mc_null;
	if(sd == side_left){
		my_snp = (synapse*)bdr;
	} else {
		PTD_CK(sd == side_right);
		my_snp = bj_get_syn_of_rgt_handle(bdr);
	}
	PTD_CK(my_snp != mc_null);
	PTD_CK(bj_ck_is_synapse(my_snp));
	MCK_CK(my_snp->owner->ki != nd_invalid);
	return my_snp;
}

void 
with_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd, 
			bool from_rec, bool dbg_mates, void* aux)
{
	PTD_CK(mth != mc_null);

	binder * fst, * lst, * wrk, * nxt;

	fst = (binder*)(nn_all_snp->bn_right);
	lst = (binder*)mck_as_loc_pt(nn_all_snp);
	for(wrk = fst; wrk != lst; wrk = nxt){
		nxt = (binder*)(wrk->bn_right);
		synapse* my_snp = get_synapse_from_binder(sd, wrk);

		if(dbg_mates){
			PTD_DBG_CODE(my_snp = my_snp->mate);
		}

		callee_prms pms;
		pms.snp = my_snp;
		pms.sd = sd;
		pms.rec = from_rec;
		pms.aux = aux;

		(my_snp->owner->*mth)(pms);
	}
}

void
synset::transmitter_send_all_rec(bj_callee_t mth, net_side_t sd){
	MCK_CHECK_SP();
	//MCK_CK(! mc_addr_has_id(this));
	//MCK_CK(! mc_addr_has_id(&(all_syn)));
	//MCK_CK(! mc_addr_has_id(&(all_grp)));
	with_all_synapses(&(all_syn), mth, sd, true /* IS_FROM_REC */);

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = (binder*)mck_as_loc_pt(grps);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		//PTD_CK(sub_grp->parent == this);
		sub_grp->transmitter_send_all_rec(mth, sd);
	}
}

void
netstate::send_sync_transmitter(tier_kind_t tiki, nervenet* the_dst, sync_tok_t the_tok, num_tier_t the_ti, 
			nervenode* the_cfl_src)
{
	PTD_CODE(char* ts = bj_dbg_tier_kind_to_str(tiki); MC_MARK_USED(ts););

	sync_transmitter* trm = sync_transmitter::acquire();
	trm->src = bj_nervenet;
	trm->dst = the_dst;
	trm->tok = the_tok;
	trm->wrk_side = my_side;
	trm->wrk_tier = the_ti;
	trm->cfl_src = the_cfl_src;
	trm->send();

	PTD_CODE(mc_workeru_nn_t dbg_dst_nn = mc_id_to_nn(mc_addr_get_id(the_dst)); MC_MARK_USED(dbg_dst_nn););
	SYNC_LOG(" %s_SYNCR_send_transmitter_%s_t%d_%s_ [%ld ->> %ld] \n", ts, 
		net_side_to_str(my_side), the_ti, sync_tok_to_str(the_tok), kernel::get_workeru_nn(), dbg_dst_nn);
	PTD_CK(the_ti != BJ_INVALID_NUM_TIER);
}

nervenet*
nervenet::get_nervenet(mc_workeru_id_t id){
	nervenet* rem_net = (nervenet*)mc_addr_set_id(id, this);
	return rem_net;
}

bool
nervenode::is_tier_complete(signal_data* dat){
	neurostate& stt = get_neurostate(dat->sd);
	return stt.is_full();
}

bool
polaron::is_tier_complete(signal_data* dat){
	neurostate& pol_stt = get_neurostate(dat->sd);
	neurostate& opp_stt = opp->get_neurostate(dat->sd);

	bool both_full = pol_stt.is_full() && opp_stt.is_full();
	return both_full;
}

void
neurostate::step_reset_complete(){
	PTD_LOG("::step_reset_complete flags=%p flgs_pt=%p \n", (void*)(uintptr_t)step_flags, 
			(void*)(&step_flags));

	//step_flags = 0;
	mc_reset_flag(step_flags, bj_stt_charge_all_flag);

	step_num_complete = 0;
	step_num_ping = 0;
	step_prev_tot_active = step_active_set.tot_syn;
}

void
synset::reset_rec_tree(){
	MCK_CHECK_SP();
	while(! all_grp.is_alone()){
		synset* sub_grp = (synset*)(binder*)(all_grp.bn_right);
		//PTD_CK(sub_grp->parent == this);
		sub_grp->reset_rec_tree();

		PTD_CK(sub_grp->all_grp.is_alone());
		all_syn.move_all_to_my_right(sub_grp->all_syn);
		sub_grp->release();
	}
}

void
nervenet::send_all_neus(mck_token_t tok){
	nervenet* my_net = this;

	binder * fst, * lst, * wrk;

	binder* pt_all_neu = &(all_neu);
	fst = (binder*)(pt_all_neu->bn_right);
	lst = (binder*)mck_as_loc_pt(pt_all_neu);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		neuron* my_neu = (neuron*)wrk;
		PTD_CK(my_neu->ki == nd_neu);
		my_net->send(my_neu, tok);
	}
}

void
netstate::broadcast_tier(tier_kind_t tiki, tierdata& lti, int dbg_caller){
	mc_workeru_id_t pnt_id = bj_nervenet->sync_parent_id;
	if(pnt_id != 0){
		nervenet* pnt_net = bj_nervenet->get_nervenet(pnt_id);
		send_sync_transmitter(tiki, pnt_net, bj_tok_sync_add_tier, lti.tdt_id, mc_null);
	} 
	send_sync_to_children(bj_tok_sync_add_tier, lti.tdt_id, tiki, mc_null);
}

bool
neurostate::neu_is_to_delay(netstate& nstt, nervenode* nd, tier_kind_t tiki, 
		num_tier_t the_ti, grip& all_ti, int dbg_caller)
{ 
	PTD_CODE(char* ts = bj_dbg_tier_kind_to_str(tiki); MC_MARK_USED(ts););

	PTD_CK(the_ti != BJ_INVALID_NUM_TIER);
	
	num_tier_t ti = the_ti - 1;
	tierdata& lti = get_last_tier(all_ti);

	lti.update_tidat();

	bool to_dly = neu_all_ping(tiki);
	if(tiki == tiki_stabi){
		bool is_itct = mc_get_flag(step_flags, bj_stt_stabi_intact_id_flag);
		to_dly = (to_dly && is_itct);
	}

	if(to_dly && (lti.tdt_id < ti)){
		PTD_CK_PRT(is_alone(), "cllr=%d", dbg_caller);
		lti.dly_neus++;
		lti.all_delayed.bind_to_my_left(*this);
		return true;
	}

	tierdata& tda = nstt.get_tier(tiki, all_ti, ti, 14);

	SYNC_LOG(" %s_TO_DELAY_t%d_%s_%ld %s_%s ((%d > 0) && (%d == %d) && (t%d >= t%d)) %s \n", 
		ts, ti, node_kind_to_str(nd->ki), nd->id, ts, ((to_dly)?("INC_STILL"):("")), 
		step_prev_tot_active, step_num_ping, step_prev_tot_active, lti.tdt_id, ti,
		(mc_get_flag(step_flags, bj_stt_stabi_intact_id_flag))?("intact"):("")
	);
	SYNC_CODE(bj_nervenet->act_left_side.dbg_prt_all_tiers(tiki, mc_cstr("TO_DELAY_"), ti));

	tda.inc_rcv();
	/*
	if(to_dly){
		tda.stl_neus++;
	} else {
		tda.inc_rcv();
	}*/

	return false;
}

void
inc_tier(tier_kind_t tiki, grip& all_ti, net_side_t sd, int dbg_caller){
	PTD_CODE(char* ts = bj_dbg_tier_kind_to_str(tiki); MC_MARK_USED(ts););

	tierdata& lti = get_last_tier(all_ti);

	lti.update_tidat();

	tierdata* ti_dat = tierdata::acquire();
	ti_dat->tdt_id = lti.tdt_id + 1;

	all_ti.bind_to_my_left(*ti_dat);

	PTD_LOG("%s_INC_NET_TIER_%s_t%d (cllr=%d)\n", ts, net_side_to_str(sd), ti_dat->tdt_id, dbg_caller);

	mck_slog2("inc_tier__");
	mck_ilog(ti_dat->tdt_id);
	mck_slog2("__\n");

	ti_dat->update_tidat();

	lti.proc_delayed(tiki, all_ti, sd, true);
	ti_dat->all_delayed.move_all_to_my_right(lti.all_delayed);
	ti_dat->dly_neus = lti.dly_neus;
	lti.dly_neus = 0;

	PTD_CK(lti.all_delayed.is_alone());

}

tierdata&
netstate::get_tier(tier_kind_t tiki, grip& all_ti, num_tier_t nti, int dbg_caller){
	PTD_CK(! all_ti.is_alone());
	PTD_CK(nti != BJ_INVALID_NUM_TIER);

	tierdata* dat = mc_null;
	binder * fst, * lst, * wrk;

	binder* tis = &(all_ti);
	if(nti == BJ_LAST_TIER){
		dat = (tierdata*)(binder*)(tis->bn_left);
	}

	if(dat == mc_null){
		fst = (binder*)(tis->bn_left);
		lst = (binder*)mck_as_loc_pt(tis);
		for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_left)){
			tierdata* tidat = (tierdata*)wrk;
			if(tidat->tdt_id == nti){
				dat = tidat;
				break;
			}
			if(tidat->tdt_id < nti){
				break;
			}
		}
	}

	if(dat == mc_null){
		mck_slog2("CALC_TIER__");
		mck_ilog(dbg_caller);
		mck_slog2("__\n");
		while(get_last_tier(all_ti).tdt_id < nti){
			inc_tier(tiki, all_ti, my_side, dbg_caller);
		}
		tierdata& lti = get_last_tier(all_ti);
		broadcast_tier(tiki, lti, dbg_caller);
		dat = (tierdata*)(all_ti.bn_left);
	}

	PTD_CK(dat != mc_null);
	PTD_CK_PRT((dat->tdt_id == nti), "(%d == %d)",  dat->tdt_id, nti);

	dat->update_tidat();
	return *dat;
}

void
tierdata::proc_delayed(tier_kind_t tiki, grip& all_ti, net_side_t sd, bool star_nxt_ti){
	binder * fst, * lst, * wrk, * nxt;

	netstate& nstt = bj_nervenet->get_active_netstate(sd);

	binder* dlyd = &(all_delayed);
	fst = (binder*)(dlyd->bn_right);
	lst = (binder*)mck_as_loc_pt(dlyd);
	for(wrk = fst; wrk != lst; wrk = nxt){
		neurostate* stt = (neurostate*)wrk;
		nxt = (binder*)(wrk->bn_right);

		if(! star_nxt_ti){
			dly_neus--;
			stt->let_go();
			continue;
		}

		num_tier_t the_ti = BJ_INVALID_NUM_TIER;
		mck_token_t tok = BJ_INVALID_TOKEN;
		switch(tiki){
			case tiki_propag: 
				the_ti = stt->propag_num_tier;
				tok = bj_tok_propag_tier_done;
			break;
			case tiki_stabi: 
				the_ti = stt->stabi_num_tier;
				tok = bj_tok_stabi_tier_done;
			break;
			default: 
			break;
		}

		//PTD_CK(false);
		//PTD_CK_PRT((tdt_id == (the_ti - 1)), "FAILED (%d != %d)", tdt_id, (the_ti - 1));
		nervenode* nd = mc_null;
		if(sd == side_left){
			nd = bj_get_nod_of_pt_lft_st(stt);
		} else {
			PTD_CK(sd == side_right);
			nd = bj_get_nod_of_pt_lft_st(stt);
		}
		PTD_CK(nd->ki == nd_neu);

		bool to_dly = stt->neu_is_to_delay(nstt, nd, tiki, the_ti, all_ti, 1);
		PTD_CK(! to_dly);
		if(! to_dly){
			dly_neus--;
			stt->let_go();

			signal_data dat;
			dat.tok = tok;
			dat.sd = sd;
			dat.ti = the_ti - 1;

			switch(tiki){
				case tiki_propag: 
					nd->propag_start_nxt_tier(&dat);
				break;
				case tiki_stabi: 
					nd->stabi_start_nxt_tier(&dat);
				break;
				default: 
				break;
			}

			SYNC_LOG(" %s_SYNCR_UPDTING_DELAYED_%s_t%d_%s_%ld \n", bj_dbg_tier_kind_to_str(tiki), 
				net_side_to_str(dat.sd), dat.ti, node_kind_to_str(nd->ki), nd->id);
		}
	}
}

grip&
netstate::get_all_tiers(tier_kind_t tiki){
	grip* all_tiers_pt = mc_null;
	switch(tiki){
		case tiki_propag: 
			all_tiers_pt = &(all_propag_tiers);
		break;
		case tiki_stabi: 
			all_tiers_pt = &(all_stabi_tiers);
		break;
		default: 
		break;
	}
	PTD_CK(all_tiers_pt != mc_null);
	return *all_tiers_pt;
}

void 
netstate::send_sync_to_children(sync_tok_t the_tok, num_tier_t the_ti, tier_kind_t tiki, nervenode* the_cfl)
{
	PTD_CODE(char* ts = bj_dbg_tier_kind_to_str(tiki); MC_MARK_USED(ts););
	SYNC_LOG(" %s_SYNCR_STOP_CHILDREN_%s_t%d_ WORKERU=%d \n", ts, net_side_to_str(my_side), 
			the_ti, kernel::get_workeru_nn());

	PTD_CK(the_ti != BJ_INVALID_NUM_TIER);

	if(the_cfl != mc_null){
		PTD_CK((the_tok == bj_tok_sync_confl_down_neu) || (the_tok == bj_tok_sync_confl_down_pol));
		tok_confl = the_tok;
		nod_confl = the_cfl;
		ti_confl = the_ti;

		PTD_LOG(" %s_SYNCR_CONFLICT_%s_t%d_%s confl_pt=%p \n", ts, 
				net_side_to_str(my_side), the_ti, 
				sync_tok_to_str(bj_tok_sync_confl_down_pol), (void*)nod_confl);
	}

	mc_load_map_st** my_children = bj_nervenet->sync_map->childs;
	if(my_children != mc_null){ 
		int aa = 0;
		mc_load_map_st* ch_map = (my_children)[aa];
		while(ch_map != mc_null){
			mc_workeru_nn_t chd_nn = ch_map->num_workeru;
			nervenet* ch_net = bj_nervenet->get_nervenet(mc_nn_to_id(chd_nn));
			send_sync_transmitter(tiki, ch_net, the_tok, the_ti, the_cfl);

			aa++;
			ch_map = (my_children)[aa];
		}
	}

	if(the_tok == bj_tok_sync_to_children){
		PTD_LOG(" %s_SYNCR_END_%s_t%d \n", ts, net_side_to_str(my_side), the_ti);

		sync_is_ending = true;
		sync_is_inactive = true;
	}
}

void 
tierdata::update_tidat(){
	if(tdt_id == 0){
		return;
	}
	tierdata* prv = (tierdata*)(bn_left);
	if((inp_neus == BJ_INVALID_NUM_NODE) && prv->got_all_neus()){
		PTD_CK(prv->inp_neus != BJ_INVALID_NUM_NODE);
		inp_neus = prv->inp_neus - prv->off_neus;
		PTD_CK(inp_neus != BJ_INVALID_NUM_NODE);
		PTD_LOG(" UPDATED_TIER_%d inp_neus=%d \n", tdt_id, inp_neus);
		//PTD_CK(stl_neus >= 0);
	}
}

char*
nervenode::get_ki_str(){
	if(ki == nd_neu){ return mc_cstr("n"); }
	return mc_cstr("p");
}

char* 
bj_dbg_tier_kind_to_str(tier_kind_t tiki){
	char* resp = mc_null;
	switch(tiki){
	case tiki_invalid:
		resp = mc_cstr("inv");
	break;
	case tiki_propag:
		resp = mc_cstr("prp");
	break;
	case tiki_stabi:
		resp = mc_cstr("stb");
	break;
	}
	PTD_CK(resp != mc_null);
	return resp;
}

void
nervenet::sync_handler(tier_kind_t tiki, missive* msv){
	PTD_CODE(char* ts = bj_dbg_tier_kind_to_str(tiki); MC_MARK_USED(ts););

	mck_token_t msv_tok = msv->tok;

	sync_transmitter* sy_tmt = (sync_transmitter*)msv;
	net_side_t tmt_sd = sy_tmt->wrk_side;
	num_tier_t tmt_ti = sy_tmt->wrk_tier;
	nervenode* tmt_cfl = sy_tmt->cfl_src;

	PTD_CK(tmt_ti != BJ_INVALID_NUM_TIER);
	PTD_CK(tmt_sd != side_invalid);

	netstate& nst = get_active_netstate(tmt_sd);

	grip& all_tiers = nst.get_all_tiers(tiki);

	tierdata& lti = get_last_tier(all_tiers);

	lti.update_tidat();

	SYNC_LOG(" %s_SYNCR_RECV_%s_t%d_%s_ [%d <<- %d] lti=%d cf=%p chdn=(%d of %d) %s\n", ts, 
		net_side_to_str(tmt_sd), tmt_ti, sync_tok_to_str((sync_tok_t)(msv_tok)), 
		kernel::get_workeru_nn(), mc_id_to_nn(mc_addr_get_id(msv->src)), 
		lti.tdt_id, tmt_cfl, lti.num_inert_chdn, bj_nervenet->sync_tot_children,
		((tmt_ti < lti.tdt_id)?("OLDER_TIER"):(""))
	);

	//if(tmt_ti < lti.tdt_id){
	if((tmt_ti < lti.tdt_id) && (msv_tok != bj_tok_sync_to_children)){
		PTD_CK_PRT((msv_tok != bj_tok_sync_to_children), "(%d < %d) \n", tmt_ti, lti.tdt_id);
		return;
	}

	tierdata& tdt = nst.get_tier(tiki, all_tiers, tmt_ti, 12);
	MC_MARK_USED(tdt);
	//PTD_CK(is_last_tier(all_tiers, tdt));

	switch(msv_tok){
		case bj_tok_sync_add_tier:
		break;
		case bj_tok_sync_inert_child:
			tdt.num_inert_chdn++;
			SYNC_LOG(" %s_SYNCR_RCV_INERT_%s_t%d_dt%d_nt%d_ chdn=(%d of %d)\n", ts, 
				net_side_to_str(tmt_sd), tmt_ti, tdt.tdt_id, nst.sync_wait_tier,
				tdt.num_inert_chdn, bj_nervenet->sync_tot_children);
		break;

		case bj_tok_sync_confl_up_neu:
			nst.send_up_confl_tok(bj_tok_sync_confl_up_neu, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_confl_up_pol:
			nst.send_up_confl_tok(bj_tok_sync_confl_up_pol, tmt_ti, tmt_cfl);
		break;
		case bj_tok_sync_confl_down_neu:
			nst.send_sync_to_children(bj_tok_sync_confl_down_neu, tmt_ti, tiki, tmt_cfl);
		break;
		case bj_tok_sync_confl_down_pol:
			nst.send_sync_to_children(bj_tok_sync_confl_down_pol, tmt_ti, tiki, tmt_cfl);
		break;
		case bj_tok_sync_to_children:
			nst.send_sync_to_children(bj_tok_sync_to_children, tmt_ti, tiki, mc_null);
		break;
		default:
			mck_abort(1, mc_cstr("BAD_SYNC_TOK"));
		break;
	}

	nst.update_sync_inert(tiki);
}

void
netstate::update_sync_inert(tier_kind_t tiki, bool remove_full){ 
	PTD_CODE(char* ts = bj_dbg_tier_kind_to_str(tiki); MC_MARK_USED(ts););

	if(sync_is_inactive){
		SYNC_LOG(" %s_SYNCR_sync_is_inactive_%s_t%d_\n", ts, net_side_to_str(my_side), sync_wait_tier);
		return;
	}
	grip& all_tiers = get_all_tiers(tiki);

	tierdata& wt_tdt = get_tier(tiki, all_tiers, sync_wait_tier, 13);
	PTD_CK(wt_tdt.tdt_id == sync_wait_tier);
	PTD_CK(sync_wait_tier >= 0);

	if(! wt_tdt.got_all_neus()){ 
		SYNC_LOG(" %s_SYNCR_NO_snd_to_pnt_%s_t%d_not_got_all_NEUS [%d,%d,%d,%d,%d] \n", 
			ts, net_side_to_str(my_side), sync_wait_tier, 
			wt_tdt.inp_neus, wt_tdt.off_neus, wt_tdt.rcv_neus, wt_tdt.stl_neus, wt_tdt.dly_neus
		);
		return; 
	}
	PTD_CK(wt_tdt.inp_neus != BJ_INVALID_NUM_NODE);

	nervenet* the_net = bj_nervenet;

	if(! is_last_tier(all_tiers, wt_tdt)){
		SYNC_LOG(" %s_SYNCR_NO_snd_to_pnt_%s_t%d_not_is_last_tier \n", 
				ts, net_side_to_str(my_side), wt_tdt.tdt_id);
		PTD_CK(wt_tdt.all_delayed.is_alone());
		if(remove_full && ! wt_tdt.is_first_tier(all_tiers)){
			wt_tdt.prv_tier().release();
		}
		sync_wait_tier++;
		return;
	}

	mc_workeru_nn_t tot_chdn = the_net->sync_tot_children;

	if(wt_tdt.num_inert_chdn < tot_chdn){
		SYNC_LOG(" %s_SYNCR_NO_snd_to_pnt_%s_t%d_not_all_inert_chdn (%d < %d) \n", ts, 
			net_side_to_str(my_side), sync_wait_tier, wt_tdt.num_inert_chdn, tot_chdn);
		return;
	}
	PTD_CK(wt_tdt.num_inert_chdn == tot_chdn);

	if(! wt_tdt.is_inert() && ! wt_tdt.is_tidat_empty()){
		SYNC_LOG(" %s_SYNCR_NO_snd_to_pnt_%s_t%d_not_is_inert [%d,%d,%d,%d,%d] \n", ts, 
			net_side_to_str(my_side), sync_wait_tier, 
			wt_tdt.inp_neus, wt_tdt.off_neus, wt_tdt.rcv_neus, wt_tdt.stl_neus, wt_tdt.dly_neus
		);
		return;
	}

	bool already_sent = mc_get_flag(wt_tdt.tdt_flags, bj_sent_inert_flag);
	if(already_sent){ 
		SYNC_LOG(" %s_SYNCR_already_sent_%s_t%d_\n", ts, net_side_to_str(my_side), sync_wait_tier);
		return; 
	}
	mc_set_flag(wt_tdt.tdt_flags, bj_sent_inert_flag);

	SYNC_LOG(" %s_SYNCR_GOT_is_inert_%s_t%d [%d,%d,%d,%d,%d] \n", ts, net_side_to_str(my_side), wt_tdt.tdt_id,
		wt_tdt.inp_neus, wt_tdt.off_neus, wt_tdt.rcv_neus, wt_tdt.stl_neus, wt_tdt.dly_neus
	);

	mc_workeru_id_t pnt_id = the_net->sync_parent_id;
	if(pnt_id != 0){
		nervenet* pnt_net = the_net->get_nervenet(pnt_id);
		send_sync_transmitter(tiki, pnt_net, bj_tok_sync_inert_child, wt_tdt.tdt_id);
	} else {
		send_sync_to_children(bj_tok_sync_to_children, wt_tdt.tdt_id, tiki, mc_null);
	}
}

synapse*
synset::get_first_snp(net_side_t sd){
	if(all_syn.is_alone()){
		return mc_null;
	}
	binder* fst = (binder*)(all_syn.bn_right);
	synapse* snp = get_synapse_from_binder(sd, fst);
	return snp;
}

void
synset::reset_vessels(bool set_vessel){
	PTD_CK(all_grp.is_alone());

	binder* nn_all_snp = &all_syn;
	binder * fst, * lst, * wrk;

	fst = (binder*)(nn_all_snp->bn_right);
	lst = (binder*)mck_as_loc_pt(nn_all_snp);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synapse* my_snp = get_synapse_from_binder(side_left, wrk);
		synset* val = mc_null;
		if(set_vessel){ val = this; }
		my_snp->stabi_vessel = val;
	}
}

int
bj_cmp_num_syn(num_syn_t const & n1, num_syn_t const & n2){ 
	if(n1 == n2){ return 0; }
	if(n1 < n2){ return -1; }
	return 1;
}

bool 
bj_is_sorted(grip& grp, bj_cmp_func_t cmp_fn, int ord){
	binder* all_bn = &grp;
	binder * fst, * lst, * wrk;

	bool sted = true;

	fst = (binder*)(all_bn->bn_right);
	lst = (binder*)mck_as_loc_pt(all_bn);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		if(wrk == fst){
			continue;
		}
		int vc = (*cmp_fn)(wrk->bn_left, wrk);
		if(vc == 0){ continue; }
		if(ord < 0){
			if(vc > 0){
				sted = false;
				break;
			}
		} else {
			if(vc < 0){
				sted = false;
				break;
			}
		}
	}

	return sted;
}

int 
bj_dbg_cmp_synset_by_arr_id(binder* obj1, binder* obj2){
	return 0;
}

int 
bj_dbg_cmp_synset_by_tot_syn(binder* obj1, binder* obj2){
	return 0;
}
