
#include "hgen_net.h"

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
hnode_1to1::print_node(FILE* ff, hg_prt_mode_t md){
	if(md == hg_addr_prt){
		print_addr(ff);
		return;
	}
	
	fprintf(ff, "<");
	if(md == hg_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in1, in1);
		fprintf(ff, "o(%p -> %p)", &out1, out1);
	} else {
		print_addr(ff);
		fprintf(ff, "i");
		in1->print_node(ff, hg_addr_prt);
		fprintf(ff, "o");
		out1->print_node(ff, hg_addr_prt);
	}
	fprintf(ff, ">");
	fprintf(ff, "\n");
}

void // virtual
hnode_direct::print_node(FILE* ff, hg_prt_mode_t md){
	if(md == hg_addr_prt){
		print_addr(ff);
		return;
	}
	
	fprintf(ff, "[");
	if(md == hg_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in1, in1);
		fprintf(ff, "o(%p -> %p)", &out1, out1);
	} else {
		if(in1 != this){
			fprintf(ff, "i");
			in1->print_node(ff, hg_addr_prt);
		} else {
			fprintf(ff, "-");
		}
		if(out1 != this){
			fprintf(ff, "o");
			out1->print_node(ff, hg_addr_prt);
		} else {
			fprintf(ff, "-");
		}
	}
	fprintf(ff, "]");
	fprintf(ff, "\n");
}

void // virtual
hnode_1to2::print_node(FILE* ff, hg_prt_mode_t md){
	if(md == hg_addr_prt){
		print_addr(ff);
		return;
	}
	
	fprintf(ff, "<");
	if(md == hg_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in1, in1);
		fprintf(ff, "o(%p -> %p)", &out1, out1);
		fprintf(ff, "o(%p -> %p)", &out2, out2);
	} else {
		print_addr(ff);
		fprintf(ff, "i");
		in1->print_node(ff, hg_addr_prt);
		fprintf(ff, "o");
		out1->print_node(ff, hg_addr_prt);
		fprintf(ff, "o");
		out2->print_node(ff, hg_addr_prt);
	}
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
	if(md == hg_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in1, in1);
		fprintf(ff, "i(%p -> %p)", &in2, in2);
		fprintf(ff, "o(%p -> %p)", &out1, out1);
	} else {
		print_addr(ff);
		fprintf(ff, "i");
		in1->print_node(ff, hg_addr_prt);
		fprintf(ff, "i");
		in2->print_node(ff, hg_addr_prt);
		fprintf(ff, "o");
		out1->print_node(ff, hg_addr_prt);
	}
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
print_pt_nods(FILE* ff, vector<hnode**>& vec){
	for(long ii = 0; ii < (long)vec.size(); ii++){
		fprintf(ff, "\t");
		if(vec[ii] != gh_null){
			fprintf(ff, "%ld:%p:%p\n", ii, (void*)(vec[ii]), (void*)(*(vec[ii])));
		} else {
			fprintf(ff, "gh_null \n");
		}
	}
}

void
hnode_box::init_all_addr(){
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		all_nodes[ii]->addr = ii;
	}
}

void
hnode_box::print_box(FILE* ff, hg_prt_mode_t md){
	fprintf(ff, "BOX\n");
	fprintf(ff, "INPUTS %ld\n", (long)inputs.size());
	for(long ii = 0; ii < (long)inputs.size(); ii++){
		hnode** ppi = inputs[ii];
		GH_CK(ppi != gh_null);
		hnode* pi = *ppi;
		GH_CK(pi != gh_null);
		
		fprintf(ff, "\t");
		if(md == hg_full_pt_prt){
			fprintf(ff, "(%p -> %p)\n", ppi, pi);
		} else {
			pi->print_node(ff, md);
		}
	}
	fprintf(ff, "OUTPUTS %ld\n", (long)outputs.size());
	for(long ii = 0; ii < (long)outputs.size(); ii++){
		hnode** ppo = outputs[ii];
		GH_CK(ppo != gh_null);
		hnode* po = *ppo;
		GH_CK(po != gh_null);
		
		fprintf(ff, "\t");
		if(md == hg_full_pt_prt){
			fprintf(ff, "(%p -> %p)\n", ppo, po);
		} else {
			po->print_node(ff, md);
		}
	}
	fprintf(ff, "ALL_NODES %ld\n", (long)all_nodes.size());
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		GH_CK(all_nodes[ii] != gh_null);
		all_nodes[ii]->print_node(ff, md);
	}
	fprintf(ff, "ALL_DIRECT %ld\n", (long)all_direct.size());
	for(long ii = 0; ii < (long)all_direct.size(); ii++){
		GH_CK(all_direct[ii] != gh_null);
		all_direct[ii]->print_node(ff, md);
	}
	fprintf(ff, "\n");
}

