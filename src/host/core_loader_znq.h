/*
  File: e-loader.h

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

#ifndef BJ_LOADER_H
#define BJ_LOADER_H

#include <elf.h>
#include "e-hal.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "shared.h"

#ifndef BJL_MARK_USED
#define BJL_MARK_USED(X)  ((void)(&(X)))
#endif

extern uint8_t* BJH_EXTERNAL_RAM_BASE_PT;

extern e_mem_t bjh_glb_emem;
extern e_epiphany_t bjh_glb_dev;

#define bjh_min_shd_eph_addr ((bj_addr_t) bjh_glb_emem.ephy_base)
#define bjh_max_shd_eph_addr ((bj_addr_t) (bjh_glb_emem.ephy_base + BJ_EXTERNAL_RAM_LOAD_DATA.extnl_ram_size))
#define bjh_min_shd_znq_addr ((bj_addr_t) bjh_glb_emem.base)
#define bjh_max_shd_znq_addr ((bj_addr_t) (bjh_glb_emem.base + BJ_EXTERNAL_RAM_LOAD_DATA.extnl_ram_size))
#define bjh_znq_addr_in_shd_ram(znq_addr) ((bjh_min_shd_znq_addr <= znq_addr) && (znq_addr < bjh_max_shd_znq_addr))

#define bjh_disp_to_pt(disp) (BJH_EXTERNAL_RAM_BASE_PT + disp)

typedef enum {
	L_D0 = 0,
	L_D1 = 1,
	L_D2 = 2,
	L_D3 = 3,
	L_D4 = 40,
} bjl_loader_diag_t;

extern bjl_loader_diag_t bjl_load_verbose;

#define bjl_diag(vN)   if (bjl_load_verbose >= vN)

struct load_info_st {    
	char *executable;
	e_epiphany_t *dev;
	unsigned row;
	unsigned col;
	unsigned rows;
	unsigned cols;
	char**	all_module_names;
	void**	all_module_addrs;	// as seen from ephiphany side

	void *file;
	e_mem_t *emem;
};
typedef struct load_info_st load_info_t;


int bj_load_group(load_info_t *ld_dat);

#define DBGH_CODE_SHD_SZ 20
extern uint16_t DBGH_CODE_SHD_1[DBGH_CODE_SHD_SZ];
extern bj_addr_t DBGH_FUNC_ADDR;

bool 
bjl_is_epiphany_exec_elf(Elf32_Ehdr *ehdr);

void
ck_dbg_shd_code(char* msg, uint16_t* base);

#ifdef __cplusplus
}
#endif

#endif // BJ_LOADER_H
