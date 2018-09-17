
#include <stdio.h>

#include "cell.hh"
#include "manageru_preload.hh"
//include "workerus_sort_net.hh"

char* mch_epiphany_elf_path = (mc_cstr("the_epiphany_executable.elf"));

missive_handler_t sn_mgr_handlers[mck_tot_base_cell_classes];

void sort_net_mgr_init_handlers(){
	missive_handler_t* hndlrs = sn_mgr_handlers;
	mc_init_arr_vals(mck_tot_base_cell_classes, hndlrs, mc_null);
	hndlrs[mck_tot_base_cell_classes - 1] = kernel::invalid_handler_func;

	kernel::set_tot_cell_subclasses(mck_tot_base_cell_classes);
	kernel::set_cell_handlers(hndlrs);
	kernel::set_handlers(mck_tot_base_cell_classes, hndlrs);
}

int mc_manageru_main(int argc, char *argv[])
{
	if(argc > 1){
		mch_epiphany_elf_path = argv[1];
		printf("Using workeru executable: %s \n", mch_epiphany_elf_path);
	}
	
	kernel::init_manageru_sys();

	THE_SORT_NET = mc_malloc32(pre_load_snet, 1);
	new (THE_SORT_NET) pre_load_snet(); 

	THE_SORT_NET->tot_workerus = mc_tot_nn_sys;

	create_sornet(BJ_DBG_TOT_INPUT_SORNODES);

	void* workeru_sort_net_pt = (void*)mc_manageru_addr_to_workeru_addr((mc_addr_t)THE_SORT_NET);
	kernel::get_sys()->manageru_load_data = workeru_sort_net_pt;

	sort_net_mgr_init_handlers();

	kernel::run_manageru_sys();
	kernel::finish_manageru_sys();

	printf("MANAGERU_CODE_FINISHED ==================================== \n");
	return 0;
}

