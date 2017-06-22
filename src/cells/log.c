
#include "log.h"
#include "shared.h"
#include "global.h"

void
mck_aux_sout(char* msg, mc_out_type_t outt){ 
	if(! mck_has_off_core){
		return;
	}

	uint8_t extra = 2;
	uint16_t oln = mc_strlen(msg);
	if(oln > (MC_MAX_STR_SZ - extra)){
		oln = (MC_MAX_STR_SZ - extra);
	}

	uint8_t* out_str = MC_CORE_INFO->dbg_out_str;
	mc_memcpy(out_str + extra, (uint8_t*)msg, oln);
	out_str[0] = outt;
	out_str[1] = MC_CHR;
	mck_glb_sys_st* glb_dat = MC_CORE_INFO;
	uint16_t ow = mc_rr_write_obj(glb_dat->write_rrarray, oln + extra, out_str);
	while(ow == 0){
		mck_wait_sync(MC_WAITING_BUFFER, 0, mc_null);
		ow = mc_rr_write_obj(glb_dat->write_rrarray, oln + extra, out_str);
	}
}

void
mck_aux_iout(uint32_t vv, mc_out_type_t outt, mc_type_t tt){
	if(! mck_has_off_core){
		return;
	}

	uint16_t oln = 2 + sizeof(uint32_t);
	uint8_t msg[oln];
	msg[0] = outt;
	msg[1] = tt;
	uint8_t* pt = (uint8_t*)(&vv);
	msg[2] = pt[0];
	msg[3] = pt[1];
	msg[4] = pt[2];
	msg[5] = pt[3];
	mck_glb_sys_st* glb_dat = MC_CORE_INFO;
	uint16_t ow = mc_rr_write_obj(glb_dat->write_rrarray, oln, (uint8_t*)msg);
	while(ow == 0){
		mck_wait_sync(MC_WAITING_BUFFER, 0, mc_null);
		ow = mc_rr_write_obj(glb_dat->write_rrarray, oln, (uint8_t*)msg);
	}
}

