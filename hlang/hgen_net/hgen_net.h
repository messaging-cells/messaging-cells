

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
	hg_info_prt
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
	
	void
	print_addr(FILE* ff);
};

class hnode_src : public hnode {
public:
	long val_out1 = 0;
	
	hnode* out1 = gh_null;
};

class hnode_snk : public hnode {
public:
	long val_snk = 0;
	
	hnode* in1 = gh_null;
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

	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
	
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
	
	virtual void
	print_node(FILE* ff, hg_prt_mode_t md);
	
};


class hnode_box {
public:
	vector<hnode*> all_nodes;
	vector<hnode**> inputs;
	vector<hnode**> outputs;
	
	hnode_box(){}
	~hnode_box(){
		reset_nodes();
	}

	void 	init_all_addr();
	void 	reset_nodes();
	void 	print_box(FILE* ff);
	
	hnode_box* get_M_to_m();
	
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