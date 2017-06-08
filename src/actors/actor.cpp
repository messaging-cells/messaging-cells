
#ifdef BJ_IS_EMU_CODE
#include <sched.h>
#endif

#ifdef BJ_IS_ZNQ_CODE
#include <stdio.h>
#endif

#include <stddef.h>
#include "interruptions_eph.h"
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
	magic_id = BJ_MAGIC_ID;
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

	routed_from_host = bj_null;
	routed_ack_from_host = bjk_ready_ack;

	has_from_host_work = false;
	has_to_host_work = false;

	bj_init_arr_vals(kernel_class_names_arr_sz, class_names_arr, bj_null);

	bjk_set_class_name(agent);
	bjk_set_class_name(actor);
	bjk_set_class_name(missive);
	bjk_set_class_name(agent_ref);
	bjk_set_class_name(agent_grp);

	host_kernel = bj_null;

	first_actor = actor::acquire();
	//ZNQ_CODE(printf("INITED_first_actor = %p \n", first_actor));

	user_func = bj_null;
	user_data = bj_null;

	host_running = false;
	did_work = 0x80;
	exit_when_idle = false;

	end_magic_id = BJ_MAGIC_ID;
}

bool
bjk_ck_type_sizes(){
	EPH_CODE(
	BJK_CK(sizeof(void*) == sizeof(bj_addr_t));
	BJK_CK(sizeof(void*) == sizeof(unsigned));
	BJK_CK(sizeof(void*) == sizeof(uint32_t));
	);
	return true;
}

void	// static
kernel::init_sys(){
	bjk_glb_init();

	BJK_CK(bjk_ck_type_sizes());

	kernel* ker = BJK_FIRST_KERNEL;

	new (ker) kernel(); 

	ker->host_kernel = (kernel*)(BJK_PT_EXTERNAL_HOST_DATA->pt_host_kernel);

	bjk_glb_sys_st* in_shd = BJK_GLB_SYS;

	in_shd->binder_sz = sizeof(binder);
	in_shd->kernel_sz = sizeof(kernel);
	in_shd->agent_sz = sizeof(agent);
	in_shd->actor_sz = sizeof(actor);
	in_shd->missive_sz = sizeof(missive);
	in_shd->agent_ref_sz = sizeof(agent_ref);
	in_shd->agent_grp_sz = sizeof(agent_grp);
	in_shd->bjk_glb_sys_st_sz = sizeof(bjk_glb_sys_st);

	in_shd->pt_core_kernel = bj_null;

	bjk_enable_all_irq();
	bjk_global_irq_enable();
}

void // static
kernel::run_sys(){
	kernel* ker = BJK_KERNEL;
	
	if(! ker->is_host_kernel){
		BJK_GLB_SYS->pt_core_kernel = (void*)bj_addr_set_id(BJK_GLB_SYS->the_core_id, ker);
		BJK_GLB_SYS->inited_core = BJK_GLB_SYS->the_core_id;
	}
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
	BJK_PT_EXTERNAL_HOST_DATA->pt_host_kernel = (void*)bj_host_addr_to_core_addr((bj_addr_t)BJK_KERNEL);
	BJK_KERNEL->is_host_kernel = true;

	//ZNQ_CODE(printf("init_host_sys. BJK_KERNEL = %p \n", BJK_KERNEL));
	//ZNQ_CODE(printf("init_host_sys. pt_host_kernel = %p \n", BJK_PT_EXTERNAL_HOST_DATA->pt_host_kernel));
	//ZNQ_CODE(printf("init_host_sys. mg=%x emg=%x \n", BJK_KERNEL->magic_id, BJK_KERNEL->end_magic_id));
	//ZNQ_CODE(printf("init_host_sys. fst_act=%p \n", BJK_KERNEL->first_actor));
}

