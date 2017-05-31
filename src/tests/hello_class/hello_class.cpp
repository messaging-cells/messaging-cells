
#include "actor.hh"

class hello : public actor {
public:
	char f1;
	void handler_1(missive* msv);
};

void 
hello::handler_1(missive* msv){
	bjk_slog2("HELLO_CLASS\n");	
}

typedef void (actor::*bj_handler_t)(missive* msv);

void bj_cores_main() {
	bjk_glb_init();

	hello ob1;

	bj_handler_t pt_fun = (bj_handler_t)(&hello::handler_1);

	(ob1.*pt_fun)(bj_null);

	bjk_glb_finish();
}

