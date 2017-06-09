
//----------------------------------------------------------------------------
// actor.hh

#ifndef ACTOR_HH
#define ACTOR_HH

#include <new>
#include "dyn_mem.h"
#include "binder.hh"
#include "err_msgs.h"
#include "global.h"
//include "cores_main.h"

// look for "class bj_aligned "

class kernel;
class agent;
class actor;
class missive;
class agent_ref;
class agent_grp;

typedef agent_grp missive_grp_t;
typedef agent_ref missive_ref_t;
typedef agent_grp actor_grp_t;
typedef agent_ref actor_ref_t;


//-------------------------------------------------------------------------
// casts

typedef grip& (* bj_method_1_t)();

typedef void (*bj_kenel_func_t)(void);

//-------------------------------------------------------------------------
// actor ids

#define bjk_actor_id(cls) BJ_ACTOR_ID_##cls

enum bjk_actor_id_t : uint8_t {
	bjk_invalid_actor = 0,

	bjk_actor_id(agent),
	bjk_actor_id(actor),
	bjk_actor_id(missive),
	bjk_actor_id(agent_ref),
	bjk_actor_id(agent_grp),

	bjk_tot_actor_ids
};

//-------------------------------------------------------------------------
// dyn mem

#define bjk_all_available(nam) BJK_KERNEL->cls_available_##nam

#define BJK_DEFINE_SEPARATE_AVA(nam, all_ava) \
void \
nam::separate(uint16_t sz){ \
	grip& ava = all_ava; \
	nam* obj = nam::acquire(sz); \
	for(int bb = 0; bb < sz; bb++){ \
		obj[bb].let_go(); \
		ava.bind_to_my_left(obj[bb]); \
	} \
} \

// end_macro

#define BJK_DEFINE_SEPARATE(nam) BJK_DEFINE_SEPARATE_AVA(nam, bjk_all_available(nam))

