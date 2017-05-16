
#include <new>

#include "actor.hh"

#include "thread_emu.hh"

kernel*
kernel::get_sys(){
	return &(bjk_get_emu_info()->emu_THE_KERNEL);
}

void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq) {
	bjk_abort((bj_addr_t)bjk_send_irq, const_cast<char*>("bjk_send_irq abort"));
}

