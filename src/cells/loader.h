
// loader.h

#ifndef MC_LOADER_H
#define MC_LOADER_H

#include "shared.h"

#ifdef __cplusplus
mc_c_decl {
#endif

#ifdef MC_IS_EPH_CODE

	extern mc_addr_t LD_EXTERNAL_RAM_SIZE;
	extern mc_addr_t LD_EXTERNAL_CODE_SIZE;
	extern mc_addr_t LD_EXTERNAL_LOAD_SIZE;
	extern mc_addr_t LD_EXTERNAL_HOST_DATA_SIZE;
	extern mc_addr_t LD_EXTERNAL_HOST_ALLOC_SIZE;
	extern mc_addr_t LD_EXTERNAL_RAM_ORIG;
	extern mc_addr_t LD_EXTERNAL_CODE_ORIG;
	extern mc_addr_t LD_EXTERNAL_LOAD_ORIG;
	extern mc_addr_t LD_EXTERNAL_HOST_DATA_ORIG;
	extern mc_addr_t LD_EXTERNAL_HOST_ALLOC_ORIG;

	extern mc_addr_t LD_CORE_MODULE_ORIG;
	extern mc_addr_t LD_CORE_MODULE_SIZE;

	#define BJK_LNK_SCRPT_SYM_VAL(xx) ((mc_addr_t)(&xx))

	#define MC_VAL_EXTERNAL_RAM_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_RAM_SIZE)
	#define MC_VAL_EXTERNAL_CODE_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_CODE_SIZE)
	#define MC_VAL_EXTERNAL_LOAD_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_LOAD_SIZE)
	#define MC_VAL_EXTERNAL_HOST_DATA_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_HOST_DATA_SIZE)
	#define MC_VAL_EXTERNAL_HOST_ALLOC_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_HOST_ALLOC_SIZE)
	#define MC_VAL_EXTERNAL_RAM_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_RAM_ORIG)
	#define MC_VAL_EXTERNAL_CODE_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_CODE_ORIG)
	#define MC_VAL_EXTERNAL_LOAD_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_LOAD_ORIG)
	#define MC_VAL_EXTERNAL_HOST_DATA_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_HOST_DATA_ORIG)
	#define MC_VAL_EXTERNAL_HOST_ALLOC_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_HOST_ALLOC_ORIG)

	#define MC_VAL_CORE_MODULE_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_CORE_MODULE_ORIG)
	#define MC_VAL_CORE_MODULE_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_CORE_MODULE_SIZE)

#endif

struct mc_aligned mc_link_syms_data_def { 
	mc_addr_t extnl_ram_size;
	mc_addr_t extnl_code_size;
	mc_addr_t extnl_load_size;
	mc_addr_t extnl_host_data_size;
	mc_addr_t extnl_host_alloc_size;
	mc_addr_t extnl_ram_orig;
	mc_addr_t extnl_code_orig;
	mc_addr_t extnl_load_orig;
	mc_addr_t extnl_host_data_orig;
	mc_addr_t extnl_host_alloc_orig;

	mc_addr_t core_module_orig;
	mc_addr_t core_module_size;

	mc_addr_t extnl_code_disp;
	mc_addr_t extnl_load_disp;
	mc_addr_t extnl_host_data_disp;
	mc_addr_t extnl_host_alloc_disp;
};
typedef struct mc_link_syms_data_def mc_link_syms_data_st;

#ifdef MC_IS_EPH_CODE
	#define MC_EXTERNAL_RAM_LOAD_DATA mck_external_ram_load_data
#else
	#define MC_EXTERNAL_RAM_LOAD_DATA mch_external_ram_load_data
#endif

void*
mc_add_lk_syms() mc_external_code_ram;

void
mc_extnl_ram_load_data_fill(mc_link_syms_data_st* syms) mc_external_code_ram;


struct mc_aligned mc_load_map_def {
	mc_core_nn_t 			num_core;
	bool 					is_loaded;
	struct mc_load_map_def**	childs;
};
typedef struct mc_load_map_def mc_load_map_st;

#define BJL_NODE_NAM(nam, aa) mc_load_ ## nam ## _node_ ## aa

#define BJL_NODE(nam, aa) (& BJL_NODE_NAM(nam, aa))

#define BJL_LEAF_NODE(nam, aa) \
	mc_load_map_st BJL_NODE_NAM(nam, aa) mc_external_data_ram = { \
		.num_core = aa, \
		.is_loaded = false, \
		.childs = mc_null \
	}; \

// end_of_macro

#define BJL_TREE_NODE(nam, aa, ...) \
	mc_load_map_st* childs_of_ ## nam ## aa [] mc_external_data_ram = { __VA_ARGS__ , mc_null }; \
	mc_load_map_st BJL_NODE_NAM(nam, aa) mc_external_data_ram = { \
		.num_core = aa, \
		.is_loaded = false, \
		.childs = childs_of_ ## nam ## aa \
	}; \

// end_of_macro

#define mc_dbg_e3_node(nn) BJL_NODE(lib_dbg_map, nn)
#define mc_dbg_e3_leaf(nn) BJL_LEAF_NODE(lib_dbg_map, nn)
#define mc_dbg_e3_tree(nn, ...) BJL_TREE_NODE(lib_dbg_map, nn, __VA_ARGS__)

#define mc_std_e3_node(nn) BJL_NODE(lib_std_map, nn)
#define mc_std_e3_leaf(nn) BJL_LEAF_NODE(lib_std_map, nn)
#define mc_std_e3_tree(nn, ...) BJL_TREE_NODE(lib_std_map, nn, __VA_ARGS__)

void
mcl_load_module(char* module_name) mc_external_code_ram;

void
mc_reset_core(mc_core_id_t id) mc_external_code_ram;

mc_inline_fn void
mc_copy_mem_to_core(mc_core_id_t koid){
	uint8_t* dst = (uint8_t*)mc_addr_set_id(koid, 0x0);
	mc_memcpy(dst, (uint8_t*)0x0, mc_core_tot_mem);
}

void
mc_prt_load_map(mc_load_map_st* mp, int lv) mc_external_code_ram;

void
mc_load_map() mc_external_code_ram;

mc_load_map_st*
mc_get_first_load_map() mc_external_code_ram;

#ifdef __cplusplus
}
#endif

#endif // MC_LOADER_H

