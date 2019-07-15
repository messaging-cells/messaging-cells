
#include "gen_hnet.h"

using namespace std;

void
hnode::print_addr(FILE* ff){
	fprintf(ff, "%ld", addr);
}

void // virtual
hnode::print_node(FILE* ff, hg_prt_mode_t md){
	print_addr(ff);
}

void // virtual
hnode_1to2::print_node(FILE* ff, hg_prt_mode_t md){
	if(md == hg_addr_prt){
		print_addr(ff);
		return;
	}
	
	fprintf(ff, "<");
	print_addr(ff);
	fprintf(ff, "i");
	in1->print_node(ff, hg_addr_prt);
	fprintf(ff, "o");
	out1->print_node(ff, hg_addr_prt);
	fprintf(ff, "o");
	out2->print_node(ff, hg_addr_prt);
	fprintf(ff, ">");
	fprintf(ff, "\n");
}

void // virtual
hnode_2to1::print_node(FILE* ff, hg_prt_mode_t md){
	if(md == hg_addr_prt){
		print_addr(ff);
		return;
	}
	
	fprintf(ff, "<");
	print_addr(ff);
	fprintf(ff, "i");
	in1->print_node(ff, hg_addr_prt);
	fprintf(ff, "i");
	in2->print_node(ff, hg_addr_prt);
	fprintf(ff, "o");
	out1->print_node(ff, hg_addr_prt);
	fprintf(ff, ">");
	fprintf(ff, "\n");
}

void // virtual
hmultinode::print_node(FILE* ff, hg_prt_mode_t md){
	if(md == hg_addr_prt){
		print_addr(ff);
		return;
	}
	
	fprintf(ff, "[");
	fprintf(ff, "%ld:", addr);
	fprintf(ff, "i(");
	for(long ii = 0; ii < (long)inputs.size(); ii++){
		GH_CK(inputs[ii] != gh_null);
		inputs[ii]->print_node(ff, hg_addr_prt);
	}
	fprintf(ff, ") o(");
	for(long ii = 0; ii < (long)outputs.size(); ii++){
		GH_CK(outputs[ii] != gh_null);
		outputs[ii]->print_node(ff, hg_addr_prt);
	}
	fprintf(ff, ")");
	fprintf(ff, "]");
	fprintf(ff, "\n");
	
}

void
hnod_net::init_nodes(long tot_nodes){
	all_to_bigger.resize(tot_nodes, gh_null);
	all_to_smaller.resize(tot_nodes, gh_null);
	for(long ii = 0; ii < (long)all_to_bigger.size(); ii++){
		hmultinode* mn = gh_null;
		
		mn = new hmultinode;
		all_to_bigger[ii] = mn;
		mn->addr = ii;
		mn->outputs.push_back(mn);
		
		mn = new hmultinode;
		all_to_smaller[ii] = mn;
		mn->addr = ii;
		mn->outputs.push_back(mn);
	}
	
	long step = 1;
	bool go_on = true;
	while(go_on){
		go_on = link_nodes(step);
		step *= 2;
	}
}

void
hnod_net::print_nodes(FILE* ff, hg_prt_mode_t md){
	for(long ii = 0; ii < (long)all_to_bigger.size(); ii++){
		all_to_bigger[ii]->print_node(ff, md);
	}
}

void
gen_hnet(long num_obj){
	long lg = (long)log2(num_obj);
	fprintf(stdout, "LOG %ld\n", lg);
	
	hnod_net the_net;
	
	the_net.init_nodes(num_obj);
	the_net.print_nodes(stdout, hg_full_prt);
}

bool
hnod_net::link_nodes(long step){
	long num_jumps = 0;
	long idx = 0;
	while((idx + step) < (long)all_to_bigger.size()){
		hmultinode* nd1 = (hmultinode*)(all_to_bigger[idx]);
		hmultinode* nd2 = (hmultinode*)(all_to_bigger[idx + step]);
		nd1->outputs.push_back(nd2);
		nd2->inputs.push_back(nd1);

		nd1 = (hmultinode*)(all_to_smaller[idx]);
		nd2 = (hmultinode*)(all_to_smaller[idx + step]);
		nd1->inputs.push_back(nd2);
		nd2->outputs.push_back(nd1);
		
		num_jumps++;
		idx += step;
	}
	return (num_jumps > 1);
}

