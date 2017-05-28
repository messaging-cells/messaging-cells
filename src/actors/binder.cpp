
/*------------------------------------------------------------

binder.cpp  

binder class.

--------------------------------------------------------------*/

#include "binder.hh"
#include "global.h"

bj_size_t
binder::calc_size(){
	// for debug purposes (it only work on local binders)
	binder * fst, * lst, * wrk;
	bj_size_t sz = 0;

	fst = bjk_pt_to_binderpt(this->bn_right);
	lst = this;
	for(wrk = fst; wrk != lst; wrk = bjk_pt_to_binderpt(wrk->bn_right)){
		sz++;
	}
	return sz;
}

