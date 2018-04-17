
#include "cell.hh"
#include "stabi.hh"

#define BJ_DBG_STABI_MAX_TIER 10

void 
synapse_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(synapse, stabi_handler, msv);
}

void 
nervenet_stabi_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, stabi_handler, msv);
}


void bj_stabi_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_synapse] = synapse_stabi_handler;
	hndlrs[idx_nervenet] = nervenet_stabi_handler;

	kernel::set_handlers(idx_total, hndlrs);
}

void
synapse::stabi_handler(missive* msv){
	signal_data dat;
	dat.trm = (transmitter*)msv;
	dat.snp = this;
	dat.tok = (stabi_tok_t)(dat.trm)->tok;
	//dat.sd = (dat.trm)->wrk_side;
	dat.ti = (dat.trm)->wrk_tier;

	EMU_CK((dat.trm)->wrk_side == side_left);
	EMU_CK(dat.ti != BJ_INVALID_NUM_TIER);

	//if(bj_nervenet->get_active_netstate(dat.sd).sync_ending_propag){ return; }

	nervenode* owr = (nervenode*)(mck_as_loc_pt(owner));
	owr->stabi_recv_transmitter(&dat);
}

void 
synset::stabi_calc_arr_rec(num_syn_t cap, num_syn_t* arr, num_syn_t& ii) {
	MCK_CHECK_SP();

	EMU_CK(ii < cap);
	arr[ii] = tot_syn;
	ii++;

	binder * fst, * lst, * wrk;

	binder* grps = &(all_grp);
	fst = (binder*)(grps->bn_right);
	lst = (binder*)mck_as_loc_pt(grps);
	for(wrk = fst; wrk != lst; wrk = (binder*)(wrk->bn_right)){
		synset* sub_grp = (synset*)wrk;
		EMU_CK(sub_grp->parent == this);
		sub_grp->stabi_calc_arr_rec(cap, arr, ii);
	}

	//EMU_CK(ii < cap);
	//arr[ii] = tot_grp;
	//ii++;
}

// mc_addr_is_local(addr)

void 
neurostate::calc_stabi_arr() {
	if(stabi_arr == mc_null){
		stabi_arr_cap = calc_stabi_arr_cap(propag_active_set.tot_syn);
		stabi_arr = mc_malloc32(num_syn_t, stabi_arr_cap);
	}
	stabi_arr_sz = 0;
	propag_active_set.stabi_calc_arr_rec(stabi_arr_cap, stabi_arr, stabi_arr_sz);
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
nervenet::stabi_handler(missive* msv){
	EMU_CK(((stabi_tok_t)msv->tok) == bj_tok_stabi_start);

	//stabi_nervenet();
	kernel::stop_sys(bj_tok_stabi_end);
}

void
nervenode::stabi_recv_transmitter(signal_data* dat){
	EMU_CODE(
		EMU_CK(dat->ti == side_left);
		neurostate& stt = get_neurostate(side_left);
		EMU_CK(stt.propag_num_tier != BJ_INVALID_NUM_TIER);

		bool ok_3 =  false;
		if(ki == nd_neu){
			ok_3 = ((dat->ti + 1) == stt.propag_num_tier);
		} else {
			ok_3 = (dat->ti == stt.propag_num_tier);
		}
		
		EMU_CK_PRT(ok_3, "%s %s %ld %s (%d > %d)", stabi_tok_to_str((stabi_tok_t)dat->tok),
			node_kind_to_str(ki), id, net_side_to_str(side_left), (dat->ti + 1), stt.propag_num_tier);

		//EMU_CK(dat->ti < BJ_DBG_STABI_MAX_TIER); // debug_purposes_only
		EMU_CK(	(bj_nervenet->sync_parent_id != 0) ||
				bj_nervenet->get_active_netstate(side_left).sync_is_inactive ||
				(dat->ti < BJ_DBG_STABI_MAX_TIER)
		); // debug_purposes_only

		EMU_CK(dat->snp != mc_null);
		nervenode* rem_nd = dat->snp->mate->owner;
		EMU_LOG(" ::RECV_stabi_transmitter_%s_t%d_%s [%s %ld <<- %s %ld] #ti%d \n", 
			net_side_to_str(side_left), dat->ti, stabi_tok_to_str((stabi_tok_t)dat->tok), 
			node_kind_to_str(ki), id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
			stt.propag_num_tier
		);
	);

	switch(dat->tok){
		case bj_tok_stabi_ping:
		break;
		case bj_tok_stabi_step:
		break;
		case bj_tok_stabi_tier_done:
		break;
		default:
			mck_abort(1, mc_cstr("nervenode::propag_recv_propag. BAD_PROPAG_TOK"));
		break;
	}
}

