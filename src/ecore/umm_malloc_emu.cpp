// ----------------------------------------------------------------------------
// umm_mallocemu_.c - 
//
// ----------------------------------------------------------------------------

#include "umm_malloc.h"

#include "thread_emu.hh"

umm_idx_t umm_numblocks = UMM_HEAP_NUM_BLOCKS;

umm_block*
umm_get_heap(){
	return bjk_get_thread_info()->umm_heap;
}

UMM_HEAP_INFO*
umm_get_info(){
	return &(bjk_get_thread_info()->heapInfo);
}

