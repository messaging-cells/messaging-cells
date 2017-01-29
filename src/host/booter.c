
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

#include <e-hal.h>
#include <e-loader.h>
#include <epiphany-hal-api-local.h>

#include "shared.h"
#include "booter.h"

#define f_nm_sz   1024
#define BJ_SHARED_MEM_START_ADDR (0x01000000)

int	write_file(char* the_pth, char* the_data, long the_sz, int write_once);

char before[bj_mem_32K];
char after[bj_mem_32K];

bj_sys_st bj_glb_sys;

void 
bjh_abort_func(long val, const char* msg){
	fprintf(stderr, "\nABORTING! %s\n", msg); 
	exit(val);
}

bool 
bjh_call_assert(bool vv_ck, const char* file, int line, const char* ck_str, const char* msg){
	
	if(! vv_ck){
		fprintf(stderr, "ASSERT '%s' FAILED\n", ck_str);
		//bj_out << get_stack_trace(file, line) << bj_eol;
		if(msg != NULL){
			fprintf(stderr, "MSG=%s\n", msg);
		}
	}
	assert(vv_ck);
	return vv_ck;
}

bool ck_sys_data(bj_sys_st* sys1){
	BJH_CK(sys1->xx == bj_glb_sys.xx);
	BJH_CK(sys1->yy == bj_glb_sys.yy);
	BJH_CK(sys1->xx_sz == bj_glb_sys.xx_sz);
	BJH_CK(sys1->yy_sz == bj_glb_sys.yy_sz);
	return true;
}

int prt_inko_shd_dat(bj_in_core_st* sh_dat){
	if(sh_dat->magic_id != BJ_MAGIC_ID){
		printf("ERROR with inco.magic_id (0x%08x)\n", sh_dat->magic_id);
		return 1;
	}
	if(sh_dat->magic_end != BJ_MAGIC_END){
		printf("ERROR with inco.magic_end (0x%08x)\n", sh_dat->magic_end);
		return 1;
	}
	printf("InCORE 0x%03x \n", sh_dat->the_coreid);
	
	printf("dbg_error_code=0x%08x \n", sh_dat->dbg_error_code);
	printf("dbg_progress_flag=0x%08x \n", sh_dat->dbg_progress_flag);
	printf("dbg_info_wait=0x%08x \n", sh_dat->dbg_info_wait);

	printf("val_reg1=0x%08x \n", sh_dat->val_reg1);
	printf("val_reg2=0x%08x \n", sh_dat->val_reg2);
	
	
	printf("got_irq0=0x%02x \n", sh_dat->got_irq0);
	
	printf("\n");
	
	return 0;
}

