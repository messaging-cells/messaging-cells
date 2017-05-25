
#ifdef BJ_IS_EMU_CODE
#include <sched.h>
#endif

#include "interruptions.h"
#include "err_msgs.h"
#include "actor.hh"

//----------------------------------------------------------------------------
// To FAKE std c++ lib initialization and destructions of global objects
// DO NOT FORGET to call initializers explicitly.

#ifdef BJ_IS_EPH_CODE

	bj_c_decl int __cxa_atexit(void* obj, void (*destruc) (void*), void* dso_hndl) bj_external_code_ram;

	int 
	__cxa_atexit(void* obj, void (*destruc) (void*), void* dso_hndl){
		static_cast<void>(obj);
		static_cast<void>(destruc);
		static_cast<void>(dso_hndl);
		return 0;
	}

	void* __dso_handle = bj_null;

#endif	//BJ_IS_EMU_CODE

//----------------------------------------------------------------------------

BJK_DEFINE_ACQUIRE_ALLOC(actor, 32)
BJK_DEFINE_ACQUIRE_ALLOC(missive, 32)
BJK_DEFINE_ACQUIRE_ALLOC(agent_ref, 32)
BJK_DEFINE_ACQUIRE_ALLOC(agent_grp, 32)

BJK_DEFINE_ACQUIRE(actor)
BJK_DEFINE_ACQUIRE(missive)
BJK_DEFINE_ACQUIRE(agent_ref)
BJK_DEFINE_ACQUIRE(agent_grp)

BJK_DEFINE_SEPARATE(actor)
BJK_DEFINE_SEPARATE(missive)
BJK_DEFINE_SEPARATE(agent_ref)
BJK_DEFINE_SEPARATE(agent_grp)

kernel::kernel(){
	init_kernel();
}

kernel::~kernel(){}

void
kernel::init_kernel(){
	is_host_kernel = false;

	tot_handlers = 0;
	all_handlers = bj_null;

	bj_init_arr_vals(kernel_signals_arr_sz, signals_arr, bj_false);

	bj_init_arr_vals(kernel_pw0_routed_arr_sz, pw0_routed_arr, bj_null);
	bj_init_arr_vals(kernel_pw2_routed_arr_sz, pw2_routed_arr, bj_null);
	bj_init_arr_vals(kernel_pw4_routed_arr_sz, pw4_routed_arr, bj_null);
	bj_init_arr_vals(kernel_pw6_routed_arr_sz, pw6_routed_arr, bj_null);

	bj_init_arr_vals(kernel_pw0_routed_arr_sz, pw0_routed_ack_arr, bjk_virgin_ack);
	bj_init_arr_vals(kernel_pw2_routed_arr_sz, pw2_routed_ack_arr, bjk_virgin_ack);
	bj_init_arr_vals(kernel_pw4_routed_arr_sz, pw4_routed_ack_arr, bjk_virgin_ack);
	bj_init_arr_vals(kernel_pw6_routed_arr_sz, pw6_routed_ack_arr, bjk_virgin_ack);

	bj_init_arr_vals(kernel_class_names_arr_sz, class_names_arr, bj_null);

	bjk_set_class_name(agent);
	bjk_set_class_name(actor);
	bjk_set_class_name(missive);
	bjk_set_class_name(agent_ref);
	bjk_set_class_name(agent_grp);

	host_kernel = bj_null;

	first_actor = actor::acquire();

	user_func = bj_null;
	user_data = bj_null;

	did_work = 0x80;
	exit_when_idle = false;
}

bool
bjk_ck_type_sizes(){
	EPH_CODE(
	BJK_CK2(ck_sz1, (sizeof(void*) == sizeof(bj_addr_t)));
	BJK_CK2(ck_sz1, (sizeof(void*) == sizeof(unsigned)));
	BJK_CK2(ck_sz1, (sizeof(void*) == sizeof(uint32_t)));
	);
	return true;
}

void	// static
kernel::init_sys(){
	bjk_glb_init();

	BJK_CK2(ck_szs, bjk_ck_type_sizes());

	kernel* ker = BJK_FIRST_KERNEL;

	new (ker) kernel(); 

	ker->host_kernel = (kernel*)(BJK_PT_EXTERNAL_DATA->pt_host_kernel);

	bjk_glb_sys_st* in_shd = BJK_GLB_SYS;

	in_shd->binder_sz = sizeof(binder);
	in_shd->kernel_sz = sizeof(kernel);
	in_shd->agent_sz = sizeof(agent);
	in_shd->actor_sz = sizeof(actor);
	in_shd->missive_sz = sizeof(missive);
	in_shd->agent_ref_sz = sizeof(agent_ref);
	in_shd->agent_grp_sz = sizeof(agent_grp);
	in_shd->bjk_glb_sys_st_sz = sizeof(bjk_glb_sys_st);

	in_shd->pt_kernel = ker;

	bjk_enable_all_irq();
	bjk_global_irq_enable();
}

