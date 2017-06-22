

//	register uint16_t pt_jj asm("r40");

//include "e-lib.h"

	/*
	mc_core_id_t dst1 = mc_ro_co_to_id(0, 0);
	mc_core_id_t dst2 = mc_ro_co_to_id(0, 1);

	mck_slog2("ID 0 ="); mck_xlog(dst1); mck_slog2("\n");
	mck_slog2("ID 1 ="); mck_xlog(dst2); mck_slog2("\n");

	dst1 = mc_ro_co_to_id(0, 2);
	dst2 = mc_ro_co_to_id(0, 3);

	mck_slog2("ID 2 ="); mck_xlog(dst1); mck_slog2("\n");
	mck_slog2("ID 3 ="); mck_xlog(dst2); mck_slog2("\n");

	*/

/*
		//e_reg_write(E_REG_ILATST, (unsigned)0x00000002);
		e_irq_set(po[0] ,po[1], name_irq[0]);

		//e_reg_write(E_REG_ILATCL, (unsigned)0x00000002);
		e_irq_clear(po[0], po[1], name_irq[0]);		
		e_irq_mask(name_irq[0], E_TRUE);
		e_irq_global_mask(E_TRUE);


	ivt_entry_user

	mc_asm("mov r0, #0x1ff"); 
	mc_asm("movts imask, r0");
	mc_asm("gie");
	//mc_asm("movts ilatst, r0");

void e_irq_set(unsigned row, unsigned col, e_irq_type_t irq)
{
	unsigned *ilatst;

//	if ((row == E_SELF) || (col == E_SELF))
//		ilatst = (unsigned *) E_ILATST;
//	else
	ilatst = (unsigned *) e_get_global_address(row, col, (void *) E_REG_ILATST);

	*ilatst = 1 << (irq - E_SYNC);

	return;
}

E_SYNC         = 0,
E_SW_EXCEPTION = 1,
E_MEM_FAULT    = 2,
E_TIMER0_INT   = 3,
E_TIMER1_INT   = 4,
E_MESSAGE_INT  = 5,
E_DMA0_INT     = 6,
E_DMA1_INT     = 7,
E_USER_INT     = 9,


		MCK_MARK_PLACE(START_UGLY_WAIT);
		//while(test_send_irq2 < 1){ mc_asm("nop"); }	
		//for(uint32_t aa = 0; aa < 1234567; aa++){ mc_asm("nop"); }
		MCK_MARK_PLACE(END_UGLY_WAIT);

*/
