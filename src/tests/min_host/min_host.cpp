
#include <stdio.h>

#include "actor.hh"

char* bjh_epiphany_elf_path = (const_cast<char*>("the_epiphany_executable.elf"));

int bj_host_main(int argc, char *argv[])
{
	if(argc > 1){
		bjh_epiphany_elf_path = argv[1];
		printf("Using core executable: %s \n", bjh_epiphany_elf_path);
	}
	if(argc > 2){
		printf("LOADING WITH MEMCPY \n");
		BJH_LOAD_WITH_MEMCPY = true;
	}

	kernel::init_host_sys();

	kernel::run_host_sys();

	kernel::finish_host_sys();
	return 0;
}


