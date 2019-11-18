
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
hnode::print_addr(FILE* ff, char pfx){
	fprintf(ff, ".%c%ld.", pfx, addr + GH_GLOBALS.dbg_prt_disp_all_addr_simu);
	fflush(ff);
}

void
hnode::print_dbg_tgt_addr(FILE* ff, gh_prt_mode_t md){
	if(! GH_GLOBALS.prt_tgt_info){
		return;
	}
	if(dbg_tgt_addr == GH_INVALID_ADDR){
		return;
	}
	
	fprintf(ff, "{");
	fprintf(ff, "%ld", dbg_tgt_addr);
	if(dbg_tgt_quarter != gh_null){
		fprintf(ff, "_%s", dbg_tgt_quarter);
	}
	fprintf(ff, "}");
	fflush(ff);
}

int // virtual
hnode::print_node(FILE* ff, gh_prt_mode_t md){
	print_addr(ff);
	fflush(ff);
	return 0;
}

int // virtual
hnode_1to1::print_node(FILE* ff, gh_prt_mode_t md){
	fflush(ff);
	GH_CK(ck_connections());
	if(md == gh_addr_prt){
		print_addr(ff);
		return 0;
	}
	
	bool is_tgt = (get_1t1_kind() == gh_target_1t1);
	
	if(! is_tgt){
		print_addr(ff);
	}
	print_dbg_tgt_addr(ff, md);
	
	fprintf(ff, "[");
	
	if(md == gh_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in0, in0);
		fprintf(ff, "o(%p -> %p)", &out0, out0);
	} else {
		fprintf(ff, "i");
		in0->print_node(ff, gh_addr_prt);
		fprintf(ff, "o");
		out0->print_node(ff, gh_addr_prt);
	}
	fprintf(ff, "]");
	
	if(is_tgt){
		hnode_target* tg = (hnode_target*)this;
		tg->print_filter_info(ff);
	}
	
	fprintf(ff, "\n");
	fflush(ff);
	return 0;
}

int // virtual
hnode_direct::print_node(FILE* ff, gh_prt_mode_t md){
	fflush(ff);
	GH_CK(ck_connections());
	if(md == gh_addr_prt){
		print_addr(ff);
		return 0;
	}
	
	fprintf(ff, "dr");
	hnode_1to1::print_node(ff, md);
	fflush(ff);
	return 0;
}

int // virtual
hnode_target::print_node(FILE* ff, gh_prt_mode_t md){
	char pfx = '$';
	fflush(ff);
	GH_CK(ck_connections());
	if(md == gh_addr_prt){
		print_addr(ff, pfx);
		return 0;
	}
	
	print_addr(ff, pfx);
	if(is_source_simu){
		fprintf(ff, "s");
	}
	fprintf(ff, "<%ld, %ld, %ld, %ld>", dbg_lft_in_sz, dbg_lft_out_sz, dbg_rgt_in_sz, dbg_rgt_out_sz);
	hnode_1to1::print_node(ff, md);

	fflush(ff);
	return 0;
}

void
hnode::print_filter_info(FILE* ff){
	fprintf(ff, "%s", get_filter_str().c_str());
}

std::string
hnode::get_filter_str(){
	std::ostringstream tmp_ss;
	bool has_lm = get_flag(gh_has_limit);
	if(has_lm){
		tmp_ss << "[";
	}
	
	bool is_gt = get_flag(gh_is_gt_cmp);
	bool is_eq = get_flag(gh_is_eq_cmp);

	const char* cmstr = "?";
	if(is_gt){ 
		if(is_eq){ cmstr = ">="; } else { cmstr = ">"; }
		
	} else { 
		if(is_eq){ cmstr = "<="; } else { cmstr = "<"; }
	}
	
	char itch = (get_flag(gh_is_interval))?('I'):(' ');
	
	tmp_ss << itch << cmstr << filter_addr;
	
	if(has_lm){
		tmp_ss << ", " << filter_lim_addr << "]";
	} else if(filter_lim_addr != GH_INVALID_ADDR) {
		tmp_ss << " (" << filter_lim_addr << ")";
	}

	return tmp_ss.str();
}
	
const char*
hnode_1to2::dbg_kind_to_str(gh_dbg_call_t cll){
	switch(dbg_kind){
		case gh_call_01:
			return "2to3_b1";
		case gh_call_02:
			return "2to3_b2";
		case gh_call_03:
			return "3to2_b1";
		case gh_call_04:
			return "3to2_b2";
		case gh_call_05:
			return "1toN";
		case gh_call_06:
			return "fx_in";
		case gh_call_07:
			return "spl_lft";
		case gh_call_08:
			return "spl_rgt";
		case gh_call_09:
			return "zpl_in";
		case gh_call_10:
			return "zpl_out";
		case gh_call_11:
			return "Nto2";
		case gh_call_12:
			return "spl_in";
		case gh_call_13:
			return "spl_out";
		default:
			break;
	}
	return "GH_INVALID_DBG_KIND";
}

int // virtual
hnode_1to2::print_node(FILE* ff, gh_prt_mode_t md){
	fflush(ff);
	if(md == gh_addr_prt){
		print_addr(ff);
		return 0;
	}

	
	print_addr(ff);
	print_dbg_tgt_addr(ff, md);
	
	if(rou_kind == gh_sm_to_bm_rou){
		fprintf(ff, "_%s", dbg_kind_to_str(dbg_kind));
	} else {
		fprintf(ff, "%s", gh_dbg_get_rou_kind_str(rou_kind));
	}
	
	fprintf(ff, "<");
	//fprintf(ff, "%c", gh_get_col_chr(node_flags));
	if(md == gh_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in0, in0);
		fprintf(ff, "o(%p -> %p)", &out0, out0);
		fprintf(ff, "o(%p -> %p)", &out1, out1);
	} else {
		fprintf(ff, " i");
		in0->print_node(ff, gh_addr_prt);
		fprintf(ff, " o");
		out0->print_node(ff, gh_addr_prt);
		fprintf(ff, " o");
		out1->print_node(ff, gh_addr_prt);
	}
	fprintf(ff, ">");

	bool h0 = (out0 == this);
	bool h1 = (out1 == this);
	bool hout = (h0 || h1);
	
	print_filter_info(ff);
	
	if(hout){ 
		fprintf(ff, "{");
		if(h0){ fprintf(ff, "%ld", o_idx0); }
		fprintf(ff, ", ");
		if(h1){ fprintf(ff, "%ld", o_idx1); }
		fprintf(ff, "}"); 
	}
	
	fprintf(ff, "\n");
	fflush(ff);
	GH_CK(ck_connections());
	return 0;
}

int // virtual
hnode_2to1::print_node(FILE* ff, gh_prt_mode_t md){
	fflush(ff);
	if(md == gh_addr_prt){
		print_addr(ff);
		return 0;
	}
	
	print_addr(ff);
	print_dbg_tgt_addr(ff, md);
	
	fprintf(ff, "2to1");

	fprintf(ff, "<");
	if(md == gh_full_pt_prt){
		fprintf(ff, "(%p)", this);
		fprintf(ff, "i(%p -> %p)", &in0, in0);
		fprintf(ff, "i(%p -> %p)", &in1, in1);
		fprintf(ff, "o(%p -> %p)", &out0, out0);
	} else {
		fprintf(ff, " i");
		in0->print_node(ff, gh_addr_prt);
		fprintf(ff, " i");
		in1->print_node(ff, gh_addr_prt);
		fprintf(ff, " o");
		out0->print_node(ff, gh_addr_prt);
	}
	fprintf(ff, ">");

	if(get_flag(gh_is_lognet_io)){
		print_filter_info(ff);
	}
	
	fprintf(ff, "\n");
	fflush(ff);
	GH_CK(ck_connections());
	return 0;
}

