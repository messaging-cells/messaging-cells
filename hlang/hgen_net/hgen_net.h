

#ifndef GEN_HNET_H
#define GEN_HNET_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <vector>
#include <iterator>

#include "gh_dbg_util.h"

using namespace std;

#define GH_INVALID_IDX -1

enum hg_prt_mode_t {
	hg_addr_prt,
	hg_full_prt,
	hg_full_pt_prt,
	hg_info_prt
};

enum hg_hnode_kind_t {
	hg_invalid_nod,
	hg_1_to_1_nod,
	hg_1_to_2_nod,
	hg_2_to_1_nod
};

enum hg_nk_lnk_mod_t {
	hg_invalid_ck_mod,
	hg_strict_ck_mod,
	hg_valid_self_ck_mod,
	hg_soft_ck_mod
};

enum gh_io_kind_t {
	gh_in_kind,
	gh_out_kind
};

typedef long hg_target_addr_t;
typedef long hg_addr_t;

class hnode;

typedef vector<hnode**> ppnode_vec_t;

class hgen_globals {
public:
	hg_nk_lnk_mod_t CK_LINK_MODE = hg_soft_ck_mod;
};

extern hgen_globals GH_GLOBALS;

class hnode {
public:
	hg_addr_t addr = 0;
	bool ready = false;
	
	hnode(){}
	virtual ~hnode(){}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
	
	virtual bool 	ck_connections(){ return false; }
	
	virtual hg_hnode_kind_t
	get_kind(){
		return hg_invalid_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return false;
	}
	
	virtual hnode* 	get_in0(){ return gh_null; }
	virtual hnode* 	get_in1(){ return gh_null; }
	virtual hnode* 	get_out0(){ return gh_null; }
	virtual hnode* 	get_out1(){ return gh_null; }

	virtual hnode** set_in0(hnode* nd){ return gh_null; }
	virtual hnode** set_in1(hnode* nd){ return gh_null; }
	virtual hnode** set_out0(hnode* nd){ return gh_null; }
	virtual hnode** set_out1(hnode* nd){ return gh_null; }
	
	virtual void set_direct_idx(gh_io_kind_t kk, ppnode_vec_t& all_io, long idx){}
	
	hnode** re_link_in(hnode* old_nd, hnode* nw_nd){
		if(get_in0() == old_nd){ return set_in0(nw_nd); }
		if(get_in1() == old_nd){ return set_in1(nw_nd); }
		GH_CK(false && "Bad_re_link_in");
		return gh_null;
	}
	
	hnode** re_link_out(hnode* old_nd, hnode* nw_nd){
		if(get_out0() == old_nd){ return set_out0(nw_nd); }
		if(get_out1() == old_nd){ return set_out1(nw_nd); }
		GH_CK(false && "Bad_re_link_out");
		return gh_null;
	}
	
	bool ck_link(hnode* lnk, gh_io_kind_t kk);

	void
	print_addr(FILE* ff);
};

class test_cls {
public:
	long val;
	
	test_cls(){}
	~test_cls(){
		fprintf(stdout, "DESTROING test_cls obj %ld\n", val);
	}
};

class hnode_1to1 : public hnode {
public:
	long val_out0 = 0;
	
	hnode* in0 = gh_null;
	hnode* out0 = gh_null;

	hnode_1to1(){
		val_out0 = 0;
	
		in0 = gh_null;
		out0 = gh_null;
	}
	virtual ~hnode_1to1(){}
	
	void init_to_me(){
		in0 = this;
		out0 = this;
	}

	virtual hnode* 	get_in0(){ return in0; }
	virtual hnode* 	get_out0(){ return out0; }

	virtual hnode** set_in0(hnode* nd){ in0 = nd; return &in0; }
	virtual hnode** set_out0(hnode* nd){ out0 = nd; return &out0; }
	
	virtual bool 	ck_connections(){ 
		bool c1 = ck_link(in0, gh_in_kind);
		bool c2 = ck_link(out0, gh_out_kind);
		return (c1 && c2);
	}
	
	virtual hg_hnode_kind_t
	get_kind(){
		return hg_1_to_1_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in0 == io) || (&out0 == io));
	}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);

};

class hnode_direct : public hnode_1to1 {
public:
	ppnode_vec_t* in_vec = gh_null;
	long in_idx = GH_INVALID_IDX;
	
	ppnode_vec_t* out_vec = gh_null;
	long out_idx = GH_INVALID_IDX;

	hnode_direct(){
		init_hnode_direct();
	}
	
	virtual ~hnode_direct(){
		init_hnode_direct();
	}
	
	void init_hnode_direct(){
		in_vec = gh_null;
		in_idx = GH_INVALID_IDX;
		
		out_vec = gh_null;
		out_idx = GH_INVALID_IDX;
	}
	
