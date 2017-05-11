
//define _GNU_SOURCE

#include <inttypes.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thread_emu.hh"
#include "booter.h"
#include "string_hst.hh"

#include "cores_main.h"
#include "dlmalloc.h"

#include "dyn_mem.h"
#include "actor.hh"

// =====================================================================================


#define DLMALLOC_HEAP_SZ (10 * MBY_SZ)
uint8_t dlmalloc_heap[DLMALLOC_HEAP_SZ];

mspace bjm_glb_mspace;

bj_sys_sz_st bjh_glb_host_sys;

void 
bjh_prt_core_call_stack_emu(thread_info_t& thd_inf){
	char** trace = thd_inf.bjk_glb_sys_data.bjk_dbg_call_nams_stack_trace;
	bjh_out << "---------------------------------------------------\n";
	bjh_out << "STACK_TRACE for core num " << std::dec << thd_inf.thread_num;
	bjh_out << " with core_id = 0x" << std::hex << thd_inf.bjk_core_id << "\n";
	for(int aa = 0; aa < BJ_MAX_CALL_STACK_SZ; aa++){
		if(trace[aa] == bj_null){ break; }
		bjh_out << trace[aa] << "\n";
	}
	bjh_out << "---------------------------------------------------\n";
}

bool
ck_all_core_ids(){
	if (ALL_THREADS_INFO == NULL){
		bjh_abort_func(0, "ck_all_core_ids. NULL ALL_THREADS_INFO \n");
	}
	for(int aa = 0; aa < TOT_THREADS; aa++){
		bj_core_id_t koid = bj_nn_to_id(aa);
		if(ALL_THREADS_INFO[aa].bjk_core_id != koid){
			bjh_abort_func(0, "ck_all_core_ids. BAD CORE ID \n");
		}
	}
	return true;
}

void
bj_host_init(){

	bjm_glb_mspace = create_mspace_with_base(dlmalloc_heap, DLMALLOC_HEAP_SZ, 0);

	bj_init_glb_sys_sz(&bjh_glb_host_sys);

	memset(&bjh_external_ram_load_data, 0, sizeof(bj_link_syms_data_st));

	ALL_THREADS_INFO = bj_null;

	HOST_THREAD_ID = pthread_self();

	TOT_THREADS = bj_tot_nn_sys;
	ALL_THREADS_INFO = (thread_info_t *)calloc(TOT_THREADS, sizeof(thread_info_t));
	if (ALL_THREADS_INFO == NULL){
		bjh_abort_func(0, "host_main. NULL ALL_THREADS_INFO \n");
	}

	bjm_pt_THE_KERNEL = bj_malloc32(kernel, 1);

	printf("TOT_THREADS = %d\n", TOT_THREADS);

	bj_off_sys_st* pt_shd_data = BJK_PT_EXTERNAL_DATA;
	BJH_CK(sizeof(*pt_shd_data) == sizeof(bj_off_sys_st));
	printf("sizeof(*pt_shd_data)=%ld\n", sizeof(*pt_shd_data));

	// init shared data.
	memset(pt_shd_data, 0, sizeof(*pt_shd_data));

	pt_shd_data->magic_id = BJ_MAGIC_ID;
	BJH_CK(pt_shd_data->magic_id == BJ_MAGIC_ID);

	bj_sys_sz_st* sys_sz = BJK_GLB_SYS_SZ;

	pt_shd_data->wrk_sys = *sys_sz;
	BJH_CK(bjh_ck_sys_data(&(pt_shd_data->wrk_sys)));
}

