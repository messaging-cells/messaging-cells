
// shared_znq.h

#ifndef BJ_SHARED_DATA_ZNQ_H
#define BJ_SHARED_DATA_ZNQ_H

#ifndef BJ_IS_ZNQ_CODE
	#error Only compile for zynq
#endif

#include "shared_eph3.h"

#ifdef __cplusplus
bj_c_decl {
#endif

#define bj_addr_has_local_id(addr) (! bj_addr_in_sys((bj_addr_t)addr))
#define bj_addr_is_local(addr) bj_addr_has_local_id(addr)

#define bjk_as_glb_pt(pt) ((void*)(pt))
#define bjk_as_loc_pt(pt) ((void*)(pt))

#ifdef __cplusplus
}
#endif

#endif // BJ_SHARED_DATA_ZNQ_H


