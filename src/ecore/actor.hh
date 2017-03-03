
//----------------------------------------------------------------------------
// actor.hh

#ifndef ACTOR_HH
#define ACTOR_HH

#include "binder.hh"

class agent;
class actor;
class missive;
class missive_ref;
class missive_grp;

//-------------------------------------------------------------------------
// actor ids

#define bjk_actor_id(cls) BJ_ACTOR_ID_##cls

enum bjk_actor_id_t : uint8_t {
	bjk_invalid_actor = 0,

	bjk_actor_id(agent),
	bjk_actor_id(actor),
	bjk_actor_id(missive),
	bjk_actor_id(missive_ref),
	bjk_actor_id(missive_grp),

	bjk_tot_actor_ids
};

//-------------------------------------------------------------------------
// dyn mem

#define bjk_get_available(nam) \
	if(! nam::AVAILABLE.is_alone()){ \
		binder* fst = nam::AVAILABLE.bn_right; \
		fst->let_go(); \
		return (nam *)fst; \
	} \

// end_macro

#define bjk_separate(nam, sz) \
	nam* obj = nam::acquire(sz); \
	for(int bb = 0; bb < sz; bb++){ \
		obj[bb].let_go(); \
		nam::AVAILABLE.bind_to_my_left(obj[bb]); \
	} \

// end_macro

#define BJK_DEFINE_ACQUIRE(nam) \
nam* \
nam::acquire(uint16_t sz){ \
	if(sz == 1){ \
		bjk_get_available(nam); \
	} \
	nam* obj = bjk_malloc32(nam, sz); \
	for(int bb = 0; bb < sz; bb++){ \
		new (&(obj[bb])) nam(); \
	} \
	return obj; \
} \

// end_macro


//-------------------------------------------------------------------------
// handler ids

#define bjk_handler_idx(cls) BJ_CLASS_IDX_##cls

enum bjk_handler_idx_t : uint8_t {
	bjk_invalid_handler = 0,

	bjk_handler_idx(actor),

	bjk_tot_handler_ids
};

enum bjk_core_state_t : uint8_t {
	bjk_invalid_state = 0,
	bjk_inited_state
};

typedef void (*missive_handler_t)(missive* msg);

//-------------------------------------------------------------------------
// kernel data

enum bjk_route_t : uint8_t {
	bjk_up_route = 0,
	bjk_down_route,
	bjk_left_route,
	bjk_right_route,
	bjk_tot_routes
};

enum bjk_signal_t : uint8_t {
	bjk_do_pw0_routes_sgnl = 0,
	bjk_do_pw2_routes_sgnl,
	bjk_do_pw4_routes_sgnl,
	bjk_do_pw6_routes_sgnl,
	bjk_do_pw8_routes_sgnl,
	bjk_do_direct_routes_sgnl,
	bjk_tot_signals
};

#define kernel_signals_arr_sz bjk_tot_signals
#define kernel_handlers_arr_sz bjk_tot_handler_ids
#define kernel_pw0_routed_arr_sz bj_sys_max_cores
#define kernel_pw2_routed_arr_sz bjk_tot_routes
#define kernel_pw4_routed_arr_sz bjk_tot_routes
#define kernel_pw6_routed_arr_sz bjk_tot_routes

#define kernel_class_names_arr_sz bjk_tot_actor_ids

struct bjk_kernel_dat_def { 
	bj_bool_t signals_arr[kernel_signals_arr_sz];
	missive_handler_t handlers_arr[kernel_handlers_arr_sz];
	missive_grp* pw0_routed_arr[kernel_pw0_routed_arr_sz];
	missive_grp* pw2_routed_arr[kernel_pw2_routed_arr_sz];
	missive_grp* pw4_routed_arr[kernel_pw4_routed_arr_sz];
	missive_grp* pw6_routed_arr[kernel_pw6_routed_arr_sz];

	grip direct_routed;

	grip in_work;
	grip local_work;
	grip out_work;
	grip sent_work;

	char* class_names_arr[kernel_class_names_arr_sz];
};
typedef struct bjk_kernel_dat_def bjk_kernel_dat_st;

bjk_kernel_dat_st*
bjk_get_kernel_dat();

#define bjk_is_valid_handler_idx(idx) \
	((idx >= 0) && (idx < kernel_handlers_arr_sz) && ((bjk_get_kernel_dat()->handlers_arr)[idx] != bj_null))

#define bj_class_name(cls) const_cast<char*>("{" #cls "}");

#define bjk_is_valid_class_name_idx(id) ((id >= 0) && (id < kernel_class_names_arr_sz))

#define bjk_set_class_name(cls) \
	(bjk_get_kernel_dat()->class_names_arr)[bjk_actor_id(cls)] = bj_class_name(cls)


//-------------------------------------------------------------------------
// kernel funcs

bj_opt_sz_fn void 
add_out_missive(missive& msv);

bj_opt_sz_fn void 
call_handlers_of_group(missive_grp& mgrp);

bj_opt_sz_fn void 
actors_main_loop();