void // static
kernel::run_sys(){
	kernel* ker = BJK_KERNEL;
	
	BJK_GLB_SYS->the_core_state = bjk_inited_state;
	while(true){
		ker->did_work = 0x0;
		ker->handle_missives();
		if(ker->user_func != bj_null){
			(* (ker->user_func))();
		}
		if(! ker->did_work && ker->exit_when_idle){
			break;
		}
		EMU_CODE(sched_yield());
	}
}

void	// static
kernel::finish_sys(){
	bjk_glb_finish();
}

void // static
kernel::init_host_sys(){
	bj_host_init();
	kernel::init_sys();
	BJK_PT_EXTERNAL_DATA->pt_host_kernel = (void*)bj_host_addr_to_core_addr((bj_addr_t)BJK_KERNEL);
	BJK_KERNEL->is_host_kernel = true;
}

void // static
kernel::run_host_sys(){
	bj_host_run();
}

void // static 
kernel::finish_host_sys(){
	kernel::finish_sys();
	bj_host_finish();
}

char*
agent::get_class_name(){
	kernel* ker = BJK_KERNEL;
	bjk_actor_id_t id = get_actor_id();
	if(bjk_is_valid_class_name_idx(id)){
		return (ker->class_names_arr)[id];
	}
	return bj_null;
}

void 
kernel::add_out_missive(missive& msv1){
	binder * fst, * lst, * wrk;
	kernel* ker = this;

	bool found_grp = false;

	fst = bjk_pt_to_binderpt(ker->out_work.bn_right);
	lst = &(ker->out_work);
	for(wrk = fst; wrk != lst; wrk = bjk_pt_to_binderpt(wrk->bn_right)){
		missive_grp_t* mgrp = (missive_grp_t*)wrk;
		missive* msv2 = (missive*)(mgrp->all_agts.get_right_pt());
		if(bj_addr_same_id(msv1.dst, msv2->dst)){
			msv1.let_go();
			mgrp->all_agts.bind_to_my_left(msv1);
			found_grp = true;
			break;
		}
	}
	if(found_grp){
		return;
	}

	missive_grp_t* mgrp2 = agent_grp::acquire();
	EMU_CK(mgrp2 != bj_null);
	EMU_CK(mgrp2->all_agts.is_alone());

	msv1.let_go();
	mgrp2->all_agts.bind_to_my_left(msv1);
	ker->out_work.bind_to_my_left(*mgrp2);
}

void 
kernel::call_handlers_of_group(missive_grp_t* rem_mgrp){
	binder * fst, * lst, * wrk;
	//kernel* ker = this;

	binder* all_msvs = &(rem_mgrp->all_agts);
	bj_core_id_t msvs_id = bj_addr_get_id(all_msvs);

	fst = bj_glb_binder_get_rgt(all_msvs, msvs_id);
	lst = all_msvs;
	for(wrk = fst; wrk != lst; wrk = bj_glb_binder_get_rgt(wrk, msvs_id)){
		missive* remote_msv = (missive*)wrk;

		bjk_handle_missive(remote_msv);
	}

	rem_mgrp->handled = bj_true;
}

grip&	
agent::get_available(){
	bjk_abort((bj_addr_t)err_9, err_9);
	return *((grip*)bj_null);
}

void
agent::init_me(int caller){
	bjk_abort((bj_addr_t)err_10, err_10);
}

actor*	//	static 
kernel::get_core_actor(bj_core_id_t dst_id){
	actor* loc_act = kernel::get_core_actor();
	if(dst_id == kernel::get_core_id()){
		return loc_act;
	}
	actor* rem_act = (actor*)bj_addr_set_id(dst_id, loc_act);
	return rem_act;
}

void // static 
kernel::set_handlers(uint8_t tot_hdlrs, missive_handler_t* hdlrs){
	kernel* ker = BJK_KERNEL;
	ker->tot_handlers = tot_hdlrs;
	ker->all_handlers = hdlrs;
}

