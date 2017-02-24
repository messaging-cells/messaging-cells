
#include <cstdlib>
#include <new>

#include "global.h"
#include "trace.h"
#include "cpp_main.h"
//include "row.hh"
#include "dyn_mem.hh"
#include "actor.hh"

//----------------------------------------------------------------------------
// To FAKE std c++ lib initialization and destructions of global objects
// DO NOT FORGET to call initializers explicitly.

extern "C" int 
__cxa_atexit(void* obj, void (*destruc) (void*), void* dso_hndl) bj_code_dram;

int 
__cxa_atexit(void* obj, void (*destruc) (void*), void* dso_hndl){
	static_cast<void>(obj);
	static_cast<void>(destruc);
	static_cast<void>(dso_hndl);
	return 0;
}

void* __dso_handle = bj_null;

//----------------------------------------------------------------------------

grip 			actor::AVAILABLE;
grip 			missive::AVAILABLE;
grip 			missive_ref::AVAILABLE;

DEFINE_ACQUIRE(actor)
DEFINE_ACQUIRE(missive)
DEFINE_ACQUIRE(missive_ref)

bjk_actor_id_t 	actor::THE_ACTOR_ID = bjk_actor_id(actor);
bjk_actor_id_t 	missive::THE_ACTOR_ID = bjk_actor_id(missive);
bjk_actor_id_t 	missive_ref::THE_ACTOR_ID = bjk_actor_id(missive_ref);

char* kernel_class_names_arr[kernel_class_names_arr_sz];
missive_handler_t kernel_handlers_arr[kernel_handlers_arr_sz];
missive* kernel_received_arr[kernel_received_arr_sz];
uint8_t kernel_confirmed_arr[kernel_confirmed_arr_sz];

grip kernel_in_work;
grip kernel_local_work;
grip kernel_out_work;

void
init_class_names(){
	bjk_set_class_name(actor);
	bjk_set_class_name(missive);
	bjk_set_class_name(missive_ref);
}

void 
init_cpp_main(){
	new (&actor::AVAILABLE) grip(); 
	new (&missive::AVAILABLE) grip(); 
	new (&missive_ref::AVAILABLE) grip(); 

	bj_init_arr_vals(kernel_class_names_arr_sz, kernel_class_names_arr, bj_null);
	bj_init_arr_vals(kernel_handlers_arr_sz, kernel_handlers_arr, bj_null);
	bj_init_arr_vals(kernel_received_arr_sz, kernel_received_arr, bj_null);
	bj_init_arr_objs(kernel_confirmed_arr_sz, kernel_confirmed_arr, uint8_t);

	new (&kernel_in_work) grip(); 
	new (&kernel_local_work) grip(); 
	new (&kernel_out_work) grip(); 

	bj_in_core_shd.binder_sz = sizeof(binder);
	bj_in_core_shd.receptor_sz = sizeof(receptor<actor>);
	bj_in_core_shd.actor_sz = sizeof(actor);
	bj_in_core_shd.missive_sz = sizeof(missive);

	init_class_names();
}

void 
actors_main_loop(){
	
	while(true){
		binder * fst, * lst, * wrk, * nxt;

		fst = kernel_in_work.bn_right;
		lst = &kernel_in_work;
		for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
			missive_ref* fst_ref = (missive_ref*)wrk;
			nxt = wrk->bn_right;

			missive* remote_msv = (missive*)(fst_ref->remote_msv);
			actor* dst = remote_msv->dst;
			bjk_handler_idx_t idx = dst->id_idx;
			if(bjk_is_valid_handler_idx(idx)){
				(*(kernel_handlers_arr[idx]))(remote_msv);
			}
		}

		fst = kernel_local_work.bn_right;
		lst = &kernel_local_work;
		for(wrk = fst; wrk != lst; wrk = nxt){
			missive* fst_msg = (missive*)wrk;
			nxt = wrk->bn_right;

			actor* dst = fst_msg->dst;
			if(bjk_addr_is_local(dst)){
				if(bjk_is_valid_handler_idx(dst->id_idx)){
					(*(kernel_handlers_arr[dst->id_idx]))(fst_msg);
				}
				fst_msg->release();
			} else {
				fst_msg->let_go();
				kernel_out_work.bind_to_my_left(*fst_msg);
			}
		}

		fst = kernel_out_work.bn_right;
		lst = &kernel_out_work;
		for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
		}
	}
}

void
wait_inited_state(bj_core_id_t dst_id){
	uint8_t* loc_st = &(bj_in_core_shd.the_core_state);
	uint8_t* rmt_st = (uint8_t*)bj_addr_with(dst_id, loc_st);
	while(*rmt_st != bjk_inited_state);
}

void
cpp_main(){
	init_cpp_main();

	bjk_slog2("sizeof(bjk_handler_idx_t)");
	bjk_ilog(sizeof(bjk_handler_idx_t));
	bjk_slog2("\n");

	bj_in_core_shd.the_core_state = bjk_inited_state;

	if(bjk_is_core(0,0)){
		bjk_slog2("CORE (0,0) started\n");
		bj_core_id_t dst = bj_ro_co_to_id(0, 1);
		wait_inited_state(dst);
		bjk_slog2("CORE (0,0) SAW core (0,1) INITED\n");
	}
	if(bjk_is_core(0,1)){
		bjk_slog2("CORE (0,1) started\n");
		bj_core_id_t dst = bj_ro_co_to_id(0, 0);
		wait_inited_state(dst);
		bjk_slog2("CORE (0,1) SAW core (0,0) INITED\n");
	}
}

