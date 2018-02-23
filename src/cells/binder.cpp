
/*------------------------------------------------------------

binder.cpp  

binder class.

--------------------------------------------------------------*/

#include "binder.hh"
#include "global.h"

mc_size_t
binder::calc_size(){
	// for debug purposes (it only work on local binders)
	binder* loc_ths = (binder*)mck_as_loc_pt(this);
	binder * fst, * lst, * wrk;
	mc_size_t sz = 0;

	fst = loc_ths->bn_right;
	lst = loc_ths;
	for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
		sz++;
	}
	return sz;
}

