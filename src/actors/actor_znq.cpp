
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

kernel* //static 
kernel::get_core_kernel(bj_core_id_t id){
	bj_core_nn_t nn = bj_id_to_nn(id);
	bj_off_sys_st* pt_shd_data = bjz_pt_external_data_obj;
	bjk_glb_sys_st* glb_dat = 
		(bjk_glb_sys_st*)bj_eph_addr_to_znq_addr((bj_addr_t)(pt_shd_data->sys_cores[nn]).core_data);
	if(glb_dat == bj_null){
		return bj_null;	//not inited yet
	}
	if(glb_dat->inited_core != id){
		return bj_null;	//not inited yet
	}
	kernel* ker = (kernel*)(glb_dat->pt_kernel);
	return ker;
}
