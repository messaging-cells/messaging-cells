
//----------------------------------------------------------------------------
// actor.hh

#ifndef ACTOR_HH
#define ACTOR_HH

#include "binder.hh"

class actor;
class missive;
class missive_ref;

//-------------------------------------------------------------------------
// dyn mem

#define bjk_get_available(nam) \
	if(! nam::AVAILABLE.is_alone()){ \
		binder* fst = nam::AVAILABLE.bn_right; \
		fst->let_go(); \
		return (nam *)fst; \
	} \

// end_macro

#define DEFINE_ACQUIRE(nam) \
nam* \
nam::acquire(uint16_t sz){ \
	if(sz == 1){ \
		bjk_get_available(nam); \
	} \
	nam* obj = bjk_malloc32(nam, sz); \
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

#define kernel_handlers_arr_sz bjk_tot_handler_ids
extern missive_handler_t kernel_handlers_arr[kernel_handlers_arr_sz];

#define bjk_is_valid_handler_idx(idx) ((idx >= 0) && (idx < kernel_handlers_arr_sz))

#define kernel_received_arr_sz bj_sys_max_cores
extern missive* kernel_received_arr[kernel_received_arr_sz];

#define kernel_confirmed_arr_sz bj_sys_max_cores
extern uint8_t kernel_confirmed_arr[kernel_confirmed_arr_sz];

extern grip kernel_in_work;
extern grip kernel_local_work;
extern grip kernel_out_work;


//-------------------------------------------------------------------------
// kernel funcs

bj_opt_sz_fn void 
actors_main_loop();

//-------------------------------------------------------------------------
// actor ids

#define bjk_actor_id(cls) BJ_ACTOR_ID_##cls

enum bjk_actor_id_t : uint8_t {
	bjk_invalid_actor = 0,

	bjk_actor_id(actor),
	bjk_actor_id(missive),
	bjk_actor_id(missive_ref),

	bjk_tot_actor_ids
};

//-------------------------------------------------------------------------
// actor class names

#define bj_class_name(cls) const_cast<char*>("{" #cls "}");

#define kernel_class_names_arr_sz bjk_tot_actor_ids
extern char* kernel_class_names_arr[kernel_class_names_arr_sz];

#define bjk_is_valid_class_name_idx(id) ((id >= 0) && (id < kernel_class_names_arr_sz))

#define bjk_set_class_name(cls) kernel_class_names_arr[bjk_actor_id(cls)] = bj_class_name(cls)

//-------------------------------------------------------------------------
// actor class 

class actor: public binder{
public:
	static
	grip 			AVAILABLE;
	static
	bjk_actor_id_t	THE_ACTOR_ID;
	//static
	//void init_statics();
	static
	actor*			acquire(uint16_t sz = 1);

	bjk_handler_idx_t 	id_idx;
	bjk_flags_t 		flags;

	actor(){
		init_actor();
	}
	~actor(){}

	void init_actor(){
		id_idx = bjk_invalid_handler;
		flags = 0;
	}

	virtual
	bjk_actor_id_t	get_actor_id(){
		return actor::THE_ACTOR_ID;
	}

	virtual
	grip&	get_available(){
		return actor::AVAILABLE;
	}

	void	release(){
		let_go();
		grip& ava = get_available();
		ava.bind_to_my_left(*this);
	}

	virtual
	char* 	get_class_name(){
		bjk_actor_id_t id = get_actor_id();
		if(bjk_is_valid_class_name_idx(id)){
			return kernel_class_names_arr[id];
		}
		return bj_null;
	}
};

//-------------------------------------------------------------------------
// missive class 

class missive : public actor {
public:
	static
	grip 			AVAILABLE;
	static
	bjk_actor_id_t 	THE_ACTOR_ID;
	static
	missive*		acquire(uint16_t sz = 1);

	actor*	dst;
	actor*	src;

	missive(){
		init_missive();
	}
	~missive(){}

	void init_missive(){
		dst = bj_null;
		src = bj_null;
	}

	virtual
	bjk_actor_id_t	get_actor_id(){
		return missive::THE_ACTOR_ID;
	}

	virtual
	grip&	get_available(){
		return missive::AVAILABLE;
	}
};

//-------------------------------------------------------------------------
// missive_ref class 

class missive_ref : public actor {
public:
	static
	grip 			AVAILABLE;
	static
	bjk_actor_id_t 	THE_ACTOR_ID;
	static
	missive_ref*		acquire(uint16_t sz = 1);

	missive*	remote_msv;

	missive_ref(){
		init_missive_ref();
	}
	~missive_ref(){}

	void init_missive_ref(){
		remote_msv = bj_null;
	}

	virtual
	bjk_actor_id_t	get_actor_id(){
		return missive_ref::THE_ACTOR_ID;
	}

	virtual
	grip&	get_available(){
		return missive_ref::AVAILABLE;
	}
};

#ifdef __cplusplus
extern "C" {
#endif

void
wait_inited_state(bj_core_id_t dst) bj_code_dram;

void
init_class_names() bj_code_dram;

#ifdef __cplusplus
}
#endif


//static  void
//__static_initialization_and_destruction_0(int, int) bj_code_dram;
// ignored
// pragma GCC diagnostic warning "-fpermissive"


#endif		// ACTOR_HH
