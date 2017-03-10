
//define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "thread_emu.hh"
#include "shared.h"
#include "booter.h"


thread_info_t* ALL_THREADS_INFO = bj_null;
int TOT_THREADS = 0;

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

#define handle_error_en(en, msg) \
		do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
		do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* Thread start function: display address near top of our stack,
	and return upper-cased copy of argv_string */

thread_info_t*
bjk_get_thread_info(){
	if(ALL_THREADS_INFO == bj_null){
		bjh_abort_func(2, "bjk_get_thread_info. NULL ALL_THREADS_INFO \n");
		return bj_null;
	}
	pthread_t slf = pthread_self();
	char thd_name[NAMELEN];
	int rc = pthread_getname_np(slf, thd_name, NAMELEN);
	if(rc != 0){
		bjh_abort_func(1, "bjk_get_thread_info. INVALID THREAD NAME \n");
		return bj_null;
	}
	uint16_t thd_idx = bj_hex_bytes_to_uint16((uint8_t*)thd_name);
	if((thd_idx < 0) || (thd_idx >= TOT_THREADS)){
		bjh_abort_func(1, "bjk_get_thread_info. INVALID thd_idx \n");
		return bj_null;
	}
	thread_info_t* info = &(ALL_THREADS_INFO[thd_idx]);
	return info;
}

static void *
thread_start(void *arg)
{
	thread_info_t *tinfo = (thread_info_t *)arg;
	char *uargv, *p;
	char thd_name[NAMELEN];

	printf("Thread %d: top of stack near %p; argv_string=%s\n",
			tinfo->thread_num, &p, tinfo->argv_string);

	pthread_t slf = pthread_self();

	printf("SELF = %ld \nINFO = %ld \nIN_NAME = %s \n", slf, tinfo->thread_id, tinfo->thread_name);

	pthread_setname_np(slf, tinfo->thread_name);
	//pthread_setname_np(slf, tinfo->argv_string);

	int rc = pthread_getname_np(slf, thd_name, NAMELEN);
	if(rc == 0){
		uint16_t idx = bj_hex_bytes_to_uint16((uint8_t*)thd_name);
		printf("%ld OUT_NAME = %s \n", slf, thd_name);
		printf("%ld IDX = %d \n", slf, idx);
	}

	uargv = strdup(tinfo->argv_string);
	if (uargv == NULL)
		handle_error("strdup");

	for (p = uargv; *p != '\0'; p++)
		*p = toupper(*p);

	return uargv;
}

// =====================================================================================

int
threads_main(int argc, char *argv[])
{
	int s, tnum, opt, num_threads;
	pthread_attr_t attr;
	int stack_size;
	void *res;

	ALL_THREADS_INFO = bj_null;

	/* The "-s" option specifies a stack size for our threads */
	printf("THREADS FLAG1\n");

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

	printf("num_threads = %d\n", num_threads);


	/* Initialize thread creation attributes */

	s = pthread_attr_init(&attr);
	if (s != 0){
		handle_error_en(s, "pthread_attr_init");
	}

	if (stack_size > 0) {
		s = pthread_attr_setstacksize(&attr, stack_size);
		if (s != 0)
			handle_error_en(s, "pthread_attr_setstacksize");
	}

	/* Allocate memory for pthread_create() arguments */

	TOT_THREADS = num_threads;
	ALL_THREADS_INFO = (thread_info_t *)calloc(num_threads, sizeof(thread_info_t));
	if (ALL_THREADS_INFO == NULL){
		handle_error("calloc");
	}

	/* Create one thread for each command-line argument */

	for (tnum = 0; tnum < num_threads; tnum++) {
		ALL_THREADS_INFO[tnum].thread_num = tnum + 1;
		ALL_THREADS_INFO[tnum].argv_string = argv[optind + tnum];

		bj_uint16_to_hex_bytes(ALL_THREADS_INFO[tnum].thread_num, (uint8_t*)(ALL_THREADS_INFO[tnum].thread_name));

		/* The pthread_create() call stores the thread ID into
			corresponding element of ALL_THREADS_INFO[] */

		//s = pthread_create(&ALL_THREADS_INFO[tnum].thread_id, &attr,
		//					&thread_start, &ALL_THREADS_INFO[tnum]);
		s = pthread_create(&ALL_THREADS_INFO[tnum].thread_id, NULL,
							&thread_start, &ALL_THREADS_INFO[tnum]);
		if (s != 0){
			handle_error_en(s, "pthread_create");
		}
	}

	/* Destroy the thread attributes object, since it is no
		longer needed */

	s = pthread_attr_destroy(&attr);
	if (s != 0){
		handle_error_en(s, "pthread_attr_destroy");
	}

	/* Now join with each thread, and display its returned value */

	for (tnum = 0; tnum < num_threads; tnum++) {
		s = pthread_join(ALL_THREADS_INFO[tnum].thread_id, &res);
		if (s != 0)
			handle_error_en(s, "pthread_join");

		printf("Joined with thread %d; returned value was %s\n",
				ALL_THREADS_INFO[tnum].thread_num, (char *) res);
		free(res);      /* Free memory allocated by thread */
	}

	free(ALL_THREADS_INFO);
	exit(EXIT_SUCCESS);
}

