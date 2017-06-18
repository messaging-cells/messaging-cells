
// broadcast_maps.c 

#include "global.h"

mc_dbg_e3_leaf(15)
mc_dbg_e3_leaf(14)
mc_dbg_e3_leaf(13)
mc_dbg_e3_leaf(12)
mc_dbg_e3_leaf(11)
mc_dbg_e3_leaf(10)
mc_dbg_e3_leaf(9)
mc_dbg_e3_leaf(8)
mc_dbg_e3_leaf(7)
mc_dbg_e3_leaf(6)
mc_dbg_e3_leaf(5)
mc_dbg_e3_leaf(4)
mc_dbg_e3_leaf(3)
mc_dbg_e3_leaf(2)
mc_dbg_e3_leaf(1)

mc_dbg_e3_tree(0, 
	mc_dbg_e3_node(1),
	mc_dbg_e3_node(2),
	mc_dbg_e3_node(3),
	mc_dbg_e3_node(4),
	mc_dbg_e3_node(5),
	mc_dbg_e3_node(6),
	mc_dbg_e3_node(7),
	mc_dbg_e3_node(8),
	mc_dbg_e3_node(9),
	mc_dbg_e3_node(10),
	mc_dbg_e3_node(11),
	mc_dbg_e3_node(12),
	mc_dbg_e3_node(13),
	mc_dbg_e3_node(14),
	mc_dbg_e3_node(15)
)


mc_std_e3_leaf(7)
mc_std_e3_leaf(8)
mc_std_e3_leaf(9)
mc_std_e3_leaf(10)
mc_std_e3_leaf(11)
mc_std_e3_leaf(12)
mc_std_e3_leaf(13)
mc_std_e3_leaf(14)
mc_std_e3_leaf(15)

mc_std_e3_tree(3, 
	mc_std_e3_node(7),
	mc_std_e3_node(8)
)

mc_std_e3_tree(4, 
	mc_std_e3_node(9),
	mc_std_e3_node(10)
)

mc_std_e3_tree(5, 
	mc_std_e3_node(11),
	mc_std_e3_node(12)
)

mc_std_e3_tree(6, 
	mc_std_e3_node(13),
	mc_std_e3_node(14),
	mc_std_e3_node(15)
)

mc_std_e3_tree(1, 
	mc_std_e3_node(3),
	mc_std_e3_node(4)
)

mc_std_e3_tree(2, 
	mc_std_e3_node(5),
	mc_std_e3_node(6)
)

mc_std_e3_tree(0, 
	mc_std_e3_node(1),
	mc_std_e3_node(2)
)

mc_load_map_st*
mc_get_first_load_map(){
	return mc_std_e3_node(0);
}


