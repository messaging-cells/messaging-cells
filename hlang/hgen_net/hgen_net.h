

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
#define GH_INVALID_ADDR -1

#define GH_BASE_TWO 2

#define gh_min(v1, v2) (((v1) < (v2))?(v1):(v2))
#define gh_max(v1, v2) (((v1) > (v2))?(v1):(v2))

//======================================================================
// bitarray

// where 'a' is the byte stream pointer, and b is the bit number.

#define gh_div8(b)	((b)>>3)
#define gh_mod8(b)	((b)&7)

#define gh_get_bit(a, b)		((((int8_t*)a)[gh_div8(b)] >> gh_mod8(b)) & 1)
#define gh_set_bit(a, b)		(((int8_t*)a)[gh_div8(b)] |= (1 << gh_mod8(b)))
#define gh_reset_bit(a, b) 		(((int8_t*)a)[gh_div8(b)] &= ~(1 << gh_mod8(b)))
#define gh_toggle_bit(a, b) 	(((int8_t*)a)[gh_div8(b)] ^= (1 << gh_mod8(b)))

#define gh_to_bytes(num_bits)	(gh_div8(num_bits) + (gh_mod8(num_bits) > 0))
#define gh_to_bits(num_bytes)	(num_bytes * 8)

//======================================================================

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

enum gh_route_direction_t {
	gh_left_dir,
	gh_right_dir
};

typedef int hg_flag_idx_t;
typedef char hg_flags_t;
typedef long hg_target_addr_t;
typedef long hg_addr_t;

class hgen_globals;
class hnode;
class hlognet_box;
class hnode_1to1;
class hnode_direct;
class hnode_target;
class hnode_src;
class hnode_snk;
class hnode_1to2;
class hnode_2to1;
class hnode_box;
class hroute_box;
class htarget_box;
class hlognet_box;


typedef hnode* pnode_t;
typedef vector<hnode**> ppnode_vec_t;

class hgen_globals {
public:
	long DBG_LV = 0;
	hg_nk_lnk_mod_t CK_LINK_MODE = hg_soft_ck_mod;
};

extern hgen_globals GH_GLOBALS;

hg_addr_t
gh_recalc_range_val(hg_addr_t idx_ref, long base, hg_addr_t val){
	double pp = idx_ref + pow(base, val);
	return pp;
}

class haddr_frame {
public:
	haddr_frame* parent_frame = gh_null;
	long pow_base = 0;
	long idx = GH_INVALID_IDX;
	gh_route_direction_t dir = gh_right_dir;
};

class hrange {
public:
	hg_addr_t min = GH_INVALID_ADDR;
	hg_addr_t max = GH_INVALID_ADDR;
	
	bool ck_range(){
		GH_CK(0 <= min);
		GH_CK(min <= max);
		return true;
	}
	
	void recalc(hg_addr_t idx_ref, long base){
		min = gh_recalc_range_val(idx_ref, base, min);
		max = gh_recalc_range_val(idx_ref, base, max);
	}

	void print_range(FILE* ff);
	
};

class hmessage {
public:
	long val = 0;
	hg_addr_t src = GH_INVALID_ADDR;
	hg_addr_t dst = GH_INVALID_ADDR;
	hrange rng;
};

#define gh_is_red_bit 		1
#define gh_is_black_bit 	2
#define gh_to_range_bit 	3
#define gh_has_range_bit 	4

hg_flag_idx_t
gh_get_opp_color_bit(hg_flag_idx_t col){
	if(col == gh_is_red_bit){
		return gh_is_black_bit;
	}
	return gh_is_red_bit;
}

char
gh_get_col_chr(hg_flags_t flgs){
	char cc = 'x';
	if(gh_get_bit(&flgs, gh_is_red_bit)){
		GH_CK(! gh_get_bit(&flgs, gh_is_black_bit));
		return 'r';
	}
	if(gh_get_bit(&flgs, gh_is_black_bit)){
		GH_CK(! gh_get_bit(&flgs, gh_is_red_bit));
		return 'b';
	}
	return cc;
}

class hnode {
public:
	hg_flags_t node_flags = 0;
	hg_addr_t addr = GH_INVALID_ADDR;
	bool ready = false;
	
