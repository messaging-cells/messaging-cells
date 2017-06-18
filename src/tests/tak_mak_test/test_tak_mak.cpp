
#include "cell.hh"
#include "tak_mak.hh"

void mc_cores_main() {
	bjk_glb_init();

	tak_mak gg(123);

	bjk_slog2("TAK_MAK_TEST = ");
	long val = gg.gen_rand_int32_ie(1, 1000);
	bjk_ilog(val);
	bjk_slog2("\n");

	bjk_glb_finish();
}


