
// bj_shared_emu.h

#ifndef BJ_SHARED_DATA_EMU_H
#define BJ_SHARED_DATA_EMU_H

#if ! defined(BJ_IS_EMU_CODE)
	#error Only compile for emulation code (your linux)
#endif

#ifdef __cplusplus
bj_c_decl {
#endif

//======================================================================
// epiphany III macros
	
#define bj_axis_bits	6
#define bj_axis_mask	0x3f

typedef uintptr_t bj_addr_t;
typedef uint16_t bj_core_id_t;	// e_coreid_t
typedef uint16_t bj_core_co_t;
typedef uint16_t bj_core_nn_t;

//define bj_addr_val_in_p16(p16) ((bj_addr_t)(bj_v32_of_p16(p16)))

//======================================================================
// address macros

bj_core_id_t
bjm_get_addr_core_id_fn(void*);

void*
bjm_addr_with_fn(bj_core_id_t id, void* addr);

#define bj_addr_has_id(addr) true
#define bj_addr_get_id(addr) bjm_get_addr_core_id_fn((void*)(addr))
#define bj_addr_set_id(id, addr) bjm_addr_with_fn((id), (void*)(addr))
#define bj_addr_has_local_id(addr) (bj_addr_get_id(addr) == BJK_GLB_SYS->the_core_id)
#define bj_addr_is_local(addr) bj_addr_has_local_id(addr)

#define bj_addr_get_disp(addr) ((bj_addr_t)(addr))
#define bj_addr_set_disp(disp, addr) bj_addr_set_id(bj_addr_get_id(addr), (disp))

#define bjk_as_glb_pt(pt) ((void*)(pt))
#define bjk_as_loc_pt(pt) ((void*)(pt))

#define bj_addr_same_id(addr1, addr2) (bj_addr_get_id(addr1) == bj_addr_get_id(addr2))

#ifdef __cplusplus
}
#endif

#endif // BJ_SHARED_DATA_EMU_H


