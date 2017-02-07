

// bj_shared_data.h

#ifndef BJ_SHARED_DATA_H
#define BJ_SHARED_DATA_H

#include <stdbool.h>
#include <inttypes.h>
#include "attribute.h"
#include "rr_array.h"

#ifdef __cplusplus
extern "C"
{
#endif

//======================================================================
// epiphany version dependant definitions
	
// epiphany III
	
#define bj_axis_bits	6
#define bj_axis_mask	0x3f
	
typedef uint16_t bj_id_t;	// e_coreid_t
typedef uint16_t bj_coor_t;
typedef uint32_t bj_consec_t;

typedef uint32_t bj_addr_t;
typedef uint16_t bj_core_addr_t;
typedef uint16_t bj_size_t;

#define bj_addr_val_in_p16(p16) ((bj_addr_t)(bj_v32_of_p16(p16)))

#define bj_e3_xx 32
#define bj_e3_yy 8
#define bj_e3_xx_sz 4
#define bj_e3_yy_sz 4

#define bj_e3_num_cores 16

#define bj_glb_id_mask		0xfff00000
#define bj_glb_addr_mask	0x000fffff
#define bj_glb_addr_sz	20

//======================================================================
// working system struct
	
#define bj_null 0x0
#define bj_align(aa)	__attribute__ ((aligned (aa)))

#define bj_sys_max_cores bj_e3_num_cores

struct bj_align(8) bj_sys_def { 
	bj_coor_t 	xx;		// absolute xx epiphany space coordinates
	bj_coor_t 	yy;		// absolute yy epiphany space coordinates
	bj_coor_t 	xx_sz;		// this running sys number of ekores in xx axis (sys length)
	bj_coor_t 	yy_sz;		// this running sys number of ekores in yy axis (sys witdh)
};
typedef struct bj_sys_def bj_sys_st;

extern bj_sys_st bj_glb_sys;

void bj_inline_fn
bj_init_glb_sys() {
	bj_glb_sys.xx = bj_e3_xx;
	bj_glb_sys.yy = bj_e3_yy;
	bj_glb_sys.xx_sz = bj_e3_xx_sz;
	bj_glb_sys.yy_sz = bj_e3_yy_sz;
}

void bj_inline_fn
bj_init_glb_sys_with(bj_coor_t xx_val, bj_coor_t yy_val, bj_coor_t xx_sz_val, bj_coor_t yy_sz_val){
	bj_glb_sys.xx = xx_val;
	bj_glb_sys.yy = yy_val;
	bj_glb_sys.xx_sz = xx_sz_val;
	bj_glb_sys.yy_sz = yy_sz_val;
}

#define bjh_init_glb_sys_with_dev(dev) \
	bj_init_glb_sys_with((dev)->row, (dev)->col, (dev)->rows, (dev)->cols)
	
// end_of_macro
	
//======================================================================
// convertion functions
	
// xx and yy are absolute epiphany space coordinates
// ro and co are relative epiphany space coordinates with respect to the 
// 		allocated running cores (bj_glb_sys)
// id is the coreid absolute in epiphany space 
// nn is a consec with respect to the allocated running cores (bj_glb_sys)

#define bj_min_xx_sys (bj_glb_sys.xx)
#define bj_max_xx_sys (bj_min_xx_sys + (bj_glb_sys.xx_sz))
#define bj_min_yy_sys (bj_glb_sys.yy)
#define bj_max_yy_sys (bj_min_yy_sys + (bj_glb_sys.yy_sz))


#define bj_id_to_xx(id)	(((id) >> bj_axis_bits) & bj_axis_mask)
#define bj_id_to_yy(id)	((id) & bj_axis_mask)
#define bj_xx_to_ro(xx)	((xx) - bj_min_xx_sys)
#define bj_yy_to_co(yy)	((yy) - bj_min_yy_sys)
#define bj_id_to_ro(id)	bj_xx_to_ro(bj_id_to_xx(id))
#define bj_id_to_co(id)	bj_yy_to_co(bj_id_to_yy(id))
#define bj_ro_to_xx(ro)	((ro) + bj_min_xx_sys)
#define bj_co_to_yy(co)	((co) + bj_min_yy_sys)
#define bj_ro_co_to_nn(ro, co) (((ro) * (bj_glb_sys.yy_sz)) + (co))
#define bj_xx_yy_to_id(xx, yy) (((xx) << bj_axis_bits) + (yy))
#define bj_ro_co_to_id(ro, co) ((bj_ro_to_xx(ro) << bj_axis_bits) + bj_co_to_yy(co))
#define bj_nn_to_ro(nn)	((nn) / (bj_glb_sys.yy_sz))
#define bj_nn_to_co(nn)	((nn) % (bj_glb_sys.yy_sz))
#define bj_id_to_nn(id) (bj_ro_co_to_nn(bj_id_to_ro(id), bj_id_to_co(id)))
#define bj_nn_to_id(nn) (bj_ro_co_to_id(bj_nn_to_ro(nn), bj_nn_to_co(nn)))

#define bj_xx_in_sys(xx) (((xx) >= bj_min_xx_sys) && ((xx) < bj_max_xx_sys))
#define bj_yy_in_sys(yy) (((yy) >= bj_min_yy_sys) && ((yy) < bj_max_yy_sys))
#define bj_xx_yy_in_sys(xx, yy) (bj_xx_in_sys(xx) && bj_yy_in_sys(yy))

//======================================================================
// address functions

#define bj_addr_mask_id(addr) (((bj_addr_t)(addr)) & bj_glb_id_mask)
#define bj_addr_mask_ad(addr) (((bj_addr_t)(addr)) & bj_glb_addr_mask)

#define bj_addr_is_global(addr) bj_addr_mask_id(addr)
#define bj_addr_get_coreid(addr) ((bj_id_t)(bj_addr_mask_id(addr) >> bj_glb_addr_sz))
#define bj_addr_with(id, addr) ((bj_addr_t)((((bj_addr_t)(id)) << bj_glb_addr_sz) | bj_addr_mask_ad(addr)))

bj_id_t bj_inline_fn
bjk_get_coreid(void) {
	bj_id_t koid = 0x0; 
	bj_asm("movfs %0, coreid" : "=r" (koid));
	return koid;
}

bool bj_inline_fn
bj_addr_in_core(bj_addr_t addr, bj_id_t koid) {
	bj_id_t addr_koid = bj_addr_get_coreid(addr);
	return ((addr_koid == 0) || (addr_koid == koid));
}

bool bj_inline_fn
bj_addr_in_sys(bj_addr_t addr) {
	bj_id_t addr_koid = bj_addr_get_coreid(addr);
	bj_coor_t xx = bj_id_to_xx(addr_koid);
	bj_coor_t yy = bj_id_to_yy(addr_koid);
	return bj_xx_yy_in_sys(xx, yy);
}

	
//======================================================================
// sane alignment/access functions

#define BJ_IS_ALIGNED_16(ptr) ((((uintptr_t)ptr) & 0x1) == 0)
#define BJ_IS_ALIGNED_32(ptr) ((((uintptr_t)ptr) & 0x3) == 0)
#define BJ_IS_ALIGNED_64(ptr) ((((uintptr_t)ptr) & 0x7) == 0)
//define BJ_IS_ALIGNED(ptr, agn) ((((uintptr_t)ptr) & (agn - 1)) == 0)

bj_opt_sz_fn uint8_t 
bj_get_aligment(void* ptr);

uint32_t bj_inline_fn
bj_v32_of_p16(uint16_t* p16){
	uint32_t v32 = p16[1];
	v32 <<= 16;
	v32 |= p16[0];
	return v32;
}

#define bj_set_off_chip_var(var, val) \
	(var) = (val); \
	while((var) != (val)); \
		
// end_macro
	

//======================================================================
// bitarray

// where 'a' is the byte stream pointer, and b is the bit number.

#define bj_div8(b)	((b)>>3)
#define bj_mod8(b)	((b)&7)

#define bj_get_bit(a, b)		((((uint8_t*)a)[bj_div8(b)] >> bj_mod8(b)) & 1)
#define bj_set_bit(a, b)		(((uint8_t*)a)[bj_div8(b)] |= (1 << bj_mod8(b)))
#define bj_reset_bit(a, b) 	(((uint8_t*)a)[bj_div8(b)] &= ~(1 << bj_mod8(b)))
#define bj_toggle_bit(a, b) 	(((uint8_t*)a)[bj_div8(b)] ^= (1 << bj_mod8(b)))

#define bj_to_bytes(num_bits)	(bj_div8(num_bits) + (bj_mod8(num_bits) > 0))
#define bj_to_bits(num_bytes)	(num_bytes * k_num_bits_byte)

#define bj_mem_2K   2048
#define bj_mem_16K   16384
#define bj_mem_32K   32768
#define bj_max_core_addr 0x7ff0
#define bj_max_opcodes_func 16384

#define BJ_MAGIC_ID 0xaabbccdd
#define BJ_MAGIC_END 0x6789abcd

#define BJ_ABORT_ERR 				0xdeadbeaf
#define BJ_CALL_STACK_TRACE_ERR		0x01234567

#define BJ_MAX_CALL_STACK_SZ	20

struct bj_align(8) bj_in_core_shared_data_def { 
	// CAREFUL !! sometimes aligment(ekore) != aligment(host). bj_align(8) SHOULD SOLVE that.
	uint32_t 	magic_id;
	void** 		dbg_stack_trace;
	
	uint32_t 	dbg_error_code;
	uint32_t 	dbg_progress_flag;

	bj_id_t 	the_coreid;
	
	uint8_t 	cpp_fun1;
	uint8_t 	cpp_dcla1;
	uint8_t 	got_irq0;
	
	uint32_t 	magic_end;
};
typedef struct bj_in_core_shared_data_def bj_in_core_st;

#define BJ_NOT_FINISHED_VAL 0x21
#define BJ_FINISHED_VAL 	0xf1

#define BJ_NOT_WAITING	 	0x0
#define BJ_WAITING_ENTER	0xaa
#define BJ_WAITING_BUFFER	0xbb

struct bj_align(8) bj_off_core_shared_data_def { 
	uint32_t 	magic_id;
	bj_id_t		the_coreid;
	uint8_t 	is_finished;
	uint8_t 	is_waiting;
	bj_in_core_st* core_data;
};
typedef struct bj_off_core_shared_data_def bj_off_core_st;


#define BJ_OUT_BUFF_SZ 	bj_mem_16K
#define BJ_OUT_BUFF_MAX_OBJ_SZ 500

struct bj_align(8) bj_core_out_def { 
	uint32_t 		magic_id;
	bj_rrarray_st 	wr_arr;
	bj_rrarray_st 	rd_arr;
	uint8_t 		buff[BJ_OUT_BUFF_SZ];
};
typedef struct bj_core_out_def bj_core_out_st;


struct bj_align(8) bj_off_sys_shared_data_def { 
	uint32_t 		magic_id;
	uint32_t 		dbg_error_code;
	bj_sys_st 		wrk_sys;
	bj_off_core_st 	sys_cores[bj_sys_max_cores];
	bj_core_out_st 	sys_out_buffs[bj_sys_max_cores];
};
typedef struct bj_off_sys_shared_data_def bj_off_sys_st;

enum bj_out_obj_type_def {
	BJ_OUT_LOG,
	BJ_OUT_PRT,
	BJ_OUT_MSG
};
typedef enum bj_out_obj_type_def bj_out_type_t;

enum bj_type_def {
	BJ_CHR,
	BJ_I8,
	BJ_I16,
	BJ_I32,
	BJ_UI8,
	BJ_UI16,
	BJ_UI32,
	BJ_X8,
	BJ_X16,
	BJ_X32
};
typedef enum bj_type_def bj_type_t;

int 
bjh_prt_call_stack(const char *elf_nm, int addrs_sz, void** stack_addrs);

uint8_t*
bj_memset(uint8_t* dest, uint8_t val, bj_size_t sz);

uint8_t*
bj_memcpy(uint8_t* dest, const uint8_t* src, bj_size_t sz);

uint8_t*
bj_memmove(uint8_t* dest, const uint8_t* src, bj_size_t sz);

uint16_t 
bj_strlen(char* str) bj_code_dram;

bj_inline_fn bool
bj_isprint(char cc){
	return ((cc >= ' ' && cc <= '~') ? true : false);
}

#ifdef __cplusplus
}
#endif

#endif // BJ_SHARED_DATA_H

