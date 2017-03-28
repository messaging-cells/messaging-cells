/*
  File: e-loader.c

  This file is part of the Epiphany Software Development Kit.

  Copyright (C) 2013 Adapteva, Inc.
  See AUTHORS for list of contributors.
  Support e-mail: <support@adapteva.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License (LGPL)
  as published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  and the GNU Lesser General Public License along with this program,
  see the files COPYING and COPYING.LESSER.  If not, see
  <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include <elf.h>
#include <inttypes.h>

#include "e-hal.h"
#include "core_loader_znq.h"
//include "esim-target.h"
#include "shared.h"
#include "booter.h"

#ifndef BJL_MARK_USED
#define BJL_MARK_USED(X)  ((void)(&(X)))
#endif

/* 
#define bjh_code_loader_buff_sz 1048576
uint8_t BJH_CODE_LOADER_BUFF[bjh_code_loader_buff_sz];

uint16_t DBGH_CODE_SHD_1[DBGH_CODE_SHD_SZ];
bj_addr_t DBGH_FUNC_ADDR = 0;

void
ck_dbg_shd_code(char* msg, uint16_t* base){
	printf("%s \n", msg);
	if(base == NULL){
		bjh_abort_func(9, "ck_dbg_shd_code() FAILED !!\n");
	}
	uint16_t* pt_func = (uint16_t*)(((uint8_t*)base) + DBGH_FUNC_ADDR);
	for(int aa = 0; aa < DBGH_CODE_SHD_SZ; aa++){
		printf("0x%04x \n", pt_func[aa]);
		if(DBGH_CODE_SHD_1[aa] != pt_func[aa]){
			printf("0x%04x != 0x%04x \n", DBGH_CODE_SHD_1[aa], pt_func[aa]);
			bjh_abort_func(9, "ck_dbg_shd_code() FAILED !! FUNCTION_LOADING_FAILED !!\n");
			//printf("ck_dbg_shd_code() FAILED !!\n");
		}
	}
}

bj_addr_t
dbg_read_addr_test_func(){
	off_t fsz = 0;
	uint8_t* data = read_file("addr_func_test_link_shd_code.txt", &fsz);
	bj_addr_t addr = 0;
	if(data == NULL){
		return 0;
	}	
	sscanf((char*)data, "%x", &addr);
	printf("Function 'test_link_shd_code' HAS_LOADING_ADDRESS= %x\n", addr);
	return addr;
}

*/

void
bj_ck_memload(uint8_t* pt1, uint8_t* pt2, size_t sz){
	for(long aa = 0; aa < sz; aa++){
		if(pt1[aa] != pt2[aa]){
			bjh_abort_func(9, "bj_ck_memload() FAILED !! FUNCTION_LOADING_FAILED !!\n");
		}
	}
}

uint8_t*
bj_memload(uint8_t* dest, const uint8_t* src, bj_size_t sz){
	bj_size_t idx = 0;
	for(idx = 0; idx < sz; idx++){
		bj_set_off_chip_var(dest[idx], src[idx]);
	}
	return dest;
}




void ee_get_coords_from_id(e_epiphany_t *dev, unsigned coreid,
								  unsigned *row, unsigned *col);

extern e_platform_t e_platform;

#define bjl_pt_out_of_range(pt, rs, rf) (((pt) < (rs)) || ((pt) > (rf)))

#define BJL_ARRAY_SIZE(_a) (sizeof(_a) / sizeof((_a)[0]))

#define bjl_diag(vN)   if (bjl_load_verbose >= vN)

typedef enum {
	L_D0 = 0,
	L_D1 = 1,
	L_D2 = 2,
	L_D3 = 3,
	L_D4 = 40,
} bjl_loader_diag_t;

enum bjl_loader_sections {
	BJL_SEC_WORKGROUP_CFG,
	BJL_SEC_EXT_MEM_CFG,
	BJL_SEC_LOADER_CFG,
	BJL_SEC_NUM,
};

