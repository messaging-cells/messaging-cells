
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

//include "e-lib.h"

	/*
	bj_core_id_t dst1 = bj_ro_co_to_id(0, 0);
	bj_core_id_t dst2 = bj_ro_co_to_id(0, 1);

	bjk_slog2("ID 0 ="); bjk_xlog(dst1); bjk_slog2("\n");
	bjk_slog2("ID 1 ="); bjk_xlog(dst2); bjk_slog2("\n");

	dst1 = bj_ro_co_to_id(0, 2);
	dst2 = bj_ro_co_to_id(0, 3);

	bjk_slog2("ID 2 ="); bjk_xlog(dst1); bjk_slog2("\n");
	bjk_slog2("ID 3 ="); bjk_xlog(dst2); bjk_slog2("\n");

	*/

/*
		//e_reg_write(E_REG_ILATST, (unsigned)0x00000002);
		e_irq_set(po[0] ,po[1], name_irq[0]);

		//e_reg_write(E_REG_ILATCL, (unsigned)0x00000002);
		e_irq_clear(po[0], po[1], name_irq[0]);		
		e_irq_mask(name_irq[0], E_TRUE);
		e_irq_global_mask(E_TRUE);


	ivt_entry_user

	bj_asm("mov r0, #0x1ff"); 
	bj_asm("movts imask, r0");
	bj_asm("gie");
	//bj_asm("movts ilatst, r0");

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

E_SYNC         = 0,
E_SW_EXCEPTION = 1,
E_MEM_FAULT    = 2,
E_TIMER0_INT   = 3,
E_TIMER1_INT   = 4,
E_MESSAGE_INT  = 5,
E_DMA0_INT     = 6,
E_DMA1_INT     = 7,
E_USER_INT     = 9,

*/


//----------------------------------------------------------------------------
// To FAKE std c++ lib initialization and destructions of global objects
// DO NOT FORGET to call initializers explicitly.

bj_c_decl int __cxa_atexit(void* obj, void (*destruc) (void*), void* dso_hndl) bj_code_dram;

int 
__cxa_atexit(void* obj, void (*destruc) (void*), void* dso_hndl){
	static_cast<void>(obj);
	static_cast<void>(destruc);
	static_cast<void>(dso_hndl);
	return 0;
}

#ifndef IS_EMU_CODE
void* __dso_handle = bj_null;
#endif	//IS_EMU_CODE

//----------------------------------------------------------------------------

bjk_actor_id_t 	agent::THE_ACTOR_ID = bjk_actor_id(agent);
bjk_actor_id_t 	actor::THE_ACTOR_ID = bjk_actor_id(actor);
bjk_actor_id_t 	missive::THE_ACTOR_ID = bjk_actor_id(missive);
bjk_actor_id_t 	missive_ref::THE_ACTOR_ID = bjk_actor_id(missive_ref);
bjk_actor_id_t 	missive_grp::THE_ACTOR_ID = bjk_actor_id(missive_grp);

grip 	actor::AVAILABLE;
grip 	missive::AVAILABLE;
grip 	missive_ref::AVAILABLE;
grip 	missive_grp::AVAILABLE;

BJK_DEFINE_ACQUIRE(actor)
BJK_DEFINE_ACQUIRE(missive)
BJK_DEFINE_ACQUIRE(missive_ref)
BJK_DEFINE_ACQUIRE(missive_grp)

bjk_kernel_dat_st bjk_KERNEL_DAT;

bjk_kernel_dat_st*
bjk_get_kernel_dat(){
	return &bjk_KERNEL_DAT;
}

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

	bjk_kernel_dat_st* ker = bjk_get_kernel_dat();

	bj_init_arr_vals(kernel_class_names_arr_sz, ker->class_names_arr, bj_null);
	bj_init_arr_vals(kernel_signals_arr_sz, ker->signals_arr, bj_false);
	bj_init_arr_vals(kernel_handlers_arr_sz, ker->handlers_arr, bj_null);
	bj_init_arr_vals(kernel_pw0_routed_arr_sz, ker->pw0_routed_arr, bj_null);

	new (&(ker->in_work)) grip(); 
	new (&(ker->local_work)) grip(); 
	new (&(ker->out_work)) grip(); 
	new (&(ker->sent_work)) grip(); 

	bj_in_core_st* in_shd = bjk_get_glb_in_core_shd();

	in_shd->binder_sz = sizeof(binder);
	in_shd->receptor_sz = sizeof(receptor<actor>);
	in_shd->actor_sz = sizeof(actor);
	in_shd->missive_sz = sizeof(missive);
	in_shd->missive_grp_sz = sizeof(missive_grp);

	init_class_names();

	bjk_separate(missive_grp, bj_sys_max_cores);

	bjk_enable_all_irq();
	bjk_global_irq_enable();
}

void 
add_out_missive(missive& msv1){
	binder * fst, * lst, * wrk;
	bjk_kernel_dat_st* ker = bjk_get_kernel_dat();

	fst = ker->out_work.bn_right;
	lst = &(ker->out_work);
	for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
		missive_grp* mgrp = (missive_grp*)wrk;
		missive* msv2 = (missive*)(mgrp->all_msv.get_right_pt());
		if(bj_addr_same_id(msv1.dst, msv2->dst)){
			mgrp->bind_to_my_left(*msv2);
		}
	}
	missive_grp* mgrp2 = missive_grp::acquire();
	mgrp2->bind_to_my_left(msv1);
	ker->out_work.bind_to_my_left(*mgrp2);
}

