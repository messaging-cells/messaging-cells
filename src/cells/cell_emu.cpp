
#include <new>

#include "cell.hh"

#include "thread_emu.hh"

kernel* //static
kernel::get_sys(){
	return &(mck_get_emu_info()->emu_THE_KERNEL);
}

void 
mck_send_irq(mc_core_id_t koid, uint16_t num_irq) {
	mck_abort((mc_addr_t)mck_send_irq, const_cast<char*>("mck_send_irq abort"));
}

kernel* //static 
kernel::get_core_kernel(mc_core_id_t id){
	mc_core_nn_t nn = mc_id_to_nn(id);
	EMU_CK((0 <= nn) && (nn < TOT_THREADS));
	thread_info_t* info = &(ALL_THREADS_INFO[nn]);
	if(info->thd_emu.emu_glb_sys_data.inited_core != id){
		return mc_null;
	}
	return &(info->thd_emu.emu_THE_KERNEL);
}
