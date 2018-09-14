

/*************************************************************

This file is part of messaging-cells.

messaging-cells is free software: you can redistribute it and/or modify
it under the terms of the version 3 of the GNU General Public 
License as published by the Free Software Foundation.

messaging-cells is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with messaging-cells.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------------

Copyright (C) 2017-2018. QUIROGA BELTRAN, Jose Luis.
Id (cedula): 79523732 de Bogota - Colombia.
See https://messaging-cells.github.io/

messaging-cells is free software thanks to The Glory of Our Lord 
	Yashua Melej Hamashiaj.
Our Resurrected and Living, both in Body and Spirit, 
	Prince of Peace.

------------------------------------------------------------*/


#ifdef MC_IS_PTD_CODE
#include <sched.h>
#endif

#ifdef MC_IS_ZNQ_CODE
#include <stdio.h>
#endif

#include <stddef.h>
#include "interruptions_eph.h"
#include "loader.h"
#include "cell.hh"

//----------------------------------------------------------------------------
// To FAKE std c++ lib initialization and destructions of global objects
// DO NOT FORGET to call initializers explicitly.

#ifdef MC_IS_EPH_CODE

	mc_c_decl int __cxa_atexit(void* obj, void (*destruc) (void*), void* dso_hndl) mc_external_code_ram;

	int 
	__cxa_atexit(void* obj, void (*destruc) (void*), void* dso_hndl){
		static_cast<void>(obj);
		static_cast<void>(destruc);
		static_cast<void>(dso_hndl);
		return 0;
	}

	void* __dso_handle = mc_null;

#endif	//MC_IS_PTD_CODE

//----------------------------------------------------------------------------

missive_handler_t mc_nil_handlers[1] = { mc_null };

MCK_DEFINE_MEM_METHODS(cell, 32, mck_all_available(cell), 0)
MCK_DEFINE_MEM_METHODS(missive, 32, mck_all_available(missive), 0)
MCK_DEFINE_MEM_METHODS(agent_ref, 32, mck_all_available(agent_ref), 0)
MCK_DEFINE_MEM_METHODS(agent_grp, 32, mck_all_available(agent_grp), 0)


kernel::kernel(){
	init_kernel();
}

kernel::~kernel(){}

void 
kernel::init_router_ack_arrays(){
	//PTD_PRT("kernel::init_router_ack_arrays\n");
	mc_init_arr_vals(kernel_pw0_routed_arr_sz, pw0_routed_ack_arr, mck_virgin_ack);
	mc_init_arr_vals(kernel_pw2_routed_arr_sz, pw2_routed_ack_arr, mck_virgin_ack);
	mc_init_arr_vals(kernel_pw4_routed_arr_sz, pw4_routed_ack_arr, mck_virgin_ack);
	mc_init_arr_vals(kernel_pw6_routed_arr_sz, pw6_routed_ack_arr, mck_virgin_ack);
}

void
kernel::init_kernel(){
	magic_id = MC_MAGIC_ID;
	is_manageru_kernel = false;

	tot_handlers = 0;
	all_handlers = mc_null;

	mc_init_arr_vals(kernel_signals_arr_sz, signals_arr, mc_false);

	mc_init_arr_vals(kernel_pw0_routed_arr_sz, pw0_routed_arr, mc_null);
	mc_init_arr_vals(kernel_pw2_routed_arr_sz, pw2_routed_arr, mc_null);
	mc_init_arr_vals(kernel_pw4_routed_arr_sz, pw4_routed_arr, mc_null);
	mc_init_arr_vals(kernel_pw6_routed_arr_sz, pw6_routed_arr, mc_null);

	init_router_ack_arrays();

	routed_from_manageru = mc_null;
	routed_ack_from_manageru = mck_ready_ack;

	has_from_manageru_work = false;
	has_to_manageru_work = false;

	mc_init_arr_vals(kernel_class_names_arr_sz, class_names_arr, mc_null);

	mck_set_class_name(agent);
	mck_set_class_name(cell);
	mck_set_class_name(missive);
	mck_set_class_name(agent_ref);
	mck_set_class_name(agent_grp);

	manageru_kernel = mc_null;

	PTD_CK(cell::get_curr_separate_sz() == 1);
	//PTD_PRT("CURR_SEP_SIZE=%u \n\n", cell::get_curr_separate_sz());
	first_cell = cell::acquire();
	//ZNQ_CODE(printf("INITED_first_cell = %p \n", first_cell));

	manageru_load_data = mc_null;

	user_func = mc_null;
	user_data = mc_null;

	manageru_running = false;
	did_work = mc_bit0;
	exit_when_idle = false;

	reset_stop_sys(); 

	end_magic_id = MC_MAGIC_ID;
}

