
/*------------------------------------------------------------

binder.cpp  

binder class.

--------------------------------------------------------------*/

#include "binder.hh"
#include "global.h"

mc_size_t
binder::calc_size(){
	// for debug purposes (it only work on local binders)
	binder * fst, * lst, * wrk;
	mc_size_t sz = 0;

	fst = this->bn_right;
	lst = this;
	for(wrk = fst; wrk != lst; wrk = wrk->bn_right){
		sz++;
	}
	return sz;
}

