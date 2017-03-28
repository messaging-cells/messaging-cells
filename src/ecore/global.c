
#include "global.h"

//======================================================================
// off chip shared memory

bj_off_sys_st BJK_OFF_CHIP_SHARED_MEM bj_shared_dram;


//======================================================================
// global funcs

void 
bjk_glb_init(void) {
	// basic init
	bjk_set_irq0_handler();

	bjk_glb_sys_st* glb_dat = bjk_get_glb_sys();
	bj_memset((uint8_t*)glb_dat, 0, sizeof(bjk_glb_sys_st));

	glb_dat->off_core_pt = bj_null;
	glb_dat->write_rrarray = 0x0;

	bj_sys_sz_st* sys_sz = bj_get_glb_sys_sz();
	bj_init_glb_sys_sz(sys_sz);
	
	if(BJK_OFF_CHIP_SHARED_MEM.magic_id != BJ_MAGIC_ID){
		bjk_abort((bj_addr_t)bjk_glb_init, 0, bj_null);
	}

	BJK_OFF_CHIP_SHARED_MEM.pt_this_from_eph = &BJK_OFF_CHIP_SHARED_MEM;	// should be same for all cores
	
	// glb_sys_sz init
	bj_core_id_t koid = bjk_get_core_id();
	bj_memset((uint8_t*)sys_sz, 0, sizeof(bj_sys_sz_st));
	*sys_sz = BJK_OFF_CHIP_SHARED_MEM.wrk_sys;

	// num_core init
	bj_core_nn_t num_core = bj_id_to_nn(koid);

	// in_shd init 
	bj_in_core_st* in_shd = bjk_get_glb_in_core_shd();
	bj_memset((uint8_t*)in_shd, 0, sizeof(bj_in_core_st));

	in_shd->magic_id = BJ_MAGIC_ID;
	in_shd->dbg_stack_trace = bj_null;
	in_shd->magic_end = BJ_MAGIC_END;	
	in_shd->the_core_id = koid;
	in_shd->the_core_ro = bj_id_to_ro(koid);
	in_shd->the_core_co = bj_id_to_co(koid);
	in_shd->the_core_nn = num_core;

	if(num_core < bj_out_num_cores){
		glb_dat->off_core_pt = &((BJK_OFF_CHIP_SHARED_MEM.sys_cores)[num_core]);
		if((BJK_OFF_CHIP_SHARED_MEM.sys_out_buffs)[num_core].magic_id != BJ_MAGIC_ID){
			bjk_abort((bj_addr_t)bjk_glb_init, 0, bj_null);
		}

		bj_core_out_st* out_st = &((BJK_OFF_CHIP_SHARED_MEM.sys_out_buffs)[num_core]);
		glb_dat->write_rrarray = &(out_st->wr_arr);
		bj_rr_init(glb_dat->write_rrarray, BJ_OUT_BUFF_SZ, out_st->buff, 0);

		if(glb_dat->off_core_pt->magic_id != BJ_MAGIC_ID){
			bjk_abort((bj_addr_t)bjk_glb_init, 0, bj_null);
		}

		// glb_dat->off_core_pt init	
		//bj_set_off_chip_var(glb_dat->off_core_pt->magic_id, BJ_MAGIC_ID);
		bj_set_off_chip_var(glb_dat->off_core_pt->ck_core_id, koid);
		bj_set_off_chip_var(glb_dat->off_core_pt->core_data, in_shd);
		
		bjk_set_finished(BJ_NOT_FINISHED_VAL);
		bj_set_off_chip_var(glb_dat->off_core_pt->is_waiting, BJ_NOT_WAITING);
	}
}

void 
bjk_glb_finish(){
	bjk_set_finished(BJ_FINISHED_VAL);
}

