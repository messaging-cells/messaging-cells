
// bj_shared_data.h

#ifndef BJ_SHARED_DATA_H
#define BJ_SHARED_DATA_H

#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#include "attribute.h"
#include "log.h"
#include "rr_array.h"

#ifdef __cplusplus
bj_c_decl {
#endif

#define bj_false 0x00
#define bj_true 0xff

typedef uint8_t bj_bool_t;

//======================================================================
// epiphany III

#define bj_e3_xx 32
#define bj_e3_yy 8
#define bj_e3_xx_sz 4
#define bj_e3_yy_sz 4
#define bj_e3_yy_sz_pw2 2

#define bj_e3_num_chip_cores 16

#define bj_core_tot_mem		0x8000

//======================================================================
// address opers

#ifdef BJ_IS_EMU_CODE
	#include "shared_emu.h"
#endif

#ifdef BJ_IS_EPH_CODE
	#include "shared_eph.h"
#endif

#ifdef BJ_IS_ZNQ_CODE
	#include "shared_znq.h"
#endif

typedef bj_addr_t bj_size_t;
	
//======================================================================
// working system struct

#define bj_pw2(pw2) (1 << (pw2))
#define bj_div_pw2(v1, pw2) ((v1) >> (pw2))
#define bj_mod_pw2(v1, pw2) ((v1) & ((1 << (pw2)) - 1))
	
#define bj_null 0x0

#define bj_out_num_cores bj_e3_num_chip_cores

struct bj_aligned bj_sys_def { 
	bj_core_co_t 	xx;		// absolute xx epiphany space coordinates
	bj_core_co_t 	yy;		// absolute yy epiphany space coordinates
	bj_core_co_t 	xx_sz;		// this running sys number of ekores in xx axis (sys length)
	uint8_t 	 	yy_sz_pw2;		// this running sys number of ekores in yy axis (sys witdh) is (2 ^ yy_sz_pw2)
};
typedef struct bj_sys_def bj_sys_sz_st;

#ifdef BJ_IS_EPH_CODE
	extern bj_sys_sz_st 	bjk_system_sz;
	#define BJK_GLB_SYS_SZ (&bjk_system_sz)
#else
	bj_sys_sz_st*
	bj_get_glb_sys_sz();

	#define BJK_GLB_SYS_SZ bj_get_glb_sys_sz()
#endif

void bj_inline_fn
bj_init_glb_sys_sz(bj_sys_sz_st* sys_sz) {
	sys_sz->xx = bj_e3_xx;
	sys_sz->yy = bj_e3_yy;
	sys_sz->xx_sz = bj_e3_xx_sz;
	sys_sz->yy_sz_pw2 = bj_e3_yy_sz_pw2;
}

void bj_inline_fn
bj_init_glb_sys_sz_with(bj_sys_sz_st* sys_sz, bj_core_co_t xx_val, bj_core_co_t yy_val, 
				bj_core_co_t xx_sz_val, uint8_t yy_sz_pw2_val)
{
	sys_sz->xx = xx_val;
	sys_sz->yy = yy_val;
	sys_sz->xx_sz = xx_sz_val;
	sys_sz->yy_sz_pw2 = yy_sz_pw2_val;
}

#define bj_e3_co_to_pw(co) ((uint8_t)log2l(co))

#define bjh_init_glb_sys_sz_with_dev(sys_sz, dev) \
	bj_init_glb_sys_sz_with((sys_sz), (dev)->row, (dev)->col, (dev)->rows, bj_e3_co_to_pw((dev)->cols))
	
// end_of_macro


//======================================================================
// convertion functions
	
// xx and yy are absolute epiphany space coordinates
// ro and co are relative epiphany space coordinates with respect to the 
// 		allocated running cores (BJK_GLB_SYS_SZ)
// id is the core id absolute in epiphany space 
// nn is a consec with respect to the allocated running cores (BJK_GLB_SYS_SZ)

#define bj_pw2_yy_sys (BJK_GLB_SYS_SZ->yy_sz_pw2)

#define bj_tot_xx_sys (BJK_GLB_SYS_SZ->xx_sz)
#define bj_tot_yy_sys ((bj_core_co_t)(1 << bj_pw2_yy_sys))
#define bj_tot_nn_sys (bj_tot_xx_sys * bj_tot_yy_sys)

#define bj_min_xx_sys (BJK_GLB_SYS_SZ->xx)
#define bj_max_xx_sys (bj_min_xx_sys + bj_tot_xx_sys)
#define bj_min_yy_sys (BJK_GLB_SYS_SZ->yy)
#define bj_max_yy_sys (bj_min_yy_sys + bj_tot_yy_sys)

#define bj_id_to_xx(id)	(((id) >> bj_axis_bits) & bj_axis_mask)
#define bj_id_to_yy(id)	((id) & bj_axis_mask)
#define bj_xx_to_ro(xx)	((xx) - bj_min_xx_sys)
#define bj_yy_to_co(yy)	((yy) - bj_min_yy_sys)
#define bj_id_to_ro(id)	bj_xx_to_ro(bj_id_to_xx(id))
#define bj_id_to_co(id)	bj_yy_to_co(bj_id_to_yy(id))
#define bj_ro_to_xx(ro)	((ro) + bj_min_xx_sys)
#define bj_co_to_yy(co)	((co) + bj_min_yy_sys)
#define bj_ro_co_to_nn(ro, co) (((ro) * bj_tot_yy_sys) + (co))
#define bj_xx_yy_to_id(xx, yy) (((xx) << bj_axis_bits) + (yy))
#define bj_ro_co_to_id(ro, co) ((bj_ro_to_xx(ro) << bj_axis_bits) + bj_co_to_yy(co))
#define bj_nn_to_ro(nn)	bj_div_pw2(nn, bj_pw2_yy_sys)
#define bj_nn_to_co(nn)	bj_mod_pw2(nn, bj_pw2_yy_sys)
#define bj_id_to_nn(id) (bj_ro_co_to_nn(bj_id_to_ro(id), bj_id_to_co(id)))
#define bj_nn_to_id(nn) (bj_ro_co_to_id(bj_nn_to_ro(nn), bj_nn_to_co(nn)))

#define bj_xx_in_sys(xx) (((xx) >= bj_min_xx_sys) && ((xx) < bj_max_xx_sys))
#define bj_yy_in_sys(yy) (((yy) >= bj_min_yy_sys) && ((yy) < bj_max_yy_sys))
#define bj_xx_yy_in_sys(xx, yy) (bj_xx_in_sys(xx) && bj_yy_in_sys(yy))
#define bj_id_in_sys(id) (bj_xx_yy_in_sys(bj_id_to_xx(id), bj_id_to_yy(id)))


//======================================================================
// address functions 2

#ifdef BJ_IS_EPH_CODE
bj_core_id_t bj_inline_fn
bjk_get_core_id() {
	bj_core_id_t koid = 0x0; 
	bj_asm("movfs %0, coreid" : "=r" (koid));
	return koid;
}
#else
bj_core_id_t 
bjk_get_core_id();
#endif

bool bj_inline_fn
bj_addr_in_core(bj_addr_t addr, bj_core_id_t koid) {
	bj_core_id_t addr_koid = bj_addr_get_id(addr);
	return ((addr_koid == 0) || (addr_koid == koid));
}

bool bj_inline_fn
bj_addr_in_sys(bj_addr_t addr) {
	bj_core_id_t addr_koid = bj_addr_get_id(addr);
	if(addr_koid == 0){
		return true;
	}
	return bj_id_in_sys(addr_koid);
}

#define bj_addr_in_host(addr) (! bj_addr_in_sys(addr))

#define bj_dref(typ_nam, glb_pt, pt_field) ((typ_nam*)bj_addr_set_id(bj_addr_get_id(glb_pt), (glb_pt)->pt_field))

#define bjk_is_core(row, col) \
	((BJK_GLB_SYS->the_core_ro == (row)) && (BJK_GLB_SYS->the_core_co == (col)))


//======================================================================
// sane alignment/access functions

#define BJ_IS_ALIGNED_16(ptr) ((((uintptr_t)ptr) & 0x1) == 0)
#define BJ_IS_ALIGNED_32(ptr) ((((uintptr_t)ptr) & 0x3) == 0)
#define BJ_IS_ALIGNED_64(ptr) ((((uintptr_t)ptr) & 0x7) == 0)
//define BJ_IS_ALIGNED(ptr, agn) ((((uintptr_t)ptr) & (agn - 1)) == 0)

bj_opt_sz_fn uint8_t 
bj_get_aligment(void* ptr) bj_external_code_ram;

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

typedef uint8_t bjk_exception_t;

#define bjk_invalid_exception 0
#define bjk_software_exception 1
#define bjk_memory_exception 2

#define BJ_NOT_FINISHED_VAL 0x21
#define BJ_FINISHED_VAL 	0xf1

#define BJ_NOT_WAITING	 	0x0
#define BJ_WAITING_ENTER	0xaa
#define BJ_WAITING_BUFFER	0xbb

struct bj_aligned bj_off_core_shared_data_def { 
	uint32_t 		magic_id;
	bj_core_id_t	ck_core_id;
	uint8_t 		is_finished;
	uint8_t 		is_waiting;
	void* 			core_data;
};
typedef struct bj_off_core_shared_data_def bj_off_core_st;


//define BJ_OUT_BUFF_SZ 	bj_mem_16K
#define BJ_OUT_BUFF_SZ 	300
#define BJ_OUT_BUFF_MAX_OBJ_SZ 500

struct bj_aligned bj_core_out_def { 
	uint32_t 		magic_id;
	bj_rrarray_st 	wr_arr;
	bj_rrarray_st 	rd_arr;
	uint8_t 		buff[BJ_OUT_BUFF_SZ];
};
typedef struct bj_core_out_def bj_core_out_st;


struct bj_aligned bj_off_sys_shared_data_def { 
	uint32_t 		magic_id;
	uint32_t 		dbg_error_code;
	void* 			pt_this_from_znq;
	void* 			pt_this_from_eph;
	void* 			pt_host_kernel;
	bj_addr_t		znq_shared_mem_base;
	bj_addr_t		eph_shared_mem_base;

	uint32_t 		tot_modules;

	bj_core_id_t	first_load_core_id;

	bj_sys_sz_st 	wrk_sys;
	bj_off_core_st 	sys_cores[bj_out_num_cores];
	bj_core_out_st 	sys_out_buffs[bj_out_num_cores];
};
typedef struct bj_off_sys_shared_data_def bj_off_sys_st;

bj_opt_sz_fn uint8_t*
bj_memset(uint8_t* dest, uint8_t val, bj_size_t sz) bj_external_code_ram;

bj_opt_sz_fn uint8_t*
bj_memcpy(uint8_t* dest, const uint8_t* src, bj_size_t sz) bj_external_code_ram;

bj_opt_sz_fn uint8_t*
bj_memmove(uint8_t* dest, const uint8_t* src, bj_size_t sz) bj_external_code_ram;

uint16_t 
bj_strlen(char* str) bj_external_code_ram;

bj_inline_fn bool
bj_isprint(char cc){
	return ((cc >= ' ' && cc <= '~') ? true : false);
}

#define bj_init_arr_objs(sz, arr, cls) \
	for(int aa = 0; aa < sz; aa++){ \
		new (&(arr[aa])) cls(); \
	} \

// end_macro

#define bj_init_arr_vals(sz, arr, val) \
	for(int aa = 0; aa < sz; aa++){ \
		arr[aa] = (val); \
	} \

// end_macro

#define bjk_has_off_core (BJK_GLB_SYS->off_core_pt != bj_null)

bj_addr_t
bj_host_addr_to_core_addr(bj_addr_t h_addr) bj_external_code_ram;

bj_addr_t
bj_core_addr_to_host_addr(bj_addr_t c_addr) bj_external_code_ram;

#define bj_host_pt_to_core_pt(pt) (bj_host_addr_to_core_addr((bj_addr_t)(pt)))
#define bj_core_pt_to_host_pt(pt) (bj_core_addr_to_host_addr((bj_addr_t)(pt)))

#define bj_dref_field(cls_base, base, cls_field, field)	\
	((cls_field*)(uint8_t*)(((uint8_t*)base) + bj_offsetof(&cls_base::field)))


#define bjc_host_saddr_to_core_saddr(h_addr) \
	(BJK_GLB_SYS->eph_shd_mem_base + (((bj_addr_t)h_addr) - BJK_GLB_SYS->znq_shd_mem_base))


#define bjc_core_saddr_to_core_saddr(c_addr) \
	(BJK_GLB_SYS->znq_shd_mem_base + (((bj_addr_t)c_addr) - BJK_GLB_SYS->eph_shd_mem_base))


#define bjc_glb_binder_get_rgt(bdr) (((binder*)bjc_host_saddr_to_core_saddr(bdr))->bn_right)
#define bjc_glb_binder_get_lft(bdr) (((binder*)bjc_host_saddr_to_core_saddr(bdr))->bn_left)

#ifdef __cplusplus
}
#endif

#define as_pt_char(the_str) (const_cast<char *>(the_str))

#endif // BJ_SHARED_DATA_H

