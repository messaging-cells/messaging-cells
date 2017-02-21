
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

grip 	actor::AVAILABLE;
char* 	actor::THE_CLASS_NAME = bj_class_name(actor);
grip 	missive::AVAILABLE;
char* 	missive::THE_CLASS_NAME = bj_class_name(missive);

missive_handler_t kernel_handlers_arr[kernel_handlers_arr_sz];
missive kernel_input_arr[kernel_input_arr_sz];
bjk_pt_t kernel_received_arr[kernel_received_arr_sz];
uint8_t kernel_confirmed_arr[kernel_confirmed_arr_sz];

grip kernel_in_work;
grip kernel_out_work;

void 
init_cpp_main(){
	new (&actor::AVAILABLE) grip(); 
	new (&missive::AVAILABLE) grip(); 

	bj_init_arr_vals(kernel_handlers_arr_sz, kernel_handlers_arr, bj_null);
	bj_init_arr_objs(kernel_input_arr_sz, kernel_input_arr, missive);
	bj_init_arr_objs(kernel_received_arr_sz, kernel_received_arr, bjk_pt_t);
	bj_init_arr_objs(kernel_confirmed_arr_sz, kernel_confirmed_arr, uint8_t);

	new (&kernel_in_work) grip(); 
	new (&kernel_out_work) grip(); 
}

void 
actors_main_loop(){
	while(true){
		binder * fst, * lst, * wrk, * nxt;
		fst = kernel_in_work.bn_right;
		lst = &kernel_in_work;
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
cpp_main(){
	if(BINDER_BASE_POINTER != bj_null){
		bjk_abort((uint32_t)cpp_main, 0, bj_null);
	}
	if(__dso_handle != bj_null){
		bjk_abort((uint32_t)cpp_main, 0, bj_null);
	}

	init_cpp_main();

	receptor<actor> r1;

	for(int bb = 0; bb < kernel_input_arr_sz; bb++){
		if(! kernel_input_arr[bb].is_alone()){
			bjk_slog2("ALONE FAILED\n");
		}
	}
	bjk_slog2("ALONE CHECKS FINISHED\n");

	if(actor::AVAILABLE.is_alone()){
		bjk_slog2("actor::AVAILABLE.is_alone()\n");
	}

	bjk_slog2(actor::THE_CLASS_NAME);
	bjk_slog2("\n");
	bjk_slog2(missive::THE_CLASS_NAME);
	bjk_slog2("\n");

	bjk_slog2("sizeof(binder)");
	bjk_ilog(sizeof(binder));
	bjk_slog2("\n");

	bjk_slog2("sizeof(receptor<actor>)");
	bjk_ilog(sizeof(receptor<actor>));
	bjk_slog2("\n");

	bjk_slog2("sizeof(actor)");
	bjk_ilog(sizeof(actor));
	bjk_slog2("\n");

	bjk_slog2("sizeof(sub_actor)");
	bjk_ilog(sizeof(sub_actor));
	bjk_slog2("\n");

	bjk_slog2("sizeof(missive)");
	bjk_ilog(sizeof(missive));
	bjk_slog2("\n");

	bjk_slog2("sizeof(bjk_id_t)");
	bjk_ilog(sizeof(bjk_id_t));
	bjk_slog2("\n");

	bjk_slog2("sizeof(bjk_pt_t)");
	bjk_ilog(sizeof(bjk_pt_t));
	bjk_slog2("\n");

	bjk_slog2("sizeof(bj_size_t)");
	bjk_ilog(sizeof(bj_size_t));
	bjk_slog2("\n");

}

actor*
actor::acquire(uint16_t sz){
	if(sz == 1){
		bjk_get_available(actor);
	}
	actor* obj = bjk_malloc32(actor, sz);
	return obj;
}

missive*
missive::acquire(uint16_t sz){
	if(sz == 1){
		bjk_get_available(missive);
	}
	missive* obj = bjk_malloc32(missive, sz);
	return obj;
}

