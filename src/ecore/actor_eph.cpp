
//include <new>

#include "all_regs.h"

#include "actor.hh"

kernel bjk_THE_KERNEL;

kernel*
kernel::get_sys(){
	return &bjk_THE_KERNEL;
}

void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq) {
	unsigned* ilatst = (unsigned*)bj_addr_with(koid, (void*) BJ_REG_ILATST);
	*ilatst = 1 << num_irq;
}