bool
mck_ck_type_sizes(){
	EPH_CODE(
	MCK_CK(sizeof(void*) == sizeof(mc_addr_t));
	MCK_CK(sizeof(void*) == sizeof(unsigned));
	MCK_CK(sizeof(void*) == sizeof(uint32_t));
	);
	return true;
}

void	// static
kernel::init_sys(bool is_the_manageru){
	mck_glb_init(is_the_manageru);

	MCK_CK(mck_ck_type_sizes());

	kernel* ker = MCK_FIRST_KERNEL;

	new (ker) kernel(); 

	ker->manageru_kernel = (kernel*)(MCK_PT_EXTERNAL_MANAGERU_DATA->pt_manageru_kernel);
	if(ker->manageru_kernel != mc_null){
		ker->manageru_load_data = ker->manageru_kernel->manageru_load_data;
		//PTD_PRT("SETTING manageru_load_data = %p \n", ker->manageru_load_data);
	}

	mck_glb_sys_st* in_shd = MC_WORKERU_INFO;

	in_shd->pt_workeru_kernel = mc_null;

	mck_enable_all_irq();
	mck_global_irq_enable();
}

void // static
kernel::run_sys(){
	kernel* ker = MCK_KERNEL;
	
	if(! ker->is_manageru_kernel){
		ker->reset_stop_sys();
		MC_WORKERU_INFO->pt_workeru_kernel = (void*)mc_addr_set_id(MC_WORKERU_INFO->the_workeru_id, ker);
		MC_WORKERU_INFO->inited_workeru = MC_WORKERU_INFO->the_workeru_id;
		/*
		#ifdef MC_PLL_LOADING
			if(MC_WORKERU_INFO->the_workeru_nn == 0){
				mck_sprt2("INITED___"); 
				mck_xprt((mc_addr_t)(&(MC_WORKERU_INFO->inited_workeru)));
				mck_sprt2("___\n");
			}
		#endif
		*/
	}
	ker->exit_when_idle = false;
	while(true){
		ker->did_work = 0x0000;
		ker->handle_missives();
		if(! ker->did_work && ker->exit_when_idle){
			break;
		}
		PTD_CODE(sched_yield());
	}

	MC_WORKERU_INFO->inited_workeru = 0;

	ker->init_router_ack_arrays();
}

void	// static
kernel::finish_sys(){
	mck_glb_finish();
}

void // static
kernel::init_manageru_sys(){
	mc_manageru_init();
	kernel::init_sys(true);
	MCK_PT_EXTERNAL_MANAGERU_DATA->pt_manageru_kernel = (void*)mc_manageru_addr_to_workeru_addr((mc_addr_t)MCK_KERNEL);
	MCK_KERNEL->is_manageru_kernel = true;

	//ZNQ_CODE(printf("init_manageru_sys. MCK_KERNEL = %p \n", MCK_KERNEL));
	//ZNQ_CODE(printf("init_manageru_sys. pt_manageru_kernel = %p \n", MCK_PT_EXTERNAL_MANAGERU_DATA->pt_manageru_kernel));
	//ZNQ_CODE(printf("init_manageru_sys. mg=%x emg=%x \n", MCK_KERNEL->magic_id, MCK_KERNEL->end_magic_id));
	//ZNQ_CODE(printf("init_manageru_sys. fst_act=%p \n", MCK_KERNEL->first_cell));
}

void // static
kernel::run_manageru_sys(){
	//ZNQ_CODE(printf("run_manageru_sys. fst_act=%p \n", MCK_KERNEL->first_cell));
	MCK_KERNEL->manageru_running = true;
	mc_manageru_run();
}

void // static 
kernel::finish_manageru_sys(){
	kernel::finish_sys();
	mc_manageru_finish();
}

