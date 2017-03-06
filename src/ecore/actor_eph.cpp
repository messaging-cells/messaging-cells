
#include <new>

#include "actor.hh"

kernel bjk_THE_KERNEL;

void
kernel::init_sys(){
}

kernel*
kernel::get_sys(){
	return &bjk_THE_KERNEL;
}

void
kernel::finish_sys(){
}

