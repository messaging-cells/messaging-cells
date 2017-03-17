
/*------------------------------------------------------------

binder.cpp  

binder class.

--------------------------------------------------------------*/

#include "binder.hh"

binder* // static
binder::get_glb_right_pt(binder* bdr){
	bj_core_id_t dst_id = bj_addr_get_core_id(bdr);
	binder* loc_rgt = bjk_pt_to_binderpt(bdr->bn_right);
	binder* glb_rgt = (binder*)bj_addr_with(dst_id, loc_rgt);
	return glb_rgt;
}

binder* // static
binder::get_glb_left_pt(binder* bdr){
	bj_core_id_t dst_id = bj_addr_get_core_id(bdr);
	binder* loc_lft = bjk_pt_to_binderpt(bdr->bn_left);
	binder* glb_lft = (binder*)bj_addr_with(dst_id, loc_lft);
	return glb_lft;
}

