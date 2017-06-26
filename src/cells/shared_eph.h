//----------------------------------------------------------------------------
/*! \file shared_eph.h

\brief Addressing functions for the epiphany architecture..

*/

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

//! True if 'addr' has local id
#define mc_addr_has_local_id(addr) (mc_addr_get_id(addr) == MC_CORE_INFO->the_core_id)

//! True if 'addr' is local
#define mc_addr_is_local(addr) ((! mc_addr_has_id(addr)) || mc_addr_has_local_id(addr))

//! Sets the id of 'pt' to the local core id.
#define mck_as_glb_pt(pt) ((void*)mc_addr_set_id(MC_CORE_INFO->the_core_id, (pt)))

//! Sets to zero the id of 'pt'.
#define mck_as_loc_pt(pt) ((void*)mc_addr_mask_ad(pt))

#ifdef __cplusplus
}
#endif

#endif // MC_SHARED_DATA_EPH_H