int main(int argc, char *argv[])
{
	const char* epiphany_elf_nm = "e_prog_18.elf";
	unsigned row, col, max_row, max_col, coreid;
	e_platform_t platform;
	e_epiphany_t dev;
	e_mem_t emem;

	printf("sizeof(bj_off_sys_st)=%d\n", sizeof(bj_off_sys_st));
	
	e_set_loader_verbosity(H_D0);

	e_init(NULL);
	e_reset_system();
	e_get_platform_info(&platform);

	e_alloc(&emem, BJ_SHARED_MEM_START_ADDR, sizeof(bj_off_sys_st));
	
	e_open(&dev, 0, 0, platform.rows, platform.cols);
	
	bjh_init_glb_sys_with_dev(&dev);

	e_reset_group(&dev);

	e_load_group(epiphany_elf_nm, &dev, 0, 0, platform.rows, platform.cols, E_FALSE);
	
	bj_off_sys_st* pt_shd_data = (bj_off_sys_st*)emem.base;
	BJH_CK(sizeof(*pt_shd_data) == sizeof(bj_off_sys_st));
	printf("sizeof(*pt_shd_data)=%d\n", sizeof(*pt_shd_data));
	
	row = 0;
	col = 0;
	max_row = 1;
	max_col = 1;
	max_row = platform.rows;
	max_col = platform.cols;
	for (row=0; row < max_row; row++){
		for (col=0; col < max_col; col++){
			coreid = (row + platform.row) * 64 + col + platform.col;
			bj_consec_t num_core = bj_id_to_nn(coreid);
			printf("DOING CORE 0x%03x (%2d,%2d) NUM=%d\n", coreid, row, col, num_core);
			
			// init shared data.
			memset(pt_shd_data, 0, sizeof(*pt_shd_data));
			pt_shd_data->magic_id = BJ_MAGIC_ID;
			pt_shd_data->wrk_sys = bj_glb_sys;
			pt_shd_data->sys_cores[num_core].magic_id = BJ_MAGIC_ID;
			
			BJH_CK(pt_shd_data->magic_id == BJ_MAGIC_ID);
			BJH_CK(pt_shd_data->sys_cores[num_core].magic_id == BJ_MAGIC_ID);
			BJH_CK(ck_sys_data(&(pt_shd_data->wrk_sys)));
	
			// Start one core
			e_start(&dev, row, col);
			
			// Wait for core program execution to finish.
			bj_off_core_st* sh_dat_1 = &(pt_shd_data->sys_cores[num_core]);
			
			while((sh_dat_1->core_data == 0x0) || (sh_dat_1->is_finished == 0x0)){
				BJH_CK(sh_dat_1->magic_id == BJ_MAGIC_ID);
				if(sh_dat_1->magic_id == BJ_MAGIC_ID){ printf("."); }
				sched_yield();				//yield
			}
			printf("\n");
			
			BJH_CK(sh_dat_1->magic_id == BJ_MAGIC_ID);
			BJH_CK(	(sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL) ||
					(sh_dat_1->is_finished == BJ_FINISHED_VAL)
			);
			BJH_CK(sh_dat_1->the_coreid == coreid);
			if(sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL){ 
				printf("Waiting for finish.\n");
			}

			bj_in_core_st inco;
			void* 	trace[BJ_MAX_CALL_STACK_SZ];
			
			// wait for finish
			while(sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL){
				if(sh_dat_1->is_waiting){
					memset(&inco, 0, sizeof(bj_in_core_st));
					e_read(&dev, row, col, (uint32_t)(sh_dat_1->core_data), &inco, sizeof(inco));
					int err = prt_inko_shd_dat(&inco);
					if(err){
						break;
					}
					
					memset(trace, 0, sizeof(trace));
					e_read(&dev, row, col, (uint32_t)(inco.dbg_stack_trace), 
						   trace, sizeof(trace));
					bjh_prt_call_stack(epiphany_elf_nm, BJ_MAX_CALL_STACK_SZ, trace);
					
					// CONTINUE
					printf("CORE (%d, %d) WAITING. Type enter\n", row, col);
					getchar();
					
					int SYNC = (1 << E_SYNC);
					sh_dat_1->is_waiting = 0;
					if (ee_write_reg(&dev, row, col, E_REG_ILATST, SYNC) == E_ERR) {
						printf("ERROR sending SYNC to (%d, %d) \n", row, col);
						break;
					}
				}
				sched_yield();				//yield
			}
			BJH_CK(sh_dat_1->is_finished == BJ_FINISHED_VAL);
			printf("Finished\n");
			memset(&inco, 0, sizeof(bj_in_core_st));
			e_read(&dev, row, col, (uint32_t)sh_dat_1->core_data, &inco, sizeof(inco));
			int err2 = prt_inko_shd_dat(&inco);
			if(err2){
				break;
			}

			memset(trace, 0, sizeof(trace));
			e_read(&dev, row, col, (uint32_t)inco.dbg_stack_trace, trace, sizeof(trace));
			bjh_prt_call_stack(epiphany_elf_nm, BJ_MAX_CALL_STACK_SZ, trace);
		}
	}
	
	printf("PLATFORM row=%2d col=%2d \n", platform.row, platform.col);
	printf("bj_glb_sys.xx=%d\n", bj_glb_sys.xx);
	printf("bj_glb_sys.yy=%d\n", bj_glb_sys.yy);
	printf("bj_glb_sys.xx_sz=%d\n", bj_glb_sys.xx_sz);
	printf("bj_glb_sys.yy_sz=%d\n", bj_glb_sys.yy_sz);
	
	// Reset the workgroup
	e_reset_group(&dev); // FAILS. Why?
	e_reset_system();
	
	// Close the workgroup
	e_close(&dev);
	
	// Release the allocated buffer and finalize the
	// e-platform connection.
	e_free(&emem);
	e_finalize();

	return 0;
}

int
write_file(char* the_pth, char* the_data, long the_sz, int write_once){
	int fd = 0;
	
	if(write_once){
		// old perm 0444
		if((fd = open(the_pth, O_RDWR|O_CREAT|O_EXCL, 0777)) == -1){
			return 0;
		}
	} else {
		if((fd = creat(the_pth, 0777)) == -1){
			return 0;
		}
	}

	write(fd, the_data, the_sz);
	close(fd);

	return 1;
}

