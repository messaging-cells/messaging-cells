
#include "dyn_mem.h"
#include "global.h"

uint8_t* 
a64_malloc(umm_size_t num_bytes){
	umm_size_t mem_sz = ceil_64(num_bytes);
	uint8_t* tmp = (uint8_t*)umm_malloc(mem_sz);
	if(tmp != umm_null){
		tmp += umm_aligned_disp;
		BJK_CK(MC_IS_ALIGNED_64(tmp));
	}
	return tmp; 
}

uint8_t* 
a64_realloc(uint8_t* ptr, umm_size_t num_bytes){
	umm_size_t mem_sz = ceil_64(num_bytes);
	void* umm_ptr = umm_null;
	if(ptr != umm_null){
		umm_ptr = (void*)(((uint8_t*)ptr) - umm_aligned_disp);
	}
	uint8_t* tmp = (uint8_t*)umm_realloc((void*)umm_ptr, mem_sz);
	if(tmp != umm_null){
		tmp += umm_aligned_disp;
		BJK_CK(MC_IS_ALIGNED_64(tmp));
	}
	return tmp; 
}

void 
a64_free(uint8_t* ptr){
	if(ptr != umm_null){ 
		void* umm_ptr = (void*)(((uint8_t*)ptr) - umm_aligned_disp);
		umm_free(umm_ptr); 
		//ptr = umm_null;
	}
}

