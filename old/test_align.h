
// test_align.h

#ifndef TEST_ALIGN_H
#define TEST_ALIGN_H

#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif

struct pru_def {
	uint8_t vv1;
	uint16_t aa;
	uint32_t bb;
	uint64_t cc;
};
typedef struct pru_def pru_st;

#define tot_objs 5

#ifdef __cplusplus
}
#endif

/*

void 
prt_host_aligns(){
	int kk;
	for(kk = 0; kk < tot_objs; kk++){
		pru_st* obj1 = &(arr[kk]);

		prt_aligns((void*)(obj1)); printf(".pt_obj1\n"); 
		prt_aligns((void*)(&(obj1->aa))); printf(".pt_aa\n"); 
		prt_aligns((void*)(&(obj1->bb))); printf(".pt_bb\n"); 
		prt_aligns((void*)(&(obj1->cc))); printf(".pt_cc\n"); 

		printf(">>>>>>>>>>>>\n");

	}
	printf("sizeof(pru_st) = %d\n", sizeof(pru_st));
}

pru_st	arr[tot_objs];

*/

#endif // TEST_ALIGN_H

