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

extern e_platform_t e_platform;

e_return_stat_t bjl_load_elf(int row, int col, load_info_t *ld_dat);

//bjl_loader_diag_t bjl_load_verbose = L_D3;
bjl_loader_diag_t bjl_load_verbose = L_D0;

void
bj_ck_memload(uint8_t* dst, uint8_t* src, uint32_t sz){
	bool ok = true;
	for(long aa = 0; aa < sz; aa++){
		if(dst[aa] != src[aa]){
			ok = false;
			break;
		}
	}
	if(! ok){
		bjh_write_file("SOURCE_shd_mem_dump.dat", src, sz, false);
		bjh_write_file("DEST_shd_mem_dump.dat", dst, sz, false);
		bjh_abort_func(9, "bj_ck_memload() FAILED !! CODE_LOADING_FAILED !!\n");
	}
}

uint8_t*
bj_memload(uint8_t* dest, const uint8_t* src, uint32_t sz){
	uint32_t idx = 0;
	for(idx = 0; idx < sz; idx++){
		bj_set_off_chip_var(dest[idx], src[idx]);
	}
	return dest;
}

#define EM_ADAPTEVA_EPIPHANY   0x1223  /* Adapteva's Epiphany architecture.  */
bool bjl_is_epiphany_exec_elf(Elf32_Ehdr *ehdr)
{
	bool ok = true;
	if(! ehdr){ 
		bjl_diag(L_D1) { fprintf(BJ_STDERR, "bjl_is_epiphany_exec_elf(): ERROR_1\n"); }
		return false;
	}
	if(memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0){ 
		bjl_diag(L_D1) { fprintf(BJ_STDERR, "bjl_is_epiphany_exec_elf(): NOT ELFMAG\n"); }
		ok = false;
	}
	if(ehdr->e_ident[EI_CLASS] != ELFCLASS32){
		bjl_diag(L_D1) { fprintf(BJ_STDERR, "bjl_is_epiphany_exec_elf(): NOT ELFCLASS32\n"); }
		ok = false;
	}
	if(ehdr->e_type != ET_EXEC){
		bjl_diag(L_D1) { fprintf(BJ_STDERR, "bjl_is_epiphany_exec_elf(): NOT ET_EXEC\n"); }
		ok = false;
	}
	if(ehdr->e_version != EV_CURRENT){
		bjl_diag(L_D1) { fprintf(BJ_STDERR, "bjl_is_epiphany_exec_elf(): NOT EV_CURRENT\n"); }
		ok = false;
	}
	if(ehdr->e_machine != EM_ADAPTEVA_EPIPHANY){
		bjl_diag(L_D1) { fprintf(BJ_STDERR, "bjl_is_epiphany_exec_elf(): NOT EM_ADAPTEVA_EPIPHANY\n"); }
		ok = false;
	}

	return ok;
}

static void bjl_clear_sram(e_epiphany_t *dev, unsigned row, unsigned col,unsigned rows, unsigned cols)
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

e_return_stat_t
bj_start_load(load_info_t *ld_dat){
	int          fd;
	struct stat  st;
	void        *file;

	e_set_host_verbosity(H_D0);

	const char *executable = ld_dat->executable;
	e_epiphany_t *dev = ld_dat->dev;
	bj_core_co_t row = ld_dat->row;
	bj_core_co_t col = ld_dat->col;
	bj_core_co_t rows = ld_dat->rows;
	bj_core_co_t cols = ld_dat->cols;

	bj_link_syms_data_st* lk_dat = &(BJ_EXTERNAL_RAM_LOAD_DATA);

	if (!dev) {
		warnx("ERROR: Can't connect to Epiphany or external memory.\n");
		return E_ERR;
	}

	fd = open(executable, O_RDONLY);
	if (fd == -1) {
		warnx("ERROR: Can't open executable file \"%s\".\n", executable);
		return E_ERR;
	}

	if (fstat(fd, &st) == -1) {
		warnx("ERROR: Can't stat file \"%s\".\n", executable);
		close(fd);
		return E_ERR;
    }

	file = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file == MAP_FAILED) {
		warnx("ERROR: Can't mmap file \"%s\".\n", executable);
		close(fd);
		return E_ERR;
    }
	
	uint8_t* pt_mem_start = (uint8_t*)(bjh_glb_emem.base);
	uint8_t* pt_mem_end = pt_mem_start + lk_dat->extnl_ram_size;
	uint8_t* pt_file_start = (uint8_t*)(file);
	uint8_t* pt_file_end = pt_mem_start + st.st_size;
	bjl_diag(L_D3) {
		fprintf(BJ_STDERR, "load_group(): mem_beg=%p end=%p file_beg=%p end=%p\n",
				pt_mem_start, pt_mem_end, pt_file_start, pt_file_end); 
	}

	if (bjl_is_epiphany_exec_elf((Elf32_Ehdr *) file)) {
		bjl_diag(L_D1) { fprintf(BJ_STDERR, "load_group(): loading ELF file %s ...\n", executable); }
	} else {
		bjl_diag(L_D1) { fprintf(BJ_STDERR, "load_group(): ERROR: unidentified file format\n"); }
		warnx("ERROR: Can't load executable file: unidentified format.\n");
		munmap(file, st.st_size);
		close(fd);
		return E_ERR;
	}

	bjl_clear_sram(dev, row, col, rows, cols);

	ld_dat->file = file;
	ld_dat->emem = &bjh_glb_emem;
	ld_dat->f_sz = st.st_size;
	ld_dat->fd = fd;

	return E_OK;
}

