

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

#include "cell.hh"
#include "solver.hh"

class pre_cnf_node;
class pre_cnf_net;

class transmitter;
class sync_transmitter;
class synapse;
class nervenode;
class neurostate;
class polaron;
class neuron;
class netstate;
class nervenet;

#define SYNC_LOG(...) EMU_LOG(__VA_ARGS__)
//define SYNC_LOG(...) 

#define SYNC_COND_LOG(cond, ...) EMU_COND_LOG(cond, __VA_ARGS__)
//define SYNC_COND_LOG(cond, ...) 

#define SYNC_CODE_2(prm) EMU_CODE(prm)
#define SYNC_LOG_2(...) EMU_LOG(__VA_ARGS__)

#define DBG_TIER(prm) EMU_DBG_CODE(prm)

#define OLD_SYNC_MTH(prm) 
#define NEW_SYNC_MTH(prm) prm

enum net_side_t : uint8_t {
	side_invalid,
	side_left,
	side_right
};

enum sync_tok_t : mck_token_t {
	bj_tok_sync_invalid = mck_tok_last + 1,
	bj_tok_sync2_add_tier,
	bj_tok_sync2_inert_child,
	bj_tok_sync_empty_child,
	bj_tok_sync_alive_child,
	bj_tok_sync_still_child,
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

enum stabi_tok_t : mck_token_t {
	bj_tok_stabi_invalid = bj_tok_load_end + 1,
	bj_tok_stabi_start,
	bj_tok_stabi_ping,
	bj_tok_stabi_charge_all,
	bj_tok_stabi_charge_src,
	bj_tok_stabi_all_still,
	bj_tok_stabi_tier_done,
	bj_tok_stabi_end
};

enum bj_hdlr_idx_t : uint8_t {
	idx_invalid,
	idx_synset,
	idx_tierset,
	idx_synapse,
	idx_polaron,
	idx_neuron,
	idx_tierdata,
	idx_nervenet,
	idx_total
};

struct mc_aligned callee_prms {
public:
	synapse* snp;
	net_side_t sd;
	bool rec;
};

typedef void (nervenode::*bj_callee_t)(synapse* snp, net_side_t sd, bool from_rec);

void emu_prt_tok_codes() mc_external_code_ram;

char* net_side_to_str(net_side_t sd) mc_external_code_ram;
char* node_kind_to_str(node_kind_t ki) mc_external_code_ram;


mc_inline_fn bool is_sync_tok(mck_token_t tok){
	return ((bj_tok_sync_invalid <= tok) && (tok <= bj_tok_sync_end));
}

mc_inline_fn bool is_load_tok(mck_token_t tok){
	return ((bj_tok_load_invalid <= tok) && (tok <= bj_tok_load_end));
}

mc_inline_fn bool is_stabi_tok(mck_token_t tok){
	return ((bj_tok_stabi_invalid <= tok) && (tok <= bj_tok_stabi_end));
}


char* sync_tok_to_str(sync_tok_t tok) mc_external_code_ram;
char* load_tok_to_str(load_tok_t tok) mc_external_code_ram;
char* stabi_tok_to_str(stabi_tok_t tok) mc_external_code_ram;

void dbg_call_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd, bool from_rec) mc_external_code_ram;

void send_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd, bool from_rec = false) bj_stabi_cod;

//net_side_t opp_side_of(net_side_t sd) bj_stabi_cod;

#define BJ_DECLARE_CLS_NAM(cnam) \
extern char cnam##_cls_nam[] mc_external_data_ram; \
bool bj_is_##cnam(agent* pt_obj); \

// end_of_macro

