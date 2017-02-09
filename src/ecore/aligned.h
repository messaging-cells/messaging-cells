

/*************************************************************
aligned.h

Declaration of mem trace funcs and other.

--------------------------------------------------------------*/

#ifndef BJ_ALIGNED_H
#define BJ_ALIGNED_H

#include "umm_malloc.h"

/*
template <bool> struct ILLEGAL_USE_OF_OBJECT;
template <> struct ILLEGAL_USE_OF_OBJECT<true>{};
#define OBJECT_COPY_ERROR ILLEGAL_USE_OF_OBJECT<false>()
*/

//======================================================================
// aligned umm_malloc memory allocation 
//
// The following code depends on the umm_malloc implementation. 
// So, if you change allocator, you must change the code.


#define ceil_64(vv) (((vv % 8) == 0) ? (vv) : ((vv) + (8 - ((vv) % 8))))

#define umm_aligned_disp 4

template<class obj_t> static inline obj_t* 
a64_malloc(umm_size_t the_size = 1){
	umm_size_t mem_sz = ceil_64(the_size * sizeof(obj_t));
	uint8_t* tmp = (uint8_t*)umm_malloc(mem_sz);
	if(tmp != umm_null){
		tmp += umm_aligned_disp;
		BJK_CK(BJ_IS_ALIGNED_64(tmp));
	}
	return (obj_t*)tmp; 
}

template<class obj_t> static inline obj_t* 
a64_realloc(obj_t* ptr, umm_size_t the_size){
	umm_size_t mem_sz = ceil_64(the_size * sizeof(obj_t));
	void* umm_ptr = umm_null;
	if(ptr != umm_null){
		umm_ptr = (void*)(((uint8_t*)ptr) - umm_aligned_disp);
	}
	uint8_t* tmp = (uint8_t*)umm_realloc((void*)umm_ptr, mem_sz);
	if(tmp != umm_null){
		tmp += umm_aligned_disp;
		BJK_CK(BJ_IS_ALIGNED_64(tmp));
	}
	return (obj_t*)tmp; 
}

template<class obj_t> static inline void 
a64_free(obj_t*& ptr){
	if(ptr != umm_null){ 
		void* umm_ptr = (void*)(((uint8_t*)ptr) - umm_aligned_disp);
		umm_free(umm_ptr); 
		ptr = umm_null;
	}
}

#endif // BJ_ALIGNED_H


