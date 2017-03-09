
#define _GNU_SOURCE

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shared.h"
#include "booter.h"


//include "test_align.h"

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

#define NAMELEN 16

#define handle_error_en(en, msg) \
		do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
		do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct thread_info {    /* Used as argument to thread_start() */
	pthread_t 	thread_id;        /* ID returned by pthread_create() */
	uint16_t 	thread_num;       /* Application-defined thread # */
	char 		thread_name[NAMELEN];
	char 		*argv_string;      /* From command-line argument */
};

/* Thread start function: display address near top of our stack,
	and return upper-cased copy of argv_string */

static void *
thread_start(void *arg)
{
	struct thread_info *tinfo = arg;
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


#define f_nm_sz   1024
#define BJ_SHARED_MEM_START_ADDR (0x01000000)

const char* epiphany_elf_nm = "bj-core-actor.elf";

int	write_file(char* the_pth, char* the_data, long the_sz, int write_once);

char before[bj_mem_32K];
char after[bj_mem_32K];

bj_sys_sz_st bj_glb_host_sys;

/*
bj_sys_sz_st*
bj_get_glb_sys_sz(){
	return &bj_glb_sys;
}
*/

void 
prt_aligns(void* ptr){
	int8_t alg = bj_get_aligment(ptr);
	printf("%d", alg); 
}


void
get_enter(bj_off_core_st* sh_dat_1, unsigned row, unsigned col){
	// CONTINUE
	printf("CORE (%d, %d) WAITING. Type enter\n", row, col);
	getchar();
}

int 
host_main(int argc, char *argv[])
{
	unsigned row, col, max_row, max_col, core_id;
	//e_platform_t platform;
	//e_epiphany_t dev;
	//e_mem_t emem;
	char f_nm[200];
	char* all_f_nam[bj_out_num_cores];
	int num_wrk_cores;

	memset(&all_f_nam, 0, sizeof(all_f_nam));
	num_wrk_cores = 0;

	printf("sizeof(bj_off_sys_st)=%ld\n", sizeof(bj_off_sys_st));
	
	/*
	e_set_loader_verbosity(H_D0);

	e_init(NULL);
	e_reset_system();
	e_get_platform_info(&platform);

	e_alloc(&emem, BJ_SHARED_MEM_START_ADDR, sizeof(bj_off_sys_st));
	
	e_open(&dev, 0, 0, platform.rows, platform.cols);
	
	bjh_init_glb_sys_sz_with_dev(bj_get_glb_sys_sz(), &dev);

	e_reset_group(&dev);

	e_load_group(epiphany_elf_nm, &dev, 0, 0, platform.rows, platform.cols, E_FALSE);
	*/
	
	//bj_off_sys_st* pt_shd_data = (bj_off_sys_st*)emem.base;
	bj_off_sys_st* pt_shd_data = bj_null;
	BJH_CK(sizeof(*pt_shd_data) == sizeof(bj_off_sys_st));
	printf("sizeof(*pt_shd_data)=%ld\n", sizeof(*pt_shd_data));

	// init shared data.
	memset(pt_shd_data, 0, sizeof(*pt_shd_data));

	pt_shd_data->magic_id = BJ_MAGIC_ID;
	BJH_CK(pt_shd_data->magic_id == BJ_MAGIC_ID);

	bj_sys_sz_st* sys_sz = bj_get_glb_sys_sz();

	pt_shd_data->wrk_sys = *sys_sz;
	BJH_CK(ck_sys_data(&(pt_shd_data->wrk_sys)));

	max_row = 1;
	max_col = 2;
	max_row = sys_sz->xx_sz;
	max_col = sys_sz->yy_sz;

	for (row=0; row < max_row; row++){
		for (col=0; col < max_col; col++){
			core_id = bj_ro_co_to_id(row, col);
			bj_core_nn_t num_core = bj_id_to_nn(core_id);
			printf("STARTING CORE 0x%03x (%2d,%2d) NUM=%d\n", core_id, row, col, num_core);
			memset(&f_nm, 0, sizeof(f_nm));
			sprintf(f_nm, "log_core_%02d.txt", num_core);

			BJH_CK(num_core < bj_out_num_cores);
			all_f_nam[num_core] = strdup((const char*)f_nm);
			num_wrk_cores++;
			
			// init shared data.
			pt_shd_data->sys_cores[num_core].magic_id = BJ_MAGIC_ID;
			BJH_CK(pt_shd_data->sys_cores[num_core].magic_id == BJ_MAGIC_ID);

			bj_core_out_st* pt_buff = &(pt_shd_data->sys_out_buffs[num_core]);

			pt_buff->magic_id = BJ_MAGIC_ID;
			BJH_CK(pt_buff->magic_id == BJ_MAGIC_ID);

			bj_rr_init(&(pt_buff->rd_arr), BJ_OUT_BUFF_SZ, pt_buff->buff, 1);

			// Start one core
			//e_start(&dev, row, col);
		}
	}

	bool core_started[max_row][max_col];
	memset(core_started, 0, sizeof(core_started));

	bool core_finished[max_row][max_col];
	memset(core_finished, 0, sizeof(core_finished));

	bool has_work = true;	
	while(has_work){
		sched_yield();				//yield
		has_work = false;
		for (row=0; row < max_row; row++){
			for (col=0; col < max_col; col++){
				core_id = bj_ro_co_to_id(row, col);
				bj_core_nn_t num_core = bj_id_to_nn(core_id);
				bj_off_core_st* sh_dat_1 = &(pt_shd_data->sys_cores[num_core]);
				bj_core_out_st* pt_buff = &(pt_shd_data->sys_out_buffs[num_core]);

				/*if(sh_dat_1->is_finished == BJ_FINISHED_VAL){
					continue;
				}*/
				
				// Wait for core program execution to finish.
				if((sh_dat_1->core_data == 0x0) || (sh_dat_1->is_finished == 0x0)){
					has_work = true;
					BJH_CK(sh_dat_1->magic_id == BJ_MAGIC_ID);
					//if(sh_dat_1->magic_id == BJ_MAGIC_ID){ printf("."); }
					//sched_yield();				//yield
					continue;
				}
				
				BJH_CK(sh_dat_1->magic_id == BJ_MAGIC_ID);
				BJH_CK(	(sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL) ||
						(sh_dat_1->is_finished == BJ_FINISHED_VAL)
				);
				BJH_CK(sh_dat_1->the_core_id == core_id);
				if(! core_started[row][col] && (sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL)){ 
					core_started[row][col] = true;
					printf("Waiting for finish 0x%03x (%2d,%2d) NUM=%d\n", 
								core_id, row, col, num_core);
				}

				bj_in_core_st inco;
				void* 	trace[BJ_MAX_CALL_STACK_SZ];
				
				// wait for finish
				if(sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL){
					has_work = true;
					print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core], num_core);
					if(sh_dat_1->is_waiting){
						if(sh_dat_1->is_waiting == BJ_WAITING_ENTER){
							get_enter(sh_dat_1, row, col);
						}
						if(sh_dat_1->is_waiting == BJ_WAITING_BUFFER){
							print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core], num_core);
						}
						
						sh_dat_1->is_waiting = BJ_NOT_WAITING;
						/*
						int SYNC = (1 << E_SYNC);
						if (ee_write_reg(&dev, row, col, E_REG_ILATST, SYNC) == E_ERR) {
							printf("ERROR sending SYNC to (%d, %d) \n", row, col);
							break;
						}*/
					}
				} else {
					BJH_CK(sh_dat_1->is_finished == BJ_FINISHED_VAL);
	
					if(! core_finished[row][col]){
						core_finished[row][col] = true;

						print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core], num_core);
						BJH_CK(bj_rr_ck_zero(&(pt_buff->rd_arr)));
						//bj_rr_print(&(pt_buff->rd_arr));

						printf("Finished\n");
						memset(&inco, 0, sizeof(bj_in_core_st));
						//e_read(&dev, row, col, (uint32_t)sh_dat_1->core_data, 
						//			&inco, sizeof(inco));
						int err2 = prt_inko_shd_dat(&inco);
						if(err2){
							break;
						}

						memset(trace, 0, sizeof(trace));
						//e_read(&dev, row, col, (uint32_t)inco.dbg_stack_trace, 
						//			trace, sizeof(trace));
						//bjh_prt_call_stack(epiphany_elf_nm, BJ_MAX_CALL_STACK_SZ, trace);
					}

				}
			}
		}
	} // while
	
	//printf("PLATFORM row=%2d col=%2d \n", platform.row, platform.col);
	printf("sys_sz->xx=%d\n", sys_sz->xx);
	printf("sys_sz->yy=%d\n", sys_sz->yy);
	printf("sys_sz->xx_sz=%d\n", sys_sz->xx_sz);
	printf("sys_sz->yy_sz=%d\n", sys_sz->yy_sz);
	
	/*
	// Reset the workgroup
	e_reset_group(&dev); // FAILS. Why?
	e_reset_system();
	
	// Close the workgroup
	e_close(&dev);
	
	// Release the allocated buffer and finalize the
	// e-platform connection.
	e_free(&emem);
	e_finalize();
	*/

	int nn;
	for (nn=0; nn < num_wrk_cores; nn++){
		if(all_f_nam[nn] != bj_null){
			free(all_f_nam[nn]);
		}
	}

	//prt_host_aligns();

	return 0;
}