hnode_1to2*
hnode_box::add_1to2(){
	hnode_1to2* bnod = new hnode_1to2;
	bnod->init_to_me();
	
	all_nodes.push_back(bnod);
	all_nodes.back()->addr = all_nodes.size() - 1;
	return bnod;
}

hnode_2to1*
hnode_box::add_2to1(){
	hnode_2to1* bnod = new hnode_2to1;
	bnod->init_to_me();
	
	all_nodes.push_back(bnod);
	all_nodes.back()->addr = all_nodes.size() - 1;
	return bnod;
}

hnode_direct*
hnode_box::add_direct(){
	hnode_direct* bnod = new hnode_direct;
	bnod->init_to_me();
	
	all_direct.push_back(bnod);
	all_direct.back()->addr = all_direct.size() - 1;
	return bnod;
}

bool
gh_is_free_io(hnode** io){
	GH_CK(io != gh_null);
	hnode* nd = *io;
	GH_CK(nd != gh_null);
	return nd->has_io(io);
}

long
gh_get_first_null_idx(vector<hnode**>& vec){
	long ii = 0;
	for(ii = 0; ii < (long)vec.size(); ii++){
		if(vec[ii] == gh_null){
			break;
		}
	}
	return ii;
}

void
hnode_box::init_all_direct(){
	long ii = gh_get_first_null_idx(inputs);
	long oo = gh_get_first_null_idx(outputs);
	for(; ii < (long)inputs.size(); ii++, oo++){
		GH_CK(oo < (long)outputs.size());
		GH_CK(inputs[ii] == gh_null);
		GH_CK(outputs[oo] == gh_null);
		
		hnode_direct* dr = add_direct();
		inputs[ii] = (&(dr->in1));
		outputs[oo] = (&(dr->out1));
	}
}

