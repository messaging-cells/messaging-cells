
#include "cell.hh"
#include "sornet.hh"

void 
nervenet_sornet_handler(missive* msv){
	MCK_CALL_HANDLER(nervenet, sornet_handler, msv);
}


void bj_sornet_init_handlers(){
	missive_handler_t* hndlrs = bj_handlers;
	mc_init_arr_vals(idx_total, hndlrs, mc_null);
	hndlrs[idx_nervenet] = nervenet_sornet_handler;

	kernel::set_handlers(idx_total, hndlrs);
}


void bj_sornet_kernel_func(){
}

void
nervenet::sornet_handler(missive* msv){
	//mck_token_t msv_tok = msv->tok;
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

	mck_slog2("__dbg2.sornet\n");

	bj_print_active_cnf(side_left, tiki_stabi, mc_cstr("stb_before"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	my_net->send(my_net, bj_tok_sornet_start);
	kernel::run_sys();

	bj_print_active_cnf(side_left, tiki_stabi, mc_cstr("stb_after"), 3, 0, 
		bj_dbg_prt_nd_neu_flag | bj_dbg_prt_nd_pol_flag);

	EMU_PRT("...............................END_SORNET\n");
	mck_slog2("END_SORNET___");
	mck_ilog(nn);
	mck_slog2("_________________________\n");
	mck_sprt2("dbg2.sornet.end\n");

}

