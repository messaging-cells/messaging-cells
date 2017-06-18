
// thread_emu.h

#ifndef THREAD_EMU_HH
#define THREAD_EMU_HH

#include <pthread.h>

#include "umm_malloc.h"
#include "global.h"
#include "cell.hh"
#include "booter.h"

#define NAMELEN 16

struct emu_info_st {    // Used as argument to thread_start() 
	pthread_t 		emu_id;        // id returned by pthread_create() 
	mc_core_nn_t	emu_num;       // core consec
	char 			emu_name[NAMELEN];

	void 		(*emu_core_func)();

	mc_core_id_t 	emu_core_id;	// core id as in epiphany arch
	mc_sys_sz_st 	emu_system_sz;
	bjk_glb_sys_st	emu_glb_sys_data;
	kernel 			emu_THE_KERNEL;
};

typedef struct emu_info_st emu_info_t;

struct thread_info_st {    // Used as argument to thread_start() 
	emu_info_t		thd_emu;

	umm_block 		thd_umm_heap[UMM_HEAP_NUM_BLOCKS];
};

typedef struct thread_info_st thread_info_t;

extern emu_info_t*	bjm_HOST_EMU_INFO;

extern thread_info_t* ALL_THREADS_INFO;
extern int TOT_THREADS;
extern pthread_t HOST_THREAD_ID;

uint16_t
bjk_get_thread_idx();

emu_info_t*
bjk_get_emu_info();

mc_inline_fn bool
bjm_addr_in_host(void* addr){
	uint8_t* pt = (uint8_t*)addr;
	uint8_t* hh = (uint8_t*)bjm_dlmalloc_heap;
	uint8_t* ll = hh + sizeof(bjm_dlmalloc_heap);
	if((pt >= hh) && (pt < ll)){ return true; }
	return false;
}

mc_inline_fn bool
bjk_addr_in_cores(void* addr){
	uint8_t* pt = (uint8_t*)addr;
	uint8_t* hh = (uint8_t*)ALL_THREADS_INFO;
	uint8_t* ll = hh + (sizeof(thread_info_t) * TOT_THREADS);
	if((pt >= hh) && (pt < ll)){ return true; }
	return false;
}

mc_inline_fn mc_core_nn_t
bjk_get_addr_idx(void* addr){
	EMU_CK(bjk_addr_in_cores(addr));
	mc_core_nn_t idx = (mc_core_nn_t)(((uintptr_t)addr - (uintptr_t)ALL_THREADS_INFO) / sizeof(thread_info_t));
	return idx;
}

mc_inline_fn uintptr_t
bjk_get_addr_offset(void* addr){
	EMU_CK(bjk_addr_in_cores(addr));
	uintptr_t ofs = (uintptr_t)(((uintptr_t)addr - (uintptr_t)ALL_THREADS_INFO) % sizeof(thread_info_t));
	return ofs;
}

mc_core_id_t
bjm_get_addr_core_id_fn(void* addr);

void*
bjm_addr_with_fn(mc_core_id_t id, void* addr);

mc_inline_fn bool
mc_is_host_thread(){
	return (pthread_self() == HOST_THREAD_ID);
}

void
mc_uint16_to_hex_bytes(uint16_t ival, uint8_t* hex_str);

void *
thread_start(void *arg);

#ifdef __cplusplus
mc_c_decl {
#endif


#ifdef __cplusplus
}
#endif

#endif // THREAD_EMU_HH