char*
agent::get_class_name(){
	kernel* ker = MCK_KERNEL;
	mck_cell_id_t id = get_cell_id();
	if(mck_is_valid_class_name_idx(id)){
		char* cnm = (ker->class_names_arr)[id];
		if(cnm == mc_null){
			return mc_cstr("NULL_CLASS_NAME");
		}
		return cnm;
	}
	return mc_cstr("INVALID_CLASS_NAME");
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
		if(mc_addr_same_id(msv1.dst, msv2->dst)){
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
	PTD_CK(mgrp2 != mc_null);
	PTD_CK(mgrp2->all_agts.is_alone());

	msv1.let_go();
	mgrp2->all_agts.bind_to_my_left(msv1);
	out_wk->bind_to_my_left(*mgrp2);
}

void 
kernel::call_handlers_of_group(missive_grp_t* rem_mgrp){
	binder * fst, * lst, * wrk;
	//kernel* ker = this;

	binder* all_msvs = &(rem_mgrp->all_agts);
	mc_workeru_id_t msvs_id = mc_addr_get_id(all_msvs);

	fst = mc_glb_binder_get_rgt(all_msvs, msvs_id);
	lst = all_msvs;
	for(wrk = fst; wrk != lst; wrk = mc_glb_binder_get_rgt(wrk, msvs_id)){
		missive* remote_msv = (missive*)wrk;

		mck_handle_missive(remote_msv);
	}

	rem_mgrp->handled = mc_true;
}

grip&	
agent::get_available(){
	mck_abort(__LINE__, MC_ABORT_MSG("Invalid agent::get_available func call\n"));
	return *((grip*)mc_null);
}

void
agent::init_me(int caller){
	mck_abort(__LINE__, MC_ABORT_MSG("Invalid agent::init_me func call\n"));
}

cell*	//	static 
kernel::get_first_cell(mc_workeru_id_t dst_id){
	if(! MCK_KERNEL->is_manageru_kernel){
		cell* loc_act = kernel::get_first_cell();
		if(dst_id == kernel::get_workeru_id()){
			return loc_act;
		}
		cell* rem_act = (cell*)mc_addr_set_id(dst_id, loc_act);
		return rem_act;
	}
	kernel* workeru_ker = kernel::get_workeru_kernel(dst_id);
	if(workeru_ker != mc_null){
		return workeru_ker->first_cell;
	}
	return mc_null;
}

cell* // static 
kernel::get_manageru_cell(){
	kernel* ker = MCK_KERNEL;
	if(ker->is_manageru_kernel){
		return ker->first_cell;
	} 
	return ker->manageru_kernel->first_cell;
}

void // static
kernel::fix_handlers(uint8_t tot_hdlrs, missive_handler_t* hdlrs){
	if(tot_hdlrs > 0){
		if(hdlrs == mc_null){
			mck_abort(__LINE__, 
				MC_ABORT_MSG("kernel::set_handlers. If (tot_hdlrs > 0) then hdlrs CAN NOT be mc_null. \n"));
		}
		if((hdlrs[0] != mc_null) && (hdlrs[0] != mc_kernel_handler)){
			//PTD_PRT("hdlrs[0] = %p \n", (void*)(hdlrs[0]));
			mck_abort(__LINE__, 
				MC_ABORT_MSG("kernel::set_handlers. If (tot_hdlrs > 0) then hdlrs[0] MUST be mc_null. \n"));
		}
		hdlrs[0] = mc_kernel_handler;
	}
}

void // static 
kernel::set_handlers(uint8_t tot_hdlrs, missive_handler_t* hdlrs){
	kernel* ker = MCK_KERNEL;
	kernel::fix_handlers(tot_hdlrs, hdlrs);
	ker->tot_handlers = tot_hdlrs;
	ker->all_handlers = hdlrs;
}

void 
kernel::process_signal(binder& in_wrk, int sz, missive_grp_t** arr, mck_ack_t* acks){
	mc_workeru_nn_t dst_idx = get_workeru_nn();
	bool is_from_manageru = (arr == &routed_from_manageru);

	for(int aa = 0; aa < sz; aa++){
		missive_grp_t* glb_msv_grp = arr[aa];
		if(glb_msv_grp != mc_null){
			arr[aa] = mc_null;

			missive_ref_t* nw_ref = agent_ref::acquire();
			PTD_CK(nw_ref->is_alone());
			PTD_CK(nw_ref->glb_agent_ptr == mc_null);

			nw_ref->glb_agent_ptr = glb_msv_grp;
			in_wrk.bind_to_my_left(*nw_ref);

			mc_workeru_id_t src_id = mc_addr_get_id((mc_addr_t)(glb_msv_grp));
			PTD_CK_PRT((is_from_manageru || (aa == mc_id_to_nn(src_id))), "is_from_manageru = %d \n", is_from_manageru);

			mck_ack_t* rem_dst_ack_pt;
			if(! is_manageru_kernel){
				mck_ack_t* loc_dst_ack_pt = &(acks[dst_idx]);
				if(! is_from_manageru){
					rem_dst_ack_pt = (mck_ack_t*)mc_addr_set_id(src_id, loc_dst_ack_pt);
				} else {
					rem_dst_ack_pt = loc_dst_ack_pt;
				}
			} else {
				PTD_CK(! is_from_manageru);
				kernel* workeru_ker = kernel::get_workeru_kernel(src_id);
				rem_dst_ack_pt = (mck_ack_t*)(&(workeru_ker->routed_ack_from_manageru));
				//PTD_PRT("process_signal. rem_dst_ack_pt=%p\n", rem_dst_ack_pt);
				//ZNQ_CODE(printf("process_signal. rem_dst_ack_pt=%p \n", rem_dst_ack_pt));
			}

			//PTD_COND_PRT(is_from_manageru, "FLAG1_is_from_manageru = %d \n", is_from_manageru);

			PTD_CK(rem_dst_ack_pt != mc_null);
			PTD_CK(*rem_dst_ack_pt == mck_busy_ack);
			*rem_dst_ack_pt = mck_ready_ack;

			did_work |= mc_bit1;

			//PTD_COND_PRT(is_from_manageru, "FLAG2_is_from_manageru = %d \n", is_from_manageru);
		}
	}

	//ZNQ_CODE(printf("process_signal FLAG2\n"));
	//PTD_COND_PRT(is_from_manageru, "FLAG3_is_from_manageru = %d \n", is_from_manageru);
}

bool
mck_has_same_module(mc_workeru_id_t dst_id){
	mck_glb_sys_st* in_shd = MC_WORKERU_INFO;
	mc_addr_t* loc_mdl = &(in_shd->current_module_addr);
	mc_addr_t* rmt_mdl = (mc_addr_t*)mc_addr_set_id(dst_id, loc_mdl);
	if((*rmt_mdl) != (*loc_mdl)){
		//PTD_PRT("DIFF_MODULES %s != %s \n", 
		//	(char*)(*loc_mdl), (char*)(*rmt_mdl));
		return false;
	}

	return true;
}

bool
mck_has_module(){
	mck_glb_sys_st* in_shd = MC_WORKERU_INFO;
	mc_addr_t* loc_mdl = &(in_shd->current_module_addr);
	return (loc_mdl != mc_null);
}

bool
mck_has_same_sub_module(mc_workeru_id_t dst_id){
	mck_glb_sys_st* in_shd = MC_WORKERU_INFO;
	uint8_t* loc_mdl = &(in_shd->current_sub_module_id);
	uint8_t* rmt_mdl = (uint8_t*)mc_addr_set_id(dst_id, loc_mdl);
	if((*rmt_mdl) != (*loc_mdl)){
		//PTD_PRT("DIFF_SUB_MODULES %d != %d \n", (*loc_mdl), (*rmt_mdl));
		return false;
	}

	return true;
}

bool
mck_is_id_inited(mc_workeru_id_t dst_id){
	mck_glb_sys_st* in_shd = MC_WORKERU_INFO;
	mc_workeru_id_t* loc_st = &(in_shd->inited_workeru);
	mc_workeru_id_t* rmt_st = (mc_workeru_id_t*)mc_addr_set_id(dst_id, loc_st);
	if((*rmt_st) != dst_id){
		return false;
	}

	return true;
}

#define MC_ERR_CELL_01 "ABORTING. MUST call 'kernel::set_handlers' BEFORE 'kernel::run_sys'. \n"

void 
kernel::handle_missives(){
	kernel* ker = this;
	binder * fst, * lst, * wrk, * nxt;

	if(all_handlers == mc_null){
		//mck_slog2(MC_ERR_CELL_01);
		//PTD_PRT(MC_ERR_CELL_01);
		mck_abort(__LINE__, MC_ABORT_MSG(MC_ERR_CELL_01));
		return;
	}

	for(int aa = 0; aa < kernel_signals_arr_sz; aa++){
		if(signals_arr[aa] == mc_true){
			signals_arr[aa] = mc_false;
			switch(aa){
				case mck_do_pw0_routes_sgnl:
					process_signal(in_work, kernel_pw0_routed_arr_sz, pw0_routed_arr, pw0_routed_ack_arr);
					break;
				case mck_do_pw2_routes_sgnl:
					process_signal(in_work, kernel_pw2_routed_arr_sz, pw2_routed_arr, pw2_routed_ack_arr);
					break;
				case mck_do_pw4_routes_sgnl:
					process_signal(in_work, kernel_pw4_routed_arr_sz, pw4_routed_arr, pw4_routed_ack_arr);
					break;
				case mck_do_pw6_routes_sgnl:
					process_signal(in_work, kernel_pw6_routed_arr_sz, pw6_routed_arr, pw6_routed_ack_arr);
					break;
				default:
					break;
			}
		}
	}

	if(has_from_manageru_work){
		handle_work_from_manageru();
	}

	binder* in_grp = &(ker->in_work);
	fst = in_grp->bn_right;
	lst = in_grp;
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_ref_t* fst_ref = (missive_ref_t*)wrk;
		nxt = wrk->bn_right;

		missive_grp_t* remote_grp = (missive_grp_t*)(fst_ref->glb_agent_ptr);

		//mck_slog2("RECEIVING MISSIVE\n");
		//PTD_PRT("RECEIVING pt_msv_grp= %p\n", remote_grp);
		if(! is_manageru_kernel){ 
			call_handlers_of_group(remote_grp);
		} else {
			call_manageru_handlers_of_group(remote_grp);
		}

		fst_ref->release(2);
		PTD_CK(fst_ref->glb_agent_ptr == mc_null);
		did_work |= mc_bit2;
	}

	grip* out_msvs = &(ker->out_work);
	if(is_manageru_kernel){
		out_msvs = &(ker->to_workerus_work);
	}

	fst = ker->local_work.bn_right;
	lst = &(ker->local_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive* fst_msg = (missive*)wrk;
		nxt = wrk->bn_right;

		cell* dst = fst_msg->dst;
		if(mc_addr_is_local(dst)){
			mck_handle_missive(fst_msg);
			fst_msg->release(3);
		} else {
			add_out_missive(out_msvs, *fst_msg);
			PTD_CK(! fst_msg->is_alone());
		}
		did_work |= mc_bit3;
	}

	mc_workeru_nn_t src_idx = get_workeru_nn();

	PTD_CK(is_manageru_kernel || ker->to_workerus_work.is_alone());
	if(is_manageru_kernel){
		PTD_CK(ker->out_work.is_alone());
		handle_work_to_workerus();
	}

	fst = ker->out_work.bn_right;
	lst = &(ker->out_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_grp_t* mgrp = (missive_grp_t*)wrk;
		nxt = wrk->bn_right;

		PTD_CK(! is_manageru_kernel);
		PTD_CK(! mgrp->all_agts.is_alone());
		
		missive* msv = (missive*)(mgrp->all_agts.get_right_pt());
		mc_workeru_id_t dst_id = mc_addr_get_id(msv->dst);
		mc_workeru_nn_t dst_idx = mc_id_to_nn(dst_id);

		// ONLY pw0 case
		mck_ack_t& loc_dst_ack_pt = (ker->pw0_routed_ack_arr)[dst_idx];

		if(loc_dst_ack_pt == mck_virgin_ack){
			// Have never sent missives
			if(! mck_is_id_inited(dst_id)){
				did_work |= mc_bit4;
				continue;
			}
			if(! mck_has_same_module(dst_id)){
				did_work |= mc_bit5;
				//PTD_PRT("SKIP msg %d => %d tok=%d \n", MC_WORKERU_INFO->the_workeru_nn, mc_id_to_nn(dst_id), msv->tok);
				continue;
			}
			if(mck_has_module() && ! mck_has_same_sub_module(dst_id)){
				did_work |= mc_bit6;
				//PTD_PRT("SKIP msg %d => %d tok=%d \n", MC_WORKERU_INFO->the_workeru_nn, mc_id_to_nn(dst_id), msv->tok);
				continue;
			}
			loc_dst_ack_pt = mck_ready_ack;
		}
		if(loc_dst_ack_pt != mck_ready_ack){
			did_work |= mc_bit7;
			continue;
		}
		loc_dst_ack_pt = mck_busy_ack;

		missive_grp_t** loc_src_pt = &((ker->pw0_routed_arr)[src_idx]);
		missive_grp_t** rmt_src_pt = (missive_grp_t**)mc_addr_set_id(dst_id, loc_src_pt);
		missive_grp_t* glb_mgrp = (missive_grp_t*)mck_as_glb_pt(mgrp);

		//PTD_PRT("SENDING pt_msv_grp= %p right= %p\n", mgrp, mgrp->get_right_pt());

		PTD_CK(*rmt_src_pt == mc_null);	
		*rmt_src_pt = glb_mgrp;

		// send signal
		mc_bool_t* loc_sg = &((ker->signals_arr)[mck_do_pw0_routes_sgnl]);
		mc_bool_t* rmt_sg = (mc_bool_t*)mc_addr_set_id(dst_id, loc_sg);

		*rmt_sg = mc_true;

		mgrp->let_go();
		ker->sent_work.bind_to_my_left(*mgrp);
		did_work |= mc_bit8;
	}

	if(has_to_manageru_work){
		handle_work_to_manageru();
	}

	fst = ker->sent_work.bn_right;
	lst = &(ker->sent_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_grp_t* mgrp = (missive_grp_t*)wrk;
		nxt = wrk->bn_right;

		if(mgrp->handled){
			mgrp->release_all_agts();
			mgrp->release(4);
		}
		did_work |= mc_bit9;
	}

	if(ker->user_func != mc_null){
		(* (ker->user_func))();
	}

	if(ker->stop_key != 0){
		ker->handle_stop();
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

		agt->release(5);
	}
}

