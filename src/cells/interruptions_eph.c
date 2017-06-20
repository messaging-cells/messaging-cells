
#include "interruptions_eph.h"
#include "shared.h"
#include "global.h"

//pragma GCC diagnostic error "-Wattributes"

uint32_t test_send_irq3 = 0;

void
mck_sync_handler(){	// must be set afer normal start in glb init // IVT_RESET has irq0
	// replaces the boot routines (normal start) that call the main func 
}

void
mck_software_exception_handler(){ 	// ivt_entry_software_exception has irq1
	mck_simple_abort(mck_software_exception_handler, mck_software_exception);
}

void
mck_page_miss_handler(){ 	// ivt_entry_page_miss has irq2
	mck_simple_abort(mck_page_miss_handler, mck_memory_exception);
}

void
mck_timer0_handler(){ 	// ivt_entry_timer0 has irq3
	test_send_irq3++;
}

