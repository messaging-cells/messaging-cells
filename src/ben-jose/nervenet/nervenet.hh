

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
class synapse;
class nervenode;
class neurostate;
class polaron;
class neuron;
class nervenet;


enum net_side_t : uint8_t {
	side_invalid,
	side_left,
	side_right
};

enum sync_tok_t : mck_token_t {
	bj_tok_sync_invalid = mck_tok_last + 1,
	bj_tok_sync_empty_child,
	bj_tok_sync_to_parent,
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
	bj_tok_stabi_tier_done,
	bj_tok_stabi_conflict,
	bj_tok_stabi_end_forward,
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

typedef void (nervenode::*bj_callee_t)(synapse* snp, net_side_t sd);

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

void dbg_call_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd) mc_external_code_ram;

void send_all_synapses(binder* nn_all_snp, bj_callee_t mth, net_side_t sd) bj_stabi_cod;

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
BJ_DECLARE_CLS_NAM(synapse)
BJ_DECLARE_CLS_NAM(nervenode)
BJ_DECLARE_CLS_NAM(neuron)
BJ_DECLARE_CLS_NAM(polaron)
BJ_DECLARE_CLS_NAM(tierdata)
BJ_DECLARE_CLS_NAM(nervenet)

//class mc_aligned synset : public cell {
class mc_aligned synset : public agent {
public:
	MCK_DECLARE_MEM_METHODS(synset, bj_nervenet_mem)

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

	void calc_stabi_arr_rec(num_syn_t cap, num_syn_t* arr, num_syn_t& ii) bj_stabi_cod;

	void dbg_rec_call_all(bj_callee_t mth, net_side_t sd) mc_external_code_ram;

	void stabi_rec_send_all(bj_callee_t mth, net_side_t sd) bj_stabi_cod;

	void stabi_rec_reset() bj_stabi_cod;

