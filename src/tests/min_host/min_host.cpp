
#include <stdio.h>

#include "actor.hh"
#include "booter.h"

char* bjh_epiphany_elf_path = (const_cast<char*>("the_epiphany_executable.elf"));

int bj_host_main(int argc, char *argv[])
{
	if(argc > 1){
		bjh_epiphany_elf_path = argv[1];
		printf("Using core executable: %s \n", bjh_epiphany_elf_path);
	}

	kernel::init_host_sys();

	printf("STARTING min-host \n");

	/*
	kernel* ker = BJK_KERNEL;

	bj_core_id_t koid = ker->get_core_id(); 
	//bj_addr_t addr_0 = bj_addr_set_id(koid, 0);

	//bj_link_syms_data_st* lk_dat = &(BJ_EXTERNAL_RAM_LOAD_DATA);
	//bj_addr_t addr_0 = (bj_addr_t)bjh_disp_to_pt(lk_dat->extnl_host_alloc_disp);

	actor* act1 = kernel::get_core_actor();

	bj_addr_t eph_act1 = bj_znq_addr_to_eph_addr((bj_addr_t)act1);

	bj_core_id_t koid2 = bj_addr_get_id(eph_act1);

	printf("CORE_ID=%p Kactor=%p koid2=%p eph_act1=%p \n", 
		(void*)(bj_addr_t)koid, act1, (void*)(bj_addr_t)koid2, (void*)eph_act1);

	//kernel::run_host_sys();
	*/

	kernel::finish_host_sys();


	return 0;
}


