
#include "shared.h"
#include "err_msgs.h"
#include "global.h"

//include "link_syms_vals.h"

bj_sys_sz_st 	bjk_system_sz;


bj_addr_t
bj_host_addr_to_core_addr(bj_addr_t h_addr){
	return (BJ_VAL_EXTERNAL_RAM_ORIG + (h_addr - BJK_GLB_SYS->znq_shd_mem_base));
	//bjk_abort((bj_addr_t)bj_host_addr_to_core_addr, err_12);
	//return 0;
}

bj_addr_t
bj_core_addr_to_host_addr(bj_addr_t c_addr){
	return (BJK_GLB_SYS->znq_shd_mem_base + (c_addr - BJ_VAL_EXTERNAL_RAM_ORIG));
	//bjk_abort((bj_addr_t)bj_core_addr_to_host_addr, err_13);
	//return 0;
}