void
cell::send(cell* des, mck_token_t tok){
	missive* msv = missive::acquire();
	msv->src = this;
	msv->dst = des;
	msv->tok = tok;
	msv->send();
}

void
cell::respond(missive* msv_orig, mck_token_t tok){
	missive* msv = missive::acquire();
	msv->src = this;
	msv->dst = msv_orig->src;
	msv->tok = tok;
	msv->send();
}

void 
kernel::handle_work_to_workerus(){
	PTD_CK(is_manageru_kernel);

	kernel* ker = this;
	binder * fst, * lst, * wrk, * nxt;

	fst = ker->to_workerus_work.bn_right;
	lst = &(ker->to_workerus_work);
	for(wrk = fst; wrk != lst; wrk = nxt){
		missive_grp_t* mgrp = (missive_grp_t*)wrk;
		nxt = wrk->bn_right;

		PTD_CK(! mgrp->all_agts.is_alone());
		//ZNQ_CODE(printf("handle_work_to_workerus. mgrp=%p &all_agts=%p \n", 
		//		mgrp, (binder*)(&(mgrp->all_agts)) ));
		
		missive* msv = (missive*)(mgrp->all_agts.get_right_pt());
		mc_workeru_id_t dst_id = mc_addr_get_id(msv->dst);
		mc_workeru_nn_t dst_idx = mc_id_to_nn(dst_id);

		// ONLY pw0 case
		mck_ack_t& loc_dst_ack_pt = (ker->pw0_routed_ack_arr)[dst_idx];

		kernel* workeru_ker = kernel::get_workeru_kernel(dst_id);
		if(workeru_ker == mc_null){
			did_work |= mc_bit10;
			continue;
		}
		if(loc_dst_ack_pt == mck_virgin_ack){
			// Have never sent missives
			if(workeru_ker == mc_null){
				did_work |= mc_bit11;
				continue;
			}
			loc_dst_ack_pt = mck_ready_ack;
		}
		if(loc_dst_ack_pt != mck_ready_ack){
			did_work |= mc_bit12;
			continue;
		}
		//PTD_PRT("kernel::handle_work_to_workerus. loc_dst_ack_pt= %p \n", &loc_dst_ack_pt);
		loc_dst_ack_pt = mck_busy_ack;

		missive_grp_t* glb_mgrp = (missive_grp_t*)mc_manageru_pt_to_workeru_pt(mgrp);

		PTD_CK(workeru_ker->routed_from_manageru == mc_null);
		workeru_ker->routed_from_manageru = glb_mgrp;

		// send signal
		workeru_ker->has_from_manageru_work = mc_true;

		mgrp->let_go();
		ker->sent_work.bind_to_my_left(*mgrp);
		did_work |= mc_bit13;

		//PTD_PRT("kernel::handle_work_to_workerus. added to sent_work. \n");
	}
}

