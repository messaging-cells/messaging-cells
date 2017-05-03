
#include "global.h"
#include "dyn_mem.h"

uint8_t* 
bj_malloc_impl(umm_size_t num_bytes){
	return bj_null;
}

uint8_t* 
bj_realloc_impl(uint8_t* ptr, umm_size_t num_bytes){
	return bj_null;
}

void 
bj_free_impl(uint8_t* ptr){
}

