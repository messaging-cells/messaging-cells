
#include "log.h"
#include "shared.h"
#include "global.h"

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