struct bjl_section_info {
	const char *name;
	bool present;
	Elf32_Addr	sh_addr;		/* Section virtual addr at execution */
};
// TODO: These should be defined in common header file
#define BJL_BSS_CLEARED_FLAG 1
#define BJL_CUSTOM_ARGS_FLAG 2

struct bjl_loader_cfg {
	uint32_t flags;
	uint32_t __pad1;
	uint32_t args_ptr;
	uint32_t __pad2;
} __attribute__((packed));

void bjl_lookup_sections(const void *file, struct bjl_section_info *tbl,
							size_t tbl_size);

e_return_stat_t bjl_process_elf(const void *file, e_epiphany_t *dev,
									  e_mem_t *emem, int row, int col);

//int bjl_set_core_config(struct bjl_section_info *tbl, e_epiphany_t *dev,
//							  e_mem_t *emem, int row, int col);

bjl_loader_diag_t bjl_load_verbose = L_D3;

/* bjl_diag_fd is set by set_loader_verbosity() */
FILE *bjl_diag_fd = bj_null;

// TODO: replace with platform data
#define BJL_EMEM_SIZE (0x02000000)

extern bj_off_sys_st* DBG_BASE;
uint8_t* BJL_BASE_PT = bj_null;

#define EM_ADAPTEVA_EPIPHANY   0x1223  /* Adapteva's Epiphany architecture.  */
static inline bool bjl_is_epiphany_exec_elf(Elf32_Ehdr *ehdr)
{
	return ehdr
		&& memcmp(ehdr->e_ident, ELFMAG, SELFMAG) == 0
		&& ehdr->e_ident[EI_CLASS] == ELFCLASS32
		&& ehdr->e_type == ET_EXEC
		&& ehdr->e_version == EV_CURRENT
		&& ehdr->e_machine == EM_ADAPTEVA_EPIPHANY;
}

static bool bjl_is_srec_file(const char *hdr)
{
	const char srechdr[] = {'S', '0'};
	return (memcmp(hdr, srechdr, sizeof(srechdr)) == 0);
}

int bj_load(const char *executable, e_epiphany_t *dev, unsigned row, unsigned col, e_bool_t start)
{
	int status;

	status = bj_load_group(executable, dev, row, col, 1, 1, start);

	return status;
}

static void bjl_clear_sram(e_epiphany_t *dev,
					   unsigned row, unsigned col,unsigned rows, unsigned cols)
{
	unsigned i, j;
	size_t sram_size;
	void *empty;

	/* Assume one chip type */
	sram_size = e_platform.chip[0].sram_size;

	empty = alloca(sram_size);
	memset(empty, 0, sram_size);

	for (i = row; i < row + rows; i++){
		for (j = col; j < col + cols; j++){
			e_write(dev, i, j, 0, empty, sram_size);
		}
	}
}

