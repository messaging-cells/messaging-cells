
#include "interruptions.h"
#include "global.h"

//======================================================================
// off chip shared memory

bj_off_sys_st BJK_OFF_CHIP_SHARED_MEM bj_shared_dram;

//=====================================================================
// global data

bjk_glb_sys_st	bj_glb_sys_data;

//=====================================================================
// global funcs

#define BJ_B_OPCODE 0x000000e8 // OpCode of the B<*> instruction

#ifndef IS_EMU_CODE
void
abort(){	// Needed when optimizing for size
	BJK_CK2(ck2_abort, 0);
	bjk_abort((bj_addr_t)abort, 0, bj_null);
	while(1);
}
#endif	//IS_EMU_CODE

bjk_glb_sys_st*
bjk_get_glb_sys(){
	return &bj_glb_sys_data;
}

bj_sys_sz_st*
bj_get_glb_sys_sz(){
	return &(bjk_get_glb_sys()->sys_sz);
}

bj_in_core_st*
bjk_get_glb_in_core_shd(){
	return &(bjk_get_glb_sys()->in_core_shd);
}

void 
bjk_set_irq0_handler() bj_code_dram;
	
void 
bjk_set_irq0_handler(){
	unsigned * ivt = 0x0;
	*ivt = ((((unsigned)bjk_sync_handler) >> 1) << 8) | BJ_B_OPCODE;
}

void 
bjk_init_global(void) {
	// basic init
	bjk_set_irq0_handler();

	bjk_glb_sys_st* glb_dat = bjk_get_glb_sys();

	glb_dat->off_core_pt = 0x0;
	glb_dat->write_rrarray = 0x0;

	bj_sys_sz_st* sys_sz = bj_get_glb_sys_sz();
	bj_init_glb_sys_sz(sys_sz);
	
	if(BJK_OFF_CHIP_SHARED_MEM.magic_id != BJ_MAGIC_ID){
		bjk_abort((bj_addr_t)bjk_init_global, 0, bj_null);
	}
	
	// glb_sys_sz init
	bj_core_id_t koid = bjk_get_core_id();
	bj_memset((uint8_t*)sys_sz, 0, sizeof(bj_sys_sz_st));
	*sys_sz = BJK_OFF_CHIP_SHARED_MEM.wrk_sys;

	// num_core init
	bj_core_nn_t num_core = bj_id_to_nn(koid);
	glb_dat->off_core_pt = &((BJK_OFF_CHIP_SHARED_MEM.sys_cores)[num_core]);

	if((BJK_OFF_CHIP_SHARED_MEM.sys_out_buffs)[num_core].magic_id != BJ_MAGIC_ID){
		bjk_abort((bj_addr_t)bjk_init_global, 0, bj_null);
	}

	bj_core_out_st* out_st = &((BJK_OFF_CHIP_SHARED_MEM.sys_out_buffs)[num_core]);
	glb_dat->write_rrarray = &(out_st->wr_arr);
	bj_rr_init(glb_dat->write_rrarray, BJ_OUT_BUFF_SZ, out_st->buff, 0);
	
	if(glb_dat->off_core_pt->magic_id != BJ_MAGIC_ID){
		bjk_abort((bj_addr_t)bjk_init_global, 0, bj_null);
	}
	

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
	
	// glb_dat->off_core_pt init	
	//bj_set_off_chip_var(glb_dat->off_core_pt->magic_id, BJ_MAGIC_ID);
	bj_set_off_chip_var(glb_dat->off_core_pt->the_core_id, in_shd->the_core_id);
	bj_set_off_chip_var(glb_dat->off_core_pt->core_data, in_shd);
	
	bjk_set_finished(BJ_NOT_FINISHED_VAL);
	bj_set_off_chip_var(glb_dat->off_core_pt->is_waiting, BJ_NOT_WAITING);
}

void
bjk_aux_sout(char* msg, bj_out_type_t outt){ 
	uint8_t extra = 2;
	uint16_t oln = bj_strlen(msg);
	if(oln > (BJ_OUT_BUFF_MAX_OBJ_SZ - extra)){
		oln = (BJ_OUT_BUFF_MAX_OBJ_SZ - extra);
	}

	uint8_t* out_str = bjk_get_glb_sys()->dbg_out_str;
	bj_memcpy(out_str + extra, (uint8_t*)msg, oln);
	out_str[0] = outt;
	out_str[1] = BJ_CHR;
	bjk_glb_sys_st* glb_dat = bjk_get_glb_sys();
	uint16_t ow = bj_rr_write_obj(glb_dat->write_rrarray, oln + extra, out_str);
	while(ow == 0){
		bjk_wait_sync(BJ_WAITING_BUFFER, 0, bj_null);
		ow = bj_rr_write_obj(glb_dat->write_rrarray, oln + extra, out_str);
	}
}

void
bjk_aux_iout(uint32_t vv, bj_out_type_t outt, bj_type_t tt){
	uint16_t oln = 2 + sizeof(uint32_t);
	uint8_t msg[oln];
	msg[0] = outt;
	msg[1] = tt;
	uint8_t* pt = (uint8_t*)(&vv);
	msg[2] = pt[0];
	msg[3] = pt[1];
	msg[4] = pt[2];
	msg[5] = pt[3];
	bjk_glb_sys_st* glb_dat = bjk_get_glb_sys();
	uint16_t ow = bj_rr_write_obj(glb_dat->write_rrarray, oln, (uint8_t*)msg);
	while(ow == 0){
		bjk_wait_sync(BJ_WAITING_BUFFER, 0, bj_null);
		ow = bj_rr_write_obj(glb_dat->write_rrarray, oln, (uint8_t*)msg);
	}
}

