// link_syms_struct_eph.c 

#include "global.h"

extern bj_addr_t LD_EXTERNAL_RAM_SIZE;
extern bj_addr_t LD_EXTERNAL_CODE_SIZE;
extern bj_addr_t LD_EXTERNAL_LOAD_SIZE;
extern bj_addr_t LD_EXTERNAL_DATA_SIZE;
extern bj_addr_t LD_EXTERNAL_ALLOC_SIZE;
extern bj_addr_t LD_EXTERNAL_RAM_ORIG;
extern bj_addr_t LD_EXTERNAL_CODE_ORIG;
extern bj_addr_t LD_EXTERNAL_LOAD_ORIG;
extern bj_addr_t LD_EXTERNAL_DATA_ORIG;
extern bj_addr_t LD_EXTERNAL_ALLOC_ORIG;

#define BJK_LK_VAL(vv)  BJK_LINK_SCRIPT_SYM_VAL(vv)
#define BJK_EXTRNL_BASE  BJK_LK_VAL(LD_EXTERNAL_RAM_ORIG)

bj_link_syms_data_st bjk_external_ram_load_data bj_lk_syms_dat = {
	.extnl_ram_size = BJK_LK_VAL(LD_EXTERNAL_RAM_SIZE),
	.extnl_code_size = BJK_LK_VAL(LD_EXTERNAL_CODE_SIZE),
	.extnl_load_size = BJK_LK_VAL(LD_EXTERNAL_LOAD_SIZE),
	.extnl_data_size = BJK_LK_VAL(LD_EXTERNAL_DATA_SIZE),
	.extnl_alloc_size = BJK_LK_VAL(LD_EXTERNAL_ALLOC_SIZE),
	.extnl_ram_orig = BJK_EXTRNL_BASE,
	.extnl_code_orig = BJK_LK_VAL(LD_EXTERNAL_CODE_ORIG),
	.extnl_load_orig = BJK_LK_VAL(LD_EXTERNAL_LOAD_ORIG),
	.extnl_data_orig = BJK_LK_VAL(LD_EXTERNAL_DATA_ORIG),
	.extnl_alloc_orig = BJK_LK_VAL(LD_EXTERNAL_ALLOC_ORIG),
	.extnl_code_disp = 0,
	.extnl_load_disp = 0,
	.extnl_data_disp = 0,
	.extnl_alloc_disp = 0
};

// BJK_LK_VAL(LD_EXTERNAL_ALLOC_ORIG) - BJK_EXTRNL_BASE

void*
bj_add_lk_syms(){
	bj_extnl_ram_load_data_fill(&bjk_external_ram_load_data);
	return (void*)&bjk_external_ram_load_data;
};
