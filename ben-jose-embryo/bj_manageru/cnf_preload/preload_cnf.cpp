
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "preload.hh"

pre_load_cnf* THE_CNF = mc_null;

grip ava_pre_sornode;
grip ava_pre_cnf_node;
grip ava_pre_cnf_net;

MCK_DEFINE_MEM_METHODS_AND_GET_AVA(pre_sornode, 32, ava_pre_sornode, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(pre_cnf_node, 32, ava_pre_cnf_node, 0)
MCK_DEFINE_MEM_METHODS_AND_GET_AVA(pre_cnf_net, 32, ava_pre_cnf_net, 0)

void init_node_arr(long sz, pre_cnf_node** arr, node_kind_t kk){
	for(long aa = 0; aa < sz; aa++){
		arr[aa] = pre_cnf_node::acquire();
		arr[aa]->ki = kk;
		if(kk == nd_pos){
			arr[aa]->id = aa + 1;
		}
		if(kk == nd_neg){
			arr[aa]->id = -(aa + 1);
		}
	}
}

pre_cnf_node*
get_lit(long lit_id){
	if(lit_id > 0){
		pre_cnf_node* pos =  THE_CNF->all_pos[lit_id - 1];
		PTD_CK(pos->id == lit_id);
		return pos;
	}
	PTD_CK(lit_id < 0);
	pre_cnf_node* neg =  THE_CNF->all_neg[(-lit_id) - 1];
	PTD_CK(neg->id == lit_id);
	return neg;
}

void
print_cnf(){
	for(long aa = 0; aa < THE_CNF->tot_ccls; aa++){
		pre_cnf_node* ccl =  THE_CNF->all_ccl[aa];

		printf("[");

		binder * fst, * lst, * wrk;
		binder* lits = &(ccl->all_agts);

		fst = lits->bn_right;
		lst = lits;
		for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
			agent_ref* ref = (agent_ref*)wrk;
			pre_cnf_node* lit = (pre_cnf_node*)(ref->glb_agent_ptr);

			printf("%ld ", lit->id);
		}

		printf("] \n");
	}
}

void
manageru_print_nods(){
	printf("ALL_NODS {");
	for(long aa = 0; aa < THE_CNF->tot_tmp_pre_load_nods; aa++){
		pre_cnf_node* nod =  THE_CNF->all_tmp_pre_load_nods[aa];
		printf("[k%d id%ld sz%ld] \n", nod->ki, nod->id, nod->pre_sz);
	}
	printf("} \n");
}

void
print_all_nods(binder& grip){
	binder * fst, * lst, * wrk;
	binder* grp = &(grip);

	fst = grp->bn_right;
	lst = grp;
	for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
		pre_cnf_node* nod = (pre_cnf_node*)wrk;
		printf("[k%d id%ld sz%ld] ", nod->ki, nod->id, nod->pre_sz);
	}
}

void
print_pre_cnf_nets(){
	printf("ALL_CNFS {\n");
	for(long aa = 0; aa < THE_CNF->tot_workerus; aa++){
		pre_cnf_net& cnf =  THE_CNF->all_cnf[aa];

		printf("CNF %ld ======================================= \n", aa);

		//printf("[k%d id%ld sz%ld] \n", nod->ki, nod->id, nod->sz);
		printf("\tCCLS[");
		print_all_nods(cnf.all_pre_neu);
		printf("\t] \n");

		printf("\tPOS[");
		print_all_nods(cnf.all_pre_pos);
		printf("\t] \n");

		printf("\tNEG[");
		print_all_nods(cnf.all_pre_neg);
		printf("\t] \n");
	}
	printf("} \n");
}

int 
cmp_nodes(const void * p1, const void * p2){
	long sz1 = (*((pre_cnf_node **)p1))->pre_sz;
	long sz2 = (*((pre_cnf_node **)p2))->pre_sz;
	if(sz1 < sz2){ return -1; }
	if(sz1 > sz2){ return 1; }
	return 0;
}

void
check_node_sz(pre_node_sz_t sz){
	if(sz > THE_CNF->max_nod_sz){
		mck_abort(9, mc_cstr(
			"CNF node too big. Variable in too many clauses or clause too big. (BJ_MAX_NODE_SZ). Fix CNF."));
	}
	PTD_CK(sz < THE_CNF->max_nod_sz);
}