	bool is_empty() bj_stabi_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned tierset : public agent {
public:
	MCK_DECLARE_MEM_METHODS(tierset, bj_nervenet_mem)

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
	MCK_DECLARE_MEM_METHODS(transmitter, bj_nervenet_mem)

	net_side_t wrk_side;
	num_tier_t wrk_tier;

	transmitter() mc_external_code_ram;
	~transmitter() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned synapse : public cell {
public:
	MCK_DECLARE_MEM_METHODS(synapse, bj_nervenet_mem)

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

	void send_transmitter(stabi_tok_t tok, net_side_t sd) bj_stabi_cod;

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

#define	bj_stt_stabi_flag mc_flag0
#define	bj_stt_charge_all_flag mc_flag1
#define	bj_stt_charge_src_flag mc_flag2

class mc_aligned neurostate {
public:
	num_tier_t		stabi_num_tier;  // FIX_THIS

	synapse*		stabi_source;
	grip			stabi_tiers;

	num_syn_t 		prev_tot_active;
	synset			stabi_active_set;

	mc_flags_t		stabi_flags;
	num_syn_t		stabi_num_complete;
	num_syn_t		stabi_num_ping;

	num_syn_t		stabi_arr_cap;
	num_syn_t		stabi_arr_sz;
	num_syn_t*  	stabi_arr;

	neurostate() mc_external_code_ram;
	~neurostate() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void calc_stabi_arr() bj_stabi_cod;
	bool charge_all_active(propag_data* dat, node_kind_t ki) bj_stabi_cod;
	void reset_complete() bj_stabi_cod;

	tierset*	dbg_get_tiset(num_tier_t nti) mc_external_code_ram;

	tierset*	get_tiset(num_tier_t nti = BJ_INVALID_NUM_TIER) bj_stabi_cod;
	tierset&	add_tiset(num_tier_t nti) bj_stabi_cod;

	mc_inline_fn void update_prev_tot_active() bj_load_cod;

	bool is_mono(num_tier_t nti) bj_stabi_cod;

	void send_all_propag(nervenode* nd, propag_data* dat) bj_stabi_cod;

	void update_stills(nervenode* nd, propag_data* dat) bj_stabi_cod;
	void send_all_ti_done(nervenode* nd, net_side_t sd) bj_stabi_cod;
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

	synset& get_active_set(net_side_t sd) bj_stabi_cod;

	neurostate& get_neurostate(net_side_t sd) bj_stabi_cod;

	void stabi_recv_transmitter(propag_data* dat) bj_stabi_cod;
	void stabi_recv_charge_all(propag_data* dat) bj_stabi_cod;
	void stabi_recv_charge_src(propag_data* dat) bj_stabi_cod;
	void stabi_recv_ping(propag_data* dat) bj_stabi_cod;
	void stabi_recv_tier_done(propag_data* dat) bj_stabi_cod;

	virtual 
	void stabi_send_snp_propag(synapse* snp, net_side_t sd) bj_stabi_cod;

	void stabi_send_snp_charge_src(synapse* snp, net_side_t sd) bj_stabi_cod;
	void stabi_send_snp_conflict(synapse* snp, net_side_t sd) bj_stabi_cod;
	void stabi_send_snp_end_forward(synapse* snp, net_side_t sd) bj_stabi_cod;
	void stabi_send_snp_tier_done(synapse* snp, net_side_t sd) bj_stabi_cod;

	virtual 
	void stabi_start_nxt_tier(propag_data* dat) bj_stabi_cod;

	void dbg_prt_syn(synapse* snp, net_side_t sd) mc_external_code_ram;

	void dbg_prt_nod(net_side_t sd, dbg_consec_t prt_id, num_pulse_t num_pul, 
					num_tier_t num_ti) mc_external_code_ram;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned neuron : public nervenode {
public:
	MCK_DECLARE_MEM_METHODS(neuron, bj_nervenet_mem)

	//EMU_CODE(int pru_attr);
	
	neuron() mc_external_code_ram;
	~neuron() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void stabi_handler(missive* msv) bj_stabi_cod;

	void stabi_neuron_start() bj_stabi_cod;

	virtual 
	void stabi_send_snp_propag(synapse* snp, net_side_t sd) bj_stabi_cod;

	virtual 
	void stabi_start_nxt_tier(propag_data* dat) bj_stabi_cod;

	void pru_callee(synapse* snp, net_side_t sd) mc_external_code_ram;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned polaron : public nervenode {
public:
	MCK_DECLARE_MEM_METHODS(polaron, bj_nervenet_mem)
	
	polaron*		opp;

	polaron() mc_external_code_ram;
	~polaron() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) mc_external_code_ram;

	void load_handler(missive* msv) bj_load_cod;
	void stabi_handler(missive* msv) bj_stabi_cod;

	void stabi_send_snp_charge_all(synapse* snp, net_side_t sd) bj_stabi_cod;

	void charge_all_and_start_nxt_ti(propag_data* dat) bj_stabi_cod;

	virtual 
	void stabi_start_nxt_tier(propag_data* dat) bj_stabi_cod;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

class mc_aligned tierdata : public agent {
public:
	MCK_DECLARE_MEM_METHODS(tierdata, bj_nervenet_mem)

	num_tier_t	tdt_id;

	num_nod_t inp_neus;
	num_nod_t off_neus;
	num_nod_t rcv_neus;

	tierdata() mc_external_code_ram;
	~tierdata() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0);

	void add_all_inp_from(grip& grp, net_side_t sd) mc_external_code_ram;

	void inc_rcv(node_kind_t kk) bj_stabi_cod;
	void inc_off(net_side_t sd, node_kind_t kk) bj_stabi_cod;

	mc_inline_fn bool got_all(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == rcv_neus));
	}

	void update_tidat() bj_stabi_cod;

	void update_parent_num_empty(net_side_t sd) bj_stabi_cod;

	mc_inline_fn bool is_tidat_empty(){
		return ((inp_neus != BJ_INVALID_NUM_NODE) && (inp_neus == off_neus));
	}

	virtual
	char* 	get_class_name() mc_external_code_ram;

	char* to_str() mc_external_code_ram;
};

class mc_aligned netstate {
public:
	net_side_t my_side;

	num_nod_t curr_ti_still_neus;

	num_tier_t	sync_sent_tier_empty;
	mc_core_nn_t sync_tot_empty_children;
	bool	sync_sent_ti_empty;

	num_tier_t	sync_tier_out;
	num_tier_t	sync_tier_in;

	mc_core_nn_t sync_tot_stopping_children;
	bool 		sync_sent_stop_to_parent;
	
	bool sync_ending_propag;

	grip 	all_tiers;


	netstate() mc_external_code_ram;
	~netstate() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0) mc_external_code_ram;

	void init_tiers(nervenet& nnt) mc_external_code_ram;
	void inc_tier() bj_stabi_cod;
	void inc_still(node_kind_t kk) bj_stabi_cod;

	bool is_propag_over() bj_stabi_cod;

	void send_sync_transmitter(nervenet* the_dst, sync_tok_t the_tok, num_tier_t the_ti, 
			mc_core_nn_t dbg_dst_nn) bj_stabi_cod;

	bool has_work_children() bj_stabi_cod;
	void handle_my_sync() bj_stabi_cod;
	void send_sync_to_children() mc_external_code_ram;
	void update_sync_ti_out() bj_stabi_cod;
	void reset_sync(num_tier_t rem_ti) bj_stabi_cod;


	mc_inline_fn bool is_last_empty(){
		return (get_last_tier().is_tidat_empty());
	}


	mc_inline_fn tierdata& get_last_tier(){
		EMU_CK(! all_tiers.is_alone());
		return *((tierdata*)(all_tiers.bn_left));
	}

	tierdata& get_tier(num_tier_t nti) bj_stabi_cod;

	mc_inline_fn num_tier_t get_ti_id(){
		return get_last_tier().tdt_id;
	}

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

	nervenet() mc_external_code_ram;
	~nervenet() mc_external_code_ram;

	void init_nervenet_with(pre_cnf_net* pre_net) mc_external_code_ram;

	void load_handler(missive* msv) bj_load_cod;
	void stabi_handler(missive* msv) bj_stabi_cod;

	void stabi_init_sync() mc_external_code_ram;
	void stabi_nervenet_start() bj_stabi_cod;

	void handle_sync() bj_stabi_cod;
	void start_send_empty_child(net_side_t sd) bj_stabi_cod;
	void send_parent_tok_empty_child(net_side_t sd) bj_stabi_cod;

	nervenet* get_nervenet(mc_core_id_t core_id) mc_external_code_ram;

	netstate& get_active_netstate(net_side_t sd) bj_stabi_cod;

	void dbg_stabi_stop_sys(propag_data* dat, nervenode* nod) mc_external_code_ram;

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

#define bj_num_sep_tiersets (bj_nervenet->num_sep_tiersets)
#define bj_num_sep_tierdatas (bj_nervenet->num_sep_tierdatas)

#define bj_nervenet ((nervenet*)(kernel::get_sys()->user_data))
#define bj_ava_transmitters (bj_nervenet->ava_transmitters)
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

void bj_print_active_cnf(net_side_t sd, dbg_consec_t prt_id, num_pulse_t num_pul, 
			num_tier_t num_ti) mc_external_code_ram;


#endif		// NERVENET_H

