

#include <stdio.h>

#include "hlang.hh"
#include "hl_get_set_test.h"

hcell_class_def(cls_gs_data);

hnucleus_def(cls_gs_data, central, (
	hswitch(hmsg_tok_as(char)) /= (
		hcase(htk_start) /= (
			dst = hmsg_ref_as(cls_gs_data),
			s1 = hlit(123),
			hset(dst, htok(hid_cls_gs_data_v1), s1),
			s1 = hlit(321),
			hset(dst, htok(hid_cls_gs_data_v2), s1),
			hget(dst, htok(hid_cls_gs_data_v1), s2),
			hdbg(R"my_code(printf("GOT htk_start.\n");)my_code"),
			hfinished
		)
	),
	hreturn
));


int main(int argc, char *argv[]){
	int rr = 0;
	printf("HGENERATION_STARTING: hl_get_set_test ==================================== \n");
	
	fprintf(stdout, "######################################################\n");

	HLANG_SYS().init_sys();
	
	fprintf(stdout, "RUNNING PATH= %s \n", path_get_running_path().c_str());

	HLANG_SYS().generate_cpp_code();

	printf("HGENERATION_FINISHED: hl_get_set_test ==================================== \n");
	return rr;
}

