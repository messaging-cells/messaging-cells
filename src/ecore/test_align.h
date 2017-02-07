
// test_align.h

#ifndef TEST_ALIGN_H
#define TEST_ALIGN_H

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

#ifdef __cplusplus
}
#endif

#endif // TEST_ALIGN_H

