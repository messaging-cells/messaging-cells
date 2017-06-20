
#include "shared.h"

#include "thread_emu.hh"
#include "booter.h"

mc_sys_sz_st*
mc_get_glb_sys_sz(){
	return &(mck_get_emu_info()->emu_system_sz);
}

mc_core_id_t 
mck_get_core_id(){
	return mck_get_emu_info()->emu_core_id;
}

mc_addr_t
mc_host_addr_to_core_addr(mc_addr_t h_addr){
	return h_addr;
}

mc_addr_t
mc_core_addr_to_host_addr(mc_addr_t c_addr){
	return c_addr;
}

