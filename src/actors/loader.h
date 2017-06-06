
// loader.h

#ifndef BJ_LOADER_H
#define BJ_LOADER_H

#include "shared.h"

#ifdef __cplusplus
bj_c_decl {
#endif


struct bj_aligned bj_load_map_def {
	bj_core_nn_t 			num_core;
	bool 					is_loaded;
	struct bj_load_map_def**	childs;
};
typedef struct bj_load_map_def bj_load_map_st;

#define BJL_NODE_NAM(nam, aa) bj_load_ ## nam ## _node_ ## aa

#define BJL_NODE(nam, aa) (& BJL_NODE_NAM(nam, aa))

#define BJL_LEAF_NODE(nam, aa) \
	bj_load_map_st BJL_NODE_NAM(nam, aa) bj_external_code_ram = { \
		.num_core = aa, \
		.is_loaded = false, \
		.childs = bj_null \
	}; \

// end_of_macro

#define BJL_TREE_NODE(nam, aa, ...) \
	bj_load_map_st* childs_of_ ## nam ## aa [] bj_external_code_ram = { __VA_ARGS__ , bj_null }; \
	bj_load_map_st BJL_NODE_NAM(nam, aa) bj_external_code_ram = { \
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

#ifdef __cplusplus
}
#endif

#endif // BJ_LOADER_H

