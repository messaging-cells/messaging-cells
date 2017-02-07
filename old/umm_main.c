

#include <stdlib.h>

#include "global.h"
#include "umm_malloc.h"

#define TOT_OBJS 256
#define TOT_OPS 65535

void * all_objs[TOT_OBJS];
umm_size_t all_osz[TOT_OBJS];

void
before_mem(umm_size_t ii, umm_size_t nsz){
	umm_size_t aa;
	uint8_t* obj = all_objs[ii];
	umm_size_t osz = all_osz[ii];
	uint8_t vv = ii;
	if(obj != umm_null){
		for(aa = 0; aa < osz; aa++){
			if(obj[aa] != vv){
				bjk_abort((uint32_t)before_mem, 0, 0x0);
			}
			if(nsz == 0){
				obj[aa] = 0;
			}
		}
	}
}

void
after_mem(umm_size_t ii, umm_size_t nsz){
	umm_size_t aa;
	uint8_t* obj = all_objs[ii];
	//umm_size_t osz = all_osz[ii];
	uint8_t vv = ii;
	if(obj != umm_null){
		if(nsz == 0){
			bjk_abort((uint32_t)after_mem, 0, 0x0);
		}
		for(aa = 0; aa < nsz; aa++){
			obj[aa] = vv;
		}
		all_osz[ii] = nsz;
	}
}


int main() {
	bjk_init_global();

	umm_size_t ii;

	int idx;

	bj_memset( (uint8_t*)umm_heap, 0, sizeof(umm_heap) );

	umm_info( umm_null, 1 );

	for( idx=0; idx < TOT_OBJS; ++idx ){
		all_objs[idx] = (void *)umm_null;
		all_osz[idx] = 0;
	}

	for( idx=0; idx < TOT_OPS; ++idx ) {
		ii = rand() % TOT_OBJS;
		int hh = rand() % 16;
		int rsz = rand();
		int nsz = 0;

		switch( hh ) {
			case  0:
			case  1:
			case  2:
			case  3:
			case  4:
			case  5:
			case  6: 
				nsz = 0;
				break;
			case  7:
			case  8: 
				nsz = (rsz % 40);
				break;
			case  9:
			case 10:
			case 11:
			case 12: 
				nsz = (rsz % 100);
				break;
			case 13:
			case 14: 
				nsz = (rsz % 200);
				break;
			default: 
				nsz = (rsz % 400);
				break;
		}
		before_mem(ii, nsz);
		all_objs[ii] = umm_realloc(all_objs[ii], nsz );
		after_mem(ii, nsz);

	}

	umm_info( umm_null, 1 );

	bj_id_t koid = bjk_get_coreid();
	bj_consec_t num_core = bj_id_to_nn(koid);
	bjk_slog("TEST_UMM OK CORE ID=");
	bjk_xlog(koid);
	bjk_slog(" NUM=");
	bjk_ilog(num_core);
	bjk_slog("\n");

	bj_in_core_shd.dbg_progress_flag = 0xeee;
	
	bjk_set_finished(BJ_FINISHED_VAL);
	return 0;
}

