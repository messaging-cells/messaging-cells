

/*************************************************************
dyn_mem.hh

Declaration of dynamic mem funcs.

--------------------------------------------------------------*/

#ifndef BJ_DYN_MEM_HH
#define BJ_DYN_MEM_HH

#ifdef __cplusplus
extern "C" {
#endif

#include "umm_malloc.h"

//======================================================================
// aligned umm_malloc memory allocation 
//
// The following code depends on the umm_malloc implementation. 
// So, if you change allocator, you must change the code.

// the umm implementation already is 32 bit aligned

#define a32_malloc(size) umm_malloc(size)
#define a32_realloc(ptr, size) umm_realloc((ptr), (size))
#define a32_free(ptr) umm_free(ptr)

#define ceil_64(vv) (((vv % 8) == 0) ? (vv) : ((vv) + (8 - ((vv) % 8))))

#define umm_aligned_disp 4

bj_opt_sz_fn uint8_t* 
a64_malloc(umm_size_t num_bytes = 1) bj_code_dram;

bj_opt_sz_fn uint8_t* 
a64_realloc(uint8_t* ptr, umm_size_t num_bytes) bj_code_dram;

bj_opt_sz_fn void 
a64_free(uint8_t*& ptr) bj_code_dram;

#define bjk_malloc32(nam, sz)	(nam *)(a32_malloc(sz * sizeof(nam)))
#define bjk_realloc32(nam, ptr, sz)	(nam *)(a32_realloc((ptr), (sz * sizeof(nam))))
#define bjk_free32(ptr)	a32_free(ptr)

#define bjk_malloc64(nam, sz)	(nam *)(a64_malloc(sz * sizeof(nam)))
#define bjk_realloc64(nam, ptr, sz)	(nam *)(a64_realloc((ptr), (sz * sizeof(nam))))
#define bjk_free64(ptr)	a64_free(ptr)

#ifdef __cplusplus
}
#endif

#endif // BJ_DYN_MEM_HH