#define BJK_DEFINE_ACQUIRE_ALLOC(nam, align) \
nam* \
nam::acquire_alloc(uint16_t sz){ \
	nam* obj = bj_malloc##align(nam, sz); \
	if(obj == bj_null){ \
		bjk_abort((bj_addr_t)nam::acquire_alloc, err_1); \
	} \
	BJK_CK(BJ_IS_ALIGNED_##align(obj)); \
	for(int bb = 0; bb < sz; bb++){ \
		new (&(obj[bb])) nam(); \
	} \
	return obj; \
} \

// end_macro

#define BJK_DEFINE_ACQUIRE_AVA(nam, all_ava) \
nam* \
nam::acquire(uint16_t sz){ \
	grip& ava = all_ava; \
	if((sz == 1) && (! ava.is_alone())){ \
		binder* fst = ava.bn_right; \
		fst->let_go(); \
		return (nam *)fst; \
	} \
	return nam::acquire_alloc(sz); \
} \

// end_macro

#define BJK_DEFINE_ACQUIRE(nam) BJK_DEFINE_ACQUIRE_AVA(nam, bjk_all_available(nam))

#define BJK_DECLARE_MEM_METHODS(nam) \
	static	nam*			acquire_alloc(uint16_t sz = 1) bj_external_code_ram; \
	static	nam*			acquire(uint16_t sz = 1); \
	static	void			separate(uint16_t sz) bj_external_code_ram; \

// end_macro

#define BJK_DEFINE_MEM_METHODS(nam, align, all_ava) \
	BJK_DEFINE_ACQUIRE_ALLOC(nam, align) \
	BJK_DEFINE_ACQUIRE_AVA(nam, all_ava) \
	BJK_DEFINE_SEPARATE_AVA(nam, all_ava) \

// end_macro

//-------------------------------------------------------------------------
// handler ids

typedef uint8_t bjk_handler_idx_t;

enum bjk_core_state_t : uint8_t {
	bjk_invalid_state = 10,
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
	bjk_tot_signals
};

enum bjk_ack_t : uint8_t {
	bjk_ready_ack = 30,
	bjk_busy_ack,
	bjk_virgin_ack
};


//-------------------------------------------------------------------------
// kernel class

//define bj_virgin bj_null
#define bj_virgin ((missive_grp_t*)(~((bj_addr_t)bj_null)))

#define kernel_signals_arr_sz bjk_tot_signals
#define kernel_pw0_routed_arr_sz bj_out_num_cores
#define kernel_pw2_routed_arr_sz bjk_tot_routes
#define kernel_pw4_routed_arr_sz bjk_tot_routes
#define kernel_pw6_routed_arr_sz bjk_tot_routes

#define kernel_class_names_arr_sz bjk_tot_actor_ids

//if defined(XXX) && !defined(YYY) 

#ifdef BJ_IS_EPH_CODE
	kernel*
	bjk_get_first_kernel() bj_external_code_ram;

	extern kernel*	bjk_PT_THE_KERNEL;
	#define BJK_FIRST_KERNEL bjk_get_first_kernel()
	#define BJK_KERNEL (bjk_PT_THE_KERNEL)
#endif

#ifdef BJ_IS_ZNQ_CODE
	kernel*
	bjh_get_first_kernel();

	extern kernel*	bjh_PT_THE_KERNEL;
	#define BJK_FIRST_KERNEL bjh_get_first_kernel()
	#define BJK_KERNEL (bjh_PT_THE_KERNEL)
#endif

#ifdef BJ_IS_EMU_CODE
	#define BJK_FIRST_KERNEL kernel::get_sys()
	#define BJK_KERNEL kernel::get_sys()
#endif

#define bjk_get_kernel() BJK_KERNEL

class bj_aligned kernel { 
public:
	uint32_t 	magic_id;
	bool		is_host_kernel;

	bjk_handler_idx_t 	tot_handlers;
	missive_handler_t* 	all_handlers;

	bj_bool_t signals_arr[kernel_signals_arr_sz];

	missive_grp_t* pw0_routed_arr[kernel_pw0_routed_arr_sz];
	missive_grp_t* pw2_routed_arr[kernel_pw2_routed_arr_sz];
	missive_grp_t* pw4_routed_arr[kernel_pw4_routed_arr_sz];
	missive_grp_t* pw6_routed_arr[kernel_pw6_routed_arr_sz];

	bjk_ack_t pw0_routed_ack_arr[kernel_pw0_routed_arr_sz];
	bjk_ack_t pw2_routed_ack_arr[kernel_pw2_routed_arr_sz];
	bjk_ack_t pw4_routed_ack_arr[kernel_pw4_routed_arr_sz];
	bjk_ack_t pw6_routed_ack_arr[kernel_pw6_routed_arr_sz];

	missive_grp_t*	routed_from_host;
	bjk_ack_t	routed_ack_from_host;

	bj_bool_t has_from_host_work;
	bj_bool_t has_to_host_work;

	grip to_cores_work;
	grip to_host_work;
	grip from_host_work;

	grip in_work;
	grip local_work;
	grip out_work;
	grip sent_work;

	char* class_names_arr[kernel_class_names_arr_sz];

	grip 	cls_available_actor;
	grip 	cls_available_missive;
	grip 	cls_available_agent_ref;
	grip 	cls_available_agent_grp;

	kernel*	host_kernel;

	actor* 	first_actor;

	bj_kenel_func_t	user_func;
	void*	user_data;

	bool		host_running;
	uint16_t 	did_work;
	bool 		exit_when_idle;

	uint32_t 	end_magic_id;

	kernel() bj_external_code_ram;

	~kernel() bj_external_code_ram;

	void init_kernel() bj_external_code_ram;

	static void
	init_sys() bj_external_code_ram;

	static bj_opt_sz_fn void 
	run_sys();

	static void
	finish_sys() bj_external_code_ram;

	static void
	init_host_sys() bj_external_code_ram;

	static void 
	run_host_sys() bj_external_code_ram;

	static void
	finish_host_sys() bj_external_code_ram;

	static kernel*
	get_sys();

	static bj_inline_fn bjk_glb_sys_st& 
	get_glb(){
		return *BJK_GLB_SYS;
	}

	static bj_inline_fn bj_off_core_st& 
	get_off_shd(){
		return *(BJK_GLB_SYS->off_core_pt);
	}

	static bj_inline_fn bj_sys_sz_st& 
	get_sys_sz(){
		return *BJK_GLB_SYS_SZ;
		//return BJK_GLB_SYS->bjk_system_sz;
	}

	static bj_inline_fn bj_core_nn_t 
	get_core_nn(){
		return BJK_GLB_SYS->the_core_nn;
	}

	static bj_inline_fn bj_core_co_t 
	get_core_ro(){
		return BJK_GLB_SYS->the_core_ro;
	}

	static bj_inline_fn bj_core_co_t 
	get_core_co(){
		return BJK_GLB_SYS->the_core_co;
	}

	static bj_inline_fn bj_core_id_t 
	get_core_id(){
		return BJK_GLB_SYS->the_core_id;
	}

	static bj_inline_fn actor*
	get_core_actor(){
		return BJK_KERNEL->first_actor;
	}

	static actor*
	get_core_actor(bj_core_id_t dst_id);

	static actor*
	get_host_actor() bj_external_code_ram;

	static void
	set_handlers(uint8_t tot_hdlrs, missive_handler_t* hdlrs) bj_external_code_ram;

	static kernel*
	get_core_kernel(bj_core_id_t id) bj_external_code_ram;

	bj_inline_fn
	void set_idle_exit(){
		exit_when_idle = true;
	}

	bj_opt_sz_fn void 
	process_signal(binder& in_wrk, int sz, missive_grp_t** arr, bjk_ack_t* acks);

	bj_opt_sz_fn void 
	handle_missives();

	bj_opt_sz_fn void 
	add_out_missive(grip* out_wk, missive& msv);

	bj_opt_sz_fn void 
	call_handlers_of_group(missive_grp_t* mgrp);

	void 
	handle_work_to_host() bj_external_code_ram;

	void
	handle_work_from_host() bj_external_code_ram;

	void 
	handle_work_to_cores() bj_external_code_ram;

	void 
	handle_host_missives() bj_external_code_ram;

	void 
	call_host_handlers_of_group(missive_grp_t* mgrp) bj_external_code_ram;

};

#define bjk_is_valid_handler_idx(idx) ((idx >= 0) && (idx < tot_handlers))

#define bjk_is_valid_handler_index(idx) \
	((all_handlers != bj_null) && bjk_is_valid_handler_idx(idx) && (all_handlers[idx] != bj_null))


#define bjk_handle_missive_base(msv, hdlr_idx) \
	if(bjk_is_valid_handler_idx(hdlr_idx)){ \
		(*(all_handlers[hdlr_idx]))(msv); \
		EMU_DBG_CODE(msv->dbg_msv |= 0x2); \
	} \

// end_macro

#define bjk_handle_missive(msv) \
	actor* hdlr_dst = (msv)->dst; \
	EMU_CK(hdlr_dst != bj_null); \
	bjk_handle_missive_base(msv, hdlr_dst->handler_idx) \

// end_macro


#define bj_class_name(cls) const_cast<char*>("{" #cls "}");

#define bjk_is_valid_class_name_idx(id) ((id >= 0) && (id < kernel_class_names_arr_sz))

#define bjk_set_class_name(cls) class_names_arr[bjk_actor_id(cls)] = bj_class_name(cls)

//-------------------------------------------------------------------------
// agent class 

class bj_aligned agent: public binder{
public:
	bj_opt_sz_fn 
	agent(){}

	bj_opt_sz_fn 
	~agent(){}

	virtual bj_opt_sz_fn 
	bjk_actor_id_t	get_actor_id(){
		return bjk_actor_id(agent);
	}

	virtual bj_opt_sz_fn 
	grip&	get_available() bj_external_code_ram;

	virtual bj_opt_sz_fn 
	void	init_me(int caller = 0) bj_external_code_ram;

	bj_opt_sz_fn 
	void	release(){
		let_go();
		init_me(1);
		grip& ava = get_available();
		ava.bind_to_my_left(*this);
	}

	bj_inline_fn
	agent*	get_glb_ptr(){
		return (agent*)bjk_as_glb_pt(this);
	}

	virtual
	char* 	get_class_name() bj_external_code_ram;
};

//-------------------------------------------------------------------------
// actor class 

typedef uint16_t bjk_token_t; 
typedef uint8_t bjk_flags_t;

class bj_aligned actor: public agent {
public:
	static
	actor*			acquire_alloc(uint16_t sz) bj_external_code_ram;
	static
	actor*			acquire(uint16_t sz = 1);
	static
	void			separate(uint16_t sz) bj_external_code_ram;

	bjk_handler_idx_t 	handler_idx;
	bjk_flags_t 		flags;

	bj_opt_sz_fn 
	actor(){
		init_me();
	}

	bj_opt_sz_fn 
	~actor(){}

	virtual bj_opt_sz_fn 
	void init_me(int caller = 0){
		handler_idx = 0;
		flags = 0;
	}

	virtual
	bj_opt_sz_fn bjk_actor_id_t	get_actor_id(){
		return bjk_actor_id(actor);
	}

	virtual
	bj_opt_sz_fn grip&	get_available(){
		return bjk_all_available(actor);
	}

	bj_opt_sz_fn
	void
	respond(missive* msv, bjk_token_t tok);
};

//-------------------------------------------------------------------------
// missive class

class bj_aligned missive : public agent {
public:
	static
	missive*		acquire_alloc(uint16_t sz) bj_external_code_ram;
	static
	missive*		acquire(uint16_t sz = 1);
	static
	void			separate(uint16_t sz) bj_external_code_ram;

	actor* 				dst;
	actor*				src;
	bjk_token_t 		tok;

	EMU_DBG_CODE(uint8_t	dbg_msv);

	bj_opt_sz_fn 
	missive(){
		init_me();
	}

	bj_opt_sz_fn 
	~missive(){}

	virtual bj_opt_sz_fn 
	void init_me(int caller = 0){
		EMU_CK((caller != 1) || (! (dbg_msv & 0x1)) || (dbg_msv & 0x2));
		dst = bj_null;
		src = bj_null;
		tok = 0;
		EMU_DBG_CODE(dbg_msv = 0);
	}

	bj_inline_fn 
	void send(){
		EMU_CK(dbg_msv == 0);
		EMU_DBG_CODE(dbg_msv |= 0x1);

		EMU_CK(dst != bj_null);
		EMU_CK(bj_addr_in_sys((bj_addr_t)dst));

		src = (actor*)bjk_as_glb_pt(src);
		BJK_KERNEL->local_work.bind_to_my_left(*this);
	}

	bj_inline_fn 
	void send_to_host(){
		EMU_CK(dbg_msv == 0);
		EMU_DBG_CODE(dbg_msv |= 0x1);

		EMU_CK(dst != bj_null);
		if(! BJK_KERNEL->is_host_kernel){
			EMU_CK(bj_addr_get_id((bj_addr_t)dst) != 0);
			EMU_CK(! bj_addr_in_sys((bj_addr_t)dst));
			src = (actor*)bjk_as_glb_pt(src);
			BJK_KERNEL->to_host_work.bind_to_my_left(*this);
			BJK_KERNEL->has_to_host_work = true;
		} else {
			BJK_KERNEL->local_work.bind_to_my_left(*this);
		}
	}

	virtual
	bj_opt_sz_fn bjk_actor_id_t	get_actor_id(){
		return bjk_actor_id(missive);
	}

	virtual
	bj_opt_sz_fn grip&	get_available(){
		return bjk_all_available(missive);
	}

	bj_inline_fn actor*
	get_source(){
		return src;
	}

	bj_inline_fn void
	set_source(actor* act){
		src = act;
	}
};

//-------------------------------------------------------------------------
// agent_grp class 

class bj_aligned agent_grp : public agent {
public:
	static
	agent_grp*		acquire_alloc(uint16_t sz) bj_external_code_ram;
	static
	agent_grp*		acquire(uint16_t sz = 1);
	static
	void			separate(uint16_t sz) bj_external_code_ram;

	grip		all_agts;
	uint8_t 	tot_agts;	// optional use
	bj_bool_t 	handled;

	bj_opt_sz_fn 
	agent_grp(){
		init_me();
	}

	bj_opt_sz_fn 
	~agent_grp(){}

	virtual bj_opt_sz_fn 
	void init_me(int caller = 0){
		tot_agts = 0;
		handled = bj_false;
	}

	virtual
	bj_opt_sz_fn bjk_actor_id_t	get_actor_id(){
		return bjk_actor_id(agent_grp);
	}

	virtual
	bj_opt_sz_fn grip&	get_available(){
		return bjk_all_available(agent_grp);
	}

	void
	release_all_agts();
};

//-------------------------------------------------------------------------
// agent_ref class 

class bj_aligned agent_ref : public agent {
public:
	static
	agent_ref*		acquire_alloc(uint16_t sz) bj_external_code_ram;
	static
	agent_ref* 		acquire(uint16_t sz = 1);
	static
	void			separate(uint16_t sz) bj_external_code_ram;

	agent* 		glb_agent_ptr;

	bj_opt_sz_fn 
	agent_ref(){
		init_me();
	}

	bj_opt_sz_fn 
	~agent_ref(){}

	virtual bj_opt_sz_fn 
	void init_me(int caller = 0){
		glb_agent_ptr = bj_null;
	}

	virtual
	bj_opt_sz_fn bjk_actor_id_t	get_actor_id(){
		return bjk_actor_id(agent_ref);
	}

	virtual
	bj_opt_sz_fn grip&	get_available(){
		return bjk_all_available(agent_ref);
	}
};

#define bj_glb_binder_get_rgt(bdr, id) ((binder*)bj_addr_set_id((id), ((bdr)->bn_right)))
#define bj_glb_binder_get_lft(bdr, id) ((binder*)bj_addr_set_id((id), ((bdr)->bn_left)))

#define bjh_glb_binder_get_rgt(bdr, id) (binder*)bj_glb_binder_get_rgt((binder*)bj_core_pt_to_host_pt(bdr), id)
#define bjh_glb_binder_get_lft(bdr, id) (binder*)bj_glb_binder_get_lft((binder*)bj_core_pt_to_host_pt(bdr), id)

#define BJK_CALL_HANDLER(cls, nam, msv) (((cls*)(bjk_as_loc_pt(msv->dst)))->nam(msv))

template<typename T, typename U> constexpr bj_size_t bj_offsetof(U T::*member) bj_external_code_ram;

template<typename T, typename U> constexpr bj_size_t bj_offsetof(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

#ifdef __cplusplus
bj_c_decl {
#endif

bool
bjk_is_id_inited(bj_core_id_t dst_id) bj_external_code_ram;

bool
bjk_ck_type_sizes() bj_external_code_ram;

//bj_opt_sz_fn 
void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq) bj_external_code_ram;

#ifdef __cplusplus
}
#endif


//static  void
//__static_initialization_and_destruction_0(int, int) bj_external_code_ram;
// ignored
// pragma GCC diagnostic warning "-fpermissive"


#endif		// ACTOR_HH