#define BJ_DEFINE_GET_CLS_NAM(cnam) \
char cnam##_cls_nam[] = "{" #cnam "}"; \
char* cnam::get_class_name(){ return cnam##_cls_nam; } \
bool bj_is_##cnam(agent* pt_obj){ \
	if(pt_obj != mc_null){ return (pt_obj->get_class_name() == cnam##_cls_nam); } \
	return false; \
} \

// end_of_macro

BJ_DECLARE_CLS_NAM(synset)
BJ_DECLARE_CLS_NAM(tierset)
BJ_DECLARE_CLS_NAM(transmitter)
BJ_DECLARE_CLS_NAM(sync_transmitter)
BJ_DECLARE_CLS_NAM(synapse)
BJ_DECLARE_CLS_NAM(nervenode)
BJ_DECLARE_CLS_NAM(neuron)
BJ_DECLARE_CLS_NAM(polaron)
BJ_DECLARE_CLS_NAM(tierdata)
BJ_DECLARE_CLS_NAM(nervenet)

class mc_aligned synset : public agent {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(synset, bj_nervenet_mem)

	synset*		parent;

	num_syn_t 	tot_syn;
	grip		all_syn;
	grip		all_grp;

	synset() mc_external_code_ram;
	~synset() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void add_left_synapse(synapse* snp);
	void add_right_synapse(synapse* snp);

	void stabi_handler(missive* msv) bj_stabi_cod;

	//void calc_stabi_arr_rec(num_syn_t cap, num_syn_t* arr, num_syn_t& ii) bj_stabi_cod;

	void dbg_rec_call_all(bj_callee_t mth, net_side_t sd) mc_external_code_ram;

	void stabi_rec_send_all(bj_callee_t mth, net_side_t sd) bj_stabi_cod;

	void stabi_rec_reset() bj_stabi_cod;

	bool is_synset_empty() bj_stabi_cod;

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
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(synapse, bj_nervenet_mem)

	synset*		left_vessel;

	binder		right_handle;
	synset*		right_vessel;

	nervenode*	owner;
	synapse*	mate;

	synapse() mc_external_code_ram;
	~synapse() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void load_handler(missive* msv) bj_load_cod;
	void stabi_handler(missive* msv) bj_stabi_cod;

	void send_transmitter(stabi_tok_t tok, net_side_t sd, bool dbg_is_forced = false) bj_stabi_cod;

	mc_inline_fn binder& get_side_binder(net_side_t sd) bj_stabi_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

struct mc_aligned propag_data {
public:
	transmitter* trm;
	synapse* snp;
	stabi_tok_t tok;
	net_side_t sd;
	num_tier_t ti;
};

#define bj_get_syn_of_rgt_handle(bdr) ((synapse*)(((uint8_t*)bdr) - mc_offsetof(&synapse::right_handle)))

#define	bj_stt_all_ping_flag mc_flag0
#define	bj_stt_charge_all_flag mc_flag1

//class neurostate {
class mc_aligned neurostate {
public:
	synset			stabi_active_set;
	num_tier_t		stabi_num_tier;

	DBG_TIER(num_tier_t		dbg_num_tier);

	synapse*		stabi_source;
	grip			stabi_tiers;

	num_syn_t 		prev_tot_active;

	mc_flags_t		stabi_flags;
	num_syn_t		stabi_num_complete;
	num_syn_t		stabi_num_ping;

	num_syn_t		stabi_arr_cap;
	num_syn_t		stabi_arr_sz;
	num_syn_t*  	stabi_arr;

	EMU_DBG_CODE(bool was_all_pg);

	neurostate() mc_external_code_ram;
	~neurostate() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	//void calc_stabi_arr() bj_stabi_cod;
	bool charge_all_active(propag_data* dat, node_kind_t ki) bj_stabi_cod;
	void reset_complete() bj_stabi_cod;

	tierset*	dbg_get_tiset(num_tier_t nti) mc_external_code_ram;

	tierset*	get_tiset(num_tier_t nti = BJ_INVALID_NUM_TIER) bj_stabi_cod;
	tierset&	add_tiset(num_tier_t nti) bj_stabi_cod;

	mc_inline_fn void update_prv_tot_active() bj_load_cod;

	bool is_mono(num_tier_t nti) bj_stabi_cod;

	mc_inline_fn bool neu_all_ping(){
		bool all_pg = ((prev_tot_active > 1) && (stabi_num_ping == prev_tot_active));
		return all_pg;
	}

	mc_inline_fn bool pol_all_ping(){
		//bool all_pg = ((prev_tot_active > 0) && (stabi_num_ping == prev_tot_active));
		bool all_pg = (stabi_num_ping == prev_tot_active);
		return all_pg;
	}

	void send_all_propag(nervenode* nd, propag_data* dat) bj_stabi_cod;

	//void update_stills(nervenode* nd, propag_data* dat) bj_stabi_cod;
	//void neu_update_stills(nervenode* nd, propag_data* dat) bj_stabi_cod;

	mc_inline_fn bool is_full(){
		return (stabi_num_complete == prev_tot_active);
	}

	void send_all_ti_done(nervenode* nd, net_side_t sd, num_tier_t dbg_ti) bj_stabi_cod;

	num_tier_t dbg_neu_tier() mc_external_code_ram;
};

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

	void stabi_recv_transmitter(propag_data* dat) bj_stabi_cod;
	void stabi_recv_charge_all(propag_data* dat) bj_stabi_cod;
	void stabi_recv_charge_src(propag_data* dat) bj_stabi_cod;
	void stabi_recv_ping(propag_data* dat) bj_stabi_cod;
	void stabi_recv_tier_done(propag_data* dat) bj_stabi_cod;

	virtual 
	void stabi_send_snp_propag(synapse* snp, net_side_t sd, bool from_rec) bj_stabi_cod;

	void stabi_send_snp_charge_src(synapse* snp, net_side_t sd, bool from_rec) bj_stabi_cod;
	//void stabi_send_snp_end_forward(synapse* snp, net_side_t sd, bool from_rec) bj_stabi_cod;
	void stabi_send_snp_tier_done(synapse* snp, net_side_t sd, bool from_rec) bj_stabi_cod;

	void send_confl_tok(propag_data* dat, sync_tok_t the_tok) mc_external_code_ram;

	virtual 
	bool is_tier_complete(propag_data* dat) bj_stabi_cod;

	virtual 
	void restore_tiers(propag_data* dat) bj_stabi_cod;

	void neu_update_net_tier_counters(propag_data* dat) mc_external_code_ram;
	void neu_update_tier_counters(propag_data* dat) bj_stabi_cod;

	virtual 
	void stabi_start_nxt_tier(propag_data* dat) bj_stabi_cod;

	void dbg_prt_syn(synapse* snp, net_side_t sd, bool from_rec) mc_external_code_ram;

	void dbg_prt_nod(net_side_t sd, char* prefix, num_pulse_t num_pul, num_tier_t num_ti) mc_external_code_ram;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned neuron : public nervenode {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(neuron, bj_nervenet_mem)

	//EMU_CODE(int pru_attr);
	
	neuron() mc_external_code_ram;
	~neuron() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void stabi_handler(missive* msv) bj_stabi_cod;

	void stabi_neuron_start() bj_stabi_cod;

	virtual 
	void stabi_send_snp_propag(synapse* snp, net_side_t sd, bool from_rec) bj_stabi_cod;

	virtual 
	void stabi_start_nxt_tier(propag_data* dat) bj_stabi_cod;

	void pru_callee(synapse* snp, net_side_t sd, bool from_rec) mc_external_code_ram;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned polaron : public nervenode {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(polaron, bj_nervenet_mem)
	
	polaron*		opp;

	polaron() mc_external_code_ram;
	~polaron() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) mc_external_code_ram;

	void load_handler(missive* msv) bj_load_cod;
	void stabi_handler(missive* msv) bj_stabi_cod;

	void stabi_send_snp_charge_all(synapse* snp, net_side_t sd, bool from_rec) bj_stabi_cod;

	void charge_all_confl_and_start_nxt_ti(propag_data* dat) mc_external_code_ram;
	void charge_all_and_start_nxt_ti(propag_data* dat) bj_stabi_cod;

	bool can_chg_all() bj_stabi_cod;

	virtual 
	bool is_tier_complete(propag_data* dat) bj_stabi_cod;

	virtual 
	void restore_tiers(propag_data* dat) bj_stabi_cod;

	virtual 
	void stabi_start_nxt_tier(propag_data* dat) bj_stabi_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

#define	bj_sent_inert_flag mc_flag0

class mc_aligned tierdata : public agent {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(tierdata, bj_nervenet_mem)

	num_tier_t	tdt_id;
	mc_flags_t	tdt_flags;

	mc_core_nn_t num_inert_chdn; // new_sync

	mc_core_nn_t ety_chdn;
	mc_core_nn_t alv_chdn;
	mc_core_nn_t stl_chdn;

	num_nod_t inp_neus;
	num_nod_t off_neus;
	num_nod_t rcv_neus;
	num_nod_t stl_neus;

	tierdata() mc_external_code_ram;
	~tierdata() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void add_all_inp_from(grip& grp, net_side_t sd) mc_external_code_ram;

	mc_inline_fn void inc_rcv(){ rcv_neus++; }
	mc_inline_fn void inc_off(){ off_neus++; }

	mc_inline_fn bool has_neus(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus > 0));
	}

	mc_inline_fn mc_core_nn_t tot_rcv_chdn(){
		return (ety_chdn + alv_chdn + stl_chdn);
	}

	mc_inline_fn bool got_all_neus(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == (rcv_neus + stl_neus)));
	}

	void update_tidat(netstate& nst) bj_stabi_cod;

	mc_inline_fn bool is_tidat_empty(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == 0));
	}

	mc_inline_fn bool all_neu_still(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == stl_neus));
	}

	mc_inline_fn bool is_inert(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == (stl_neus + off_neus) ));
	}

	mc_inline_fn bool is_busy(){
		//return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus != 0) && (inp_neus != stl_neus));
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus != 0) && (inp_neus != (stl_neus + off_neus)));
	}

	mc_inline_fn tierdata& prv_tier(){
		return *((tierdata*)bn_left);
	}

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned netstate {
public:
	net_side_t my_side;

	mc_flags_t	sync_flags;

	bool	sync_is_inactive;

	num_tier_t	sync_wait_tier;
	num_tier_t	sync_tier_out;
	num_tier_t	sync_tier_in;

	bool 		sync_sent_stop_to_parent;
	
	bool sync_ending_propag;

	grip 	all_tiers;

	sync_tok_t  tok_confl;
	nervenode*	nod_confl;
	num_tier_t	ti_confl;

	netstate() mc_external_code_ram;
	~netstate() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) mc_external_code_ram;

	void init_tiers(nervenet& nnt) mc_external_code_ram;
	void broadcast_last_tier(int dbg_caller) bj_stabi_cod;
	void inc_tier(int dbg_caller) bj_stabi_cod;

	//bool is_propag_over() bj_stabi_cod;

	void send_sync_transmitter(nervenet* the_dst, sync_tok_t the_tok, num_tier_t the_ti,
			nervenode* cfl_src = mc_null) bj_stabi_cod;

	//bool has_work_children() bj_stabi_cod;
	void update_prop_sync() bj_stabi_cod;
	void update_sync() mc_external_code_ram;

	void handle_my_sync() bj_stabi_cod;
	void send_sync_to_children(sync_tok_t the_tok, num_tier_t the_ti, nervenode* cfl_src) mc_external_code_ram;
	void send_up_confl_tok(sync_tok_t the_tok, num_tier_t the_ti, nervenode* the_cfl) mc_external_code_ram;

	mc_inline_fn tierdata& get_last_tier(){
		EMU_CK(! all_tiers.is_alone());
		return *((tierdata*)(all_tiers.bn_left));
	}

	mc_inline_fn bool is_last_tier(tierdata& tdt){
		EMU_CK(! all_tiers.is_alone());
		return (((tierdata*)(all_tiers.bn_left)) == (&tdt));
	}

	tierdata& get_tier(num_tier_t nti, int dbg_caller) bj_stabi_cod;

	void inc_ety_chdn(num_tier_t nti) mc_external_code_ram;

	bool dbg_prt_all_tiers() mc_external_code_ram;

};

