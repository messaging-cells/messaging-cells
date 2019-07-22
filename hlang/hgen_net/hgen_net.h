

#ifndef GEN_HNET_H
#define GEN_HNET_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <vector>
#include <iterator>

using namespace std;

#define GH_MARK_USED(X)  ((void)(&(X)))
#define GH_CK(prm) assert(prm)

#define gh_null NULL

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

typedef long hg_target_addr_t;
typedef long hg_addr_t;

class hnode {
public:
	hg_addr_t addr = 0;
	bool ready = false;
	
	hnode(){}
	virtual ~hnode(){}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
	
	virtual hg_hnode_kind_t
	get_kind(){
		return hg_invalid_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return false;
	}
	
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
	long val_out1 = 0;
	
	hnode* in1 = gh_null;
	hnode* out1 = gh_null;

	hnode_1to1(){
		val_out1 = 0;
	
		in1 = gh_null;
		out1 = gh_null;
	}
	virtual ~hnode_1to1(){}
	
	void init_to_me(){
		in1 = this;
		out1 = this;
	}

	virtual hg_hnode_kind_t
	get_kind(){
		return hg_1_to_1_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in1 == io) || (&out1 == io));
	}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);

};

class hnode_direct : public hnode_1to1 {
public:
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
	long val_out1 = 0;
	long val_out2 = 0;
	
	hnode* in1 = gh_null;
	hnode* out1 = gh_null;
	hnode* out2 = gh_null;

	hnode_1to2(){
		val_out1 = 0;
		val_out2 = 0;
	
		in1 = gh_null;
		out1 = gh_null;
		out2 = gh_null;
	}
	virtual ~hnode_1to2(){}
	
	void init_to_me(){
		in1 = this;
		out1 = this;
		out2 = this;
	}

	virtual hg_hnode_kind_t
	get_kind(){
		return hg_1_to_2_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in1 == io) || (&out1 == io) || (&out2 == io));
	}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
	
};

class hnode_2to1 : public hnode {
public:
	long val_out1 = 0;
	
	hnode* in1 = gh_null;
	hnode* in2 = gh_null;
	hnode* out1 = gh_null;

	hnode_2to1(){
		val_out1 = 0;
	
		in1 = gh_null;
		in2 = gh_null;
		out1 = gh_null;
	}
	virtual ~hnode_2to1(){}
	
	void init_to_me(){
		in1 = this;
		in2 = this;
		out1 = this;
	}
	
	virtual hg_hnode_kind_t
	get_kind(){
		return hg_2_to_1_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in1 == io) || (&in2 == io) || (&out1 == io));
	}
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
	
};

long 	gh_get_first_null_idx(vector<hnode**>& vec);
bool 	gh_is_free_io(hnode** io);

hnode* 	gh_set_io(vector<hnode**> all_io, long idx_io, hnode* nd){
	GH_CK(idx_io < (long)all_io.size());
	hnode** ppo = all_io[idx_io];
	GH_CK(gh_is_free_io(ppo));
	hnode* po = *ppo;
	*ppo = nd;
	return po;
}

void gh_connect_out_to_in(vector<hnode**> all_out, long out, vector<hnode**> all_in, long in){
	GH_CK(in < (long)all_in.size());
	hnode** ppi = all_in[in];
	GH_CK(gh_is_free_io(ppi));
	hnode* pi = *ppi;
	hnode* po = gh_set_io(all_out, out, pi);
	*ppi = po;
}

void
gh_connect_outputs_to_inputs(vector<hnode**>& out, vector<hnode**>& in);

class hnode_box {
public:
	vector<hnode_direct*> all_direct;
	vector<hnode*> all_nodes;
	vector<hnode**> inputs;
	vector<hnode**> outputs;
	
	hnode_box(){}
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
	
	bool move_io_to(vector<hnode**>& in, vector<hnode**>& out);
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
			GH_CK(nd.in1 == &nd);
			nd.in1 = po;
		} else {
			GH_CK(nd.in2 == &nd);
			nd.in2 = po;
		}
	}
	
	void connect_output_to_node(long out, hnode_1to2& nd){
		hnode* po = set_output(out, &nd);
		GH_CK(nd.in1 == &nd);
		nd.in1 = po;
	}
	
	void connect_node_output_to_input(hnode_1to2& nd, long out, long in){
		hnode* pi = set_input(in, &nd);
		if(out == 0){
			GH_CK(nd.out1 == &nd);
			nd.out1 = pi;
		} else {
			GH_CK(nd.out2 == &nd);
			nd.out2 = pi;
		}
	}
	
	void connect_node_to_input(hnode_2to1& nd, long in){
		hnode* pi = set_input(in, &nd);
		GH_CK(nd.out1 == &nd);
		nd.out1 = pi;
	}

	void connect_outputs_to_box_inputs(hnode_box& bx){
		gh_connect_outputs_to_inputs(outputs, bx.inputs);
	}
};

hnode_box*
gh_get_binnet_m_to_n(long num_in, long num_out);

class hroute_box : public hnode_box {
public:
	long base;
	hroute_box(long bb){
		base = bb;
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
gh_print_io(FILE* ff, hg_prt_mode_t md, vector<hnode**>& all_io);

class htarget_box : public hnode_box {
public:
	long base;
	hnode_target* target = gh_null;
	vector<hnode**> lft_in;
	vector<hnode**> lft_out;
	vector<hnode**> rgt_in;
	vector<hnode**> rgt_out;
	
	htarget_box(long bb){
		base = bb;
		target = gh_null;
	}
	virtual ~htarget_box(){
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

	void 	join_outputs(hroute_box* rte_bx, hnode_box* spl_bx);

	void 	init_basic_target_box(long lft_ht, long rgt_ht);
	void 	init_target_box(long lft_sz, long rgt_sz);

	virtual
	void 	print_box(FILE* ff, hg_prt_mode_t md);
};

void 	gh_calc_num_io(long base, long length, long idx, long& num_in, long& num_out);

class hlognet_box : public hnode_box {
public:
	long base;
	long height;
	long length;
	vector<hnode_target*> all_targets;
	
	hlognet_box(long bb){
		base = bb;
		height = 0;
		length = 0;
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

