
#include "actor.hh"
#include "common.h"

long some_glb_val bj_comm_dat = 6;

comm_cla some_comm_obj bj_comm_dat;

void comm_f1_core(){
	//comm_cla oo;
	prts("comm_f1_core \n");
	comm_f2_core();
}

void comm_f2_core(){
	//actor a;
	prts("comm_f2_core \n");
}

void comm_prt(char* val){
}

void
comm_cla::method1(){
}

comm_cla::comm_cla(){
	init_me();
}

comm_cla::~comm_cla(){
}

void
comm_cla::init_me(){
	aa = 7;
	bb = 33;
}

