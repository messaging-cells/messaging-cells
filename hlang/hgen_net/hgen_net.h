

#ifndef GEN_HNET_H
#define GEN_HNET_H


#include <limits.h>
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

enum gh_prt_mode_t {
	gh_addr_prt,
	gh_full_prt,
	gh_full_pt_prt,
	gh_info_prt
};

enum gh_hnode_kind_t {
	gh_invalid_nod,
	gh_1_to_1_nod,
	gh_1_to_2_nod,
	gh_2_to_1_nod
};

enum gh_nk_lnk_mod_t {
	gh_invalid_ck_mod,
	gh_strict_ck_mod,
	gh_valid_self_ck_mod,
	gh_soft_ck_mod
};

enum gh_io_kind_t {
	gh_in_kind,
	gh_out_kind
};

enum gh_route_side_t {
	gh_invalid_side,
	gh_left_side,
	gh_right_side
};

enum gh_frame_kind_t {
	gh_invalid_frm,
	gh_sm_to_bm_frm,
	gh_route_frm,
	gh_target_frm,
	gh_lognet_frm
};

enum gh_1to2_kind_t {
	gh_invalid_rou,
	gh_sm_to_bm_rou,
	gh_2to2_nd0_rou,
	gh_2to2_nd1_rou,
	gh_3to2_nd0_rou,
	gh_3to2_nd1_rou,
	gh_3to2_nd2_rou,
	gh_lgnet_in_rou,
	gh_tgt_out_rou,
	gh_bs_tgt_out_rou,
	gh_bs_tgt_lft_in_rou,
	gh_bs_tgt_rgt_in_rou,
	gh_bs_tgt_bx_in_rou
};

typedef int gh_flag_idx_t;
typedef char gh_flags_t;
typedef long gh_target_addr_t;
typedef long gh_addr_t;

class hgen_globals;
class haddr_frame;
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
	gh_nk_lnk_mod_t CK_LINK_MODE = gh_soft_ck_mod;
	vector<haddr_frame*> all_frames;
	hnode_box* watch_bx = gh_null;
	haddr_frame* ref_frm = gh_null;

	hgen_globals(){}
	virtual ~hgen_globals(){
		release_all_frames();
	}
	
	void release_all_frames();
};

extern hgen_globals GH_GLOBALS;

inline gh_route_side_t
gh_get_opp_side(gh_route_side_t rt_sd){
	switch(rt_sd){
		case gh_invalid_side: 
			return gh_invalid_side;
		case gh_left_side: 
			return gh_right_side;
		case gh_right_side: 
			return gh_left_side;
		default:
			break;
	}
	return gh_invalid_side;
}

class haddr_frame {
public:
	haddr_frame* parent_frame = gh_null;
	
	gh_frame_kind_t kind = gh_invalid_frm;
	long pow_base = 0;
	long idx = GH_INVALID_IDX;
	long sz = GH_INVALID_ADDR;
	gh_route_side_t src_side = gh_invalid_side;
	bool has_zero = false;
	
	hnode* dbg_nd = gh_null;

	bool ck_frame();
	
	gh_addr_t recalc_addr(gh_addr_t vin);
	
	void print_frame(FILE* ff, const char* msg = gh_null);
};

inline const char*
gh_dbg_get_side_str(gh_route_side_t dd){
	switch(dd){
		case gh_invalid_side: 
			return "gh_invalid_side";
		case gh_left_side: 
			return "lft";
		case gh_right_side: 
			return "rgt";
		default:
			break;
	}
	return "GH_INVALID_SIDE";
};

inline const char*
gh_dbg_get_frame_kind_str(gh_frame_kind_t kk){
	switch(kk){
		case gh_invalid_frm:
			return "gh_invalid_frm";
		case gh_sm_to_bm_frm:
			return "gh_sm_to_bm_frm";
		case gh_route_frm:
			return "gh_route_frm";
		case gh_target_frm:
			return "gh_target_frm";
		case gh_lognet_frm:
			return "gh_lognet_frm";
	}
	return "gh_INVALID_frm";
};

