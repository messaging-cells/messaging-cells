
#include "shared.h"

void 
bj_memset(uint8_t* bytes, uint8_t val, uint32_t sz){
	uint32_t idx = 0;
	for(idx = 0; idx < sz; idx++){
		bytes[idx] = val;
	}
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

