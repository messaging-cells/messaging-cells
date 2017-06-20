
#include <stdio.h>

#include "cell.hh"
#include "booter.h"

char* mch_epiphany_elf_path = (const_cast<char*>("the_epiphany_executable.elf"));

int mc_host_main(int argc, char *argv[])
{
	if(argc > 1){
		mch_epiphany_elf_path = argv[1];
		printf("Using core executable: %s \n", mch_epiphany_elf_path);
	}

	kernel::init_host_sys();

	printf("STARTING min-host \n");

	/*
	kernel* ker = BJK_KERNEL;

	mc_core_id_t koid = ker->get_core_id(); 
	//mc_addr_t addr_0 = mc_addr_set_id(koid, 0);

	//mc_link_syms_data_st* lk_dat = &(MC_EXTERNAL_RAM_LOAD_DATA);
	//mc_addr_t addr_0 = (mc_addr_t)mch_disp_to_pt(lk_dat->extnl_host_alloc_disp);

	cell* act1 = kernel::get_core_cell();

	mc_addr_t eph_act1 = mc_znq_addr_to_eph_addr((mc_addr_t)act1);

	mc_core_id_t koid2 = mc_addr_get_id(eph_act1);

	printf("CORE_ID=%p Kcell=%p koid2=%p eph_act1=%p \n", 
		(void*)(mc_addr_t)koid, act1, (void*)(mc_addr_t)koid2, (void*)eph_act1);

	//kernel::run_host_sys();
	*/

	kernel::finish_host_sys();


	return 0;
}


