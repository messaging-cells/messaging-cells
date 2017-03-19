

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>

#include <e-hal.h>
#include <e-loader.h>
#include <epiphany-hal-api-local.h>

#include "shared.h"
#include "booter.h"

//include "test_align.h"


#define f_nm_sz   1024
#define BJ_SHARED_MEM_START_ADDR (0x01000000)

const char* epiphany_elf_nm = "bj-core-actor.elf";

int	write_file(char* the_pth, char* the_data, long the_sz, int write_once);

char before[bj_mem_32K];
char after[bj_mem_32K];

bj_sys_sz_st bj_glb_sys;

bj_sys_sz_st*
bj_get_glb_sys_sz(){
	return &bj_glb_sys;
}

void 
prt_aligns(void* ptr){
	int8_t alg = bj_get_aligment(ptr);
	printf("%d", alg); 
}

void
get_enter(bj_off_core_st* sh_dat_1, e_epiphany_t* dev, unsigned row, unsigned col){
	bj_in_core_st inco;
	memset(&inco, 0, sizeof(bj_in_core_st));
	e_read(dev, row, col, (uint32_t)(sh_dat_1->core_data), &inco, sizeof(inco));
	int err = prt_inko_shd_dat(&inco);
	if(err){
		bjh_abort_func(0, "get_enter failed");
	}
	
	void* 	trace[BJ_MAX_CALL_STACK_SZ];
	memset(trace, 0, sizeof(trace));
	e_read(dev, row, col, (uint32_t)(inco.dbg_stack_trace), trace, sizeof(trace));
	bjh_prt_core_call_stack(epiphany_elf_nm, BJ_MAX_CALL_STACK_SZ, trace);
	
	// CONTINUE
	printf("CORE (%d, %d) WAITING. Type enter\n", row, col);
	getchar();
}

int main(int argc, char *argv[])
{
	unsigned row, col, max_row, max_col, core_id;
	e_platform_t platform;
	e_epiphany_t dev;
	e_mem_t emem;
	char f_nm[200];
	char* all_f_nam[bj_out_num_cores];
	int num_wrk_cores;

	memset(&all_f_nam, 0, sizeof(all_f_nam));
	num_wrk_cores = 0;

	printf("sizeof(bj_off_sys_st)=%d\n", sizeof(bj_off_sys_st));
	
	e_set_loader_verbosity(H_D0);

	e_init(NULL);
	e_reset_system();
	e_get_platform_info(&platform);

	e_alloc(&emem, BJ_SHARED_MEM_START_ADDR, sizeof(bj_off_sys_st));
	
	e_open(&dev, 0, 0, platform.rows, platform.cols);
	
	bjh_init_glb_sys_sz_with_dev(bj_get_glb_sys_sz(), &dev);

	e_reset_group(&dev);

	e_load_group(epiphany_elf_nm, &dev, 0, 0, platform.rows, platform.cols, E_FALSE);
	
	bj_off_sys_st* pt_shd_data = (bj_off_sys_st*)emem.base;
	BJH_CK(sizeof(*pt_shd_data) == sizeof(bj_off_sys_st));
	printf("sizeof(*pt_shd_data)=%d\n", sizeof(*pt_shd_data));

	// init shared data.
	memset(pt_shd_data, 0, sizeof(*pt_shd_data));

	pt_shd_data->magic_id = BJ_MAGIC_ID;
	BJH_CK(pt_shd_data->magic_id == BJ_MAGIC_ID);

	bj_sys_sz_st* sys_sz = bj_get_glb_sys_sz();

	pt_shd_data->wrk_sys = *sys_sz;
	BJH_CK(ck_sys_data(&(pt_shd_data->wrk_sys)));

	max_row = 1;
	max_col = 2;
	max_row = dev.rows;
	max_col = dev.cols;

	for (row=0; row < max_row; row++){
		for (col=0; col < max_col; col++){
			core_id = (row + platform.row) * 64 + col + platform.col;
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
			e_start(&dev, row, col);
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
				core_id = (row + platform.row) * 64 + col + platform.col;
				bj_core_nn_t num_core = bj_id_to_nn(core_id);
				bj_off_core_st* sh_dat_1 = &(pt_shd_data->sys_cores[num_core]);
				bj_core_out_st* pt_buff = &(pt_shd_data->sys_out_buffs[num_core]);

				// Wait for core program execution to start
				if((sh_dat_1->core_data == 0x0) || (sh_dat_1->is_finished == 0x0)){
					has_work = true;
					BJH_CK(sh_dat_1->magic_id == BJ_MAGIC_ID);
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
							get_enter(sh_dat_1, &dev, row, col);
						}
						if(sh_dat_1->is_waiting == BJ_WAITING_BUFFER){
							print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core], num_core);
						}
						
						int SYNC = (1 << E_SYNC);
						sh_dat_1->is_waiting = BJ_NOT_WAITING;
						if (ee_write_reg(&dev, row, col, E_REG_ILATST, SYNC) == E_ERR) {
							printf("ERROR sending SYNC to (%d, %d) \n", row, col);
							break;
						}
					}
				} else {
					BJH_CK(sh_dat_1->is_finished == BJ_FINISHED_VAL);
	
					if(! core_finished[row][col]){
						core_finished[row][col] = true;

						print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core], num_core);
						BJH_CK(bj_rr_ck_zero(&(pt_buff->rd_arr)));

						printf("Finished\n");
						memset(&inco, 0, sizeof(bj_in_core_st));
						e_read(&dev, row, col, (uint32_t)sh_dat_1->core_data, 
									&inco, sizeof(inco));
						int err2 = prt_inko_shd_dat(&inco);
						if(err2){
							break;
						}

						memset(trace, 0, sizeof(trace));
						e_read(&dev, row, col, (uint32_t)inco.dbg_stack_trace, 
									trace, sizeof(trace));
						bjh_prt_core_call_stack(epiphany_elf_nm, BJ_MAX_CALL_STACK_SZ, trace);
					}

				}
			}
		}
	} // while
	
	printf("PLATFORM row=%2d col=%2d \n", platform.row, platform.col);
	printf("sys_sz->xx=%d\n", sys_sz->xx);
	printf("sys_sz->yy=%d\n", sys_sz->yy);
	printf("sys_sz->xx_sz=%d\n", sys_sz->xx_sz);
	printf("sys_sz->yy_sz_pw2=%d\n", sys_sz->yy_sz_pw2);
	
	// Reset the workgroup
	e_reset_group(&dev); // FAILS. Why?
	e_reset_system();
	
	// Close the workgroup
	e_close(&dev);
	
	// Release the allocated buffer and finalize the
	// e-platform connection.
	e_free(&emem);
	e_finalize();

	int nn;
	for (nn=0; nn < num_wrk_cores; nn++){
		if(all_f_nam[nn] != bj_null){
			free(all_f_nam[nn]);
		}
	}

	//prt_host_aligns();

	return 0;
}