inline const char*
gh_dbg_get_rou_kind_str(gh_1to2_kind_t kk){
	switch(kk){
		case gh_invalid_rou:
			return "gh_invalid_rou";
		case gh_sm_to_bm_rou:
			return "sm_bm";
		case gh_2to2_nd0_rou:
			return "22_0";
		case gh_2to2_nd1_rou:
			return "22_1";
		case gh_3to2_nd0_rou:
			return "32_0";
		case gh_3to2_nd1_rou:
			return "32_1";
		case gh_3to2_nd2_rou:
			return "32_2";
		case gh_lgnet_in_rou:
			return "lgnet_in";
		case gh_tgt_out_rou:
			return "tgt_out";
		case gh_bs_tgt_out_rou:
			return "bt_out";
		case gh_bs_tgt_lft_in_rou:
			return "bt_lfi";
		case gh_bs_tgt_rgt_in_rou:
			return "bt_rgi";
		case gh_bs_tgt_bx_in_rou:
			return "bt_bxi";
		default:
			break;
	}
	return "GH_INVALID_ROU_KIND";
};

#define gh_skip_one_frame_bit 		1

class hrange {
public:
	gh_flags_t range_flags = 0;

	gh_addr_t min = GH_INVALID_ADDR;
	gh_addr_t max = GH_INVALID_ADDR;
	
	bool ck_range(){
		GH_CK(0 <= min);
		GH_CK(min <= max);
		return true;
	}
	
	void recalc(haddr_frame& frm){
		if(get_flag(gh_skip_one_frame_bit)){
			reset_flag(gh_skip_one_frame_bit);
			return;
		}
		min = frm.recalc_addr(min);
		max = frm.recalc_addr(max);
	}

	void set_flag(gh_flag_idx_t num_flg){
		gh_set_bit(&range_flags, num_flg);
	}

	void reset_flag(gh_flag_idx_t num_flg){
		gh_reset_bit(&range_flags, num_flg);
	}

	bool get_flag(gh_flag_idx_t num_flg){
		return gh_get_bit(&range_flags, num_flg);
	}
	
	void calc_raddr(haddr_frame& nd_frm, haddr_frame& bx_frm);
	
	void print_range(FILE* ff);
	
};

class hmessage {
public:
	long val = 0;
	gh_addr_t src = GH_INVALID_ADDR;
	gh_addr_t dst = GH_INVALID_ADDR;
	hrange rng;
	hrange addr;
	
	void	calc_msg_raddr(haddr_frame& nd_frm, haddr_frame& bx_frm){
		addr = rng;
		addr.calc_raddr(nd_frm, bx_frm);
	}
};

#define gh_is_red_bit 		1
#define gh_is_black_bit 	2
#define gh_to_range_bit 	3
#define gh_has_range_bit 	4
#define gh_is_box_copy		5
#define gh_is_trichotomy	6

inline gh_flag_idx_t
gh_get_opp_color_bit(gh_flag_idx_t col){
	if(col == gh_is_red_bit){
		return gh_is_black_bit;
	}
	return gh_is_red_bit;
}

inline char
gh_get_col_chr(gh_flags_t flgs){
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

inline bool gh_is_1to1(gh_hnode_kind_t kk){ return (kk == gh_1_to_1_nod); }
inline bool gh_is_1to2(gh_hnode_kind_t kk){ return (kk == gh_1_to_2_nod); }
inline bool gh_is_2to1(gh_hnode_kind_t kk){ return (kk == gh_2_to_1_nod); }

class hnode {
public:
	gh_flags_t node_flags = 0;
	gh_addr_t addr = GH_INVALID_ADDR;
	bool ready = false;
	
	hnode(){
		node_flags = 0;
		addr = GH_INVALID_ADDR;
		ready = false;
	}
	virtual ~hnode(){}
	
	virtual void
	print_node(FILE* ff, gh_prt_mode_t md);
	
	virtual bool 	ck_connections(){ return false; }
	
	virtual gh_hnode_kind_t
	get_kind(){
		return gh_invalid_nod;
	}
	
	bool is_1to1(){ return (get_kind() == gh_1_to_1_nod); }
	bool is_1to2(){ return (get_kind() == gh_1_to_2_nod); }
	bool is_2to1(){ return (get_kind() == gh_2_to_1_nod); }
	
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

	void set_flag(gh_flag_idx_t num_flg){
		gh_set_bit(&node_flags, num_flg);
	}

	void reset_flag(gh_flag_idx_t num_flg){
		gh_reset_bit(&node_flags, num_flg);
	}

	bool get_flag(gh_flag_idx_t num_flg){
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
	
	virtual gh_hnode_kind_t
	get_kind(){
		return gh_1_to_1_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in0 == io) || (&out0 == io));
	}
	
	virtual void
	print_node(FILE* ff, gh_prt_mode_t md);

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
	print_node(FILE* ff, gh_prt_mode_t md);
};

