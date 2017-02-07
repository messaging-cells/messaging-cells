

#ifndef BJ_RRARRAY_H
#define BJ_RRARRAY_H

#include <inttypes.h>

#include "attribute.h"

#ifdef __cplusplus
extern "C" {
#endif

struct bj_align(8) bj_rrarray_def { 
	uint32_t magic_id;
	uint8_t* data;
	uint8_t* end_data;
	uint8_t* wr_obj;
	uint8_t* rd_obj;
	
	uint32_t num_wr_errs;
	int8_t	 wr_err;
	int8_t	 rd_err;
};
typedef struct bj_rrarray_def bj_rrarray_st;

void
bj_rr_init(bj_rrarray_st* arr, uint16_t size, uint8_t* data, uint8_t reset) bj_code_dram;

uint16_t
bj_rr_read_obj(bj_rrarray_st* arr, uint16_t obj_sz, uint8_t* obj) bj_code_dram;

uint16_t
bj_rr_write_obj(bj_rrarray_st* arr, uint16_t obj_sz, uint8_t* obj) bj_code_dram;

#ifdef __cplusplus
}
#endif

#endif // BJ_RRARRAY_H
