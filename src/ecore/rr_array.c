
#include "shared.h"
#include "rr_array.h"

//==============================================================================
// rrarray funcs

#define BJ_CRC16_POLY 0x8408

uint16_t 
bj_crc16(uint8_t *data_p, uint16_t length) bj_code_dram;

uint16_t 
bj_get_v16_of_p8(uint8_t* p8) bj_code_dram;

void
bj_set_v16_of_p8(uint8_t* p8, uint16_t v16) bj_code_dram;

uint16_t
bj_rr_get_v16(bj_rrarray_st* arr, uint8_t** pt_dat) bj_code_dram;

void
bj_rr_set_v16(bj_rrarray_st* arr, uint8_t** pt_dat, uint16_t v16) bj_code_dram;

uint16_t 
bj_crc16(uint8_t *data_p, uint16_t length){
	uint8_t ii;
	uint16_t data;
	uint16_t crc = 0xffff;

	if (length == 0) {
		return (~crc);
	}

	do{
		for (ii = 0, data = (uint16_t)0xff & *data_p++;
				ii < 8; 
				ii++, data >>= 1)
		{
				if ((crc & 0x0001) ^ (data & 0x0001)) {
					crc = (crc >> 1) ^ BJ_CRC16_POLY;
				} else { 
					crc >>= 1; 
				}
		}
	} while (--length);

	crc = ~crc;
	data = crc;
	crc = (crc << 8) | (data >> 8 & 0xff);

	return (crc);
}

uint16_t 
bj_get_v16_of_p8(uint8_t* p8){
	uint16_t v16 = p8[1];
	v16 <<= 8;
	v16 |= p8[0];
	return v16;
}

void
bj_set_v16_of_p8(uint8_t* p8, uint16_t v16){
	uint16_t low = v16 & 0x00ff;
	uint16_t hi = v16 & 0xff00;
	hi >>= 8;
	p8[1] = (uint8_t)hi;
	p8[0] = (uint8_t)low;
}

void
bj_rr_init(bj_rrarray_st* arr, uint32_t sz, uint8_t* dat, uint8_t reset){
	if(arr == bj_null){
		return;
	}
	set_off_chip_var(arr->magic_id, BJ_MAGIC_ID);
	set_off_chip_var(arr->data, dat);
	if(reset){
		bj_memset(arr->data, 0, sz);
	}
	
	set_off_chip_var(arr->end_data, (dat + sz));
	set_off_chip_var(arr->wr_obj, arr->data);
	set_off_chip_var(arr->rd_obj, arr->data);
	
	set_off_chip_var(arr->num_wr_errs, 0);
	set_off_chip_var(arr->wr_err, 0);
	set_off_chip_var(arr->rd_err, 0);
}

uint16_t
bj_rr_get_v16(bj_rrarray_st* arr, uint8_t** pt_dat){
	if(arr == bj_null){
		return 0;
	}
	uint8_t* dat = *pt_dat;
	uint8_t asz[2];
	int pos;
	for(pos = 0; pos < 2; pos++){
		if(dat == arr->end_data){
			dat = arr->data;
		}
		asz[pos] = *dat;
		dat++;
	}
	*pt_dat = dat;
	uint16_t osz = bj_get_v16_of_p8(asz);
	return osz;
}

void
bj_rr_set_v16(bj_rrarray_st* arr, uint8_t** pt_dat, uint16_t v16){
	if(arr == bj_null){
		return;
	}
	uint8_t* dat = *pt_dat;
	uint8_t asz[2];
	bj_set_v16_of_p8(asz, v16);
	int pos;
	for(pos = 0; pos < 2; pos++){
		if(dat == arr->end_data){
			dat = arr->data;
		}
		*dat = asz[pos];
		dat++;
	}
	*pt_dat = dat;
}

uint16_t
bj_rr_read_obj(bj_rrarray_st* arr, uint16_t obj_sz, uint8_t* obj){
	if(arr == bj_null){
		return 0;
	}
	uint8_t* dat = arr->rd_obj;
	uint16_t osz = bj_rr_get_v16(arr, &dat);
	if(osz == 0){
		set_off_chip_var(arr->rd_err, -1);
		return 0;
	}
	if(osz > obj_sz){
		set_off_chip_var(arr->rd_err, -2);
		return 0;
	}
	if(osz > (arr->end_data - arr->data)){
		set_off_chip_var(arr->rd_err, -3);
		return 0;
	}
	uint16_t ii;
	for(ii = 0; ii < osz; ii++){
		if(dat == arr->end_data){
			dat = arr->data;
		}
		obj[ii] = *dat;
		dat++;
	}
	uint16_t tcrc16 = bj_rr_get_v16(arr, &dat);
	uint16_t rcrc16 = bj_crc16(obj, osz);
	if(tcrc16 != rcrc16){
		set_off_chip_var(arr->rd_err, -4);
		return 0;
	}
	uint8_t* dat2 = arr->rd_obj;
	while(dat2 != dat){
		if(dat2 == arr->end_data){
			dat2 = arr->data;
		}
		(*dat2) = 0;
		dat2++;
	}
	set_off_chip_var(arr->rd_obj, dat2);
	return osz;
}

uint16_t
bj_rr_write_obj(bj_rrarray_st* arr, uint16_t obj_sz, uint8_t* obj){
	if(arr == bj_null){
		return 0;
	}
	uint32_t nme = arr->num_wr_errs;
	uint16_t osz = obj_sz;
	if(osz > ((arr->end_data - arr->data) - (2 * sizeof(uint16_t)))){
		set_off_chip_var(arr->wr_err, -1);
		nme++;
		set_off_chip_var(arr->num_wr_errs, nme);
		return 0;
	}
	if(osz <= 0){
		set_off_chip_var(arr->wr_err, -2);
		nme++;
		set_off_chip_var(arr->num_wr_errs, nme);
		return 0;
	}
	uint16_t w_sz = obj_sz + (3 * sizeof(uint16_t));
	uint8_t* dat2 = arr->wr_obj;
	for(; w_sz != 0; w_sz--){
		if(dat2 == arr->end_data){
			dat2 = arr->data;
		}
		if((*dat2) != 0){
			dat2 = 0;
			break;
		}
		dat2++;
	}
	if(dat2 == 0){
		set_off_chip_var(arr->wr_err, -3);
		nme++;
		set_off_chip_var(arr->num_wr_errs, nme);
		return 0;
	}
	uint8_t* dat = arr->wr_obj;
	bj_rr_set_v16(arr, &dat, obj_sz);
	uint16_t ii;
	for(ii = 0; ii < osz; ii++){
		if(dat == arr->end_data){
			dat = arr->data;
		}
		*dat = obj[ii];
		dat++;
	}
	uint16_t rcrc16 = bj_crc16(obj, osz);
	bj_rr_set_v16(arr, &dat, rcrc16);
	set_off_chip_var(arr->wr_obj, dat); 
	return osz;
}

