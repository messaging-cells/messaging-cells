
#include "actor.hh"
#include "pru_2.h"
#include "common.h"

void m2_f1_shd(){
	prts("m2_f1_shd \n");		
}

void m2_f2_shd(){
	prts("m2_f2_shd \n");		
}

char* msg2 bj_mod2_dat = const_cast<char*>("m2_f3_core \n");
void m2_f3_core(){
	prts(msg2);
}


void m2_main() {
	prts("STARTED m2_main !!\n");	

	m2_f1_shd();
	m2_f3_core();
	m2_f2_shd();

	comm_f1_core();

	prts("FINISHED m2_main !!\n");	
}