int bj_load_group(load_info_t *ld_dat){

	e_return_stat_t ret_start;
	ret_start = bj_start_load(ld_dat);
	if (ret_start == E_ERR) {
		return E_ERR;
	}

	unsigned row = ld_dat->row;
	unsigned col = ld_dat->col;
	unsigned rows = ld_dat->rows;
	unsigned cols = ld_dat->cols;

	unsigned int irow, icol;

	for (irow=row; irow<(row+rows); irow++) {
		for (icol=col; icol<(col+cols); icol++) {
			e_return_stat_t retval = bjl_load_elf(irow, icol, ld_dat);

			if (retval == E_ERR) {
				warnx("ERROR: Can't load executable file \"%s\".\n", ld_dat->executable);
				munmap(ld_dat->file, ld_dat->f_sz);
				close(ld_dat->fd);
				return E_ERR;
			}
		}
	}

	bjl_diag(L_D1) { fprintf(BJ_STDERR, "load_group(): done loading.\n"); }

	munmap(ld_dat->file, ld_dat->f_sz);
	close(ld_dat->fd);

	return E_OK;
}

static bool bjl_is_valid_addr(uint32_t addr)
{
	return (! bj_addr_has_id(addr))
		|| e_is_addr_on_chip((void *) addr)
		|| e_is_addr_in_emem(addr);
}

static bool bjl_is_valid_range(uint32_t from, uint32_t size)
{
	if(!size){
		return true;
	}

	return bjl_is_valid_addr(from) && bjl_is_valid_addr(from + size - 1);
}

bj_addr_t
bj_znq_addr_to_eph_addr(bj_addr_t znq_addr){
	BJH_CK(bjh_znq_addr_in_shd_ram(znq_addr));

	bj_addr_t eph_addr = znq_addr - bjh_min_shd_znq_addr + bjh_min_shd_eph_addr;
	
	return eph_addr;
}

bj_addr_t
bj_eph_addr_to_znq_addr(bj_addr_t eph_addr){
	e_epiphany_t *dev = &bjh_glb_dev;

	BJH_CK(bj_addr_has_id(eph_addr));
	
	bj_addr_t znq_addr = bj_null;
	if (bj_addr_in_sys(eph_addr)) {
		bj_core_id_t coreid = bj_addr_get_id(eph_addr);
		bj_core_co_t g_ro = bj_id_to_ro(coreid);
		bj_core_co_t g_co = bj_id_to_co(coreid);

		znq_addr = ((bj_addr_t) dev->core[g_ro][g_co].mems.base) + bj_addr_get_disp(eph_addr);

	} else {
		znq_addr = eph_addr - bjh_min_shd_eph_addr + bjh_min_shd_znq_addr;
	}
	return znq_addr;
}

bj_addr_t
bj_core_eph_addr_to_znq_addr(int row, int col, bj_addr_t ld_addr){
	e_epiphany_t *dev = &bjh_glb_dev;

	bj_addr_t dst = bj_null;
	if (! bj_addr_has_id(ld_addr)) {
		dst = ((uintptr_t) dev->core[row][col].mems.base) + ld_addr;
	} else {
		dst = bj_eph_addr_to_znq_addr(ld_addr);
	}
	return dst;
}

char*
bj_addr_case(bj_addr_t ld_addr){
	if(! bj_addr_has_id(ld_addr)){
		return "(local)";
	}
	if(bj_addr_in_sys(ld_addr)){
		return "(onchip)";
	}
	return "(external)";
}