void 
kernel::process_signal(int sz, missive_grp_t** arr, bjk_ack_t* acks){
	bj_core_nn_t dst_idx = get_core_nn();

	for(int aa = 0; aa < sz; aa++){
		missive_grp_t* glb_msv_grp = arr[aa];
		arr[aa] = bj_null;
		if(glb_msv_grp != bj_null){
			missive_ref_t* nw_ref = agent_ref::acquire();
			EMU_CK(nw_ref->is_alone());
			EMU_CK(nw_ref->glb_agent_ptr == bj_null);

			nw_ref->glb_agent_ptr = glb_msv_grp;
			in_work.bind_to_my_left(*nw_ref);

			bj_core_id_t src_id = bj_addr_get_id((bj_addr_t)(glb_msv_grp));
			bjk_ack_t* loc_dst_ack_pt = &(acks[dst_idx]);
			bjk_ack_t* rem_dst_ack_pt = (bjk_ack_t*)bj_addr_set_id(src_id, loc_dst_ack_pt);
			*rem_dst_ack_pt = bjk_ready_ack;

			did_work |= 0x01;
		}
	}
}

bool
bjk_is_inited(bj_core_id_t dst_id){
	bjk_glb_sys_st* in_shd = BJK_GLB_SYS;
	uint8_t* loc_st = &(in_shd->the_core_state);
	uint8_t* rmt_st = (uint8_t*)bj_addr_set_id(dst_id, loc_st);
	if((*rmt_st) != bjk_inited_state){
		return false;
	}
	return true;
}

void 
kernel::handle_missives(){
	kernel* ker = this;
	binder * fst, * lst, * wrk, * nxt;

	if(all_handlers == bj_null){
		return;
	}

	for(int aa = 0; aa < kernel_signals_arr_sz; aa++){
		if(signals_arr[aa] == bj_true){
			signals_arr[aa] = bj_false;
			switch(aa){
				case bjk_do_pw0_routes_sgnl:
					process_signal(kernel_pw0_routed_arr_sz, pw0_routed_arr, pw0_routed_ack_arr);
					break;
				case bjk_do_pw2_routes_sgnl:
					process_signal(kernel_pw2_routed_arr_sz, pw2_routed_arr, pw2_routed_ack_arr);
					break;
				case bjk_do_pw4_routes_sgnl:
					process_signal(kernel_pw4_routed_arr_sz, pw4_routed_arr, pw4_routed_ack_arr);
					break;
				case bjk_do_pw6_routes_sgnl:
					process_signal(kernel_pw6_routed_arr_sz, pw6_routed_arr, pw6_routed_ack_arr);
					break;
				default:
					break;
			}
		}
	}

	if(has_from_host_work){
		handle_work_from_host();
	}

	binder* in_grp = &(ker->in_work);
	fst = bjk_pt_to_binderpt(in_grp->bn_right);
	lst = in_grp;
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_ref_t* fst_ref = (missive_ref_t*)wrk;
		nxt = bjk_pt_to_binderpt(wrk->bn_right);

		missive_grp_t* remote_grp = (missive_grp_t*)(fst_ref->glb_agent_ptr);

		//bjk_slog2("RECEIVING MISSIVE\n");
		//EMU_PRT("RECEIVING pt_msv_grp= %p\n", remote_grp);

		call_handlers_of_group(remote_grp);
		fst_ref->release();
		EMU_CK(fst_ref->glb_agent_ptr == bj_null);
		did_work |= 0x02;
	}

	fst = bjk_pt_to_binderpt(ker->local_work.bn_right);
	lst = &(ker->local_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive* fst_msg = (missive*)wrk;
		nxt = bjk_pt_to_binderpt(wrk->bn_right);

		actor* dst = fst_msg->dst;
		if(bj_addr_is_local(dst)){
			bjk_handle_missive(fst_msg);
			fst_msg->release();
		} else {
			add_out_missive(*fst_msg);
			EMU_CK(! fst_msg->is_alone());
		}
		did_work |= 0x04;
	}

	bj_core_nn_t src_idx = get_core_nn();

	fst = bjk_pt_to_binderpt(ker->out_work.bn_right);
	lst = &(ker->out_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_grp_t* mgrp = (missive_grp_t*)wrk;
		nxt = bjk_pt_to_binderpt(wrk->bn_right);

		EMU_CK(! mgrp->all_agts.is_alone());
		
		missive* msv = (missive*)(mgrp->all_agts.get_right_pt());
		bj_core_id_t dst_id = bj_addr_get_id(msv->dst);
		bj_core_nn_t dst_idx = bj_id_to_nn(dst_id);

		// ONLY pw0 case
		bjk_ack_t& loc_dst_ack_pt = (ker->pw0_routed_ack_arr)[dst_idx];

		if(loc_dst_ack_pt == bjk_virgin_ack){
			// Have never sent missives
			if(! bjk_is_inited(dst_id)){
				did_work |= 0x08;
				continue;
			}
			loc_dst_ack_pt = bjk_ready_ack;
		}
		if(loc_dst_ack_pt != bjk_ready_ack){
			did_work |= 0x10;
			continue;
		}
		loc_dst_ack_pt = bjk_busy_ack;

		missive_grp_t** loc_src_pt = &((ker->pw0_routed_arr)[src_idx]);
		missive_grp_t** rmt_src_pt = (missive_grp_t**)bj_addr_set_id(dst_id, loc_src_pt);
		missive_grp_t* glb_mgrp = (missive_grp_t*)bjk_as_glb_pt(mgrp);

		//EMU_PRT("SENDING pt_msv_grp= %p right= %p\n", mgrp, mgrp->get_right_pt());

		EMU_CK(*rmt_src_pt == bj_null);
		*rmt_src_pt = glb_mgrp;

		// send signal
		bj_bool_t* loc_sg = &((ker->signals_arr)[bjk_do_pw0_routes_sgnl]);
		bj_bool_t* rmt_sg = (bj_bool_t*)bj_addr_set_id(dst_id, loc_sg);

		*rmt_sg = bj_true;

		mgrp->let_go();
		ker->sent_work.bind_to_my_left(*mgrp);
		did_work |= 0x20;
	}

	if(has_to_host_work){
		handle_work_to_host();
	}

	fst = bjk_pt_to_binderpt(ker->sent_work.bn_right);
	lst = &(ker->sent_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_grp_t* mgrp = (missive_grp_t*)wrk;
		nxt = bjk_pt_to_binderpt(wrk->bn_right);

		if(mgrp->handled){
			mgrp->release_all_agts();
			mgrp->release();
		}
		did_work |= 0x40;
	}
}

