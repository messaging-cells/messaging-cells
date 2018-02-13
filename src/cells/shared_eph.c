
#include "shared.h"
#include "global.h"

//include "link_syms_vals.h"

mc_sys_sz_st 	mck_system_sz;


mc_addr_t
mc_host_addr_to_core_addr(mc_addr_t h_addr){
	return (MC_VAL_EXTERNAL_RAM_ORIG + (h_addr - MC_CORE_INFO->znq_shd_mem_base));
}

mc_addr_t
mc_core_addr_to_host_addr(mc_addr_t c_addr){
	return (MC_CORE_INFO->znq_shd_mem_base + (c_addr - MC_VAL_EXTERNAL_RAM_ORIG));
}

