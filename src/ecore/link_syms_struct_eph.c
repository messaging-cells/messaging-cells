// link_syms_struct_eph.c 

#include "global.h"

extern bj_addr_t LD_EXTERNAL_CODE_SIZE;
extern bj_addr_t LD_EXTERNAL_LOAD_SIZE;
extern bj_addr_t LD_EXTERNAL_DATA_SIZE;
extern bj_addr_t LD_EXTERNAL_ALLOC_SIZE;
extern bj_addr_t LD_EXTERNAL_ORIG;
extern bj_addr_t LD_EXTERNAL_CODE_ORIG;
extern bj_addr_t LD_EXTERNAL_LOAD_ORIG;
extern bj_addr_t LD_EXTERNAL_DATA_ORIG;
extern bj_addr_t LD_EXTERNAL_ALLOC_ORIG;

bj_link_syms_data_st bj_link_syms_values bj_lk_syms_dat = {
	.bj_val_external_code_size = BJK_LINK_SCRIPT_SYM_VAL(LD_EXTERNAL_CODE_SIZE),
	.bj_val_external_load_size = BJK_LINK_SCRIPT_SYM_VAL(LD_EXTERNAL_LOAD_SIZE),
	.bj_val_external_data_size = BJK_LINK_SCRIPT_SYM_VAL(LD_EXTERNAL_DATA_SIZE),
	.bj_val_external_alloc_size = BJK_LINK_SCRIPT_SYM_VAL(LD_EXTERNAL_ALLOC_SIZE),
	.bj_val_external_orig = BJK_LINK_SCRIPT_SYM_VAL(LD_EXTERNAL_ORIG),
	.bj_val_external_code_orig = BJK_LINK_SCRIPT_SYM_VAL(LD_EXTERNAL_CODE_ORIG),
	.bj_val_external_load_orig = BJK_LINK_SCRIPT_SYM_VAL(LD_EXTERNAL_LOAD_ORIG),
	.bj_val_external_data_orig = BJK_LINK_SCRIPT_SYM_VAL(LD_EXTERNAL_DATA_ORIG),
	.bj_val_external_alloc_orig = BJK_LINK_SCRIPT_SYM_VAL(LD_EXTERNAL_ALLOC_ORIG)
};

void*
bj_add_lk_syms(){
	return (void*)&bj_link_syms_values;
};
