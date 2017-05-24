
#include <new>

#include "booter.h"
#include "actor.hh"

#include "dyn_mem.h"

kernel* bjh_PT_THE_KERNEL = bj_null;

kernel*
bjh_get_first_kernel(){
	bjh_PT_THE_KERNEL = bj_malloc32(kernel, 1);
	return bjh_PT_THE_KERNEL;
}

void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq) {
	bjh_abort_func((bj_addr_t)bjk_send_irq, "ERROR. Host cannot send irqs.");
}