void 
kernel::handle_work_to_manageru(){
	MCK_CK(! is_manageru_kernel);
	MCK_CK(manageru_kernel != mc_null);
	MCK_CK(has_to_manageru_work);

	if(routed_ack_from_manageru != mck_ready_ack){
		did_work |= mc_bit14;
		//PTD_PRT("MANAGERU NOT READY \n");
		return;
	}

	routed_ack_from_manageru = mck_busy_ack;

	missive_grp_t* mgrp2 = agent_grp::acquire();
	PTD_CK(mgrp2 != mc_null);
	PTD_CK(mgrp2->all_agts.is_alone());

	mgrp2->all_agts.move_all_to_my_left(to_manageru_work);

	/*mck_sprt2("SND_MANAGERU fst_msv___");
	mck_xprt((mc_addr_t)(mgrp2->all_agts.bn_right));
	mck_sprt2("___\n");
	mck_sprt2("SND_MANAGERU handle_work_to_manageru SENDING MISSIVE\n");*/

	mc_workeru_nn_t src_idx = get_workeru_nn();
	missive_grp_t* glb_mgrp = (missive_grp_t*)mck_as_glb_pt(mgrp2);

	(manageru_kernel->pw0_routed_arr)[src_idx] = glb_mgrp;

	// send signal
	manageru_kernel->signals_arr[mck_do_pw0_routes_sgnl] = mc_true;

	sent_work.bind_to_my_left(*mgrp2);

	has_to_manageru_work = false;
}

