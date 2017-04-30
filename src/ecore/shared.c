
#include "shared.h"

uint8_t*
bj_memset(uint8_t* dest, uint8_t val, bj_size_t sz){
	bj_size_t idx = 0;
	for(idx = 0; idx < sz; idx++){
		dest[idx] = val;
	}
	return dest;
}

uint8_t*
bj_memcpy(uint8_t* dest, const uint8_t* src, bj_size_t sz){
	bj_size_t idx = 0;
	for(idx = 0; idx < sz; idx++){
		dest[idx] = src[idx];
	}
	return dest;
}

uint8_t*
bj_memmove(uint8_t* dest, const uint8_t* src, bj_size_t sz){
	if (dest <= src){
		return bj_memcpy(dest, src, sz);
	}

	/* copy backwards, from end to beginning */
	src += sz;
	dest += sz;

	while (sz--){
		*--dest = *--src;
	}

	return dest;
}

uint16_t 
bj_strlen(char* str) {
	uint16_t sln = 0;
	if(str == bj_null){
		return 0;
	}
	while(str[sln] != '\0'){
		sln++;
	}
	return sln;
}

uint8_t 
bj_get_aligment(void* ptr){
	if(BJ_IS_ALIGNED_64(ptr)){
		return 64;
	}
	if(BJ_IS_ALIGNED_32(ptr)){
		return 32;
	}
	if(BJ_IS_ALIGNED_16(ptr)){
		return 16;
	}
	return 8;
}

void
bj_extnl_ram_load_data_fill(bj_link_syms_data_st* syms){
	bj_addr_t ex_orig = syms->extnl_ram_orig;
	syms->extnl_code_disp = syms->extnl_code_orig - ex_orig;
	syms->extnl_load_disp = syms->extnl_load_orig - ex_orig;
	syms->extnl_data_disp = syms->extnl_data_orig - ex_orig;
	syms->extnl_alloc_disp = syms->extnl_alloc_orig - ex_orig;
}