	virtual void 
	set_direct_idx(gh_io_kind_t kk, ppnode_vec_t& all_io, long idx){
		GH_CK(idx != GH_INVALID_IDX);
		if(kk == gh_out_kind){
			GH_CK(&out0 == all_io[idx]);
			out_vec = &all_io;
			out_idx = idx;
		} else {
			GH_CK(kk == gh_in_kind);
			GH_CK(&in0 == all_io[idx]);
			in_vec = &all_io;
			in_idx = idx;
		}
	}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
};

class hnode_target : public hnode_1to1 {
public:
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
};

class hnode_src : public hnode_1to1 {
public:
};

class hnode_snk : public hnode_1to1 {
public:
};

class hnode_1to2 : public hnode {
public:
	long val_out0 = 0;
	long val_out1 = 0;
	
	hnode* in0 = gh_null;
	hnode* out0 = gh_null;
	hnode* out1 = gh_null;

	hnode_1to2(){
		val_out0 = 0;
		val_out1 = 0;
	
		in0 = gh_null;
		out0 = gh_null;
		out1 = gh_null;
	}
	virtual ~hnode_1to2(){}
	
	void init_to_me(){
		in0 = this;
		out0 = this;
		out1 = this;
	}

	virtual hnode* 	get_in0(){ return in0; }
	virtual hnode* 	get_out0(){ return out0; }
	virtual hnode* 	get_out1(){ return out1; }
	
	virtual hnode** set_in0(hnode* nd){ in0 = nd; return &in0; }
	virtual hnode** set_out0(hnode* nd){ out0 = nd; return &out0; }
	virtual hnode** set_out1(hnode* nd){ out1 = nd; return &out1; }
	
	virtual bool 	ck_connections(){ 
		bool c1 = ck_link(in0, gh_in_kind);
		bool c2 = ck_link(out0, gh_out_kind);
		bool c3 = ck_link(out1, gh_out_kind);
		return (c1 && c2 && c3);
	}
	
	virtual hg_hnode_kind_t
	get_kind(){
		return hg_1_to_2_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in0 == io) || (&out0 == io) || (&out1 == io));
	}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
	
};

class hnode_2to1 : public hnode {
public:
	long val_out0 = 0;
	
	hnode* in0 = gh_null;
	hnode* in1 = gh_null;
	hnode* out0 = gh_null;

	hnode_2to1(){
		val_out0 = 0;
	
		in0 = gh_null;
		in1 = gh_null;
		out0 = gh_null;
	}
	virtual ~hnode_2to1(){}
	
	void init_to_me(){
		in0 = this;
		in1 = this;
		out0 = this;
	}
	
	virtual hnode* 	get_in0(){ return in0; }
	virtual hnode* 	get_in1(){ return in1; }
	virtual hnode* 	get_out0(){ return out0; }
	
	virtual hnode** set_in0(hnode* nd){ in0 = nd; return &in0; }
	virtual hnode** set_in1(hnode* nd){ in1 = nd; return &in1; }
	virtual hnode** set_out0(hnode* nd){ out0 = nd; return &out0; }
	
	virtual bool 	ck_connections(){ 
		bool c1 = ck_link(in0, gh_in_kind);
		bool c2 = ck_link(in1, gh_in_kind);
		bool c3 = ck_link(out0, gh_out_kind);
		return (c1 && c2 && c3);
	}
	
	virtual hg_hnode_kind_t
	get_kind(){
		return hg_2_to_1_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in0 == io) || (&in1 == io) || (&out0 == io));
	}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
	
};

long 	gh_get_first_null_idx(ppnode_vec_t& vec);
bool 	gh_is_free_io(hnode** io);

hnode* 	gh_set_io(ppnode_vec_t& all_io, long idx_io, hnode* nd){
	GH_CK(idx_io < (long)all_io.size());
	hnode** ppo = all_io[idx_io];
	GH_CK(gh_is_free_io(ppo));
	hnode* po = *ppo;
	*ppo = nd;
	return po;
}

void gh_connect_out_to_in(ppnode_vec_t& all_out, long out, ppnode_vec_t& all_in, long in);
void gh_connect_outputs_to_inputs(ppnode_vec_t& out, ppnode_vec_t& in);
bool gh_move_io(gh_io_kind_t kk, ppnode_vec_t& src, ppnode_vec_t& dst);
void gh_move_nodes(vector<hnode*>& src, vector<hnode*>& dst);
void gh_init_all_addr(vector<hnode*>& all_nd, long fst);

class hnode_box {
public:
	long base;
	
	vector<hnode*> all_direct;
	vector<hnode*> all_nodes;
	ppnode_vec_t inputs;
	ppnode_vec_t outputs;
	
	hnode_box(){
		base = 0;
	}
	
	virtual ~hnode_box(){
		release_nodes();
	}

	void 	clear_box(){
		// CAREFUL. Pointers are not released.
		all_direct.clear();
		all_nodes.clear();
		inputs.clear();
		outputs.clear();
	}
	
