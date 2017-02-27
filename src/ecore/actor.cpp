
#include <cstdlib>
#include <new>

#include "interruptions.h"
#include "all_regs.h"
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
grip 			missive_grp::AVAILABLE;

BJK_DEFINE_ACQUIRE(actor)
BJK_DEFINE_ACQUIRE(missive)
BJK_DEFINE_ACQUIRE(missive_ref)
BJK_DEFINE_ACQUIRE(missive_grp)

bjk_actor_id_t 	actor::THE_ACTOR_ID = bjk_actor_id(actor);
bjk_actor_id_t 	missive::THE_ACTOR_ID = bjk_actor_id(missive);
bjk_actor_id_t 	missive_ref::THE_ACTOR_ID = bjk_actor_id(missive_ref);
bjk_actor_id_t 	missive_grp::THE_ACTOR_ID = bjk_actor_id(missive_grp);

char* kernel_class_names_arr[kernel_class_names_arr_sz];
missive_handler_t kernel_handlers_arr[kernel_handlers_arr_sz];
missive_grp* kernel_received_arr[kernel_received_arr_sz];
uint8_t kernel_confirmed_arr[kernel_confirmed_arr_sz];

grip kernel_in_work;
grip kernel_local_work;
grip kernel_out_work;
grip kernel_sent_work;

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
	new (&kernel_sent_work) grip(); 

	bj_in_core_shd.binder_sz = sizeof(binder);
	bj_in_core_shd.receptor_sz = sizeof(receptor<actor>);
	bj_in_core_shd.actor_sz = sizeof(actor);
	bj_in_core_shd.missive_sz = sizeof(missive);
	bj_in_core_shd.missive_grp_sz = sizeof(missive_grp);

	init_class_names();

	bjk_separate(missive_grp, bj_sys_max_cores);

	bjk_enable_all_irq();
	bjk_global_irq_enable();
}

void 
add_out_missive(missive& msv1){
	binder * fst, * lst, * wrk;

	fst = kernel_out_work.bn_right;
	lst = &kernel_out_work;
	for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
		missive_grp* mgrp = (missive_grp*)wrk;
		missive* msv2 = (missive*)(mgrp->all_msv.get_right_pt());
		if(bj_addr_same_id(msv1.dst, msv2->dst)){
			mgrp->bind_to_my_left(*msv2);
		}
	}
	missive_grp* mgrp2 = missive_grp::acquire();
	mgrp2->bind_to_my_left(msv1);
	kernel_out_work.bind_to_my_left(*mgrp2);
}

void 
call_handlers_of_group(missive_grp& mgrp){
	binder * fst, * lst, * wrk;

	fst = mgrp.bn_right;
	lst = &mgrp;
	for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
		missive* remote_msv = (missive*)wrk;
		actor* dst = remote_msv->dst;
		bjk_handler_idx_t idx = dst->id_idx;
		if(bjk_is_valid_handler_idx(idx)){
			(*(kernel_handlers_arr[idx]))(remote_msv);
		}
	}
}

void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq) {
	bj_bool_t* irq_act = (bj_bool_t*)bj_addr_with(koid, (bj_bool_t*)(&(bjk_irq_act[num_irq])));
	*irq_act = bj_true;

	uint32_t* ilatst = (uint32_t*)bj_addr_with(koid, (void*) BJ_REG_ILATST);
	*ilatst = 1 << num_irq;
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

			missive_grp* remote_grp = (missive_grp*)(fst_ref->remote_grp);
			call_handlers_of_group(*remote_grp);
			fst_ref->remote_grp = bj_null;
			fst_ref->release();
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
				add_out_missive(*fst_msg);
			}
		}

		fst = kernel_out_work.bn_right;
		lst = &kernel_out_work;
		for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
			missive_grp* mgrp = (missive_grp*)wrk;
			nxt = wrk->bn_right;

			missive* msv = (missive*)(mgrp->all_msv.get_right_pt());
			bj_core_id_t dst_id = bj_addr_get_core_id(msv->dst);
			bj_core_nn_t idx = bj_id_to_nn(dst_id);
			void* loc_pt = &(kernel_received_arr[idx]);
			missive_grp** rmt_pt = (missive_grp**)bj_addr_with(dst_id, loc_pt);

			*rmt_pt = mgrp;

			// send interrupt
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

		bjk_send_irq(dst, 1);
		bjk_slog2("CORE (0,0) SENT IRQ\n");
	}
	if(bjk_is_core(0,1)){
		bjk_slog2("CORE (0,1) started\n");
		bj_core_id_t dst = bj_ro_co_to_id(0, 0);
		wait_inited_state(dst);
		bjk_slog2("CORE (0,1) SAW core (0,0) INITED\n");

		while(bj_in_core_shd.got_irq1 == 0);
		bjk_slog2("CORE (0,1) RECEIVED IRQ\n");
	}
}

/*
		//e_reg_write(E_REG_ILATST, (unsigned)0x00000002);
		e_irq_set(po[0] ,po[1], name_irq[0]);

		//e_reg_write(E_REG_ILATCL, (unsigned)0x00000002);
		e_irq_clear(po[0], po[1], name_irq[0]);		
		e_irq_mask(name_irq[0], E_TRUE);
		e_irq_global_mask(E_TRUE);


	ivt_entry_user

	e_asm("mov r0, #0x1ff"); 
	e_asm("movts imask, r0");
	e_asm("gie");
	//e_asm("movts ilatst, r0");

void e_irq_set(unsigned row, unsigned col, e_irq_type_t irq)
{
	unsigned *ilatst;

//	if ((row == E_SELF) || (col == E_SELF))
//		ilatst = (unsigned *) E_ILATST;
//	else
	ilatst = (unsigned *) e_get_global_address(row, col, (void *) E_REG_ILATST);

	*ilatst = 1 << (irq - E_SYNC);

	return;
}
*/