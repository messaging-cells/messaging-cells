
// class_ids.h

#ifndef BJ_CLASS_IDS_H
#define BJ_CLASS_IDS_H

#include <inttypes.h>

typedef uint8_t bj_clid_t;

#define bj_class_id(cls) BJ_CLASS_##cls

#define bj_class_set_id(cls) \
	all_class_ids_arr[bj_class_id(cls)] = (const_cast<char *>("{" #cls "}"));


enum bj_all_classes_ids {
	bj_invalid_id = 7,

	bj_class_id(actor),
	bj_class_id(message),
	bj_class_id(core_actor),

	bj_tot_class_ids
};

extern char* all_class_ids_arr[bj_tot_class_ids];

void 
init_all_class_ids();
	
#endif // BJ_CLASS_IDS_H