void
agent_grp::release_all_agts(){
	binder * fst, * lst, * wrk, * nxt;
	binder* all_agts = &(this->all_agts);

	fst = bjk_pt_to_binderpt(all_agts->bn_right);
	lst = all_agts;
	for(wrk = fst; wrk != lst; wrk = nxt){
		agent* agt = (agent*)wrk;
		nxt = bjk_pt_to_binderpt(wrk->bn_right);

		agt->release();
	}
}

void 
kernel::handle_host_missives(){
	if(! is_host_kernel){ return; }
}

void 
kernel::call_host_handlers_of_group(missive_grp_t* mgrp){
	if(! is_host_kernel){ return; }
}

void 
kernel::handle_work_from_host(){
	if(is_host_kernel){ return; }
	if(host_kernel == bj_null){ return; }
	if(! has_from_host_work){ return; }

	has_from_host_work = false;
}

void 
kernel::handle_work_to_host(){
	if(is_host_kernel){ return; }
	if(host_kernel == bj_null){ return; }
	if(! has_to_host_work){ return; }

	missive_grp_t* mgrp2 = agent_grp::acquire();
	EMU_CK(mgrp2 != bj_null);
	EMU_CK(mgrp2->all_agts.is_alone());

	mgrp2->all_agts.move_all_to_my_left(to_host_work);

	bj_core_nn_t src_idx = get_core_nn();
	missive_grp_t* glb_mgrp = (missive_grp_t*)bjk_as_glb_pt(mgrp2);

	(host_kernel->pw0_routed_arr)[src_idx] = glb_mgrp;

	// send signal
	host_kernel->signals_arr[bjk_do_pw0_routes_sgnl] = bj_true;

	sent_work.bind_to_my_left(*mgrp2);

	has_to_host_work = false;
}

void 
kernel::process_host_signal(int sz, missive_grp_t** arr){
	//bj_core_nn_t dst_idx = get_core_nn();

	/*
	for(int aa = 0; aa < sz; aa++){
		if(arr[aa] != bj_null){
			missive_ref_t* nw_ref = agent_ref::acquire();
			EMU_CK(nw_ref->is_alone());
			EMU_CK(nw_ref->glb_agent_ptr == bj_null);

			nw_ref->glb_agent_ptr = arr[aa];
			in_work.bind_to_my_left(*nw_ref);

			bj_core_id_t src_id = bj_addr_get_id((bj_addr_t)(arr[aa]));
			bjk_ack_t* loc_dst_ack_pt = &(acks[dst_idx]);
			bjk_ack_t* rem_dst_ack_pt = (bjk_ack_t*)bj_addr_set_id(src_id, loc_dst_ack_pt);
			*rem_dst_ack_pt = bjk_ready_ack;

			arr[aa] = bj_null;
		}
	}*/
}

void
actor::respond(missive* msv_orig, bjk_token_t tok){
	missive* msv = missive::acquire();
	msv->src = this;
	msv->dst = msv_orig->src;
	msv->tok = tok;
	msv->send();
}

