
#include "actor.hh"

char* test_string_1  bj_external_data_ram = const_cast<char*>("AAAAAAAAAA");

void
bj_pru_string(){
	//bj_asm(".section bj_strings_sect"); 
	//BJ_MARK_USED(test_string_1);
	//bj_asm(".previous"); 
}

void bj_cores_main() {
	bjk_glb_init();

	bjk_slog2("HELLO_WORLD\n");	

	bjk_glb_finish();
}

