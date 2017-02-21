
//----------------------------------------------------------------------------
// actor.hh

#ifndef ACTOR_HH
#define ACTOR_HH

#include "binder.hh"

class actor;
class missive;


#define bjk_handler_idx(cls) BJ_CLASS_IDX_##cls

#define bj_class_name(cls) const_cast<char*>("{" #cls "}");

#define bjk_get_available(nam) \
	if(! nam::AVAILABLE.is_alone()){ \
		binder* fst = nam::AVAILABLE.bn_right; \
		fst->let_go(); \
		return (nam *)fst; \
	} \

// end_macro
		

enum bjk_handler_id_t {
	bj_invalid_id = 0,

	bjk_handler_idx(actor),
	bjk_handler_idx(missive),

	bj_tot_handler_ids
};

typedef uint8_t bjk_id_t;

typedef void (*missive_handler_t)(missive* msg);

class actor: public binder{
public:
	static
	grip 	AVAILABLE;
	static
	char* 	THE_CLASS_NAME;
	//static
	//void init_statics();
	static
	actor*	acquire(uint16_t sz = 1);


	bjk_id_t	id_idx;
	bjk_flags_t flags;
	uint16_t	size;

	actor(){
		init_actor();
	}
	~actor(){}

	void init_actor(){
		id_idx = bjk_handler_idx(actor);
		flags = 0;
		size = 0;
	}

	virtual
	char*	get_class_name(){
		return actor::THE_CLASS_NAME;
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
};

class sub_actor : public actor{
public:
	uint32_t	extra;
	//uint16_t	extra2;
};

class missive : public actor{
public:
	static
	grip 	AVAILABLE;
	static
	char* 	THE_CLASS_NAME;
	static
	missive*	acquire(uint16_t sz = 1);

	actor*	dst;
	actor*	src;
	bjk_id_t	kind;
	uint16_t	extra;

	missive(){
		init_missive();
	}
	~missive(){}

	void init_missive(){
		id_idx = bjk_handler_idx(missive);
		kind = bjk_handler_idx(missive);
		dst = bj_null;
		src = bj_null;
	}

	virtual
	char*	get_class_name(){
		return missive::THE_CLASS_NAME;
	}

	virtual
	grip&	get_available(){
		return missive::AVAILABLE;
	}
};

#define kernel_handlers_arr_sz bj_tot_handler_ids
extern missive_handler_t kernel_handlers_arr[kernel_handlers_arr_sz];

#define kernel_input_arr_sz bj_sys_max_cores
extern missive kernel_input_arr[kernel_input_arr_sz];

#define kernel_received_arr_sz bj_sys_max_cores
extern bjk_pt_t kernel_received_arr[kernel_received_arr_sz];

#define kernel_confirmed_arr_sz bj_sys_max_cores
extern uint8_t kernel_confirmed_arr[kernel_confirmed_arr_sz];

extern grip kernel_in_work;
extern grip kernel_out_work;

bj_opt_sz_fn void 
actors_main_loop();

#define bjk_is_valid_handler_idx(idx) ((idx >= 0) && (idx < kernel_handlers_arr_sz))

//static  void
//__static_initialization_and_destruction_0(int, int) bj_code_dram;
// ignored
// pragma GCC diagnostic warning "-fpermissive"


#endif		// ACTOR_HH
