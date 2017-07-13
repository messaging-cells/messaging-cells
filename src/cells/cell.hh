
//----------------------------------------------------------------------------
/*! \file cell.hh

\brief The one and only include file necessarry to use the Messagging Cells library.

\callgraph
\callergraph
*/

#ifndef CELL_HH
#define CELL_HH

#include <new>
#include "dyn_mem.h"
#include "binder.hh"
#include "err_msgs.h"
#include "global.h"
//include "cores_main.h"

// look for "class mc_aligned "

class kernel;
class agent;
class cell;
class missive;
class agent_ref;
class agent_grp;

typedef agent_grp missive_grp_t;
typedef agent_ref missive_ref_t;
typedef agent_grp cell_grp_t;
typedef agent_ref cell_ref_t;


//-------------------------------------------------------------------------
// casts

typedef grip& (* mc_method_1_t)();

typedef void (*mc_kenel_func_t)(void);

//-------------------------------------------------------------------------
// cell ids

#define mck_cell_id(cls) MC_CELL_ID_##cls

enum mck_cell_id_t : uint8_t {
	mck_invalid_cell = 0,

	mck_cell_id(agent),
	mck_cell_id(cell),
	mck_cell_id(missive),
	mck_cell_id(agent_ref),
	mck_cell_id(agent_grp),

	mck_tot_cell_ids
};

//-------------------------------------------------------------------------
// dyn mem

#define mck_all_available(nam) MCK_KERNEL->cls_available_##nam

#define MCK_DEFINE_SEPARATE_AVA(nam, all_ava) \
void \
nam::separate(uint16_t sz){ \
	if(sz <= 0){ return; } \
	grip& ava = all_ava; \
	nam* obj = nam::acquire(sz); \
	for(int bb = 0; bb < sz; bb++){ \
		obj[bb].let_go(); \
		ava.bind_to_my_left(obj[bb]); \
	} \
} \

// end_macro

#define MCK_DEFINE_SEPARATE(nam) MCK_DEFINE_SEPARATE_AVA(nam, mck_all_available(nam))

