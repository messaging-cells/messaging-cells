
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "philo.h"


void
get_input_info(ld_arr_t& in_arr){
	in_arr.sz = (NUM_PHILO * sizeof(ld_chopstick_t)) + (NUM_PHILO * sizeof(ld_philoso_t));
	in_arr.dat = (uint8_t*) calloc(in_arr.sz);
}


