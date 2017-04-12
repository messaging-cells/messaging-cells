
// thread_emu.h

#ifndef THREAD_EMU_HH
#define THREAD_EMU_HH

#include <pthread.h>

#include "umm_malloc.h"
#include "global.h"
#include "actor.hh"

#define NAMELEN 16

struct thread_info_st {    /* Used as argument to thread_start() */
	pthread_t 	thread_id;        /* ID returned by pthread_create() */
	uint16_t 	thread_num;       /* Application-defined thread # */
	char 		thread_name[NAMELEN];
	char 		*argv_string;      /* From command-line argument */

	void 		(*core_func)();

	bj_core_id_t 	bjk_core_id;
	bjk_glb_sys_st	bj_glb_sys_data;
	kernel 			bjk_THE_KERNEL;

	umm_block 		umm_heap[UMM_HEAP_NUM_BLOCKS];
};

typedef struct thread_info_st thread_info_t;

extern thread_info_t* ALL_THREADS_INFO;
extern int TOT_THREADS;
extern pthread_t HOST_THREAD_ID;

uint16_t
bjk_get_thread_idx();

thread_info_t*
bjk_get_thread_info();

bj_inline_fn bj_core_nn_t
bjk_get_addr_idx(void* addr){
	bj_core_nn_t idx = (bj_core_nn_t)(((uintptr_t)addr - (uintptr_t)ALL_THREADS_INFO) / sizeof(thread_info_t));
	return idx;
}

bj_inline_fn uintptr_t
bjk_get_addr_offset(void* addr){
	uintptr_t ofs = (uintptr_t)(((uintptr_t)addr - (uintptr_t)ALL_THREADS_INFO) % sizeof(thread_info_t));
	return ofs;
}

bj_core_id_t
bjk_get_addr_core_id_fn(void* addr);

void*
bjk_addr_with_fn(bj_core_id_t id, void* addr);

bj_inline_fn bool
bj_is_host_thread(){
	return (pthread_self() == HOST_THREAD_ID);
}

void
bj_uint16_to_hex_bytes(uint16_t ival, uint8_t* hex_str);

void *
thread_start(void *arg);

#ifdef __cplusplus
bj_c_decl {
#endif


#ifdef __cplusplus
}
#endif

#endif // THREAD_EMU_HH

