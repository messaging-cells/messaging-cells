// ----------------------------------------------------------------------------
// umm_mallocemu_.c - 
//
// ----------------------------------------------------------------------------

#include "umm_malloc.h"

#include "thread_emu.hh"

umm_block*
umm_get_heap(){
	return bjk_get_thread_info()->thd_umm_heap;
}

