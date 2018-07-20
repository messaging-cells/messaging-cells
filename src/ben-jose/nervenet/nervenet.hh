

/*************************************************************

This file is part of ben-jose.

ben-jose is free software: you can redistribute it and/or modify
it under the terms of the version 3 of the GNU General Public 
License as published by the Free Software Foundation.

ben-jose is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ben-jose.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------------

Copyright (C) 2007-2012, 2014-2016. QUIROGA BELTRAN, Jose Luis.
Id (cedula): 79523732 de Bogota - Colombia.
See https://github.com/joseluisquiroga/ben-jose

ben-jose is free software thanks to The Glory of Our Lord 
	Yashua Melej Hamashiaj.
Our Resurrected and Living, both in Body and Spirit, 
	Prince of Peace.

------------------------------------------------------------

nervenet.hh

Declaration of nervenet class.

--------------------------------------------------------------*/

#ifndef NERVENET_H
#define NERVENET_H


#ifdef MC_IS_EMU_CODE
#include <stdio.h>
#include <string.h>

#include <sstream>
typedef std::ostringstream bj_dbg_str_stream;
#endif


#include "cell.hh"
#include "solver.hh"


class pre_cnf_node;
class pre_cnf_net;

class transmitter;
class sornet_transmitter;
class stabi_transmitter;
class sync_transmitter;
class synapse;
class nervenode;
class neurostate;
class neuron;
class polaron;
class sorcell;
class netstate;
class nervenet;

//define SYNC_LOG(...) EMU_LOG(__VA_ARGS__)
#define SYNC_LOG(...) 

//define SYNC_CODE(...) EMU_CODE(__VA_ARGS__)
#define SYNC_CODE(...) 

enum binval_t : uint8_t {
	binval_invalid = 0,
	binval_bottom = 11,
	binval_top = 22
};

enum net_side_t : uint8_t {
	side_invalid,
	side_left,
	side_right
};

enum tier_kind_t : uint8_t {
	tiki_invalid,
	tiki_propag,
	tiki_stabi
};

enum sync_tok_t : mck_token_t {
	bj_tok_sync_invalid = mck_tok_last + 1,
	bj_tok_sync_add_tier,
	bj_tok_sync_inert_child,
	bj_tok_sync_confl_up_neu,
	bj_tok_sync_confl_up_pol,
	bj_tok_sync_confl_down_neu,
	bj_tok_sync_confl_down_pol,
	bj_tok_sync_to_children,
	bj_tok_sync_end
};

enum load_tok_t : mck_token_t {
	bj_tok_load_invalid = bj_tok_sync_end + 1,
	bj_tok_load_nw_syn,
	bj_tok_load_no_lits,
	bj_tok_load_end
};

enum propag_tok_t : mck_token_t {
	bj_tok_propag_invalid = bj_tok_load_end + 1,
	bj_tok_propag_start,
	bj_tok_propag_ping,
	bj_tok_propag_charge_all,
	bj_tok_propag_charge_src,
	bj_tok_propag_tier_done,
	bj_tok_propag_end
};

enum mirrow_tok_t : mck_token_t {
	bj_tok_mirrow_invalid = bj_tok_propag_end + 1,
	bj_tok_mirrow_start,
	bj_tok_mirrow_end
};

enum stabi_tok_t : mck_token_t {
	bj_tok_stabi_invalid = bj_tok_mirrow_end + 1,
	bj_tok_stabi_start,
	bj_tok_stabi_ping,
	bj_tok_stabi_rank,
	bj_tok_stabi_tier_done,
	bj_tok_stabi_end
};

enum sornet_tok_t : mck_token_t {
	bj_tok_sornet_invalid = bj_tok_stabi_end + 1,
	bj_tok_sornet_start,
	bj_tok_sornet_out,
	bj_tok_sornet_bin,
	bj_tok_sornet_end
};

enum bj_hdlr_idx_t : uint8_t {
	idx_invalid,
	idx_synset,
	idx_tierset,
	idx_synapse,
	idx_neuron,
	idx_polaron,
	idx_sorcell,
	idx_tierdata,
	idx_nervenet,
	idx_total
};

