

#include "actor.hh"
#include "pru_1.h"
#include "pru_2.h"
#include "pru_3.h"

bj_c_decl int main();

#define map1_node(nn) BJL_NODE(map1, nn)
#define map1_leaf(nn) BJL_LEAF_NODE(map1, nn)
#define map1_tree(nn, ...) BJL_TREE_NODE(map1, nn, __VA_ARGS__)

map1_leaf(16)
map1_leaf(15)
map1_leaf(14)

map1_tree(12, map1_node(15), map1_node(16), map1_node(14))
map1_tree(13, map1_node(14))


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

