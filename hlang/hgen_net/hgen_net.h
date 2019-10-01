

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

enum gh_dbg_call_t {
	gh_call_0,
	gh_call_1,
	gh_call_2,
	gh_call_3,
	gh_call_4,
	gh_call_5,
	gh_call_6,
	gh_call_7,
	gh_call_8,
	gh_call_9,
	gh_call_10,
	gh_call_11,
	gh_call_12,
	gh_call_13,
	gh_call_14
};

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

enum gh_1t1_kind_t {
	gh_invalid_1t1,
	gh_direct_1t1,
	gh_target_1t1,
	gh_source_1t1,
	gh_sink_1t1
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
	gh_lognet_frm,
	gh_top_lognet_frm,
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
typedef uint16_t gh_flags_t;
typedef long gh_target_addr_t;
typedef long gh_addr_t;

class thd_data;

class hgen_globals;
class haddr_frame;
class hnode;
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

//typedef hnode_target* (hnode_target::*gh_choose_tgt_simu_fn)();
//typedef void (*gh_init_simu_fn)();

class hgen_globals {
public:
	long DBG_LV = 0;
	gh_nk_lnk_mod_t CK_LINK_MODE = gh_soft_ck_mod;
	vector<haddr_frame*> all_frames;
	hnode_box* watch_bx = gh_null;
	haddr_frame* ref_frm = gh_null;

	long idx_test_simu = 0;
	
	vector<thd_data*> all_thread_data_simu;
	vector<hnode_target*>* all_tgt_simu = gh_null;
	long tot_tgt_simu = 0;
	long tot_src_msg_simu = 0;
	bool all_thread_inited_simu = false;
	gh_addr_t dbg_src_simu = GH_INVALID_ADDR;

	const char* dbg_LI_quarter = "LI";
	const char* dbg_LO_quarter = "LO";
	const char* dbg_RI_quarter = "RI";
	const char* dbg_RO_quarter = "RO";

	gh_addr_t dbg_curr_tgt_addr = GH_INVALID_ADDR;
	const char* dbg_curr_tgt_quarter = gh_null;
	
	hgen_globals(){}
	
	virtual ~hgen_globals(){
		release_all_frames();
	}
	
	void release_all_frames();
};

extern hgen_globals GH_GLOBALS;

#define GH_LI GH_GLOBALS.dbg_LI_quarter
#define GH_LO GH_GLOBALS.dbg_LO_quarter
#define GH_RI GH_GLOBALS.dbg_RI_quarter
#define GH_RO GH_GLOBALS.dbg_RO_quarter

#define GH_QRT(qq) ((GH_GLOBALS.dbg_curr_tgt_quarter != gh_null)?(GH_GLOBALS.dbg_curr_tgt_quarter):(qq))

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
	
	gh_addr_t recalc_addr(gh_addr_t vin, hnode* nd);
	
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
		case gh_top_lognet_frm:
			return "gh_top_lognet_frm";
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
		GH_CK_PRT((0 <= min), "%ld \n", min);
		GH_CK(min <= max);
		return true;
	}
	
	bool is_virgin(){
		bool v1 = (min == GH_INVALID_ADDR);
		bool v2 = (max == GH_INVALID_ADDR);
		return (v1 && v2);
	}
	
	void recalc(haddr_frame& frm, hnode* nd){
		if(get_flag(gh_skip_one_frame_bit)){
			reset_flag(gh_skip_one_frame_bit);
			return;
		}
		min = frm.recalc_addr(min, nd);
		max = frm.recalc_addr(max, gh_null);
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
	
	void calc_raddr(haddr_frame& nd_frm, haddr_frame& bx_frm, hnode* nd);
	
	bool in_range(gh_addr_t addr){
		//bool irng = (min <= addr) && (addr <= max);
		bool irng = (min <= addr) && (addr < max);
		return irng;
	}
	
	void print_range(FILE* ff);
	
};

class hmessage {
public:
	long mg_val = 0;
	gh_addr_t mg_src = GH_INVALID_ADDR;
	gh_addr_t mg_dst = GH_INVALID_ADDR;
	
	hrange rng;
	hrange bak_rg;
	
	void	calc_msg_raddr(haddr_frame& nd_frm, haddr_frame& bx_frm, hnode* nd){
		GH_CK(bak_rg.is_virgin());
		bak_rg = rng;
		rng.calc_raddr(nd_frm, bx_frm, nd);
	}
	
	bool in_range(gh_addr_t addr){
		return rng.in_range(addr);
	}
	
	void copy_mg_to(hmessage& mg, hnode* dbg_src_nod, hnode* dbg_dst_nod);
	
	void print_message(FILE* ff){
		fprintf(ff, "(%ld -> %ld) %ld", mg_src, mg_dst, mg_val);
		fflush(ff);
	}
	
};

