
#include "shared.h"

#include "thread_emu.hh"

bj_core_id_t 
bjk_get_core_id(){
	return bjk_get_thread_info()->bjk_core_id;
}
