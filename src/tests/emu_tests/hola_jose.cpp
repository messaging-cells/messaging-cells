
#include <stdio.h>

#include "booter.h"
#include <actor.hh>

int bj_host_main(int argc, char *argv[])
{
	missive_grp_t grp1;
	grp1.tot_agts = 123;

	missive_grp_t* grp2 = &grp1;
	uint8_t* tot1 = &(grp2->tot_agts);
	uint8_t* tot2 = (uint8_t*)(((uint8_t*)grp2) + bj_offsetof(&missive_grp_t::tot_agts));
	printf("offset of all_agts in missive_grp_t ==  %lu\n", bj_offsetof(&missive_grp_t::all_agts));
	printf("tot1 %d \n", *tot1);
	printf("tot2 %d \n", *tot2);

	return 0;
}

void bj_cores_main(){
}
