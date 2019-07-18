

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
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);

	bool is_active(){
		return ((in1 == this) && (out1 == this));
	}
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

class hnode_box {
public:
	vector<hnode_direct*> all_direct;
	vector<hnode*> all_nodes;
	vector<hnode**> inputs;
	vector<hnode**> outputs;
	
	hnode_box(){}
	~hnode_box(){
		reset_nodes();
	}
	
	void 	init_all_addr();
	void 	init_all_direct();
	void 	reset_nodes();
	void 	print_box(FILE* ff, hg_prt_mode_t md);
	
	hnode_1to2* add_1to2();
	hnode_2to1* add_2to1();
	hnode_direct* add_direct();
	
	hnode_box* get_2to1_net_box();
	
	void move_nodes_to(hnode_box& bx);
	
	hnode* set_output(long out, hnode* nd){
		GH_CK(out < (long)outputs.size());
		hnode** ppo = outputs[out];
		GH_CK(gh_is_free_io(ppo));
		hnode* po = *ppo;
		*ppo = nd;
		return po;
	}

	hnode* set_input(long in, hnode* nd){
		GH_CK(in < (long)inputs.size());
		hnode** ppi = inputs[in];
		GH_CK(gh_is_free_io(ppi));
		hnode* pi = *ppi;
		*ppi = nd;
		return pi;
	}

	void connect_output_to_box_input(long out, long in, hnode_box& bx){
		GH_CK(in < (long)bx.inputs.size());
		hnode** ppi = bx.inputs[in];
		GH_CK(gh_is_free_io(ppi));
		hnode* pi = *ppi;
		hnode* po = set_output(out, pi);
		*ppi = po;
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
};

class hnode_2_to_2_box : public hnode_box {
public:
	hnode_2_to_2_box(){
		init_box();
	}
	~hnode_2_to_2_box(){
	}

	void 	init_box();
};

class hnode_3_to_2_box : public hnode_box {
public:
	hnode_3_to_2_box(){
		init_box();
	}
	~hnode_3_to_2_box(){
	}

	void 	init_box();
};

class hnode_2_to_3_box : public hnode_box {
public:
	hnode_2_to_3_box(){
		init_box();
	}
	~hnode_2_to_3_box(){
	}

	void 	init_box();
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

