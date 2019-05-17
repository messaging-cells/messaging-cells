

#include <stdio.h>

#include "hlang.hh"
#include "hl_send_test.h"

hconst(k0, 98);
hconst(k1, 11);
hconst(k2, 123);

hcell_class_def(cls_snd);

hnucleus_def(cls_snd, central, (
	hswitch(hmsg_tok_as(char)) >> (
		hcase(htk_start) >> mth_start(), 
		hcase(pr_tok_snd_val1) >> (
			v1 = hmsg_val, 
			hdbg(R"my_code(printf("GOT pr_tok_snd_val1\n");)my_code")
		),
		hcase(pr_tok_snd_val2) >> (
			v2 = hmsg_val_as(int),
			hdbg(R"my_code(printf("GOT pr_tok_snd_val2\n");)my_code")
		),
		hcase(pr_tok_snd_add) >> (
			sum = (v1 + v2),
			hdbg(R"my_code(printf("GOT pr_tok_snd_add\n");)my_code"),
			hsend(hmsg_src, pr_tok_snd_finished, hlit(0))
			, hfinished
		),
		hcase(pr_tok_snd_finished) >> (
			hdbg(R"my_code(printf("GOT pr_tok_snd_finished\n");)my_code")
			, hfinished
		)
	),
	hreturn
));


hmethod_def(cls_snd, mth_start, (
	hdbg(R"my_code(printf("Started mth_start\n");)my_code"),
	dst = hmsg_ref_as(cls_snd),
	hsend(dst, pr_tok_snd_val1, hcon(k1)),
	hsend(dst, pr_tok_snd_val2, hcon(k2)),
	hsend(dst, pr_tok_snd_add, hcon(k0)),
	hdbg(R"my_code(printf("Ended mth_start\n");)my_code")
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

