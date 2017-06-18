

// loader_eph.c 

#include "global.h"
#include "all_regs.h"
#include "umm_malloc.h"

mc_load_map_st* bjz_loader_map;
mc_load_map_st* bjk_first_load_map;

mc_link_syms_data_st bjk_external_ram_load_data mc_lk_syms_dat = {
	.extnl_ram_size = MC_VAL_EXTERNAL_RAM_SIZE,
	.extnl_code_size = MC_VAL_EXTERNAL_CODE_SIZE,
	.extnl_load_size = MC_VAL_EXTERNAL_LOAD_SIZE,
	.extnl_host_data_size = MC_VAL_EXTERNAL_HOST_DATA_SIZE,
	.extnl_host_alloc_size = MC_VAL_EXTERNAL_HOST_ALLOC_SIZE,
	.extnl_ram_orig = MC_VAL_EXTERNAL_RAM_ORIG,
	.extnl_code_orig = MC_VAL_EXTERNAL_CODE_ORIG,
	.extnl_load_orig = MC_VAL_EXTERNAL_LOAD_ORIG,
	.extnl_host_data_orig = MC_VAL_EXTERNAL_HOST_DATA_ORIG,
	.extnl_host_alloc_orig = MC_VAL_EXTERNAL_HOST_ALLOC_ORIG,

	.core_module_orig = MC_VAL_CORE_MODULE_ORIG,
	.core_module_size = MC_VAL_CORE_MODULE_SIZE,

	.extnl_code_disp = 0,
	.extnl_load_disp = 0,
	.extnl_host_data_disp = 0,
	.extnl_host_alloc_disp = 0
};

void*
mc_add_lk_syms(){
	mc_extnl_ram_load_data_fill(&bjk_external_ram_load_data);
	return (void*)&bjk_external_ram_load_data;
};

char* err_load_map_1 mc_external_data_ram = "mc_load_map. Null bjz_loader_map.";
char* err_load_map_2 mc_external_data_ram = "mc_load_map. Bad num core.";

void
mc_load_map(){
	mc_load_map_st* mp = bjz_loader_map;
	mc_core_id_t koid = bjk_get_core_id();

	/*
	bjk_sprt("STARTING_LOAD_MAP core___");
	bjk_xprt(koid);
	EPH_CODE(
		bjk_sprt("___umm_heap___");
		bjk_xprt((mc_addr_t)umm_heap);
	)
	//bjk_sprt("___BJK_GLB_SYS___");
	//bjk_xprt((mc_addr_t)BJK_GLB_SYS);
	bjk_sprt("___\n");
	*/

	if(mp == mc_null){
		if(BJK_PT_EXTERNAL_HOST_DATA->first_load_core_id != koid){
			bjk_abort((mc_addr_t)err_load_map_1, err_load_map_1);
		}
		if(bjk_first_load_map != mc_null){
			mp = bjk_first_load_map;
		} else {
			mp = mc_get_first_load_map();
		}
	}
	if(mp->num_core != mc_id_to_nn(koid)){
		//bjk_sprt("ABORTING_LOAD_MAP");
		bjk_abort((mc_addr_t)err_load_map_2, err_load_map_2);
		return;
	}

	mc_load_map_st** pt_ld_map = &bjz_loader_map;

	if(mp->childs == mc_null){ return; }

	//bjk_sprt("pt_ld_map___");
	//bjk_xprt((mc_addr_t)pt_ld_map);
	//bjk_sprt("___\n");

	//uint32_t SYNC = (1 << E_SYNC);
	//uint32_t SYNC = (1 << 0);
	uint32_t SYNC = 1;
	int aa = 0;
	mc_load_map_st* ch_map = (mp->childs)[aa];
	while(ch_map != mc_null){
		mc_core_id_t ch_id = mc_nn_to_id(ch_map->num_core);

		uint8_t* dst = (uint8_t*)mc_addr_set_id(ch_id, 0x0);

		mc_memcpy(dst, (uint8_t*)0x0, mc_core_tot_mem);

		unsigned *ivt = (unsigned*)mc_addr_set_id(ch_id, 0x0);
		mc_set_off_chip_var(*ivt, bjk_original_ivt_0);

		mc_load_map_st** ch_ld_map = (mc_load_map_st**)mc_addr_set_id(ch_id, pt_ld_map);
		mc_set_off_chip_var(*ch_ld_map, ch_map);

		uint32_t* rem_reg = (uint32_t*)mc_addr_set_id(ch_id, MC_REG_ILATST);

		//bjk_sprt("rem_reg___");
		//bjk_xprt((mc_addr_t)rem_reg);
		//bjk_sprt("___\n");

		*rem_reg = SYNC;

		aa++;
		ch_map = (mp->childs)[aa];
	}
}

/*
void
mc_prt_margin(int lv){
	while(lv-- >= 0){ bjk_sprt("   "); }
}

void
mc_prt_load_map(mc_load_map_st* mp, int lv){
	mc_prt_margin(lv);
	bjk_sprt("[");
	if(mp == mc_null){
		bjk_sprt("NULL_MAP");
		bjk_sprt("]\n");
		return;
	}
	bjk_sprt("_");
	bjk_iprt(mp->num_core);
	if(mp->childs == mc_null){
		//mc_prt_margin(lv);
		//bjk_sprt("NULL_CHILDS \n");
		bjk_sprt("_]\n");
		return;
	}
	bjk_sprt("_\n");

	int aa = 0;
	mc_load_map_st* ch_map = (mp->childs)[aa];
	while(ch_map != mc_null){
		mc_prt_load_map(ch_map, lv + 1);
		aa++;
		ch_map = (mp->childs)[aa];
	}
	
	mc_prt_margin(lv);
	bjk_sprt("]\n");
}

*/

