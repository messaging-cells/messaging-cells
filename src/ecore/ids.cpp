
//----------------------------------------------------------------------
// ids.cpp

#include "ids.h"

char* all_class_ids_arr[bj_tot_class_ids];

void 
init_all_class_ids(){
	bj_class_set_id(actor);
	bj_class_set_id(message);
	bj_class_set_id(core_actor);
};
	
