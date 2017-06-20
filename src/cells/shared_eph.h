
// shared_eph.h

#ifndef MC_SHARED_DATA_EPH_H
#define MC_SHARED_DATA_EPH_H

#if !defined(MC_IS_EPH_CODE) && ! defined(MC_IS_ZNQ_CODE)
	#error Only compile for parallella (epiphany or zynq)
#endif

#include "shared_eph3.h"

#ifdef __cplusplus
mc_c_decl {
#endif

#define mc_addr_has_local_id(addr) (mc_addr_get_id(addr) == BJK_GLB_SYS->the_core_id)
#define mc_addr_is_local(addr) ((! mc_addr_has_id(addr)) || mc_addr_has_local_id(addr))

#define mck_as_glb_pt(pt) ((void*)mc_addr_set_id(BJK_GLB_SYS->the_core_id, (pt)))
#define mck_as_loc_pt(pt) ((void*)mc_addr_mask_ad(pt))

#ifdef __cplusplus
}
#endif

#endif // MC_SHARED_DATA_EPH_H


