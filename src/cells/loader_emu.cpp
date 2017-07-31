

// loader_emu.cpp

#include "global.h"
#include "umm_malloc.h"

#include "thread_emu.hh"

mc_load_map_st* mck_first_load_map;

mc_core_id_t
mc_map_get_parent_core_id(){
	return mck_get_emu_info()->emu_map_parent_core_id;
}

mc_load_map_st*
mc_map_get_loaded(){
	return mck_get_emu_info()->emu_map_loaded;
}

mc_core_nn_t
mc_map_get_tot_children(){
	return mck_get_emu_info()->emu_map_tot_children;
}