// ===============================================================================

int
threads_main(int argc, char *argv[])
{
	int s, tnum, opt, num_threads;
	struct thread_info *tinfo;
	pthread_attr_t attr;
	int stack_size;
	void *res;

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
	if (s != 0)
		handle_error_en(s, "pthread_attr_init");

	if (stack_size > 0) {
		s = pthread_attr_setstacksize(&attr, stack_size);
		if (s != 0)
			handle_error_en(s, "pthread_attr_setstacksize");
	}

	/* Allocate memory for pthread_create() arguments */

	tinfo = calloc(num_threads, sizeof(struct thread_info));
	if (tinfo == NULL)
		handle_error("calloc");

	/* Create one thread for each command-line argument */

	for (tnum = 0; tnum < num_threads; tnum++) {
		tinfo[tnum].thread_num = tnum + 1;
		tinfo[tnum].argv_string = argv[optind + tnum];

		bj_uint16_to_hex_bytes(tinfo[tnum].thread_num, (uint8_t*)(tinfo[tnum].thread_name));

		/* The pthread_create() call stores the thread ID into
			corresponding element of tinfo[] */

		//s = pthread_create(&tinfo[tnum].thread_id, &attr,
		//					&thread_start, &tinfo[tnum]);
		s = pthread_create(&tinfo[tnum].thread_id, NULL,
							&thread_start, &tinfo[tnum]);
		if (s != 0)
			handle_error_en(s, "pthread_create");
	}

	/* Destroy the thread attributes object, since it is no
		longer needed */

	s = pthread_attr_destroy(&attr);
	if (s != 0)
		handle_error_en(s, "pthread_attr_destroy");

	/* Now join with each thread, and display its returned value */

	for (tnum = 0; tnum < num_threads; tnum++) {
		s = pthread_join(tinfo[tnum].thread_id, &res);
		if (s != 0)
			handle_error_en(s, "pthread_join");

		printf("Joined with thread %d; returned value was %s\n",
				tinfo[tnum].thread_num, (char *) res);
		free(res);      /* Free memory allocated by thread */
	}

	free(tinfo);
	exit(EXIT_SUCCESS);
}

