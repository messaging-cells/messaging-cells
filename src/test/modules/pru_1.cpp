
#include "actor.hh"
#include "pru_1.h"
#include "common.h"

void m1_f1_shd(){
	prts("m1_f1_shd \n");
}

void m1_f2_shd(){
	prts("m1_f2_shd \n");
}

void m1_f3_core(){
	prts("m1_f3_core \n");
}


void m1_main() {
	prts("STARTED m1_main !!\n");

	m1_f1_shd();
	m1_f3_core();
	m1_f2_shd();

	comm_f1_core();

	prts("FINISHED m1_main !!\n");
}


