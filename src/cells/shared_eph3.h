//----------------------------------------------------------------------------
/*! \file shared_eph3.h

\brief Addressing functions of the epiphany 3 architecture.

*/

#ifndef MC_SHARED_DATA_EPH3_H
#define MC_SHARED_DATA_EPH3_H

#if !defined(MC_IS_EPH_CODE) && ! defined(MC_IS_ZNQ_CODE)
	#error Only compile for parallella (epiphany or zynq)
#endif

#ifdef __cplusplus
mc_c_decl {
#endif

//======================================================================
// epiphany III macros
	
#define mc_axis_bits	6
#define mc_axis_mask	0x3f

typedef uint32_t mc_addr_t;	//!< Type for epiphany addresses
typedef uint16_t mc_core_id_t;	//!< Type for core ids
typedef uint16_t mc_core_co_t;	//!< Type for core coordinates (row and col)
typedef uint16_t mc_core_nn_t; //!< Type for core numbers (starts in 0)

#define mc_addr_val_in_p16(p16) ((mc_addr_t)(mc_v32_of_p16(p16)))

#define mc_glb_id_mask		0xfff00000
#define mc_glb_addr_mask	0x000fffff
#define mc_glb_addr_sz	20

//======================================================================
// address macros

//! Masks the id part of 'addr'
#define mc_addr_mask_id(addr) (((mc_addr_t)(addr)) & mc_glb_id_mask)
//! Masks the displacement (local-addr) part of 'addr'
#define mc_addr_mask_ad(addr) (((mc_addr_t)(addr)) & mc_glb_addr_mask)

//! True 'addr' has 'id' (not zero id)
#define mc_addr_has_id(addr) mc_addr_mask_id(addr)
//! Returns the id part of 'addr' as mc_core_id_t value
#define mc_addr_get_id(addr) ((mc_core_id_t)(mc_addr_mask_id(addr) >> mc_glb_addr_sz))
//! Sets the id part of 'addr' with 'id'
#define mc_addr_set_id(id, addr) ((mc_addr_t)((((mc_addr_t)(id)) << mc_glb_addr_sz) | mc_addr_mask_ad(addr)))

//! Returns the displacement (local-addr) part of 'addr' as mc_addr_t value
#define mc_addr_get_disp(addr) ((mc_addr_t)mc_addr_mask_ad(addr))
//! Sets the displacement (local-addr) part of 'addr' with 'disp'
#define mc_addr_set_disp(disp, addr) ((mc_addr_t)(mc_addr_mask_id(addr) | mc_addr_mask_ad(disp)))

//! True if 'addr1' and 'addr2' have the same id part value
#define mc_addr_same_id(addr1, addr2) (mc_addr_mask_id(addr1) == mc_addr_mask_id(addr2))

#ifdef __cplusplus
}
#endif

#endif // MC_SHARED_DATA_EPH3_H

