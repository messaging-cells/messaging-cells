

#include "actor.hh"
#include "pru_1.h"
#include "pru_2.h"
#include "pru_3.h"

bj_c_decl int main();

int main() {
	bjk_glb_init();
	bjk_slog2("Modules main \n");
	bool aa = false;
	if(aa){
		m1_main();
		m2_main();
		m3_main();
	}
	bjk_glb_finish();
	return 0;
}

