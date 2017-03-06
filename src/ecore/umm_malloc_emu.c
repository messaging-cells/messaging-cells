// ----------------------------------------------------------------------------
// umm_mallocemu_.c - 
//
// ----------------------------------------------------------------------------

#include "umm_malloc.h"

UMM_HEAP_INFO heapInfo;
umm_block umm_heap[UMM_HEAP_NUM_BLOCKS] bj_data_bank2;

umm_idx_t umm_numblocks = (sizeof(umm_heap) / sizeof(umm_block));

umm_block*
umm_get_heap(){
	return umm_heap;
}

UMM_HEAP_INFO*
umm_get_info(){
	return &heapInfo;
}

