
#include "cell.hh"
#include "common.h"

long some_glb_val mc_comm_dat = 6;


// THE FOLLOWING COMMENTED LINE generates code of all 
// 		*static_initialization_and_destruction* functions
// 		*_GLOBAL__sub_I_main* functions (wrappers to the first)
//
// NEVER USE GLOBAL VARIABLES (EMULATOR WILL NOT WORK)

//comm_cla some_comm_obj mc_comm_dat;  

// INSTED USE GLOBAL POINTER AND EXPLICITLY INITIALIZE A START UP TIME

comm_cla* some_comm_obj mc_comm_dat = mc_null;

void comm_f1_core(){
	//comm_cla oo;
	prts("comm_f1_core \n");
	comm_f2_core();
}

void comm_f2_core(){
	//cell a;
	prts("comm_f2_core \n");
}

void comm_prt(char* val){
}

void
comm_cla::method1(){
}

comm_cla::comm_cla(){
	init_comm_cla();
}

comm_cla::~comm_cla(){
}

void
comm_cla::init_comm_cla(){
	aa = 7;
	bb = 33;
}

