
#include <new>

#include "actor.hh"

#include "thread_emu.hh"

kernel*
kernel::get_sys(){
	if(bj_is_host_thread()){
		EMU_CK(bjm_pt_THE_KERNEL != bj_null);
		return bjm_pt_THE_KERNEL;
	}
	return &(bjk_get_thread_info()->bjk_THE_KERNEL);
}

void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq) {
	bjk_abort((bj_addr_t)bjk_send_irq, const_cast<char*>("bjk_send_irq abort"));
}

