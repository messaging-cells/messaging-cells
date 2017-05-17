
#include "shared.h"

#include "thread_emu.hh"
#include "booter.h"

bj_sys_sz_st*
bj_get_glb_sys_sz(){
	return &(bjk_get_emu_info()->emu_system_sz);
}

bj_core_id_t 
bjk_get_core_id(){
	return bjk_get_emu_info()->emu_core_id;
}

bj_addr_t
bj_host_addr_to_core_addr(bj_addr_t h_addr){
	return h_addr;
}

bj_addr_t
bj_core_addr_to_host_addr(bj_addr_t c_addr){
	return c_addr;
}

