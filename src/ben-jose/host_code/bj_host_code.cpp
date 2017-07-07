
#include <stdio.h>

#include "cell.hh"
#include "dimacs.h"
#include "preload_cnf.hh"
#include "file_funcs.h"

char* mch_epiphany_elf_path = (const_cast<char*>("the_epiphany_executable.elf"));

int mc_host_main(int argc, char *argv[])
{
	if(argc > 1){
		mch_epiphany_elf_path = argv[1];
		printf("Using core executable: %s \n", mch_epiphany_elf_path);
	}

	if(argc < 3){
		printf("args: <epiphany_elf> <cnf_file_path>\n");
		return 1;
	}
	ch_string f_nam = argv[2];

	if(! file_exists(f_nam)){
		printf("Cannot find file %s \n", f_nam.c_str() );
		return 1;
	}

	row<long> all_lits;
	all_lits.clear();

	bool load_ok = true;
	dimacs_loader	the_loader(NULL);
	try{
		the_loader.parse_file(f_nam, all_lits, true);
	} catch (const top_exception& ex1){
		load_ok = false;
	}

	if(load_ok){
		//std::cout << all_lits << "\n";
		std::cout << "LOAD CNN SUCCEDED f_nam=" << f_nam << "\n";
	} else {
		std::cout << "LOAD CNN FAILED f_nam=" << f_nam << "\n";
	}

	const long* arr = all_lits.get_c_array();
	long sz = all_lits.get_c_array_sz();

	kernel::init_host_sys();

	THE_CNF = mc_malloc32(pre_load_cnf, 1);
	new (THE_CNF) pre_load_cnf(); 

	THE_CNF->tot_ccls = the_loader.ld_num_ccls;
	THE_CNF->tot_vars = the_loader.ld_num_vars;
	THE_CNF->tot_lits = the_loader.ld_tot_lits;
	THE_CNF->tot_cores = mc_tot_nn_sys;

	preload_cnf(sz, arr);

	void* core_cnf_pt = (void*)mc_host_addr_to_core_addr((mc_addr_t)THE_CNF);
	kernel::get_sys()->host_load_data = core_cnf_pt;

	printf("LITS_SZ=%ld tot_lits=%ld tot_vars=%ld tot_ccls=%ld tot_cores=%ld \n", all_lits.size(),
			the_loader.ld_tot_lits, the_loader.ld_num_vars, the_loader.ld_num_ccls, THE_CNF->tot_cores);

	printf("THE_CNF=%p \n", core_cnf_pt);
	printf("magic = %ld \n", THE_CNF->MAGIC);

	//print_cnf();
	//print_nods();
	//print_core_cnfs();

	missive_handler_t hndlers = mc_null;
	kernel::set_handlers(0, &hndlers);

	kernel::run_host_sys();
	kernel::finish_host_sys();

	printf("ALL FINISHED ==================================== \n");

	return 0;
}


