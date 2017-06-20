
#include "global.h"
#include "dyn_mem.h"

extern mspace mch_glb_mspace;

uint8_t* 
mc_malloc_impl(umm_size_t num_bytes){
	return (uint8_t*)mspace_malloc(mch_glb_mspace, num_bytes);
}

uint8_t* 
mc_realloc_impl(uint8_t* ptr, umm_size_t num_bytes){
	return (uint8_t*)mspace_realloc(mch_glb_mspace, ptr, num_bytes);
}

void 
mc_free_impl(uint8_t* ptr){
	mspace_free(mch_glb_mspace, ptr);
}

