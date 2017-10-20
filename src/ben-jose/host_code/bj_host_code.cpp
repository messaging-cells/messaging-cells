
#include <stdio.h>

#include "cell.hh"
#include "dimacs.h"
#include "load_cnf.hh"
#include "preload_cnf.hh"
#include "file_funcs.h"

char* mch_epiphany_elf_path = (mc_cstr("the_epiphany_executable.elf"));

void bj_test(int argc, char *argv[]) mc_external_code_ram;
int bj_host_main(int argc, char *argv[]) mc_external_code_ram;

int bj_host_main(int argc, char *argv[])
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

	printf("BJ_MAX_NODE_SZ=%lu\n", BJ_MAX_NODE_SZ);

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

	missive_handler_t the_handlers[] = { mc_null };
	kernel::set_handlers(0, the_handlers);

	kernel::run_host_sys();
	kernel::finish_host_sys();

	return 0;
}

#ifdef MC_IS_EMU_CODE

void bj_test(int argc, char *argv[])
{
	binder b1;
	binder b2;
	synapse s1;

	s1.handler_idx = 55;
	
	b1.bind_to_my_left(b2);
	b1.bind_to_my_left(s1.right_handle); // test

	if(b1.bn_right == &b2){
		printf("b2 is FIRST\n");
	}
	if(b1.bn_left == &s1.right_handle){ // test
		printf("syn is LAST\n");
	}
	binder* lft = b1.bn_left;
	synapse* pt_s1 = bj_get_syn_of_rgt_handle(lft);

	printf("syn_idx = %d\n", pt_s1->handler_idx);

	printf("BJ_HOST_TESTS_FINISHED\n");
}

typedef uint16_t test_int_t;

void bj_test_2(int argc, char *argv[])
{
	unsigned long imax = mc_maxof(test_int_t);

	printf("imax = %lu\n", imax);
}

void call_nerv_pt_fn(nervenode* nn, synapse* snp, bj_callee_t mth){
	(nn->*mth)(snp, side_right);
}

void 
neuron::pru_callee(synapse* snp, net_side_t sd){
	//printf("pru_callee %ld %d \n", id, pru_attr);
	printf("pru_callee %ld \n", id);
}

void bj_test_3(int argc, char *argv[])
{
	neuron nn1;
	synapse snp1;

	//nn1.pru_attr = 321;
	nn1.id = 1234;
	snp1.owner = &nn1;

	call_nerv_pt_fn(&nn1, &snp1, (bj_callee_t)(&neuron::pru_callee));
	//call_nerv_pt_fn(&nn1, &snp1, &neuron::pru_callee);
}

void bj_test_4(int argc, char *argv[])
{
	long aa = 1234;
	long bb = (aa >> 3);

	printf("aa = %ld bb = %ld\n", aa, bb);
}

#endif

int mc_host_main(int argc, char *argv[])
{
	int rr = 0;

	//EMU_CODE(bj_test(argc, argv));
	//EMU_CODE(bj_test_2(argc, argv));
	//EMU_CODE(bj_test_3(argc, argv));
	//EMU_CODE(bj_test_4(argc, argv));
	rr = bj_host_main(argc, argv);

	printf("HOST_CODE_FINISHED ==================================== \n");
	return rr;
}