e_return_stat_t
bjl_load_elf(int row, int col, load_info_t *ld_dat)
{
	int ii;
	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdr;
	Elf32_Shdr *shdr, *sh_strtab;
	const char *strtab;
	int        ihdr;

	e_mem_t *emem = ld_dat->emem;
	uint8_t   *src = (uint8_t *) ld_dat->file;

	e_epiphany_t *dev = ld_dat->dev;
	bj_link_syms_data_st* lk_dat = &(BJ_EXTERNAL_RAM_LOAD_DATA);

	BJL_MARK_USED(phdr);
	BJL_MARK_USED(ihdr);
	BJL_MARK_USED(shdr);
	BJL_MARK_USED(sh_strtab);
	BJL_MARK_USED(strtab);

	BJH_CK(sizeof(Elf32_Addr) == sizeof(bj_addr_t));
	BJH_CK(dev == &bjh_glb_dev);
	BJH_CK(emem == &bjh_glb_emem);

	bj_core_id_t curr_id = bj_ro_co_to_id(row, col);
	BJL_MARK_USED(curr_id);

	ehdr = (Elf32_Ehdr *) &src[0];
	phdr = (Elf32_Phdr *) &src[ehdr->e_phoff];
	shdr = (Elf32_Shdr *) &src[ehdr->e_shoff];
	int shnum = ehdr->e_shnum;

	sh_strtab = &shdr[ehdr->e_shstrndx];
	strtab = (char *) &src[sh_strtab->sh_offset];

	for (ii = 0; ii < shnum; ii++) {
		if (!bjl_is_valid_range(shdr[ii].sh_addr, shdr[ii].sh_size)){
			return E_ERR;
		}
	}

	for (ii = 0; ii < shnum; ii++) {
		Elf32_Addr ld_sh_addr = shdr[ii].sh_addr;
		Elf32_Word ld_sz = shdr[ii].sh_size;
		Elf32_Word ld_src_sz = shdr[ii].sh_size;
		Elf32_Off  ld_src_off = shdr[ii].sh_offset;
		Elf32_Word ld_tp = shdr[ii].sh_type;
		Elf32_Word ld_flags = shdr[ii].sh_flags;

		const char* sect_nm = &strtab[shdr[ii].sh_name];
		bjl_diag(L_D1) { fprintf(BJ_STDERR, "%d.LOADING section %s.\n", ii, sect_nm); }

		if(ld_sz == 0){
			continue;
		}

		if(ld_tp != SHT_PROGBITS){
			continue;
		}

		if((ld_flags & SHF_ALLOC) != SHF_ALLOC){
			continue;
		}

		if(ld_sh_addr == lk_dat->core_module_orig){
			fprintf(BJ_STDERR, "%d.SKIP load of MODULE section %s.\n", ii, sect_nm);
			continue;
		}

		bj_addr_t ld_addr = ld_sh_addr;

		bj_addr_t dst = bj_core_eph_addr_to_znq_addr(row, col, ld_addr);

		uint8_t* pt_dst = (void *) dst;
		uint8_t* pt_src = &src[ld_src_off];
		size_t blk_sz = ld_src_sz;

		uint8_t* pt_dst_end = pt_dst + blk_sz;
		uint8_t* pt_src_end = pt_src + blk_sz;

		uint8_t* pt_ram_base = (uint8_t*)(emem->base);
		uint8_t* pt_end_code = (pt_ram_base + lk_dat->extnl_data_disp);
		uint8_t* pt_end_mem = (pt_ram_base + lk_dat->extnl_ram_size);
		BJL_MARK_USED(pt_end_code);
		BJL_MARK_USED(pt_end_mem);

		bjl_diag(L_D1) { fprintf(BJ_STDERR, 
				"%d.LOADING(%s). row=%d col=%d dst=%p end=%p src=%p end=%p sz=%d p_vaddr=%04x (%p).\n", 
				ii, bj_addr_case(ld_addr), row, col, pt_dst, pt_dst_end, pt_src, pt_src_end, blk_sz, ld_addr, 
				(void*)ld_addr); 
		}

		/*if(BJH_LOAD_WITH_MEMCPY){
			memcpy(pt_dst, pt_src, blk_sz);
		} else {
			bj_memload(pt_dst, pt_src, blk_sz);
		}*/

		memcpy(pt_dst, pt_src, blk_sz);
		bj_ck_memload(pt_dst, pt_src, blk_sz);
	}

	return E_OK;
}

int bj_load_root(load_info_t *ld_dat){

	e_return_stat_t ret_start;
	ret_start = bj_start_load(ld_dat);
	if (ret_start == E_ERR) {
		return E_ERR;
	}

	bj_core_co_t root_ro = bj_nn_to_ro(ld_dat->root_nn);
	bj_core_co_t root_co = bj_nn_to_co(ld_dat->root_nn);

	e_return_stat_t retval = 
		bjl_load_elf(root_ro, root_co, ld_dat);

	if (retval == E_ERR) {
		warnx("ERROR: Can't load executable file \"%s\".\n", ld_dat->executable);
		munmap(ld_dat->file, ld_dat->f_sz);
		close(ld_dat->fd);
		return E_ERR;
	}

	bjl_diag(L_D1) { fprintf(BJ_STDERR, "bj_load_root(): done loading.\n"); }

	munmap(ld_dat->file, ld_dat->f_sz);
	close(ld_dat->fd);

	return E_OK;
}

