

/*************************************************************

This file is part of ben-jose.

ben-jose is free software: you can redistribute it and/or modify
it under the terms of the version 3 of the GNU General Public 
License as published by the Free Software Foundation.

ben-jose is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ben-jose.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------------

Copyright (C) 2007-2012, 2014-2016. QUIROGA BELTRAN, Jose Luis.
Id (cedula): 79523732 de Bogota - Colombia.
See https://github.com/joseluisquiroga/ben-jose

ben-jose is free software thanks to The Glory of Our Lord 
	Yashua Melej Hamashiaj.
Our Resurrected and Living, both in Body and Spirit, 
	Prince of Peace.

------------------------------------------------------------

sornet.hh

Declaration of functions to use the sornet.

--------------------------------------------------------------*/

#ifndef SORNET_H
#define SORNET_H

#include "nervenet.hh"

void sorcell_sornet_handler(missive* msv) bj_sornet_cod;
void endcell_sornet_handler(missive* msv) bj_sornet_cod;
void nervenet_sornet_handler(missive* msv) bj_sornet_cod;

int bj_dbg_cmp_bin_objs(void* obj1, void* obj2) mc_external_code_ram;
int bj_dbg_cmp_num_objs(void* obj1, void* obj2) mc_external_code_ram;
int bj_cmp_rnk_objs(void* obj1, void* obj2) bj_sornet_cod;

void bj_send_sornet_tmt(cell* src, sornet_tok_t tok, void* obj, sorcell* dst, num_nod_t idx) bj_sornet_cod;

void bj_sornet_kernel_func() bj_sornet_cod;
void bj_sornet_init_handlers() mc_external_code_ram;
void bj_sornet_main() mc_external_code_ram;

#endif		// SORNET_H


