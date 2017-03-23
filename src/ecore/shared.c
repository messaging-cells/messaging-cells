
#include "shared.h"

#ifdef IS_ZNQ_CODE
	#include <stdio.h>
	#include "booter.h"
	extern bj_off_sys_st* DBG_BASE;
#endif

#define NO_ZNQ_CODE(cod)

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
		NO_ZNQ_CODE(BJH_CK(DBG_BASE->magic_id == BJ_MAGIC_ID));
		dest[idx] = src[idx];
		NO_ZNQ_CODE(
			if(DBG_BASE->magic_id != BJ_MAGIC_ID){
				printf("dest=%p src=%p DBG_BASE=%p val=%d\n", &(dest[idx]), &(src[idx]), DBG_BASE, src[idx]);
			}
			BJH_CK(DBG_BASE->magic_id == BJ_MAGIC_ID);
		)
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