class mc_aligned dbg_stats {
public:
	mc_alloc_size_t dbg_tot_new_synset;
	mc_alloc_size_t dbg_tot_new_tierset;
	mc_alloc_size_t dbg_tot_new_transmitter;
	mc_alloc_size_t dbg_tot_new_sync_transmitter;
	mc_alloc_size_t dbg_tot_new_synapse;
	mc_alloc_size_t dbg_tot_new_neurostate;
	mc_alloc_size_t dbg_tot_new_nervenode;
	mc_alloc_size_t dbg_tot_new_neuron;
	mc_alloc_size_t dbg_tot_new_polaron;
	mc_alloc_size_t dbg_tot_new_tierdata;

	dbg_stats() mc_external_code_ram;
	~dbg_stats() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) mc_external_code_ram;

	void dbg_prt_all() mc_external_code_ram;
};

class mc_aligned nervenet : public cell  {
public:
	MCK_DECLARE_MEM_METHODS(nervenet, bj_nervenet_mem)

	long MAGIC;

	num_nod_t tot_neus;
	num_nod_t tot_vars;
	num_nod_t tot_lits;
	num_nod_t tot_rels;

	mc_alloc_size_t	num_sep_tiersets;
	mc_alloc_size_t	num_sep_tierdatas;

	grip		ava_transmitters;
	grip		ava_sync_transmitters;
	grip		ava_synsets;
	grip		ava_tiersets;
	grip		ava_synapses;
	grip		ava_polarons;
	grip		ava_neurons;
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

