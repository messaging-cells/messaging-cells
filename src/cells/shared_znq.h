
// shared_znq.h

#ifndef MC_SHARED_DATA_ZNQ_H
#define MC_SHARED_DATA_ZNQ_H

#ifndef MC_IS_ZNQ_CODE
	#error Only compile for zynq
#endif

#include "shared_eph3.h"

#ifdef __cplusplus
mc_c_decl {
#endif

#define mc_addr_has_local_id(addr) (! mc_addr_in_sys((mc_addr_t)addr))
#define mc_addr_is_local(addr) mc_addr_has_local_id(addr)

#define mck_as_glb_pt(pt) ((void*)(pt))
#define mck_as_loc_pt(pt) ((void*)(pt))

#ifdef __cplusplus
}
#endif

#endif // MC_SHARED_DATA_ZNQ_H


