
#include "send_irq.hh"

int main() {
	pru_send_irq1();
	return 0;
}

void pru_send_irq1() {
	kernel::init_sys();

	if(bjk_is_core(3, 3)){
		bj_core_id_t dst = kernel::get_core_id();
		bjk_send_irq(dst, 1);	// send mem exception itself
	}

	bjk_slog2("FINISHED !!\n");	
	kernel::finish_sys();
}


