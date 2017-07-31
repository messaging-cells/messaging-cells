

// loader_znq.cpp

#include "global.h"
#include "loader.h"

mc_core_id_t
mc_map_get_parent_core_id(){
	mch_abort_func((mc_addr_t)mc_map_get_parent_core_id, "ERROR. Host cannot mc_map_get_parent_core_id.");
	return 0;
}

mc_load_map_st*
mc_map_get_loaded(){
	mch_abort_func((mc_addr_t)mc_map_get_loaded, "ERROR. Host cannot mc_map_get_loaded.");
	return mc_null;
}

mc_core_nn_t
mc_map_get_tot_children(){
	mch_abort_func((mc_addr_t)mc_map_get_tot_children, "ERROR. Host cannot mc_map_get_tot_children.");
	return 0;
}

