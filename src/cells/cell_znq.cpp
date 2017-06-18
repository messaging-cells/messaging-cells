
#include <new>

#include "booter.h"
#include "cell.hh"

#include "dyn_mem.h"

kernel* bjh_PT_THE_KERNEL = mc_null;

kernel*
bjh_get_first_kernel(){
	bjh_PT_THE_KERNEL = mc_malloc64(kernel, 1);
	return bjh_PT_THE_KERNEL;
}

void 
bjk_send_irq(mc_core_id_t koid, uint16_t num_irq) {
	bjh_abort_func((mc_addr_t)bjk_send_irq, "ERROR. Host cannot send irqs.");
}

kernel* //static 
kernel::get_core_kernel(mc_core_id_t id){
	mc_core_nn_t nn = mc_id_to_nn(id);
	mc_off_sys_st* pt_shd_data = bjz_pt_external_host_data_obj;
	bjk_glb_sys_st* glb_dat = 
		(bjk_glb_sys_st*)mc_eph_addr_to_znq_addr((mc_addr_t)(pt_shd_data->sys_cores[nn]).core_data);
	if(glb_dat == mc_null){
		return mc_null;	//not inited yet
	}
	if(glb_dat->inited_core != id){
		return mc_null;	//not inited yet
	}
	kernel* ker = (kernel*)(glb_dat->pt_core_kernel);
	ker = (kernel*)mc_eph_addr_to_znq_addr((mc_addr_t)ker);
	return ker;
}