	EMU_DBG_CODE(dbg_stats all_dbg_dat);

	nervenet() mc_external_code_ram;
	~nervenet() mc_external_code_ram;

	void init_nervenet_with(pre_cnf_net* pre_net) mc_external_code_ram;

	void load_handler(missive* msv) bj_load_cod;
	void stabi_nn_handler(missive* msv) mc_external_code_ram;
	void stabi_sync_handler(missive* msv) bj_stabi_cod;

	void stabi_init_sync() mc_external_code_ram;
	void stabi_nervenet_start() bj_stabi_cod;

	void handle_sync() bj_stabi_cod;
	void send_parent_tok_empty_child(net_side_t sd) bj_stabi_cod;

	nervenet* get_nervenet(mc_core_id_t core_id) bj_stabi_cod;

	netstate& get_active_netstate(net_side_t sd) bj_stabi_cod;

	void dbg_stabi_stop_sys(propag_data* dat, nervenode* nod) mc_external_code_ram;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

#define bj_num_sep_tiersets (bj_nervenet->num_sep_tiersets)
#define bj_num_sep_tierdatas (bj_nervenet->num_sep_tierdatas)

#define bj_nervenet ((nervenet*)(kernel::get_sys()->user_data))
#define bj_ava_transmitters (bj_nervenet->ava_transmitters)
#define bj_ava_sync_transmitters (bj_nervenet->ava_sync_transmitters)
#define bj_ava_synsets (bj_nervenet->ava_synsets)
#define bj_ava_tiersets (bj_nervenet->ava_tiersets)
#define bj_ava_synapses (bj_nervenet->ava_synapses)
#define bj_ava_polarons (bj_nervenet->ava_polarons)
#define bj_ava_neurons (bj_nervenet->ava_neurons)
#define bj_ava_tierdatas (bj_nervenet->ava_tierdatas)

#define bj_handlers (bj_nervenet->all_handlers)

extern missive_handler_t bj_nil_handlers[];

void bj_kernel_func();

void bj_print_loaded_poles(grip& all_pol, node_kind_t ki) mc_external_code_ram;
void bj_print_loaded_cnf() mc_external_code_ram;

void bj_print_active_cnf(net_side_t sd, char* prefix, num_pulse_t num_pul, 
			num_tier_t num_ti, bool with_pols = false) mc_external_code_ram;

void bj_print_class_szs() mc_external_code_ram;

#endif		// NERVENET_H