struct mc_aligned callee_prms {
public:
	synapse* snp = mc_null;
	net_side_t sd = side_invalid;
	bool rec = false;
	void* aux = mc_null;
};

typedef void (nervenode::*bj_callee_t)(callee_prms& pms);
typedef int (*bj_cmp_obj_func_t)(void* obj1, void* obj2);

void emu_prt_tok_codes() mc_external_code_ram;

char* net_side_to_str(net_side_t sd) mc_external_code_ram;
char* node_kind_to_str(node_kind_t ki) mc_external_code_ram;

mc_inline_fn bool is_sync_tok(mck_token_t tok){
	return ((bj_tok_sync_invalid <= tok) && (tok <= bj_tok_sync_end));
}

mc_inline_fn bool is_load_tok(mck_token_t tok){
	return ((bj_tok_load_invalid <= tok) && (tok <= bj_tok_load_end));
}

mc_inline_fn bool is_propag_tok(mck_token_t tok){
	return ((bj_tok_propag_invalid <= tok) && (tok <= bj_tok_propag_end));
}

mc_inline_fn bool is_stabi_tok(mck_token_t tok){
	return ((bj_tok_stabi_invalid <= tok) && (tok <= bj_tok_stabi_end));
}


char* sync_tok_to_str(sync_tok_t tok) mc_external_code_ram;
char* load_tok_to_str(load_tok_t tok) mc_external_code_ram;
char* propag_tok_to_str(propag_tok_t tok) mc_external_code_ram;
char* stabi_tok_to_str(stabi_tok_t tok) mc_external_code_ram;

void dbg_call_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd, bool from_rec) mc_external_code_ram;

void with_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd, 
		bool from_rec = false, bool dbg_mates = false, void* aux = mc_null);

//net_side_t opp_side_of(net_side_t sd) bj_propag_cod;

#define BJ_IS_CLS(obj, cnam) (((obj) != mc_null)?((obj)->get_class_name() == cnam##_cls_nam):(false))

#define BJ_DECLARE_CLS_NAM(cnam) \
extern char cnam##_cls_nam[] mc_external_data_ram; \
bool bj_ck_is_##cnam(agent* pt_obj) mc_external_code_ram; \

// end_of_macro

#define BJ_DEFINE_GET_CLS_NAM(cnam) \
char cnam##_cls_nam[] = "{" #cnam "}"; \
char* cnam::get_class_name(){ return cnam##_cls_nam; } \
bool bj_ck_is_##cnam(agent* obj){ \
	return BJ_IS_CLS(obj, cnam); \
} \

// end_of_macro

//	return (((obj) != mc_null)?((obj)->get_class_name() == cnam##_cls_nam):(false)); 
//	if(pt_obj != mc_null){ return (pt_obj->get_class_name() == cnam##_cls_nam); } 
//	return false; 


struct mc_aligned signal_data {
public:
	missive* msv = mc_null;
	synapse* snp = mc_null;
	mck_token_t tok = mck_tok_invalid;
	net_side_t sd = side_invalid;
	num_tier_t ti = BJ_INVALID_NUM_TIER;
	num_syn_t	id_arr_sz = 0;
	num_syn_t*  id_arr = mc_null;
};


BJ_DECLARE_CLS_NAM(synset)
BJ_DECLARE_CLS_NAM(tierset)
BJ_DECLARE_CLS_NAM(transmitter)
BJ_DECLARE_CLS_NAM(sornet_transmitter)
BJ_DECLARE_CLS_NAM(stabi_transmitter)
BJ_DECLARE_CLS_NAM(sync_transmitter)
BJ_DECLARE_CLS_NAM(synapse)
BJ_DECLARE_CLS_NAM(nervenode)
BJ_DECLARE_CLS_NAM(neuron)
BJ_DECLARE_CLS_NAM(polaron)
BJ_DECLARE_CLS_NAM(sorcell)
BJ_DECLARE_CLS_NAM(tierdata)
BJ_DECLARE_CLS_NAM(nervenet)

