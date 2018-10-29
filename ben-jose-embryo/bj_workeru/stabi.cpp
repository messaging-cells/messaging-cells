
#include "cell.hh"
#include "stabi.hh"

#define BJ_DBG_STABI_MAX_TIER 10

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


void bj_stabi_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_neuron] = neuron_stabi_handler;
	hndlrs[idx_synapse] = synapse_stabi_handler;
	hndlrs[idx_nervenet] = nervenet_stabi_handler;
	hndlrs[idx_last_invalid] = kernel::invalid_handler_func;

	kernel::set_tot_cell_subclasses(idx_total);
	kernel::set_cell_handlers(hndlrs);
}

void
synapse::stabi_handler(missive* msv){
	stabi_transmitter* sb_tmt = (stabi_transmitter*)msv;

	signal_data dat;
	dat.msv = msv;
	dat.snp = this;
	dat.tok = (stabi_tok_t)(sb_tmt->tok);
	dat.sd = side_left;
	dat.ti = sb_tmt->d.stb.wrk_tier;
	dat.id_arr_sz = sb_tmt->d.stb.id_arr_sz;
	dat.id_arr = sb_tmt->d.stb.id_arr;

	PTD_CK(dat.sd == side_left);
	PTD_CK(dat.ti != BJ_INVALID_NUM_TIER);

	//if(bj_nervenet->act_left_side.sync_is_ending){ return; }

	nervenode* owr = (nervenode*)(mck_as_loc_pt(owner));
	owr->stabi_recv_transmitter(&dat);
}

int bj_cmp_stabi_id_arrs(num_syn_t sz1, num_syn_t* arr1, num_syn_t sz2, num_syn_t* arr2){
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
nervenode::stabi_recv_transmitter(signal_data* dat){
	//PTD_CK(dat->sd == side_left);
	PTD_CODE(
		//side_state& stt = left_side;
		PTD_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);

		bool ok_3 =  false;
		if(ki == nd_neu){
			ok_3 = ((dat->ti + 1) == stabi_num_tier);
		} else {
			ok_3 = (dat->ti == stabi_num_tier);
		}
		
		PTD_CK_PRT(ok_3, "%s %s %ld %s (%d > %d)", stabi_tok_to_str((stabi_tok_t)dat->tok),
			node_kind_to_str(ki), id, net_side_to_str(side_left), (dat->ti + 1), stabi_num_tier);

		//PTD_CK(dat->ti < BJ_DBG_STABI_MAX_TIER); // debug_purposes_only
		PTD_CK(	(bj_nervenet->sync_parent_id != 0) ||
				bj_nervenet->act_left_side.sync_is_inactive ||
				(dat->ti < BJ_DBG_STABI_MAX_TIER)
		); // debug_purposes_only

		PTD_CK(dat->snp != mc_null);
		nervenode* rem_nd = dat->snp->mate->owner;
		PTD_LOG(" ::RECV_stabi_transmitter_%s_t%d_%s [%s %ld <<- %s %ld] #ti%d \n", 
			net_side_to_str(side_left), dat->ti, stabi_tok_to_str((stabi_tok_t)dat->tok), 
			node_kind_to_str(ki), id, node_kind_to_str(rem_nd->ki), rem_nd->id, 
			stabi_num_tier
		);
	);

	switch(dat->tok){
		case bj_tok_stabi_rank:
			stabi_recv_rank(dat);
		break;
		case bj_tok_stabi_ping:
			stabi_recv_ping(dat);
		break;
		case bj_tok_stabi_tier_done:
			stabi_recv_tier_done(dat);
		break;
		default:
			mck_abort(1, mc_cstr("nervenode::stabi_recv_transmitter. BAD_STABI_TOK"));
		break;
	}
}

void 
nervenode::stabi_send_snp_tier_done(callee_prms& pms){
	PTD_CK(pms.snp->owner == this);
	pms.snp->stabi_send_transmitter(bj_tok_stabi_tier_done);
}