void // static
kernel::run_host_sys(){
	//ZNQ_CODE(printf("run_host_sys. fst_act=%p \n", BJK_KERNEL->first_actor));
	BJK_KERNEL->host_running = true;
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
kernel::add_out_missive(grip* out_wk, missive& msv1){
	binder * fst, * lst, * wrk;
	//kernel* ker = this;

	bool found_grp = false;

	fst = out_wk->bn_right;
	lst = out_wk;
	for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
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
	out_wk->bind_to_my_left(*mgrp2);
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
	if(! BJK_KERNEL->is_host_kernel){
		actor* loc_act = kernel::get_core_actor();
		if(dst_id == kernel::get_core_id()){
			return loc_act;
		}
		actor* rem_act = (actor*)bj_addr_set_id(dst_id, loc_act);
		return rem_act;
	}
	kernel* core_ker = kernel::get_core_kernel(dst_id);
	if(core_ker != bj_null){
		return core_ker->first_actor;
	}
	return bj_null;
}

actor* // static 
kernel::get_host_actor(){
	kernel* ker = BJK_KERNEL;
	if(ker->is_host_kernel){
		return ker->first_actor;
	} 
	return ker->host_kernel->first_actor;
}

void // static 
kernel::set_handlers(uint8_t tot_hdlrs, missive_handler_t* hdlrs){
	kernel* ker = BJK_KERNEL;
	ker->tot_handlers = tot_hdlrs;
	ker->all_handlers = hdlrs;
}

void 
kernel::process_signal(binder& in_wrk, int sz, missive_grp_t** arr, bjk_ack_t* acks){
	bj_core_nn_t dst_idx = get_core_nn();
	bool is_from_host = (arr == &routed_from_host);

	for(int aa = 0; aa < sz; aa++){
		missive_grp_t* glb_msv_grp = arr[aa];
		if(glb_msv_grp != bj_null){
			arr[aa] = bj_null;

			missive_ref_t* nw_ref = agent_ref::acquire();
			EMU_CK(nw_ref->is_alone());
			EMU_CK(nw_ref->glb_agent_ptr == bj_null);

			nw_ref->glb_agent_ptr = glb_msv_grp;
			in_wrk.bind_to_my_left(*nw_ref);

			bj_core_id_t src_id = bj_addr_get_id((bj_addr_t)(glb_msv_grp));
			EMU_CK_PRT((is_from_host || (aa == bj_id_to_nn(src_id))), "is_from_host = %d \n", is_from_host);

			bjk_ack_t* rem_dst_ack_pt;
			if(! is_host_kernel){
				bjk_ack_t* loc_dst_ack_pt = &(acks[dst_idx]);
				if(! is_from_host){
					rem_dst_ack_pt = (bjk_ack_t*)bj_addr_set_id(src_id, loc_dst_ack_pt);
				} else {
					rem_dst_ack_pt = loc_dst_ack_pt;
				}
			} else {
				EMU_CK(! is_from_host);
				kernel* core_ker = kernel::get_core_kernel(src_id);
				rem_dst_ack_pt = (bjk_ack_t*)(&(core_ker->routed_ack_from_host));
				//EMU_PRT("process_signal. rem_dst_ack_pt=%p\n", rem_dst_ack_pt);
				//ZNQ_CODE(printf("process_signal. rem_dst_ack_pt=%p \n", rem_dst_ack_pt));
			}

			//EMU_COND_PRT(is_from_host, "FLAG1_is_from_host = %d \n", is_from_host);

			EMU_CK(rem_dst_ack_pt != bj_null);
			EMU_CK(*rem_dst_ack_pt == bjk_busy_ack);
			*rem_dst_ack_pt = bjk_ready_ack;

			did_work |= 0x01;

			//EMU_COND_PRT(is_from_host, "FLAG2_is_from_host = %d \n", is_from_host);
		}
	}

	//ZNQ_CODE(printf("process_signal FLAG2\n"));
	//EMU_COND_PRT(is_from_host, "FLAG3_is_from_host = %d \n", is_from_host);
}

bool
bjk_is_inited(bj_core_id_t dst_id){
	bjk_glb_sys_st* in_shd = BJK_GLB_SYS;
	bj_core_id_t* loc_st = &(in_shd->inited_core);
	bj_core_id_t* rmt_st = (bj_core_id_t*)bj_addr_set_id(dst_id, loc_st);
	if((*rmt_st) != dst_id){
		return false;
	}
	return true;
}

void 
kernel::handle_missives(){
	kernel* ker = this;
	binder * fst, * lst, * wrk, * nxt;

	if(all_handlers == bj_null){
		bjk_slog2("ABORTING. MUST call kernel::set_handlers BEFORE kernel::run_sys. \n");
		EMU_PRT("ABORTING. MUST call kernel::set_handlers BEFORE kernel::run_sys. \n");
		bjk_abort((bj_addr_t)err_15, err_15);
		return;
	}

	for(int aa = 0; aa < kernel_signals_arr_sz; aa++){
		if(signals_arr[aa] == bj_true){
			signals_arr[aa] = bj_false;
			switch(aa){
				case bjk_do_pw0_routes_sgnl:
					process_signal(in_work, kernel_pw0_routed_arr_sz, pw0_routed_arr, pw0_routed_ack_arr);
					break;
				case bjk_do_pw2_routes_sgnl:
					process_signal(in_work, kernel_pw2_routed_arr_sz, pw2_routed_arr, pw2_routed_ack_arr);
					break;
				case bjk_do_pw4_routes_sgnl:
					process_signal(in_work, kernel_pw4_routed_arr_sz, pw4_routed_arr, pw4_routed_ack_arr);
					break;
				case bjk_do_pw6_routes_sgnl:
					process_signal(in_work, kernel_pw6_routed_arr_sz, pw6_routed_arr, pw6_routed_ack_arr);
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
	fst = in_grp->bn_right;
	lst = in_grp;
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_ref_t* fst_ref = (missive_ref_t*)wrk;
		nxt = wrk->bn_right;

		missive_grp_t* remote_grp = (missive_grp_t*)(fst_ref->glb_agent_ptr);

		//bjk_slog2("RECEIVING MISSIVE\n");
		//EMU_PRT("RECEIVING pt_msv_grp= %p\n", remote_grp);
		if(! is_host_kernel){ 
			call_handlers_of_group(remote_grp);
		} else {
			call_host_handlers_of_group(remote_grp);
		}

		fst_ref->release();
		EMU_CK(fst_ref->glb_agent_ptr == bj_null);
		did_work |= 0x02;
	}

	grip* out_msvs = &(ker->out_work);
	if(is_host_kernel){
		out_msvs = &(ker->to_cores_work);
	}

	fst = ker->local_work.bn_right;
	lst = &(ker->local_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive* fst_msg = (missive*)wrk;
		nxt = wrk->bn_right;

		actor* dst = fst_msg->dst;
		if(bj_addr_is_local(dst)){
			bjk_handle_missive(fst_msg);
			fst_msg->release();
		} else {
			add_out_missive(out_msvs, *fst_msg);
			EMU_CK(! fst_msg->is_alone());
		}
		did_work |= 0x04;
	}

	bj_core_nn_t src_idx = get_core_nn();

	EMU_CK(is_host_kernel || ker->to_cores_work.is_alone());
	if(is_host_kernel){
		EMU_CK(ker->out_work.is_alone());
		handle_work_to_cores();
	}

	fst = ker->out_work.bn_right;
	lst = &(ker->out_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_grp_t* mgrp = (missive_grp_t*)wrk;
		nxt = wrk->bn_right;

		EMU_CK(! is_host_kernel);
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

	fst = ker->sent_work.bn_right;
	lst = &(ker->sent_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_grp_t* mgrp = (missive_grp_t*)wrk;
		nxt = wrk->bn_right;

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

	fst = all_agts->bn_right;
	lst = all_agts;
	for(wrk = fst; wrk != lst; wrk = nxt){
		agent* agt = (agent*)wrk;
		nxt = wrk->bn_right;

		agt->release();
	}
}

void
actor::respond(missive* msv_orig, bjk_token_t tok){
	missive* msv = missive::acquire();
	msv->src = this;
	msv->dst = msv_orig->src;
	msv->tok = tok;
	msv->send();
}

void 
kernel::handle_work_to_cores(){
	EMU_CK(is_host_kernel);

	kernel* ker = this;
	binder * fst, * lst, * wrk, * nxt;

	fst = ker->to_cores_work.bn_right;
	lst = &(ker->to_cores_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_grp_t* mgrp = (missive_grp_t*)wrk;
		nxt = wrk->bn_right;

		EMU_CK(! mgrp->all_agts.is_alone());
		//ZNQ_CODE(printf("handle_work_to_cores. mgrp=%p &all_agts=%p \n", 
		//		mgrp, (binder*)(&(mgrp->all_agts)) ));
		
		missive* msv = (missive*)(mgrp->all_agts.get_right_pt());
		bj_core_id_t dst_id = bj_addr_get_id(msv->dst);
		bj_core_nn_t dst_idx = bj_id_to_nn(dst_id);

		// ONLY pw0 case
		bjk_ack_t& loc_dst_ack_pt = (ker->pw0_routed_ack_arr)[dst_idx];

		kernel* core_ker = kernel::get_core_kernel(dst_id);
		if(core_ker == bj_null){
			did_work |= 0x200;
			continue;
		}
		if(loc_dst_ack_pt == bjk_virgin_ack){
			// Have never sent missives
			if(core_ker == bj_null){
				did_work |= 0x400;
				continue;
			}
			loc_dst_ack_pt = bjk_ready_ack;
		}
		if(loc_dst_ack_pt != bjk_ready_ack){
			did_work |= 0x800;
			continue;
		}
		//EMU_PRT("kernel::handle_work_to_cores. loc_dst_ack_pt= %p \n", &loc_dst_ack_pt);
		loc_dst_ack_pt = bjk_busy_ack;

		missive_grp_t* glb_mgrp = (missive_grp_t*)bj_host_pt_to_core_pt(mgrp);

		EMU_CK(core_ker->routed_from_host == bj_null);
		core_ker->routed_from_host = glb_mgrp;

		// send signal
		core_ker->has_from_host_work = bj_true;

		mgrp->let_go();
		ker->sent_work.bind_to_my_left(*mgrp);
		did_work |= 0x20;

		//EMU_PRT("kernel::handle_work_to_cores. added to sent_work. \n");
	}
}

void 
kernel::handle_work_to_host(){
	BJK_CK(! is_host_kernel);
	BJK_CK(host_kernel != bj_null);
	BJK_CK(has_to_host_work);

	if(routed_ack_from_host != bjk_ready_ack){
		did_work |= 0x100;
		EMU_PRT("HOST NOT READY \n");
		return;
	}

	routed_ack_from_host = bjk_busy_ack;

	missive_grp_t* mgrp2 = agent_grp::acquire();
	EMU_CK(mgrp2 != bj_null);
	EMU_CK(mgrp2->all_agts.is_alone());

	mgrp2->all_agts.move_all_to_my_left(to_host_work);

	/*bjk_sprt2("SND_HOST fst_msv___");
	bjk_xprt((bj_addr_t)(mgrp2->all_agts.bn_right));
	bjk_sprt2("___\n");
	bjk_sprt2("SND_HOST handle_work_to_host SENDING MISSIVE\n");*/

	bj_core_nn_t src_idx = get_core_nn();
	missive_grp_t* glb_mgrp = (missive_grp_t*)bjk_as_glb_pt(mgrp2);

	(host_kernel->pw0_routed_arr)[src_idx] = glb_mgrp;

	// send signal
	host_kernel->signals_arr[bjk_do_pw0_routes_sgnl] = bj_true;

	sent_work.bind_to_my_left(*mgrp2);

	has_to_host_work = false;
}

void 
kernel::handle_host_missives(){
	//EMU_PRT("handle_host_missives ker=%p\n", this);
	BJK_CK(is_host_kernel);
	if(! host_running){
		return;
	}
	bool hdl = true;
	/*ZNQ_CODE(
		char buff[200];
		printf("handle_missives?\n");
		fgets(buff, 200, stdin);
		if(buff[0] != 'Y'){ hdl = false; }
	)*/
	
	if(hdl){	
		did_work = 0x0;
		handle_missives();
		if(user_func != bj_null){
			(* (user_func))();
		}
		if(! did_work && exit_when_idle){
			host_running = false;
		}
	}
}

void 
kernel::call_host_handlers_of_group(missive_grp_t* core_mgrp){
	EMU_CK(is_host_kernel);
	
	binder * fst, * lst, * wrk;

	bj_core_id_t msvs_id = bj_addr_get_id(core_mgrp);
	missive_grp_t* rem_mgrp = (missive_grp_t*)bj_core_pt_to_host_pt(core_mgrp);

	//binder* all_msvs = &(rem_mgrp->all_agts);
	binder* all_msvs = (binder*)(((uint8_t*)core_mgrp) + bj_offsetof(&missive_grp_t::all_agts));

	fst = bjh_glb_binder_get_rgt(all_msvs, msvs_id);
	lst = all_msvs;
	for(wrk = fst; wrk != lst; wrk = bjh_glb_binder_get_rgt(wrk, msvs_id)){
		missive* remote_msv = (missive*)(binder*)bj_core_pt_to_host_pt(wrk);

		actor* hdlr_dst = (remote_msv)->dst;
		EMU_CK(hdlr_dst != bj_null);

		bjk_handle_missive_base(remote_msv, hdlr_dst->handler_idx);
	}

	rem_mgrp->handled = bj_true;
	//ZNQ_CODE(printf("call_host_handlers_of_group. END. \n"));
}

void
kernel::handle_work_from_host(){
	BJK_CK(! is_host_kernel);
	BJK_CK(host_kernel != bj_null);
	BJK_CK(has_from_host_work);

	EMU_CK(from_host_work.is_alone());
	process_signal(from_host_work, 1, &routed_from_host, host_kernel->pw0_routed_ack_arr);
	EMU_CK(! from_host_work.is_alone());

	missive_ref_t* fst_ref = (missive_ref_t*)from_host_work.bn_right;
	fst_ref->let_go();
	EMU_CK(from_host_work.is_alone());

	missive_grp_t* host_mgrp = (missive_grp_t*)(fst_ref->glb_agent_ptr);

	binder * fst, * lst, * wrk;

	binder* all_msvs = &(host_mgrp->all_agts);

	//bjk_sprt2("handle_work_from_host. FLAG1 \n");

	fst = (binder*)bj_host_pt_to_core_pt(all_msvs->bn_right);
	lst = all_msvs;
	for(wrk = fst; wrk != lst; wrk = (binder*)bj_host_pt_to_core_pt(wrk->bn_right)){
		missive* remote_msv = (missive*)wrk;

		actor* hdlr_dst = (remote_msv)->dst;
		EMU_CK(hdlr_dst != bj_null);

		bjk_handle_missive_base(remote_msv, hdlr_dst->handler_idx);
	}

	host_mgrp->handled = bj_true;

	fst_ref->release();
	EMU_CK(fst_ref->glb_agent_ptr == bj_null);
	did_work |= 0x1000;

	has_from_host_work = false;

	//bjk_sprt2("handle_work_from_host. end_FLAG \n");
}

