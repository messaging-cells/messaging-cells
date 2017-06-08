
#include "shared.h"

#include "booter.h"

bj_sys_sz_st bjh_system_sz;

bj_sys_sz_st*
bj_get_glb_sys_sz(){
	return &bjh_system_sz;
}


bj_core_id_t 
bjk_get_core_id(){
	bj_link_syms_data_st* lk_dat = &(BJ_EXTERNAL_RAM_LOAD_DATA);
	return bj_addr_get_id(lk_dat->extnl_host_alloc_orig);
}

bj_addr_t
bj_host_addr_to_core_addr(bj_addr_t h_addr){
	return bj_znq_addr_to_eph_addr(h_addr);
}

bj_addr_t
bj_core_addr_to_host_addr(bj_addr_t c_addr){
	return bj_eph_addr_to_znq_addr(c_addr);
}