int bj_load_group(const char *executable, e_epiphany_t *dev, unsigned row, unsigned col, 
			unsigned rows, unsigned cols, e_bool_t start)
{
	e_mem_t      emem;
	unsigned int irow, icol, i;
	int          status;
	//int          fd;
	struct stat  st;
	void        *file;
	bool         is_srec = false;
	e_return_stat_t retval;

	e_set_host_verbosity(H_D0);
	bjl_diag_fd = stderr;

	/*int eph_fd = open("/dev/epiphany/mesh0", O_RDWR | O_SYNC);
	if (eph_fd == -1){
		bjh_abort_func(9, "bj_load_group() Cannot open epiphany device.\n");
		return -1;
	}*/

	struct bjl_section_info tbl[] = {
		{ .name = "workgroup_cfg" },
		{ .name = "ext_mem_cfg" },
		{ .name = "loader_cfg" },
	};

	status = E_OK;

	if (!dev) {
		warnx("ERROR: Can't connect to Epiphany or external memory.\n");
		return E_ERR;
	}

	// Allocate External DRAM for the epiphany executable code
	// TODO: this is barely scalable. Really need to test ext. mem size to load
	// and possibly split the ext. mem accesses into 1MB chunks.
	if (e_alloc(&emem, 0, BJL_EMEM_SIZE)) {
		warnx("\nERROR: Can't allocate external memory buffer!\n\n");
		return E_ERR;
	}

	BJL_BASE_PT = (uint8_t*)(emem.base);

	/*
	fd = open(executable, O_RDONLY);
	if (fd == -1) {
		warnx("ERROR: Can't open executable file \"%s\".\n", executable);
		e_free(&emem);
		return E_ERR;
	}

	if (fstat(fd, &st) == -1) {
		warnx("ERROR: Can't stat file \"%s\".\n", executable);
		close(fd);
		e_free(&emem);
		return E_ERR;
    }

	BJH_CK(st.st_size < bjh_code_loader_buff_sz);
	file = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file == MAP_FAILED) {
		warnx("ERROR: Can't mmap file \"%s\".\n", executable);
		close(fd);
		e_free(&emem);
		return E_ERR;
    }
	*/
	off_t fsize;
	uint8_t* fdata = read_file((char*)executable, &fsize);
	file = fdata;

	uint8_t* pt_mem_start = (uint8_t*)(emem.base);
	uint8_t* pt_mem_end = pt_mem_start + BJL_EMEM_SIZE;
	uint8_t* pt_file_start = (uint8_t*)(file);
	uint8_t* pt_file_end = pt_mem_start + st.st_size;
	bjl_diag(L_D3) {
		fprintf(bjl_diag_fd, "bj_load_group(): mem_beg=%p end=%p file_beg=%p end=%p\n",
				pt_mem_start, pt_mem_end, pt_file_start, pt_file_end); 
	}
	/*
	BJH_CK(bjl_pt_out_of_range(pt_mem_start, pt_file_start, pt_file_end));
	BJH_CK(bjl_pt_out_of_range(pt_mem_end, pt_file_start, pt_file_end));
	BJH_CK(bjl_pt_out_of_range(pt_file_start, pt_mem_start, pt_mem_end));
	BJH_CK(bjl_pt_out_of_range(pt_file_end, pt_mem_start, pt_mem_end));
	bjl_diag(L_D3) {
		printf("TYPE ENTER\n");
		getchar();
	}
	*/

	if (bjl_is_epiphany_exec_elf((Elf32_Ehdr *) file)) {
		bjl_diag(L_D1) { fprintf(bjl_diag_fd, "load_group(): loading ELF file %s ...\n", executable); }
	} else if (bjl_is_srec_file((char *) file)) {
		is_srec = true;
		warnx("load_group(): WARNING: SREC file support is deprecated and will be removed in the next ESDK release. Use ELF format instead.\n");
	} else {
		bjl_diag(L_D1) { fprintf(bjl_diag_fd, "load_group(): ERROR: unidentified file format\n"); }
		warnx("ERROR: Can't load executable file: unidentified format.\n");
		status = E_ERR;
		goto out;
	}

	if (is_srec) {
		/* No symbol info in SREC files, use hard coded values */
		tbl[BJL_SEC_WORKGROUP_CFG].present = true;
		tbl[BJL_SEC_WORKGROUP_CFG].sh_addr = 0x28;
		tbl[BJL_SEC_EXT_MEM_CFG].present   = true;
		tbl[BJL_SEC_EXT_MEM_CFG].sh_addr   = 0x50;
		tbl[BJL_SEC_LOADER_CFG].present    = true;
		tbl[BJL_SEC_LOADER_CFG].sh_addr    = 0x58;
	} else {
		bjl_lookup_sections(file, tbl, BJL_ARRAY_SIZE(tbl));
	}

	for (i = 0; i < BJL_SEC_NUM; i++) {
		if (!tbl[i].present) {
			warnx("load_group(): WARNING: %s section not in binary.",
				  tbl[i].name);
		}
	}

	bjl_clear_sram(dev, row, col, rows, cols);

	for (irow=row; irow<(row+rows); irow++) {
		for (icol=col; icol<(col+cols); icol++) {
			if (is_srec){
				warnx("ERROR: SREC FORMAT NOT SUPPORTED ANYMORE.\n");
				retval = E_ERR;
			} else {
				retval = bjl_process_elf(file, dev, &emem, irow, icol);
			}

			if (retval == E_ERR) {
				warnx("ERROR: Can't load executable file \"%s\".\n", executable);
				status = E_ERR;
				goto out;
			}

			//bjl_set_core_config(tbl, dev, &emem, irow, icol);
		}
	}

	if (start) {
		for (irow=row; irow<(row+rows); irow++) {
			for (icol=col; icol<(col + cols); icol++) {
				bjl_diag(L_D1) {
					fprintf(bjl_diag_fd,
							"load_group(): send SYNC signal to core (%d,%d)...\n",
							irow, icol); }
				e_start(dev, irow, icol);
				bjl_diag(L_D1) {fprintf(bjl_diag_fd, "load_group(): done.\n"); }
			}
		}
	}

	bjl_diag(L_D1) { fprintf(bjl_diag_fd, "load_group(): done loading.\n"); }

	//ck_dbg_shd_code("CHECK_1", emem.base);

out:
	//munmap(file, st.st_size);
	//close(fd);
	free(fdata);
	e_free(&emem);

	return status;
}

