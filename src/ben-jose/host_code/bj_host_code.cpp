
#include <stdio.h>

#include "cell.hh"
#include "dimacs.h"
#include "preload_cnf.hh"

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
		std::cout << all_lits << "\n";
		std::cout << "LOAD CNN SUCCEDED f_nam=" << f_nam << "\n";
	} else {
		std::cout << "LOAD CNN FAILED f_nam=" << f_nam << "\n";
	}

	const long* arr = all_lits.get_c_array();
	long sz = all_lits.get_c_array_sz();

	kernel::init_host_sys();

	THE_CNF = mc_malloc32(pre_cnf, 1);

	THE_CNF->tot_ccls = the_loader.ld_num_ccls;
	THE_CNF->tot_vars = the_loader.ld_num_vars;
	THE_CNF->tot_lits = the_loader.ld_tot_lits;
	THE_CNF->tot_cores = mc_tot_nn_sys;

	printf("LITS_SZ=%ld tot_lits=%ld tot_vars=%ld tot_ccls=%ld tot_cores=%ld \n", all_lits.size(),
			the_loader.ld_tot_lits, the_loader.ld_num_vars, the_loader.ld_num_ccls, THE_CNF->tot_cores);


	preload_cnf(sz, arr);
	print_cnf();
	print_nods();

	missive_handler_t hndlers = mc_null;
	kernel::set_handlers(0, &hndlers);

	//kernel::run_host_sys();
	kernel::finish_host_sys();

	printf("ALL FINISHED ==================================== \n");

	return 0;
}