#define	bj_ss_ranked_snps_flag mc_flag1

int
bj_cmp_num_syn(num_syn_t const & n1, num_syn_t const & n2);

class mc_aligned synset : public agent {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(synset, bj_nervenet_mem)

	EMU_DBG_CODE(mc_flags_t		ss_flags);

	num_syn_t 	num_ss_recv;
	num_syn_t 	num_ss_ping;

	num_syn_t 	tot_syn;
	grip		all_syn;
	grip		all_grp;

	synset() mc_external_code_ram;
	~synset() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void add_left_synapse(synapse* snp, bool set_vessel = true);
	void add_right_synapse(synapse* snp, bool set_vessel = true);

	void propag_handler(missive* msv) bj_propag_cod;

	void stabi_calc_arr_rec(num_syn_t cap, num_syn_t* arr, num_syn_t& ii) bj_stabi_cod;
	void stabi_rank_all_snp(signal_data* dat, nervenode* dbg_nd) bj_stabi_cod;
	synset* stabi_get_subset_of(synapse* my_snp, signal_data* dat) bj_stabi_cod;

	void dbg_rec_call_all(bj_callee_t mth, net_side_t sd) mc_external_code_ram;

	void transmitter_send_all_rec(bj_callee_t mth, net_side_t sd);

	void reset_vessels(bool set_vessel);
	void reset_rec_tree();

	void stabi_insert_sort() bj_stabi_cod;

	bool is_synset_empty() bj_propag_cod;

	synapse* get_first_snp(net_side_t sd);

