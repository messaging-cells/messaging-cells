
#include "shared.h"

#include "booter.h"

mc_sys_sz_st mch_system_sz;

mc_sys_sz_st*
mc_get_glb_sys_sz(){
	return &mch_system_sz;
}


mc_core_id_t 
mck_get_core_id(){
	mc_link_syms_data_st* lk_dat = &(MC_EXTERNAL_RAM_LOAD_DATA);
	return mc_addr_get_id(lk_dat->extnl_host_alloc_orig);
}

mc_addr_t
mc_host_addr_to_core_addr(mc_addr_t h_addr){
	return mc_znq_addr_to_eph_addr(h_addr);
}

mc_addr_t
mc_core_addr_to_host_addr(mc_addr_t c_addr){
	return mc_eph_addr_to_znq_addr(c_addr);
}

