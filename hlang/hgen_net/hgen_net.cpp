
#include "hgen_net.h"

using namespace std;

hgen_globals GH_GLOBALS;

void
print_pt_nods(FILE* ff, ppnode_vec_t& vec){
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
hnode::print_addr(FILE* ff){
	fprintf(ff, "%ld", addr);
	fflush(ff);
}

void // virtual
hnode::print_node(FILE* ff, hg_prt_mode_t md){
	print_addr(ff);
	fflush(ff);
}

void // virtual
hnode_1to1::print_node(FILE* ff, hg_prt_mode_t md){
	fflush(ff);
	GH_CK(ck_connections());
	if(md == hg_addr_prt){
		print_addr(ff);
		return;
	}
	
	fprintf(ff, "[");
	if(md == hg_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in0, in0);
		fprintf(ff, "o(%p -> %p)", &out0, out0);
	} else {
		print_addr(ff);
		fprintf(ff, "i");
		in0->print_node(ff, hg_addr_prt);
		fprintf(ff, "o");
		out0->print_node(ff, hg_addr_prt);
	}
	fprintf(ff, "]");
	fprintf(ff, "\n");
	fflush(ff);
}

void // virtual
hnode_direct::print_node(FILE* ff, hg_prt_mode_t md){
	fflush(ff);
	GH_CK(ck_connections());
	fprintf(ff, "dr");
	hnode_1to1::print_node(ff, md);
	fflush(ff);
}

void // virtual
hnode_target::print_node(FILE* ff, hg_prt_mode_t md){
	fflush(ff);
	GH_CK(ck_connections());
	fprintf(ff, "tg");
	hnode_1to1::print_node(ff, md);
	fflush(ff);
}

void
hrange::print_range(FILE* ff){
	fprintf(ff, "(%ld,%ld)", min, max);
}

void // virtual
hnode_1to2::print_node(FILE* ff, hg_prt_mode_t md){
	fflush(ff);
	if(md == hg_addr_prt){
		print_addr(ff);
		return;
	}
	
	fprintf(ff, "<");
	fprintf(ff, "%c", gh_get_col_chr(node_flags));
	if(md == hg_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in0, in0);
		fprintf(ff, "o(%p -> %p)", &out0, out0);
		fprintf(ff, "o(%p -> %p)", &out1, out1);
	} else {
		print_addr(ff);
		fprintf(ff, "i");
		in0->print_node(ff, hg_addr_prt);
		fprintf(ff, "o");
		out0->print_node(ff, hg_addr_prt);
		fprintf(ff, "o");
		out1->print_node(ff, hg_addr_prt);
	}
	fprintf(ff, ">");
	msg0.rng.print_range(ff);
	msg1.rng.print_range(ff);
	fprintf(ff, "\n");
	fflush(ff);
	GH_CK(ck_connections());
}

void // virtual
hnode_2to1::print_node(FILE* ff, hg_prt_mode_t md){
	fflush(ff);
	if(md == hg_addr_prt){
		print_addr(ff);
		return;
	}
	
	fprintf(ff, "<");
	if(md == hg_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in0, in0);
		fprintf(ff, "i(%p -> %p)", &in1, in1);
		fprintf(ff, "o(%p -> %p)", &out0, out0);
	} else {
		print_addr(ff);
		fprintf(ff, "i");
		in0->print_node(ff, hg_addr_prt);
		fprintf(ff, "i");
		in1->print_node(ff, hg_addr_prt);
		fprintf(ff, "o");
		out0->print_node(ff, hg_addr_prt);
	}
	fprintf(ff, ">");
	fprintf(ff, "\n");
	fflush(ff);
	GH_CK(ck_connections());
}

void
gh_print_io(FILE* ff, hg_prt_mode_t md, ppnode_vec_t& all_io){
	fflush(ff);
	for(long ii = 0; ii < (long)all_io.size(); ii++){
		hnode** ppi = all_io[ii];
		if(ppi != gh_null){
			hnode* pi = *ppi;
			GH_CK(pi != gh_null);
			
			fprintf(ff, "\t");
			if(md == hg_full_pt_prt){
				fprintf(ff, "(%p -> %p)\n", ppi, pi);
			} else {
				pi->print_node(ff, md);
			}
		} else {
			fprintf(ff, "%ld gh_null IO\n", ii);
		}
	}
	fflush(ff);
}

void
hnode_box::print_box(FILE* ff, hg_prt_mode_t md){
	fprintf(ff, "BOX\n");
	fprintf(ff, "INPUTS %ld\n", (long)inputs.size());
	gh_print_io(ff, md, inputs);
	fprintf(ff, "OUTPUTS %ld\n", (long)outputs.size());
	gh_print_io(ff, md, outputs);
	fprintf(ff, "ALL_NODES %ld\n", (long)all_nodes.size());
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		if(all_nodes[ii] != gh_null){
			all_nodes[ii]->print_node(ff, md);
		} else {
			fprintf(ff, "%ld gh_null NODE\n", ii);
		}
	}
	fprintf(ff, "ALL_DIRECT %ld\n", (long)all_direct.size());
	for(long ii = 0; ii < (long)all_direct.size(); ii++){
		if(all_direct[ii] != gh_null){
			all_direct[ii]->print_node(ff, md);
		} else {
			fprintf(ff, "%ld gh_null DIRECT\n", ii);
		}
	}
	fprintf(ff, "\n");
	fflush(ff);
}

void
htarget_box::print_box(FILE* ff, hg_prt_mode_t md){
	GH_CK(target != gh_null);
	hnode_box::print_box(ff, md);
	fprintf(ff, "LFT_IN %ld\n", (long)lft_in.size());
	gh_print_io(ff, md, lft_in);
	fprintf(ff, "LFT_OUT %ld\n", (long)lft_out.size());
	gh_print_io(ff, md, lft_out);
	fprintf(ff, "RGT_IN %ld\n", (long)rgt_in.size());
	gh_print_io(ff, md, rgt_in);
	fprintf(ff, "RGT_OUT %ld\n", (long)rgt_out.size());
	gh_print_io(ff, md, rgt_out);
	fprintf(ff, "TARGET \n");
	target->print_node(ff, md);
	fprintf(ff, "++++++++++++\n");
	fflush(ff);
}

void
hlognet_box::print_box(FILE* ff, hg_prt_mode_t md){
	hnode_box::print_box(ff, md);
	fprintf(ff, "ALL_TARGET %ld\n", (long)all_targets.size());
	for(long ii = 0; ii < (long)all_targets.size(); ii++){
		GH_CK(all_targets[ii] != gh_null);
		all_targets[ii]->print_node(ff, md);
	}
	fflush(ff);
	GH_COND_PRT((GH_GLOBALS.DBG_LV > 0), "flag1\n");
}

bool
gh_is_free_io(hnode** io){
	GH_CK(io != gh_null);
	hnode* nd = *io;
	GH_CK(nd != gh_null);
	return nd->has_io(io);
}

