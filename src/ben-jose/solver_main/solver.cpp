
#include "solver.hh"

#include "load_cnf.hh"

mc_c_decl int main();

char load_module_nam[] mc_external_data_ram = "module1";
char m2_nam[] mc_external_data_ram = "module2";
char m3_nam[] mc_external_data_ram = "module3";

#define TOT_MODS 1

#define CNF_LOADER_IDX 0
#define MOD2_IDX 2
#define MOD3_IDX 1
#define MOD_MAX_IDX 0

char* all_mod_nams[TOT_MODS] mc_external_data_ram;
mc_addr_t* all_mod_addr;

void
init_module_nams() mc_external_code_ram;

void
init_module_nams(){
	all_mod_nams[CNF_LOADER_IDX] = load_module_nam;
	//all_mod_nams[MOD2_IDX] = m2_nam;
	//all_mod_nams[MOD3_IDX] = m3_nam;
}

void
print_module_nams() mc_external_code_ram;

char dbg_slvr1[] mc_external_data_ram = "ALL_MODULE_NAMES=\n";

void
print_module_nams(){
	uint32_t to_m = mck_get_tot_modules();
	uint32_t aa = 0;
	mck_sprt2(dbg_slvr1);
	for(aa = 0; aa < to_m; aa++){
		char* nam0 = mck_get_module_name(aa);
		mck_sprt2(nam0);
		mck_sprt2("\n");
	}
}

void
print_module_addrs() mc_external_code_ram;

char dbg_slvr2[] mc_external_data_ram = "ALL_MODULE_ADDRS=\n";
char dbg_slvr3[] mc_external_data_ram = " addr____";
char dbg_slvr4[] mc_external_data_ram = "____\n";

void
print_module_addrs(){
	uint32_t aa = 0;
	mck_sprt2(dbg_slvr2);
	for(aa = 0; aa < TOT_MODS; aa++){
		char* nam0 = all_mod_nams[aa];
		mck_sprt2(nam0);
		mck_sprt2(dbg_slvr3);
		mck_xprt(all_mod_addr[aa]);
		mck_sprt2(dbg_slvr4);
	}
}

void
link_all_modules_aux_fn() mc_external_code_ram;

void
link_all_modules_aux_fn(){
	bj_load_main();
}

void mc_cores_main() {
	kernel::init_sys();

	EMU_PRT("SOLVER main\n");

	init_module_nams();

	all_mod_addr = mc_malloc32(mc_addr_t, TOT_MODS);
	mck_fill_module_external_addresses(TOT_MODS, all_mod_nams, all_mod_addr);

	bool ok = mck_load_module(all_mod_addr[CNF_LOADER_IDX]);
	if(ok){
		bj_load_main();
	}

	mck_sprt2("SOLVER ENDED\n");

	kernel::finish_sys();
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


