
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
	return bj_addr_get_core_id(lk_dat->extnl_alloc_orig);
}

