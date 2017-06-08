

// loader_eph.c 

#include "global.h"
#include "all_regs.h"

bj_core_id_t 	loader_parent;
bj_load_map_st* loader_map;

bj_link_syms_data_st bjk_external_ram_load_data bj_lk_syms_dat = {
	.extnl_ram_size = BJ_VAL_EXTERNAL_RAM_SIZE,
	.extnl_code_size = BJ_VAL_EXTERNAL_CODE_SIZE,
	.extnl_load_size = BJ_VAL_EXTERNAL_LOAD_SIZE,
	.extnl_host_data_size = BJ_VAL_EXTERNAL_HOST_DATA_SIZE,
	.extnl_host_alloc_size = BJ_VAL_EXTERNAL_HOST_ALLOC_SIZE,
	.extnl_ram_orig = BJ_VAL_EXTERNAL_RAM_ORIG,
	.extnl_code_orig = BJ_VAL_EXTERNAL_CODE_ORIG,
	.extnl_load_orig = BJ_VAL_EXTERNAL_LOAD_ORIG,
	.extnl_host_data_orig = BJ_VAL_EXTERNAL_HOST_DATA_ORIG,
	.extnl_host_alloc_orig = BJ_VAL_EXTERNAL_HOST_ALLOC_ORIG,

	.core_module_orig = BJ_VAL_CORE_MODULE_ORIG,
	.core_module_size = BJ_VAL_CORE_MODULE_SIZE,

	.extnl_code_disp = 0,
	.extnl_load_disp = 0,
	.extnl_host_data_disp = 0,
	.extnl_host_alloc_disp = 0
};

void*
bj_add_lk_syms(){
	bj_extnl_ram_load_data_fill(&bjk_external_ram_load_data);
	return (void*)&bjk_external_ram_load_data;
};

void
bj_load_map(){
	if(loader_map == bj_null){
		bjk_abort((bj_addr_t)bj_load_map, "bj_load_map 1.");
	}
	BJK_CK(loader_map != bj_null);

	BJK_CK(loader_map->num_core == bj_id_to_nn(bjk_get_core_id()));
	if(loader_map->childs == bj_null){ return; }
	//int SYNC = (1 << E_SYNC);
	uint16_t SYNC = 1;
	int aa = 0;
	bj_load_map_st* ch_map = (loader_map->childs)[aa];
	for(; (ch_map != bj_null); aa++){
		ch_map = (loader_map->childs)[aa];
		bj_core_id_t ch_id = bj_nn_to_id(ch_map->num_core);

		uint8_t* dst = (uint8_t*)bj_addr_set_id(ch_id, 0x0);
		bj_memcpy(dst, (uint8_t*)0x0, bj_core_tot_mem);

		bj_load_map_st** ch_ld_map = (bj_load_map_st**)bj_addr_set_id(ch_id, &loader_map);
		bj_set_off_chip_var(*ch_ld_map, ch_map);

		uint16_t* rem_reg = (uint16_t*)bj_addr_set_id(ch_id, BJ_REG_ILATST);
		*rem_reg = SYNC;
	}
}

