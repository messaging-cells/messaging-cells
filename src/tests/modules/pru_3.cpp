
#include "cell.hh"
#include "pru_3.h"
#include "common.h"

void m3_f1_shd(){
	prts("mm3_f1_shd \n");		
}

void m3_f2_shd(){
	prts("mm3_f2_shd \n");		
}

char* msg3 mc_mod3_dat = const_cast<char*>("mm3_f3_core \n");
void m3_f3_core(){
	prts(msg3);
}


void m3_main() {
	prts("STARTED mm3_main !!\n");	

	m3_f1_shd();
	m3_f3_core();
	m3_f2_shd();

	comm_f1_core();

	prts("FINISHED mm3_main !!\n");	
}