//! Defines 'acquire_alloc' method for class 'nam' with aligment 'align' (32 or 64).
#define MCK_DEFINE_ACQUIRE_ALLOC(nam, align) \
nam* \
nam::acquire_alloc(uint16_t sz){ \
	nam* obj = mc_malloc##align(nam, sz); \
	if(obj == mc_null){ \
		mck_abort((mc_addr_t)nam::acquire_alloc, err_1); \
	} \
	MCK_CK(MC_IS_ALIGNED_##align(obj)); \
	for(int bb = 0; bb < sz; bb++){ \
		new (&(obj[bb])) nam(); \
	} \
	return obj; \
} \

// end_macro

#define MCK_DEFINE_ACQUIRE_AVA(nam, all_ava) \
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

#define MCK_DEFINE_ACQUIRE(nam) MCK_DEFINE_ACQUIRE_AVA(nam, mck_all_available(nam))

//! Declares dynamic memory methods for class 'nam'
#define MCK_DECLARE_MEM_METHODS(nam, module) \
	static	nam*			acquire_alloc(uint16_t sz = 1) mc_external_code_ram; \
	static	nam*			acquire(uint16_t sz = 1) module; \
	static	void			separate(uint16_t sz) mc_external_code_ram; \

// end_macro

//! Defines dynamic memory methods for class 'nam' with aligment 'align' (32 or 64) and available list 'all_ava'.
#define MCK_DEFINE_MEM_METHODS(nam, align, all_ava) \
	MCK_DEFINE_ACQUIRE_ALLOC(nam, align) \
	MCK_DEFINE_ACQUIRE_AVA(nam, all_ava) \
	MCK_DEFINE_SEPARATE_AVA(nam, all_ava) \

// end_macro

//-------------------------------------------------------------------------
// handler ids

//! Type to identify a \ref missive handler.
typedef uint8_t mck_handler_idx_t;

enum mck_core_state_t : uint8_t {
	mck_invalid_state = 10,
	mck_inited_state
};

//! Type for functions that handle \ref missive s (it is a pointer to the handler function).
typedef void (*missive_handler_t)(missive* msg);

//-------------------------------------------------------------------------
// kernel data

enum mck_route_t : uint8_t {
	mck_up_route = 0,
	mck_down_route,
	mck_left_route,
	mck_right_route,
	mck_tot_routes
};

enum mck_signal_t : uint8_t {
	mck_do_pw0_routes_sgnl = 0,
	mck_do_pw2_routes_sgnl,
	mck_do_pw4_routes_sgnl,
	mck_do_pw6_routes_sgnl,
	mck_tot_signals
};

//=============================================================================
/*! \enum mck_ack_t
\brief ack state of a particular routing port.
\ingroup docgrp_inner_working

*/
enum mck_ack_t : uint8_t {
	mck_ready_ack = 30,	//!< It is ready to route (send) again through this route.
	mck_busy_ack, //!< It is has routed (sent) through this route and is waiting to be ready again.
	mck_virgin_ack //!< It is has never used this route yet.
};


//-------------------------------------------------------------------------
/*! \class kernel
\brief The kernel of a core that is using the library.
\ingroup docgrp_inner_working

\details 
<p>
Every core must have one and only one kernel inited with kernel::init_sys. 

*/

//define mc_virgin mc_null
#define mc_virgin ((missive_grp_t*)(~((mc_addr_t)mc_null)))

#define kernel_signals_arr_sz mck_tot_signals
#define kernel_pw0_routed_arr_sz mc_out_num_cores
#define kernel_pw2_routed_arr_sz mck_tot_routes
#define kernel_pw4_routed_arr_sz mck_tot_routes
#define kernel_pw6_routed_arr_sz mck_tot_routes

#define kernel_class_names_arr_sz mck_tot_cell_ids

//if defined(XXX) && !defined(YYY) 

#ifdef MC_IS_EPH_CODE
	kernel*
	mck_get_first_kernel() mc_external_code_ram;

	//! This core's kernel
	extern kernel*	mck_PT_THE_KERNEL;

	#define MCK_FIRST_KERNEL mck_get_first_kernel()

	//! Returns the kernel of this core
	#define MCK_KERNEL (mck_PT_THE_KERNEL)
#endif

#ifdef MC_IS_ZNQ_CODE
	kernel*
	mch_get_first_kernel();

	extern kernel*	mch_PT_THE_KERNEL;
	#define MCK_FIRST_KERNEL mch_get_first_kernel()
	#define MCK_KERNEL (mch_PT_THE_KERNEL)
#endif

#ifdef MC_IS_EMU_CODE
	kernel*
	mcm_get_kernel();

	#define MCK_FIRST_KERNEL mcm_get_kernel()
	#define MCK_KERNEL mcm_get_kernel()
#endif

//! Gets the local kernel
#define mck_get_kernel() MCK_KERNEL

class mc_aligned kernel { 
public:
	uint32_t 	magic_id;
	bool		is_host_kernel;

	mck_handler_idx_t 	tot_handlers;
	missive_handler_t* 	all_handlers; //!< Current array of \ref missive handlers of \ref cell s for this core.

	mc_bool_t signals_arr[kernel_signals_arr_sz];

	missive_grp_t* pw0_routed_arr[kernel_pw0_routed_arr_sz];
	missive_grp_t* pw2_routed_arr[kernel_pw2_routed_arr_sz];
	missive_grp_t* pw4_routed_arr[kernel_pw4_routed_arr_sz];
	missive_grp_t* pw6_routed_arr[kernel_pw6_routed_arr_sz];

	mck_ack_t pw0_routed_ack_arr[kernel_pw0_routed_arr_sz];
	mck_ack_t pw2_routed_ack_arr[kernel_pw2_routed_arr_sz];
	mck_ack_t pw4_routed_ack_arr[kernel_pw4_routed_arr_sz];
	mck_ack_t pw6_routed_ack_arr[kernel_pw6_routed_arr_sz];

	missive_grp_t*	routed_from_host;
	mck_ack_t	routed_ack_from_host;

	mc_bool_t has_from_host_work;
	mc_bool_t has_to_host_work;

	grip to_cores_work;
	grip to_host_work;
	grip from_host_work;

	grip in_work;
	grip local_work;
	grip out_work;
	grip sent_work;

	char* class_names_arr[kernel_class_names_arr_sz];

	grip 	cls_available_cell;
	grip 	cls_available_missive;
	grip 	cls_available_agent_ref;
	grip 	cls_available_agent_grp;

	kernel*	host_kernel;

	cell* 	first_cell;

	void*	host_load_data;

	mc_kenel_func_t	user_func;
	void*	user_data;

	bool		host_running;
	uint16_t 	did_work;
	bool 		exit_when_idle;

	uint32_t 	end_magic_id;

	kernel() mc_external_code_ram;

	~kernel() mc_external_code_ram;

	void init_kernel() mc_external_code_ram;

	static void
	init_sys() mc_external_code_ram; //!< Static method that inits this core kernel.

	static mc_opt_sz_fn void 
	run_sys(); //!< Static method that starts handling \ref missive s. No \ref missive s are handled before.

	static void
	finish_sys() mc_external_code_ram; //!< Static method that finishes this core kernel.

	static void
	init_host_sys() mc_external_code_ram;

	static void 
	run_host_sys() mc_external_code_ram;

	static void
	finish_host_sys() mc_external_code_ram;

	//! Returns the kernel
	static mc_inline_fn kernel*
	get_sys(){ return MCK_KERNEL; }

	//! Returns the core global info
	static mc_inline_fn mck_glb_sys_st& 
	get_core_info(){
		return *MC_CORE_INFO;
	}

	static mc_inline_fn mc_off_core_st& 
	get_off_shd(){
		return *(MC_CORE_INFO->off_core_pt);
	}

	//! Returns the system size structure
	static mc_inline_fn mc_sys_sz_st& 
	get_sys_sz(){
		return *MC_SYS_SZ;
		//return MC_CORE_INFO->mck_system_sz;
	}

	//! Returns the core number
	static mc_inline_fn mc_core_nn_t 
	get_core_nn(){
		return MC_CORE_INFO->the_core_nn;
	}

	//! Returns the core row
	static mc_inline_fn mc_core_co_t 
	get_core_ro(){
		return MC_CORE_INFO->the_core_ro;
	}

	//! Returns the core column
	static mc_inline_fn mc_core_co_t 
	get_core_co(){
		return MC_CORE_INFO->the_core_co;
	}

	//! Returns the core id
	static mc_inline_fn mc_core_id_t 
	get_core_id(){
		return MC_CORE_INFO->the_core_id;
	}

	//! Returns this kernel first created \ref cell 
	static mc_inline_fn cell*
	get_core_cell(){
		return MCK_KERNEL->first_cell;
	}

	//! Returns the core_cell (see \ref get_core_cell) of the core with id 'dst_id'
	static cell*
	get_core_cell(mc_core_id_t dst_id);

	//! Returns the core_cell (see \ref get_core_cell) of the host
	static cell*
	get_host_cell() mc_external_code_ram;

	//! \brief This methods sets \ref kernel::all_handlers to 'hdlrs' and it must have size 'tot_hdlrs'.
	static void
	set_handlers(uint8_t tot_hdlrs, missive_handler_t* hdlrs) mc_external_code_ram;

	static kernel*
	get_core_kernel(mc_core_id_t id) mc_external_code_ram;

	//! Tells the kernel to exit \ref kernel::run_sys when no more work is pending or done (idle).
	mc_inline_fn
	void set_idle_exit(){
		exit_when_idle = true;
	}

	mc_opt_sz_fn void 
	process_signal(binder& in_wrk, int sz, missive_grp_t** arr, mck_ack_t* acks);

	mc_opt_sz_fn void 
	handle_missives();

	mc_opt_sz_fn void 
	add_out_missive(grip* out_wk, missive& msv);

	mc_opt_sz_fn void 
	call_handlers_of_group(missive_grp_t* mgrp);

	void 
	handle_work_to_host() mc_external_code_ram;

	void
	handle_work_from_host() mc_external_code_ram;

	void 
	handle_work_to_cores() mc_external_code_ram;

	void 
	handle_host_missives() mc_external_code_ram;

	void 
	call_host_handlers_of_group(missive_grp_t* mgrp) mc_external_code_ram;

};

#define mck_is_valid_handler_idx(idx) ((idx >= 0) && (idx < tot_handlers))

#define mck_is_valid_handler_index(idx) \
	((all_handlers != mc_null) && mck_is_valid_handler_idx(idx) && (all_handlers[idx] != mc_null))


#define mck_handle_missive_base(msv, hdlr_idx) \
	if(mck_is_valid_handler_idx(hdlr_idx)){ \
		(*(all_handlers[hdlr_idx]))(msv); \
		EMU_DBG_CODE(msv->dbg_msv |= 0x2); \
	} \

// end_macro

#define mck_handle_missive(msv) \
	cell* hdlr_dst = (msv)->dst; \
	EMU_CK(hdlr_dst != mc_null); \
	mck_handle_missive_base(msv, hdlr_dst->handler_idx) \

// end_macro


#define mc_class_name(cls) const_cast<char*>("{" #cls "}");

#define mck_is_valid_class_name_idx(id) ((id >= 0) && (id < kernel_class_names_arr_sz))

#define mck_set_class_name(cls) class_names_arr[mck_cell_id(cls)] = mc_class_name(cls)

//-------------------------------------------------------------------------
/*! \class agent
\brief The base class for any library object including \ref cell s, \ref missive s,  \ref agent_grp s
and \ref agent_ref s.
\ingroup docgrp_inner_working

*/
class mc_aligned agent: public binder{
public:
	mc_opt_sz_fn 
	agent(){}

	mc_opt_sz_fn 
	~agent(){}

	virtual mc_opt_sz_fn 
	mck_cell_id_t	get_cell_id(){
		return mck_cell_id(agent);
	}

	//! Method that must return the available \ref grip for each \ref agent derived class.
	virtual mc_opt_sz_fn 
	grip&	get_available() mc_external_code_ram;

	virtual mc_opt_sz_fn 
	void	init_me(int caller = 0) mc_external_code_ram;

	//! Releases this \ref agent so that it can latter be acquired again.
	mc_opt_sz_fn 
	void	release(){
		let_go();
		init_me(1);
		grip& ava = get_available();
		ava.bind_to_my_left(*this);
	}

	mc_inline_fn
	agent*	get_glb_ptr(){
		return (agent*)mck_as_glb_pt(this);
	}

	virtual
	char* 	get_class_name() mc_external_code_ram;
};

//-------------------------------------------------------------------------
/*! \class cell
\brief The base class for any user processing class that wishes send \ref missive s. 
\ingroup docgrp_messaging

\details 
<p>
A cell is the fundamental unit of concurrent computation of the library. 

<p>
The user can think of it as a concurrent object (as in object oriented programming), an object that can receive \ref missive s.

<p>
Every cell has a \ref mck_handler_idx_t called \ref handler_idx .
*/


typedef uint16_t mck_token_t; 
typedef uint8_t mck_flags_t;

class mc_aligned cell: public agent {
public:
	static
	cell*			acquire_alloc(uint16_t sz) mc_external_code_ram;
	static
	cell*			acquire(uint16_t sz = 1);
	static
	void			separate(uint16_t sz) mc_external_code_ram;

	mck_handler_idx_t 	handler_idx; //!< The index of my handler function in \ref kernel::all_handlers.
	mck_flags_t 		flags;

	mc_opt_sz_fn 
	cell(){
		init_me();
	}

	mc_opt_sz_fn 
	~cell(){}

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0){
		handler_idx = 0;
		flags = 0;
	}

	virtual
	mc_opt_sz_fn mck_cell_id_t	get_cell_id(){
		return mck_cell_id(cell);
	}

	virtual
	mc_opt_sz_fn grip&	get_available(){
		return mck_all_available(cell);
	}

	mc_opt_sz_fn
	void
	respond(missive* msv, mck_token_t tok);
};

