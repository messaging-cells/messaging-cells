
#include <math.h>
#include <sched.h>
#include <string.h>

#include <e-hal.h>
#include <epiphany-hal-api-local.h>

#include "core_loader_znq.h"

#include "booter.h"
#include "tak_mak.hh"

//define NUM_OPERS 100000
#define NUM_OPERS 10000000

char* bjh_epiphany_elf_path = (const_cast<char*>("the_epiphany_executable.elf"));

#define BJT_COREID(_addr) ((_addr) >> 20)
static inline bool bjt_is_local(uint32_t addr)
{
	return BJT_COREID(addr) == 0;
}

#define addr_in_shd_mem(addr) (! (\
	((addr) >= BJH_EXTERNAL_RAM_BASE_PT) && \
	((addr) < (BJH_EXTERNAL_RAM_BASE_PT + lk_dat->extnl_ram_size)) \
	)) \


int 
bj_host_main(int argc, char *argv[])
{
	e_mem_t emem;
	e_epiphany_t dev;
	e_platform_t platform;
	bj_link_syms_data_st syms;
	char* elf_path = (const_cast<char *>("the_epiphany_executable.elf"));

	if(argc > 1){
		elf_path = argv[1];
		printf("Using core executable: %s \n", elf_path);
	}

	bj_link_syms_data_st* lk_dat = &(syms);
	bjh_read_eph_link_syms(elf_path, lk_dat);

	if(lk_dat->extnl_ram_orig == 0) {
		printf("ERROR: Can't read external memory location from '%s'\n", elf_path);
		printf("Make sure linker script for '%s' defines LD_EXTERNAL_* symbols\n\n", elf_path);
		bjh_abort_func(301, "301. ERROR: Bad ELF\n");
	}

	// sys init

	e_init(NULL);
	e_reset_system();
	e_get_platform_info(&platform);

	if (e_alloc(&emem, 0, lk_dat->extnl_ram_size)) {
		bjh_abort_func(302, "302. ERROR: Can't allocate external memory buffer!\n\n");
	}

	BJH_EXTERNAL_RAM_BASE_PT = ((uint8_t*)emem.base);
	BJ_MARK_USED(BJH_EXTERNAL_RAM_BASE_PT);

	// dev init
	
	e_open(&dev, 0, 0, platform.rows, platform.cols);

	bj_sys_sz_st* g_sys_sz = BJK_GLB_SYS_SZ;
	bjh_init_glb_sys_sz_with_dev(g_sys_sz, &dev);

	bj_off_sys_st* pt_shd_data = (bj_off_sys_st*)bjh_disp_to_pt(lk_dat->extnl_host_data_disp);
	BJH_CK(sizeof(*pt_shd_data) == sizeof(bj_off_sys_st));

	/*
	printf("BJH_EXTERNAL_RAM_BASE_PT=%p \n", BJH_EXTERNAL_RAM_BASE_PT);
	printf("pt_shd_data=%p \n", pt_shd_data);

	printf("extnl_ram_size = %p \n", (void*)syms.extnl_ram_size);
	printf("extnl_code_size = %p \n", (void*)syms.extnl_code_size);
	printf("extnl_load_size = %p \n", (void*)syms.extnl_load_size);
	printf("extnl_host_data_size = %p \n", (void*)syms.extnl_host_data_size);
	printf("extnl_host_alloc_size = %p \n", (void*)syms.extnl_host_alloc_size);
	printf("extnl_ram_orig = %p \n", (void*)syms.extnl_ram_orig);
	printf("extnl_code_orig = %p \n", (void*)syms.extnl_code_orig);
	printf("extnl_load_orig = %p \n", (void*)syms.extnl_load_orig);
	printf("extnl_host_data_orig = %p \n", (void*)syms.extnl_host_data_orig);
	printf("extnl_host_alloc_orig = %p \n", (void*)syms.extnl_host_alloc_orig);
	printf("extnl_code_disp = %p \n", (void*)syms.extnl_code_disp);
	printf("extnl_load_disp = %p \n", (void*)syms.extnl_load_disp);
	printf("extnl_host_data_disp = %p \n", (void*)syms.extnl_host_data_disp);
	printf("extnl_host_alloc_disp = %p \n", (void*)syms.extnl_host_alloc_disp);
	*/

	memset(pt_shd_data, 0, sizeof(*pt_shd_data));

	//============================================================

	bj_core_co_t row, col, max_row, max_col;

	void* min_shd = (void*)BJH_EXTERNAL_RAM_BASE_PT;
	void* max_shd = (void*)(BJH_EXTERNAL_RAM_BASE_PT + lk_dat->extnl_ram_size);

	max_row = 1;
	max_col = 2;
	max_row = dev.rows;
	max_col = dev.cols;
	for (row=0; row < max_row; row++){
		for (col=0; col < max_col; col++){
			void* dst = ((void*) dev.core[row][col].mems.base);
			printf("min=%p dst=%p max=%p\n", min_shd, dst, max_shd);
			BJH_CK(addr_in_shd_mem(dst));
		}
	}

	
	unsigned long init_val = 10;
	tak_mak gg(init_val);

	printf("STARTING ADDR CONV \n");

	for(long kk=0; kk < NUM_OPERS; kk++) {
		printf("%ld\r", kk);
		//long ii = gg.gen_rand_int32_ie(0, TEST_NUM_PTS);
		//long osz = gg.gen_rand_int32_ie(MIN_OBJ_SZ, MAX_OBJ_SZ);
		uint32_t ld_addr = gg.gen_rand_int32();
		//uint32_t ld_addr = gg.gen_rand_int32_ie(0, 1000);

		bool islocal = bjt_is_local(ld_addr);
		bool isonchip = islocal ? true : e_is_addr_on_chip((void *) ((uintptr_t) ld_addr));
		bool isexternal = ((! islocal) && (! isonchip));

		unsigned coreid = ld_addr >> 20;
		bj_addr_t coreid_2 = bj_addr_get_id(ld_addr);

		BJH_CK(coreid == coreid_2);

		bool islocal_2 = (coreid_2 == 0);
		bool isonchip_2 = bj_addr_in_sys(ld_addr);
		bool isexternal_2 = ((! islocal) && (! isonchip));

		//printf("%" PRIu32 " == %p  coreid=%u \n", ld_addr, (void*)ld_addr, coreid);
		bool islocal_3 = ! bj_addr_has_id(ld_addr);
		
		BJH_CK(islocal == islocal_2);
		BJH_CK(islocal == islocal_3);
		BJH_CK(isonchip == isonchip_2);
		BJH_CK(isexternal == isexternal_2);

		if(!islocal && isonchip){
			unsigned  globrow, globcol;
			ee_get_coords_from_id(&dev, coreid, &globrow, &globcol);
			bj_core_co_t g_ro = bj_id_to_ro(coreid);
			bj_core_co_t g_co = bj_id_to_co(coreid);

			//printf("coreid=%p \n", (void*)coreid);
			//printf("g_ro=%d globrow=%d\n", g_ro, globrow);

			BJH_CK(g_ro == globrow);
			BJH_CK(g_co == globcol);
		}

	}

	printf("\nFINISHED\n");
	

	//============================================================

	e_reset_group(&dev); // FAILS. Why?
	e_reset_system();
	
	e_close(&dev);
	
	e_free(&emem);
	e_finalize();

	return 0;
}