long
gh_get_first_null_idx(ppnode_vec_t& vec){
	long ii = 0;
	for(ii = 0; ii < (long)vec.size(); ii++){
		if(vec[ii] == gh_null){
			break;
		}
	}
	return ii;
}

hnode_box*
gh_get_binnet_sm_to_bm(long num_in, long num_out){
	hnode_box* bx = new hnode_box;
	long dpth = 0;
	GH_MARK_USED(dpth);
	long nout = 0;
	GH_MARK_USED(nout);
	GH_CK(num_in > 0);
	GH_CK(num_in < num_out);

	bx->inputs.resize(num_in, gh_null);
	
	bx->start_color();
	
	ppnode_vec_t next_level;
	
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
			bx->switch_color();
		}
		
		next_level.push_back(&(bnod->out0));
		next_level.push_back(&(bnod->out1));
		
		bnod->set_color_as_in(*bx);
		
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
			
			bx->inputs[aa] = (&(bnod->in0));
			GH_CK(*(bx->inputs[aa]) == bnod);
		} else {
			GH_CK(! bx->outputs.empty());
			GH_CK(out_idx < out_sz);
			
			hnode** old_pt_out = bx->outputs[out_idx];

			hnode* old_nd = *(old_pt_out);
			hnode_1to2* old_out = (hnode_1to2*)old_nd;

			//fprintf(stdout, "DOING__ %ld:%p:%p\n", out_idx, (void*)old_pt_out, (void*)old_out);
			
			bnod->in0 = old_out;
			*old_pt_out = bnod;
			
			out_idx++;
		}
	}
	
	if(! bx->outputs.empty()){
		bx->outputs.erase(bx->outputs.begin(), bx->outputs.begin() + out_idx);
	}
	bx->outputs.insert(bx->outputs.begin(), next_level.begin(), next_level.end());
	if((long)(bx->outputs.size()) < num_out){
		GH_CK((num_in * 2) > num_out);
		bx->outputs.resize(num_out, gh_null);
	}

	GH_CK((long)(bx->outputs.size()) == num_out);
	
	bx->init_all_direct();
	
	gh_init_sm_to_bm_ranges(bx->outputs, bx->get_last_color(), bx);
	
	return bx;
}

hnode_box*
gh_get_binnet_bm_to_sm(long num_in, long num_out){
	GH_CK(num_out > 0);
	GH_CK(num_in > num_out);
	
	hnode_box* obx = gh_get_binnet_sm_to_bm(num_out, num_in);
	hnode_box* cbx = obx->convert_net_from_1to2_to_2to1();
	delete obx;
	return cbx;
}

hnode_box*
gh_get_binnet_m_to_n(long num_in, long num_out){
	hnode_box* bx = gh_null;
	
	GH_CK(num_out > 0);
	GH_CK(num_in != num_out);
	if(num_in > num_out){
		bx = gh_get_binnet_bm_to_sm(num_in, num_out);
	} else {
		bx = gh_get_binnet_sm_to_bm(num_in, num_out);
	}
	GH_CK(bx != gh_null);
	return bx;
}

bool
hnode::ck_link(hnode* lnk, gh_io_kind_t kk){
	hg_nk_lnk_mod_t mod = GH_GLOBALS.CK_LINK_MODE;
	GH_CK(mod != hg_invalid_ck_mod);
	
	hnode* nd = this;
	if(lnk == gh_null){
		if(mod != hg_soft_ck_mod){
			return false;
		}
		return true;
	}
	if(lnk == nd){
		if((mod != hg_soft_ck_mod) && (mod != hg_valid_self_ck_mod)){
			return false;
		}
		return true;
	}
	GH_CK(lnk != gh_null);

	hnode* lk0 = gh_null;
	hnode* lk1 = gh_null;
	if(kk == gh_out_kind){
		lk0 = lnk->get_in0();
		lk1 = lnk->get_in1();
	} else {
		GH_CK(kk == gh_in_kind);
		lk0 = lnk->get_out0();
		lk1 = lnk->get_out1();
	}
	bool is_nd = ((lk0 == nd) || (lk1 == nd));
	
	return is_nd;
}

void gh_init_all_addr(vector<hnode*>& all_nd, long fst){
	for(long ii = 0; ii < (long)all_nd.size(); ii++){
		if(all_nd[ii] != gh_null){
			all_nd[ii]->addr = fst + ii;
		}
	}
}
	
void
hnode_box::init_all_addr(){
	gh_init_all_addr(all_nodes, 0);
}

hnode_1to2*
hnode_box::add_1to2(bool ini_rngs){
	hnode_1to2* bnod = new hnode_1to2;
	bnod->init_to_me();
	
	if(ini_rngs){
		bnod->msg0.rng.min = 0;
		bnod->msg0.rng.max = 0;
		bnod->msg1.rng.min = 1;
		bnod->msg1.rng.max = 1;
	}
	
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

void
hnode_box::fill_with_directs(ppnode_vec_t& all_in, ppnode_vec_t& all_out){
	long ii = gh_get_first_null_idx(all_in);
	long oo = gh_get_first_null_idx(all_out);
	for(; ii < (long)all_in.size(); ii++, oo++){
		GH_CK(oo < (long)all_out.size());
		GH_CK(all_in[ii] == gh_null);
		GH_CK(all_out[oo] == gh_null);
		
		hnode_direct* dr = add_direct();
		all_in[ii] = (&(dr->in0));
		all_out[oo] = (&(dr->out0));
		
		dr->set_direct_idx(gh_in_kind, all_in, ii);
		dr->set_direct_idx(gh_out_kind, all_out, oo);
	}
}

void
hnode_box::init_all_direct(){
	fill_with_directs(inputs, outputs);
}

void
hnode_box::release_nodes(){
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		GH_CK(all_nodes[ii] != gh_null);
		delete all_nodes[ii];
		all_nodes[ii] = gh_null;
	}
	all_nodes.clear();
	inputs.clear();
	outputs.clear();
}

void
htarget_box::del_htarget_box(){
	release_nodes();
	if(target != gh_null){
		delete target;
	}
	target = gh_null;
	lft_in.clear();
	lft_out.clear();
	rgt_in.clear();
	rgt_out.clear();
}

