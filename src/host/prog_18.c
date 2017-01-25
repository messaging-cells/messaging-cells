
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

#include "shared_data.h"

#define f_nm_sz   1024
#define buff_offset (0x01000000)

int	write_file(char* the_pth, char* the_data, long the_sz, int write_once);

char before[bj_mem_32K];
char after[bj_mem_32K];

bj_sys_st bj_glb_sys;

void ck_sys_data(e_mem_t* emem){
	bj_off_sys_st off_dat_1;
	memset(&off_dat_1, 0, sizeof(off_dat_1));
	e_read(emem, -1, 0, 0x0, &off_dat_1, sizeof(off_dat_1));
	
	bj_sys_st* sys1 = &(off_dat_1.wrk_sys);
	printf("sys1.xx=%d\n", sys1->xx);
	printf("sys1.yy=%d\n", sys1->yy);
	printf("sys1.xx_sz=%d\n", sys1->xx_sz);
	printf("sys1.yy_sz=%d\n", sys1->yy_sz);
	if(sys1->xx != bj_glb_sys.xx){
		printf("FAILED bj_glb_sys.xx %d != %d\n", sys1->xx, bj_glb_sys.xx);
	}
}

void prt_stack_trace(void** trace){
	int aa = 0;
	printf("STACK_TRACE=[ \n");
	for(aa = 0; aa < BJ_MAX_CALL_STACK_SZ; aa++){
		printf("%p \n", trace[aa]);
	}
	printf("]\n");
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

	/*
	printf("pc_val=%p \n", sh_dat->pc_val);
	printf("rts_addr=%p \n", sh_dat->rts_addr);
	printf("call_addr=%p \n", sh_dat->call_addr);
	printf("disp=%u \n", sh_dat->disp);
	*/
	printf("val_reg1=0x%08x \n", sh_dat->val_reg1);
	printf("val_reg2=0x%08x \n", sh_dat->val_reg2);
	
	
	printf("got_irq0=0x%02x \n", sh_dat->got_irq0);
	
	printf("cpp_fun1=0x%02x \n", sh_dat->cpp_fun1);
	printf("cpp_dcla1=0x%02x \n", sh_dat->cpp_dcla1);
	printf("\n");
	
	return 0;
}

/*
uint64_t 
get_num_core(unsigned coreid){
	return bj_e3_id_to_nn(coreid);
}
*/

