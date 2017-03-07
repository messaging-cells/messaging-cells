
#include <new>

#include "actor.hh"

kernel bjk_THE_KERNEL;

kernel*
kernel::get_sys(){
	return &bjk_THE_KERNEL;
}

