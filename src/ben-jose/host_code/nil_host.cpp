
#include <stdio.h>

#include "cell.hh"

char* mch_epiphany_elf_path = (mc_cstr("the_epiphany_executable.elf"));

int mc_host_main(int argc, char *argv[])
{
	if(argc > 1){
		mch_epiphany_elf_path = argv[1];
		printf("Using core executable: %s \n", mch_epiphany_elf_path);
	}

	kernel::init_host_sys();

	missive_handler_t the_handlers[] = { mc_null };
	kernel::set_handlers(0, the_handlers);

	kernel::run_host_sys();
	kernel::finish_host_sys();

	printf("ALL FINISHED ==================================== \n");

	return 0;
}


