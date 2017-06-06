// link_syms_struct_eph.c 

#include "global.h"
#include "link_syms_vals.h"

bj_link_syms_data_st bjk_external_ram_load_data bj_lk_syms_dat = {
	.extnl_ram_size = BJ_VAL_EXTERNAL_RAM_SIZE,
	.extnl_code_size = BJ_VAL_EXTERNAL_CODE_SIZE,
	.extnl_load_size = BJ_VAL_EXTERNAL_LOAD_SIZE,
	.extnl_data_size = BJ_VAL_EXTERNAL_DATA_SIZE,
	.extnl_alloc_size = BJ_VAL_EXTERNAL_ALLOC_SIZE,
	.extnl_ram_orig = BJ_VAL_EXTERNAL_RAM_ORIG,
	.extnl_code_orig = BJ_VAL_EXTERNAL_CODE_ORIG,
	.extnl_load_orig = BJ_VAL_EXTERNAL_LOAD_ORIG,
	.extnl_data_orig = BJ_VAL_EXTERNAL_DATA_ORIG,
	.extnl_alloc_orig = BJ_VAL_EXTERNAL_ALLOC_ORIG,

	.core_module_orig = BJ_VAL_CORE_MODULE_ORIG,
	.core_module_size = BJ_VAL_CORE_MODULE_SIZE,

	.extnl_code_disp = 0,
	.extnl_load_disp = 0,
	.extnl_data_disp = 0,
	.extnl_alloc_disp = 0
};

void*
bj_add_lk_syms(){
	bj_extnl_ram_load_data_fill(&bjk_external_ram_load_data);
	return (void*)&bjk_external_ram_load_data;
};
