

#include <stdio.h>

#include "hlang.hh"
#include "hl_send_test.h"

hcell_class_def(cls_snd);

// hmsg_tok(snd_tok_t)


hnucleus_def(cls_snd, central, (
	hswitch(v1) >> (
		hcase(pr_tok_snd_start) >> mth_start(), 
		hcase(pr_tok_snd_val1) >> (v1 = hmsg_val(char)), 
		hcase(pr_tok_snd_val2) >> (v2 = hmsg_val(int)),
		hcase(pr_tok_snd_add) >> (sum = (v1 + v2))
	)
));


hmethod_def(cls_snd, mth_start, (
	dst = hmsg_ref(cls_snd),
	hsend(dst, pr_tok_snd_val1, k1),
	hsend(dst, pr_tok_snd_val2, k2),
	hsend(dst, pr_tok_snd_add, k0)
));

void hl_send_test(int argc, char *argv[])
{
	printf("hl_send_test \n");
	
	//hexternal(CLS_A, e1);
	//hconst(long, k1, 123);
	
	printf("######################################################\n");
	printf("######################################################\n");
	
	HLANG_SYS().init_sys();
	
	printf("\n End of hl_send_test\n");
}

