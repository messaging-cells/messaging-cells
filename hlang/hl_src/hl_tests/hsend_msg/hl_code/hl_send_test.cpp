

#include <stdio.h>

#include "hlang.hh"
#include "hl_send_test.h"

hdefine_token(tk_start);
hdefine_token(tk_write_val);
hdefine_token(tk_finished);

// TODO: WRITE CODE TO CHECK WHEN NOT ALL CLASSES ARE DEFINED.
hmissive_class_def(msv_1);		
hcell_class_def(cls_snd);

hnucleus_def(cls_snd, central, (
	hswitch(hmsg_tok_as(char)) /= (
		hcase(htk_start) /= mth_start(), 
		hcase(tk_write_val) /= (
			hget(hmsg_val, htok(hid_msv_1_vv), in),
			out = in,
			hdbg(R"my_code(printf("GOT tk_write_val\n");)my_code"),
			hsend(hmsg_src, tk_finished, hlit(0))
		),
		hcase(tk_finished) /= (
			hdbg(R"my_code(printf("GOT pr_tok_snd_finished. Ending with abort (no sync). \n");)my_code"),
			hfinished
		)
	),
	hreturn
));


hmethod_def(cls_snd, mth_start, (
	hdbg(R"my_code(printf("Started mth_start\n");)my_code"),
	hsend(dst, tk_write_val, dat),
	hdbg(R"my_code(printf("Ended mth_start\n");)my_code")
));

int main(int argc, char *argv[]){
	int rr = 0;
	printf("HGENERATION_STARTING: hl_send_test ==================================== \n");
	
	fprintf(stdout, "######################################################\n");

	HLANG_SYS().allow_send_values("cls_snd");
	HLANG_SYS().init_sys(hl_null);
	
	fprintf(stdout, "RUNNING PATH= %s \n", path_get_running_path().c_str());

	HLANG_SYS().generate_cpp_code();

	printf("HGENERATION_FINISHED: hl_send_test ==================================== \n");
	return rr;
}

