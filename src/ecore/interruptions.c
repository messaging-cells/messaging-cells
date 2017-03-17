
#include "interruptions.h"
#include "shared.h"
#include "global.h"

//pragma GCC diagnostic error "-Wattributes"

void
bjk_sync_handler(){	// must be set afer normal start in glb init // IVT_RESET has irq0
	// replaces the boot routines (normal start) that call the main func 
}

void
bjk_software_exception_handler(){ 	// ivt_entry_software_exception has irq1
	bjk_simple_abort(bjk_software_exception_handler, bjk_software_exception);
}

void
bjk_page_miss_handler(){ 	// ivt_entry_page_miss has irq2
	bjk_simple_abort(bjk_page_miss_handler, bjk_memory_exception);
}

void
bjk_timer0_handler(){ 	// ivt_entry_timer0 has irq3
	test_send_irq3++;
}

