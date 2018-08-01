

/*************************************************************

This file is part of messaging-cells.

messaging-cells is free software: you can redistribute it and/or modify
it under the terms of the version 3 of the GNU General Public 
License as published by the Free Software Foundation.

messaging-cells is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with messaging-cells.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------------

Copyright (C) 2017-2018. QUIROGA BELTRAN, Jose Luis.
Id (cedula): 79523732 de Bogota - Colombia.
See https://messaging-cells.github.io/

messaging-cells is free software thanks to The Glory of Our Lord 
	Yashua Melej Hamashiaj.
Our Resurrected and Living, both in Body and Spirit, 
	Prince of Peace.

------------------------------------------------------------*/


#include <stdio.h>

//include "booter.h"
#include "cell.hh"

char* mch_epiphany_elf_path = (mc_cstr("the_epiphany_executable.elf"));

int mc_manageru_main(int argc, char *argv[])
{
	if(argc > 1){
		mch_epiphany_elf_path = argv[1];
		printf("Using workeruni executable: %s \n", mch_epiphany_elf_path);
	}

	kernel::init_manageru_sys();

	missive_handler_t the_handlers[] = { mc_null };
	kernel::set_handlers(0, the_handlers);

	kernel::run_manageru_sys();
	kernel::finish_manageru_sys();

	printf("ALL FINISHED ==================================== \n");

	return 0;
}