hnode_box*
hnode_box::convert_net_from_1to2_to_2to1(){
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
		
		hg_addr_t o_in0_addr = onod->in0->addr;
		hg_addr_t o_out0_addr = onod->out0->addr;
		hg_addr_t o_out1_addr = onod->out1->addr;
		
		cnod->out0 = bx->all_nodes[o_in0_addr];
		cnod->in0 = bx->all_nodes[o_out0_addr];
		cnod->in1 = bx->all_nodes[o_out1_addr];
		
		if(cnod->out0 == cnod){
			bx->outputs.push_back(&(cnod->out0));
		}
		if(cnod->in0 == cnod){
			bx->inputs.push_back(&(cnod->in0));
		}
		if(cnod->in1 == cnod){
			bx->inputs.push_back(&(cnod->in1));
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

bool
gh_move_io(gh_io_kind_t kk, ppnode_vec_t& src, ppnode_vec_t& dst){
	bool mvd_all = true;
	for(long ii = 0; ii < (long)src.size(); ii++){
		hnode** pps = src[ii];
		if(pps == gh_null){
			continue;
		}
		if(gh_is_free_io(pps)){
			dst.push_back(pps);
			GH_CK(*pps != gh_null);
			(*pps)->set_direct_idx(kk, dst, dst.size() - 1);
		} else {
			mvd_all = false;
		}
		src[ii] = gh_null;
	}
	src.clear();
	return mvd_all;
}

void
gh_move_nodes(vector<hnode*>& src, vector<hnode*>& dst){
	for(long ii = 0; ii < (long)src.size(); ii++){
		if(src[ii] == gh_null){
			continue;
		}
		dst.push_back(src[ii]);
		dst.back()->addr = dst.size() - 1;
		src[ii] = gh_null;
	}
	src.clear();
}

bool
hnode_box::move_nodes_to(hnode_box& bx){
	bool a1 = gh_move_io(gh_in_kind, inputs, bx.inputs);
	bool a2 = gh_move_io(gh_out_kind, outputs, bx.outputs);
	bool mvd_all = (a1 && a2);
	gh_move_nodes(all_nodes, bx.all_nodes);
	gh_move_nodes(all_direct, bx.all_direct);
	return mvd_all;
}

void
hroute_box::init_as_2to2_route_box(){
	hnode_1to2* nd1 = add_1to2();
	hnode_1to2* nd2 = add_1to2();
	hnode_2to1* nd3 = add_2to1();
	hnode_2to1* nd4 = add_2to1();
	
	inputs.resize(2, gh_null);
	inputs[0] = (&(nd1->in0));
	inputs[1] = (&(nd2->in0));
	
	outputs.resize(2, gh_null);
	outputs[0] = (&(nd3->out0));
	outputs[1] = (&(nd4->out0));
	
	nd1->out0 = nd3;
	nd3->in0 = nd1;
	
	nd1->out1 = nd4;
	nd4->in0 = nd1;
	
	nd2->out0 = nd3;
	nd3->in1 = nd2;
	
	nd2->out1 = nd4;
	nd4->in1 = nd2;
	
	GH_CK(all_direct.empty());
}

void
hroute_box::init_as_2to3_route_box(){
	hnode_box* bx1 = gh_get_binnet_m_to_n(1, 3);
	hnode_box* bx2 = gh_get_binnet_m_to_n(1, 3);
	hnode_2to1* nd1 = add_2to1();
	hnode_2to1* nd2 = add_2to1();
	hnode_2to1* nd3 = add_2to1();

	outputs.resize(3, gh_null);
	outputs[0] = (&(nd1->out0));
	outputs[1] = (&(nd2->out0));
	outputs[2] = (&(nd3->out0));
	
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

	GH_CK(all_direct.empty());
}

void
hroute_box::init_as_3to2_route_box(){
	hnode_box* bx1 = gh_get_binnet_m_to_n(3, 1);
	hnode_box* bx2 = gh_get_binnet_m_to_n(3, 1);
	hnode_1to2* nd1 = add_1to2();
	hnode_1to2* nd2 = add_1to2();
	hnode_1to2* nd3 = add_1to2();
	
	inputs.resize(3, gh_null);
	inputs[0] = (&(nd1->in0));
	inputs[1] = (&(nd2->in0));
	inputs[2] = (&(nd3->in0));

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
	
	GH_CK(all_direct.empty());
}

void
hlognet_box::init_all_target_addr(){
	for(long ii = 0; ii < (long)all_targets.size(); ii++){
		all_targets[ii]->addr = ii;
	}
}

void
hlognet_box::init_as_io(){
	GH_CK(inputs.empty());
	GH_CK(outputs.empty());
	GH_CK(all_direct.empty());
	
	for(long aa = 0; aa < (long)all_targets.size(); aa++){
		hnode_target* tg = all_targets[aa];
		all_targets[aa] = gh_null;
		
		hnode_1to2* nd1 = add_1to2();
		hnode_2to1* nd2 = add_2to1();
		inputs.push_back(&(nd1->in0));
		outputs.push_back(&(nd2->out0));
		
		nd1->out0 = nd2;
		nd2->in1 = nd1;
		
		GH_CK(tg->in0 != gh_null);
		GH_CK(tg->in0->get_kind() == hg_2_to_1_nod);
		hnode_2to1* tg_in = (hnode_2to1*)tg->in0;
		GH_CK(tg_in != gh_null);
		nd2->in0 = tg_in;
		tg_in->out0 = nd2;
		tg->in0 = gh_null;
		
		GH_CK(tg->out0 != gh_null);
		GH_CK(tg->out0->get_kind() == hg_1_to_2_nod);
		hnode_1to2* tg_out = (hnode_1to2*)tg->out0;
		GH_CK(tg_out != gh_null);
		nd1->out1 = tg_out;
		tg_out->in0 = nd1;
		tg->out0 = gh_null;
		
		delete tg;
	}
	
	GH_CK(inputs.size() == all_targets.size());
	GH_CK(outputs.size() == all_targets.size());
	
	all_targets.clear();

	init_all_addr();
}

void
hlognet_box::release_targets(){
	for(long ii = 0; ii < (long)all_targets.size(); ii++){
		GH_CK(all_targets[ii] != gh_null);
		delete all_targets[ii];
		all_targets[ii] = gh_null;
	}
	all_targets.clear();
}

void
gh_connect_node_out_to_node_in(hnode& nd_out, long out, hnode& nd_in, long in){
	GH_CK((out == 0) || (out == 1));
	GH_CK((in == 0) || (in == 1));
	hnode** ppo = gh_null;
	hnode** ppi = gh_null;
	if(out == 0){
		if(in == 0){
			ppo = nd_out.set_out0(&nd_in);
			ppi = nd_in.set_in0(&nd_out);
		} else {
			GH_CK(in == 1);
			ppo = nd_out.set_out0(&nd_in);
			ppi = nd_in.set_in1(&nd_out);
		}
	} else {
		GH_CK(out == 1);
		if(in == 0){
			ppo = nd_out.set_out1(&nd_in);
			ppi = nd_in.set_in0(&nd_out);
		} else {
			GH_CK(in == 1);
			ppo = nd_out.set_out1(&nd_in);
			ppi = nd_in.set_in1(&nd_out);
		}
	}
	GH_CK(ppo != gh_null);
	GH_CK(ppi != gh_null);
}

void
gh_connect_out_to_in(ppnode_vec_t& all_out, long out, ppnode_vec_t& all_in, long in){
	GH_CK(in < (long)all_in.size());
	hnode** ppi = all_in[in];
	hnode** ppo = all_out[out];
	
	GH_CK(ppi != gh_null);
	GH_CK(ppo != gh_null);
	GH_CK(gh_is_free_io(ppi));
	GH_CK(gh_is_free_io(ppo));
	
	hnode* pi = *ppi;
	hnode* po = *ppo;
	
	hnode* po2 = gh_set_io(all_out, out, pi);
	GH_CK(po2 == po);
	*ppi = po;
	
	all_in[in] = gh_null;
	all_out[out] = gh_null;
}

void
gh_connect_outputs_to_inputs(ppnode_vec_t& out, ppnode_vec_t& in){
	GH_CK(out.size() == in.size());
	for(long aa = 0; aa < (long)out.size(); aa++){
		gh_connect_out_to_in(out, aa, in, aa);
	}
}

void
hroute_box::init_route_box(long num_in, long num_out){
	GH_CK(num_in > 0);
	GH_CK(num_out > 0);
	if((num_in == 1) || (num_out == 1)){
		GH_CK(num_in != num_out);
		if(num_in != num_out){
			hnode_box* bx = gh_get_binnet_m_to_n(num_in, num_out);
			hnode_box& me = *this;
			bool all = bx->move_nodes_to(me);
			GH_MARK_USED(all);
			GH_CK(all);
			delete bx;
			GH_CK(ck_route_box(num_in, num_out, 1));
			return;
		}
		GH_CK(ck_route_box(num_in, num_out, 2));
		
		// abort here
		return;
	}
	if((num_in == 2) && (num_out == 2)){
		init_as_2to2_route_box();
		GH_CK(ck_route_box(num_in, num_out, 3));
		return;
	}
	if((num_in == 3) && (num_out == 2)){
		init_as_3to2_route_box();
		GH_CK(ck_route_box(num_in, num_out, 4));
		return;
	}
	if((num_in == 2) && (num_out == 3)){
		init_as_2to3_route_box();
		GH_CK(ck_route_box(num_in, num_out, 5));
		return;
	}
	
	hlognet_box* bx1 = new hlognet_box(base);
	bx1->init_lognet_box(num_out);
	bx1->init_as_io();
	
	GH_CK((long)(bx1->inputs.size()) == num_out);
	GH_CK((long)(bx1->outputs.size()) == num_out);
	
	hnode_box* bx2 = gh_null;
	if(num_in != num_out){
		bx2 = gh_get_binnet_m_to_n(num_in, num_out); // CAN_HAVE_DIRECT
		bx2->connect_outputs_to_box_inputs(*bx1);
		GH_CK((long)bx2->inputs.size() == num_in);
	}
	
	hnode_box& dest = *this;
	bx1->move_nodes_to(dest);
	
	GH_CK((long)outputs.size() == num_out);
	
	delete bx1;
	
	if(bx2 != gh_null){
		bx2->move_nodes_to(dest);
		delete bx2;
		bx2 = gh_null;
	}

	init_all_addr();

	GH_CK(ck_route_box(num_in, num_out, 6));
}

void
htarget_box::join_outputs(hnode_box* bx1, hnode_box* bx2, long num_out, ppnode_vec_t& all_out){
	GH_CK(bx1 != gh_null);
	GH_CK(bx2 != gh_null);
	GH_CK(num_out <= (long)bx1->outputs.size());
	GH_CK(num_out <= (long)bx2->outputs.size());
	for(long aa = 0; aa < (long)num_out; aa++){
		hnode_2to1* nd_out = add_2to1();
		bx1->connect_output_to_node_input(aa, *nd_out, 0);
		bx2->connect_output_to_node_input(aa, *nd_out, 1);

		all_out.push_back(&(nd_out->out0));
	}
}

void
hlognet_box::init_length(long num_elems){
	double lbb = log2(base);
	double lnn = log2(num_elems - 1);
	height = (long)(lnn/lbb);
	length = num_elems;
}

htarget_box*
hlognet_box::get_target_box(long idx){
	htarget_box* bx = new htarget_box(base);
	long nin = 0;
	long nout = 0;
	gh_calc_num_io(base, length, idx, nin, nout);
	GH_CK((idx == 0) || (nin >= nout));
	bx->init_target_box(nin, nout);
	return bx;
}

void 
gh_calc_num_io(long base, long length, long idx, long& num_in, long& num_out){
	GH_CK(base > 1);
	GH_CK(length > 1);
	GH_CK(idx < length);
	
	double lbb = log2(base);
	double lnn = log2(length - 1);
	long max_hh = (long)(lnn/lbb) + 1;
	GH_MARK_USED(lbb);
	GH_MARK_USED(lnn);
	GH_MARK_USED(max_hh);

	//fprintf(stdout, "max_hh=%ld\n", max_hh);
	
	num_in = 0;
	num_out = 0;
	long pw = 1;
	for(long aa = 0; aa < max_hh; aa++, pw *= base){
		//fprintf(stdout, "idx=%ld pw=%ld\n", idx, pw);
		if((idx % pw) != 0){
			break;
		}
		if(idx > 0){
			num_in++;
		}
		if((idx + pw) < length){
			num_out++;
		}
	}
}

bool
htarget_box::ck_target_box(long lft_ht, long rgt_ht){
	GH_CK(inputs.empty());
	GH_CK(outputs.empty());
	GH_CK((long)lft_in.size() == lft_ht);
	GH_CK((long)lft_out.size() == rgt_ht);
	GH_CK((long)rgt_in.size() == rgt_ht);
	GH_CK((long)rgt_out.size() == lft_ht);
	GH_CK(target != gh_null);
	GH_CK(target->in0 != gh_null);
	GH_CK(target->out0 != gh_null);
	GH_CK((target->in0 == target) || (target->in0->get_kind() == hg_2_to_1_nod));
	GH_CK((target->out0 == target) || (target->out0->get_kind() == hg_1_to_2_nod));
	GH_CK(all_direct.empty());
	return true;
}

void
htarget_box::init_target_box(long lft_ht, long rgt_ht){
	if((lft_ht <= 1) || (rgt_ht <= 1)){
		init_basic_target_box(lft_ht, rgt_ht);
		GH_CK(ck_target_box(lft_ht, rgt_ht));
		return;
	}
	
	GH_CK(lft_ht > 1);
	GH_CK(rgt_ht > 1);
	hroute_box* lft = new hroute_box(base);
	hroute_box* rgt = new hroute_box(base);
	
	hnode_2to1* tg_in = add_2to1();
	hnode_1to2* tg_out = add_1to2();
	
	lft->init_route_box(lft_ht, rgt_ht + 1);
	rgt->init_route_box(rgt_ht, lft_ht + 1);

	hnode_box* spl_lft = gh_get_binnet_m_to_n(1, rgt_ht);
	hnode_box* spl_rgt = gh_get_binnet_m_to_n(1, lft_ht);
	
	join_outputs(lft, spl_lft, rgt_ht, lft_out);
	join_outputs(rgt, spl_rgt, lft_ht, rgt_out);
	
	target = new hnode_target;
	target->in0 = tg_in;
	tg_in->out0 = target;
	target->out0 = tg_out;
	tg_out->in0 = target;
	
	long lft_lst = lft->outputs.size() - 1;
	lft->connect_output_to_node_input(lft_lst, *tg_in, 0);
	long rgt_lst = rgt->outputs.size() - 1;
	rgt->connect_output_to_node_input(rgt_lst, *tg_in, 1);
	
	spl_lft->connect_node_output_to_input(*tg_out, 0, 0);
	spl_rgt->connect_node_output_to_input(*tg_out, 1, 0);
	
	gh_move_io(gh_in_kind, lft->inputs, lft_in);
	gh_move_io(gh_in_kind, rgt->inputs, rgt_in);
	gh_move_io(gh_out_kind, spl_lft->outputs, lft_out);
	gh_move_io(gh_out_kind, spl_rgt->outputs, rgt_out);
	
	hnode_box& dest = *this;
	lft->move_nodes_to(dest);
	rgt->move_nodes_to(dest);
	spl_lft->move_nodes_to(dest);
	spl_rgt->move_nodes_to(dest);

	delete lft;
	delete rgt;
	delete spl_lft;
	delete spl_rgt;

	init_all_addr();

	GH_CK(ck_target_box(lft_ht, rgt_ht));
}

void
hnode_box::connect_outputs_to_box_inputs(hnode_box& bx){
	gh_connect_outputs_to_inputs(outputs, bx.inputs);
	remove_connected_directs();
	bx.remove_connected_directs();
}

void
hnode_box::remove_connected_directs(){
	for(long aa = 0; aa < (long)all_direct.size(); aa++){
		hnode_direct* nd = (hnode_direct*)all_direct[aa];
		if(nd == gh_null){
			continue;
		}
		GH_CK(nd != gh_null);
		GH_CK(nd->in_vec != gh_null);
		GH_CK(nd->in_idx != GH_INVALID_IDX);
		GH_CK(nd->out_vec != gh_null);
		GH_CK(nd->out_idx != GH_INVALID_IDX);
		ppnode_vec_t& vin = *(nd->in_vec);
		ppnode_vec_t& vout = *(nd->out_vec);
		long idx_in = nd->in_idx;
		long idx_out = nd->out_idx;
		
		hnode* nd_in0 = nd->in0;
		hnode* nd_out0 = nd->out0;
		GH_CK(nd_in0 != gh_null);
		GH_CK(nd_out0 != gh_null);
		if((nd_in0 != nd) && (nd_out0 != nd)){
			GH_CK(vin[idx_in] == gh_null);
			GH_CK(vout[idx_out] == gh_null);
			
			hnode** ppn1 = nd_in0->re_link_out(nd, nd_out0);
			hnode** ppn2 = nd_out0->re_link_out(nd, nd_in0);
			GH_MARK_USED(ppn1);
			GH_MARK_USED(ppn2);
			GH_CK(ppn1 != gh_null);
			GH_CK(ppn2 != gh_null);
			
			all_direct[aa] = gh_null;
		} else 
		if((nd_in0 != nd) && (nd_out0 == nd)){
			GH_CK(vin[idx_in] == gh_null);
			GH_CK(vout[idx_out] == &(nd->out0));
			
			hnode** ppn = nd_in0->re_link_out(nd, nd_in0);
			GH_CK(ppn != gh_null);
			vout[idx_out] = ppn;
			nd_in0->set_direct_idx(gh_out_kind, vout, idx_out);
			
			all_direct[aa] = gh_null;
		} else 
		if((nd_in0 == nd) && (nd_out0 != nd)){
			GH_CK(vin[idx_in] == &(nd->in0));
			GH_CK(vout[idx_out] == gh_null);

			hnode** ppn = nd_out0->re_link_in(nd, nd_out0);
			GH_CK(ppn != gh_null);
			vin[idx_in] = ppn;
			nd_out0->set_direct_idx(gh_in_kind, vin, idx_in);
			
			all_direct[aa] = gh_null;
		}

		if(all_direct[aa] == gh_null){
			delete nd;
		}
	}
}

void
htarget_box::init_basic_target_box(long lft_ht, long rgt_ht){
	GH_CK(lft_ht >= 0);
	GH_CK(rgt_ht >= 0);
	GH_CK((lft_ht <= 1) || (rgt_ht <= 1));
	
	hnode_box& dest = *this;
	
	long full_ht = lft_ht + rgt_ht;
	target = new hnode_target;
	
	if((lft_ht == 0) || (rgt_ht == 0)){
		GH_CK((lft_ht != 0) || (rgt_ht != 0));
		if(full_ht == 1){
			target->init_to_me();
			if(lft_ht == 1){
				lft_in.push_back(&(target->in0));
				rgt_out.push_back(&(target->out0));
			} else {
				GH_CK(rgt_ht == 1);
				lft_out.push_back(&(target->out0));
				rgt_in.push_back(&(target->in0));
			}
			return;
		}
		GH_CK((lft_ht > 1) || (rgt_ht > 1));
		GH_CK(full_ht > 1);
		
		hnode_box* spl_in = gh_get_binnet_m_to_n(full_ht, 1);
		hnode_box* spl_out = gh_get_binnet_m_to_n(1, full_ht);

		GH_CK(spl_in->outputs.size() == 1);
		hnode* nd_in = *(spl_in->outputs[0]);
		gh_set_io(spl_in->outputs, 0, target);
		target->in0 = nd_in;
		
		GH_CK(spl_out->inputs.size() == 1);
		hnode* nd_out = *(spl_out->inputs[0]);
		gh_set_io(spl_out->inputs, 0, target);
		target->out0 = nd_out;
		
		if(lft_ht == 0){
			gh_move_io(gh_out_kind, spl_out->outputs, lft_out);
			gh_move_io(gh_in_kind, spl_in->inputs, rgt_in);
		} else {
			GH_CK(rgt_ht == 0);
			gh_move_io(gh_in_kind, spl_in->inputs, lft_in);
			gh_move_io(gh_out_kind, spl_out->outputs, rgt_out);
		}
		
		spl_in->move_nodes_to(dest);
		spl_out->move_nodes_to(dest);
		
		init_all_addr();
		
		return;
	}
	
	if((lft_ht == 1) && (rgt_ht == 1)){
		if(base == 2){
			hnode_2to1* tg_in = add_2to1();
			hnode_1to2* tg_out = add_1to2();
			
			target->in0 = tg_in;
			tg_in->out0 = target;
			target->out0 = tg_out;
			tg_out->in0 = target;
			
			lft_in.push_back(&(tg_in->in0));
			lft_out.push_back(&(tg_out->out0));
			rgt_in.push_back(&(tg_in->in1));
			rgt_out.push_back(&(tg_out->out1));
					
			GH_CK(target->in0->get_kind() == hg_2_to_1_nod);
			GH_CK(target->out0->get_kind() == hg_1_to_2_nod);
		} else {
			hnode_2to1* tg_in = add_2to1();
			hnode_1to2* tg_out = add_1to2();
			
			target->in0 = tg_in;
			tg_in->out0 = target;
			target->out0 = tg_out;
			tg_out->in0 = target;
			
			hnode_1to2* l_in = add_1to2();
			hnode_2to1* l_out = add_2to1();
			hnode_1to2* r_in = add_1to2();
			hnode_2to1* r_out = add_2to1();

			l_in->out0 = l_out;
			l_out->in0 = l_in;
			
			l_in->out1 = tg_in;
			tg_in->in0 = l_in;

			l_out->in1 = tg_out;
			tg_out->out0 = l_out;
			
			tg_out->out1 = r_out;
			r_out->in1 = tg_out;
			
			r_out->in0 = r_in;
			r_in->out1 = r_out;

			r_in->out0 = tg_in;
			tg_in->in1 = r_in;
			
			lft_in.push_back(&(l_in->in0));
			lft_out.push_back(&(l_out->out0));
			rgt_in.push_back(&(r_in->in0));
			rgt_out.push_back(&(r_out->out0));
		}
		
		init_all_addr();
		
		return;
	}
	GH_CK((lft_ht == 1) || (rgt_ht == 1));
	GH_CK((lft_ht > 1) || (rgt_ht > 1));
	
	hnode_2to1* tg_in = add_2to1();
	hnode_1to2* tg_out = add_1to2();
	
	target->in0 = tg_in;
	tg_in->out0 = target;
	target->out0 = tg_out;
	tg_out->in0 = target;
	
	long bt1_ht = full_ht - 1;
	GH_CK(bt1_ht > 1);
	GH_CK((lft_ht == bt1_ht) || (rgt_ht == bt1_ht));
	
	hroute_box* rt_in_bx = new hroute_box(base);
	rt_in_bx->init_as_2to2_route_box();
	
	GH_CK(all_direct.empty());
	if(bt1_ht > 2){
		hnode_box* bn = gh_get_binnet_m_to_n(bt1_ht, 2); // CAN_HAVE_DIRECT
		if(rgt_ht == 1){
			GH_CK(lft_ht > 1);
			gh_move_io(gh_in_kind, bn->inputs, lft_in);
		} else {
			GH_CK(lft_ht == 1);
			GH_CK(rgt_ht > 1);
			gh_move_io(gh_in_kind, bn->inputs, rgt_in);
		}
		bn->connect_outputs_to_box_inputs(*rt_in_bx);
		bn->move_nodes_to(dest);
		GH_CK(all_direct.empty());
	} else {
		if(rgt_ht == 1){
			GH_CK(lft_ht > 1);
			gh_move_io(gh_in_kind, rt_in_bx->inputs, lft_in);
		} else {
			GH_CK(lft_ht == 1);
			GH_CK(rgt_ht > 1);
			gh_move_io(gh_in_kind, rt_in_bx->inputs, rgt_in);
		}
	}
	GH_CK(all_direct.empty());
	
	hnode_box* spl_bx_in = gh_get_binnet_m_to_n(1, bt1_ht);
	hnode_box* spl_bx_out = gh_get_binnet_m_to_n(1, bt1_ht);

	hnode_1to2* bx_in = add_1to2();
	hnode_2to1* bx_out = add_2to1();

	if(rgt_ht == 1){
		GH_CK(lft_ht > 1);
		rt_in_bx->connect_output_to_node_input(0, *bx_out, 0);
		rt_in_bx->connect_output_to_node_input(1, *tg_in, 0);
		spl_bx_out->connect_node_output_to_input(*tg_out, 1, 0);
		spl_bx_in->connect_node_output_to_input(*bx_in, 1, 0);
		
		tg_out->out0 = bx_out;
		bx_out->in1 = tg_out;
		
		tg_in->in1 = bx_in;
		bx_in->out0 = tg_in;
		
		join_outputs(spl_bx_in, spl_bx_out, bt1_ht, rgt_out);
		lft_out.push_back(&(bx_out->out0));
		rgt_in.push_back(&(bx_in->in0));
	} else {
		GH_CK(lft_ht == 1);
		GH_CK(rgt_ht > 1);
		spl_bx_in->connect_node_output_to_input(*bx_in, 0, 0);
		spl_bx_out->connect_node_output_to_input(*tg_out, 0, 0);
		rt_in_bx->connect_output_to_node_input(0, *tg_in, 1);
		rt_in_bx->connect_output_to_node_input(1, *bx_out, 1);
		
		bx_in->out1 = tg_in;
		tg_in->in0 = bx_in;
		
		tg_out->out1 = bx_out;
		bx_out->in0 = tg_out;
		
		join_outputs(spl_bx_in, spl_bx_out, bt1_ht, lft_out);
		lft_in.push_back(&(bx_in->in0));
		rgt_out.push_back(&(bx_out->out0));
	}

	GH_CK(inputs.empty());
	GH_CK(outputs.empty());
	GH_CK(all_direct.empty());
	
	rt_in_bx->move_nodes_to(dest);
	GH_CK(inputs.empty());
	GH_CK(outputs.empty());
	GH_CK(all_direct.empty());
	
	spl_bx_in->move_nodes_to(dest);
	GH_CK(inputs.empty());
	GH_CK(outputs.empty());
	GH_CK(all_direct.empty());

	spl_bx_out->move_nodes_to(dest);
	GH_CK(inputs.empty());
	GH_CK(outputs.empty());
	GH_CK(all_direct.empty());
	
	init_all_addr();

	GH_CK(all_direct.empty());
}

int
test_m_to_n(int argc, char *argv[]){
	if(argc < 3){
		printf("%s <num_in> <num_out>\n", argv[0]);
		return 1;
	}
	
	long mm = atol(argv[1]);
	long nn = atol(argv[2]);

	hnode_box* bx = gh_get_binnet_m_to_n(mm, nn);
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
	
	hroute_box* bx = new hroute_box(2);
	GH_MARK_USED(bx);
	switch(mm){
		case 0: 
			bx->init_as_2to3_route_box();
			break;
		case 1: 
			bx->init_as_3to2_route_box();
			break;
		default: 
			bx->init_as_2to2_route_box();
			break;
	}
	
	bx->print_box(stdout, hg_full_prt);
	delete bx;
	
	return 0;
}

int
test_log(int argc, char *argv[]){
	if(argc < 3){
		printf("%s <base> <num>\n", argv[0]);
		return 1;
	}
	
	long bb = atol(argv[1]);
	long nn = atol(argv[2]);
	
	double lbb = log2(bb);
	long lg = (long)(log2(nn)/lbb);
	fprintf(stdout, "LOG(%ld, %ld) = %ld\n", bb, nn, lg);
	return 0;
	
}

int
test_mod(int argc, char *argv[]){
	if(argc < 3){
		printf("%s <n1> <n2>\n", argv[0]);
		return 1;
	}
	
	long n1 = atol(argv[1]);
	long n2 = atol(argv[2]);
	long n3 = (n1 % n2);
	
	fprintf(stdout, "%ld mod %ld = %ld\n", n1, n2, n3);
	return 0;
}

int
test_num_io(int argc, char *argv[]){
	if(argc < 4){
		printf("%s <base> <length> <idx>\n", argv[0]);
		return 1;
	}
	
	long bb = atol(argv[1]);
	long ll = atol(argv[2]);
	long idx = atol(argv[3]);
	long nin = 0;
	long nout = 0;
	
	gh_calc_num_io(bb, ll, idx, nin, nout);
	fprintf(stdout, "base=%ld length=%ld idx=%ld num_in=%ld num_out=%ld\n", bb, ll, idx, nin, nout);
	return 0;
}

int
test_get_target(int argc, char *argv[]){
	if(argc < 4){
		printf("%s <base> <#in> <#out>\n", argv[0]);
		return 1;
	}
	
	long bb = atol(argv[1]);
	long nin = atol(argv[2]);
	long nout = atol(argv[3]);
	fprintf(stdout, "base=%ld #in=%ld #out=%ld\n", bb, nin, nout);
	
	htarget_box* bx = new htarget_box(bb);
	bx->init_target_box(nin, nout);

	fprintf(stdout, "\n\n\n===========\n");
	
	GH_GLOBALS.CK_LINK_MODE = hg_valid_self_ck_mod;
	bx->print_box(stdout, hg_full_prt);
	
	delete bx;
		
	return 0;
}

int
main(int argc, char *argv[]){
	int resp = 0;
	resp = test_m_to_n(argc, argv);
	//resp = test_bases(argc, argv);
	//resp = test_log(argc, argv);
	//resp = test_mod(argc, argv);
	//resp = test_num_io(argc, argv);
	//resp = test_get_target(argc, argv);
	
	printf("ENDING_TESTS______________________\n");
	return resp;
}

void
hlognet_box::init_lognet_box(long num_elems){
	GH_CK(num_elems > 1);
	
	init_length(num_elems);

	//print_box(stdout, hg_full_prt);
	
	hlognet_box& dest = *this;
	
	htarget_box* prv_bx = gh_null;
	for(long aa = 0; aa < num_elems; aa++){
		//fprintf(stdout, "ITER %ld of %ld ===========================================\n", aa, num_elems);
		//print_box(stdout, hg_full_prt);
		
		htarget_box* bx = get_target_box(aa);
		
		//fprintf(stdout, "TGT_BOX %ld of %ld ++++++++++\n", aa, num_elems);
		//bx->print_box(stdout, hg_full_prt);
		
		if(prv_bx != gh_null){
			GH_CK((aa < 2) || (prv_bx->lft_in.size() >= prv_bx->lft_out.size()));
			GH_CK(bx->lft_in.size() >= bx->lft_out.size());
			GH_CK(prv_bx->lft_out.size() == prv_bx->rgt_in.size());
			GH_CK(bx->rgt_out.size() == bx->lft_in.size());
			
			if(prv_bx->lft_out.size() > bx->lft_in.size()){
				bx->resize_with_directs(prv_bx->lft_out.size());
			}

			/*
			fprintf(stdout, "BEFORE %ld &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n", aa);
			fprintf(stdout, "PRV ______________\n");
			prv_bx->print_box(stdout, hg_full_pt_prt);
			fprintf(stdout, "BX ______________\n");
			bx->print_box(stdout, hg_full_pt_prt);
			*/
			
			GH_CK(prv_bx->lft_out.size() == bx->lft_in.size());
			gh_connect_outputs_to_inputs(prv_bx->lft_out, bx->lft_in);
			
			GH_CK(bx->rgt_out.size() == prv_bx->rgt_in.size());
			gh_connect_outputs_to_inputs(bx->rgt_out, prv_bx->rgt_in);

			bx->remove_connected_directs();
			prv_bx->remove_connected_directs();

			/*
			fprintf(stdout, "AFTER %ld &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n", aa);
			fprintf(stdout, "PRV ______________\n");
			prv_bx->print_box(stdout, hg_full_pt_prt);
			fprintf(stdout, "BX ______________\n");
			bx->print_box(stdout, hg_full_pt_prt);
			*/
			
			prv_bx->move_nodes_to(dest);
			prv_bx->move_target_to(dest);

			delete prv_bx;
			prv_bx = gh_null;
		}
		prv_bx = bx;
	}
	
	//fprintf(stdout, "==============================================\n");
	
	if(prv_bx != gh_null){
		GH_CK(prv_bx->lft_out.empty());
		GH_CK(prv_bx->rgt_in.empty());
		
		prv_bx->move_nodes_to(dest);
		prv_bx->move_target_to(dest);
		delete prv_bx;
		prv_bx = gh_null;
	}
	
	init_all_addr();

	GH_CK(ck_lognet_box(num_elems));
	
	//GH_DBG_CODE(GH_GLOBALS.DBG_LV = 1);
	//print_box(stdout, hg_full_pt_prt);
	
	fprintf(stdout, "LGNET_BOX %ld **********************************************\n", length);
	fflush(stdout);
}

void
htarget_box::resize_with_directs(long nw_side_sz){
	GH_CK(nw_side_sz > (long)lft_in.size());
	GH_CK(nw_side_sz > (long)rgt_in.size());
	GH_CK(lft_in.size() == lft_out.size());
	GH_CK(rgt_in.size() == rgt_out.size());
	
	lft_in.resize(nw_side_sz, gh_null);
	lft_out.resize(nw_side_sz, gh_null);
	rgt_in.resize(nw_side_sz, gh_null);
	rgt_out.resize(nw_side_sz, gh_null);

	fill_with_directs(lft_in, lft_out);
	fill_with_directs(rgt_in, rgt_out);
}


void
htarget_box::move_target_to(hlognet_box& bx){
	bx.all_targets.push_back(target);
	bx.all_targets.back()->addr = bx.all_targets.size() - 1;
	target = gh_null;
}

bool
hlognet_box::ck_lognet_box(long num_elem){
	GH_CK(inputs.empty());
	GH_CK(outputs.empty());
	GH_CK(all_direct.empty());
	GH_CK(length == (long)all_targets.size());
	return true;
}

bool
hroute_box::ck_route_box(long num_in, long num_out, int dbg_case){
	GH_CK_PRT(((long)inputs.size() == num_in), "%ld != %ld (%d) #in=%ld #out=%ld \n", 
			  (long)inputs.size(), num_in, dbg_case, num_in, num_out);
	GH_CK((long)outputs.size() == num_out);
	GH_CK(all_direct.empty());
	return true;
}

void
gh_get_last_level(ppnode_vec_t& all_out, hg_flag_idx_t lv_col, vector<hnode*>& last_lv){
	//GH_PRT("lv col=%d \n", lv_col);
	
	last_lv.clear();
	for(long aa = 0; aa < (long)all_out.size(); aa++){
		hnode** ppo = all_out[aa];
		GH_CK(ppo != gh_null);
		GH_CK(gh_is_free_io(ppo));
		
		hnode* po = *ppo;
		GH_CK(po != gh_null);
		
		hg_hnode_kind_t kk = po->get_kind();
		GH_CK((kk == hg_1_to_1_nod) || (kk == hg_1_to_2_nod));
		
		if(kk == hg_1_to_2_nod){
			hnode_1to2* nd = (hnode_1to2*)po;
			if(nd->get_flag(lv_col)){
				if(&(nd->out0) == ppo){
					nd->msg0.rng.min = aa;
					nd->msg0.rng.max = aa;
				} else {
					GH_CK(&(nd->out1) == ppo);
					nd->msg1.rng.min = aa;
					nd->msg1.rng.max = aa;
				}
				if(nd->has_connected_in0()){
					hnode* in0 = po->get_in0();
					if(! in0->get_flag(gh_to_range_bit)){
						in0->set_flag(gh_to_range_bit);
						last_lv.push_back(in0);
						GH_PRT("%p added in0 %p of %p \n", (void*)ppo, (void*)in0, (void*)po);
					}
				}
			}
		} else {
			hnode_1to1* nd = (hnode_1to1*)po;
			GH_CK(&(nd->out0) == ppo);
			GH_CK(! nd->has_connected_in0());
			if(! nd->get_flag(gh_has_range_bit)){
				nd->set_flag(gh_has_range_bit);
				nd->msg0.rng.min = aa;
				nd->msg0.rng.max = aa;
			}
		}
		
	}
}

void
gh_init_level_ranges(vector<hnode*>& prv_lv, vector<hnode*>& next_lv, hg_flag_idx_t lv_col, char dbg_case){
	for(long aa = 0; aa < (long)prv_lv.size(); aa++){
		hnode* nd = prv_lv[aa];
		GH_CK(nd != gh_null);
		GH_CK(nd->get_kind() == hg_1_to_2_nod);
		GH_CK_PRT((nd->get_flag(lv_col)), "%d (%p) col=%d %c \n", dbg_case, (void*)nd, lv_col, gh_get_col_chr(nd->node_flags));
		
		hnode* po0 = nd->get_out0();
		hnode* po1 = nd->get_out1();

		GH_CK(po0 != gh_null);
		GH_CK(po1 != gh_null);
		
		if(po0 != nd){
			hrange* rng0 = nd->get_range0();
			GH_CK(rng0 != gh_null);
			po0->get_joined_range(*rng0);
		}

		if(po1 != nd){
			hrange* rng1 = nd->get_range1();
			GH_CK(rng1 != gh_null);
			po1->get_joined_range(*rng1);
		}
		
		if(nd->has_connected_in0()){
			hnode* in0 = nd->get_in0();
			if(! in0->get_flag(gh_to_range_bit)){
				in0->set_flag(gh_to_range_bit);
				next_lv.push_back(in0);
				GH_PRT("added in0 %p of %p \n", (void*)in0, (void*)nd);
			}
		}
	}
}

void
gh_init_sm_to_bm_ranges(ppnode_vec_t& all_out, hg_flag_idx_t lst_col, hnode_box* dbg_bx){

	//GH_DBG_CODE(if(dbg_bx != gh_null){ dbg_bx->print_box(stdout, hg_full_pt_prt); });
	
	vector<hnode*> last_lv;
	gh_get_last_level(all_out, lst_col, last_lv);
	
	vector<hnode*> next_lv;
	hg_flag_idx_t nxt_col = gh_get_opp_color_bit(lst_col);
	gh_get_last_level(all_out, nxt_col, next_lv);
	
	//GH_DBG_CODE(long num_lv = 0);
	gh_init_level_ranges(last_lv, next_lv, nxt_col, 1);

	vector<hnode*> prv_lv;
	while(! next_lv.empty()){
		//GH_PRT("num_lv=%ld \n", num_lv++);
		
		prv_lv.clear();
		prv_lv = next_lv;
		next_lv.clear();
		nxt_col = gh_get_opp_color_bit(nxt_col);
		
		gh_init_level_ranges(prv_lv, next_lv, nxt_col, 2);
	}
}

void
hnode::get_joined_range(hrange& rng){
	hrange* rng0 = get_range0();
	GH_CK(rng0 != gh_null);
	GH_CK(rng0->ck_range());
	
	rng.min = rng0->min;
	rng.max = rng0->max;

	hrange* rng1 = get_range1();
	GH_CK(rng1 != gh_null);
	GH_CK(rng1->ck_range());
	
	GH_CK_PRT(((rng.max + 1) == rng1->min), "(%p) ((%d + 1) == %d) " 
		" 0(%d, %d) 1(%d, %d)\n", (void*)this, rng.max, rng1->min, rng0->min, rng0->max, rng1->min, rng1->max);
	rng.max = rng1->max;
	//rng.min = gh_min(rng.min, rng1->min);
	//rng.max = gh_max(rng.max, rng1->max);
}

void
hnode::set_color_as_in(hnode_box& bx){
	GH_CK(node_flags == 0);
	if(bx.get_flag(gh_is_red_bit)){
		set_flag(gh_is_red_bit);
	} else {
		GH_CK(bx.get_flag(gh_is_black_bit));
		set_flag(gh_is_black_bit);
	}
}

void 
gh_recalc_ranges(vector<hnode*>& all_nod, hg_addr_t idx_ref, long base){
	for(long ii = 0; ii < (long)all_nod.size(); ii++){
		hnode* nd = all_nod[ii];
		if(nd == gh_null){
			continue;
		}
		
		hg_hnode_kind_t kk = nd->get_kind();
		if(kk == hg_1_to_2_nod){
			hnode_1to2* nod = (hnode_1to2*)nd;
			nod->msg0.rng.recalc(idx_ref, base);
			nod->msg1.rng.recalc(idx_ref, base);
		}
		if(kk == hg_1_to_1_nod){
			hnode_1to1* nod = (hnode_1to1*)nd;
			nod->msg0.rng.recalc(idx_ref, base);
		}
	}
}

hg_addr_t
gh_recalc_range_val(hg_addr_t idx_ref, long base, hg_addr_t val){
	double pp = idx_ref + pow(base, val);
	return pp;
}


