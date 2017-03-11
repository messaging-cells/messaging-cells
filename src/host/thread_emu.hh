
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

	bj_core_id_t 	bjk_core_id;

	bjk_glb_sys_st	bj_glb_sys_data;

	kernel 			bjk_THE_KERNEL;

	UMM_HEAP_INFO 	heapInfo;
	umm_block 		umm_heap[UMM_HEAP_NUM_BLOCKS];
};

typedef struct thread_info_st thread_info_t;

uint16_t
bjk_get_thread_idx();

thread_info_t*
bjk_get_thread_info();

uint16_t
bjk_get_addr_idx(void*);

bool
bj_is_host_thread();

#ifdef __cplusplus
bj_c_decl {
#endif


#ifdef __cplusplus
}
#endif

#endif // THREAD_EMU_HH

