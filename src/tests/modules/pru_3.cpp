
#include "actor.hh"
#include "pru_3.h"
#include "common.h"

void m3_f1_shd(){
	prts("m3_f1_shd \n");		
}

void m3_f2_shd(){
	prts("m3_f2_shd \n");		
}

void m3_f3_core(){
	prts("m3_f3_core \n");		
}


void m3_main() {
	prts("STARTED m3_main !!\n");	

	m3_f1_shd();
	m3_f3_core();
	m3_f2_shd();

	comm_f1_core();

	prts("FINISHED m3_main !!\n");	
}

