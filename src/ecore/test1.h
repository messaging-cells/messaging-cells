
// test1.h

#ifndef TEST1_H
#define TEST1_H

#ifdef __cplusplus
extern "C" {
#endif

struct pru_def {
	uint8_t vv1;
	uint16_t aa;
	uint32_t bb;
	uint64_t cc;
};
typedef struct pru_def pru_st;

#define tot_objs 5

void 
cpp_main();
	
	
#ifdef __cplusplus
}
#endif

#endif // TEST1_H

