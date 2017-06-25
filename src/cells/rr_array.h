

#ifndef MC_RRARRAY_H
#define MC_RRARRAY_H

#include <inttypes.h>

#include "attribute.h"

#ifdef __cplusplus
mc_c_decl {
#endif

struct mc_aligned mc_rrarray_def { 
	uint32_t magic_id;
	uint8_t* data;
	uint8_t* end_data;
	uint8_t* wr_obj;
	uint8_t* rd_obj;
	
	uint32_t num_wr_errs;
	int8_t	 wr_err;
	int8_t	 rd_err;
};
typedef struct mc_rrarray_def mc_rrarray_st;

void
mc_rr_init(mc_rrarray_st* arr, uint16_t size, uint8_t* data, uint8_t reset) mc_external_code_ram;

uint16_t
mc_rr_read_obj(mc_rrarray_st* arr, uint16_t omc_sz, uint8_t* obj) mc_external_code_ram;

uint16_t
mc_rr_write_obj(mc_rrarray_st* arr, uint16_t omc_sz, uint8_t* obj) mc_external_code_ram;

#ifdef __cplusplus
}
#endif

#endif // MC_RRARRAY_H