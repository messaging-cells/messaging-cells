
// bj_shared_emu.h

#ifndef BJ_SHARED_DATA_EMU_H
#define BJ_SHARED_DATA_EMU_H

#ifdef __cplusplus
bj_c_decl {
#endif

//======================================================================
// epiphany III macros
	
#define bj_axis_bits	6
#define bj_axis_mask	0x3f

#ifdef IS_CORE_CODE
	typedef uint32_t bj_addr_t;
#else
	typedef uintptr_t bj_addr_t;
#endif
	
typedef uint16_t bj_core_id_t;	// e_coreid_t
typedef uint16_t bj_core_co_t;
typedef uint16_t bj_core_nn_t;

typedef uint16_t bj_size_t;

#define bj_addr_val_in_p16(p16) ((bj_addr_t)(bj_v32_of_p16(p16)))

#define bj_e3_xx 32
#define bj_e3_yy 8
#define bj_e3_xx_sz 4
#define bj_e3_yy_sz 4
#define bj_e3_yy_sz_pw2 2

#define bj_e3_num_chip_cores 16

#define bj_glb_id_mask		0xfff00000
#define bj_glb_addr_mask	0x000fffff
#define bj_glb_addr_sz	20

//======================================================================
// address macros

bj_core_id_t
bjk_get_addr_core_id_fn(void*);

void*
bjk_addr_with_fn(bj_core_id_t id, void* addr);

#define bj_addr_is_global(addr) true
#define bj_addr_get_core_id(addr) bjk_get_addr_core_id_fn((void*)(addr))
#define bj_addr_with(id, addr) bjk_addr_with_fn(id, (void*)addr)

#define bjk_addr_is_local(addr) \
	(! bj_addr_is_global(addr) || (bj_addr_get_core_id(addr) == bjk_get_glb_in_core_shd()->the_core_id))

#define bjk_is_core(row, col) \
	((bjk_get_glb_in_core_shd()->the_core_ro == (row)) && (bjk_get_glb_in_core_shd()->the_core_co == (col)))

#define bj_addr_same_id(addr1, addr2) (bj_addr_get_core_id(addr1) == bj_addr_get_core_id(addr2))

#define bjk_as_glb_pt(pt) ((void*)(pt))

/*

#define bjk_as_loc_pt(pt) ((void*)bj_addr_mask_ad(pt))
#define bjk_as_img_pt(pt, id) ((void*)bj_addr_with((id), (pt)))

*/

#ifdef __cplusplus
}
#endif

#endif // BJ_SHARED_DATA_EMU_H

