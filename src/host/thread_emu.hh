

/*************************************************************

This file is part of messaging-cells.

messaging-cells is free software: you can redistribute it and/or modify
it under the terms of the version 3 of the GNU General Public 
License as published by the Free Software Foundation.

messaging-cells is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with messaging-cells.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------------

Copyright (C) 2017-2018. QUIROGA BELTRAN, Jose Luis.
Id (cedula): 79523732 de Bogota - Colombia.
See https://messaging-cells.github.io/

messaging-cells is free software thanks to The Glory of Our Lord 
	Yashua Melej Hamashiaj.
Our Resurrected and Living, both in Body and Spirit, 
	Prince of Peace.

------------------------------------------------------------*/


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
	mck_glb_sys_st	emu_glb_sys_data;
	mc_core_id_t	emu_map_parent_core_id;
	mc_core_nn_t	emu_map_tot_children;
	mc_load_map_st*	emu_map_loaded;
	kernel 			emu_THE_KERNEL;
};

typedef struct emu_info_st emu_info_t;

struct thread_info_st {    // Used as argument to thread_start() 
	emu_info_t		thd_emu;
	char*			thd_log_fnam;
	umm_block 		thd_umm_heap[UMM_HEAP_NUM_BLOCKS];
};

typedef struct thread_info_st thread_info_t;

extern emu_info_t*	mcm_HOST_EMU_INFO;

extern thread_info_t* ALL_THREADS_INFO;
extern int TOT_THREADS;
extern pthread_t HOST_THREAD_ID;

uint16_t
mck_get_thread_idx();

emu_info_t*
mck_get_emu_info();

mc_inline_fn bool
mcm_addr_in_host(void* addr){
	uint8_t* pt = (uint8_t*)addr;
	uint8_t* hh = (uint8_t*)mcm_dlmalloc_heap;
	uint8_t* ll = hh + sizeof(mcm_dlmalloc_heap);
	if((pt >= hh) && (pt < ll)){ return true; }
	return false;
}

mc_inline_fn bool
mck_addr_in_cores(void* addr){
	uint8_t* pt = (uint8_t*)addr;
	uint8_t* hh = (uint8_t*)ALL_THREADS_INFO;
	uint8_t* ll = hh + (sizeof(thread_info_t) * TOT_THREADS);
	if((pt >= hh) && (pt < ll)){ return true; }
	return false;
}

mc_inline_fn mc_core_nn_t
mck_get_addr_idx(void* addr){
	EMU_CK(mck_addr_in_cores(addr));
	mc_core_nn_t idx = (mc_core_nn_t)(((uintptr_t)addr - (uintptr_t)ALL_THREADS_INFO) / sizeof(thread_info_t));
	return idx;
}

mc_inline_fn uintptr_t
mck_get_addr_offset(void* addr){
	EMU_CK(mck_addr_in_cores(addr));
	uintptr_t ofs = (uintptr_t)(((uintptr_t)addr - (uintptr_t)ALL_THREADS_INFO) % sizeof(thread_info_t));
	return ofs;
}

mc_core_id_t
mcm_get_addr_core_id_fn(void* addr);

void*
mcm_addr_with_fn(mc_core_id_t id, void* addr);

mc_inline_fn bool
mc_is_host_thread(){
	return (pthread_self() == HOST_THREAD_ID);
}

void
mc_uint16_to_hex_bytes(uint16_t ival, uint8_t* hex_str);

void *
thread_start(void *arg);

void 
thread_abort();

void
mch_load_map();

#ifdef __cplusplus
mc_c_decl {
#endif


#ifdef __cplusplus
}
#endif

#endif // THREAD_EMU_HH

