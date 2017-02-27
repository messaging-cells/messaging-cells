
#include "interruptions.h"
#include "shared.h"
#include "global.h"

#pragma GCC diagnostic error "-Wattributes"

void
bjk_irq0_handler(){	// must be set afer normal start in glb init // IVT_RESET
	if(bjk_irq_act[0]){
		bjk_irq_act[0] = bj_false;
		bj_in_core_shd.got_irq0++;
	}
}

void
bjk_irq1_handler(){ 	// ivt_entry_software_exception
	if(bjk_irq_act[1]){
		bjk_irq_act[1] = bj_false;
		bj_in_core_shd.got_irq1++;
	} else {
		bjk_abort((uint32_t)bjk_irq1_handler, 0, bj_null);
	}
}

void
bjk_irq2_handler(){ 	// ivt_entry_page_miss
	if(bjk_irq_act[2]){
		bjk_irq_act[2] = bj_false;
		bj_in_core_shd.got_irq2++;
	}
	//bjk_abort((uint32_t)bjk_irq2_handler, 0, bj_null);
}

void
bjk_irq3_handler(){ 	// ivt_entry_timer0
	if(bjk_irq_act[3]){
		bjk_irq_act[3] = bj_false;
		bj_in_core_shd.got_irq3++;
	}
}

void
bjk_irq4_handler(){ 	// ivt_entry_timer1
	if(bjk_irq_act[4]){
		bjk_irq_act[4] = bj_false;
		bj_in_core_shd.got_irq4++;
	}
}

void
bjk_irq5_handler(){ 	// ivt_entry_message
	if(bjk_irq_act[5]){
		bjk_irq_act[5] = bj_false;
		bj_in_core_shd.got_irq5++;
	}
}

void
bjk_irq6_handler(){ 	// ivt_entry_dma0
	if(bjk_irq_act[6]){
		bjk_irq_act[6] = bj_false;
		bj_in_core_shd.got_irq6++;
	}
}

void
bjk_irq7_handler(){ 	// ivt_entry_dma1
	if(bjk_irq_act[7]){
		bjk_irq_act[7] = bj_false;
		bj_in_core_shd.got_irq7++;
	}
}

void
bjk_irq8_handler(){ 	// ivt_entry_wand
	if(bjk_irq_act[8]){
		bjk_irq_act[8] = bj_false;
		bj_in_core_shd.got_irq8++;
	}
}

void
bjk_irq9_handler(){ 	// ivt_entry_user
	if(bjk_irq_act[9]){
		bjk_irq_act[9] = bj_false;
		bj_in_core_shd.got_irq9++;
	}
}

