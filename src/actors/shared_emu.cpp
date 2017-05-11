
#include "shared.h"

#include "thread_emu.hh"
#include "booter.h"

bj_sys_sz_st*
bj_get_glb_sys_sz(){
	if(bj_is_host_thread()){
		return &bjh_glb_host_sys;
	}
	return &(bjk_get_thread_info()->bjk_system_sz);
}

bj_core_id_t 
bjk_get_core_id(){
	return bjk_get_thread_info()->bjk_core_id;
}
