
#include "cell.hh"
#include "tak_mak.hh"

void mc_cores_main() {
	mck_glb_init(false);

	tak_mak gg(123);

	mck_slog2("TAK_MAK_TEST = ");
	long val = gg.gen_rand_int32_ie(1, 1000);
	mck_ilog(val);
	mck_slog2("\n");

	mck_glb_finish();
}


