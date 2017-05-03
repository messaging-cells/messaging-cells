
#include "global.h"

#include "thread_emu.hh"
#include "booter.h"
#include "dyn_mem.h"

#include "dlmalloc.h"

extern mspace bjm_glb_mspace;

uint8_t* 
bj_malloc_impl(umm_size_t num_bytes){
	if(bj_is_host_thread()){
		return (uint8_t*)mspace_malloc(bjm_glb_mspace, num_bytes);
	}
	return a64_malloc(num_bytes);
}

uint8_t* 
bj_realloc_impl(uint8_t* ptr, umm_size_t num_bytes){
	if(bj_is_host_thread()){
		return (uint8_t*)mspace_realloc(bjm_glb_mspace, ptr, num_bytes);
	}
	return a64_realloc(ptr, num_bytes);
}

void 
bj_free_impl(uint8_t* ptr){
	if(bj_is_host_thread()){
		mspace_free(bjm_glb_mspace, ptr);
	}
	a64_free(ptr);
}

