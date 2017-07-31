
#include "cell.hh"

class hello : public cell {
public:
	char f1;
	void handler_1(missive* msv);
};

void 
hello::handler_1(missive* msv){
	mck_slog2("HELLO_CLASS\n");	
}

typedef void (cell::*mc_handler_t)(missive* msv);

void mc_cores_main() {
	mck_glb_init(false);

	hello ob1;

	mc_handler_t pt_fun = (mc_handler_t)(&hello::handler_1);

	(ob1.*pt_fun)(mc_null);

	mck_glb_finish();
}

