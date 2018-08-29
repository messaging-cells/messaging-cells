
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

void
add_sornod_to_glb_cnf(pre_sornode* nod, mc_workeru_nn_t& nxt_nn){
	if(THE_CNF != mc_null){
		long num_workerus = THE_CNF->tot_workerus;
		PTD_CK(nxt_nn < num_workerus);

		nod->nod_nn = nxt_nn;

		pre_cnf_net& cnf = THE_CNF->all_cnf[nxt_nn];
		cnf.tot_pre_sornods++;
		cnf.all_pre_sornods.bind_to_my_left(*nod);

		nxt_nn++;
		if(nxt_nn == num_workerus){ nxt_nn = 0; }
		PTD_CK(nxt_nn < num_workerus);
	}
}

pre_sornode*
create_node(sornod_kind_t knd, num_nod_t up_idx, num_nod_t down_idx, sornet_prms& prms){
	pre_sornode* nod = pre_sornode::acquire();
	MCK_CK(nod != mc_null);
	
	mc_workeru_nn_t ptd_up_nid = 0;
	mc_workeru_nn_t ptd_down_nid = 0;
	MC_MARK_USED(ptd_up_nid);
	MC_MARK_USED(ptd_down_nid);
	
	prms.curr_nod_id++;
	nod->nod_id = prms.curr_nod_id;

	PTD_CK(up_idx < down_idx);
	PTD_CK(up_idx < prms.tot_nods);
	PTD_CK(down_idx < prms.tot_nods);

	nod->up_idx = up_idx;
	nod->down_idx = down_idx;

	nod->out_up = prms.arr_nods[up_idx];
	nod->out_down = prms.arr_nods[down_idx];

	prms.arr_nods[up_idx] = nod;
	prms.arr_nods[down_idx] = nod;

	if(nod->out_up != mc_null){
		nod->level = nod->out_up->level + 1;
		PTD_CK(nod->out_down != mc_null);
		PTD_CK(nod->out_down->level == nod->out_up->level);

		ptd_up_nid = nod->out_up->nod_id;
		ptd_down_nid = nod->out_down->nod_id;

		nod->up_conn = nod->out_up->get_conn_kind(up_idx);
		nod->down_conn = nod->out_down->get_conn_kind(down_idx);
	}

	PTD_CK(nod->level >= 0);
	PTD_CK(nod->level < prms.tot_lvs);
	
	if(nod->level == prms.first_lv_for_merge_sz){
		nod->srt_sz = prms.curr_merge_sz;
	}

	mc_workeru_nn_t& nxt_nn = prms.arr_lvs[nod->level];
	add_sornod_to_glb_cnf(nod, nxt_nn);

	PTD_CK(knd != snod_invalid);
	PTD_PRT("%s_NOD (%ld)  %ld[%ld %ld]%ld \t(%ld %ld) \n", ((knd == snod_alte)?("ALT"):("HLF")), 
			nod->nod_id, nod->level, up_idx, down_idx, nod->srt_sz, ptd_up_nid, ptd_down_nid);
	ZNQ_CODE(printf("%s_NOD (%ld)  %ld[%ld %ld] \t(%d %d) \n", ((knd == snod_alte)?("ALT"):("HLF")), 
				nod->nod_id, nod->level, up_idx, down_idx, ptd_up_nid, ptd_down_nid));

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
	
	prms.curr_merge_sz = sz;
	pre_sornode* fst_nod = prms.arr_nods[pos];
	if(fst_nod != mc_null){
		prms.first_lv_for_merge_sz = fst_nod->level + 1;
		PTD_PRT("\nNET_MERGE_SZ=%ld FST_LV=%ld \n", prms.curr_merge_sz, prms.first_lv_for_merge_sz);
	}
	
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
	mc_init_arr_vals(prms.tot_nods, prms.arr_nods, mc_null);

	if(THE_CNF != mc_null){
		printf("THE_CNF not null \n");

		THE_CNF->tot_pre_sorinput_nod = prms.tot_nods;
		THE_CNF->all_pre_sorinput_nod = prms.arr_nods;
	}

	prms.tot_lvs = get_tot_levels(prms.tot_nods);
	prms.arr_lvs = (mc_workeru_nn_t*)calloc(prms.tot_lvs, sizeof(mc_workeru_nn_t));

	create_net_sorter(0, prms.tot_nods, prms);

	ZNQ_CODE(printf("\nTOT_INPUT_NODS=%ld TOT_LVS=%ld \n", prms.tot_nods, prms.tot_lvs));
	PTD_PRT("\nTOT_INPUT_NODS=%ld TOT_LVS=%ld \n", prms.tot_nods, prms.tot_lvs);
}

