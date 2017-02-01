
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