void
gh_print_io(FILE* ff, gh_prt_mode_t md, ppnode_vec_t& all_io){
	fflush(ff);
	for(long ii = 0; ii < (long)all_io.size(); ii++){
		hnode** ppi = all_io[ii];
		if(ppi != gh_null){
			hnode* pi = *ppi;
			GH_CK(pi != gh_null);
			
			fprintf(ff, "\t");
			if(md == gh_full_pt_prt){
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
hnode_box::print_box(FILE* ff, gh_prt_mode_t md){
	fprintf(ff, "BOX\n");
	fprintf(ff, "INPUTS %ld\n", (long)inputs.size());
	gh_print_io(ff, md, inputs);
	fprintf(ff, "OUTPUTS %ld\n", (long)outputs.size());
	gh_print_io(ff, md, outputs);
	fprintf(ff, "ALL_NODES %ld\n", (long)all_nodes.size());
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		if(all_nodes[ii] != gh_null){
			//all_nodes[ii]->print_addr(ff);
			all_nodes[ii]->print_node(ff, md);
		} else {
			fprintf(ff, "gh_null NODE\n");
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
	fprintf(ff, "TOTAL_NODES %ld\n", (long)all_nodes.size());
	fprintf(ff, "TOTAL_DIRECT %ld\n", (long)all_direct.size());
	fprintf(ff, "\n");
	fflush(ff);
}

void
htarget_box::print_box(FILE* ff, gh_prt_mode_t md){
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
hlognet_box::print_targets(FILE* ff, gh_prt_mode_t md){
	fprintf(ff, "ALL_TARGET %ld\n", (long)all_targets.size());
	for(long ii = 0; ii < (long)all_targets.size(); ii++){
		GH_CK(all_targets[ii] != gh_null);
		all_targets[ii]->print_node(ff, md);
	}
}

void
hlognet_box::print_box(FILE* ff, gh_prt_mode_t md){
	hnode_box::print_box(ff, md);
	print_targets(ff, md);
	fprintf(ff, "TOTAL_NODES %ld\n", (long)all_nodes.size());
	fprintf(ff, "TOTAL_TARGET %ld\n", (long)all_targets.size());
	fprintf(ff, "height = %ld max_lgnet_sz= %ld\n", height, height + 1);
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

/*
hnode_box*
gh_get_binnet_sm_to_bm(long num_in, long num_out, const char* dbg_qrt, gh_dbg_call_t dbg_case){
	hnode_box* bx = new hnode_box();
	long dpth = 0;
	GH_MARK_USED(dpth);
	long nout = 0;
	GH_MARK_USED(nout);
	GH_CK(num_in > 0);
	GH_CK(num_in < num_out);

	bx->inputs.resize(num_in, gh_null);
	
	//bx->start_color();
	
	ppnode_vec_t next_level;
	
	long out_idx = 0;
	long out_sz = 0;
	for(long aa = 0; aa < (num_out - num_in); aa++){
		hnode_1to2* bnod = bx->add_1to2(gh_sm_to_bm_rou, dbg_qrt, dbg_case);
		
		bool in_fst_lv = (aa < num_in);
		if(! in_fst_lv && (out_idx == out_sz)){
			bx->outputs = next_level; // COPY VEC
			next_level.clear();
			out_idx = 0;
			out_sz = bx->outputs.size();
			//bx->switch_color();
		}
		
		next_level.push_back(&(bnod->out0));
		next_level.push_back(&(bnod->out1));
		
		//fprintf(stdout, "=========================================\n");
		//fprintf(stdout, "ITER %ld\n", aa);
		//fprintf(stdout, "INPUTS\n");
		//print_pt_nods(stdout, bx->inputs);
		//fprintf(stdout, "_______\n");
		//fprintf(stdout, "OUTPUTS\n");
		//print_pt_nods(stdout, bx->outputs);
		//fprintf(stdout, "_______\n");
		//fprintf(stdout, "NEXT_LV\n");
		//print_pt_nods(stdout, next_level);
		//fprintf(stdout, "_______\n");
		
		
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
	
	return bx;
}*/

hnode_box*
gh_get_binnet_bm_to_sm(long num_in, long num_out, const char* dbg_qrt){
	GH_CK(num_out > 0);
	GH_CK(num_in > num_out);
	
	hnode_box* obx = gh_get_binnet_sm_to_bm(num_out, num_in, dbg_qrt, gh_call_14);
	hnode_box* cbx = obx->convert_net_from_1to2_to_2to1();
	delete obx;
	return cbx;
}

hnode_box*
gh_get_binnet_m_to_n(long num_in, long num_out, slice_set* out_addrs, 
					 const char* dbg_qrt, gh_dbg_call_t dbg_case){
	hnode_box* bx = gh_null;

	
	GH_CK(num_in < GH_MAX_OUTS);
	GH_CK(num_out < GH_MAX_OUTS);
	GH_CK(num_in > 0);
	GH_CK(num_out > 0);
	GH_CK(num_in != num_out);
	if(num_in > num_out){
		//GH_CK(out_addrs == gh_null);
		bx = gh_get_binnet_bm_to_sm(num_in, num_out, dbg_qrt);
	} else {
		GH_CK(out_addrs != gh_null);
		bx = gh_get_binnet_sm_to_bm(num_in, num_out, dbg_qrt, dbg_case);
		bx->init_sm_to_bm_filters(out_addrs);
	}
	GH_CK(bx != gh_null);
	return bx;
}

bool
hnode::ck_link(hnode* lnk, gh_io_kind_t kk){
	gh_nk_lnk_mod_t mod = GH_GLOBALS.CK_LINK_MODE;
	GH_CK(mod != gh_invalid_ck_mod);
	
	hnode* nd = this;
	if(lnk == gh_null){
		if(mod != gh_soft_ck_mod){
			return false;
		}
		return true;
	}
	if(lnk == nd){
		if((mod != gh_soft_ck_mod) && (mod != gh_valid_self_ck_mod)){
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
hnode_box::add_1to2(gh_1to2_kind_t kk, const char* dbg_qrt, gh_dbg_call_t dbg_case){
	hnode_1to2* bnod = new hnode_1to2();
	bnod->init_to_me();
	
	bnod->rou_kind = kk;
	bnod->dbg_kind = dbg_case;
	
	if(bnod->dbg_tgt_quarter == gh_null){
		bnod->dbg_tgt_quarter = dbg_qrt;
	}

	all_nodes.push_back(bnod);
	all_nodes.back()->addr = all_nodes.size() - 1;
	return bnod;
}

hnode_2to1*
hnode_box::add_2to1(const char* dbg_qrt){
	hnode_2to1* bnod = new hnode_2to1;
	bnod->init_to_me();

	if(bnod->dbg_tgt_quarter == gh_null){
		bnod->dbg_tgt_quarter = dbg_qrt;
	}
	
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
	GH_CK(ii == (long)all_in.size());
	GH_CK(oo == (long)all_out.size());
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
	
	hnode_box* bx = new hnode_box();
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		hnode* nd = all_nodes[ii];
		GH_CK(nd != gh_null);
		GH_CK(nd->is_1to2());
		
		bx->add_2to1(nd->dbg_tgt_quarter);
	}
	
	for(long ii = 0; ii < (long)all_nodes.size(); ii++){
		GH_CK(all_nodes[ii] != gh_null);
		hnode_1to2* onod = (hnode_1to2*)(all_nodes[ii]);
		hnode_2to1* cnod = (hnode_2to1*)(bx->all_nodes[ii]);
		GH_CK(onod->addr == ii);
		GH_CK(cnod->addr == ii);
		GH_CK(onod->is_1to2());
		GH_CK(cnod->is_2to1());
		
		gh_addr_t o_in0_addr = onod->in0->addr;
		gh_addr_t o_out0_addr = onod->out0->addr;
		gh_addr_t o_out1_addr = onod->out1->addr;
		
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
			mvd_all = false;
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
gh_copy_nodes(vector<hnode*>& src, vector<hnode*>& dst, bool clr_src){
	for(long ii = 0; ii < (long)src.size(); ii++){
		if(src[ii] == gh_null){
			continue;
		}
		dst.push_back(src[ii]);
		dst.back()->addr = dst.size() - 1;
		if(clr_src){
			src[ii] = gh_null;
		}
	}
	if(clr_src){
		src.clear();
	}
}

void
gh_move_nodes(vector<hnode*>& src, vector<hnode*>& dst){
	gh_copy_nodes(src, dst, true);
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
hroute_box::init_as_2to2_route_box(slice_set* pt_out_addrs, const char* dbg_qrt){
	GH_CK(pt_out_addrs != gh_null);
	slice_set& out_addrs = *pt_out_addrs;
	GH_CK(out_addrs.size() == 2);
	
	bool is_dec_itv = out_addrs.is_dec();
	bool is_pre_itv = out_addrs.is_pre_sliced();
	
	hnode_1to2* nd0 = add_1to2(gh_2to2_nd0_rou, dbg_qrt);
	hnode_1to2* nd1 = add_1to2(gh_2to2_nd1_rou, dbg_qrt);
	hnode_2to1* nd2 = add_2to1(dbg_qrt);
	hnode_2to1* nd3 = add_2to1(dbg_qrt);
	
	if(is_dec_itv){ 
		nd0->set_flag(gh_is_gt_cmp); 
		nd1->set_flag(gh_is_gt_cmp); 
	}
	long idx_flt = 1;
	if(is_pre_itv){ 
		idx_flt = 0;
		nd0->set_flag(gh_is_eq_cmp); 
		nd1->set_flag(gh_is_eq_cmp); 
	}
	
	gh_addr_t flt_addr = out_addrs.get_addr(idx_flt);
	nd0->filter_addr = flt_addr;
	nd1->filter_addr = flt_addr;
	
	inputs.resize(2, gh_null);
	inputs[0] = (&(nd0->in0));
	inputs[1] = (&(nd1->in0));
	
	outputs.resize(2, gh_null);
	outputs[0] = (&(nd2->out0));
	outputs[1] = (&(nd3->out0));
	
	nd0->out0 = nd2;
	nd2->in0 = nd0;
	
	nd0->out1 = nd3;
	nd3->in0 = nd0;
	
	nd1->out0 = nd2;
	nd2->in1 = nd1;
	
	nd1->out1 = nd3;
	nd3->in1 = nd1;
	
	GH_CK(all_direct.empty());
}

void
hroute_box::init_as_2to3_route_box(slice_set* out_addrs, const char* dbg_qrt){
	GH_CK(out_addrs != gh_null);
	GH_CK(out_addrs->size() == 3);

	hnode_box* bx1 = gh_get_binnet_m_to_n(1, 3, out_addrs, dbg_qrt, gh_call_01);
	hnode_box* bx2 = gh_get_binnet_m_to_n(1, 3, out_addrs, dbg_qrt, gh_call_02);
	hnode_2to1* nd1 = add_2to1(dbg_qrt);
	hnode_2to1* nd2 = add_2to1(dbg_qrt);
	hnode_2to1* nd3 = add_2to1(dbg_qrt);

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

	hnode_box& dest = *this;
	bx1->move_nodes_to(dest);
	bx2->move_nodes_to(dest);
	
	delete bx1;
	delete bx2;

	init_all_addr();

	GH_CK(all_direct.empty());
}

void
hroute_box::init_as_3to2_route_box(slice_set* pt_out_addrs, const char* dbg_qrt){
	GH_CK(pt_out_addrs != gh_null);
	slice_set& out_addrs = *pt_out_addrs;
	GH_CK(out_addrs.size() == 2);

	bool is_dec_itv = out_addrs.is_dec();
	bool is_pre_itv = out_addrs.is_pre_sliced();
	
	hnode_box* bx1 = gh_get_binnet_m_to_n(3, 1, GH_NULL_OUT_ADDR, dbg_qrt, gh_call_03);
	hnode_box* bx2 = gh_get_binnet_m_to_n(3, 1, GH_NULL_OUT_ADDR, dbg_qrt, gh_call_04);
	hnode_1to2* nd1 = add_1to2(gh_3to2_nd0_rou, dbg_qrt);
	hnode_1to2* nd2 = add_1to2(gh_3to2_nd1_rou, dbg_qrt);
	hnode_1to2* nd3 = add_1to2(gh_3to2_nd2_rou, dbg_qrt);

	if(is_dec_itv){ 
		nd1->set_flag(gh_is_gt_cmp); 
		nd2->set_flag(gh_is_gt_cmp); 
		nd3->set_flag(gh_is_gt_cmp); 
	}
	long idx_flt = 1;
	if(is_pre_itv){ 
		idx_flt = 0;
		nd1->set_flag(gh_is_eq_cmp); 
		nd2->set_flag(gh_is_eq_cmp); 
		nd3->set_flag(gh_is_eq_cmp); 
	}
	
	gh_addr_t flt_addr = out_addrs.get_addr(idx_flt);
	nd1->filter_addr = flt_addr;
	nd2->filter_addr = flt_addr;
	nd3->filter_addr = flt_addr;
	
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
hlognet_box::init_as_io(slice_set& tgt_addrs){
	GH_CK(inputs.empty());
	GH_CK(outputs.empty());
	GH_CK(all_direct.empty());
	
	long tot_tgt = (long)all_targets.size();
	GH_CK(tot_tgt > 1);
	GH_CK(tot_tgt < GH_MAX_OUTS);
	GH_CK(tot_targets == tot_tgt);
	GH_CK((long)tgt_addrs.size() == tot_tgt);
	GH_CK((long)tgt_addrs.size() > 1);
	
	for(long aa = 0; aa < tot_tgt; aa++){
		hnode_target* tg = all_targets[aa];
		all_targets[aa] = gh_null;
		
		GH_CK(aa == tg->bx_idx);
		
		hnode_1to2* nd1 = add_1to2(gh_lgnet_in_rou);
		hnode_2to1* nd2 = add_2to1();
		
		nd1->set_filter_interval(aa, tgt_addrs, tot_tgt);
		nd2->set_filter_interval(aa, tgt_addrs, tot_tgt);
		
		nd2->set_flag(gh_is_lognet_io);
		
		inputs.push_back(&(nd1->in0));
		outputs.push_back(&(nd2->out0));
		
		nd1->out0 = nd2;
		nd2->in1 = nd1;
		
		GH_CK(tg->in0 != gh_null);
		GH_CK(tg->in0->is_2to1());
		hnode_2to1* tg_in = (hnode_2to1*)tg->in0;
		GH_CK(tg_in != gh_null);
		nd2->in0 = tg_in;
		tg_in->out0 = nd2;
		tg->in0 = gh_null;
		
		GH_CK(tg->out0 != gh_null);
		GH_CK(tg->out0->is_1to2());
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
hroute_box::init_route_box(long num_in, long num_out, slice_set& out_addrs, const char* dbg_qrt){
	GH_CK((long)out_addrs.size() == num_out);
	GH_CK(num_in > 0);
	GH_CK(num_out > 0);
	if((num_in == 1) || (num_out == 1)){
		GH_CK(num_in != num_out);
		if(num_in != num_out){
			hnode_box* bx = gh_get_binnet_m_to_n(num_in, num_out, &out_addrs, dbg_qrt, gh_call_05);
			hnode_box& me = *this;
			bool all = bx->move_nodes_to(me);
			GH_MARK_USED(all);
			GH_CK(all);
			delete bx;
			GH_CK(ck_route_box(num_in, num_out, 1));
			return;
		}
		GH_CK(ck_route_box(num_in, num_out, 2));
		gh_abort("**** CANNOT  hroute_box::init_route_box **** \n");
		// abort here
		return;
	}
	if((num_in == 2) && (num_out == 2)){
		init_as_2to2_route_box(&out_addrs, dbg_qrt);
		GH_CK(ck_route_box(num_in, num_out, 3));
		return;
	}
	if((num_in == 3) && (num_out == 2)){
		init_as_3to2_route_box(&out_addrs, dbg_qrt);
		GH_CK(ck_route_box(num_in, num_out, 4));
		return;
	}
	if((num_in == 2) && (num_out == 3)){
		init_as_2to3_route_box(&out_addrs, dbg_qrt);
		GH_CK(ck_route_box(num_in, num_out, 5));
		return;
	}
	
	hlognet_box* bx1 = new hlognet_box(pw_base);
	bx1->init_lognet_box(num_out, out_addrs, dbg_qrt);
	bx1->init_as_io(out_addrs);
	
	GH_CK((long)(bx1->inputs.size()) == num_out);
	GH_CK((long)(bx1->outputs.size()) == num_out);
	
	hnode_box* bx2 = gh_null;
	if(num_in != num_out){
		bx2 = gh_get_binnet_m_to_n(num_in, num_out, &out_addrs, dbg_qrt, gh_call_06); // CAN_HAVE_DIRECT
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
htarget_box::join_box_outputs(long fst_idx1, hnode_box* bx1, long fst_idx2, hnode_box* bx2, 
							  long num_idx, ppnode_vec_t& all_out, const char* dbg_qrt)
{
	GH_CK(bx1 != gh_null);
	GH_CK(bx2 != gh_null);
	GH_CK((fst_idx1 + num_idx) <= (long)bx1->outputs.size());
	GH_CK((fst_idx2 + num_idx) <= (long)bx2->outputs.size());
	long idx1 = fst_idx1;
	long idx2 = fst_idx2;
	for(long aa = 0; aa < (long)num_idx; aa++, idx1++, idx2++){
		hnode_2to1* nd_out = add_2to1(dbg_qrt);
		bx1->connect_output_to_node_input(idx1, *nd_out, 0);
		bx2->connect_output_to_node_input(idx2, *nd_out, 1);

		all_out.push_back(&(nd_out->out0));
	}
}

void
hlognet_box::init_length(long num_elems){
	if(tot_targets == num_elems){
		return;
	}
		
	double lbb = log2(get_base());
	double lnn = log2(num_elems - 1);
	height = (long)(lnn/lbb) + 1;

	tot_targets = num_elems;
}

htarget_box*
hlognet_box::get_target_box(long idx, slice_set& tgt_addrs){
	long the_sz = tot_targets;
	GH_CK(idx < the_sz);
	htarget_box* bx = new htarget_box(pw_base);

	bool was_top = (GH_GLOBALS.dbg_curr_tgt_addr == GH_INVALID_ADDR);
	if(was_top){
		GH_GLOBALS.dbg_curr_tgt_addr = idx;
	}
	
	long nin = 0;
	long nout = 0;
	gh_calc_num_io(get_base(), the_sz, idx, nin, nout);
	GH_CK((idx == 0) || (nin >= nout));
	bx->init_target_box(idx, nin, nout, tgt_addrs, the_sz);
	bx->dbg_init_tgt_szs();
	
	if(was_top){
		GH_GLOBALS.dbg_curr_tgt_addr = GH_INVALID_ADDR;
	}
	
	return bx;
}

void 
gh_calc_num_io(long base, long len, long idx, long& num_in, long& num_out){
	GH_CK(base > 1);
	GH_CK(len > 1);
	GH_CK(idx < len);
	
	double lbb = log2(base);
	double lnn = log2(len - 1);
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
		if((idx + pw) < len){
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
	GH_CK((target->in0 == target) || (target->in0->is_2to1()));
	GH_CK((target->out0 == target) || (target->out0->is_1to2()));
	GH_CK(all_direct.empty());
	return true;
}

void
htarget_box::init_target_box(long tgt_idx, long lft_ht, long rgt_ht, slice_set& tgt_addrs, long tot_tgt){
	GH_CK(tgt_idx >= 0);
	if((lft_ht <= 1) || (rgt_ht <= 1)){
		init_basic_target_box(tgt_idx, lft_ht, rgt_ht, tgt_addrs, tot_tgt);
		GH_CK(ck_target_box(lft_ht, rgt_ht));
		return;
	}
	hnode_box& dest = *this;
	
	GH_CK(lft_ht > 1);
	GH_CK(rgt_ht > 1);
	hroute_box* lft = new hroute_box(pw_base);
	hroute_box* rgt = new hroute_box(pw_base);
	
	hnode_2to1* tg_in = add_2to1();
	hnode_1to2* tg_out = add_1to2(gh_tgt_out_rou);
	
	tg_out->set_filter_addr(tgt_idx, tgt_addrs);
	
	slice_set lft_addrs;
	lft_addrs.init_slice_set(tgt_idx, tgt_addrs, rgt_ht + 1, 
					 GH_BASE_TWO, gh_left_side, true, "lft_addrs");
	
	slice_set rgt_addrs;
	rgt_addrs.init_slice_set(tgt_idx, tgt_addrs, lft_ht + 1, 
					 GH_BASE_TWO, gh_right_side, true, "rgt_addrs");
	
	lft->init_route_box(lft_ht, rgt_ht + 1, lft_addrs, GH_QRT(GH_LI));
	rgt->init_route_box(rgt_ht, lft_ht + 1, rgt_addrs, GH_QRT(GH_RI));

	slice_set spl_lft_addrs;
	spl_lft_addrs.init_slice_set(tgt_idx, tgt_addrs, rgt_ht, 
					 GH_BASE_TWO, gh_left_side, false, "spl_lft_addrs");
	
	slice_set spl_rgt_addrs;
	spl_rgt_addrs.init_slice_set(tgt_idx, tgt_addrs, lft_ht, 
					 GH_BASE_TWO, gh_right_side, false, "spl_rgt_addrs");
	
	hnode_box* spl_lft = gh_get_binnet_m_to_n(1, rgt_ht, &spl_lft_addrs, GH_QRT(GH_LO), gh_call_07);
	hnode_box* spl_rgt = gh_get_binnet_m_to_n(1, lft_ht, &spl_rgt_addrs, GH_QRT(GH_RO), gh_call_08);

	//GH_DBG_CODE(gh_dbg_init_watch_box(*spl_rgt, &dest));
	//GH_DBG_CODE(gh_dbg_init_watch_box(*spl_rgt, spl_rgt));
	
	join_box_outputs(1, lft, 0, spl_lft, rgt_ht, lft_out, GH_QRT(GH_LO));
	join_box_outputs(1, rgt, 0, spl_rgt, lft_ht, rgt_out, GH_QRT(GH_RO));
	
	target = new hnode_target();
	target->bx_idx = tgt_idx;	
	
	target->in0 = tg_in;
	tg_in->out0 = target;
	target->out0 = tg_out;
	tg_out->in0 = target;
	
	lft->connect_output_to_node_input(0, *tg_in, 0);
	rgt->connect_output_to_node_input(0, *tg_in, 1);
	
	spl_lft->connect_node_output_to_input(*tg_out, 1, 0);
	spl_rgt->connect_node_output_to_input(*tg_out, 0, 0);
	
	gh_move_io(gh_in_kind, lft->inputs, lft_in);
	gh_move_io(gh_in_kind, rgt->inputs, rgt_in);
	gh_move_io(gh_out_kind, spl_lft->outputs, lft_out);
	gh_move_io(gh_out_kind, spl_rgt->outputs, rgt_out);
	
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
hlognet_box::init_lognet_box(long num_elems, slice_set& tgt_addrs, const char* dbg_qrt){
	GH_CK(tgt_addrs.empty() || ((long)tgt_addrs.size() == num_elems));
	GH_CK(num_elems > 1);
	
	GH_DBG_CODE(gh_prt_addr_vec(tgt_addrs, "\nlgnetbox="));
	
	bool was_top = (GH_GLOBALS.dbg_curr_tgt_quarter == gh_null);
	if(was_top){
		GH_GLOBALS.dbg_curr_tgt_quarter = dbg_qrt;
	}
	
	init_length(num_elems);

	//print_box(stdout, gh_full_prt);
	
	hlognet_box& dest = *this;
	
	htarget_box* prv_bx = gh_null;
	for(long aa = 0; aa < num_elems; aa++){
		//fprintf(stdout, "ITER %ld of %ld ===========================================\n", aa, num_elems);
		//print_box(stdout, gh_full_prt);
		
		htarget_box* bx = get_target_box(aa, tgt_addrs);
		
		GH_CK(bx->target != gh_null);
		hnode_target& tgt = *(bx->target);
		
		tgt.set_filter_interval(aa, tgt_addrs, num_elems);

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
			prv_bx->print_box(stdout, gh_full_pt_prt);
			fprintf(stdout, "BX ______________\n");
			bx->print_box(stdout, gh_full_pt_prt);
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
			prv_bx->print_box(stdout, gh_full_pt_prt);
			fprintf(stdout, "BX ______________\n");
			bx->print_box(stdout, gh_full_pt_prt);
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
	//print_box(stdout, gh_full_pt_prt);
	
	//fprintf(stdout, "LGNET_BOX %ld **********************************************\n", length());
	//fflush(stdout);
	
	if(was_top){
		GH_GLOBALS.dbg_curr_tgt_quarter = gh_null;
	}
	
	GH_DBG_CODE(print_targets(stdout, gh_full_prt));
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
	GH_CK(tot_targets == (long)all_targets.size());
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
htarget_box::init_basic_target_box(long tgt_idx, long lft_ht, long rgt_ht, slice_set& tgt_addrs, long tot_tgt){
	GH_CK(tgt_idx >= 0);
	GH_CK(lft_ht >= 0);
	GH_CK(rgt_ht >= 0);
	GH_CK((lft_ht <= 1) || (rgt_ht <= 1));
	
	bool is_dec_itv = tgt_addrs.is_dec();
	
	hnode_box& dest = *this;
	
	long full_ht = lft_ht + rgt_ht;
	
	target = new hnode_target();
	target->bx_idx = tgt_idx;
	
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
		
		gh_route_side_t rou_side = (lft_ht == 0)?(gh_left_side):(gh_right_side);
	
		slice_set spl_out_addrs;
		spl_out_addrs.init_slice_set(tgt_idx, tgt_addrs, full_ht, 
					 GH_BASE_TWO, rou_side, false, "spl_out_addrs");

		hnode_box* spl_in = gh_get_binnet_m_to_n(full_ht, 1, GH_NULL_OUT_ADDR, gh_null, gh_call_09);
		hnode_box* spl_out = gh_get_binnet_m_to_n(1, full_ht, &spl_out_addrs, gh_null, gh_call_10);
		
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

	hnode_2to1* tg_in = add_2to1();
	hnode_1to2* tg_out = add_1to2(gh_bs_tgt_out_rou);
	
	tg_out->set_filter_addr(tgt_idx, tgt_addrs);
	
	target->in0 = tg_in;
	tg_in->out0 = target;
	target->out0 = tg_out;
	tg_out->in0 = target;
	
	if((lft_ht == 1) && (rgt_ht == 1)){
		
		if(get_base() == GH_BASE_TWO){
			
			lft_in.push_back(&(tg_in->in0));
			lft_out.push_back(&(tg_out->out1));
			rgt_in.push_back(&(tg_in->in1));
			rgt_out.push_back(&(tg_out->out0));
					
			GH_CK(target->in0->get_kind() == gh_2_to_1_nod);
			GH_CK(target->out0->get_kind() == gh_1_to_2_nod);
		} else {

			hnode_1to2* l_in = add_1to2(gh_bs_tgt_lft_in_rou);
			hnode_2to1* l_out = add_2to1();
			hnode_1to2* r_in = add_1to2(gh_bs_tgt_rgt_in_rou);
			hnode_2to1* r_out = add_2to1();
			
			l_in->set_filter_interval(tgt_idx, tgt_addrs, tot_tgt);
			r_in->set_filter_interval(tgt_idx, tgt_addrs, tot_tgt);
			
			l_in->out1 = l_out;
			l_out->in0 = l_in;
			
			l_in->out0 = tg_in;
			tg_in->in0 = l_in;

			l_out->in1 = tg_out;
			tg_out->out1 = l_out;
			
			tg_out->out0 = r_out;
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
	
	gh_route_side_t rt_side = (lft_ht == 1)?(gh_left_side):(gh_right_side);
	bool lft1 = (lft_ht == 1);
	
	long bt1_ht = full_ht - 1;
	GH_CK(bt1_ht > 1);
	GH_CK((lft_ht == bt1_ht) || (rgt_ht == bt1_ht));
	
	hroute_box* rt_in_bx = new hroute_box(pw_base);
	
	gh_route_side_t rt_in_bx_sd = gh_get_opp_side(rt_side);
	if(is_dec_itv){
		//rt_in_bx_sd = gh_get_opp_side(rt_in_bx_sd);
	}
	
	slice_set rt_in_bx_addrs;
	rt_in_bx_addrs.init_slice_set(tgt_idx, tgt_addrs, 2, 
					GH_BASE_TWO, rt_in_bx_sd, true, "rt_in_bx_addrs");
	
	rt_in_bx->init_as_2to2_route_box(&rt_in_bx_addrs, gh_null);
	
	GH_CK(all_direct.empty());
	if(bt1_ht > 2){
		hnode_box* bn = gh_get_binnet_m_to_n(bt1_ht, 2, GH_NULL_OUT_ADDR, gh_null, gh_call_11); // CAN_HAVE_DIRECT
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
	
	slice_set spl_bx_in_addrs;
	spl_bx_in_addrs.init_slice_set(tgt_idx, tgt_addrs, bt1_ht, 
					GH_BASE_TWO, rt_side, false, "spl_bx_in_addrs");
	
	slice_set spl_bx_out_addrs;
	spl_bx_out_addrs.init_slice_set(tgt_idx, tgt_addrs, bt1_ht, 
					GH_BASE_TWO, rt_side, false, "spl_bx_out_addrs");
	
	hnode_box* spl_bx_in = gh_get_binnet_m_to_n(1, bt1_ht, &spl_bx_in_addrs, gh_null, gh_call_12);
	hnode_box* spl_bx_out = gh_get_binnet_m_to_n(1, bt1_ht, &spl_bx_out_addrs, gh_null, gh_call_13);

	hnode_1to2* bx_in = add_1to2(gh_bs_tgt_bx_in_rou); // ERROR_tg3
	hnode_2to1* bx_out = add_2to1();
	
	bx_in->set_filter_interval(tgt_idx, tgt_addrs, tot_tgt);
	
	if(lft1){
		GH_CK(lft_ht == 1);
		GH_CK(rgt_ht > 1);
		
		spl_bx_in->connect_node_output_to_input(*bx_in, 1, 0);
		spl_bx_out->connect_node_output_to_input(*tg_out, 1, 0);
		rt_in_bx->connect_output_to_node_input(0, *tg_in, 1);
		rt_in_bx->connect_output_to_node_input(1, *bx_out, 1);
		
		bx_in->out0 = tg_in;
		tg_in->in0 = bx_in;
		
		tg_out->out0 = bx_out;
		bx_out->in0 = tg_out;
		
		join_box_outputs(0, spl_bx_in, 0, spl_bx_out, bt1_ht, lft_out, GH_QRT(GH_LO));
		
		lft_in.push_back(&(bx_in->in0));
		rgt_out.push_back(&(bx_out->out0));
	} else {
		GH_CK(lft_ht > 1);
		GH_CK(rgt_ht == 1);

		rt_in_bx->connect_output_to_node_input(0, *tg_in, 0);
		rt_in_bx->connect_output_to_node_input(1, *bx_out, 0);
		spl_bx_out->connect_node_output_to_input(*tg_out, 0, 0);
		spl_bx_in->connect_node_output_to_input(*bx_in, 1, 0);
		
		tg_out->out1 = bx_out;
		bx_out->in1 = tg_out;
		
		tg_in->in1 = bx_in;
		bx_in->out0 = tg_in;
		
		join_box_outputs(0, spl_bx_in, 0, spl_bx_out, bt1_ht, rgt_out, GH_QRT(GH_RO));

		lft_out.push_back(&(bx_out->out0));
		rgt_in.push_back(&(bx_in->in0));
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
	
} // end_of_init_basic_target_box

gh_addr_t
gh_calc_power(long base, gh_addr_t adr){
	GH_CK(base > 1);
	bool was_neg = (adr < 0);
	double pp = pow(base, labs(adr));
	if(pp > LONG_MAX){
		gh_abort("**** power_too_big_case_2. pow(%ld, %ld) > LONG_MAX **** \n", base, adr);
	}
	gh_addr_t vout = (gh_addr_t)pp;
	if(was_neg){
		vout = -vout;
	}
	return vout;
}

gh_addr_t
gh_calc_side(gh_route_side_t sd, gh_addr_t adr){
	GH_CK(sd != gh_invalid_side);
	if(sd == gh_right_side){ return -adr; } 
	return adr;
}

gh_addr_t
gh_dec_power(long base, gh_addr_t adr){
	GH_CK(base > 1);
	gh_addr_t vout = 0;
	if(labs(adr) >= base){
		GH_CK((adr % base) == 0);
		vout = adr / base;
	} 
	return vout;
}

void
htarget_box::dbg_init_tgt_szs(){
	hnode_target* tgt = target;
	GH_CK(tgt != gh_null);
	tgt->dbg_lft_in_sz = (long)(lft_in.size());
	tgt->dbg_lft_out_sz = (long)(lft_out.size());
	tgt->dbg_rgt_in_sz = (long)(rgt_in.size());
	tgt->dbg_rgt_out_sz = (long)(rgt_out.size());
}

void
gh_pos_to_addr(gh_addr_t tgt_idx, slice_set& tgt_addrs, 
					addr_vec_t& all_rel_pos, slice_set& all_addrs)
{
	GH_CK(tgt_addrs.size() < GH_MAX_OUTS);
	GH_CK(all_rel_pos.size() < GH_MAX_OUTS);
	GH_CK(all_addrs.size() == 0);
	GH_CK(tgt_idx >= 0);
	GH_CK(tgt_addrs.empty() || (tgt_idx < (gh_addr_t)tgt_addrs.size()));
	GH_CK(all_rel_pos.size() > 1);
	
	//bool pos_is_addr = tgt_addrs.empty();

	for(long aa = 0; aa < (long)all_rel_pos.size(); aa++){
		gh_addr_t pos = tgt_idx + all_rel_pos[aa];
		GH_DBG_CODE(
			if(pos < 0){
				fprintf(stdout, "errdata---------------\n");
				gh_prt_addr_vec(tgt_addrs, "tgt_addrs");
				gh_prt_addr_vec(all_addrs, "all_addrs");
			}
		);
		GH_CK_PRT((pos >= 0), "tgt_idx=%ld, rel_pos=%ld \n", tgt_idx, all_rel_pos[aa]);
		GH_CK(tgt_addrs.empty() || (pos < (gh_addr_t)tgt_addrs.size()));
		gh_addr_t addr = pos;
		if(! tgt_addrs.empty()){
			addr = tgt_addrs.get_addr(pos);
		}
		GH_CK(addr >= 0);
		all_addrs.push_addr(addr);
	}
	
	GH_CK(all_addrs.size() == (long)all_rel_pos.size());
}

void 
gh_prt_addr_vec(slice_set& tgt_addrs, const char* pfx)
{
	if(pfx != gh_null){
		fprintf(stdout, "%s ", pfx);
	}
	fprintf(stdout, "<%s>[", gh_dbg_get_slice_tp_str(tgt_addrs.sls_orig));
	for(long aa = 0; aa < (long)tgt_addrs.size(); aa++){
		fprintf(stdout, " %ld", tgt_addrs.get_addr(aa));
	}
	fprintf(stdout, "]\n");
}

void 
gh_prt_addr_vec_with(gh_addr_t tgt_idx, slice_set& tgt_addrs, slice_set& all_addrs,
					  long sz, long pw_b, gh_route_side_t sd, bool has_z, const char* dbg_str)
{
	fprintf(stdout, "%s_addr_vec.tg_idx=%ld.sz=%ld,bs=%ld,sd=%s,zr=%s\n", dbg_str, tgt_idx, sz, pw_b, 
			gh_dbg_get_side_str(sd), (has_z)?("true"):("false"));
	gh_prt_addr_vec(tgt_addrs, "tgt_addrs");
	gh_prt_addr_vec(all_addrs, dbg_str);
}

void 
slice_set::init_slice_set(gh_addr_t tgt_idx, slice_set& tgt_addrs, 
					  long sz, long pw_b, gh_route_side_t sd, bool has_z, const char* dbg_str)
{
	slice_set& all_addrs = *this;
	addr_vec_t all_rel_pos;
	gh_init_rel_pos(all_rel_pos, sz, pw_b, sd, has_z);
	gh_pos_to_addr(tgt_idx, tgt_addrs, all_rel_pos, all_addrs);
	init_orig(tgt_addrs);
	
	GH_DBG_CODE(gh_prt_addr_vec_with(tgt_idx, tgt_addrs, all_addrs, sz, pw_b, sd, has_z, dbg_str));
}

long
hnode_1to2::get_smallest_idx(){
	GH_CK(out0 != gh_null);
	GH_CK(out0->is_1to2());
	hnode_1to2* nd = this;
	hnode_1to2* oo = (hnode_1to2*)out0;
	while(oo != nd){
		nd = (hnode_1to2*)oo;
		oo = (hnode_1to2*)(nd->out0);
		GH_CK(oo->is_1to2());
	}
	GH_CK(nd->o_idx0 != GH_INVALID_IDX);
	return nd->o_idx0;
}

long
hnode_1to2::get_biggest_idx(){
	GH_CK(out1 != gh_null);
	GH_CK(out1->is_1to2());
	hnode_1to2* nd = this;
	hnode_1to2* oo = (hnode_1to2*)out1;
	while(oo != nd){
		nd = (hnode_1to2*)oo;
		oo = (hnode_1to2*)(nd->out1);
		GH_CK(oo->is_1to2());
	}
	GH_CK(nd->o_idx1 != GH_INVALID_IDX);
	return nd->o_idx1;
}

void
hnode_1to2::set_outs_smallest_idx(){
	hnode_1to2* oo0 = get_1to2_out0();
	hnode_1to2* oo1 = get_1to2_out1();

	if(oo0 != this){
		o_idx0 = oo0->get_out1_smallest_idx();
		oo0->filter_addr = o_idx0;
		oo0->set_outs_smallest_idx();
	}
	if(oo1 != this){
		o_idx1 = oo1->get_out1_smallest_idx();
		oo1->filter_addr = o_idx1;
		oo1->set_outs_smallest_idx();
	}
}

void
hnode_1to2::set_outs_biggest_idx(){
	hnode_1to2* oo0 = get_1to2_out0();
	hnode_1to2* oo1 = get_1to2_out1();

	if(oo0 != this){
		o_idx0 = oo0->get_out0_biggest_idx();
		oo0->filter_addr = o_idx0;
		oo0->set_outs_biggest_idx();
	}
	if(oo1 != this){
		o_idx1 = oo1->get_out0_biggest_idx();
		oo1->filter_addr = o_idx1;
		oo1->set_outs_biggest_idx();
	}
}

void 
gh_init_rel_pos(addr_vec_t& all_rel_pos, long sz, long pw_b, gh_route_side_t sd, bool has_z)
{
	GH_CK(pw_b > 1);
	GH_CK(sz > 0);
	all_rel_pos.resize(sz, 0);
	long min_ii = 0;
	if(has_z){
		all_rel_pos[0] = 0;
		min_ii = 1;
	}
	long nxt_pw = 0;
	for(long aa = min_ii; aa < sz; aa++){
		gh_addr_t vv = gh_calc_power(pw_b, nxt_pw);
		GH_CK(vv > 0);
		nxt_pw++;
		if(sd == gh_right_side){
			vv = -vv;
		}
		all_rel_pos[aa] = vv;
	}
}

void
hnode_box::init_sm_to_bm_filters(slice_set* pt_out_addrs){
	GH_CK(pt_out_addrs != gh_null);
	slice_set& out_addrs = *pt_out_addrs;
	
	
	GH_CK(out_addrs.sls_orig != gh_invalid_slc);
	GH_CK((long)out_addrs.size() > 1);
	bool is_dec_itv = out_addrs.is_dec();
	bool is_pre_itv = out_addrs.is_pre_sliced();
	
	ppnode_vec_t& all_out = outputs;
	for(long aa = 0; aa < (long)all_out.size(); aa++){
		hnode** ppo = all_out[aa];
		GH_CK(ppo != gh_null);
		GH_CK(gh_is_free_io(ppo));
		hnode* po = *ppo;
		GH_CK(po != gh_null);
		
		gh_hnode_kind_t kk = po->get_kind();
		GH_CK(gh_is_1to1(kk) || gh_is_1to2(kk));
		
		if(gh_is_1to2(kk)){
			hnode_1to2* nd = (hnode_1to2*)po;
			if(nd->is_out0(ppo)){
				nd->o_idx0 = out_addrs.get_addr(aa);
			} else {
				GH_CK(nd->is_out1(ppo));
				nd->o_idx1 = out_addrs.get_addr(aa);
			}
			if(is_dec_itv){ nd->set_flag(gh_is_gt_cmp); }
			if(is_pre_itv){ nd->set_flag(gh_is_eq_cmp); }
		}
	}

	ppnode_vec_t& all_in = inputs;
	
	//vector<long> in_idx_vec;
	//in_idx_vec.resize(all_in.size(), GH_INVALID_IDX);
	
	
	for(long aa = 0; aa < (long)all_in.size(); aa++){
		hnode** ppi = all_in[aa];
		GH_CK(ppi != gh_null);
		GH_CK(gh_is_free_io(ppi));
		hnode* pi = *ppi;
		GH_CK(pi != gh_null);
		
		gh_hnode_kind_t kk = pi->get_kind();
		GH_CK(gh_is_1to1(kk) || gh_is_1to2(kk));
		
		if(gh_is_1to2(kk)){
			hnode_1to2* nd = (hnode_1to2*)pi;
			long o_idx = GH_INVALID_IDX;
			
			if(is_pre_itv){
				nd->set_outs_biggest_idx();
				o_idx = nd->get_out0_biggest_idx();
			} else {
				nd->set_outs_smallest_idx();
				o_idx = nd->get_out1_smallest_idx();
			}
			
			GH_CK(o_idx != GH_INVALID_IDX);
			nd->filter_addr = o_idx;
			if(is_dec_itv){ nd->set_flag(gh_is_gt_cmp); }
			if(is_pre_itv){ nd->set_flag(gh_is_eq_cmp); }
		}
	}
}

void
hnode::set_filter_interval(long tgt_idx, slice_set& tgt_addrs, long tot_tgt){
	GH_CK(tgt_idx >= 0);
	GH_CK(tgt_idx < tot_tgt);
	GH_CK(tot_tgt > 1);

	gh_addr_t nx_tg_idx = tgt_idx + 1;
	
	set_flag(gh_is_interval);
	if(tgt_addrs.empty()){
		if(nx_tg_idx >= tot_tgt){
			filter_addr = tgt_idx;
			set_flag(gh_is_gt_cmp);
			set_flag(gh_is_eq_cmp);
			return;
		}
		if(tgt_idx > 0){
			set_flag(gh_has_limit);
		}
		filter_addr = nx_tg_idx;
		filter_lim_addr = tgt_idx;
		return;
	}
	
	GH_CK(tot_tgt == (long)tgt_addrs.size());
	bool is_dec_itv = tgt_addrs.is_dec();
	bool is_pre_itv = tgt_addrs.is_pre_sliced();
	bool has_lim = (tgt_idx > 0) && (tgt_idx < (tot_tgt - 1));
	
	if(is_pre_itv || (tgt_idx == (tot_tgt - 1))){
		set_flag(gh_is_eq_cmp);
	}
	if(has_lim){
		set_flag(gh_has_limit);
	}
	if(is_dec_itv){
		set_flag(gh_is_gt_cmp);
	}
	
	gh_addr_t tg_addr = tgt_addrs.get_addr(tgt_idx);
	gh_addr_t nx_tg_addr = GH_INVALID_ADDR;
	gh_addr_t pr_tg_addr = GH_INVALID_ADDR;
	if(tgt_idx < (tot_tgt - 1)){
		GH_CK((tgt_idx <= 0) || has_lim);
		nx_tg_addr = tgt_addrs.get_addr(tgt_idx + 1);
	}
	if(tgt_idx > 0){
		GH_CK((tgt_idx >= (tot_tgt - 1)) || has_lim);
		pr_tg_addr = tgt_addrs.get_addr(tgt_idx - 1);
	}

	if(! is_pre_itv && (tgt_idx == (tot_tgt - 1))){
		GH_CK(! get_flag(gh_has_limit));
		reset_flag(gh_is_gt_cmp);
		if(! is_dec_itv){
			set_flag(gh_is_gt_cmp);
		} 
		filter_addr = tg_addr;
		return;
	}
	
	if(is_pre_itv){
		filter_addr = tg_addr;
		filter_lim_addr = pr_tg_addr;
	} else {
		filter_addr = nx_tg_addr;
		filter_lim_addr = tg_addr;
	}
}

void
hnode::set_filter_addr(long tgt_idx, slice_set& tgt_addrs){
	gh_addr_t tg_addr = tgt_idx;

	//GH_DBG_CODE(gh_prt_addr_vec(tgt_addrs, "set_filter_addr.tgt_addrs="));
	
	bool is_pre_itv = false;
	bool is_dec_itv = false;
	
	if(! tgt_addrs.empty()){
		long the_sz = (long)tgt_addrs.size();
		GH_CK(the_sz > 1);
		
		is_dec_itv = tgt_addrs.is_dec();
		is_pre_itv = tgt_addrs.is_pre_sliced();
		tg_addr = tgt_addrs.get_addr(tgt_idx);
	}	
	
	filter_addr = tg_addr;
	if(is_dec_itv){ set_flag(gh_is_gt_cmp); }
	if(is_pre_itv){ set_flag(gh_is_eq_cmp); }
}

hnode_box*
gh_get_binnet_sm_to_bm(long num_in, long num_out, const char* dbg_qrt, gh_dbg_call_t dbg_case){
	hnode_box* bx = new hnode_box();
	long dpth = 0;
	GH_MARK_USED(dpth);
	long nout = 0;
	GH_MARK_USED(nout);
	GH_CK(num_in > 0);
	GH_CK(num_in < num_out);
	GH_CK(bx->outputs.empty());
	
	bx->inputs.resize(num_in, gh_null);
	
	ppnode_vec_t next_level;
	
	for(long aa = 0; aa < (num_out - num_in); aa++){
		hnode_1to2* bnod = bx->add_1to2(gh_sm_to_bm_rou, dbg_qrt, dbg_case);
		
		bool in_fst_lv = (aa < num_in);
		if(! in_fst_lv && bx->outputs.empty()){
			bx->outputs = next_level; // COPY VEC
			next_level.clear();
		}
		
		next_level.push_back(&(bnod->out0));
		next_level.push_back(&(bnod->out1));
		
		//fprintf(stdout, "=========================================\n");
		//fprintf(stdout, "ITER %ld\n", aa);
		//fprintf(stdout, "INPUTS\n");
		//print_pt_nods(stdout, bx->inputs);
		//fprintf(stdout, "_______\n");
		//fprintf(stdout, "OUTPUTS\n");
		//print_pt_nods(stdout, bx->outputs);
		//fprintf(stdout, "_______\n");
		//fprintf(stdout, "NEXT_LV\n");
		//print_pt_nods(stdout, next_level);
		//fprintf(stdout, "_______\n");
		
		
		if(in_fst_lv){
			GH_CK(bx->outputs.empty());

			//fprintf(stdout, "STARTING_aa=%ld\n", aa);
			
			bx->inputs[aa] = (&(bnod->in0));
			GH_CK(*(bx->inputs[aa]) == bnod);
		} else {
			GH_CK(! bx->outputs.empty());
			
			hnode** old_pt_out = bx->outputs.back();

			hnode* old_nd = *(old_pt_out);
			hnode_1to2* old_out = (hnode_1to2*)old_nd;

			//fprintf(stdout, "DOING__ %ld:%p:%p\n", out_idx, (void*)old_pt_out, (void*)old_out);
			
			bnod->in0 = old_out;
			*old_pt_out = bnod;
			
			bx->outputs.pop_back();
		}
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

edge
edge::get_compl(){
	edge co;
	GH_CK(! co.is_eq());
	GH_CK(! co.is_gt());
	if(is_undef()){
		set_flag(gh_is_undef);
		return co;
	}
	if(! is_eq()){
		co.set_flag(gh_is_eq_cmp);
	}
	if(! is_gt()){
		co.set_flag(gh_is_gt_cmp);
	}
	co.slc_edge = slc_edge;
	return co;
}

void
slice_vec::print_slice_vec(FILE* ff){
	fprintf(ff, "{");
	for(long aa = 0; aa < (long)size(); aa++){
		if(aa != 0){
			fprintf(ff, " ");
		}
		edge& eg = at(aa);
		eg.print_edge(ff);
	}
	fprintf(ff, "}\n");
	fflush(ff);
}

interval
slice_vec::get_interval(long idx){
	GH_CK(idx >= 0);
	GH_CK(idx < (long)size());
	GH_CK(size() > 1);
	
	interval itv;
	
	if(idx == 0){
		itv.lft.set_flag(gh_is_undef);
		itv.rgt = at(idx);
		return itv;
	}
	if(idx == ((long)size() - 1)){
		itv.lft = at(idx);
		itv.rgt.set_flag(gh_is_undef);
		return itv;
	}
	
	itv.lft = at(idx - 1).get_compl();
	itv.rgt = at(idx);	
	return itv;
}

void
slice_vec::print_all_intervals(FILE* ff){
	fprintf(ff, "{");
	for(long aa = 0; aa < (long)size(); aa++){
		if(aa != 0){
			fprintf(ff, " ");
		}
		interval itv = get_interval(aa);
		itv.print_interval(ff);
	}
	fprintf(ff, "}\n");
	fflush(ff);
}

void
slice_vec::init_slice_vec_with(gh_addr_t slc_idx, addr_vec_t& all_rel_pos){
	GH_CK(all_rel_pos.size() < GH_MAX_OUTS);
	GH_CK(slc_idx >= 0);
	GH_CK(empty());
	GH_CK(all_rel_pos.size() > 1);
	
	bool r_dec = (all_rel_pos.back() < 0);
	long pos = 0;
	
	for(long aa = 1; aa < (long)all_rel_pos.size(); aa++){
		pos = slc_idx + all_rel_pos[aa];
		GH_CK(pos >= 0);
		
		edge eg;
		if(r_dec){
			eg.set_flag(gh_is_gt_cmp);
		} 
		eg.slc_edge = pos;
		
		GH_CK(! eg.is_undef());
		push_back(eg);
	}
	
	edge lst;
	lst.set_flag(gh_is_eq_cmp);
	if(! r_dec){
		lst.set_flag(gh_is_gt_cmp);
	} 
	lst.slc_edge = pos;
	
	GH_CK(! lst.is_undef());
	push_back(lst);
	
	GH_CK(size() == all_rel_pos.size());
}

void 
slice_vec::init_sub_slices_with(gh_addr_t slc_idx, slice_vec& all_slices, addr_vec_t& all_rel_pos)
{
	GH_CK(all_slices.size() < GH_MAX_OUTS);
	GH_CK(all_rel_pos.size() < GH_MAX_OUTS);
	GH_CK(size() == 0);
	GH_CK(slc_idx >= 0);
	GH_CK(all_slices.empty() || (slc_idx < (long)all_slices.size()));
	GH_CK(all_rel_pos.size() > 1);
	
	if(all_slices.empty()){
		init_slice_vec_with(slc_idx, all_rel_pos);
		return;
	}
	
	bool o_dec = all_slices.is_dec();
	bool r_dec = (all_rel_pos.back() < 0);
	GH_MARK_USED(o_dec);
	GH_MARK_USED(r_dec);
	
	long pos = 0;
	interval nxt_itv;
	
	for(long aa = 1; aa < (long)all_rel_pos.size(); aa++){
		pos = slc_idx + all_rel_pos[aa];
		GH_CK(pos >= 0);
		GH_CK(pos < (long)all_slices.size());
		
		nxt_itv = all_slices.get_interval(pos);
		
		edge eg;
		if(r_dec){
			eg = nxt_itv.rgt.get_compl();
		} else {
			eg = nxt_itv.lft.get_compl();
		}
		
		GH_CK(! eg.is_undef());
		push_back(eg);
	}
	
	edge lst;
	if(r_dec){
		lst = nxt_itv.rgt;
	} else {
		lst = nxt_itv.lft;
	}
	GH_CK(! lst.is_undef());
	push_back(lst);
	
	GH_CK(size() == all_rel_pos.size());
}

