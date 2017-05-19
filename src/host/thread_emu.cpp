
//define _GNU_SOURCE

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "attribute.h"
#include "thread_emu.hh"
#include "shared.h"
#include "booter.h"

thread_info_t* ALL_THREADS_INFO = bj_null;
int TOT_THREADS = 0;
pthread_t HOST_THREAD_ID = 0;

// =====================================================================================

uint8_t
bj_hex_to_int(uint8_t in) {
	uint8_t out = 0;
	if((in >= '0') && (in <= '9')){
		out = in - '0';
	}
	if((in >= 'a') && (in <= 'f')){
		out = (in - 'a') + 10;
	}
	if((in >= 'A') && (in <= 'F')){
		out = (in - 'A') + 10;
	}
	return out;
}

uint8_t
bj_int_to_hex(uint8_t in) {
	uint8_t out = 0;
	if((in >= 0) && (in <= 9)){
		out = '0' + in;
	}
	if((in >= 10) && (in <= 15)){
		out = 'a' + (in - 10);
	}
	return out;
}

#define bj_lo_mask	0x0f
#define bj_hi_lo_to_byte(hi, lo) (((hi) << 4) | (lo))
#define bj_byte_to_hi(bb) (((bb) >> 4) & bj_lo_mask)
#define bj_byte_to_lo(bb) ((bb) & bj_lo_mask)

uint16_t
bj_hex_bytes_to_uint16(uint8_t* hex_str) {
	uint8_t hi = bj_hi_lo_to_byte(bj_hex_to_int(hex_str[3]), bj_hex_to_int(hex_str[2]));
	uint8_t lo = bj_hi_lo_to_byte(bj_hex_to_int(hex_str[1]), bj_hex_to_int(hex_str[0]));
	uint16_t out = ((((uint16_t)hi) << 8) | ((uint16_t)lo));
	return out;
}

void
bj_uint16_to_hex_bytes(uint16_t ival, uint8_t* hex_str) {
	uint8_t* ibytes = (uint8_t*)(&ival);
	hex_str[0] = bj_int_to_hex(bj_byte_to_lo(ibytes[0]));
	hex_str[1] = bj_int_to_hex(bj_byte_to_hi(ibytes[0]));
	hex_str[2] = bj_int_to_hex(bj_byte_to_lo(ibytes[1]));
	hex_str[3] = bj_int_to_hex(bj_byte_to_hi(ibytes[1]));
	hex_str[4] = '\0';
}

// =====================================================================================

uint16_t
bjk_get_thread_idx(){
	if(ALL_THREADS_INFO == bj_null){
		bjh_abort_func(2, "get_thread_idx. NULL ALL_THREADS_INFO \n");
		return 0;
	}
	pthread_t slf = pthread_self();
	if(slf == HOST_THREAD_ID){
		bjh_abort_func(2, "get_thread_idx. Host thread. \n");
		return 0;
	}

	char thd_name[NAMELEN];
	int rc = pthread_getname_np(slf, thd_name, NAMELEN);
	if(rc != 0){
		bjh_abort_func(1, "get_thread_idx. INVALID THREAD NAME \n");
		return 0;
	}
	uint16_t thd_idx = bj_hex_bytes_to_uint16((uint8_t*)thd_name);
	if((thd_idx < 0) || (thd_idx >= TOT_THREADS)){
		bjh_abort_func(1, "get_thread_idx. INVALID thd_idx \n");
		return 0;
	}
	return thd_idx;
}

emu_info_t*
bjk_get_emu_info(){
	if(bj_is_host_thread()){
		EMU_CK(bjm_HOST_EMU_INFO != bj_null);
		return bjm_HOST_EMU_INFO;
	}
	uint16_t thd_idx = bjk_get_thread_idx();
	emu_info_t* info = &(ALL_THREADS_INFO[thd_idx].thd_emu);
	return info;
}

// =====================================================================================

#define handle_error_en(en, msg) \
		do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
		do { perror(msg); exit(EXIT_FAILURE); } while (0)

bj_core_id_t
bjk_get_addr_core_id_fn(void* addr){
	if(bjk_addr_in_host(addr)){
		EMU_CK(bjm_HOST_EMU_INFO != bj_null);
		return bjm_HOST_EMU_INFO->emu_core_id;
	}	
	bj_core_nn_t idx = bjk_get_addr_idx(addr);
	thread_info_t* info = &(ALL_THREADS_INFO[idx]);
	return info->thd_emu.emu_core_id;
}

void*
bjk_addr_with_fn(bj_core_id_t core_id, void* addr){
	//if(core_id == bjm_HOST_EMU_INFO.emu_core_id){
	//}
	bj_core_nn_t idx = bj_id_to_nn(core_id);
	void* addr2 = (void*)((uintptr_t)(&(ALL_THREADS_INFO[idx])) + bjk_get_addr_offset(addr));
	return addr2;
}

bool 
bjm_call_assert(bool vv_ck, const char* file, int line, const char* ck_str, const char* msg){
	
	if(! vv_ck){
		emu_info_t* info = bjk_get_emu_info();
		bj_core_id_t koid = info->emu_core_id;
		bj_core_nn_t core_nn = info->emu_num;
		if(bj_is_host_thread()){
			fprintf(stderr, "HOST THREAD ***********************\n");
			koid = -1;
		}
		fprintf(stderr, "------------------------------------------------------------------\n");
		fprintf(stderr, "ASSERT '%s' FAILED\n CORE_ID=%x CORE_NN=%d FILE= %s\nLINE=%d \n", 
				ck_str, koid, core_nn, file, line);
		//bj_out << get_stack_trace(file, line) << bj_eol;
		if(msg != NULL){
			fprintf(stderr, "MSG=%s\n", msg);
		}
		fprintf(stderr, "------------------------------------------------------------------\n");
		bjh_ptr_call_stack_trace();
	}
	assert(vv_ck);
	return vv_ck;
}

void
bjm_log(const char *fmt, ...){
	EMU_CK(! bj_is_host_thread());

	char pp[BJ_MAX_STR_SZ];
	va_list ap;

	va_start(ap, fmt);
	int size = vsnprintf(pp, BJ_MAX_STR_SZ, fmt, ap);
	va_end(ap);

	pp[BJ_MAX_STR_SZ - 1] = '\0';

	if(size < 0){ return; }

	bjk_slog2(pp);
}

void
bjm_printf(const char *fmt, ...){
	EMU_CK(! bj_is_host_thread());

	char pp[BJ_MAX_STR_SZ];
	va_list ap;

	va_start(ap, fmt);
	int size = vsnprintf(pp, BJ_MAX_STR_SZ, fmt, ap);
	va_end(ap);

	pp[BJ_MAX_STR_SZ - 1] = '\0';

	if(size < 0){ return; }

	emu_info_t* inf = bjk_get_emu_info();

	printf("%d:%x --> %s", inf->emu_num, inf->emu_core_id, pp);
	fflush(stdout); 
}

void *
thread_start(void *arg){

	thread_info_t *tinfo = (thread_info_t *)arg;
	pthread_t slf = pthread_self();

	pthread_setname_np(slf, tinfo->thd_emu.emu_name);

	printf("SELF = %ld \tCORE_ID = %d \tNAME = %s \n", slf, bjk_get_core_id(), tinfo->thd_emu.emu_name);

	if(tinfo->thd_emu.emu_core_func != bj_null){
		(tinfo->thd_emu.emu_core_func)();
	}

	return bj_null;
}

