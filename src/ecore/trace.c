
#include "global.h"
#include "trace.h"


#define bjk_simm11_up(pt_i16)	(((pt_i16)[1] & 0x00FF) << 3)
#define bjk_simm11_low(pt_i16)	(((pt_i16)[0] & 0x0380) >> 7)
#define bjk_simm11_to_uint(pt_i16) (bjk_simm11_up(pt_i16) | bjk_simm11_low(pt_i16))

#define bj_get_two_compl(vv) ((bj_get_bit(&(vv), 10)) ? (-((((vv) & ~0x7FF) | (~(vv) & 0x7FF)) + 1)) : (vv))

#define bjk_uint_to_simm11_up(ui16)	((ui16) >> 3)
#define bjk_uint_to_simm11_low(ui16)	(((ui16) & 0x7) << 7)

//=====================================================================


static int16_t 
get_add_simm11(uint16_t* add_cod);
	
static void 
get_call_opcode(uint16_t opcode[2], int16_t disp);
	
uint16_t*
find_call(uint16_t* code_addr, uint16_t opcode[2]) bj_trace_code_dram;

uint16_t*
find_interrupt_call(uint16_t* code_addr) bj_trace_code_dram;

uint16_t*
find_rts(uint16_t* code_addr) bj_trace_code_dram;
	
int16_t
get_sp_disp(uint16_t* code_addr) bj_trace_code_dram;

//=====================================================================


static int16_t bj_inline_fn
get_add_simm11(uint16_t* add_cod){
	int16_t val_simm11 = 0;

	val_simm11 = bjk_simm11_to_uint(add_cod);
	val_simm11 = bj_get_two_compl(val_simm11);
	return val_simm11;
}

static void bj_inline_fn
get_call_opcode(uint16_t opcode[2], int16_t disp){
	opcode[0] = 0xd47c;
	opcode[1] = 0x2700;
	opcode[0] |= bjk_uint_to_simm11_low(disp);
	opcode[1] |= bjk_uint_to_simm11_up(disp);
}

uint16_t*
find_call(uint16_t* code_addr, uint16_t opcode[2]){
	uint16_t* addr = code_addr;
	bjk_trace_err = 0x0;
	while(addr > 0x0){
		if((addr[0] == opcode[0]) && (addr[1] == opcode[1])){
			bjk_trace_err = 0x1eee;
			break;
		}
		if((addr[0] == 0x194f) && (addr[1] == 0x0402)){	// should not find any rts
			bjk_trace_err = 0x11;
			addr = 0;
			break;
		}
		addr--;
	}
	return addr;
}

/*
 1d0:	14fc 0500 	strd r0,[sp,-0x1]
 1d4:	0512      	movfs r0,status
 1d6:	211f 0402 	movfs r1,iret
*/
uint16_t*
find_interrupt_call(uint16_t* code_addr){
	uint16_t* addr = code_addr;
	bjk_trace_err = 0x0;
	while(addr > 0x0){
		if(	(addr[0] == 0x14fc) && (addr[1] == 0x0500) && (addr[2] == 0x0512) &&
			(addr[3] == 0x211f) && (addr[4] == 0x0402)
		){
			bjk_trace_err = 0x2eee;
			break;
		}
		if((addr[0] == 0x194f) && (addr[1] == 0x0402)){	// should not find any rts
			bjk_trace_err = 0x21;
			addr = 0;
			break;
		}
		addr--;
	}
	return addr;
}

int16_t
get_sp_disp(uint16_t* code_addr){
	uint16_t* addr = code_addr;
	addr -= 2;
	uint16_t v0 = addr[0];
	uint16_t v1 = addr[1];

	bjk_trace_err = 0x0;
	
	// byte order in mem = 0b b0 is lower val for add(32)_sp_sp == 0xb00b
	// byte order in mem = 00 24 // upper val for add(32)_sp_sp == 0x2400
	if((v0 & 0xF00F) != 0xb00b){
		bjk_trace_err = 0x31;
		return 0;
	}
	if((v1 & 0xFF00) != 0x2400){
		bjk_trace_err = 0x32;
		return 0;
	}
	
	uint16_t* d_addr = addr;
	
	addr -= 2;
	v0 = addr[0];
	v1 = addr[1];
	
	// byte order in mem = 0c d0 is lower val for ldrd(32)_lr_sp == 0xd00c
	// byte order in mem = 00 20 // upper val for ldrd(32)_lr_sp == 0x2000
	if((v0 & 0xF00F) != 0xd00c){
		bjk_trace_err = 0x33;
		return 0;
	}
	if((v1 & 0xF000) != 0x2000){
		bjk_trace_err = 0x34;
		return 0;
	}

	int16_t simm11_int = get_add_simm11(d_addr);
	bjk_trace_err = 0x3eee;
	
	return simm11_int;
}

/*
 2dc:	0502      	movts status,r0
 2de:	210f 0402 	movts iret,r1
 2e2:	14ec 0500 	ldrd r0,[sp,-0x1]
 2e6:	01d2      	rti
*/