void
preload_cnf(long sz, const long* arr){

	THE_CNF->max_nod_sz = BJ_MAX_NODE_SZ;

	long num_ccls = THE_CNF->tot_ccls;
	long num_vars = THE_CNF->tot_vars;
	long num_lits = THE_CNF->tot_lits;
	long num_workerus = THE_CNF->tot_workerus;

	if(num_ccls == 0){
		return;
	}

	THE_CNF->tot_tmp_pre_load_nods = num_ccls + num_vars;
	long num_tmp_pre_load_nods = THE_CNF->tot_tmp_pre_load_nods;

	agent_ref::separate(2 * num_lits);
	pre_cnf_node::separate(num_ccls + (2 * num_vars));

	printf("tot_lits=%ld tot_vars=%ld tot_ccls=%ld \n", 
			THE_CNF->tot_lits, THE_CNF->tot_vars, THE_CNF->tot_ccls);

	THE_CNF->all_ccl = mc_malloc32(pre_cnf_node*, num_ccls);
	THE_CNF->all_pos = mc_malloc32(pre_cnf_node*, num_vars);
	THE_CNF->all_neg = mc_malloc32(pre_cnf_node*, num_vars);
	//THE_CNF->all_tmp_pre_load_nods = mc_malloc32(pre_cnf_node*, num_tmp_pre_load_nods);
	THE_CNF->all_tmp_pre_load_nods = (pre_cnf_node**) malloc(num_tmp_pre_load_nods * sizeof(pre_cnf_node*));

	THE_CNF->all_cnf = mc_malloc32(pre_cnf_net, num_workerus);
	for(int bb = 0; bb < num_workerus; bb++){ 
		new (&(THE_CNF->all_cnf[bb])) pre_cnf_net(); 
	} 

	init_node_arr(num_ccls, THE_CNF->all_ccl, nd_neu);
	init_node_arr(num_vars, THE_CNF->all_pos, nd_pos);
	init_node_arr(num_vars, THE_CNF->all_neg, nd_neg);

	memcpy(THE_CNF->all_tmp_pre_load_nods, THE_CNF->all_ccl, num_ccls * sizeof(pre_cnf_node*));
	memcpy(THE_CNF->all_tmp_pre_load_nods + num_ccls, THE_CNF->all_pos, num_vars * sizeof(pre_cnf_node*));

	long nn = 0;

	PTD_CK(nn < num_ccls);
	pre_cnf_node* ccl = THE_CNF->all_ccl[nn];
	ccl->id = nn;

	for(long ii = 0; ii < sz; ii++){
		long nio_id = arr[ii];
		PTD_CK(ccl != mc_null);
		
		if(nio_id != 0){
			pre_cnf_node* lit = get_lit(nio_id);
			PTD_CK(lit != NULL);

			agent_ref* rli = agent_ref::acquire();
			rli->glb_agent_ptr = lit;
			ccl->all_agts.bind_to_my_left(*rli);
			ccl->pre_sz++;
			check_node_sz(ccl->pre_sz);

			agent_ref* rcl = agent_ref::acquire();
			rcl->glb_agent_ptr = ccl;
			lit->all_agts.bind_to_my_left(*rcl);
			lit->pre_sz++;
			check_node_sz(lit->pre_sz);

			if(nio_id < 0){
				pre_cnf_node* opp = get_lit(-nio_id);
				opp->pre_sz++;
			}
		} else {
			nn++;
			if(nn < num_ccls){
				ccl = THE_CNF->all_ccl[nn];
				ccl->id = nn;
			} else {
				ccl = mc_null;
			}
		}
	}

	qsort(THE_CNF->all_tmp_pre_load_nods, num_tmp_pre_load_nods, sizeof(pre_cnf_node*), cmp_nodes);

	long kk = 0;
	for(long aa = 0; aa < num_tmp_pre_load_nods; aa++){
		if(kk == num_workerus){ kk = 0; }
		pre_cnf_node* nod = THE_CNF->all_tmp_pre_load_nods[aa];
		pre_cnf_net& cnf = THE_CNF->all_cnf[kk];
		PTD_CK(nod->is_alone());
		cnf.tot_pre_rels += nod->pre_sz;
		switch(nod->ki){
			case nd_pos:
			{
				pre_cnf_node* opp = get_lit(-(nod->id));

				nod->opp_nod = opp;
				opp->opp_nod = nod;

				PTD_CK(nod->loaded == mc_null);
				PTD_CK(opp->loaded == mc_null);

				cnf.all_pre_pos.bind_to_my_left(*nod);
				cnf.all_pre_neg.bind_to_my_left(*opp);

				cnf.tot_pre_vars++;
			}
			break;
			case nd_neu:
				cnf.all_pre_neu.bind_to_my_left(*nod);
				cnf.tot_pre_neus++;
				cnf.tot_pre_lits += nod->pre_sz;
			break;
			default:
				mck_abort(9, mc_cstr("Bad node cnf kind"));
			break;
		}
		kk++;
	}

	//num_nod_t num_to_sort = mc_max((num_vars * 2), num_ccls);
	create_sornet(BJ_DBG_TOT_INPUT_SORNODES);
	create_ranknet(BJ_DBG_TOT_INPUT_RNKNODES);
}