void bjl_lookup_sections(const void *file, struct bjl_section_info *tbl,
							size_t tbl_size)
{
	int i;
	size_t j;
	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdr;
	Elf32_Shdr *shdr, *sh_strtab;
	const char *strtab;
	uint8_t *src = (uint8_t *) file;

	BJL_MARK_USED(phdr);

	ehdr = (Elf32_Ehdr *) &src[0];
	phdr = (Elf32_Phdr *) &src[ehdr->e_phoff];
	shdr = (Elf32_Shdr *) &src[ehdr->e_shoff];
	int shnum = ehdr->e_shnum;

	sh_strtab = &shdr[ehdr->e_shstrndx];
	strtab = (char *) &src[sh_strtab->sh_offset];

	for (i = 0; i < shnum; i++) {
		for (j = 0; j < tbl_size; j++) {
			if (tbl[j].present)
				continue;

			if (strcmp(&strtab[shdr[i].sh_name], tbl[j].name) != 0)
				continue;

			tbl[j].present = true;
			tbl[j].sh_addr = shdr[i].sh_addr;
		}
	}
}

/*
int bjl_set_core_config(struct bjl_section_info *tbl, e_epiphany_t *pEpiphany,
							  e_mem_t *pEMEM, int row, int col)
{
	e_group_config_t e_group_config;
	e_emem_config_t  e_emem_config;
	struct bjl_loader_cfg loader_cfg = { 0 };

	loader_cfg.flags = BJL_BSS_CLEARED_FLAG;

	e_group_config.objtype     = E_EPI_GROUP;
	e_group_config.chiptype    = pEpiphany->type;
	e_group_config.group_id    = pEpiphany->base_coreid;
	e_group_config.group_row   = pEpiphany->row;
	e_group_config.group_col   = pEpiphany->col;
	e_group_config.group_rows  = pEpiphany->rows;
	e_group_config.group_cols  = pEpiphany->cols;
	e_group_config.core_row    = row;
	e_group_config.core_col    = col;

	e_group_config.alignment_padding = 0xdeadbeef;

	e_emem_config.objtype   = E_EXT_MEM;
	e_emem_config.base      = pEMEM->ephy_base;

	if (tbl[BJL_SEC_WORKGROUP_CFG].present)
		e_write(pEpiphany, row, col, tbl[BJL_SEC_WORKGROUP_CFG].sh_addr,
				&e_group_config, sizeof(e_group_config_t));

	if (tbl[BJL_SEC_EXT_MEM_CFG].present)
		e_write(pEpiphany, row, col, tbl[BJL_SEC_EXT_MEM_CFG].sh_addr,
				&e_emem_config, sizeof(e_emem_config_t));

	if (tbl[BJL_SEC_LOADER_CFG].present)
		e_write(pEpiphany, row, col, tbl[BJL_SEC_LOADER_CFG].sh_addr,
				&loader_cfg, sizeof(loader_cfg));

	return 0;
}
*/

