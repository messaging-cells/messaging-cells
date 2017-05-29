
//include <new>

#include "all_regs.h"

#include "err_msgs.h"
#include "actor.hh"
#include "dyn_mem.h"

kernel* bjk_PT_THE_KERNEL = bj_null;

kernel*
bjk_get_first_kernel(){
	bjk_PT_THE_KERNEL = bj_malloc32(kernel, 1);
	return bjk_PT_THE_KERNEL;
}

void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq) {
	unsigned* ilatst = (unsigned*)bj_addr_set_id(koid, (void*) BJ_REG_ILATST);
	*ilatst = 1 << num_irq;
}

kernel* //static 
kernel::get_core_kernel(bj_core_id_t id){
	bjk_abort((bj_addr_t)&(kernel::get_core_kernel), err_14);
	return bj_null;
}