hnode_box*
get_binnet_m_to_M(long num_in, long num_out){
	hnode_box* bx = new hnode_box;
	long dpth = 0;
	GH_MARK_USED(dpth);
	long nout = 0;
	GH_MARK_USED(nout);
	GH_CK(num_in > 0);
	GH_CK(num_in < num_out);

	bx->inputs.resize(num_in, gh_null);
	
	vector<hnode**> next_level;
	
	long out_idx = 0;
	long out_sz = 0;
	for(long aa = 0; aa < (num_out - num_in); aa++){
		hnode_1to2* bnod = bx->add_1to2();
		
		bool in_fst_lv = (aa < num_in);
		if(! in_fst_lv && (out_idx == out_sz)){
			bx->outputs = next_level;
			next_level.clear();
			out_idx = 0;
			out_sz = bx->outputs.size();
		}
		
		next_level.push_back(&(bnod->out1));
		next_level.push_back(&(bnod->out2));
		
		/*fprintf(stdout, "=========================================\n");
		fprintf(stdout, "ITER %ld\n", aa);
		//fprintf(stdout, "INPUTS\n");
		//print_pt_nods(stdout, bx->inputs);
		//fprintf(stdout, "_______\n");
		fprintf(stdout, "OUTPUTS\n");
		print_pt_nods(stdout, bx->outputs);
		fprintf(stdout, "_______\n");
		fprintf(stdout, "NEXT_LV\n");
		print_pt_nods(stdout, next_level);
		fprintf(stdout, "_______\n");*/
		
		
		if(in_fst_lv){
			GH_CK(bx->outputs.empty());
			GH_CK(out_idx == 0);
			GH_CK(out_sz == 0);

			//fprintf(stdout, "STARTING_aa=%ld\n", aa);
			
			bx->inputs[aa] = (&(bnod->in1));
			GH_CK(*(bx->inputs[aa]) == bnod);
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
	
	if(! bx->outputs.empty()){
		bx->outputs.erase(bx->outputs.begin(), bx->outputs.begin() + out_idx);
	}
	bx->outputs.insert(bx->outputs.end(), next_level.begin(), next_level.end());
	if((long)(bx->outputs.size()) < num_out){
		GH_CK((num_in * 2) > num_out);
		bx->outputs.resize(num_out, gh_null);
	}

	GH_CK((long)(bx->outputs.size()) == num_out);
	
	bx->init_all_direct();
	
	return bx;
}

hnode_box*
get_binnet_M_to_m(long num_in, long num_out){
	GH_CK(num_out > 0);
	GH_CK(num_in > num_out);
	
	hnode_box* obx = get_binnet_m_to_M(num_out, num_in);
	hnode_box* cbx = obx->get_2to1_net_box();
	delete obx;
	return cbx;
}

hnode_box*
get_binnet_m_to_n(long num_in, long num_out){
	hnode_box* bx = gh_null;
	
	GH_CK(num_out > 0);
	GH_CK(num_in != num_out);
	if(num_in > num_out){
		bx = get_binnet_M_to_m(num_in, num_out);
	} else {
		bx = get_binnet_m_to_M(num_in, num_out);
	}
	GH_CK(bx != gh_null);
	return bx;
}

void
hnode_box::reset_nodes(){
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		GH_CK(all_nodes[ii] != gh_null);
		delete all_nodes[ii];
	}
	inputs.clear();
	outputs.clear();
}

hnode_box*
hnode_box::get_2to1_net_box(){
	// FROM 1to2 nets to 2to1 nets
	
	long i_sz = (long)inputs.size();
	long o_sz = (long)outputs.size();
	GH_CK(i_sz != o_sz);
	GH_CK(i_sz > 0);
	GH_CK(i_sz < o_sz);
	
	hnode_box* bx = new hnode_box;
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		GH_CK(all_nodes[ii] != gh_null);
		GH_CK(all_nodes[ii]->get_kind() == hg_1_to_2_nod);
		
		bx->add_2to1();
	}
	
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		GH_CK(all_nodes[ii] != gh_null);
		hnode_1to2* onod = (hnode_1to2*)(all_nodes[ii]);
		hnode_2to1* cnod = (hnode_2to1*)(bx->all_nodes[ii]);
		GH_CK(onod->addr == ii);
		GH_CK(cnod->addr == ii);
		GH_CK(onod->get_kind() == hg_1_to_2_nod);
		GH_CK(cnod->get_kind() == hg_2_to_1_nod);
		
		hg_addr_t o_in1_addr = onod->in1->addr;
		hg_addr_t o_out1_addr = onod->out1->addr;
		hg_addr_t o_out2_addr = onod->out2->addr;
		
		cnod->out1 = bx->all_nodes[o_in1_addr];
		cnod->in1 = bx->all_nodes[o_out1_addr];
		cnod->in2 = bx->all_nodes[o_out2_addr];
		
		if(cnod->out1 == cnod){
			bx->outputs.push_back(&(cnod->out1));
		}
		if(cnod->in1 == cnod){
			bx->inputs.push_back(&(cnod->in1));
		}
		if(cnod->in2 == cnod){
			bx->inputs.push_back(&(cnod->in2));
		}
	}
	
	long num_in = o_sz;
	long num_out = i_sz;
	if((long)(bx->inputs.size()) < num_in){
		bx->inputs.resize(num_in, gh_null);
	}
	if((long)(bx->outputs.size()) < num_out){
		bx->outputs.resize(num_out, gh_null);
	}

	GH_CK((long)(bx->inputs.size()) == num_in);
	GH_CK((long)(bx->outputs.size()) == num_out);
	
	bx->init_all_direct();
	
	return bx;
}

void
hnode_box::move_nodes_to(hnode_box& bx){
	for(long ii = 0; ii < (long)inputs.size(); ii++){
		if(gh_is_free_io(inputs[ii])){
			bx.inputs.push_back(inputs[ii]);
		}
		inputs[ii] = gh_null;
	}
	inputs.clear();
	for(long ii = 0; ii < (long)outputs.size(); ii++){
		if(gh_is_free_io(outputs[ii])){
			bx.outputs.push_back(outputs[ii]);
		}
		outputs[ii] = gh_null;
	}
	outputs.clear();
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		GH_CK(all_nodes[ii] != gh_null);
		bx.all_nodes.push_back(all_nodes[ii]);
		bx.all_nodes.back()->addr = bx.all_nodes.size() - 1;
		all_nodes[ii] = gh_null;
	}
	all_nodes.clear();
	for(long ii = 0; ii < (long)all_direct.size(); ii++){
		GH_CK(all_direct[ii] != gh_null);
		hnode_direct* dr = all_direct[ii];
		bx.all_direct.push_back(dr);
		bx.all_direct.back()->addr = bx.all_direct.size() - 1;
		all_direct[ii] = gh_null;
	}
	all_direct.clear();
}

