

#include <stdio.h>

#include "hlang.hh"
#include "hl_mem_ops.h"

hdefine_token(tk_start);
hdefine_token(tk_write_val);
hdefine_token(tk_finished);

// TODO: WRITE CODE TO CHECK WHEN NOT ALL CLASSES ARE DEFINED.
hmissive_class_def(msv_1);		
hcell_class_def(cls_mem_ops);

hnucleus_def(cls_mem_ops, central, (
	hswitch(hmsg_tok_as(char)) /= (
		hcase(htk_start) /= mth_start(), 
		hcase(tk_write_val) /= (
			hget(hmsg_ref, htok(hid_msv_1_vv), in),
			hwait(in),
			hrelease(hmsg_ref),
			HPRT(R"("GOT in = %ld\n", in)"),
			hsend(hmsg_src, tk_finished, hlit(0))
		),
		hcase(tk_finished) /= (
			HPRT(R"("GOT tk_finished. Ending with hfinished. \n")"),
			hfinished
		)
	),
	hreturn
));


hmethod_def(cls_mem_ops, mth_start, (
	// dat MUST BE pre-inited before calling this func
	hacquire(dat),
	HPRT(R"("Started mth_start.\n")"),
	out = hlit(432),
	hset(dat, htok(hid_msv_1_vv), out),
	hwait(out),
	HPRT(R"("Ended mth_start.\n")"),
	hsend(hmsg_src, tk_write_val, dat)
));

int main(int argc, char *argv[]){
	int rr = 0;
	printf("HGENERATION_STARTING: hl_mem_ops ==================================== \n");
	
	fprintf(stdout, "######################################################\n");

	HLANG_SYS().allow_send_values("cls_mem_ops");
	HLANG_SYS().init_sys(hl_null);
	
	fprintf(stdout, "RUNNING PATH= %s \n", path_get_running_path().c_str());

	HLANG_SYS().generate_cpp_code();

	printf("HGENERATION_FINISHED: hl_mem_ops ==================================== \n");
	return rr;
}