	void 	init_all_addr();
	void 	init_all_direct();
	void 	release_nodes();
	
	virtual
	void 	print_box(FILE* ff, hg_prt_mode_t md);
	
	hnode_1to2* add_1to2();
	hnode_2to1* add_2to1();
	hnode_direct* add_direct();
	
	hnode_box* get_2to1_net_box();
	
	bool move_nodes_to(hnode_box& bx);
	
	hnode* set_output(long out, hnode* nd){
		return gh_set_io(outputs, out, nd);
	}

	hnode* set_input(long in, hnode* nd){
		return gh_set_io(inputs, in, nd);
	}

	void connect_output_to_box_input(long out, long in, hnode_box& bx){
		gh_connect_out_to_in(outputs, out, bx.inputs, in);
	}
	
	void connect_output_to_node_input(long out, hnode_2to1& nd, long in){
		hnode* po = set_output(out, &nd);
		if(in == 0){
			GH_CK(nd.in0 == &nd);
			nd.in0 = po;
		} else {
			GH_CK(nd.in1 == &nd);
			nd.in1 = po;
		}
	}
	
	void connect_output_to_node(long out, hnode_1to2& nd){
		hnode* po = set_output(out, &nd);
		GH_CK(nd.in0 == &nd);
		nd.in0 = po;
	}
	
	void connect_node_output_to_input(hnode_1to2& nd, long out, long in){
		hnode* pi = set_input(in, &nd);
		if(out == 0){
			GH_CK(nd.out0 == &nd);
			nd.out0 = pi;
		} else {
			GH_CK(nd.out1 == &nd);
			nd.out1 = pi;
		}
	}
	
	void connect_node_to_input(hnode_2to1& nd, long in){
		hnode* pi = set_input(in, &nd);
		GH_CK(nd.out0 == &nd);
		nd.out0 = pi;
	}

	void remove_connected_directs();
	void connect_outputs_to_box_inputs(hnode_box& bx);
};

hnode_box*
gh_get_binnet_m_to_n(long num_in, long num_out);

class hroute_box : public hnode_box {
public:
	hroute_box(long bb){
		base = bb;
		GH_CK(base > 1);
	}
	virtual ~hroute_box(){
		release_nodes();
	}
	
	void 	init_route_box(long num_in, long num_out);
	
	void 	init_as_2to2_route_box();
	void 	init_as_3to2_route_box();
	void 	init_as_2to3_route_box();
	
};
	
void
gh_print_io(FILE* ff, hg_prt_mode_t md, ppnode_vec_t& all_io);

class htarget_box : public hnode_box {
public:
	hnode_target* target = gh_null;
	ppnode_vec_t lft_in;
	ppnode_vec_t lft_out;
	ppnode_vec_t rgt_in;
	ppnode_vec_t rgt_out;
	
	htarget_box(long bb){
		base = bb;
		target = gh_null;
		GH_CK(base > 1);
	}
	
	virtual ~htarget_box(){
		del_htarget_box();
	}
	
	void del_htarget_box();
	bool ck_target_box(long lft_ht, long rgt_ht);

	void 	join_outputs(hnode_box* rte_bx, hnode_box* spl_bx, long num_out, ppnode_vec_t& all_out);

	void 	init_basic_target_box(long lft_ht, long rgt_ht);
	void 	init_target_box(long lft_sz, long rgt_sz);

	virtual
	void 	print_box(FILE* ff, hg_prt_mode_t md);
};

void 	gh_calc_num_io(long base, long length, long idx, long& num_in, long& num_out);

class hlognet_box : public hnode_box {
public:
	long height;
	long length;
	vector<hnode_target*> all_targets;
	
	hlognet_box(long bb){
		base = bb;
		height = 0;
		length = 0;
		GH_CK(base > 1);
	}
	
	virtual ~hlognet_box(){
		release_nodes();
		release_targets();
	}
	void 	release_targets();
	
	void 	init_all_target_addr();

	void 	init_length(long num_elems);
	void 	init_lognet_box(long num_elems);
	void 	init_as_io();
	
	htarget_box* get_target_box(long idx);

	virtual
	void 	print_box(FILE* ff, hg_prt_mode_t md);
};
	
class hmultinode : public hnode {
public:
	vector<hnode*> inputs;
	vector<hnode*> outputs;
	
	long mark;
	//hnod_net*
	
	hmultinode(){}
	virtual ~hmultinode(){}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
	
	void reset_marks();
	bool is_binnet();
};

class hnod_net {
public:
	vector<hnode*> all_to_bigger;
	vector<hnode*> all_to_smaller;

	void
	init_nodes(long tot_nodes);
	
	bool
	link_nodes(long step);
	
	void
	print_nodes(FILE* ff, hg_prt_mode_t md);
};



#endif // GEN_HNET_H

