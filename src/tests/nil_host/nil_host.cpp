
#include <stdio.h>

//include "booter.h"
#include "actor.hh"

char* bjh_epiphany_elf_path = (const_cast<char*>("the_epiphany_executable.elf"));

int bj_host_main(int argc, char *argv[])
{
	if(argc > 1){
		bjh_epiphany_elf_path = argv[1];
		printf("Using core executable: %s \n", bjh_epiphany_elf_path);
	}

	kernel::init_host_sys();

	missive_handler_t hndlers = bj_null;
	kernel::set_handlers(0, &hndlers);

	kernel::run_host_sys();
	kernel::finish_host_sys();

	printf("ALL FINISHED ==================================== \n");

	return 0;
}


