
// mc_shared_eph3.h

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

typedef uint32_t mc_addr_t;
typedef uint16_t mc_core_id_t;	// e_coreid_t
typedef uint16_t mc_core_co_t;
typedef uint16_t mc_core_nn_t;

#define mc_addr_val_in_p16(p16) ((mc_addr_t)(mc_v32_of_p16(p16)))

#define mc_glb_id_mask		0xfff00000
#define mc_glb_addr_mask	0x000fffff
#define mc_glb_addr_sz	20

//======================================================================
// address macros

#define mc_addr_mask_id(addr) (((mc_addr_t)(addr)) & mc_glb_id_mask)
#define mc_addr_mask_ad(addr) (((mc_addr_t)(addr)) & mc_glb_addr_mask)

#define mc_addr_has_id(addr) mc_addr_mask_id(addr)
#define mc_addr_get_id(addr) ((mc_core_id_t)(mc_addr_mask_id(addr) >> mc_glb_addr_sz))
#define mc_addr_set_id(id, addr) ((mc_addr_t)((((mc_addr_t)(id)) << mc_glb_addr_sz) | mc_addr_mask_ad(addr)))

#define mc_addr_get_disp(addr) ((mc_addr_t)mc_addr_mask_ad(addr))
#define mc_addr_set_disp(disp, addr) ((mc_addr_t)(mc_addr_mask_id(addr) | mc_addr_mask_ad(disp)))

#define mc_addr_same_id(addr1, addr2) (mc_addr_mask_id(addr1) == mc_addr_mask_id(addr2))

#ifdef __cplusplus
}
#endif

#endif // MC_SHARED_DATA_EPH3_H