void 
kernel::handle_manageru_missives(){
	//PTD_PRT("handle_manageru_missives ker=%p\n", this);
	MCK_CK(is_manageru_kernel);
	if(! manageru_running){
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
		did_work = 0x0000;
		handle_missives();
		if(! did_work && exit_when_idle){
			manageru_running = false;
		}
	}
}

void 
kernel::call_manageru_handlers_of_group(missive_grp_t* workeru_mgrp){
	PTD_CK(is_manageru_kernel);
	
	binder * fst, * lst, * wrk;

	mc_workeru_id_t msvs_id = mc_addr_get_id(workeru_mgrp);
	missive_grp_t* rem_mgrp = (missive_grp_t*)mc_workeru_pt_to_manageru_pt(workeru_mgrp);

	//binder* all_msvs = &(rem_mgrp->all_agts);
	binder* all_msvs = (binder*)(((uint8_t*)workeru_mgrp) + mc_offsetof(&missive_grp_t::all_agts));

	fst = mch_glb_binder_get_rgt(all_msvs, msvs_id);
	lst = all_msvs;
	for(wrk = fst; wrk != lst; wrk = mch_glb_binder_get_rgt(wrk, msvs_id)){
		missive* remote_msv = (missive*)(binder*)mc_workeru_pt_to_manageru_pt(wrk);

		cell* hdlr_dst = (remote_msv)->dst;
		PTD_CK(hdlr_dst != mc_null);

		mck_handle_missive_base(remote_msv, hdlr_dst->handler_idx);
	}

	rem_mgrp->handled = mc_true;
	//ZNQ_CODE(printf("call_manageru_handlers_of_group. END. \n"));
}

