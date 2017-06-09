

// loader_eph.c 

#include "global.h"
#include "all_regs.h"
#include "umm_malloc.h"

bj_load_map_st* bjz_loader_map;
bj_load_map_st* bjk_first_load_map;

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

char* err_load_map_1 bj_external_data_ram = "bj_load_map. Null bjz_loader_map.";
char* err_load_map_2 bj_external_data_ram = "bj_load_map. Bad num core.";

void
bj_load_map(){
	bj_load_map_st* mp = bjz_loader_map;
	bj_core_id_t koid = bjk_get_core_id();

	/*
	bjk_sprt("STARTING_LOAD_MAP core___");
	bjk_xprt(koid);
	EPH_CODE(
		bjk_sprt("___umm_heap___");
		bjk_xprt((bj_addr_t)umm_heap);
	)
	//bjk_sprt("___BJK_GLB_SYS___");
	//bjk_xprt((bj_addr_t)BJK_GLB_SYS);
	bjk_sprt("___\n");
	*/

	if(mp == bj_null){
		if(BJK_PT_EXTERNAL_HOST_DATA->first_load_core_id != koid){
			bjk_abort((bj_addr_t)err_load_map_1, err_load_map_1);
		}
		if(bjk_first_load_map != bj_null){
			mp = bjk_first_load_map;
		} else {
			mp = bj_get_first_load_map();
		}
	}
	if(mp->num_core != bj_id_to_nn(koid)){
		//bjk_sprt("ABORTING_LOAD_MAP");
		bjk_abort((bj_addr_t)err_load_map_2, err_load_map_2);
		return;
	}

	bj_load_map_st** pt_ld_map = &bjz_loader_map;

	if(mp->childs == bj_null){ return; }

	//bjk_sprt("pt_ld_map___");
	//bjk_xprt((bj_addr_t)pt_ld_map);
	//bjk_sprt("___\n");

	//uint32_t SYNC = (1 << E_SYNC);
	//uint32_t SYNC = (1 << 0);
	uint32_t SYNC = 1;
	int aa = 0;
	bj_load_map_st* ch_map = (mp->childs)[aa];
	while(ch_map != bj_null){
		bj_core_id_t ch_id = bj_nn_to_id(ch_map->num_core);

		uint8_t* dst = (uint8_t*)bj_addr_set_id(ch_id, 0x0);

		bj_memcpy(dst, (uint8_t*)0x0, bj_core_tot_mem);

		unsigned *ivt = (unsigned*)bj_addr_set_id(ch_id, 0x0);
		bj_set_off_chip_var(*ivt, bjk_original_ivt_0);

		bj_load_map_st** ch_ld_map = (bj_load_map_st**)bj_addr_set_id(ch_id, pt_ld_map);
		bj_set_off_chip_var(*ch_ld_map, ch_map);

		uint32_t* rem_reg = (uint32_t*)bj_addr_set_id(ch_id, BJ_REG_ILATST);

		//bjk_sprt("rem_reg___");
		//bjk_xprt((bj_addr_t)rem_reg);
		//bjk_sprt("___\n");

		*rem_reg = SYNC;

		aa++;
		ch_map = (mp->childs)[aa];
	}
}

/*
void
bj_prt_margin(int lv){
	while(lv-- >= 0){ bjk_sprt("   "); }
}

void
bj_prt_load_map(bj_load_map_st* mp, int lv){
	bj_prt_margin(lv);
	bjk_sprt("[");
	if(mp == bj_null){
		bjk_sprt("NULL_MAP");
		bjk_sprt("]\n");
		return;
	}
	bjk_sprt("_");
	bjk_iprt(mp->num_core);
	if(mp->childs == bj_null){
		//bj_prt_margin(lv);
		//bjk_sprt("NULL_CHILDS \n");
		bjk_sprt("_]\n");
		return;
	}
	bjk_sprt("_\n");

	int aa = 0;
	bj_load_map_st* ch_map = (mp->childs)[aa];
	while(ch_map != bj_null){
		bj_prt_load_map(ch_map, lv + 1);
		aa++;
		ch_map = (mp->childs)[aa];
	}
	
	bj_prt_margin(lv);
	bjk_sprt("]\n");
}

*/