#define gh_is_red_bit 		1
#define gh_is_black_bit 	2
#define gh_to_range_bit 	3
#define gh_has_range_bit 	4
#define gh_is_box_copy		5
#define gh_is_trichotomy	6
#define gh_is_dichotomy 	7
#define gh_is_inverted 		8

inline gh_flag_idx_t
gh_get_opp_color_bit(gh_flag_idx_t col){
	if(col == gh_is_red_bit){
		return gh_is_black_bit;
	}
	return gh_is_red_bit;
}

inline char
gh_get_col_chr(gh_flags_t flgs){
	char cc = '?';
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
	void* 	simu_data;
	gh_flags_t node_flags = 0;
	gh_addr_t addr = GH_INVALID_ADDR;
	
	gh_addr_t dbg_tgt_addr = GH_INVALID_ADDR;
	const char* dbg_tgt_quarter = gh_null;
	
	hnode(){
		simu_data = gh_null;
		node_flags = 0;
		addr = GH_INVALID_ADDR;
		
		dbg_tgt_addr = GH_GLOBALS.dbg_curr_tgt_addr;
		dbg_tgt_quarter = GH_GLOBALS.dbg_curr_tgt_quarter;
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

	virtual bool 	get_ack0(){ GH_CK("get_ack0" && false); return false; }
	virtual bool 	get_ack1(){ GH_CK("get_ack1" && false); return false; }
	virtual bool 	get_req0(){ GH_CK("get_req0" && false); return false; }
	virtual bool 	get_req1(){ GH_CK("get_req1" && false); return false; }
	
	virtual hnode* 	get_in0(){ return gh_null; }
	virtual hnode* 	get_in1(){ return gh_null; }
	virtual hnode* 	get_out0(){ return gh_null; }
	virtual hnode* 	get_out1(){ return gh_null; }

	virtual hnode** set_in0(hnode* nd){ return gh_null; }
	virtual hnode** set_in1(hnode* nd){ return gh_null; }
	virtual hnode** set_out0(hnode* nd){ return gh_null; }
	virtual hnode** set_out1(hnode* nd){ return gh_null; }

	virtual hmessage* get_message0(){ return gh_null; }
	virtual hmessage* get_message1(){ return gh_null; }

	virtual bool has_one_range(){ return false; }
	
	hrange* get_rng(hmessage* mg){
		if(mg != gh_null){
			return &(mg->rng);
		}
		return gh_null;
	}
	
	hrange* get_range0(){ return get_rng(get_message0()); }
	hrange* get_range1(){ return get_rng(get_message1()); }
	
	bool 	ireq(hnode& in_nd){
		if(in_nd.get_out0() == this){
			return in_nd.get_req0();
		}
		if(in_nd.get_out1() == this){
			return in_nd.get_req1();
		}
		GH_CK(false);
		return false;
	}
	
	bool 	oack(hnode& out_nd){
		if(out_nd.get_in0() == this){
			return out_nd.get_ack0();
		}
		if(out_nd.get_in1() == this){
			return out_nd.get_ack1();
		}
		GH_CK(false);
		return false;
	}
	
	virtual void set_direct_idx(gh_io_kind_t kk, ppnode_vec_t& all_io, long idx){}
	
	hmessage*	get_message_of(hnode* out){
		if(get_out0() == out){
			return get_message0();
		}
		if(get_out1() == out){
			return get_message1();
		}
		return gh_null;
	}
	
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
	
	bool can_invert(){
		bool is_dicho = get_flag(gh_is_dichotomy);
		bool is_tricho = get_flag(gh_is_trichotomy);
		return (is_dicho || is_tricho);
	}
	
	void flip_inverted_flag(){
		if(! can_invert()){
			return;
		}
		if(! get_flag(gh_is_inverted)){
			set_flag(gh_is_inverted);
		} else {
			reset_flag(gh_is_inverted);
		}
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
	
	void print_addr(FILE* ff);
	void print_dbg_tgt_addr(FILE* ff);
	
	void create_thread_simu(long idx);
};

class hnode_1to1 : public hnode {
public:
	hmessage msg0;
	
	bool ack0 = false;
	bool req0 = false;
	
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

	virtual bool 	get_ack0(){ return ack0; }
	virtual bool 	get_req0(){ return req0; }
	
	virtual hnode* 	get_in0(){ return in0; }
	virtual hnode* 	get_out0(){ return out0; }

	virtual hnode** set_in0(hnode* nd){ in0 = nd; return &in0; }
	virtual hnode** set_out0(hnode* nd){ out0 = nd; return &out0; }

	virtual hmessage* get_message0(){ return &(msg0); }
	
	virtual bool 	ck_connections(){ 
		bool c1 = ck_link(in0, gh_in_kind);
		bool c2 = ck_link(out0, gh_out_kind);
		return (c1 && c2);
	}
	
	virtual gh_hnode_kind_t
	get_kind(){
		return gh_1_to_1_nod;
	}
	
	virtual gh_1t1_kind_t
	get_1t1_kind(){
		return gh_invalid_1t1;
	}
	
	virtual bool
	has_io(hnode** io){
		return ((&in0 == io) || (&out0 == io));
	}
	
	virtual void
	print_node(FILE* ff, gh_prt_mode_t md);

	void run_1to1_simu();
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
	
	virtual gh_1t1_kind_t
	get_1t1_kind(){
		return gh_direct_1t1;
	}
	
	virtual void
	print_node(FILE* ff, gh_prt_mode_t md);
};

class hnode_target : public hnode_1to1 {
public:
	long bx_idx = GH_INVALID_IDX;
	
	bool is_source_simu = false;
	gh_addr_t curr_dest_simu = GH_INVALID_ADDR;

	long num_msg_snt_simu = 0;
	long num_msg_rcv_simu = 0;
	
	long dbg_lft_in_sz = 0;
	long dbg_lft_out_sz = 0;
	long dbg_rgt_in_sz = 0;
	long dbg_rgt_out_sz = 0;
	
	hnode_target* dbg_choose_target_simu();
	hnode_target* test0_choose_tgt_simu();
	hnode_target* test1_choose_tgt_simu();
	hnode_target* test2_choose_tgt_simu();
	hnode_target* test3_choose_tgt_simu();
	
	void run_target_simu();
	
	virtual gh_1t1_kind_t
	get_1t1_kind(){
		return gh_target_1t1;
	}
	
	virtual void
	print_node(FILE* ff, gh_prt_mode_t md);
};

class hnode_src : public hnode_1to1 {
public:
	virtual gh_1t1_kind_t
	get_1t1_kind(){
		return gh_source_1t1;
	}
	
};

class hnode_snk : public hnode_1to1 {
public:
	virtual gh_1t1_kind_t
	get_1t1_kind(){
		return gh_sink_1t1;
	}
	
};

class hnode_1to2 : public hnode {
public:
	gh_1to2_kind_t rou_kind = gh_invalid_rou;
	gh_dbg_call_t dbg_kind = gh_call_0;
	haddr_frame* node_frm = gh_null;
	
	hmessage* one_range = gh_null;
	
	hmessage msg0;
	hmessage msg1;

	bool ack0 = false;
	bool req0 = false;
	bool req1 = false;
	
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
		//if(msg0.rng.min > msg1.rng.max
		set_flag(gh_is_trichotomy);
		init_one_range0(0);
	}

	void init_one_range0(long val = GH_INVALID_ADDR){
		one_range = &(msg0);
		if(val != GH_INVALID_ADDR){
			//msg0.rng.min = val;
			//msg0.rng.max = val;
			init_simple_ranges(val, val);
		}
	}
	
	void init_one_range1(long val){
		one_range = &(msg1);
		//msg1.rng.min = val;
		//msg1.rng.max = val;
		init_simple_ranges(val, val);
	}
	
	void init_simple_ranges(long val0, long val1){
		GH_CK((val0 == val1) || ((val0 + 1) == val1));
		msg0.rng.min = val0;
		msg0.rng.max = val0 + 1;
		msg1.rng.min = val1;
		msg1.rng.max = val1 + 1;
	}
	
	void set_skip_one_frame(){
		msg0.rng.set_flag(gh_skip_one_frame_bit);
		msg1.rng.set_flag(gh_skip_one_frame_bit);
	}
	
	haddr_frame&	get_frame(){
		GH_CK(node_frm != gh_null);
		return (*node_frm);
	}
	
	void	calc_msgs_raddr(haddr_frame& frm);
	
	//void	calc_inverted();

	virtual bool 	get_ack0(){ return ack0; }
	virtual bool 	get_req0(){ return req0; }
	virtual bool 	get_req1(){ return req1; }
	
	virtual hnode* 	get_in0(){ return in0; }
	virtual hnode* 	get_out0(){ return out0; }
	virtual hnode* 	get_out1(){ return out1; }
	
	virtual hnode** set_in0(hnode* nd){ in0 = nd; return &in0; }
	virtual hnode** set_out0(hnode* nd){ out0 = nd; return &out0; }
	virtual hnode** set_out1(hnode* nd){ out1 = nd; return &out1; }
	
	virtual hmessage* get_message0(){ return &(msg0); }
	virtual hmessage* get_message1(){ return &(msg1); }
	
	virtual bool has_one_range(){ return (one_range != gh_null); }
	
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
	
	void run_1to2_simu();
	void run_one_range_simu();
	void run_trichotomy_simu();
	void run_dichotomy_simu();
};

class hnode_2to1 : public hnode {
public:
	hmessage msg0;
	
	bool choose0 = true;

	bool ack0 = false;
	bool ack1 = false;
	bool req0 = false;
	
	hnode* in0 = gh_null;
	hnode* in1 = gh_null;
	hnode* out0 = gh_null;

	hnode_2to1(){
		choose0 = true;
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
	
	virtual bool 	get_ack0(){ return ack0; }
	virtual bool 	get_ack1(){ return ack1; }
	virtual bool 	get_req0(){ return req0; }
	
	virtual hnode* 	get_in0(){ return in0; }
	virtual hnode* 	get_in1(){ return in1; }
	virtual hnode* 	get_out0(){ return out0; }
	
	virtual hnode** set_in0(hnode* nd){ in0 = nd; return &in0; }
	virtual hnode** set_in1(hnode* nd){ in1 = nd; return &in1; }
	virtual hnode** set_out0(hnode* nd){ out0 = nd; return &out0; }
	
	virtual hmessage* get_message0(){ return &(msg0); }
	
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
	
	void run_2to1_simu();
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
//void gh_init_sm_to_bm_ranges(ppnode_vec_t& all_out, gh_flag_idx_t lst_lv_flg, hnode_box* dbg_bx);

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
	
	hnode_1to2* add_1to2(haddr_frame& frm, gh_1to2_kind_t kk, 
						 const char* dbg_qrt = gh_null, gh_dbg_call_t dbg_case = gh_call_0);
	hnode_2to1* add_2to1(const char* dbg_qrt = gh_null);
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
	
	void init_sm_to_bm_ranges();
	void set_limit_one_ranges();
};

hnode_box*
gh_get_binnet_m_to_n(haddr_frame& pnt_frm, long num_in, long num_out, const char* dbg_qrt, gh_dbg_call_t dbg_case);

class hroute_box : public hnode_box {
public:
	hroute_box(haddr_frame& pnt_frm) : hnode_box(pnt_frm) {
		set_base(pnt_frm.pow_base);
		get_frame().kind = gh_route_frm;
	}
	
	virtual ~hroute_box(){
		release_nodes();
	}
	
	void 	init_route_box(long num_in, long num_out, const char* dbg_qrt);
	bool 	ck_route_box(long num_in, long num_out, int dbg_case);
	
	void 	init_as_2to2_route_box(const char* dbg_qrt);
	void 	init_as_3to2_route_box(const char* dbg_qrt);
	void 	init_as_2to3_route_box(const char* dbg_qrt);

	hnode_1to2*	get_1to2_node(long idx){
		GH_CK(idx < (long)all_nodes.size());
		hnode* nd = all_nodes[idx];
		GH_CK(nd->is_1to2());
		return (hnode_1to2*)nd;
	}
};
	
void
gh_print_io(FILE* ff, gh_prt_mode_t md, ppnode_vec_t& all_io);

void
gh_init_quarter(ppnode_vec_t qrt, gh_addr_t tg_addr, char* qrt_nm);

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
	void 	join_box_outputs(long fst_idx1, hnode_box* bx1, long fst_idx2, hnode_box* bx2, 
							 long num_idx, ppnode_vec_t& all_out, const char* dbg_qrt);
	void 	resize_with_directs(long nw_side_sz);

	void 	init_basic_target_box(long lft_ht, long rgt_ht);
	void 	init_target_box(long lft_sz, long rgt_sz);
	bool 	ck_target_box(long lft_ht, long rgt_ht);
	
	void 	move_target_to(hlognet_box& bx);
	
	void	dbg_init_tgt_szs();

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
		//get_frame().src_side = pnt_frm.src_side; // DBG_TEST1

		height = 0;
	}
	
	virtual ~hlognet_box(){
		release_nodes();
		release_targets();
	}
	void 	release_targets();
	
	void 	init_all_target_addr();

	void 	init_length(long num_elems);
	void 	init_lognet_box(long num_elems, const char* dbg_qrt = gh_null);
	bool 	ck_lognet_box(long num_elems);
	
	long 	length(){
		return get_frame().sz;
	}
	
	void 	init_as_io();
	
	htarget_box* get_target_box(long idx);

	virtual
	void 	print_box(FILE* ff, gh_prt_mode_t md);
	
	void 	wait_all_inited_simu();
	void 	wait_all_threads_ended_simu();
	void 	run_hlognet_simu();
};
	

void* run_node_simu(void* pm);

int test_get_target(int argc, char *argv[]);
int test_hlognet(int argc, char *argv[]);

#endif // GEN_HNET_H