void
kernel::handle_work_from_manageru(){
	MCK_CK(! is_manageru_kernel);
	MCK_CK(manageru_kernel != mc_null);
	MCK_CK(has_from_manageru_work);

	PTD_CK(from_manageru_work.is_alone());
	process_signal(from_manageru_work, 1, &routed_from_manageru, manageru_kernel->pw0_routed_ack_arr);
	PTD_CK(! from_manageru_work.is_alone());

	missive_ref_t* fst_ref = (missive_ref_t*)from_manageru_work.bn_right;
	fst_ref->let_go();
	PTD_CK(from_manageru_work.is_alone());

	missive_grp_t* manageru_mgrp = (missive_grp_t*)(fst_ref->glb_agent_ptr);

	binder * fst, * lst, * wrk;

	binder* all_msvs = &(manageru_mgrp->all_agts);

	//mck_sprt2("handle_work_from_manageru. FLAG1 \n");

	fst = (binder*)mc_manageru_pt_to_workeru_pt(all_msvs->bn_right);
	lst = all_msvs;
	for(wrk = fst; wrk != lst; wrk = (binder*)mc_manageru_pt_to_workeru_pt(wrk->bn_right)){
		missive* remote_msv = (missive*)wrk;

		cell* hdlr_dst = (remote_msv)->dst;
		PTD_CK(hdlr_dst != mc_null);

		mck_handle_missive_base(remote_msv, hdlr_dst->handler_idx);
	}

	manageru_mgrp->handled = mc_true;

	fst_ref->release(6);
	PTD_CK(fst_ref->glb_agent_ptr == mc_null);
	did_work |= mc_bit15;

	has_from_manageru_work = false;

	//mck_sprt2("handle_work_from_manageru. end_FLAG \n");
}

void 
mc_kernel_handler(missive* msv) {
	kernel* ker = MCK_KERNEL;
	ker->kernel_first_cell_msv_handler(msv);
}

