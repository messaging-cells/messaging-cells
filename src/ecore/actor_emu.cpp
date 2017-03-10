
#include <new>

#include "actor.hh"

#include "thread_emu.hh"

kernel*
kernel::get_sys(){
	return &(bjk_get_thread_info()->bjk_THE_KERNEL);
}

