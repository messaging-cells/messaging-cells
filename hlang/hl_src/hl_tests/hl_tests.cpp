
#include "hlang.hh"
#include "hl_pru1.h"

int main(int argc, char *argv[]){
	int rr = 0;
	printf("STARTING_HLANG_TESTS ==================================== \n");
	
	hl_test_1(argc, argv);	

	printf("HLANG_TESTS_FINISHED ==================================== \n");
	return rr;
}

