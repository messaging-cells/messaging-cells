
// shared_eph.h

#ifndef BJ_SHARED_DATA_EPH_H
#define BJ_SHARED_DATA_EPH_H

#if !defined(BJ_IS_EPH_CODE) && ! defined(BJ_IS_ZNQ_CODE)
	#error Only compile for parallella (epiphany or zynq)
#endif

#include "shared_eph3.h"

#ifdef __cplusplus
bj_c_decl {
#endif

#define bj_addr_has_local_id(addr) (bj_addr_get_id(addr) == BJK_GLB_SYS->the_core_id)
#define bj_addr_is_local(addr) ((! bj_addr_has_id(addr)) || bj_addr_has_local_id(addr))

#define bjk_as_glb_pt(pt) ((void*)bj_addr_set_id(BJK_GLB_SYS->the_core_id, (pt)))
#define bjk_as_loc_pt(pt) ((void*)bj_addr_mask_ad(pt))

#ifdef __cplusplus
}
#endif

#endif // BJ_SHARED_DATA_EPH_H