//-------------------------------------------------------------------------
// agent class 

class agent: public binder{
public:
	static
	bjk_actor_id_t	THE_ACTOR_ID;

	bj_opt_sz_fn 
	agent(){}

	bj_opt_sz_fn 
	~agent(){}

	virtual bj_opt_sz_fn 
	bjk_actor_id_t	get_actor_id(){
		return agent::THE_ACTOR_ID;
	}

	virtual bj_opt_sz_fn 
	grip&	get_available() bj_code_dram;

	bj_opt_sz_fn 
	void	release(){
		let_go();
		grip& ava = get_available();
		ava.bind_to_my_left(*this);
	}

	virtual
	bj_opt_sz_fn char* 	get_class_name(){
		bjk_kernel_dat_st* ker = bjk_get_kernel_dat();
		bjk_actor_id_t id = get_actor_id();
		if(bjk_is_valid_class_name_idx(id)){
			return (ker->class_names_arr)[id];
		}
		return bj_null;
	}
};

//-------------------------------------------------------------------------
// actor class 

class actor: public agent {
public:
	static
	grip 			AVAILABLE;
	static
	bjk_actor_id_t	THE_ACTOR_ID;
	static
	actor*			acquire(uint16_t sz = 1);

	bjk_handler_idx_t 	id_idx;
	bjk_flags_t 		flags;

	bj_opt_sz_fn 
	actor(){
		init_actor();
	}

	bj_opt_sz_fn 
	~actor(){}

	bj_opt_sz_fn 
	void init_actor(){
		id_idx = bjk_invalid_handler;
		flags = 0;
	}

	virtual
	bj_opt_sz_fn bjk_actor_id_t	get_actor_id(){
		return actor::THE_ACTOR_ID;
	}

	virtual
	bj_opt_sz_fn grip&	get_available(){
		return actor::AVAILABLE;
	}

	bj_opt_sz_fn
	void	release(){
		let_go();
		grip& ava = get_available();
		ava.bind_to_my_left(*this);
	}
};

//-------------------------------------------------------------------------
// missive class 

class missive : public agent {
public:
	static
	grip 			AVAILABLE;
	static
	bjk_actor_id_t 	THE_ACTOR_ID;
	static
	missive*		acquire(uint16_t sz = 1);

	actor*	dst;
	actor*	src;

	bj_opt_sz_fn 
	missive(){
		init_missive();
	}

	bj_opt_sz_fn 
	~missive(){}

	bj_opt_sz_fn 
	void init_missive(){
		dst = bj_null;
		src = bj_null;
	}

	virtual
	bj_opt_sz_fn bjk_actor_id_t	get_actor_id(){
		return missive::THE_ACTOR_ID;
	}

	virtual
	bj_opt_sz_fn grip&	get_available(){
		return missive::AVAILABLE;
	}
};

//-------------------------------------------------------------------------
// missive_grp class 

class missive_grp : public agent {
public:
	static
	grip 			AVAILABLE;
	static
	bjk_actor_id_t 	THE_ACTOR_ID;
	static
	missive_grp*	acquire(uint16_t sz = 1);

	grip		all_msv;
	uint8_t 	num;

	bj_opt_sz_fn 
	missive_grp(){
		init_missive_grp();
	}

	bj_opt_sz_fn 
	~missive_grp(){}

	bj_opt_sz_fn 
	void init_missive_grp(){
		num = 0;
	}

	virtual
	bj_opt_sz_fn bjk_actor_id_t	get_actor_id(){
		return missive_grp::THE_ACTOR_ID;
	}

	virtual
	bj_opt_sz_fn grip&	get_available(){
		return missive_grp::AVAILABLE;
	}
};

//-------------------------------------------------------------------------
// missive_ref class 

class missive_ref : public agent {
public:
	static
	grip 			AVAILABLE;
	static
	bjk_actor_id_t 	THE_ACTOR_ID;
	static
	missive_ref*	acquire(uint16_t sz = 1);

	missive_grp*	remote_grp;

	bj_opt_sz_fn 
	missive_ref(){
		init_missive_ref();
	}

	bj_opt_sz_fn 
	~missive_ref(){}

	bj_opt_sz_fn 
	void init_missive_ref(){
		remote_grp = bj_null;
	}

	virtual
	bj_opt_sz_fn bjk_actor_id_t	get_actor_id(){
		return missive_ref::THE_ACTOR_ID;
	}

	virtual
	bj_opt_sz_fn grip&	get_available(){
		return missive_ref::AVAILABLE;
	}
};

#ifdef __cplusplus
bj_c_decl {
#endif

bj_opt_sz_fn 
void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq);

void
wait_inited_state(bj_core_id_t dst) bj_code_dram;

void
init_class_names() bj_code_dram;

void
ck_sizes() bj_code_dram;

#ifdef __cplusplus
}
#endif


//static  void
//__static_initialization_and_destruction_0(int, int) bj_code_dram;
// ignored
// pragma GCC diagnostic warning "-fpermissive"


#endif		// ACTOR_HH