void
hnode_2_to_2_box::init_box(){
	hnode_1to2* nd1 = add_1to2();
	hnode_1to2* nd2 = add_1to2();
	hnode_2to1* nd3 = add_2to1();
	hnode_2to1* nd4 = add_2to1();
	
	inputs.resize(2, gh_null);
	inputs[0] = (&(nd1->in1));
	inputs[1] = (&(nd2->in1));
	
	outputs.resize(2, gh_null);
	outputs[0] = (&(nd3->out1));
	outputs[1] = (&(nd4->out1));
	
	nd1->out1 = nd3;
	nd1->out2 = nd4;
	nd2->out1 = nd3;
	nd2->out2 = nd4;
	
	nd3->in1 = nd1;
	nd3->in2 = nd2;
	nd4->in1 = nd1;
	nd4->in2 = nd2;
}

void
hnode_2_to_3_box::init_box(){
	hnode_box* bx1 = get_binnet_m_to_n(1, 3);
	hnode_box* bx2 = get_binnet_m_to_n(1, 3);
	hnode_2to1* nd1 = add_2to1();
	hnode_2to1* nd2 = add_2to1();
	hnode_2to1* nd3 = add_2to1();

	outputs.resize(3, gh_null);
	outputs[0] = (&(nd1->out1));
	outputs[1] = (&(nd2->out1));
	outputs[2] = (&(nd3->out1));
	
	bx1->connect_output_to_node_input(0, *nd1, 0);
	bx1->connect_output_to_node_input(1, *nd2, 0);
	bx1->connect_output_to_node_input(2, *nd3, 0);

	bx2->connect_output_to_node_input(0, *nd1, 1);
	bx2->connect_output_to_node_input(1, *nd2, 1);
	bx2->connect_output_to_node_input(2, *nd3, 1);

	/*
	fprintf(stdout, "BOX1\n");
	bx1->print_box(stdout, hg_full_pt_prt);
	fprintf(stdout, "BOX2\n");
	bx2->print_box(stdout, hg_full_pt_prt);
	fprintf(stdout, "nd1\n");
	nd1->print_node(stdout, hg_full_pt_prt);
	fprintf(stdout, "nd2\n");
	nd2->print_node(stdout, hg_full_pt_prt);
	fprintf(stdout, "nd3\n");
	nd3->print_node(stdout, hg_full_pt_prt);
	*/
	
	hnode_box& dest = *this;
	bx1->move_nodes_to(dest);
	bx2->move_nodes_to(dest);
	
	delete bx1;
	delete bx2;

	init_all_addr();
}

void
hnode_3_to_2_box::init_box(){
	hnode_box* bx1 = get_binnet_m_to_n(3, 1);
	hnode_box* bx2 = get_binnet_m_to_n(3, 1);
	hnode_1to2* nd1 = add_1to2();
	hnode_1to2* nd2 = add_1to2();
	hnode_1to2* nd3 = add_1to2();
	
	inputs.resize(3, gh_null);
	inputs[0] = (&(nd1->in1));
	inputs[1] = (&(nd2->in1));
	inputs[2] = (&(nd3->in1));

	bx1->connect_node_output_to_input(*nd1, 0, 0);
	bx1->connect_node_output_to_input(*nd2, 0, 1);
	bx1->connect_node_output_to_input(*nd3, 0, 2);

	bx2->connect_node_output_to_input(*nd1, 1, 0);
	bx2->connect_node_output_to_input(*nd2, 1, 1);
	bx2->connect_node_output_to_input(*nd3, 1, 2);
	
	hnode_box& dest = *this;
	bx1->move_nodes_to(dest);
	bx2->move_nodes_to(dest);
	
	delete bx1;
	delete bx2;
	
	init_all_addr();
}

int
test_m_to_n(int argc, char *argv[]){
	if(argc < 3){
		printf("%s <num_in> <num_out>\n", argv[0]);
		return 1;
	}
	
	long mm = atol(argv[1]);
	long nn = atol(argv[2]);

	hnode_box* bx = get_binnet_m_to_n(mm, nn);
	GH_MARK_USED(bx);
	
	bx->print_box(stdout, hg_full_prt);
	
	return 0;
}

int
test_bases(int argc, char *argv[]){
	if(argc < 2){
		printf("%s (0 | 1)\n", argv[0]);
		return 1;
	}
	
	long mm = atol(argv[1]);
	
	hnode_box* bx = gh_null;
	GH_MARK_USED(bx);
	if(mm == 0){
		bx = new hnode_2_to_3_box;
	} else {
		bx = new hnode_3_to_2_box;
	}
	
	bx->print_box(stdout, hg_full_prt);
	delete bx;
	
	return 0;
}

int
main(int argc, char *argv[]){
	int resp = 0;
	resp = test_bases(argc, argv);
	return resp;
}
