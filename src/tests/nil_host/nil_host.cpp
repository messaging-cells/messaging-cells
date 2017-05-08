
#include <stdio.h>

#include "booter.h"

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

	bj_host_init();
	bj_host_run();
	bj_host_finish();

	return 0;
}