	hnode(){
		node_flags = 0;
		addr = GH_INVALID_ADDR;
		ready = false;
	}
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

	virtual hrange* get_range0(){ return gh_null; }
	virtual hrange* get_range1(){ return gh_null; }
	
	virtual void set_direct_idx(gh_io_kind_t kk, ppnode_vec_t& all_io, long idx){}
	
	hnode** re_link_in(hnode* old_nd, hnode* nw_nd){
		GH_CK(old_nd != this);
		GH_CK(get_in0() != get_in1());
		hnode** ppn = gh_null;
		if(get_in0() == old_nd){ ppn = set_in0(nw_nd); GH_CK(get_in0() == nw_nd); return ppn; }
		if(get_in1() == old_nd){ ppn = set_in1(nw_nd); GH_CK(get_in1() == nw_nd); return ppn; }
		GH_CK(false && "Bad_re_link_in");
		return gh_null;
	}
	
	hnode** re_link_out(hnode* old_nd, hnode* nw_nd){
		GH_CK(old_nd != this);
		GH_CK(get_out0() != get_out1());
		hnode** ppn = gh_null;
		if(get_out0() == old_nd){ ppn = set_out0(nw_nd); GH_CK(get_out0() == nw_nd); return ppn; }
		if(get_out1() == old_nd){ ppn = set_out1(nw_nd); GH_CK(get_out1() == nw_nd); return ppn; }
		GH_CK(false && "Bad_re_link_out");
		return gh_null;
	}

	void set_flag(hg_flag_idx_t num_flg){
		gh_set_bit(&node_flags, num_flg);
	}

	void reset_flag(hg_flag_idx_t num_flg){
		gh_reset_bit(&node_flags, num_flg);
	}

	bool get_flag(hg_flag_idx_t num_flg){
		return gh_get_bit(&node_flags, num_flg);
	}
	
	void set_color_as_in(hnode_box& bx);
	
	void	get_joined_range(hrange& rng);
	
	bool ck_link(hnode* lnk, gh_io_kind_t kk);
	
	bool has_connected_in0(){
		hnode* pi = get_in0();
		bool hc = ((pi != gh_null) && (pi != this));
		return hc;
	}

	bool has_connected_in1(){
		hnode* pi = get_in1();
		bool hc = ((pi != gh_null) && (pi != this));
		return hc;
	}
	
	void
	print_addr(FILE* ff);
};

class hnode_1to1 : public hnode {
public:
	hmessage msg0;
	
	hnode* in0 = gh_null;
	hnode* out0 = gh_null;