void
nervenode::stabi_send_all_ti_done(nervenode* nd, num_tier_t dbg_ti){
	side_state& sst = left_side;
	net_side_t sd = side_left;
	
	PTD_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);
	//PTD_CK(&(nd->left_side) == this);

	sst.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_tier_done, sd);

	PTD_CK((dbg_ti == BJ_INVALID_NUM_TIER) || (nd->ki != nd_neu) || ((dbg_ti + 1) == stabi_num_tier));
	PTD_CK((dbg_ti == BJ_INVALID_NUM_TIER) || (nd->ki == nd_neu) || (dbg_ti == stabi_num_tier));

	PTD_CK(stabi_num_tier != BJ_INVALID_NUM_TIER);
	stabi_num_tier++;

	PTD_LOG("STABI_INC_TIER_%s_t%d_%s_%ld\n", net_side_to_str(sd), stabi_num_tier, 
			node_kind_to_str(nd->ki), nd->id);
}

void
nervenode::stabi_recv_ping(signal_data* dat){
	side_state& stt = left_side;
	stt.step_num_ping++;

	PTD_LOG("STABI_INC_PINGS %s %ld %s #pings=%d TI=%d \n", node_kind_to_str(ki), id,
			net_side_to_str(side_left), stt.step_num_ping, dat->ti);
}

void
synapse::stabi_send_transmitter(stabi_tok_t tok, nervenode* src_nd, bool dbg_is_forced){
	//net_side_t sd = side_left;

	if(bj_nervenet->act_left_side.sync_is_ending){ return; }

	num_tier_t ti = owner->stabi_num_tier;

	MC_DBG(node_kind_t the_ki = owner->ki);
	MCK_CK((the_ki == nd_pos) || (the_ki == nd_neg) || (the_ki == nd_neu));
	PTD_CODE(nervenode* rem_nd = mate->owner);
	PTD_LOG("::stabi_send_transmitter_%s_t%d_%s [%s %ld ->> %s %s %ld k%d] \n", 
			net_side_to_str(side_left), ti, stabi_tok_to_str(tok), node_kind_to_str(owner->ki), owner->id, 
		((dbg_is_forced)?("FORCED"):("")), node_kind_to_str(rem_nd->ki), rem_nd->id, 
		mc_id_to_nn(mc_addr_get_id(mate)));

	stabi_transmitter* trm = bj_stabi_transmitter_acquire();
	trm->d.stb.wrk_tier = BJ_INVALID_NUM_TIER;
	trm->d.stb.id_arr_sz = 0;
	trm->d.stb.id_arr = mc_null;
	
	trm->src = this;
	trm->dst = mate;
	trm->tok = tok;
	//trm->wrk_side = sd;
	trm->d.stb.wrk_tier = ti;
	if(src_nd != mc_null){
		trm->d.stb.id_arr_sz = src_nd->stabi_arr_sz;
		trm->d.stb.id_arr = src_nd->stabi_arr;
		EPH_CODE(
			if(! mc_addr_is_local(mate)){
				trm->d.stb.id_arr = (num_syn_t*)mck_as_glb_pt(src_nd->stabi_arr);
			}
		);
	}
	trm->send();
}

void
nervenet::stabi_nervenet_start(){
	PTD_LOG("stabi_nervenet_start \n");
	send_all_neus(bj_tok_stabi_start);
	PTD_LOG("end_stabi_nervenet_start \n");
}

void
neuron::stabi_handler(missive* msv){
	stabi_tok_t tok = (stabi_tok_t)msv->tok;

	switch(tok){
		case bj_tok_stabi_start:
			stabi_neuron_start();
		break;
		default:
			mck_abort(1, mc_cstr("BAD_STABI_TOK"));
		break;
	}
}