	EMU_DBG_CODE(void dbg_rec_prt_synset(net_side_t sd, bj_dbg_str_stream& out) mc_external_code_ram);

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned tierset : public agent {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(tierset, bj_nervenet_mem)

	num_tier_t 	ti_id;
	grip		ti_all;	//!< \ref synapse s in this tier

	tierset() mc_external_code_ram;
	~tierset() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void mirrow_tiset(tierset& tis, net_side_t src_sd) bj_stabi_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned transmitter : public missive {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(transmitter, bj_nervenet_mem)

	net_side_t wrk_side;
	num_tier_t wrk_tier;

	transmitter() mc_external_code_ram;
	~transmitter() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	/*EMU_DBG_CODE(
		virtual mc_opt_sz_fn 
		void	dbg_release(int dbg_caller) mc_external_code_ram;
	);*/

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned sornet_transmitter : public transmitter {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(sornet_transmitter, bj_sornet_cod)

	num_nod_t	idx;
	void*		obj;

	sornet_transmitter() mc_external_code_ram;
	~sornet_transmitter() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) bj_sornet_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned stabi_transmitter : public transmitter {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(stabi_transmitter, bj_nervenet_mem)

	num_syn_t	id_arr_sz;
	num_syn_t*  id_arr;

	stabi_transmitter() mc_external_code_ram;
	~stabi_transmitter() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

#define bj_id_arr_copy(dst, sz, src) for(num_syn_t idx = 0; idx < sz; idx++){ dst[idx] = src[idx]; }

class mc_aligned sync_transmitter : public transmitter {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(sync_transmitter, bj_nervenet_mem)

	nervenode* 	 cfl_src;

	sync_transmitter() mc_external_code_ram;
	~sync_transmitter() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned synapse : public cell {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(synapse, mc_external_code_ram)

	synset*		stabi_vessel;
	num_syn_t	stabi_rcv_arr_sz;
	num_syn_t*  stabi_rcv_arr;

	binder		right_handle;

	nervenode*	owner;
	synapse*	mate;

	synapse() mc_external_code_ram;
	~synapse() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void load_handler(missive* msv) bj_load_cod;
	void propag_handler(missive* msv) bj_propag_cod;
	void stabi_handler(missive* msv) bj_stabi_cod;

	void propag_send_transmitter(propag_tok_t tok, net_side_t sd, bool dbg_is_forced = false) bj_propag_cod;
	void stabi_send_transmitter(stabi_tok_t tok, neurostate* src_nd = mc_null, 
				bool dbg_is_forced = false) bj_stabi_cod;

	void stabi_set_rcv_arr(signal_data* dat) bj_stabi_cod;

	mc_inline_fn binder& get_side_binder(net_side_t sd) bj_propag_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

synapse* get_synapse_from_binder(net_side_t sd, binder* bdr);

#define bj_get_syn_of_rgt_handle(bdr) ((synapse*)(((uint8_t*)bdr) - mc_offsetof(&synapse::right_handle)))

#define	bj_stt_charge_all_flag mc_flag1
#define	bj_stt_stabi_intact_id_flag mc_flag2

//class neurostate {
class mc_aligned neurostate : public binder {
public:
	mc_flags_t		step_flags;
	synset			step_active_set;
	num_syn_t 		step_prev_tot_active;
	num_syn_t		step_num_complete;
	num_syn_t		step_num_ping;

	num_tier_t		propag_num_tier;
	synapse*		propag_source;
	grip			propag_tiers;

	num_tier_t		stabi_num_tier;
	num_syn_t		stabi_arr_cap;
	num_syn_t		stabi_arr_sz;
	num_syn_t*  	stabi_arr;

	EMU_DBG_CODE(bool was_all_pg);

	neurostate() mc_external_code_ram;
	~neurostate() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void calc_stabi_arr(nervenode* dbg_nd, signal_data* dbg_dat) bj_stabi_cod;
	bool charge_all_active(signal_data* dat, node_kind_t ki) bj_propag_cod;
	void step_reset_complete();

	tierset*	dbg_get_tiset(grip& all_ti, num_tier_t nti) mc_external_code_ram;

	tierset*	get_tiset(num_tier_t nti = BJ_INVALID_NUM_TIER) bj_propag_cod;
	tierset&	add_tiset(num_tier_t nti) bj_propag_cod;

	mc_inline_fn void update_prv_tot_active() bj_load_cod;

	bool is_mono(num_tier_t nti) bj_propag_cod;

	mc_inline_fn bool neu_all_ping(tier_kind_t tiki){
		num_syn_t lim = 0;
		if(tiki == tiki_propag){ lim = 1; }
		bool all_pg = ((step_prev_tot_active > lim) && (step_num_ping == step_prev_tot_active));
		EMU_CK(! all_pg || (step_active_set.tot_syn > 0));
		return all_pg;
	}

	void send_all_propag(nervenode* nd, signal_data* dat) bj_propag_cod;

	mc_inline_fn bool is_full(){
		return (step_num_complete == step_prev_tot_active);
	}

	void propag_send_all_ti_done(nervenode* nd, net_side_t sd, num_tier_t dat_ti) bj_propag_cod;
	void stabi_send_all_ti_done(nervenode* nd, num_tier_t dbg_ti) bj_stabi_cod;

	bool neu_is_to_delay(netstate& nstt, nervenode* nd, tier_kind_t tiki, num_tier_t the_ti, 
			grip& all_ti, int dbg_caller);

};


void bj_stabi_reset_all_tiers(grip& dst_grp, grip& src_grp) bj_stabi_cod;
int bj_cmp_stabi_id_arrs(num_syn_t sz1, num_syn_t* arr1, num_syn_t sz2, num_syn_t* arr2) bj_stabi_cod;
int bj_cmp_synapses(synapse* snp1, synapse* snp2, signal_data* dat) bj_stabi_cod;

typedef int (*bj_cmp_func_t)(binder* obj1, binder* obj2);

bool bj_is_sorted(grip& grp, bj_cmp_func_t fn, int ord) mc_external_code_ram;

int bj_dbg_cmp_synset_by_arr_id(binder* obj1, binder* obj2) mc_external_code_ram;
int bj_dbg_cmp_synset_by_tot_syn(binder* obj1, binder* obj2) mc_external_code_ram;

char* bj_dbg_stabi_id_arr_to_str(num_syn_t sz1, num_syn_t* arr1, int sz_str, char* str) mc_external_code_ram;

class mc_aligned nervenode : public cell {
public:
	node_kind_t 	ki;
	long			id;
	num_syn_t		sz;
	num_tier_t		creat_tier;

	neurostate		left_side;
	neurostate		right_side;

	nervenode() mc_external_code_ram;
	~nervenode() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void init_nervenode_with(pre_cnf_node* nod) bj_load_cod;

	neurostate& get_neurostate(net_side_t sd);	// Used in loading. It has to common code.

	char* get_ki_str() mc_external_code_ram;

	// PROPAG

	void propag_recv_transmitter(signal_data* dat) bj_propag_cod;
	void propag_recv_charge_all(signal_data* dat) bj_propag_cod;
	void propag_recv_charge_src(signal_data* dat) bj_propag_cod;
	void propag_recv_ping(signal_data* dat) bj_propag_cod;
	void propag_recv_tier_done(signal_data* dat) bj_propag_cod;

	virtual 
	void propag_send_snp_propag(callee_prms& pms) bj_propag_cod;

	void propag_send_snp_charge_src(callee_prms& pms) bj_propag_cod;
	void propag_send_snp_tier_done(callee_prms& pms) bj_propag_cod;

	void send_confl_tok(signal_data* dat, sync_tok_t the_tok) mc_external_code_ram;

	virtual 
	bool is_tier_complete(signal_data* dat);

	virtual 
	void recalc_stabi(signal_data* dat) bj_stabi_cod;

	virtual 
	void propag_start_nxt_tier(signal_data* dat) bj_propag_cod;

	void dbg_prt_syn(callee_prms& pms) mc_external_code_ram;

	void dbg_prt_nod(net_side_t sd, tier_kind_t tiki, char* prefix, num_pulse_t num_pul, 
			num_tier_t num_ti) mc_external_code_ram;

	// STABI

	void mirrow_sides(net_side_t sd) bj_stabi_cod;
	void stabi_recv_transmitter(signal_data* dat) bj_stabi_cod;
	void stabi_recv_rank(signal_data* dat) bj_stabi_cod;
	void stabi_recv_ping(signal_data* dat) bj_stabi_cod;
	void stabi_recv_tier_done(signal_data* dat) bj_stabi_cod;

	void stabi_send_snp_id_arr(callee_prms& pms) bj_stabi_cod;
	void stabi_send_snp_tier_done(callee_prms& pms) bj_stabi_cod;

	virtual 
	void dbg_prt_tier_done(signal_data* dat) mc_external_code_ram;

	virtual 
	void stabi_start_nxt_tier(signal_data* dat) bj_stabi_cod;

	void dbg_prt_active_synset(net_side_t sd, tier_kind_t tiki, char* prefix, 
				num_tier_t num_ti) mc_external_code_ram;

	EMU_DBG_CODE(void dbg_prt_snp_id(callee_prms& pms) mc_external_code_ram);

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

#define bj_get_nod_of_pt_lft_st(bdr) ((nervenode*)(((uint8_t*)bdr) - mc_offsetof(&nervenode::left_side)))
#define bj_get_nod_of_pt_rgt_st(bdr) ((nervenode*)(((uint8_t*)bdr) - mc_offsetof(&nervenode::right_side)))

class mc_aligned neuron : public nervenode {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(neuron, mc_external_code_ram)

	//EMU_CODE(int pru_attr);
	
	neuron() mc_external_code_ram;
	~neuron() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void propag_handler(missive* msv) bj_propag_cod;
	void stabi_handler(missive* msv) bj_stabi_cod;

	void propag_neuron_start() bj_propag_cod;
	void stabi_neuron_start() bj_stabi_cod;

	virtual 
	void propag_start_nxt_tier(signal_data* dat) bj_propag_cod;

	virtual 
	void propag_send_snp_propag(callee_prms& pms) bj_propag_cod;

	void pru_callee(callee_prms& pms) mc_external_code_ram;

	virtual 
	void stabi_start_nxt_tier(signal_data* dat) bj_stabi_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned polaron : public nervenode {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(polaron, mc_external_code_ram)
	
	polaron*		opp;

	polaron() mc_external_code_ram;
	~polaron() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) mc_external_code_ram;

	void load_handler(missive* msv) bj_load_cod;

	void propag_send_snp_charge_all(callee_prms& pms) bj_propag_cod;

	void charge_all_confl_and_start_nxt_ti(signal_data* dat) mc_external_code_ram;
	void charge_all_and_start_nxt_ti(signal_data* dat) bj_propag_cod;

	virtual 
	bool is_tier_complete(signal_data* dat);

	virtual 
	void recalc_stabi(signal_data* dat) bj_stabi_cod;

	virtual 
	void propag_start_nxt_tier(signal_data* dat) bj_propag_cod;

	virtual 
	void dbg_prt_tier_done(signal_data* dat) mc_external_code_ram;

	virtual 
	void stabi_start_nxt_tier(signal_data* dat) bj_stabi_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned sorcell : public cell {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(sorcell, mc_external_code_ram)

	num_nod_t 	color;

	num_nod_t 	up_idx;
	void*		up_inp;
	sorcell*	up_out;

	num_nod_t 	down_idx;
	void*		down_inp;
	sorcell*	down_out;

	sorcell() mc_external_code_ram;
	~sorcell() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) mc_external_code_ram;

	void sornet_handler(missive* msv) bj_sornet_cod;
	bj_cmp_obj_func_t sornet_get_cmp_func(sornet_tok_t tmt_tok) bj_sornet_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

void bj_send_sornet_tmt(cell* src, sornet_tok_t tok, void* obj, sorcell* dst, num_nod_t idx) bj_sornet_cod;

#define	bj_sent_inert_flag mc_flag0

class mc_aligned tierdata : public agent {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(tierdata, bj_nervenet_mem)

	num_tier_t	tdt_id;
	mc_flags_t	tdt_flags;

	binder	all_delayed;

	mc_core_nn_t num_inert_chdn;

	num_nod_t inp_neus;
	num_nod_t off_neus;
	num_nod_t rcv_neus;
	num_nod_t stl_neus;
	num_nod_t dly_neus;

	tierdata() mc_external_code_ram;
	~tierdata() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void add_all_inp_from(grip& grp, net_side_t sd) mc_external_code_ram;

	mc_inline_fn void inc_rcv(){ rcv_neus++; }
	mc_inline_fn void inc_off(){ off_neus++; }

	void update_tidat();

	mc_inline_fn bool is_tidat_empty(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == 0));
	}

	mc_inline_fn bool got_all_neus(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == rcv_neus));
	}

	mc_inline_fn bool is_inert(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && ((inp_neus - off_neus) == dly_neus));
	}

	/*
	mc_inline_fn bool got_all_neus(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == (rcv_neus + stl_neus)));
	}

	mc_inline_fn bool is_inert(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == stl_neus));
	}
	*/

	mc_inline_fn tierdata& prv_tier(){
		return *((tierdata*)bn_left);
	}

	mc_inline_fn bool is_first_tier(grip& all_tiers){
		return (bn_left == &all_tiers);
	}

	void proc_delayed(tier_kind_t tiki, grip& all_ti, net_side_t sd, bool star_nxt_ti);

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned netstate {
public:
	net_side_t my_side;

	bool		sync_is_inactive;
	num_tier_t	sync_wait_tier;
	bool 		sync_is_ending;

	grip 		all_propag_tiers;
	grip 		all_stabi_tiers;

	sync_tok_t  tok_confl;
	nervenode*	nod_confl;
	num_tier_t	ti_confl;

	netstate() mc_external_code_ram;
	~netstate() mc_external_code_ram;

	void broadcast_tier(tier_kind_t tiki, tierdata& lti, int dbg_caller);

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) mc_external_code_ram;

	void init_sync() mc_external_code_ram;

	void init_propag_tiers(nervenet& nnt) mc_external_code_ram;
	void init_stabi_tiers(nervenet& nnt) mc_external_code_ram;

	void send_sync_transmitter(tier_kind_t tiki, nervenet* the_dst, sync_tok_t the_tok, num_tier_t the_ti,
			nervenode* cfl_src = mc_null);

	void send_sync_to_children(sync_tok_t the_tok, num_tier_t the_ti, tier_kind_t tiki, nervenode* cfl_src); 

	void send_up_confl_tok(sync_tok_t the_tok, num_tier_t the_ti, nervenode* the_cfl) mc_external_code_ram;

	void propag_handle_my_sync() bj_propag_cod;
	void stabi_handle_my_sync() bj_stabi_cod;

	void update_sync_inert(tier_kind_t tiki, bool remove_full = false);

	grip& get_all_tiers(tier_kind_t tiki);

	tierdata& get_tier(tier_kind_t tiki, grip& all_ti, num_tier_t nti, int dbg_caller);

	void dbg_prt_all_tiers(tier_kind_t tiki, char* prefix, num_tier_t num_ti) mc_external_code_ram;

};

void inc_tier(tier_kind_t tiki, grip& all_ti, net_side_t sd, int dbg_caller);

mc_inline_fn tierdata& get_last_tier(grip& all_ti){
	EMU_CK(! all_ti.is_alone());
	return *((tierdata*)(all_ti.bn_left));
}

mc_inline_fn bool is_last_tier(grip& all_ti, tierdata& tdt){
	EMU_CK(! all_ti.is_alone());
	return (((tierdata*)(all_ti.bn_left)) == (&tdt));
}


class mc_aligned dbg_stats {
public:
	mc_alloc_size_t dbg_tot_new_synset;
	mc_alloc_size_t dbg_tot_new_tierset;
	mc_alloc_size_t dbg_tot_new_transmitter;
	mc_alloc_size_t dbg_tot_new_sornet_transmitter;
	mc_alloc_size_t dbg_tot_new_stabi_transmitter;
	mc_alloc_size_t dbg_tot_new_sync_transmitter;
	mc_alloc_size_t dbg_tot_new_synapse;
	mc_alloc_size_t dbg_tot_new_neurostate;
	mc_alloc_size_t dbg_tot_new_nervenode;
	mc_alloc_size_t dbg_tot_new_neuron;
	mc_alloc_size_t dbg_tot_new_polaron;
	mc_alloc_size_t dbg_tot_new_sorcell;
	mc_alloc_size_t dbg_tot_new_tierdata;

	dbg_stats() mc_external_code_ram;
	~dbg_stats() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) mc_external_code_ram;

	void dbg_prt_all() mc_external_code_ram;
};

#define BJ_MAX_ID_ARR_SZ 260

#define BJ_DBG_STR_CAP 2048

class mc_aligned nervenet : public cell  {
public:
	MCK_DECLARE_MEM_METHODS(nervenet, mc_external_code_ram)

	long MAGIC;

	num_syn_t tmp_id_arr[BJ_MAX_ID_ARR_SZ];

	num_nod_t tot_neus;
	num_nod_t tot_vars;
	num_nod_t tot_lits;
	num_nod_t tot_rels;

	mc_alloc_size_t	num_sep_tiersets;
	mc_alloc_size_t	num_sep_tierdatas;

	grip		ava_transmitters;
	grip		ava_sornet_transmitters;
	grip		ava_stabi_transmitters;
	grip		ava_sync_transmitters;
	grip		ava_synsets;
	grip		ava_tiersets;
	grip		ava_synapses;
	grip		ava_neurons;
	grip		ava_polarons;
	grip		ava_sorcells;
	grip		ava_tierdatas;

	missive_handler_t all_handlers[idx_total];

	pre_cnf_net*	shd_cnf;

	num_nod_t tot_loading;
	num_nod_t tot_loaded;

	grip	all_neu;
	grip	all_pos;
	grip	all_neg;

	mc_core_nn_t sync_tot_children;
	mc_core_id_t sync_parent_id;
	mc_load_map_st* sync_map;

	netstate	act_left_side;
	netstate	act_right_side;

	EMU_DBG_CODE(
		dbg_stats all_dbg_dat;
		char 	dbg_str1[BJ_DBG_STR_CAP];
		char 	dbg_str2[BJ_DBG_STR_CAP];
	);

	num_nod_t tot_sorcells;
	grip	all_sorcells;

	num_nod_t 	dbg_sornet_curr_cntr;

	binval_t	net_top;
	binval_t	net_bottom;

	num_nod_t 	tot_input_sorcells;
	sorcell**	all_input_sorcells;
	num_nod_t 	tot_rcv_output_sorobjs;
	void**		all_output_sorobjs;

	nervenet() mc_external_code_ram;
	~nervenet() mc_external_code_ram;

	void init_nervenet_with(pre_cnf_net* pre_net) mc_external_code_ram;

	void sync_handler(tier_kind_t tiki, missive* msv);

	void dbg_only_handler(missive* msv) bj_dbg_only_cod;
	void load_handler(missive* msv) bj_load_cod;
	void propag_handler(missive* msv) bj_propag_cod;
	void sornet_handler(missive* msv) bj_sornet_cod;

	void init_sync_cycle() mc_external_code_ram;
	void propag_nervenet_start() bj_propag_cod;

	void propag_handle_sync() bj_propag_cod;
	void send_parent_tok_empty_child(net_side_t sd) bj_propag_cod;

	void mirrow_handler(missive* msv) bj_stabi_cod;
	void mirrow_nervenet() bj_stabi_cod;
	void mirrow_start_all_nods(grip& all_nod, net_side_t sd) bj_stabi_cod;

	void stabi_handler(missive* msv) bj_stabi_cod;
	void stabi_nervenet_start() bj_stabi_cod;

	void send_all_neus(mck_token_t tok);

	bool sornet_check_order(bj_cmp_obj_func_t fn);

	bool sornet_dbg_send_cntr() bj_sornet_cod;
	void sornet_dbg_end_step() bj_sornet_cod;
	void sornet_dbg_bin_handler(missive* msv) bj_sornet_cod;


	nervenet* get_nervenet(mc_core_id_t core_id);

	netstate& get_active_netstate(net_side_t sd);

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

#define bj_num_sep_tiersets (bj_nervenet->num_sep_tiersets)
#define bj_num_sep_tierdatas (bj_nervenet->num_sep_tierdatas)

#define bj_nervenet ((nervenet*)(kernel::get_sys()->user_data))
#define bj_ava_transmitters (bj_nervenet->ava_transmitters)
#define bj_ava_sornet_transmitters (bj_nervenet->ava_sornet_transmitters)
#define bj_ava_stabi_transmitters (bj_nervenet->ava_stabi_transmitters)
#define bj_ava_sync_transmitters (bj_nervenet->ava_sync_transmitters)
#define bj_ava_synsets (bj_nervenet->ava_synsets)
#define bj_ava_tiersets (bj_nervenet->ava_tiersets)
#define bj_ava_synapses (bj_nervenet->ava_synapses)
#define bj_ava_neurons (bj_nervenet->ava_neurons)
#define bj_ava_polarons (bj_nervenet->ava_polarons)
#define bj_ava_sorcells (bj_nervenet->ava_sorcells)
#define bj_ava_tierdatas (bj_nervenet->ava_tierdatas)

#define bj_handlers (bj_nervenet->all_handlers)

extern missive_handler_t bj_nil_handlers[];

//void bj_propag_kernel_func();
//void bj_stabi_kernel_func();

#define	bj_dbg_prt_nd_neu_flag mc_flag1
#define	bj_dbg_prt_nd_pol_flag mc_flag2
#define	bj_dbg_prt_id_pol_flag mc_flag3

void bj_print_loaded_poles(grip& all_pol, node_kind_t ki) mc_external_code_ram;
void bj_print_loaded_cnf() mc_external_code_ram;

void bj_print_active_cnf(net_side_t sd, tier_kind_t tiki, char* prefix, num_pulse_t num_pul, 
			num_tier_t num_ti, mc_flags_t prt_flgs = bj_dbg_prt_nd_neu_flag) mc_external_code_ram;

void bj_print_class_szs() mc_external_code_ram;

char* bj_dbg_tier_kind_to_str(tier_kind_t tiki) mc_external_code_ram;

#endif		// NERVENET_H