	hnode_1to1(){
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

	virtual hrange* get_range0(){ return &(msg0.rng); }
	
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
	hmessage msg0;
	hmessage msg1;
	
	hnode* in0 = gh_null;
	hnode* out0 = gh_null;
	hnode* out1 = gh_null;

	hnode_1to2(){
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
	
	virtual hrange* get_range0(){ return &(msg0.rng); }
	virtual hrange* get_range1(){ return &(msg1.rng); }
	
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
	hmessage msg0;
	
	hnode* in0 = gh_null;
	hnode* in1 = gh_null;
	hnode* out0 = gh_null;

	hnode_2to1(){
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
	
	virtual hrange* get_range0(){ return &(msg0.rng); }
	
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

void gh_connect_node_out_to_node_in(hnode& nd_out, long out, hnode& nd_in, long in);
void gh_connect_out_to_in(ppnode_vec_t& all_out, long out, ppnode_vec_t& all_in, long in);
void gh_connect_outputs_to_inputs(ppnode_vec_t& out, ppnode_vec_t& in);
bool gh_move_io(gh_io_kind_t kk, ppnode_vec_t& src, ppnode_vec_t& dst);
void gh_move_nodes(vector<hnode*>& src, vector<hnode*>& dst);
void gh_init_all_addr(vector<hnode*>& all_nd, long fst);
void gh_init_sm_to_bm_ranges(ppnode_vec_t& all_out, hg_flag_idx_t lst_lv_flg, hnode_box* dbg_bx);
//void gh_recalc_ranges(vector<hnode*>& all_nod, hg_addr_t idx_ref, long base);

class hnode_box {
public:
	hg_flags_t box_flags;
	haddr_frame* parent_frm;
	
	vector<hnode*> all_direct;
	vector<hnode*> all_nodes;
	ppnode_vec_t inputs;
	ppnode_vec_t outputs;
	
	hnode_box(){
		box_flags = 0;
		parent_frm = gh_null;
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
	
	void 	fill_with_directs(ppnode_vec_t& all_in, ppnode_vec_t& all_out);
	
	virtual
	void 	print_box(FILE* ff, hg_prt_mode_t md);
	
	hnode_1to2* add_1to2(bool ini_rngs = false);
	hnode_2to1* add_2to1();
	hnode_direct* add_direct();
	
	hnode_box* convert_net_from_1to2_to_2to1();
	
	void set_flag(hg_flag_idx_t num_flg){
		gh_set_bit(&box_flags, num_flg);
	}

	void reset_flag(hg_flag_idx_t num_flg){
		gh_reset_bit(&box_flags, num_flg);
	}

	bool get_flag(hg_flag_idx_t num_flg){
		return gh_get_bit(&box_flags, num_flg);
	}

	void start_color(){
		GH_CK(box_flags == 0);
		set_flag(gh_is_red_bit);
	}
	
	void switch_color(){
		if(get_flag(gh_is_red_bit)){
			GH_CK(! get_flag(gh_is_black_bit));
			reset_flag(gh_is_red_bit);
			set_flag(gh_is_black_bit);
		} else {
			GH_CK(get_flag(gh_is_black_bit));
			GH_CK(! get_flag(gh_is_red_bit));
			reset_flag(gh_is_black_bit);
			set_flag(gh_is_red_bit);
		}
	}

	hg_flag_idx_t get_last_color(){
		GH_CK(get_flag(gh_is_red_bit) != get_flag(gh_is_black_bit));
		if(get_flag(gh_is_red_bit)){
			return gh_is_red_bit;
		} 
		return gh_is_black_bit;
	}
	
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
	haddr_frame	frame;
	hroute_box(haddr_frame* pnt_frm){
		parent_frm = pnt_frm;
	}
	virtual ~hroute_box(){
		release_nodes();
	}
	
	void 	init_route_box(long num_in, long num_out);
	bool 	ck_route_box(long num_in, long num_out, int dbg_case);
	
	void 	init_as_2to2_route_box();
	void 	init_as_3to2_route_box();
	void 	init_as_2to3_route_box();
	
};
	
void
gh_print_io(FILE* ff, hg_prt_mode_t md, ppnode_vec_t& all_io);

class htarget_box : public hnode_box {
public:
	hg_addr_t	idx_ref;
	long tgt_base;
	
	hnode_target* target = gh_null;
	ppnode_vec_t lft_in;
	ppnode_vec_t lft_out;
	ppnode_vec_t rgt_in;
	ppnode_vec_t rgt_out;
	
	htarget_box(haddr_frame* pnt_frm, long bb){
		parent_frm = pnt_frm;
		idx_ref = GH_INVALID_IDX;
		tgt_base = bb;
		
		target = gh_null;
		GH_CK(tgt_base > 1);
	}
	
	virtual ~htarget_box(){
		del_htarget_box();
	}
	
	void 	del_htarget_box();

	void 	join_outputs(hnode_box* rte_bx, hnode_box* spl_bx, long num_out, ppnode_vec_t& all_out);
	void 	join_box_outputs(long fst_idx1, hnode_box* bx1, long fst_idx2, hnode_box* bx2, long num_idx, ppnode_vec_t& all_out);
	void 	resize_with_directs(long nw_side_sz);

	void 	init_basic_target_box(long lft_ht, long rgt_ht);
	void 	init_target_box(long lft_sz, long rgt_sz);
	bool 	ck_target_box(long lft_ht, long rgt_ht);
	
	void 	move_target_to(hlognet_box& bx);

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
	
	hlognet_box(haddr_frame* pnt_frm, long bb){
		parent_frm = pnt_frm;
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
	bool 	ck_lognet_box(long num_elems);
	
	void 	init_as_io();
	
	htarget_box* get_target_box(long idx);

	virtual
	void 	print_box(FILE* ff, hg_prt_mode_t md);
};
	

#endif // GEN_HNET_H

