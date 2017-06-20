

#include "cell.hh"
#include "pru_1.h"
#include "pru_2.h"
#include "pru_3.h"

mc_c_decl int main();

char* m1_nam mc_external_data_ram = const_cast<char*>("module1");
char* m2_nam mc_external_data_ram = const_cast<char*>("module2");
char* m3_nam mc_external_data_ram = const_cast<char*>("module3");

#define TOT_MODS 3

#define MOD1_IDX 1
#define MOD2_IDX 2
#define MOD3_IDX 0

char* all_mod_nams[TOT_MODS] mc_external_data_ram;
mc_addr_t* all_mod_addr;

void
init_module_nams() mc_external_code_ram;

void
init_module_nams(){
	all_mod_nams[MOD1_IDX] = m1_nam;
	all_mod_nams[MOD2_IDX] = m2_nam;
	all_mod_nams[MOD3_IDX] = m3_nam;
}


void
print_module_nams() mc_external_code_ram;

void
print_module_nams(){
	uint32_t to_m = mck_get_tot_modules();
	uint32_t aa = 0;
	mck_sprt2("ALL_MODULE_NAMES=\n");
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
	uint32_t to_m = mck_get_tot_modules();
	uint32_t aa = 0;
	mck_sprt2("ALL_MODULE_ADDRS=\n");
	for(aa = 0; aa < to_m; aa++){
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
	m1_main();
	m2_main();
	m3_main();
}

int main() {
	mck_glb_init();
	mck_slog2("Modules main \n");

	init_module_nams();
	uint32_t tot_m = mck_get_tot_modules();
	all_mod_addr = mc_malloc32(mc_addr_t, tot_m);
	mck_fill_module_external_addresses(all_mod_nams, all_mod_addr);

	if(BJK_GLB_SYS->the_core_nn == 0){	
		//print_module_nams();
		//print_module_addrs();
		bool ok = mck_load_module(all_mod_addr[MOD2_IDX]);
		if(ok){
			m2_main();
		}
	}
	if(BJK_GLB_SYS->the_core_nn == 1){	
		//print_module_nams();
		//print_module_addrs();
		bool ok = mck_load_module(all_mod_addr[MOD1_IDX]);
		if(ok){
			m1_main();
		}
	}
	if(BJK_GLB_SYS->the_core_nn == 3){	
		//print_module_nams();
		//print_module_addrs();
		bool ok = mck_load_module(all_mod_addr[MOD3_IDX]);
		if(ok){
			m3_main();
		}
	}
	mck_slog2("______________________\n");

	mck_glb_finish();
	return 0;
}

