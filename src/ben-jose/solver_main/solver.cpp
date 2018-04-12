
#include "solver.hh"

#include "load_cnf.hh"
#include "propag.hh"
#include "stabi.hh"

mc_c_decl int main();

#define TOT_MODS 3

#define CNF_LOADER_IDX 0
#define PROPAG_IDX 1
#define STABI_IDX 2

char* all_mod_nams[TOT_MODS] mc_external_data_ram;
mc_addr_t* all_mod_addr;

void
init_module_nams() mc_external_code_ram;

void
init_module_nams(){
	all_mod_nams[CNF_LOADER_IDX] = mc_cstr("module1");
	all_mod_nams[PROPAG_IDX] = mc_cstr("module2");
	all_mod_nams[STABI_IDX] = mc_cstr("module3");
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

void
print_module_addrs(){
	uint32_t aa = 0;
	mck_sprt2("ALL_MODULE_ADDRS=\n");
	for(aa = 0; aa < TOT_MODS; aa++){
		char* nam0 = all_mod_nams[aa];
		mck_sprt2(nam0);
		mck_sprt2(" addr____");
		mck_xprt(all_mod_addr[aa]);
		mck_sprt2("____\n");
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

	EMU_PRT("SOLVER main (KER=%p)\n", (void*)MCK_KERNEL);
	mck_slog2("SOLVER_STARTED\n");	

	bj_print_class_szs();

	//EMU_DBG_CODE(transmitter_alloc_hook = bj_dbg_transmmitter_alloc);
	//EMU_DBG_CODE(transmitter_acquire_hook = bj_dbg_transmmitter_acquire);

	init_module_nams();

	all_mod_addr = mc_malloc32(mc_addr_t, TOT_MODS);
	mck_fill_module_external_addresses(TOT_MODS, all_mod_nams, all_mod_addr);

	bool ok = false;
	ok = mck_load_module(all_mod_addr[CNF_LOADER_IDX]);
	if(! ok){
		mck_abort(1, mc_cstr("mck_load_module failed for CNF_LOADER_IDX. \n"));
	}
	bj_load_main();

	ok = mck_load_module(all_mod_addr[PROPAG_IDX]);
	if(! ok){
		mck_abort(1, mc_cstr("mck_load_module_failed_for_PROPAG_IDX. \n"));
	}
	bj_propag_main();

	ok = mck_load_module(all_mod_addr[STABI_IDX]);
	if(! ok){
		mck_abort(1, mc_cstr("mck_load_module_failed_for_STABI_IDX. \n"));
	}
	bj_stabi_main();

	EMU_DBG_CODE(bj_nervenet->all_dbg_dat.dbg_prt_all());

	EMU_PRT("SOLVER_ENDED\n");
	//EMU_LOG("SOLVER_ENDED\n");
	mck_slog2("SOLVER_ENDED_OK\n");	

	kernel::finish_sys();
}