class hnode_target : public hnode_1to1 {
public:
	long bx_idx = GH_INVALID_IDX;
	
	virtual void
	print_node(FILE* ff, gh_prt_mode_t md);
};

class hnode_src : public hnode_1to1 {
public:
};

class hnode_snk : public hnode_1to1 {
public:
};

class hnode_1to2 : public hnode {
public:
	gh_1to2_kind_t rou_kind;
	haddr_frame* node_frm;
	
	hmessage* one_range = gh_null;
	
	hmessage msg0;
	hmessage msg1;
	
	hnode* in0 = gh_null;
	hnode* out0 = gh_null;
	hnode* out1 = gh_null;

	hnode_1to2(haddr_frame& frm){
		node_frm = &frm;
		
		one_range = gh_null;
		
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

	void init_as_target_out(){
		set_flag(gh_is_trichotomy);
		init_one_range0(0);
	}

	void init_one_range0(long val){
		one_range = &(msg0);
		msg0.rng.min = val;
		msg0.rng.max = val;
	}
	
	void init_one_range1(long val){
		one_range = &(msg1);
		msg1.rng.min = val;
		msg1.rng.max = val;
	}
	
	void init_simple_ranges(long rng0, long rng1){
		msg0.rng.min = rng0;
		msg0.rng.max = rng0;
		msg1.rng.min = rng1;
		msg1.rng.max = rng1;
	}
	
	void set_skip_one_frame(){
		msg0.rng.set_flag(gh_skip_one_frame_bit);
		msg1.rng.set_flag(gh_skip_one_frame_bit);
	}
	
	haddr_frame&	get_frame(){
		GH_CK(node_frm != gh_null);
		return (*node_frm);
	}
	
	void	calc_msgs_raddr(haddr_frame& frm){
		if(one_range == gh_null){
			msg0.calc_msg_raddr(get_frame(), frm);
			msg1.calc_msg_raddr(get_frame(), frm);
			return;
		}
		if(one_range == &msg0){
			msg0.calc_msg_raddr(get_frame(), frm);
			return;
		}
		GH_CK(one_range == &msg1);
		msg1.calc_msg_raddr(get_frame(), frm);
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
	
	virtual gh_hnode_kind_t
	get_kind(){
		return gh_1_to_2_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in0 == io) || (&out0 == io) || (&out1 == io));
	}
	
	virtual void
	print_node(FILE* ff, gh_prt_mode_t md);
	
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
	
	virtual gh_hnode_kind_t
	get_kind(){
		return gh_2_to_1_nod;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in0 == io) || (&in1 == io) || (&out0 == io));
	}
	
	virtual void
	print_node(FILE* ff, gh_prt_mode_t md);
	
};

long 	gh_get_first_null_idx(ppnode_vec_t& vec);
bool 	gh_is_free_io(hnode** io);

inline hnode* 	
gh_set_io(ppnode_vec_t& all_io, long idx_io, hnode* nd){
	GH_CK(idx_io < (long)all_io.size());
	hnode** ppo = all_io[idx_io];
	GH_CK(gh_is_free_io(ppo));
	hnode* po = *ppo;
	*ppo = nd;
	return po;
}

void gh_dbg_init_watch_box(hnode_box& w_bx, hnode_box* r_bx);
void gh_dbg_init_ref_box(hnode_box& r_bx);

void gh_connect_node_out_to_node_in(hnode& nd_out, long out, hnode& nd_in, long in);
void gh_connect_out_to_in(ppnode_vec_t& all_out, long out, ppnode_vec_t& all_in, long in);
void gh_connect_outputs_to_inputs(ppnode_vec_t& out, ppnode_vec_t& in);
bool gh_move_io(gh_io_kind_t kk, ppnode_vec_t& src, ppnode_vec_t& dst);
void gh_copy_nodes(vector<hnode*>& src, vector<hnode*>& dst, bool clr_src);
void gh_move_nodes(vector<hnode*>& src, vector<hnode*>& dst);
void gh_init_all_addr(vector<hnode*>& all_nd, long fst);
void gh_init_sm_to_bm_ranges(ppnode_vec_t& all_out, gh_flag_idx_t lst_lv_flg, hnode_box* dbg_bx);

class hnode_box {
public:
	gh_flags_t box_flags;
	haddr_frame* box_frm;
	
	vector<hnode*> all_direct;
	vector<hnode*> all_nodes;
	ppnode_vec_t inputs;
	ppnode_vec_t outputs;
	