void
hmultinode::reset_marks(){
}

bool
hmultinode::is_binnet(){
	bool bn = false;
	return bn;
}

void
print_pt_nods(vector<hnode**>& vec){
	for(long ii = 0; ii < (long)vec.size(); ii++){
		fprintf(stdout, "%ld:%p:%p\n", ii, (void*)(vec[ii]), (void*)(*(vec[ii])));
	}
}

void
hnode_box::init_all_addr(){
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		all_nodes[ii]->addr = ii;
	}
}

void
hnode_box::print_box(FILE* ff){
	fprintf(ff, "BOX\n");
	fprintf(ff, "INPUTS\n");
	for(long ii = 0; ii < (long)inputs.size(); ii++){
		(*(inputs[ii]))->print_node(ff, hg_full_prt);
	}
	fprintf(ff, "OUTPUTS\n");
	for(long ii = 0; ii < (long)outputs.size(); ii++){
		(*(outputs[ii]))->print_node(ff, hg_full_prt);
	}
	fprintf(ff, "ALL_NODES\n");
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		all_nodes[ii]->print_node(ff, hg_full_prt);
	}
	fprintf(ff, "\n");
}

hnode_box*
get_binnet_1_to_n(long num_out){
	hnode_box* bx = new hnode_box;
	long dpth = 0;
	GH_MARK_USED(dpth);
	long nout = 0;
	GH_MARK_USED(nout);
	GH_CK(num_out > 1);
	
	vector<hnode**> next_level;
	
	long out_idx = 0;
	long out_sz = 0;
	for(long aa = 0; aa < (num_out - 1); aa++){
		hnode_1to2* bnod = new hnode_1to2;
		bnod->init_to_me();
		
		if(out_idx == out_sz){
			bx->outputs = next_level;
			next_level.clear();
			out_idx = 0;
			out_sz = bx->outputs.size();
		}
		
		next_level.push_back(&(bnod->out1));
		next_level.push_back(&(bnod->out2));
		
		bx->all_nodes.push_back(bnod);
		bx->all_nodes.back()->addr = bx->all_nodes.size();

		/*
		fprintf(stdout, "=========================================\n");
		fprintf(stdout, "ITER %ld\n", aa);
		fprintf(stdout, "OUTPUTS\n");
		print_pt_nods(bx->outputs);
		fprintf(stdout, "_______\n");
		fprintf(stdout, "NEXT_LV\n");
		print_pt_nods(next_level);
		fprintf(stdout, "_______\n");
		*/
		
		if(aa == 0){
			GH_CK(bx->outputs.empty());
			GH_CK(out_idx == 0);
			GH_CK(out_sz == 0);
			
			bx->inputs.push_back(&(bnod->in1));
			GH_CK(*(bx->inputs[0]) == bnod);
			
			GH_CK(next_level.size() == 2);
			GH_CK(*(next_level[0]) == bnod);
			GH_CK(*(next_level[0]) == *(next_level[1]));
		} else {
			GH_CK(! bx->outputs.empty());
			GH_CK(out_idx < out_sz);
			
			hnode** old_pt_out = bx->outputs[out_idx];

			hnode* old_nd = *(old_pt_out);
			hnode_1to2* old_out = (hnode_1to2*)old_nd;

			//fprintf(stdout, "DOING__ %ld:%p:%p\n", out_idx, (void*)old_pt_out, (void*)old_out);
			
			bnod->in1 = old_out;
			*old_pt_out = bnod;
			
			out_idx++;
		}
	}
	
	bx->outputs.erase(bx->outputs.begin(), bx->outputs.begin() + out_idx);
	bx->outputs.insert(bx->outputs.end(), next_level.begin(), next_level.end());

	GH_CK((long)(bx->outputs.size()) == num_out);
	
	return bx;
}

int
main(int argc, char *argv[]){
	if(argc < 2){
		printf("args: <num>\n");
		return 1;
	}
	
	long vv = atol(argv[1]);
	
	hnode_box* bx = get_binnet_1_to_n(vv);
	bx->print_box(stdout);
	
	return 0;
}