int main(int argc, char *argv[])
{
	const char* epiphany_elf_nm = "e_prog_18.elf";
	unsigned row, col, max_row, max_col, coreid;
	e_platform_t platform;
	e_epiphany_t dev;
	e_mem_t emem;
	char f_nm[f_nm_sz];
	bj_off_sys_st shd_mem;

	printf("sizeof(bj_off_sys_st)=%d\n", sizeof(bj_off_sys_st));
	printf("sizeof(shd_mem)=%d\n", sizeof(shd_mem));
	printf("sizeof(shd_mem.sys_cores)=%d\n", sizeof(shd_mem.sys_cores));
	printf("sizeof(bj_off_core_st)=%d\n", sizeof(bj_off_core_st));
	printf("sizeof(bj_sys_st)=%d\n", sizeof(bj_sys_st));
	
	e_set_loader_verbosity(H_D0);

	e_init(NULL);
	e_reset_system();
	e_get_platform_info(&platform);

	e_alloc(&emem, buff_offset, sizeof(shd_mem));
	
	e_open(&dev, 0, 0, platform.rows, platform.cols);
	
	bjh_init_glb_sys_with_dev(&dev);

	e_reset_group(&dev);

	e_load_group(epiphany_elf_nm, &dev, 0, 0, platform.rows, platform.cols, E_FALSE);
	
	uint32_t ck_curr_core = 0xaabbccdd;

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
			void* pt_core = &((shd_mem.sys_cores)[num_core]);
			printf("DOING CORE NUM=%d pt_core=%p\n", num_core, pt_core);
			
			// clear shared buffer.			
			memset(&shd_mem, 0, sizeof(shd_mem));
			shd_mem.magic_id = BJ_MAGIC_ID;
			shd_mem.wrk_sys = bj_glb_sys;
			shd_mem.sys_cores[num_core].magic_id = BJ_MAGIC_ID;
			e_write(&emem, -1, 0, 0x0, &shd_mem, sizeof(shd_mem));

			ck_sys_data(&emem);
			
			memset(before, 0, bj_mem_32K);
			memset(after, 0, bj_mem_32K);
			
			// read local mem before.
			e_read(&dev, row, col, 0x0, before, bj_mem_32K);
			
			// Print working core 
			//coreid = bj_rowcol_to_coreid(row, col);
			//printf("plat (rows=%2d, cols=%2d): \n", platform.row, platform.col);
			printf("\n\n");
			printf("eCore 0x%03x (%2d,%2d): \n", coreid, row, col);

			// Start one core
			e_start(&dev, row, col);
			
			// Wait for core program execution to finish.
			uint32_t offset	 = 0x0;
			void* base = &shd_mem;
			offset = (uint32_t)(pt_core - base);
			
			printf("offset=%d\n", offset);
			
			bj_off_core_st sh_dat_1;
			memset(&sh_dat_1, 0, sizeof(sh_dat_1));
			
			// wait for start
			while((sh_dat_1.core_data == 0x0) || (sh_dat_1.is_finished == 0x0)){
				// read shared buffer.
				e_read(&emem, -1, 0, offset, &sh_dat_1, sizeof(sh_dat_1));
				if(sh_dat_1.magic_id != BJ_MAGIC_ID){
					printf("ERROR with sh_dat_1.magic_id 0x%08x != 0x%08x\n", 
						   sh_dat_1.magic_id, BJ_MAGIC_ID);
					
					bj_off_sys_st off_dat_2;
					memset(&off_dat_2, 0, sizeof(off_dat_2));
					e_read(&emem, -1, 0, 0x0, &off_dat_2, sizeof(off_dat_2));
					printf("dbg_error_code=0x%08x\n", off_dat_2.dbg_error_code);
					break;
				}
				if(sh_dat_1.magic_id == BJ_MAGIC_ID){
					printf("magic_id OK = 0x%08x\n", sh_dat_1.magic_id);
				}
				sched_yield();				//yield
			}
			if(sh_dat_1.magic_id != BJ_MAGIC_ID){
				break;
			}
			
			if(	(sh_dat_1.is_finished != BJ_NOT_FINISHED_VAL) && 
				(sh_dat_1.is_finished != BJ_FINISHED_VAL))
			{
				printf("ERROR with sh_dat_1.is_finished=0x%04x \n", sh_dat_1.is_finished);
				break;
			}
			
			printf("CORE 0x%03x \n", sh_dat_1.the_coreid);
			printf("is_finished=0x%08x \n", sh_dat_1.is_finished);
			printf("core_dat_pt=%p \n", sh_dat_1.core_data);

			bj_in_core_st inco;
			void* 	trace[BJ_MAX_CALL_STACK_SZ];
			
			// wait for finish
			uint8_t  finished = BJ_NOT_FINISHED_VAL;
			while(sh_dat_1.is_finished == BJ_NOT_FINISHED_VAL){
				e_read(&emem, -1, 0, offset, &sh_dat_1, sizeof(sh_dat_1));
				if(sh_dat_1.is_waiting){
					memset(&inco, 0, sizeof(bj_in_core_st));
					e_read(&dev, row, col, (uint32_t)(sh_dat_1.core_data), 
						   &inco, sizeof(inco));
					int err = prt_inko_shd_dat(&inco);
					if(err){
						break;
					}
					
					memset(trace, 0, sizeof(trace));
					e_read(&dev, row, col, (uint32_t)(inco.dbg_stack_trace), 
						   trace, sizeof(trace));
					//prt_stack_trace(trace);
					bjh_prt_call_stack(epiphany_elf_nm, BJ_MAX_CALL_STACK_SZ, trace);
					
					// CONTINUE
					printf("CORE (%d, %d) WAITING. Type enter\n", row, col);
					int chr1 = getchar();
					
					int SYNC = (1 << E_SYNC);
					sh_dat_1.is_waiting = 0;
					if (ee_write_reg(&dev, row, col, E_REG_ILATST, SYNC) == E_ERR) {
						printf("ERROR sending SYNC to (%d, %d) \n", row, col);
						break;
					}
				}
				sched_yield();				//yield
			}
			if(sh_dat_1.is_finished != BJ_FINISHED_VAL){
				printf("ERROR with finished flag \n");
				break;
			}
			printf("Finished\n");
			memset(&inco, 0, sizeof(bj_in_core_st));
			e_read(&dev, row, col, (uint32_t)sh_dat_1.core_data, &inco, sizeof(inco));
			int err2 = prt_inko_shd_dat(&inco);
			if(err2){
				break;
			}

			memset(trace, 0, sizeof(trace));
			e_read(&dev, row, col, (uint32_t)inco.dbg_stack_trace, trace, sizeof(trace));
			//prt_stack_trace(trace);
			bjh_prt_call_stack(epiphany_elf_nm, BJ_MAX_CALL_STACK_SZ, trace);
			
			// read local mem after.
			e_read(&dev, row, col, 0x0, after, bj_mem_32K);

			//if(row == 0){
			//if(1){
			//if((row == 0) && (col == 0)){
			/*
			if(0){
				sprintf(f_nm, "mem_before_row%d_col%d.dat", row, col);
				write_file(f_nm, before, bj_mem_32K, 1);
				
				sprintf(f_nm, "mem_after_row%d_col%d.dat", row, col);
				write_file(f_nm, after, bj_mem_32K, 1);
			}
			*/
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

