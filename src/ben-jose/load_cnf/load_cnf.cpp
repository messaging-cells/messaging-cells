
#include "cell.hh"

#include "preload_cnf.hh"


MCK_DEFINE_ACQUIRE_ALLOC(core_cnf, 32);	// defines core_cnf::acquire_alloc

MCK_DEFINE_MEM_METHODS(cnf_node, 32, bj_ava_cnf_nodes)

BJ_DEFINE_LOAD_CNF_FUNCS();

char dbg_cnf_ldr2[] mc_external_data_ram = "CAN NOT INIT GLB CORE DATA";

void bj_load_main() {
	//kernel* ker = kernel::get_sys();
	kernel* ker = mck_get_kernel();
	mc_core_nn_t nn = kernel::get_core_nn();

	EMU_PRT("bj_load_main 1 \n");

	mck_slog2("LOAD_CNF\n");
	if(ker->magic_id != MC_MAGIC_ID){
		mck_slog2("BAD_MAGIC\n");
	}
	
	core_cnf* my_cnf = core_cnf::acquire_alloc();
	if(my_cnf == mc_null){
		mck_abort(1, dbg_cnf_ldr2);
	}
	ker->user_data = my_cnf;

	pre_load_cnf* pre_cnf = (pre_load_cnf*)(ker->host_load_data);

	core_cnf* nn_cnf = (core_cnf*)mc_host_addr_to_core_addr((mc_addr_t)(pre_cnf->all_cnf + nn));
	bj_core_cnf->shd_cnf = nn_cnf;
	
	mck_slog2("bj_core_cnf_MAGIC_____");
	mck_ilog(bj_core_cnf->MAGIC);
	mck_slog2("_____\n");

	//EMU_PRT("nn_cnf->MAGIC = %d \n", nn_cnf->MAGIC);

	//EMU_PRT("pre_cnf = %p MAGIC = %d \n", pre_cnf, pre_cnf->MAGIC);
	/*
	*/

	mck_slog2("END_LOADING_CNF\n");
}

/*

	binder * fst, * lst, * wrk;
	binder* all_msvs = &(host_mgrp->all_agts);

	fst = (binder*)mc_host_pt_to_core_pt(all_msvs->bn_right);
	lst = all_msvs;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_host_pt_to_core_pt(wrk->bn_right)){
		missive* remote_msv = (missive*)wrk;

		cell* hdlr_dst = (remote_msv)->dst;
		EMU_CK(hdlr_dst != mc_null);

		mck_handle_missive_base(remote_msv, hdlr_dst->handler_idx);
	}

*/