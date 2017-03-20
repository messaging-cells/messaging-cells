
// attribute.h

#ifndef EATING_PHILO_SHARED_H
#define EATING_PHILO_SHARED_H

#include "shared.h"

#ifdef __cplusplus
bj_c_decl {
#endif

#define MAGIC_LD 0xddbbccaa

#define NUM_PHILO 16

#define chop_kind 1
#define philo_kind 2

struct bj_align(8) load_def { 
	uint32_t 		magic_id;
	uint32_t 		kind;	
	bj_core_id_t	koid;
	void* 			in_core_pt;
};
typedef struct load_def ld_loadable_t;

struct bj_align(8) chop_def { 
	ld_loadable_t	load;
};
typedef struct chop_def ld_chopstick_t;

struct bj_align(8) philoso_def { 
	ld_loadable_t	load;
	bj_addr_t 		left_chop;
	bj_addr_t 		right_chop;
};
typedef struct philoso_def ld_philoso_t;

struct bj_align(8) input_def { 
	uint32_t	sz;
	uint8_t* 	dat;
};
typedef struct input_def ld_arr_t;

void
get_input_info(ld_arr_t& in_arr);
	
#ifdef __cplusplus
}
#endif

#endif // EATING_PHILO_SHARED_H

