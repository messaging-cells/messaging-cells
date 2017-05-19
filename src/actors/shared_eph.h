
// bj_shared_eph3.h

#ifndef BJ_SHARED_DATA_EPH3_H
#define BJ_SHARED_DATA_EPH3_H

#if !defined(BJ_IS_EPH_CODE) && ! defined(BJ_IS_ZNQ_CODE)
	#error Only compile for parallella (epiphany or zynq)
#endif

#ifdef __cplusplus
bj_c_decl {
#endif

//======================================================================
// epiphany III macros
	
#define bj_axis_bits	6
#define bj_axis_mask	0x3f

typedef uint32_t bj_addr_t;
typedef uint16_t bj_core_id_t;	// e_coreid_t
typedef uint16_t bj_core_co_t;
typedef uint16_t bj_core_nn_t;

#define bj_addr_val_in_p16(p16) ((bj_addr_t)(bj_v32_of_p16(p16)))

#define bj_glb_id_mask		0xfff00000
#define bj_glb_addr_mask	0x000fffff
#define bj_glb_addr_sz	20

//======================================================================
// address macros

#define bj_addr_mask_id(addr) (((bj_addr_t)(addr)) & bj_glb_id_mask)
#define bj_addr_mask_ad(addr) (((bj_addr_t)(addr)) & bj_glb_addr_mask)

#define bj_addr_has_id(addr) bj_addr_mask_id(addr)
#define bj_addr_get_id(addr) ((bj_core_id_t)(bj_addr_mask_id(addr) >> bj_glb_addr_sz))
#define bj_addr_set_id(id, addr) ((bj_addr_t)((((bj_addr_t)(id)) << bj_glb_addr_sz) | bj_addr_mask_ad(addr)))
#define bj_addr_has_local_id(addr) (bj_addr_get_id(addr) == BJK_GLB_SYS->the_core_id)
#define bj_addr_is_local(addr) ((! bj_addr_has_id(addr)) || bj_addr_has_local_id(addr))

#define bj_addr_get_disp(addr) ((bj_addr_t)bj_addr_mask_ad(addr))
#define bj_addr_set_disp(disp, addr) ((bj_addr_t)(bj_addr_mask_id(addr) | bj_addr_mask_ad(disp)))

#define bjk_as_glb_pt(pt) ((void*)bj_addr_set_id(BJK_GLB_SYS->the_core_id, (pt)))
#define bjk_as_loc_pt(pt) ((void*)bj_addr_mask_ad(pt))
#define bjk_as_img_pt(pt, id) ((void*)bj_addr_set_id((id), (pt)))

#define bj_addr_same_id(addr1, addr2) (bj_addr_mask_id(addr1) == bj_addr_mask_id(addr2))

#ifdef __cplusplus
}
#endif

#endif // BJ_SHARED_DATA_EPH3_H


