// ----------------------------------------------------------------------------
// umm_mallocemu_.c - 
//
// ----------------------------------------------------------------------------

#include "umm_malloc.h"

#include "thread_emu.hh"
#include "booter.h"

umm_block*
umm_get_heap(){
	uint16_t thd_idx = bjk_get_thread_idx();
	return ALL_THREADS_INFO[thd_idx].thd_umm_heap;
}

