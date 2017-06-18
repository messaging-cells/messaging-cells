
#include <assert.h>
#include <inttypes.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.hh"
#include "tak_mak.hh"
#include "dlmalloc.h"
#include "booter.h"

#define KBY_SZ 1024
#define MBY_SZ 1048576

#define TEST_HEAP_SZ MBY_SZ
uint8_t test_heap[TEST_HEAP_SZ];

#define TEST_NUM_PTS 1000

#define MIN_OMC_SZ 0
#define MAX_OMC_SZ 1000

#define NUM_OPERS 1000


char* bjh_epiphany_elf_path = (const_cast<char*>("the_epiphany_executable.elf"));

void mc_cores_main(){
}

int mc_host_main(int argc, char *argv[]){
	printf("STARTING dlmalloc test \n");

	unsigned long init_val = 10;
	tak_mak gg(init_val);

	memset(test_heap, 0, sizeof(test_heap));
	mspace spc_1 = create_mspace_with_base(test_heap, TEST_HEAP_SZ, 0);

	void * ptr_array[TEST_NUM_PTS];
	memset(ptr_array, 0, sizeof(ptr_array));

	long num_miss = 0;

	if(! MC_IS_ALIGNED_64(test_heap)){
		printf("HEAP NOT ALIGNED pt=%p \n", test_heap);
	}

	for(long kk=0; kk < NUM_OPERS; kk++) {
		long ii = gg.gen_rand_int32_ie(0, TEST_NUM_PTS);
		long osz = gg.gen_rand_int32_ie(MIN_OMC_SZ, MAX_OMC_SZ);
		long op = gg.gen_rand_int32_ie(0, 10);
		if(op == 0){
			//printf("FREE ii=%ld \n", ii);
			ptr_array[ii] = mspace_realloc(spc_1, ptr_array[ii], 0);
		} else {
			//printf("ALLOC ii=%ld osz=%ld \n", ii, osz);
			ptr_array[ii] = mspace_realloc(spc_1, ptr_array[ii], osz);
			if(ptr_array[ii] == NULL){
				num_miss++;
			} else {
				assert(ptr_array[ii] > (void*)test_heap);
				assert(ptr_array[ii] < (void*)(test_heap + TEST_HEAP_SZ));
				//printf("ALLOC ii=%ld osz=%ld min=%p pt=%p max=%p \n", 
				//	ii, osz, test_heap, ptr_array[ii], (test_heap + TEST_HEAP_SZ));
				if(! MC_IS_ALIGNED_64(ptr_array[ii])){
					printf("NOT ALIGNED pt=%p \n", ptr_array[ii]);
					assert(0);
				}
			}
		}
	}
	printf("num_miss=%ld \n", num_miss);

	printf("\n\n");
	
	destroy_mspace(spc_1);
	return 0;
}

