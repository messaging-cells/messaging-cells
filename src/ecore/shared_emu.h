
// bj_in_core_st the IN_CORE shared with host data

// bj_shared_data.h

#ifndef BJ_SHARED_DATA_EMU_H
#define BJ_SHARED_DATA_EMU_H

#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#include "attribute.h"
#include "log.h"
#include "rr_array.h"

#ifdef __cplusplus
bj_c_decl {
#endif

//typedef uintptr_t bj_addr_t;

//======================================================================
// convertion functions
	
// xx and yy are absolute epiphany space coordinates
// ro and co are relative epiphany space coordinates with respect to the 
// 		allocated running cores (bj_get_glb_sys_sz())
// id is the core id absolute in epiphany space 
// nn is a consec with respect to the allocated running cores (bj_get_glb_sys_sz())

#define bj_id_to_xx(id)	(((id) >> bj_axis_bits) & bj_axis_mask)
#define bj_id_to_yy(id)	((id) & bj_axis_mask)
#define bj_xx_to_ro(xx)	((xx) - bj_min_xx_sys)
#define bj_yy_to_co(yy)	((yy) - bj_min_yy_sys)
#define bj_id_to_ro(id)	bj_xx_to_ro(bj_id_to_xx(id))
#define bj_id_to_co(id)	bj_yy_to_co(bj_id_to_yy(id))
#define bj_ro_to_xx(ro)	((ro) + bj_min_xx_sys)
#define bj_co_to_yy(co)	((co) + bj_min_yy_sys)
#define bj_ro_co_to_nn(ro, co) (((ro) * (bj_get_glb_sys_sz()->yy_sz)) + (co))
#define bj_xx_yy_to_id(xx, yy) (((xx) << bj_axis_bits) + (yy))
#define bj_ro_co_to_id(ro, co) ((bj_ro_to_xx(ro) << bj_axis_bits) + bj_co_to_yy(co))
#define bj_nn_to_ro(nn)	((nn) / (bj_get_glb_sys_sz()->yy_sz))
#define bj_nn_to_co(nn)	((nn) % (bj_get_glb_sys_sz()->yy_sz))
#define bj_id_to_nn(id) (bj_ro_co_to_nn(bj_id_to_ro(id), bj_id_to_co(id)))
#define bj_nn_to_id(nn) (bj_ro_co_to_id(bj_nn_to_ro(nn), bj_nn_to_co(nn)))

#define bj_xx_in_sys(xx) (((xx) >= bj_min_xx_sys) && ((xx) < bj_max_xx_sys))
#define bj_yy_in_sys(yy) (((yy) >= bj_min_yy_sys) && ((yy) < bj_max_yy_sys))
#define bj_xx_yy_in_sys(xx, yy) (bj_xx_in_sys(xx) && bj_yy_in_sys(yy))

//======================================================================
// address functions

#define bj_addr_mask_id(addr) (((bj_addr_t)(addr)) & bj_glb_id_mask)
#define bj_addr_mask_ad(addr) (((bj_addr_t)(addr)) & bj_glb_addr_mask)

#define bj_addr_is_global(addr) bj_addr_mask_id(addr)
#define bj_addr_get_core_id(addr) ((bj_core_id_t)(bj_addr_mask_id(addr) >> bj_glb_addr_sz))
#define bj_addr_with(id, addr) ((bj_addr_t)((((bj_addr_t)(id)) << bj_glb_addr_sz) | bj_addr_mask_ad(addr)))

#define bjk_addr_is_local(addr) \
	(! bj_addr_is_global(addr) || (bj_addr_get_core_id(addr) == bjk_get_glb_in_core_shd()->the_core_id))

#define bjk_is_core(row, col) \
	((bjk_get_glb_in_core_shd()->the_core_ro == (row)) && (bjk_get_glb_in_core_shd()->the_core_co == (col)))

#define bjk_as_glb_pt(pt) ((void*)bj_addr_with(bjk_get_glb_in_core_shd()->the_core_co, (pt)))
#define bjk_as_loc_pt(pt) ((void*)bj_addr_mask_ad(pt))
#define bjk_as_img_pt(pt, id) ((void*)bj_addr_with((id), (pt)))

#define bj_addr_same_id(addr1, addr2) (bj_addr_mask_id(addr1) == bj_addr_mask_id(addr2))

//define bj_addr_with_same_id(addr_id, addr) ((bj_addr_t)(bj_addr_mask_id(addr_id) | bj_addr_mask_ad(addr)))

bj_core_id_t 
bjk_get_core_id();

bool bj_inline_fn
bj_addr_in_core(bj_addr_t addr, bj_core_id_t koid) {
	bj_core_id_t addr_koid = bj_addr_get_core_id(addr);
	return ((addr_koid == 0) || (addr_koid == koid));
}

bool bj_inline_fn
bj_addr_in_sys(bj_addr_t addr) {
	bj_core_id_t addr_koid = bj_addr_get_core_id(addr);
	bj_core_co_t xx = bj_id_to_xx(addr_koid);
	bj_core_co_t yy = bj_id_to_yy(addr_koid);
	return bj_xx_yy_in_sys(xx, yy);
}

#ifdef __cplusplus
}
#endif

#endif // BJ_SHARED_DATA_EMU_H