void
bj_set_rnk_out(pre_sornode* nod, num_nod_t idx, pre_sornode* out){
	PTD_CK(nod != mc_null);
	PTD_CK(out != mc_null);
	
	if(nod->up_idx == idx){
		nod->out_up = out;
	} else{
		PTD_CK(nod->down_idx == idx);
		nod->out_down = out;
	}
}

void
add_ranknod_to_glb_cnf(pre_sornode* nod, mc_workeru_nn_t& nxt_nn){
	if(THE_CNF != mc_null){
		long num_workerus = THE_CNF->tot_workerus;
		PTD_CK(nxt_nn < num_workerus);

		nod->nod_nn = nxt_nn;

		pre_cnf_net& cnf = THE_CNF->all_cnf[nxt_nn];
		cnf.tot_pre_rnknods++;
		cnf.all_pre_rnknods.bind_to_my_left(*nod);

		nxt_nn++;
		if(nxt_nn == num_workerus){ nxt_nn = 0; }
		PTD_CK(nxt_nn < num_workerus);
	}
}

void
create_ranknet(num_nod_t num_to_rank){
	if(THE_CNF == mc_null){
		printf("THE_CNF IS null !!! \n");
		return;
	}
	//long num_workerus = THE_CNF->tot_workerus;

	sornet_prms prms;
	
	num_nod_t tot_out_nod = num_to_rank;
	pre_sornode**	all_out_nod = mc_malloc32(pre_sornode*, tot_out_nod);;
	mc_init_arr_vals(tot_out_nod, all_out_nod, mc_null);

	num_nod_t tot_in_nod = num_to_rank;
	pre_sornode**	all_in_nod = mc_malloc32(pre_sornode*, tot_in_nod);
	mc_init_arr_vals(tot_in_nod, all_in_nod, mc_null);

	THE_CNF->tot_pre_rank_in_nod = tot_in_nod;
	THE_CNF->all_pre_rank_in_nod = all_in_nod;
	
	long jmp_sz = 1;
	bool lv_has_jmps = false;
	num_nod_t fst = 0;
	num_nod_t nod_id = 0;
	
	while(true){
		bool added_jmp = false;
		mc_workeru_nn_t nxt_nn = 0;
		for(num_nod_t  aa = fst; aa < tot_out_nod; aa += (jmp_sz + 1)){
			num_nod_t bb = aa + jmp_sz;
			if(bb >= tot_out_nod){
				break;
			}
			added_jmp = true;
			
			pre_sornode* nod = pre_sornode::acquire();
			MCK_CK(nod != mc_null);
			
			nod_id++;

			nod->nod_id = nod_id;
			nod->up_idx = aa;
			nod->down_idx = bb;
			
			PTD_DBG_CODE(
				num_nod_t n1_id = 0;
				num_nod_t n2_id = 0;
			);
			
			pre_sornode* n1 = all_out_nod[aa];
			pre_sornode* n2 = all_out_nod[bb];
			if(n1 == mc_null){
				all_out_nod[aa] = nod;
				all_in_nod[aa] = nod;
			} else {
				PTD_CK(all_in_nod[aa] != mc_null);
				PTD_DBG_CODE(n1_id = n1->nod_id);
				bj_set_rnk_out(n1, aa, nod);
				all_out_nod[aa] = nod;
			}
			
			if(n2 == mc_null){
				all_out_nod[bb] = nod;
				all_in_nod[bb] = nod;
			} else {
				PTD_CK(all_in_nod[bb] != mc_null);
				PTD_DBG_CODE(n2_id = n2->nod_id);
				bj_set_rnk_out(n2, bb, nod);
				all_out_nod[bb] = nod;
			}

			add_ranknod_to_glb_cnf(nod, nxt_nn);
			
			PTD_PRT("RNK_NOD_%ld %ld[%ld %ld] \t(%ld %ld) \n", nod->nod_id, jmp_sz, aa, bb, n1_id, n2_id);
		}
		bool inc_sz = false;
		if(added_jmp){
			lv_has_jmps = true;
			fst++;
			if(fst == (jmp_sz + 1)){
				inc_sz = true;
			}
		} else {
			inc_sz = true;
		}
		if(inc_sz){
			if(! lv_has_jmps){
				break;
			}
			lv_has_jmps = false;
			fst = 0;
			jmp_sz *= 2;
		}
	}
}

