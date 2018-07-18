
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "preload.hh"

num_nod_t
get_tot_levels(num_nod_t nn){
	double in = (double)nn;
	double lg = log2(in);
	double lv = lg * (lg + 1) / 2;
	return (num_nod_t)lv;
}

num_nod_t
get_bigger_pow2(num_nod_t nn){
	num_nod_t pp = 1;
	while(pp < nn){ pp <<= 1; }
	return pp;
}

pre_sornode*
create_node(sornod_kind_t knd, num_nod_t up_idx, num_nod_t down_idx, sornet_prms& prms){
	pre_sornode* nod = pre_sornode::acquire();

	prms.curr_nod_id++;
	nod->nod_id = prms.curr_nod_id;

	EMU_CK(up_idx < prms.tot_nods);
	EMU_CK(down_idx < prms.tot_nods);

	nod->up_idx = up_idx;
	nod->down_idx = down_idx;

	nod->out_up = prms.arr_nods[up_idx];
	nod->out_down = prms.arr_nods[down_idx];

	prms.arr_nods[up_idx] = nod;
	prms.arr_nods[down_idx] = nod;

	mc_core_nn_t emu_up_nid = 0;
	mc_core_nn_t emu_down_nid = 0;
	MC_MARK_USED(emu_up_nid);
	MC_MARK_USED(emu_down_nid);

	if(nod->out_up != mc_null){
		nod->level = nod->out_up->level + 1;
		EMU_CK(nod->out_down != mc_null);
		EMU_CK(nod->out_down->level == nod->out_up->level);

		emu_up_nid = nod->out_up->nod_id;
		emu_down_nid = nod->out_down->nod_id;

		nod->up_conn = nod->out_up->get_conn_kind(up_idx);
		nod->down_conn = nod->out_down->get_conn_kind(down_idx);
	}

	EMU_CK(nod->level >= 0);
	EMU_CK(nod->level < prms.tot_lvs);

	if(THE_CNF != mc_null){
		long num_cores = THE_CNF->tot_cores;
		mc_core_nn_t& nxt_nn = prms.arr_lvs[nod->level];
		EMU_CK(nxt_nn < num_cores);

		nod->nod_nn = nxt_nn;

		pre_cnf_net& cnf = THE_CNF->all_cnf[nxt_nn];
		cnf.tot_pre_sornods++;
		cnf.all_pre_sornods.bind_to_my_left(*nod);

		nxt_nn++;
		if(nxt_nn == num_cores){ nxt_nn = 0; }
		EMU_CK(nxt_nn < num_cores);
	}

	EMU_CK(knd != snod_invalid);
	EMU_PRT("%s_NOD (%ld)  %ld[%ld %ld] \t(%ld %ld) \n", ((knd == snod_alte)?("ALT"):("HLF")), nod->nod_id, 
			nod->level, up_idx, down_idx, emu_up_nid, emu_down_nid);

	return nod;
}

void
create_net_half_cleaner(num_nod_t pos, num_nod_t sz, sornet_prms& prms){
	if(sz == 1){ return; }
	num_nod_t hlf = sz/2;
	for(num_nod_t ii = 0; ii < hlf; ii++){
		num_nod_t up_idx = pos + ii;
		num_nod_t down_idx = pos + ii + hlf;

		create_node(snod_half, up_idx, down_idx, prms);
	}
}

void
create_net_alt_half_cleaner(num_nod_t pos, num_nod_t sz, sornet_prms& prms){
	if(sz == 1){ return; }
	num_nod_t hlf = sz/2;
	for(num_nod_t ii = 0; ii < hlf; ii++){
		num_nod_t up_idx = pos + ii;
		num_nod_t down_idx = pos + (sz - ii - 1);

		create_node(snod_alte, up_idx, down_idx, prms);
	}
}

void
create_net_bitonic(num_nod_t pos, num_nod_t sz, sornet_prms& prms){
	if(sz == 1){ return; }
	num_nod_t hlf = sz/2;
	create_net_bitonic(pos, hlf, prms);
	create_net_bitonic(pos + hlf, hlf, prms);
	create_net_half_cleaner(pos, sz, prms);
}

void
create_net_merger(num_nod_t pos, num_nod_t sz, sornet_prms& prms){
	if(sz == 1){ return; }
	num_nod_t hlf = sz/2;
	create_net_bitonic(pos, hlf, prms);
	create_net_bitonic(pos + hlf, hlf, prms);
	create_net_alt_half_cleaner(pos, sz, prms);
}

void
create_net_sorter(num_nod_t pos, num_nod_t sz, sornet_prms& prms){
	if(sz == 1){ return; }
	num_nod_t hlf = sz/2;
	create_net_merger(pos, sz, prms);
	create_net_sorter(pos, hlf, prms);
	create_net_sorter(pos + hlf, hlf, prms);
}

void
create_sornet(num_nod_t num_to_sort){
	sornet_prms prms;

	//MUST be a power of 2
	prms.tot_nods = get_bigger_pow2(num_to_sort);
	prms.arr_nods = mc_malloc32(pre_sornode*, prms.tot_nods);

	if(THE_CNF != mc_null){
		printf("THE_CNF not null \n");

		THE_CNF->tot_pre_sorinput_nod = prms.tot_nods;
		THE_CNF->all_pre_sorinput_nod = prms.arr_nods;
	}

	prms.tot_lvs = get_tot_levels(prms.tot_nods);
	prms.arr_lvs = (mc_core_nn_t*)calloc(prms.tot_lvs, sizeof(mc_core_nn_t));

	create_net_sorter(0, prms.tot_nods, prms);

	EMU_PRT("\nTOT_INPUT_NODS=%ld TOT_LVS=%ld \n", prms.tot_nods, prms.tot_lvs);

	//long num_cores = THE_CNF->tot_cores;

	/*
	for(long aa = 0; aa < prms.tot_nods; aa++){
		pre_sornode* nod = prms.arr_nods[aa];
		EMU_CK(nod->nod_nn < num_cores);

		pre_cnf_net& cnf = THE_CNF->all_cnf[nod->nod_nn];
		cnf.tot_pre_sorinput_nod++;
	}

	for(long bb = 0; bb < num_cores; bb++){
		pre_cnf_net& cnf = THE_CNF->all_cnf[bb];
		cnf.all_pre_sorinput_nod = (pre_sornode**)calloc(cnf.tot_pre_sorinput_nod, sizeof(pre_sornode*));
	}

	for(long cc = 0; cc < prms.tot_nods; cc++){
		pre_sornode* nod = prms.arr_nods[cc];
		EMU_CK(nod->nod_nn < num_cores);

		pre_cnf_net& cnf = THE_CNF->all_cnf[nod->nod_nn];
		EMU_CK(cnf.tmp_nod_idx < cnf.tot_pre_sorinput_nod);
		cnf.all_pre_sorinput_nod[cnf.tmp_nod_idx] = nod;
		cnf.tmp_nod_idx++;
	}
	*/
}

//				pre_sornode* nod = pre_sornode::acquire();