uint16_t*
find_rts(uint16_t* code_addr){
	// byte order in mem = 4F 19 // lower opcode for rts(32) == 0x194f
	// byte order in mem = 02 04 // upper opcode for rts(32) == 0x0402
	// full opcode byte order in mem for rts = 4F 19 02 04

	// changed this to work in shd mem
	uint16_t* max_addr = code_addr + bj_max_opcodes_func;	
	bjk_trace_err = 0x0;
	
	uint16_t* addr = code_addr;
	while(addr < max_addr){
		if((addr[0] == 0x194f) && (addr[1] == 0x0402)){
			bjk_trace_err = 0x4eee;
			break;
		}
		if(	(addr[0] == 0x01d2) && 
			((*(addr - 5)) == 0x0502) &&
			((*(addr - 4)) == 0x210f) &&
			((*(addr - 3)) == 0x0402) 
		)
		{	
			// found interruption ending pattern
			bjk_trace_err = 0x41;
			addr = code_addr;
			break;
		}
		addr++;
	}
	if(bjk_trace_err == 0x41){
		return 0;
	}
	if(addr == max_addr){
		bjk_trace_err = 0x42;
		return 0;
	}
	if(((bj_addr_t)(addr - code_addr)) < 2){
		bjk_trace_err = 0x43;
		return 0;
	}
	return addr;
}

void 
bjk_abort(uint32_t err, uint16_t sz_trace, void** trace) {
	if(trace == bj_null){
		sz_trace = BJ_MAX_CALL_STACK_SZ;
		trace = bjk_dbg_call_stack_trace;
	}
	if(err != (uint32_t)bjk_get_call_stack_trace){
		bjk_get_call_stack_trace(sz_trace, trace);
	}
	bj_in_core_shd.dbg_error_code = err;
	
	if((bj_off_core_pt != bj_null) && (bj_off_core_pt->magic_id == BJ_MAGIC_ID)){
		bj_set_off_chip_var(bj_off_core_pt->is_finished, BJ_FINISHED_VAL);
	}
	
	bj_asm("mov r62, %0" : : "r" (&bj_in_core_shd));
	bj_asm("mov r63, %0" : : "r" (err));
	bj_asm("gid");
	bj_asm("trap 0x3");
	bj_asm("movfs r0, pc");
	bj_asm("jalr r0");
}

uint16_t
bjk_get_call_stack_trace(uint16_t sz, void** trace) {
	// WARNING
	// This function dissasembles to find RTS calls, next SP disp, and call addrs.
	// If e-gcc changes the generated code this function MUST be updated.
	if(trace == bj_null){
		return 0;
	}
	
	//bj_memset((uint8_t*)trace, 0, sz * sizeof(void*));
	
	uint16_t* pc_val = 0;
	uint16_t* sp_val = 0;
	uint16_t* rts_addr = 0;
	uint16_t idx = 0;
	
	if(sz <= 0){
		return 0;
	}
	
	bj_asm("movfs r0, pc");	
	bj_asm("mov %0, r0" : "=r" (pc_val));
	bj_asm("mov %0, sp" : "=r" (sp_val));

	rts_addr = find_rts(pc_val);
	while(rts_addr != 0){
		if(idx == sz){
			break;
		}
		
		uint16_t disp = get_sp_disp(rts_addr);
		if(disp == 0){
			break;
		} 
		if((disp % 2) != 0){ // Is disp ever odd?. If so: bad align access ...
			bjk_abort((uint32_t)bjk_get_call_stack_trace, sz, trace);
		}
		uint8_t* aux_sp = (uint8_t*)(sp_val);
		aux_sp += disp;
		sp_val = (uint16_t*)aux_sp; // casting up!! CAREFUL. disp MUST be even num

		// get call addr
		uint16_t call_opcode[2];
		uint16_t call_disp = bj_div8(disp);
		get_call_opcode(call_opcode, call_disp);
		
		uint16_t* call_addr = find_call(pc_val, call_opcode);

		// get next pc_val
		bj_addr_t aux_addr = bj_addr_val_in_p16(sp_val);
		pc_val = (uint16_t*)aux_addr;
		
		// add trace call
		//trace[idx++] = pc_val;
		trace[idx++] = call_addr;
		
		// find next rts_addr
		rts_addr = find_rts(pc_val);
	}
	if(bjk_trace_err == 0x41){
		uint16_t* call_addr = find_interrupt_call(pc_val);
		trace[idx++] = call_addr;
	}
	return idx;
}

void 
bjk_wait_sync(uint32_t info, uint16_t sz_trace, void** trace){
	if(bj_off_core_pt == bj_null){
		bjk_abort((uint32_t)bjk_wait_sync, sz_trace, trace);
	}
	if((sz_trace != 0) && (trace != bj_null)){
		bjk_get_call_stack_trace(sz_trace, trace);
	}
	// save old_mask
	uint16_t old_mask = 0;
	bj_asm("gid" "\n\t");
	bj_asm("movfs %0, imask" : "=r" (old_mask));
	bj_asm(
		"mov r0, #0x3fe" "\n\t"
		"movts imask, r0" "\n\t"
	);
	if(info == BJ_NOT_WAITING){
		info = BJ_WAITING_ENTER;
	}
	bj_set_off_chip_var(bj_off_core_pt->is_waiting, info);
	bj_asm("gie" "\n\t");
	
	// wait for SYNC
	bj_asm("idle" "\n\t");
	
	
	// restore old_mask
	bj_asm("gid" "\n\t");
	bj_asm("movts imask, %0" : : "r" (old_mask));
	bj_set_off_chip_var(bj_off_core_pt->is_waiting, BJ_NOT_WAITING);
	bj_asm("gie" "\n\t");
}