void
neuron::stabi_neuron_start(){
	PTD_CK(left_side.step_active_set.all_grp.is_alone());
	PTD_CK(right_side.step_active_set.all_grp.is_alone());

	left_side.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_id_arr, side_left);

	stabi_send_all_ti_done(this, BJ_INVALID_NUM_TIER);
	left_side.step_reset_complete();
}

void
nervenode::stabi_recv_rank(signal_data* dat){
}

void
nervenode::stabi_recv_tier_done(signal_data* dat){
	net_side_t sd = side_left;
	nervenode* nd = this;
	side_state& stt = left_side;

	stt.step_num_complete++;

	PTD_LOG("STABI_ADD_TIER_END %s %ld %s compl(%d of %d) TI=%d \n", 
			node_kind_to_str(ki), id, net_side_to_str(sd), 
			stt.step_num_complete, stt.step_prev_tot_active, dat->ti);

	if(is_tier_complete(dat)){
		recalc_stabi(dat);

		MC_DBG(dbg_prt_tier_done(dat));

		bool to_dly = false;
		netstate& nstt = bj_nervenet->get_active_netstate(sd);
		grip& all_ti = nstt.all_stabi_tiers;
		num_tier_t the_ti = stabi_num_tier;
		
		if((ki == nd_neu)){
			PTD_CK(dat->ti == (the_ti - 1));
			to_dly = ((neuron*)nd)->is_to_delay(tiki_propag, dat->sd, the_ti, all_ti);
			if(! to_dly){
				nstt.inc_tier_rcv(nd, tiki_stabi, the_ti, all_ti);
			} else {
				tierdata& lti = get_last_tier(all_ti);
				lti.delay_binder(stt, 3);
			}
		}

		char* ts = bj_dbg_tier_kind_to_str(tiki_stabi);
		MC_MARK_USED(ts);
		PTD_LOG("STABI_TIER_COMPLETE_t%d_%s_%ld %s_%s ((%d > 0) && (%d == %d) && (%d < %d)) %s \n", dat->ti, 
					node_kind_to_str(ki), id, ts, ((to_dly)?("TO_DELAY"):("")), 
			stt.step_prev_tot_active, stt.step_num_ping, stt.step_prev_tot_active, 
			get_last_tier(all_ti).tdt_id, (the_ti - 1),
			(mc_get_flag(stt.step_flags, bj_stt_stabi_intact_id_flag))?("intact"):("")
		);

		if(! to_dly){
			stabi_start_nxt_tier(dat);
		}
	}
}

void
nervenode::stabi_start_nxt_tier(signal_data* dat){
	mck_abort(1, mc_cstr("nervenode::stabi_start_nxt_tier"));
}

void
nervenode::recalc_stabi(signal_data* dat){
	//nervenode* nd = this;
}

void
polaron::recalc_stabi(signal_data* dat){
	//polaron* pol = this;
}

void
polaron::stabi_start_nxt_tier(signal_data* dat){
	net_side_t sd = side_left;
	polaron* pol = this;
	side_state& pol_stt = get_side_state(sd);
	side_state& opp_stt = opp->get_side_state(sd);

	PTD_CK(pol_stt.is_full());
	PTD_CK(opp_stt.is_full());

	//MC_DBG(pol->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	//MC_DBG(opp->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));

	pol_stt.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_id_arr, side_left);
	opp_stt.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_id_arr, side_left);

	pol->stabi_send_all_ti_done(pol, dat->ti);
	opp->stabi_send_all_ti_done(opp, dat->ti);

	pol_stt.step_reset_complete();
	opp_stt.step_reset_complete();
}

