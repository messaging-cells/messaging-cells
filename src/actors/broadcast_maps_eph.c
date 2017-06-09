
// broadcast_maps.c 

#include "global.h"

bj_dbg_e3_leaf(15)
bj_dbg_e3_leaf(14)
bj_dbg_e3_leaf(13)
bj_dbg_e3_leaf(12)
bj_dbg_e3_leaf(11)
bj_dbg_e3_leaf(10)
bj_dbg_e3_leaf(9)
bj_dbg_e3_leaf(8)
bj_dbg_e3_leaf(7)
bj_dbg_e3_leaf(6)
bj_dbg_e3_leaf(5)
bj_dbg_e3_leaf(4)
bj_dbg_e3_leaf(3)
bj_dbg_e3_leaf(2)
bj_dbg_e3_leaf(1)

bj_dbg_e3_tree(0, 
	bj_dbg_e3_node(1),
	bj_dbg_e3_node(2),
	bj_dbg_e3_node(3),
	bj_dbg_e3_node(4),
	bj_dbg_e3_node(5),
	bj_dbg_e3_node(6),
	bj_dbg_e3_node(7),
	bj_dbg_e3_node(8),
	bj_dbg_e3_node(9),
	bj_dbg_e3_node(10),
	bj_dbg_e3_node(11),
	bj_dbg_e3_node(12),
	bj_dbg_e3_node(13),
	bj_dbg_e3_node(14),
	bj_dbg_e3_node(15)
)


bj_std_e3_leaf(7)
bj_std_e3_leaf(8)
bj_std_e3_leaf(9)
bj_std_e3_leaf(10)
bj_std_e3_leaf(11)
bj_std_e3_leaf(12)
bj_std_e3_leaf(13)
bj_std_e3_leaf(14)
bj_std_e3_leaf(15)

bj_std_e3_tree(3, 
	bj_std_e3_node(7),
	bj_std_e3_node(8)
)

bj_std_e3_tree(4, 
	bj_std_e3_node(9),
	bj_std_e3_node(10)
)

bj_std_e3_tree(5, 
	bj_std_e3_node(11),
	bj_std_e3_node(12)
)

bj_std_e3_tree(6, 
	bj_std_e3_node(13),
	bj_std_e3_node(14),
	bj_std_e3_node(15)
)

bj_std_e3_tree(1, 
	bj_std_e3_node(3),
	bj_std_e3_node(4)
)

bj_std_e3_tree(2, 
	bj_std_e3_node(5),
	bj_std_e3_node(6)
)

bj_std_e3_tree(0, 
	bj_std_e3_node(1),
	bj_std_e3_node(2)
)

bj_load_map_st*
bj_get_first_load_map(){
	return bj_dbg_e3_node(0);
}


