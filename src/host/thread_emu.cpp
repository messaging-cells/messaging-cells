
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

#include "core_main.h"

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
		bjh_abort_func(2, "bjk_get_thread_idx. NULL ALL_THREADS_INFO \n");
		return 0;
	}
	pthread_t slf = pthread_self();
	if(slf == HOST_THREAD_ID){
		bjh_abort_func(2, "bjk_get_thread_idx. Host thread. \n");
		return 0;
	}

	char thd_name[NAMELEN];
	int rc = pthread_getname_np(slf, thd_name, NAMELEN);
	if(rc != 0){
		bjh_abort_func(1, "bjk_get_thread_idx. INVALID THREAD NAME \n");
		return 0;
	}
	uint16_t thd_idx = bj_hex_bytes_to_uint16((uint8_t*)thd_name);
	if((thd_idx < 0) || (thd_idx >= TOT_THREADS)){
		bjh_abort_func(1, "bjk_get_thread_idx. INVALID thd_idx \n");
		return 0;
	}
	return thd_idx;
}

thread_info_t*
bjk_get_thread_info(){
	uint16_t thd_idx = bjk_get_thread_idx();
	thread_info_t* info = &(ALL_THREADS_INFO[thd_idx]);
	return info;
}

// =====================================================================================

#define handle_error_en(en, msg) \
		do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
		do { perror(msg); exit(EXIT_FAILURE); } while (0)

/*
int
threads_main(int argc, char *argv[])
{
	int ss, tnum, opt, num_threads;
	pthread_attr_t attr;
	int stack_size;
	void *res;

	ALL_THREADS_INFO = bj_null;

	HOST_THREAD_ID = pthread_self();

	stack_size = -1;
	while ((opt = getopt(argc, argv, "s:")) != -1) {
		switch (opt) {
		case 's':
			stack_size = strtoul(optarg, NULL, 0);
			break;

		default:
			fprintf(stderr, "Usage: %s [-s stack-size] arg...\n",
					argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	num_threads = argc - optind;


	// Initialize thread creation attributes 

	ss = pthread_attr_init(&attr);
	if (ss != 0){
		handle_error_en(ss, "pthread_attr_init");
	}

	if (stack_size > 0) {
		ss = pthread_attr_setstacksize(&attr, stack_size);
		if (ss != 0)
			handle_error_en(ss, "pthread_attr_setstacksize");
	}

	// Allocate memory for pthread_create() arguments 

	TOT_THREADS = num_threads;
	ALL_THREADS_INFO = (thread_info_t *)calloc(TOT_THREADS, sizeof(thread_info_t));
	if (ALL_THREADS_INFO == NULL){
		handle_error("calloc");
	}

	printf("TOT_THREADS = %d\n", TOT_THREADS);

	// Create one thread for each command-line argument 

	for (tnum = 0; tnum < TOT_THREADS; tnum++) {
		ALL_THREADS_INFO[tnum].thread_num = tnum + 1;
		ALL_THREADS_INFO[tnum].argv_string = argv[optind + tnum];

		bj_uint16_to_hex_bytes(ALL_THREADS_INFO[tnum].thread_num, (uint8_t*)(ALL_THREADS_INFO[tnum].thread_name));

		// The pthread_create() call stores the thread ID into
		//	corresponding element of ALL_THREADS_INFO[] 

		//ss = pthread_create(&ALL_THREADS_INFO[tnum].thread_id, &attr,
		//					&thread_start, &ALL_THREADS_INFO[tnum]);
		ss = pthread_create(&ALL_THREADS_INFO[tnum].thread_id, NULL,
							&thread_start, &ALL_THREADS_INFO[tnum]);
		if (ss != 0){
			handle_error_en(ss, "pthread_create");
		}
	}

	// Destroy the thread attributes object, since it is no longer needed 

	ss = pthread_attr_destroy(&attr);
	if (ss != 0){
		handle_error_en(ss, "pthread_attr_destroy");
	}

	// Now join with each thread, and display its returned value 

	for (tnum = 0; tnum < TOT_THREADS; tnum++) {
		ss = pthread_join(ALL_THREADS_INFO[tnum].thread_id, &res);
		if (ss != 0)
			handle_error_en(ss, "pthread_join");

		printf("Joined with thread %d; returned value was %s\n",
				ALL_THREADS_INFO[tnum].thread_num, (char *) res);
		free(res);      // Free memory allocated by thread 
	}

	free(ALL_THREADS_INFO);
	exit(EXIT_SUCCESS);
}

bj_core_nn_t
bjk_get_addr_idx(void* addr){
	if(ALL_THREADS_INFO == bj_null){
		bjh_abort_func(5, "bjk_get_addr_idx. NULL ALL_THREADS_INFO \n");
		return 0;
	}
	if((uintptr_t)addr < (uintptr_t)ALL_THREADS_INFO){
		bjh_abort_func(6, "bjk_get_addr_idx. Invalid addr. Too small. \n");
		return 0;
	}
	if((uintptr_t)addr >= ((uintptr_t)(&(ALL_THREADS_INFO[TOT_THREADS])))){
		bjh_abort_func(6, "bjk_get_addr_idx. Invalid addr. Too big. \n");
		return 0;
	}
	bj_core_nn_t idx = ((uintptr_t)addr - (uintptr_t)ALL_THREADS_INFO) / sizeof(thread_info_t);
	return idx;
}

bool
bj_is_host_thread(){
	return (pthread_self() == HOST_THREAD_ID);
}


*/

bj_core_id_t
bjk_get_addr_core_id_fn(void* addr){
	bj_core_nn_t idx = bjk_get_addr_idx(addr);
	thread_info_t* info = &(ALL_THREADS_INFO[idx]);
	return info->bjk_core_id;
}

void*
bjk_addr_with_fn(bj_core_id_t core_id, void* addr){
	bj_core_nn_t idx = bj_id_to_nn(core_id);
	void* addr2 = (void*)((uintptr_t)(&(ALL_THREADS_INFO[idx])) + bjk_get_addr_offset(addr));
	return addr2;
}

bool 
bjm_call_assert(bool vv_ck, const char* file, int line, const char* ck_str, const char* msg){
	
	if(! vv_ck){
		fprintf(stderr, "------------------------------------------------------------------\n");
		fprintf(stderr, "ASSERT '%s' FAILED\nFILE= %s\nLINE=%d \n", ck_str, file, line);
		//bj_out << get_stack_trace(file, line) << bj_eol;
		if(msg != NULL){
			fprintf(stderr, "MSG=%s\n", msg);
		}
		fprintf(stderr, "------------------------------------------------------------------\n");
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

	thread_info_t* inf = bjk_get_thread_info();

	printf("%d:%x --> %s", inf->thread_num, inf->bjk_core_id, pp);
	fflush(stdout); 
}

void *
thread_start(void *arg){

	thread_info_t *tinfo = (thread_info_t *)arg;
	pthread_t slf = pthread_self();

	pthread_setname_np(slf, tinfo->thread_name);

	printf("SELF = %ld \tCORE_ID = %d \tNAME = %s \n", slf, bjk_get_core_id(), tinfo->thread_name);

	if(tinfo->core_func != bj_null){
		(tinfo->core_func)();
	}

	return bj_null;
}