void
nervenode::dbg_prt_tier_done(signal_data* dat){
	net_side_t sd = side_left;
	MC_DBG(dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	PTD_DBG_CODE(dbg_prt_active_synset(sd, tiki_stabi, mc_cstr("ACTi"), dat->ti));
}

void
polaron::dbg_prt_tier_done(signal_data* dat){
	net_side_t sd = side_left;
	polaron* pol = this;
	MC_DBG(pol->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	MC_DBG(opp->dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));
	PTD_DBG_CODE(pol->dbg_prt_active_synset(sd, tiki_stabi, mc_cstr("ACTi"), dat->ti));
	PTD_DBG_CODE(opp->dbg_prt_active_synset(sd, tiki_stabi, mc_cstr("ACTi"), dat->ti));
}

void
neuron::stabi_start_nxt_tier(signal_data* dat){
	neuron* neu = this;
	net_side_t sd = side_left;
	side_state& stt = get_side_state(sd);
	netstate& nst = bj_nervenet->get_active_netstate(sd);

	//MC_DBG(dbg_prt_nod(sd, tiki_stabi, mc_cstr("stb_TIER"), 8, dat->ti));

	stt.step_active_set.transmitter_send_all_rec(&nervenode::stabi_send_snp_id_arr, side_left);

	stabi_send_all_ti_done(neu, dat->ti);
	stt.step_reset_complete();

	//mck_slog2("dbg2.reset\n");

	nst.update_sync_inert(tiki_stabi, true);
}

void 
nervenode::stabi_send_snp_id_arr(callee_prms& pms){
	PTD_CK(pms.snp != mc_null);
	PTD_CK(pms.snp->owner == this);
	nervenode* nd = this;

	bool snd_png = false;
	if(ki == nd_neu){
		bool is_itct = mc_get_flag(left_side.step_flags, bj_stt_stabi_intact_id_flag);
		snd_png = is_itct;
	} else {
		PTD_CK(bj_is_pol(ki));
		bool all_png = left_side.neu_all_ping(tiki_stabi);
		snd_png = all_png;
	}
	if(snd_png){
		//PTD_CK(! bj_is_pol(ki));
		pms.snp->stabi_send_transmitter(bj_tok_stabi_ping, nd);
	} else {
		pms.snp->stabi_send_transmitter(bj_tok_stabi_rank, nd);
	}
}

void bj_stabi_kernel_func(){
	nervenet* my_net = bj_nervenet;
	my_net->act_left_side.stabi_handle_my_sync();
}

void 
netstate::stabi_handle_my_sync(){
	update_sync_inert(tiki_stabi, true);
	
	if(sync_is_ending){
		SYNC_LOG(" SYNCR_STOPPING_WORKERU_%s \n", net_side_to_str(my_side));
		//mck_get_kernel()->set_idle_exit();
		//kernel::stop_sys(bj_tok_propag_end);
		kernel::stop_sys(bj_tok_stabi_end);
	}
}

void
nervenet::stabi_handler(missive* msv){
	mck_token_t msv_tok = msv->tok;
	if(msv_tok == bj_tok_stabi_start){
		stabi_nervenet_start();
		//kernel::stop_sys(bj_tok_stabi_end); // DEBUG purposes only
		return;
	}

	sync_handler(tiki_stabi, msv);
}

void bj_stabi_main() {
	mck_set_sub_module_id(BJ_STABI_SUB_MODULE_STABI);

	mc_workeru_nn_t nn = kernel::get_workeru_nn();

	bj_stabi_init_handlers();

	PTD_LOG("STABI___ %d \n", nn);

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_stabi_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->init_sync_cycle();

	mck_slog2("__dbg2.stabi\n");

	bj_print_active_cnf(side_left, tiki_stabi, mc_cstr("stb_before"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	my_net->send(my_net, bj_tok_stabi_start);
	//kernel::run_sys();

	bj_print_active_cnf(side_left, tiki_stabi, mc_cstr("stb_after"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	PTD_PRT("...............................END_STABI\n");
	mck_slog2("END_STABI___");
	mck_ilog(nn);
	//mck_slog2("_________________________\n");
	mck_sprt2("dbg2.stabi.end\n");

}

