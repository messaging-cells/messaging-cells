
#include "cell.hh"
#include "sornet.hh"

void 
sorcell_sornet_handler(missive* msv){
	MCK_CALL_HANDLER(sorcell, sornet_handler, msv);
}

void 
nervenet_sornet_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, sornet_handler, msv);
}


void bj_sornet_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_sorcell] = sorcell_sornet_handler;
	hndlrs[idx_nervenet] = nervenet_sornet_handler;

	kernel::set_handlers(idx_total, hndlrs);
}


#define bj_pt_obj_as_bin(pt_oo) (*((binval_t*)(pt_oo)))

int
bj_cmp_bin_objs(void* obj1, void* obj2){
	binval_t v1 = bj_pt_obj_as_bin(obj1);
	binval_t v2 = bj_pt_obj_as_bin(obj2);
	if(v1 < v2){ return -1; }
	if(v1 > v2){ return 1;}
	return 0;
}

bj_cmp_obj_func_t
sorcell::sornet_get_cmp_func(sornet_tok_t tmt_tok){
	return &bj_cmp_bin_objs;
}

void
sorcell::sornet_handler(missive* msv){
	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);
	num_nod_t tmt_idx = sn_tmt->idx;
	void* tmt_obj = sn_tmt->obj;

	bj_cmp_obj_func_t fn = sornet_get_cmp_func(tmt_tok);

	if(tmt_idx == up_idx){
		EMU_CK(up_inp == mc_null);
		up_inp = tmt_obj;
	}
	if(tmt_idx == down_idx){
		EMU_CK(down_inp == mc_null);
		down_inp = tmt_obj;
	}

	cell* src = this;
	if((up_inp != mc_null) && (down_inp != mc_null)){
		//int cv = bj_cmp_bin_objs(up_inp, down_inp);
		int cv = (*fn)(up_inp, down_inp);
		if(cv < 0){
			bj_send_sornet_tmt(src, tmt_tok, up_inp, up_out, up_idx);
			bj_send_sornet_tmt(src, tmt_tok, down_inp, down_out, down_idx);
		} else {
			bj_send_sornet_tmt(src, tmt_tok, up_inp, down_out, down_idx);
			bj_send_sornet_tmt(src, tmt_tok, down_inp, up_out, up_idx);
		}

		up_inp = mc_null;
		down_inp = mc_null;
	}
}

void
bj_send_sornet_tmt(cell* src, sornet_tok_t tok, void* obj, sorcell* dst, num_nod_t idx){
	EMU_CK(src != mc_null);
	EMU_CK(obj != mc_null);

	sornet_transmitter* trm = sornet_transmitter::acquire();
	trm->wrk_side = side_left;

	trm->src = src;
	trm->dst = dst;
	trm->tok = tok;
	trm->idx = idx;
	trm->obj = obj;

	if(trm->dst == mc_null){
		nervenet* root_net = bj_nervenet->get_nervenet(mc_nn_to_id(0));
		trm->dst = root_net;
		trm->tok = bj_tok_sornet_out;
	}

	trm->send();
}

bool
nervenet::sornet_dbg_send_cntr(){
	EMU_CK(kernel::get_core_nn() == 0);
	EMU_CK(all_input_sorcells != mc_null);
	
	dbg_sornet_curr_cntr++;
	if(dbg_sornet_curr_cntr == tot_input_sorcells){
		return false;
	}

	num_nod_t tmp_num = dbg_sornet_curr_cntr;

	cell* src = this;

	num_nod_t aa;
	for(aa = 0; aa < tot_input_sorcells; aa++){
		bool vv = mc_get_bit(tmp_num, aa);

		sorcell* srcll = all_input_sorcells[aa];
		void* obj = mc_null;
		if(vv){
			obj = mck_as_glb_pt(&net_top);
		} else {
			obj = mck_as_glb_pt(&net_bottom);
		}
		EMU_CK(obj != mc_null);
		EMU_CK(srcll != mc_null);

		bj_send_sornet_tmt(src, bj_tok_sornet_bin, obj, srcll, aa);
	}

	return true;
}

void bj_sornet_main() {
	mc_core_nn_t nn = kernel::get_core_nn();

	kernel::set_handlers(1, bj_nil_handlers);
	bj_sornet_init_handlers();

	EMU_LOG("SORNET___ %d \n", nn);

	kernel* ker = mck_get_kernel();
	ker->user_func = bj_sornet_kernel_func;

	nervenet* my_net = bj_nervenet;
	my_net->init_sync_cycle();

	sornet_transmitter::separate(my_net->tot_sorcells * 2);

	mck_slog2("__dbg2.sornet\n");

	bj_print_active_cnf(side_left, tiki_invalid, mc_cstr("stb_before"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	if(nn == 0){
		my_net->send(my_net, bj_tok_sornet_start);
	}
	kernel::run_sys();

	bj_print_active_cnf(side_left, tiki_invalid, mc_cstr("stb_after"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	EMU_PRT("...............................END_SORNET\n");
	mck_slog2("END_SORNET___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");
	mck_sprt2("dbg2.sornet.end\n");

}

bool
nervenet::sornet_check_order(bj_cmp_obj_func_t fn){
	num_nod_t aa;
	bool sor_ok = true;
	for(aa = 1; aa < tot_input_sorcells; aa++){
		void* o1 = all_output_sorobjs[aa - 1];
		void* o2 = all_output_sorobjs[aa];
		int cv = (*fn)(o1, o2);
		if(cv > 0){
			sor_ok = false;
			break;
		}
	}
	return sor_ok;
}

void
nervenet::sornet_dbg_end_step(){
	EMU_CK(kernel::get_core_nn() == 0);

	sornet_check_order(&bj_cmp_bin_objs);

	nervenet* my_net = bj_nervenet;
	my_net->send(my_net, bj_tok_sornet_start);
}

void
nervenet::sornet_dbg_bin_handler(missive* msv){
	EMU_CK(kernel::get_core_nn() == 0);

	sornet_transmitter* sn_tmt = (sornet_transmitter*)msv;
	sornet_tok_t tmt_tok = (sornet_tok_t)(sn_tmt->tok);
	num_nod_t tmt_idx = sn_tmt->idx;
	void* tmt_obj = sn_tmt->obj;

	if(tmt_tok == bj_tok_sornet_start){
		bool has_more = sornet_dbg_send_cntr();
		if(! has_more){
			act_left_side.send_sync_to_children(bj_tok_sync_to_children, 
					BJ_INVALID_NUM_TIER, tiki_invalid, mc_null);
		}
	}
	if(tmt_tok == bj_tok_sornet_out){
		EMU_CK(tmt_idx < tot_input_sorcells);
		EMU_CK(all_output_sorobjs[tmt_idx] == mc_null);
		all_output_sorobjs[tmt_idx] = tmt_obj;

		tot_rcv_output_sorobjs++;
		if(tot_rcv_output_sorobjs == tot_input_sorcells){
			sornet_dbg_end_step();
		}
	}
}

void bj_sornet_kernel_func(){
	nervenet* my_net = bj_nervenet;
	if(my_net->act_left_side.sync_is_ending){
		kernel::stop_sys(bj_tok_sornet_end);
	}
}

void
nervenet::sornet_handler(missive* msv){
	mck_token_t tmt_tok = msv->tok;
	if(bj_tok_sync_to_children == tmt_tok){
		act_left_side.send_sync_to_children(bj_tok_sync_to_children, BJ_INVALID_NUM_TIER, tiki_invalid, mc_null);
		return;
	}

	sornet_dbg_bin_handler(msv);
}