#define BJL_COREID(_addr) ((_addr) >> 20)
static inline bool bjl_is_local(uint32_t addr)
{
	return BJL_COREID(addr) == 0;
}

static bool bjl_is_valid_addr(uint32_t addr)
{
	return bjl_is_local(addr)
		|| e_is_addr_on_chip((void *) addr)
		|| e_is_addr_in_emem(addr);
}

static bool bjl_is_valid_range(uint32_t from, uint32_t size)
{
	/* Always allow empty range */
	if (!size)
		return true;

	return bjl_is_valid_addr(from) && bjl_is_valid_addr(from + size - 1);
}

e_return_stat_t
bjl_process_elf(const void *file, e_epiphany_t *dev, e_mem_t *emem,
			   int row, int col)
{
	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdr;
	bool       islocal, isonchip, isexternal;
	int        ihdr;
	unsigned   globrow, globcol;
	unsigned   coreid;
	uintptr_t  dst;
	/* TODO: Make src const (need fix in esim.h first) */
	uint8_t   *src = (uint8_t *) file;

	islocal  = false;
	isonchip = false;
	isexternal = false;
	BJL_MARK_USED(isexternal);

	ehdr = (Elf32_Ehdr *) &src[0];
	phdr = (Elf32_Phdr *) &src[ehdr->e_phoff];

	/* Range-check sections */
	for (ihdr = 0; ihdr < ehdr->e_phnum; ihdr++) {
		if (!bjl_is_valid_range(phdr[ihdr].p_vaddr, phdr[ihdr].p_memsz))
			return E_ERR;
	}

	for (ihdr = 0; ihdr < ehdr->e_phnum; ihdr++) {
		/* Nothing to do if section is empty */
		if (!phdr[ihdr].p_memsz)
			continue;

		islocal = bjl_is_local(phdr[ihdr].p_vaddr);
		isonchip = islocal ? true
						   /* TODO: Don't cast to void */
						   : e_is_addr_on_chip((void *) ((uintptr_t) phdr[ihdr].p_vaddr));

		bjl_diag(L_D3) {
			fprintf(bjl_diag_fd, "process_elf(): copying the data (%d bytes)",
					phdr[ihdr].p_filesz); }

		/* Address calculation */
		char* dbg_case = "(undef)";
		uint32_t the_p_vaddr = phdr[ihdr].p_vaddr;
		if (islocal) {
			bjl_diag(L_D3) { dbg_case = "(local)"; fprintf(bjl_diag_fd, " (local) to core (%d,%d)\n", row, col); }

			// TODO: should this be p_paddr instead of p_vaddr?
			dst = ((uintptr_t) dev->core[row][col].mems.base)
				+ phdr[ihdr].p_vaddr;
		} else if (isonchip) {
			coreid = phdr[ihdr].p_vaddr >> 20;
			ee_get_coords_from_id(dev, coreid, &globrow, &globcol);
			bjl_diag(L_D3) { dbg_case = "(onchip)"; 
				fprintf(bjl_diag_fd, " (onchip) to core (%d,%d)\n", globrow, globcol); }
			// TODO: should this be p_paddr instead of p_vaddr?
			dst = ((uintptr_t) dev->core[globrow][globcol].mems.base)
				+ (phdr[ihdr].p_vaddr & 0x000fffff);
		} else {
			isexternal = true;
			// If it is not on an eCore, it's in external memory.
			bjl_diag(L_D3) { dbg_case = "(external)"; fprintf(bjl_diag_fd, " (external) to external memory.\n"); }
			dst = phdr[ihdr].p_vaddr - emem->ephy_base + (uintptr_t) emem->base;
			bjl_diag(L_D3) {
				fprintf(bjl_diag_fd,
						"process_elf(): converting virtual (%p) to physical (%p)...\n",
						(void*) phdr[ihdr].p_vaddr,
						(void*) dst); }

		}

		/* Write */
		uint8_t* pt_dst = (void *) dst;
		uint8_t* pt_src = &src[phdr[ihdr].p_offset];
		size_t blk_sz = phdr[ihdr].p_filesz;

		uint8_t* pt_dst_end = pt_dst + blk_sz;
		uint8_t* pt_src_end = pt_src + blk_sz;

		BJH_CK(bjl_pt_out_of_range(pt_dst, pt_src, pt_src_end));
		BJH_CK(bjl_pt_out_of_range(pt_dst_end, pt_src, pt_src_end));
		BJH_CK(bjl_pt_out_of_range(pt_src, pt_dst, pt_dst_end));
		BJH_CK(bjl_pt_out_of_range(pt_src_end, pt_dst, pt_dst_end));

		//int dbg_load_func = 0;
		//uint8_t* pt_end_code = (BJL_BASE_PT + BJ_SHARED_MEM_START_DISP);
		//uint8_t* pt_end_mem = (BJL_BASE_PT + BJL_EMEM_SIZE);

		bjl_diag(L_D1) { fprintf(bjl_diag_fd, 
				"LOADING(%s). row=%d col=%d dst=%p end=%p src=%p end=%p sz=%d p_vaddr=%04x (%p).\n", 
				dbg_case, row, col, pt_dst, pt_dst_end, pt_src, pt_src_end, blk_sz, the_p_vaddr, 
				(void*)the_p_vaddr); 
		}


		if(isexternal){
			uint8_t* pt_end_mem = (BJL_BASE_PT + BJ_SHARED_MEM_START_DISP);
			uint8_t* pt_end_code = (((uint8_t*)pt_dst) + blk_sz);
			if(pt_end_code > pt_end_mem){
				bjl_diag(L_D3) {
					fprintf(bjl_diag_fd,
							"process_elf(): SKIP section in SHARED DATA virtual (%p) to physical (%p). SIZE=%u\n",
							(void*) phdr[ihdr].p_vaddr,
							(void*) dst,
							blk_sz
							); 
				}
				continue;	// Its data (an structure) NOT code.
			}

			/*if(the_p_vaddr == 0x8e000000){
				bj_addr_t addr_fn = dbg_read_addr_test_func();
				if(addr_fn != 0){
					addr_fn -= (bj_addr_t)the_p_vaddr;
					DBGH_FUNC_ADDR = addr_fn;
					printf("ADDR=%x \n", DBGH_FUNC_ADDR);
					printf("FUNCTION MACHINE CODE IS (compare to generated file 'code_prog.s'):\n");
					uint16_t* src_test_func = (uint16_t*)(((uint8_t*)pt_src) + DBGH_FUNC_ADDR);
					for(int aa = 0; aa < DBGH_CODE_SHD_SZ; aa++){
						DBGH_CODE_SHD_1[aa] = src_test_func[aa];
						printf("0x%04x \n", DBGH_CODE_SHD_1[aa]);
					}
					ck_dbg_shd_code("CHECK_2", (uint16_t*)pt_src);
					dbg_load_func = 1;
				}
			}*/
		}

		//memcpy(pt_dst, pt_src, blk_sz);		// CHANGES MEMORY OUTSIDE OF RANGES !!!!! WHY !!!!
		//bj_memcpy(pt_dst, pt_src, blk_sz);		// CHANGES MEMORY OUTSIDE OF RANGES !!!!! WHY !!!!
		bj_memload(pt_dst, pt_src, blk_sz);

		bj_ck_memload(pt_dst, pt_src, blk_sz);	// LEAVE THIS. IT CAN FAIL !!!!

		/*if(dbg_load_func){
			ck_dbg_shd_code("CHECK_3", (uint16_t*)pt_src);
			ck_dbg_shd_code("CHECK_4", (uint16_t*)pt_dst);
		}*/

		//memcpy((void *) dst, &src[phdr[ihdr].p_offset], phdr[ihdr].p_filesz);
		/* We might want to clear mem in range [p_filesz-p_memsz] here.
		 * .bss sections have this. For now assume all memory is cleared
		 * elsewhere. */
	}

	return E_OK;
}

