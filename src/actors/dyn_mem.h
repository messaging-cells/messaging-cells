

/*************************************************************
dyn_mem.hh

Declaration of dynamic mem funcs.

--------------------------------------------------------------*/

#ifndef BJ_DYN_MEM_HH
#define BJ_DYN_MEM_HH

#include "umm_malloc.h"

#ifdef __cplusplus
bj_c_decl {
#endif

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
a64_malloc(umm_size_t num_bytes) bj_external_code_ram;

bj_opt_sz_fn uint8_t* 
a64_realloc(uint8_t* ptr, umm_size_t num_bytes) bj_external_code_ram;

bj_opt_sz_fn void 
a64_free(uint8_t* ptr) bj_external_code_ram;

#ifdef BJ_IS_EPH_CODE
	#define bj_malloc32(nam, sz)	(nam *)(a32_malloc(sz * sizeof(nam)))
	#define bj_realloc32(nam, ptr, sz)	(nam *)(a32_realloc((ptr), (sz * sizeof(nam))))
	#define bj_free32(ptr)	a32_free(ptr)

	#define bj_malloc64(nam, sz)	(nam *)(a64_malloc(sz * sizeof(nam)))
	#define bj_realloc64(nam, ptr, sz)	(nam *)(a64_realloc((ptr), (sz * sizeof(nam))))
	#define bj_free64(ptr)	a64_free(ptr)
#endif

#ifdef BJ_IS_ZNQ_CODE
	#include "dlmalloc.h"
	extern mspace bjh_glb_alloc_mspace;

	#define bj_malloc32(nam, sz)	(nam *)(mspace_malloc(bjh_glb_alloc_mspace, (sz * sizeof(nam))))
	#define bj_realloc32(nam, ptr, sz)	(nam *)(mspace_realloc(bjh_glb_alloc_mspace, ((ptr), (sz * sizeof(nam)))))
	#define bj_free32(ptr)	mspace_free(bjh_glb_alloc_mspace, ptr)

	#define bj_malloc64(nam, sz)	((nam *)(mspace_malloc(bjh_glb_alloc_mspace, (sz * sizeof(nam)))))
	#define bj_realloc64(nam, ptr, sz)	((nam *)(mspace_realloc(bjh_glb_alloc_mspace, ((ptr), (sz * sizeof(nam))))))
	#define bj_free64(ptr)	mspace_free(bjh_glb_alloc_mspace, ptr)
#endif

#ifdef BJ_IS_EMU_CODE
	uint8_t* 
	bj_malloc_impl(umm_size_t num_bytes);

	uint8_t* 
	bj_realloc_impl(uint8_t* ptr, umm_size_t num_bytes);

	void 
	bj_free_impl(uint8_t* ptr);

	#define bj_malloc32(nam, sz)	(nam *)(bj_malloc_impl(sz * sizeof(nam)))
	#define bj_realloc32(nam, ptr, sz)	(nam *)(bj_realloc_impl((ptr), (sz * sizeof(nam))))
	#define bj_free32(ptr)	bj_free_impl(ptr)

	#define bj_malloc64(nam, sz)	(nam *)(bj_malloc_impl(sz * sizeof(nam)))
	#define bj_realloc64(nam, ptr, sz)	(nam *)(bj_realloc_impl((ptr), (sz * sizeof(nam))))
	#define bj_free64(ptr)	bj_free_impl(ptr)
#endif

#ifdef __cplusplus
}
#endif

#endif // BJ_DYN_MEM_HH