//-------------------------------------------------------------------------
/*! \class missive
\brief The base class for any user data class that wishes to be sent beetwen \ref cell s.
\ingroup docgrp_messaging

*/

class mc_aligned missive : public agent {
public:
	static
	missive*		acquire_alloc(uint16_t sz) mc_external_code_ram;
	static
	missive*		acquire(uint16_t sz = 1);
	static
	void			separate(uint16_t sz) mc_external_code_ram;

	cell* 				dst;
	cell*				src;
	mck_token_t 		tok;

	EMU_DBG_CODE(uint8_t	dbg_msv);

	mc_opt_sz_fn 
	missive(){
		init_me();
	}

	mc_opt_sz_fn 
	~missive(){}

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0){
		EMU_CK((caller != 1) || (! (dbg_msv & 0x1)) || (dbg_msv & 0x2));
		dst = mc_null;
		src = mc_null;
		tok = 0;
		EMU_DBG_CODE(dbg_msv = 0);
	}

	//! Sends this \ref missive . It calls \ref mck_as_glb_pt with src before sending.
	mc_inline_fn 
	void send(){
		EMU_CK(dbg_msv == 0);
		EMU_DBG_CODE(dbg_msv |= 0x1);

		EMU_CK(dst != mc_null);
		EMU_CK(mc_addr_in_sys((mc_addr_t)dst));

		src = (cell*)mck_as_glb_pt(src);
		MCK_KERNEL->local_work.bind_to_my_left(*this);
	}

	mc_inline_fn 
	void send_to_host(){
		EMU_CK(dbg_msv == 0);
		EMU_DBG_CODE(dbg_msv |= 0x1);

		EMU_CK(dst != mc_null);
		if(! MCK_KERNEL->is_host_kernel){
			EMU_CK(mc_addr_get_id((mc_addr_t)dst) != 0);
			EMU_CK(! mc_addr_in_sys((mc_addr_t)dst));
			src = (cell*)mck_as_glb_pt(src);
			MCK_KERNEL->to_host_work.bind_to_my_left(*this);
			MCK_KERNEL->has_to_host_work = true;
		} else {
			MCK_KERNEL->local_work.bind_to_my_left(*this);
		}
	}

	virtual
	mc_opt_sz_fn mck_cell_id_t	get_cell_id(){
		return mck_cell_id(missive);
	}

	virtual
	mc_opt_sz_fn grip&	get_available(){
		return mck_all_available(missive);
	}

	mc_inline_fn cell*
	get_source(){
		return src;
	}

	mc_inline_fn void
	set_source(cell* act){
		src = act;
	}
};

