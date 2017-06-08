
// loader.h

#ifndef BJ_LOADER_H
#define BJ_LOADER_H

#include "shared.h"

#ifdef __cplusplus
bj_c_decl {
#endif

#ifdef BJ_IS_EPH_CODE

	extern bj_addr_t LD_EXTERNAL_RAM_SIZE;
	extern bj_addr_t LD_EXTERNAL_CODE_SIZE;
	extern bj_addr_t LD_EXTERNAL_LOAD_SIZE;
	extern bj_addr_t LD_EXTERNAL_HOST_DATA_SIZE;
	extern bj_addr_t LD_EXTERNAL_HOST_ALLOC_SIZE;
	extern bj_addr_t LD_EXTERNAL_RAM_ORIG;
	extern bj_addr_t LD_EXTERNAL_CODE_ORIG;
	extern bj_addr_t LD_EXTERNAL_LOAD_ORIG;
	extern bj_addr_t LD_EXTERNAL_HOST_DATA_ORIG;
	extern bj_addr_t LD_EXTERNAL_HOST_ALLOC_ORIG;

	extern bj_addr_t LD_CORE_MODULE_ORIG;
	extern bj_addr_t LD_CORE_MODULE_SIZE;

	#define BJK_LNK_SCRPT_SYM_VAL(xx) ((bj_addr_t)(&xx))

	#define BJ_VAL_EXTERNAL_RAM_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_RAM_SIZE)
	#define BJ_VAL_EXTERNAL_CODE_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_CODE_SIZE)
	#define BJ_VAL_EXTERNAL_LOAD_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_LOAD_SIZE)
	#define BJ_VAL_EXTERNAL_HOST_DATA_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_HOST_DATA_SIZE)
	#define BJ_VAL_EXTERNAL_HOST_ALLOC_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_HOST_ALLOC_SIZE)
	#define BJ_VAL_EXTERNAL_RAM_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_RAM_ORIG)
	#define BJ_VAL_EXTERNAL_CODE_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_CODE_ORIG)
	#define BJ_VAL_EXTERNAL_LOAD_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_LOAD_ORIG)
	#define BJ_VAL_EXTERNAL_HOST_DATA_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_HOST_DATA_ORIG)
	#define BJ_VAL_EXTERNAL_HOST_ALLOC_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_EXTERNAL_HOST_ALLOC_ORIG)

	#define BJ_VAL_CORE_MODULE_ORIG 	BJK_LNK_SCRPT_SYM_VAL(LD_CORE_MODULE_ORIG)
	#define BJ_VAL_CORE_MODULE_SIZE 	BJK_LNK_SCRPT_SYM_VAL(LD_CORE_MODULE_SIZE)

#endif

struct bj_aligned bj_link_syms_data_def { 
	bj_addr_t extnl_ram_size;
	bj_addr_t extnl_code_size;
	bj_addr_t extnl_load_size;
	bj_addr_t extnl_host_data_size;
	bj_addr_t extnl_host_alloc_size;
	bj_addr_t extnl_ram_orig;
	bj_addr_t extnl_code_orig;
	bj_addr_t extnl_load_orig;
	bj_addr_t extnl_host_data_orig;
	bj_addr_t extnl_host_alloc_orig;

	bj_addr_t core_module_orig;
	bj_addr_t core_module_size;

	bj_addr_t extnl_code_disp;
	bj_addr_t extnl_load_disp;
	bj_addr_t extnl_host_data_disp;
	bj_addr_t extnl_host_alloc_disp;
};
typedef struct bj_link_syms_data_def bj_link_syms_data_st;

#ifdef BJ_IS_EPH_CODE
	#define BJ_EXTERNAL_RAM_LOAD_DATA bjk_external_ram_load_data
#else
	#define BJ_EXTERNAL_RAM_LOAD_DATA bjh_external_ram_load_data
#endif

void*
bj_add_lk_syms() bj_external_code_ram;

void
bj_extnl_ram_load_data_fill(bj_link_syms_data_st* syms) bj_external_code_ram;


struct bj_aligned bj_load_map_def {
	bj_core_nn_t 			num_core;
	bool 					is_loaded;
	struct bj_load_map_def**	childs;
};
typedef struct bj_load_map_def bj_load_map_st;

#define BJL_NODE_NAM(nam, aa) bj_load_ ## nam ## _node_ ## aa

#define BJL_NODE(nam, aa) (& BJL_NODE_NAM(nam, aa))

#define BJL_LEAF_NODE(nam, aa) \
	bj_load_map_st BJL_NODE_NAM(nam, aa) bj_external_data_ram = { \
		.num_core = aa, \
		.is_loaded = false, \
		.childs = bj_null \
	}; \

// end_of_macro

#define BJL_TREE_NODE(nam, aa, ...) \
	bj_load_map_st* childs_of_ ## nam ## aa [] bj_external_data_ram = { __VA_ARGS__ , bj_null }; \
	bj_load_map_st BJL_NODE_NAM(nam, aa) bj_external_data_ram = { \
		.num_core = aa, \
		.is_loaded = false, \
		.childs = childs_of_ ## nam ## aa \
	}; \

// end_of_macro

#define bj_dbg_e3_node(nn) BJL_NODE(lib_dbg_map, nn)
#define bj_dbg_e3_leaf(nn) BJL_LEAF_NODE(lib_dbg_map, nn)
#define bj_dbg_e3_tree(nn, ...) BJL_TREE_NODE(lib_dbg_map, nn, __VA_ARGS__)

#define bj_std_e3_node(nn) BJL_NODE(lib_std_map, nn)
#define bj_std_e3_leaf(nn) BJL_LEAF_NODE(lib_std_map, nn)
#define bj_std_e3_tree(nn, ...) BJL_TREE_NODE(lib_std_map, nn, __VA_ARGS__)

void
bjl_load_module(char* module_name) bj_external_code_ram;

void
bj_reset_core(bj_core_id_t id) bj_external_code_ram;

bj_inline_fn void
bj_copy_mem_to_core(bj_core_id_t koid){
	uint8_t* dst = (uint8_t*)bj_addr_set_id(koid, 0x0);
	bj_memcpy(dst, (uint8_t*)0x0, bj_core_tot_mem);
}

void
bj_prt_load_map(bj_load_map_st* mp, int lv) bj_external_code_ram;

void
bj_load_map() bj_external_code_ram;

bj_load_map_st*
bj_get_first_load_map() bj_external_code_ram;

#ifdef __cplusplus
}
#endif

#endif // BJ_LOADER_H

