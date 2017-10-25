
#include "err_msgs.h"
#include "global.h"
#include "dyn_mem.h"

//include "link_syms_vals.h"

//======================================================================
// global funcs

//EPH_CODE(extern mc_addr_t LD_EXTERNAL_RAM_ORIG);

void 
mck_glb_init(bool is_host) {
	ZNQ_CODE(
		if(MC_EXTERNAL_RAM_LOAD_DATA.extnl_ram_orig == 0){
			mck_abort((mc_addr_t)mck_glb_init, "mck_glb_init. Use mc_host_init before.");
		}
	);
	mc_init_dyn_mem();

	// basic init
	mck_set_irq0_handler();
	EPH_CODE(mc_add_lk_syms());

	mck_glb_sys_st* glb_dat = MCK_FIRST_GLB_SYS;
	mc_memset((uint8_t*)glb_dat, 0, sizeof(mck_glb_sys_st));

	glb_dat->off_core_pt = mc_null;
	glb_dat->write_rrarray = mc_null;

	mc_sys_sz_st* sys_sz = MC_SYS_SZ;
	mc_init_glb_sys_sz(sys_sz);
	
	if(MCK_PT_EXTERNAL_HOST_DATA->magic_id != MC_MAGIC_ID){
		mck_abort((mc_addr_t)mck_glb_init, err_6);
	}

	MCK_PT_EXTERNAL_HOST_DATA->pt_this_from_eph = MCK_PT_EXTERNAL_HOST_DATA;	// should be same for all cores
	
	// glb_sys_sz init
	mc_core_id_t koid = mck_get_core_id();
	mc_memset((uint8_t*)sys_sz, 0, sizeof(mc_sys_sz_st));
	*sys_sz = MCK_PT_EXTERNAL_HOST_DATA->wrk_sys;

	// num_core init
	mc_core_nn_t num_core = mc_id_to_nn(koid);

	glb_dat->magic_id = MC_MAGIC_ID;
	glb_dat->dbg_stack_trace = mc_null;
	glb_dat->magic_end = MC_MAGIC_END;	
	glb_dat->znq_shd_mem_base = MCK_PT_EXTERNAL_HOST_DATA->znq_shared_mem_base;
	glb_dat->eph_shd_mem_base = MCK_PT_EXTERNAL_HOST_DATA->eph_shared_mem_base;
	glb_dat->the_core_id = koid;
	glb_dat->the_core_ro = mc_id_to_ro(koid);
	glb_dat->the_core_co = mc_id_to_co(koid);
	glb_dat->the_core_nn = num_core;
	glb_dat->current_module_addr = (mc_addr_t)mc_null;
	glb_dat->pt_core_kernel = mc_null;

	if(num_core < mc_out_num_cores){
		glb_dat->off_core_pt = &((MCK_PT_EXTERNAL_HOST_DATA->sys_cores)[num_core]);
		if((MCK_PT_EXTERNAL_HOST_DATA->sys_out_buffs)[num_core].magic_id != MC_MAGIC_ID){
			mck_abort((mc_addr_t)mck_glb_init, err_7);
		}

		mc_core_out_st* out_st = &((MCK_PT_EXTERNAL_HOST_DATA->sys_out_buffs)[num_core]);

		glb_dat->write_rrarray = &(out_st->wr_arr);
		mc_rr_init(glb_dat->write_rrarray, MC_OUT_BUFF_SZ, out_st->buff, 0);

		if(glb_dat->off_core_pt->magic_id != MC_MAGIC_ID){
			mck_abort((mc_addr_t)mck_glb_init, err_8);
		}

		// glb_dat->off_core_pt init	
		//mc_set_off_core_var(glb_dat->off_core_pt->magic_id, MC_MAGIC_ID);
		void* glb_dat_wid = (void*)mc_addr_set_id(koid, glb_dat);
		MC_MARK_USED(glb_dat_wid);

		mc_set_off_core_var(glb_dat->off_core_pt->ck_core_id, koid);
		mc_set_off_core_var(glb_dat->off_core_pt->core_data, glb_dat_wid);
		
		mck_set_finished(MC_NOT_FINISHED_VAL);
		mc_set_off_core_var(glb_dat->off_core_pt->is_waiting, MC_NOT_WAITING);
	}

	EPH_CODE(
		MCK_CK(glb_dat->eph_shd_mem_base == MC_VAL_EXTERNAL_RAM_ORIG)
		MCK_CK(glb_dat->znq_shd_mem_base != 0);
	)

	#if defined(MC_IS_EPH_CODE) && defined(MC_PLL_LOADING)
		mc_load_map();
	#endif

}

void 
mck_glb_finish(){
	mck_set_finished(MC_FINISHED_VAL);
}

void
mc_extnl_ram_load_data_fill(mc_link_syms_data_st* syms){
	mc_addr_t ex_orig = syms->extnl_ram_orig;
	syms->extnl_code_disp = syms->extnl_code_orig - ex_orig;
	syms->extnl_load_disp = syms->extnl_load_orig - ex_orig;
	syms->extnl_host_data_disp = syms->extnl_host_data_orig - ex_orig;
	syms->extnl_host_alloc_disp = syms->extnl_host_alloc_orig - ex_orig;
}


