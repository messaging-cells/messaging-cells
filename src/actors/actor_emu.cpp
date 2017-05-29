
#include <new>

#include "actor.hh"

#include "thread_emu.hh"

kernel* //static
kernel::get_sys(){
	return &(bjk_get_emu_info()->emu_THE_KERNEL);
}

void 
bjk_send_irq(bj_core_id_t koid, uint16_t num_irq) {
	bjk_abort((bj_addr_t)bjk_send_irq, const_cast<char*>("bjk_send_irq abort"));
}

kernel* //static 
kernel::get_core_kernel(bj_core_id_t id){
	bj_core_nn_t nn = bj_id_to_nn(id);
	EMU_CK((0 <= nn) && (nn < TOT_THREADS));
	thread_info_t* info = &(ALL_THREADS_INFO[nn]);
	if(info->thd_emu.emu_glb_sys_data.inited_core != id){
		return bj_null;
	}
	return &(info->thd_emu.emu_THE_KERNEL);
}
