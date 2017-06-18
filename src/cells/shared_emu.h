
// mc_shared_emu.h

#ifndef MC_SHARED_DATA_EMU_H
#define MC_SHARED_DATA_EMU_H

#if ! defined(MC_IS_EMU_CODE)
	#error Only compile for emulation code (your linux)
#endif

#ifdef __cplusplus
mc_c_decl {
#endif

//======================================================================
// epiphany III macros
	
#define mc_axis_bits	6
#define mc_axis_mask	0x3f

typedef uintptr_t mc_addr_t;
typedef uint16_t mc_core_id_t;	// e_coreid_t
typedef uint16_t mc_core_co_t;
typedef uint16_t mc_core_nn_t;

//define mc_addr_val_in_p16(p16) ((mc_addr_t)(mc_v32_of_p16(p16)))

//======================================================================
// address macros

mc_core_id_t
bjm_get_addr_core_id_fn(void*);

void*
bjm_addr_with_fn(mc_core_id_t id, void* addr);

#define mc_addr_has_id(addr) true
#define mc_addr_get_id(addr) bjm_get_addr_core_id_fn((void*)(addr))
#define mc_addr_set_id(id, addr) bjm_addr_with_fn((id), (void*)(addr))
#define mc_addr_has_local_id(addr) (mc_addr_get_id(addr) == BJK_GLB_SYS->the_core_id)
#define mc_addr_is_local(addr) mc_addr_has_local_id(addr)

#define mc_addr_get_disp(addr) ((mc_addr_t)(addr))
#define mc_addr_set_disp(disp, addr) mc_addr_set_id(mc_addr_get_id(addr), (disp))

#define bjk_as_glb_pt(pt) ((void*)(pt))
#define bjk_as_loc_pt(pt) ((void*)(pt))

#define mc_addr_same_id(addr1, addr2) (mc_addr_get_id(addr1) == mc_addr_get_id(addr2))

#ifdef __cplusplus
}
#endif

#endif // MC_SHARED_DATA_EMU_H