void // static
kernel::stop_sys(mck_token_t key){
	kernel* ker = MCK_KERNEL;
	if(key == 0){ 
		mck_abort(__LINE__, MC_ABORT_MSG("kernel::stop_sys. Invalid stop zero key.\n"));
	}
	if(ker->stop_key != 0){ 
		if(ker->stop_key != key){
			mck_abort(__LINE__, MC_ABORT_MSG("kernel::stop_sys. Already stopping with different key.\n"));
		}
		return; 
	}
	if((ker->rcvd_stop_key != 0) && (ker->rcvd_stop_key != key)){ 
		mck_abort(__LINE__, MC_ABORT_MSG("kernel::stop_sys. Already received different stop key.\n"));
	}

	ker->stop_key = key;

	//PTD_PRT("START_STOP_WORKERU=%d \n", ker->get_workeru_nn());
}

void 
kernel::send_stop_to_children(){
	//mck_slog2("send_stop_to_children\n");

	//reset_stop_sys();

	mc_load_map_st* mp = mc_map_get_loaded();

	//PTD_PRT("STOP_CHILDREN WORKERU=%d \n", get_workeru_nn());

	if(mp->childs != mc_null){ 
		int aa = 0;
		mc_load_map_st* ch_map = (mp->childs)[aa];
		while(ch_map != mc_null){
			//PTD_PRT("send_stop to CHILD=%d \n", ch_map->num_workeru);
			mc_workeru_nn_t chd_nn = ch_map->num_workeru;
			cell* ch_cell = get_first_cell(mc_nn_to_id(chd_nn));

			//PTD_PRT_STACK(true, "mck_tok_stop_sys_to_children WORKERU=%d \n", get_workeru_nn());

			missive* msv = missive::acquire();
			msv->src = get_first_cell();
			msv->dst = ch_cell;
			msv->tok = mck_tok_stop_sys_to_children;
			msv->send();

			aa++;
			ch_map = (mp->childs)[aa];
		}
	}

	set_idle_exit();
}

void 
kernel::handle_stop(){
	PTD_CK(stop_key != 0);
	mc_workeru_nn_t tot_child = mc_map_get_tot_children();
	//PTD_CK((tot_child == 0) == ());
	if(! sent_stop_to_parent && (num_childs_stopping == tot_child)){
		//PTD_PRT("SENDING STOP TO PARENT WORKERU=%d TOT_CHLD=%d \n", get_workeru_nn(), tot_child);

		if(user_stop_func != mc_null){
			(*user_stop_func)();
		}
		sent_stop_to_parent = true;
		mc_workeru_id_t pnt_koid = mc_map_get_parent_workeru_id();
		if(pnt_koid != 0){
			cell* pcell = get_first_cell(pnt_koid);

			missive* msv = missive::acquire();
			msv->src = get_first_cell();
			msv->dst = pcell;
			msv->tok = mck_tok_stop_sys_to_parent;
			msv->send();
		} else {
			send_stop_to_children();
		}
	}
}

void 
kernel::kernel_first_cell_msv_handler(missive* msv){
	kernel_tok_t tok = (kernel_tok_t)msv->tok;

	switch(tok){
		case mck_tok_stop_sys_to_parent:
		{
			cell* msv_src = msv->src;
			mc_workeru_id_t src_id = mc_addr_get_id(msv_src);
			kernel* ker = MCK_KERNEL;
			kernel* rem_ker = (kernel*)mc_addr_set_id(src_id, ker);

			//PTD_PRT("GOT_STOP PARENT FROM WORKERU=%d \n", mc_id_to_nn(src_id));

			mck_token_t rem_key = rem_ker->stop_key;
			if(rcvd_stop_key == 0){
				rcvd_stop_key = rem_key;
			}
			if(rcvd_stop_key != rem_key){
				mck_abort(__LINE__, 
					MC_ABORT_MSG("kernel::kernel_first_cell_msv_handler. Inconsistent received sotp key.\n"));
			}

			num_childs_stopping++;
		}
		break;
		case mck_tok_stop_sys_to_children:
			send_stop_to_children();
		break;
		default:
			mck_abort(__LINE__, 
				MC_ABORT_MSG("kernel::kernel_first_cell_msv_handler. Invalid kernel tok.\n"));
		break;
	}
}

void
kernel::dbg_set_idle(){
	//PTD_PRT_STACK(true, "CALLING kernel::set_idle_exit");
}