//-------------------------------------------------------------------------
/*! \class agent_grp
\brief A class that is used internally to group \ref missive s, \ref cell s or any
\ref agent derived class. You can use it too.
\ingroup docgrp_inner_working

*/
class mc_aligned agent_grp : public agent {
public:
	static
	agent_grp*		acquire_alloc(uint16_t sz) mc_external_code_ram;
	static
	agent_grp*		acquire(uint16_t sz = 1);
	static
	void			separate(uint16_t sz) mc_external_code_ram;

	grip		all_agts;
	uint8_t 	tot_agts;	// optional use
	mc_bool_t 	handled;

	mc_opt_sz_fn 
	agent_grp(){
		init_me();
	}

	mc_opt_sz_fn 
	~agent_grp(){}

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0){
		tot_agts = 0;
		handled = mc_false;
	}

	virtual
	mc_opt_sz_fn mck_cell_id_t	get_cell_id(){
		return mck_cell_id(agent_grp);
	}

	virtual
	mc_opt_sz_fn grip&	get_available(){
		return mck_all_available(agent_grp);
	}

	void
	release_all_agts();
};

//-------------------------------------------------------------------------
/*! \class agent_ref
\brief A class that is used internally to hold a reference 
(local or remote ) to \ref missive s, \ref cell s or any
\ref agent derived class. You can use it too.
\ingroup docgrp_inner_working

*/
class mc_aligned agent_ref : public agent {
public:
	static
	agent_ref*		acquire_alloc(uint16_t sz) mc_external_code_ram;
	static
	agent_ref* 		acquire(uint16_t sz = 1);
	static
	void			separate(uint16_t sz) mc_external_code_ram;

