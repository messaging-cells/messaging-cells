

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

#include "shared.h"
#include "booter.h"

//include "test_align.h"

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

bool ck_sys_data(bj_sys_sz_st* sys1){
	bj_sys_sz_st* sys0 = bj_get_glb_sys_sz();
	BJH_CK(sys1->xx == sys0->xx);
	BJH_CK(sys1->yy == sys0->yy);
	BJH_CK(sys1->xx_sz == sys0->xx_sz);
	BJH_CK(sys1->yy_sz == sys0->yy_sz);
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
	printf("InCORE 0x%03x \n", sh_dat->the_core_id);
	
	EMU_CODE(printf("dbg_error_code=0x%08lx \n", sh_dat->dbg_error_code));
	ZNQ_CODE(printf("dbg_error_code=0x%08x \n", sh_dat->dbg_error_code));

	printf("dbg_progress_flag=0x%08x \n", sh_dat->dbg_progress_flag);

	printf("binder_sz=%d \n", sh_dat->binder_sz);
	printf("receptor_sz=%d \n", sh_dat->receptor_sz);
	printf("actor_sz=%d \n", sh_dat->actor_sz);
	printf("missive_sz=%d \n", sh_dat->missive_sz);
	printf("missive_grp_sz=%d \n", sh_dat->missive_grp_sz);
	printf("kernel_sz=%d \n", sh_dat->kernel_sz);
	printf("bjk_glb_sys_st_sz=%d \n", sh_dat->bjk_glb_sys_st_sz);

	printf("\n");
	
	return 0;
}

bool
bj_rr_ck_zero(bj_rrarray_st* arr){
	if(arr == bj_null){
		return true;
	}
	uint8_t* dat = arr->data;
	while(dat != arr->end_data){
		uint8_t cc = (uint8_t)(*dat);
		BJH_CK(cc == 0);
		BJH_CK(! isprint(cc));
		dat++;
	}
	return true;
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

int
bj_type_sz(bj_type_t tt){
	int sz = 0;
	switch(tt){
		case BJ_CHR:
		case BJ_I8:
		case BJ_UI8:
		case BJ_X8:
			sz = 1;
			break;
		case BJ_I16:
		case BJ_UI16:
		case BJ_X16:
			sz = 2;
			break;
		case BJ_I32:
		case BJ_UI32:
		case BJ_X32:
			sz = 4;
			break;
	}
	return sz;
}

void
print_out_buffer(bj_rrarray_st* arr, char* f_nm, bj_core_nn_t num_core){
	int log_fd = 0;
	if((log_fd = open(f_nm, O_RDWR|O_CREAT|O_APPEND, 0777)) == -1){
		fprintf(stderr, "ERROR. Can NOT open file %s\n", f_nm);
		return;
	}

	uint8_t obj[BJ_OUT_BUFF_MAX_OBJ_SZ];
	while(true){
		uint16_t obj_sz = bj_rr_read_obj(arr, BJ_OUT_BUFF_MAX_OBJ_SZ, obj);
		if(obj_sz == 0){
			if(arr->rd_err != -4){
				break;
			}
		} else {
			if(obj_sz < 2){
				fprintf(stderr, "ERROR. Got unhandled obj in buffer for %s\n", f_nm);
				continue;
			}
			int fd = STDOUT_FILENO;
			if(obj[0] == BJ_OUT_LOG){
				fd = log_fd;
			} 
			bj_type_t ot = obj[1];
			if(ot == BJ_CHR){
				write(fd, obj + 2, obj_sz - 2);
				continue;
			}
			int osz = bj_type_sz(ot);
			int tot = (obj_sz - 2) / osz;
			int aa;
			uint8_t* pt_num = obj + 2;
			for(aa = 0; aa < tot; aa++, pt_num += osz){
				int istrsz = 50;
				char istr[istrsz];
				switch(ot){
					case BJ_CHR:
						break;
					case BJ_I8:
						snprintf(istr, istrsz, "%" PRId8 , *((int8_t*)pt_num));
						break;
					case BJ_I16:
						snprintf(istr, istrsz, "%" PRId16 , *((int16_t*)pt_num));
						break;
					case BJ_I32:
						snprintf(istr, istrsz, "%" PRId32 , *((int32_t*)pt_num));
						break;
					case BJ_UI8:
						snprintf(istr, istrsz, "%" PRIu8 , *((uint8_t*)pt_num));
						break;
					case BJ_UI16:
						snprintf(istr, istrsz, "%" PRIu16 , *((uint16_t*)pt_num));
						break;
					case BJ_UI32:
						snprintf(istr, istrsz, "%" PRIu32 , *((uint32_t*)pt_num));
						break;
					case BJ_X8:
						snprintf(istr, istrsz, "0x%02x", *((uint8_t*)pt_num));
						break;
					case BJ_X16:
						snprintf(istr, istrsz, "0x%04x", *((uint16_t*)pt_num));
						break;
					case BJ_X32:
						snprintf(istr, istrsz, "0x%08x", *((uint32_t*)pt_num));
						break;
				}
				int sz2 = strlen(istr);
				write(fd, istr, sz2);
			}
		}
	}
	close(log_fd);
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

