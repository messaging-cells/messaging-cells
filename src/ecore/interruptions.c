
#include "interruptions.h"
#include "shared.h"
#include "global.h"

#pragma GCC diagnostic error "-Wattributes"

void
bjk_sync_handler(){	// must be set afer normal start in glb init // IVT_RESET
	// nedded for logs
}

void
bjk_software_exception_handler(){ 	// ivt_entry_software_exception
	bjk_simple_abort(bjk_software_exception_handler);
}

void
bjk_page_miss_handler(){ 	// ivt_entry_page_miss
	test_send_irq2++;
	//bjk_simple_abort(bjk_page_miss_handler);
}

void
bjk_timer0_handler(){ 	// ivt_entry_timer0
}