void
bj_host_run()
{
	bj_off_sys_st* pt_shd_data = BJK_PT_EXTERNAL_DATA;
	bj_sys_sz_st* sys_sz = BJK_GLB_SYS_SZ;

	bj_core_id_t core_id;
	bj_core_co_t row, col, max_row, max_col;
	char f_nm[200];

	char* all_f_nam[bj_out_num_cores];
	memset(&all_f_nam, 0, sizeof(all_f_nam));

	max_row = 1;
	max_col = 2;
	max_row = sys_sz->xx_sz;
	max_col = (1 << (sys_sz->yy_sz_pw2));

	for (row=0; row < max_row; row++){
		for (col=0; col < max_col; col++){
			core_id = bj_ro_co_to_id(row, col);
			bj_core_nn_t num_core = bj_id_to_nn(core_id);

			thread_info_t& thd_inf = ALL_THREADS_INFO[num_core];
			thd_inf.thread_num = num_core;
			thd_inf.argv_string = bj_null;
			bj_uint16_to_hex_bytes(thd_inf.thread_num, (uint8_t*)(thd_inf.thread_name));
			thd_inf.bjk_core_id = core_id;
			thd_inf.core_func = &bj_cores_main;

			printf("STARTING CORE 0x%03x (%2d,%2d) NUM=%d\n", core_id, row, col, num_core);

			if(num_core < bj_out_num_cores){
				memset(&f_nm, 0, sizeof(f_nm));
				sprintf(f_nm, "log_core_%02d.txt", num_core);
				all_f_nam[num_core] = strdup((const char*)f_nm);

				// init shared data.
				pt_shd_data->sys_cores[num_core].magic_id = BJ_MAGIC_ID;
				BJH_CK(pt_shd_data->sys_cores[num_core].magic_id == BJ_MAGIC_ID);

				bj_core_out_st* pt_buff = &(pt_shd_data->sys_out_buffs[num_core]);

				pt_buff->magic_id = BJ_MAGIC_ID;
				BJH_CK(pt_buff->magic_id == BJ_MAGIC_ID);

				bj_rr_init(&(pt_buff->rd_arr), BJ_OUT_BUFF_SZ, pt_buff->buff, 1);
			}
			
			// Start one core emulation thread

			int ss = pthread_create(&thd_inf.thread_id, NULL,
								&thread_start, &thd_inf);
			if (ss != 0){
				bjh_abort_func(ss, "host_main. Cannot pthread_create");
			}
		}
	}

	BJH_CK(ck_all_core_ids());

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

				thread_info_t& thd_inf = ALL_THREADS_INFO[num_core];

				// Wait for core program execution to finish.
				if((sh_dat_1->core_data == 0x0) || (sh_dat_1->is_finished == 0x0)){
					has_work = true;
					BJH_CK(sh_dat_1->magic_id == BJ_MAGIC_ID);
					continue;
				}
				
				BJH_CK(sh_dat_1->magic_id == BJ_MAGIC_ID);
				BJH_CK(	(sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL) ||
						(sh_dat_1->is_finished == BJ_FINISHED_VAL)
				);
				BJH_CK(sh_dat_1->ck_core_id == core_id);
				if(! core_started[row][col] && (sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL)){ 
					core_started[row][col] = true;
					printf("Waiting for finish 0x%03x (%2d,%2d) NUM=%d\n", 
								core_id, row, col, num_core);
				}

				bj_in_core_st inco;
				
				// wait for finish
				if(sh_dat_1->is_finished == BJ_NOT_FINISHED_VAL){
					has_work = true;
					bjh_print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core], num_core);
					if(sh_dat_1->is_waiting){
						if(sh_dat_1->is_waiting == BJ_WAITING_ENTER){
							bjh_get_enter(row, col);
						}
						if(sh_dat_1->is_waiting == BJ_WAITING_BUFFER){
							bjh_print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core], num_core);
						}
						
						sh_dat_1->is_waiting = BJ_NOT_WAITING;

						thd_inf.bjk_glb_sys_data.bjk_sync_signal = 1;	// SEND signal
					}
				} else {
					BJH_CK(sh_dat_1->is_finished == BJ_FINISHED_VAL);
	
					if(! core_finished[row][col]){

						core_finished[row][col] = true;

						bjh_print_out_buffer(&(pt_buff->rd_arr), all_f_nam[num_core], num_core);
						BJH_CK(bjh_rr_ck_zero(&(pt_buff->rd_arr)));

						printf("Finished\n");
						memset(&inco, 0, sizeof(bj_in_core_st));
						memcpy(&inco, &thd_inf.bjk_glb_sys_data.in_core_shd, sizeof(bj_in_core_st));
						int err2 = bjh_prt_in_core_shd_dat(&inco);
						if(err2){
							break;
						}

						bjh_prt_core_call_stack_emu(thd_inf);
					}

				}
			}
		}
	} // while

	printf("sys_sz->xx=%d\n", sys_sz->xx);
	printf("sys_sz->yy=%d\n", sys_sz->yy);
	printf("sys_sz->xx_sz=%d\n", sys_sz->xx_sz);
	printf("sys_sz->yy_sz_pw2=%d\n", sys_sz->yy_sz_pw2);
	
	int nn;
	for (nn=0; nn < bj_out_num_cores; nn++){
		if(all_f_nam[nn] != bj_null){
			free(all_f_nam[nn]);
		}
	}

}

void
bj_host_finish()
{
	int tnum;
	for (tnum = 0; tnum < TOT_THREADS; tnum++) {
		void *res;
		int ss = pthread_join(ALL_THREADS_INFO[tnum].thread_id, &res);
		if(ss != 0){
			bjh_abort_func(ss, "bj_host_finish. Cannot join thread.");
		}
	}

	free(ALL_THREADS_INFO);
	destroy_mspace(bjm_glb_mspace);
}

/*
#include "tak_mak.hh"
void test_dlmalloc_align(){
	unsigned long init_val = 10;
	tak_mak gg(init_val);

	for(int aa = 0; aa < 1000; aa++){
		long val = gg.gen_rand_int32_ie(1, 1000);
		printf("%ld ", val);
	}
	printf("\n\n");
	
}*/

int main(int argc, char *argv[]) {
	int rr = 0;
	rr = bj_host_main(argc, argv);
	return rr;
	//test_dlmalloc_align();
}