	hnode_box(haddr_frame& pnt_frm){
		box_flags = 0;
		
		box_frm = new haddr_frame;
		GH_GLOBALS.all_frames.push_back(box_frm);
		box_frm->parent_frame = &pnt_frm;
	}
	
	hnode_box(hnode_box& orig, bool clr_orig){
		box_flags = orig.box_flags;
		set_flag(gh_is_box_copy);
		
		box_frm = orig.box_frm;
		gh_copy_nodes(orig.all_nodes, all_nodes, false);
	}
	
	virtual ~hnode_box(){
		if(! get_flag(gh_is_box_copy)){
			release_nodes();
		}
		clear_box();
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
	void 	print_box(FILE* ff, gh_prt_mode_t md);

	haddr_frame&	get_frame(){
		GH_CK(box_frm != gh_null);
		return (*box_frm);
	}
	
	void 	set_base(long bb){
		GH_CK(bb > 1);
		get_frame().pow_base = bb;
	}
	
	long	get_base(){
		GH_CK(get_frame().pow_base > 1);
		return get_frame().pow_base;
	}
	
	void 	set_index(long ii){
		GH_CK(ii >= 0);
		get_frame().idx = ii;
	}
	
	long 	get_index(){
		GH_CK(get_frame().idx >= 0);
		return get_frame().idx;
	}
	
	hnode_1to2* add_1to2(haddr_frame& frm, gh_1to2_kind_t kk);
	hnode_2to1* add_2to1();
	hnode_direct* add_direct();
	
	hnode_box* convert_net_from_1to2_to_2to1();
	
	void set_flag(gh_flag_idx_t num_flg){
		gh_set_bit(&box_flags, num_flg);
	}

	void reset_flag(gh_flag_idx_t num_flg){
		gh_reset_bit(&box_flags, num_flg);
	}

	bool get_flag(gh_flag_idx_t num_flg){
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

	gh_flag_idx_t get_last_color(){
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
	
	void calc_all_1to2_raddr(haddr_frame* frm = gh_null);
};

hnode_box*
gh_get_binnet_m_to_n(haddr_frame& pnt_frm, long num_in, long num_out);

class hroute_box : public hnode_box {
public:
	hroute_box(haddr_frame& pnt_frm) : hnode_box(pnt_frm) {
		set_base(pnt_frm.pow_base);
		get_frame().kind = gh_route_frm;
	}
	virtual ~hroute_box(){
		release_nodes();
	}
	
	void 	init_route_box(long num_in, long num_out);
	bool 	ck_route_box(long num_in, long num_out, int dbg_case);
	
	void 	init_as_2to2_route_box();
	void 	init_as_3to2_route_box();
	void 	init_as_2to3_route_box();

	hnode_1to2*	get_1to2_node(long idx){
		GH_CK(idx < (long)all_nodes.size());
		hnode* nd = all_nodes[idx];
		GH_CK(nd->is_1to2());
		return (hnode_1to2*)nd;
	}
};
	
void
gh_print_io(FILE* ff, gh_prt_mode_t md, ppnode_vec_t& all_io);

class htarget_box : public hnode_box {
public:
	hnode_target* target = gh_null;
	ppnode_vec_t lft_in;
	ppnode_vec_t lft_out;
	ppnode_vec_t rgt_in;
	ppnode_vec_t rgt_out;
	
	htarget_box(haddr_frame& pnt_frm) : hnode_box(pnt_frm) {
		set_base(pnt_frm.pow_base);
		get_frame().kind = gh_target_frm;
		
		target = gh_null;
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
	void 	print_box(FILE* ff, gh_prt_mode_t md);
};

void 	gh_dbg_calc_idx_and_sz(long num_in, long num_out, haddr_frame& frm);
void 	gh_calc_num_io(long base, long length, long idx, long& num_in, long& num_out);

class hlognet_box : public hnode_box {
public:
	long height;
	vector<hnode_target*> all_targets;
	
	hlognet_box(haddr_frame& pnt_frm) : hnode_box(pnt_frm) {
		set_base(pnt_frm.pow_base);
		get_frame().kind = gh_lognet_frm;

		height = 0;
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
	
	long 	length(){
		return get_frame().sz;
	}
	
	void 	init_as_io();
	
	htarget_box* get_target_box(long idx);

	virtual
	void 	print_box(FILE* ff, gh_prt_mode_t md);
};
	

int test_get_target(int argc, char *argv[]);

#endif // GEN_HNET_H