void 
call_handlers_of_group(missive_grp& mgrp){
	binder * fst, * lst, * wrk;
	bjk_kernel_dat_st* ker = bjk_get_kernel_dat();

	fst = mgrp.bn_right;
	lst = &mgrp;
	for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
		missive* remote_msv = (missive*)wrk;
		actor* dst = remote_msv->dst;
		bjk_handler_idx_t idx = dst->id_idx;
		if(bjk_is_valid_handler_idx(idx)){
			(*((ker->handlers_arr)[idx]))(remote_msv);
		}
	}
}

void 
actors_main_loop(){
	bjk_kernel_dat_st* ker = bjk_get_kernel_dat();
	
	while(true){
		binder * fst, * lst, * wrk, * nxt;

		fst = ker->in_work.bn_right;
		lst = &(ker->in_work);
		for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
			missive_ref* fst_ref = (missive_ref*)wrk;
			nxt = wrk->bn_right;

			missive_grp* remote_grp = (missive_grp*)(fst_ref->remote_grp);
			call_handlers_of_group(*remote_grp);
			fst_ref->remote_grp = bj_null;
			fst_ref->release();
		}

		fst = ker->local_work.bn_right;
		lst = &(ker->local_work);
		for(wrk = fst; wrk != lst; wrk = nxt){
			missive* fst_msg = (missive*)wrk;
			nxt = wrk->bn_right;

			actor* dst = fst_msg->dst;
			if(bjk_addr_is_local(dst)){
				if(bjk_is_valid_handler_idx(dst->id_idx)){
					(*((ker->handlers_arr)[dst->id_idx]))(fst_msg);
				}
				fst_msg->release();
			} else {
				fst_msg->let_go();
				add_out_missive(*fst_msg);
			}
		}

		fst = ker->out_work.bn_right;
		lst = &(ker->out_work);
		for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
			missive_grp* mgrp = (missive_grp*)wrk;
			nxt = wrk->bn_right;

			missive* msv = (missive*)(mgrp->all_msv.get_right_pt());
			bj_core_id_t dst_id = bj_addr_get_core_id(msv->dst);
			bj_core_nn_t idx = bj_id_to_nn(dst_id);
			void* loc_pt = &((ker->pw0_routed_arr)[idx]);
			missive_grp** rmt_pt = (missive_grp**)bj_addr_with(dst_id, loc_pt);

			*rmt_pt = mgrp;

			// send signal
		}
	}
}

void
wait_inited_state(bj_core_id_t dst_id){
	bj_in_core_st* in_shd = bjk_get_glb_in_core_shd();
	uint8_t* loc_st = &(in_shd->the_core_state);
	uint8_t* rmt_st = (uint8_t*)bj_addr_with(dst_id, loc_st);
	while(*rmt_st != bjk_inited_state);
}

//bj_opt_sz_fn
void
wait_value(uint32_t& var, uint32_t val){
	while(var < val);
}

bj_opt_sz_fn
uint32_t
wait_time(uint32_t max){
	uint32_t aa;
	for(aa = 0; aa < max; aa++){
		aa++;
	}
	return aa;
}

void
ck_sizes(){
	BJK_CK2(ck_sz1, (sizeof(void*) == sizeof(bj_addr_t)));
	BJK_CK2(ck_sz1, (sizeof(void*) == sizeof(unsigned)));
	BJK_CK2(ck_sz1, (sizeof(void*) == sizeof(uint32_t)));
}


uint32_t test_send_irq2 = 0;

void
cpp_main(){
	init_cpp_main();
	ck_sizes();

	bj_in_core_st* in_shd = bjk_get_glb_in_core_shd();
	in_shd->the_core_state = bjk_inited_state;

	test_send_irq2 = 0;
	//agent aa;
	
	if(bjk_is_core(0,0)){
		bjk_slog2("CORE (0,0) started\n");
		bj_core_id_t dst = bj_ro_co_to_id(0, 1);
		wait_inited_state(dst);
		bjk_slog2("CORE (0,0) SAW core (0,1) INITED\n");

		BJK_MARK_PLACE(START_UGLY_WAIT);
		//while(test_send_irq2 < 1){ bj_asm("nop"); }	
		//while(test_send_irq2 < 1);	
		//for(uint32_t aa = 0; aa < 1234567; aa++){ bj_asm("nop"); }
		//wait_time(123456789);
		wait_value(test_send_irq2, 4);
		BJK_MARK_PLACE(END_UGLY_WAIT);

		bjk_slog2("got_irq2="); bjk_ilog(test_send_irq2); bjk_slog2("\n");
	}
	if(bjk_is_core(0,1)){
		bjk_slog2("CORE (0,1) started\n");
		bj_core_id_t dst = bj_ro_co_to_id(0, 0);
		wait_inited_state(dst);
		bjk_slog2("CORE (0,1) SAW core (0,0) INITED\n");

		bjk_send_irq(dst, 2);
		bjk_send_irq(dst, 2);
		bjk_send_irq(dst, 2);
		bjk_send_irq(dst, 2);

		bjk_slog2("CORE (0,1) sent 2 irq2\n");
	}
	
}

void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq) {
	unsigned* ilatst = (unsigned*)bj_addr_with(koid, (void*) BJ_REG_ILATST);
	*ilatst = 1 << num_irq;
}

grip&	
agent::get_available(){
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpmf-conversions"
	bjk_abort((bj_addr_t)(void*)&agent::get_available, 0, bj_null);
	#pragma GCC diagnostic pop
	return *((grip*)bj_null);
}