	agent* 		glb_agent_ptr;

	mc_opt_sz_fn 
	agent_ref(){
		init_me();
	}

	mc_opt_sz_fn 
	~agent_ref(){}

	virtual mc_opt_sz_fn 
	void init_me(int caller = 0){
		glb_agent_ptr = mc_null;
	}

	virtual
	mc_opt_sz_fn mck_cell_id_t	get_cell_id(){
		return mck_cell_id(agent_ref);
	}

	virtual
	mc_opt_sz_fn grip&	get_available(){
		return mck_all_available(agent_ref);
	}
};

#define mc_glb_binder_get_rgt(bdr, id) ((binder*)mc_addr_set_id((id), ((bdr)->bn_right)))
#define mc_glb_binder_get_lft(bdr, id) ((binder*)mc_addr_set_id((id), ((bdr)->bn_left)))

#define mch_glb_binder_get_rgt(bdr, id) (binder*)mc_glb_binder_get_rgt((binder*)mc_core_pt_to_host_pt(bdr), id)
#define mch_glb_binder_get_lft(bdr, id) (binder*)mc_glb_binder_get_lft((binder*)mc_core_pt_to_host_pt(bdr), id)

#define MCK_CALL_HANDLER(cls, nam, msv) (((cls*)(mck_as_loc_pt(msv->dst)))->nam(msv))

template<typename T, typename U> constexpr mc_size_t mc_offsetof(U T::*member) mc_external_code_ram;

template<typename T, typename U> constexpr mc_size_t mc_offsetof(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

#ifdef __cplusplus
mc_c_decl {
#endif

bool
mck_is_id_inited(mc_core_id_t dst_id) mc_external_code_ram;

bool
mck_ck_type_sizes() mc_external_code_ram;

//mc_opt_sz_fn 
void 
mck_send_irq(mc_core_id_t koid, uint16_t num_irq) mc_external_code_ram;

#ifdef __cplusplus
}
#endif


//static  void
//__static_initialization_and_destruction_0(int, int) mc_external_code_ram;
// ignored
// pragma GCC diagnostic warning "-fpermissive"


#endif		// CELL_HH
