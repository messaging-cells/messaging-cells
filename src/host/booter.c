
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <e-hal.h>
#include <e-loader.h>
#include <epiphany-hal-api-local.h>

#include "shared.h"
#include "booter.h"


#define f_nm_sz   1024
#define BJ_SHARED_MEM_START_ADDR (0x01000000)

const char* epiphany_elf_nm = "bj-core-actor.elf";

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

bool
bjh_file_append(char* the_pth, char* the_data, long the_sz){
	int fd = 0;
	
	if((fd = open(the_pth, O_RDWR|O_CREAT|O_APPEND, 0777)) == -1){
		return false;
	}
	write(fd, the_data, the_sz);
	close(fd);

	return true;
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

	printf("got_irq0=0x%02x \n", sh_dat->got_irq0);
	
	printf("\n");
	
	return 0;
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
	bjh_prt_call_stack(epiphany_elf_nm, BJ_MAX_CALL_STACK_SZ, trace);
	
	// CONTINUE
	printf("CORE (%d, %d) WAITING. Type enter\n", row, col);
	getchar();
}

void
bj_rr_print(bj_rrarray_st* arr){
	if(arr == bj_null){
		return;
	}
	printf("#####################################\n");
	printf("data=\t%p\n", arr->data);
	printf("end_data=\t%p\n", arr->end_data);
	printf("rd_obj=\t%p\n", arr->rd_obj);
	printf("wr_obj=\t%p\n", arr->wr_obj);
	printf("num_wr_errs=\t%d\n", arr->num_wr_errs);
	printf("wr_err=\t%d\n", arr->wr_err);
	printf("rd_err=\t%d\n", arr->rd_err);
	uint8_t* dat = arr->data;
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	while(dat != arr->end_data){
		char cc = (char)(*dat);
		if(isprint(cc)){
			printf("%c", cc);
		} 
		/*else {
			printf(".");
		}*/
		dat++;
	}
	printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
}

void
print_out_buffer(bj_rrarray_st* arr, char* f_nm){
	int fd = 0;
	if((fd = open(f_nm, O_RDWR|O_CREAT|O_APPEND, 0777)) == -1){
		fprintf(stderr, "ERROR. Can NOT open file %s\n", f_nm);
		return;
	}

	char obj[BJ_MAX_OBJ_SZ];
	while(true){
		uint16_t obj_sz = bj_rr_read_obj(arr, BJ_MAX_OBJ_SZ, (uint8_t*)obj);
		if(obj_sz == 0){
			//bj_rr_print(arr);
			//printf("TYPE ENTER to continue.");
			//getchar();
			if(arr->rd_err != -4){
				break;
			}
		} else {
			//printf("OBJ:%s\n", obj);
			obj[obj_sz - 1] = '\n';
			write(fd, obj, obj_sz);
		}
	}
	close(fd);
}

int main(int argc, char *argv[])
{
	unsigned row, col, max_row, max_col, coreid;
	e_platform_t platform;
	e_epiphany_t dev;
	e_mem_t emem;
	char f_nm[200];
	char* all_f_nam[bj_sys_max_cores];
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
	
	bjh_init_glb_sys_with_dev(&dev);

	e_reset_group(&dev);

	e_load_group(epiphany_elf_nm, &dev, 0, 0, platform.rows, platform.cols, E_FALSE);
	
	bj_off_sys_st* pt_shd_data = (bj_off_sys_st*)emem.base;
	BJH_CK(sizeof(*pt_shd_data) == sizeof(bj_off_sys_st));
	printf("sizeof(*pt_shd_data)=%d\n", sizeof(*pt_shd_data));

	// init shared data.
	memset(pt_shd_data, 0, sizeof(*pt_shd_data));

	pt_shd_data->magic_id = BJ_MAGIC_ID;
	BJH_CK(pt_shd_data->magic_id == BJ_MAGIC_ID);

	pt_shd_data->wrk_sys = bj_glb_sys;	
	BJH_CK(ck_sys_data(&(pt_shd_data->wrk_sys)));

	max_row = 1;
	max_col = 1;
	max_row = dev.rows;
	max_col = dev.cols;

	for (row=0; row < max_row; row++){
		for (col=0; col < max_col; col++){
			coreid = (row + platform.row) * 64 + col + platform.col;
			bj_consec_t num_core = bj_id_to_nn(coreid);
			printf("STARTING CORE 0x%03x (%2d,%2d) NUM=%d\n", coreid, row, col, num_core);
			memset(&f_nm, 0, sizeof(f_nm));
			sprintf(f_nm, "log_core_%02d.txt", num_core);

			BJH_CK(num_core < bj_sys_max_cores);
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

	bool has_work = true;	
	while(has_work){
		sched_yield();				//yield
		has_work = false;
		for (row=0; row < max_row; row++){
			for (col=0; col < max_col; col++){
				coreid = (row + platform.row) * 64 + col + platform.col;
				bj_consec_t num_core = bj_id_to_nn(coreid);
				bj_off_core_st* sh_dat_1 = &(pt_shd_data->sys_cores[num_core]);
				bj_core_out_st* pt_buff = &(pt_shd_data->sys_out_buffs[num_core]);
				
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
				BJH_CK(sh_dat_1->the_coreid == coreid);
				if(sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL){ 
					printf("Waiting for finish 0x%03x (%2d,%2d) NUM=%d\n", 
								coreid, row, col, num_core);
				}

				bj_in_core_st inco;
				void* 	trace[BJ_MAX_CALL_STACK_SZ];
				
				// wait for finish
				if(sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL){
					has_work = true;
					print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core]);
					if(sh_dat_1->is_waiting){
						if(sh_dat_1->is_waiting == BJ_WAITING_ENTER){
							get_enter(sh_dat_1, &dev, row, col);
						}
						if(sh_dat_1->is_waiting == BJ_WAITING_BUFFER){
							print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core]);
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

					print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core]);
					bj_rr_print(&(pt_buff->rd_arr));

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
					bjh_prt_call_stack(epiphany_elf_nm, BJ_MAX_CALL_STACK_SZ, trace);
				}
			}
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

	int nn;
	for (nn=0; nn < num_wrk_cores; nn++){
		if(all_f_nam[nn] != bj_null){
			free(all_f_nam[nn]);
		}
	}

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

