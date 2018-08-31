

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

solver.hh

Declaration of main bj solver function.

--------------------------------------------------------------*/

#ifndef SOLVER_H
#define SOLVER_H

#include "cell.hh"

#define BJ_DBG_TOT_NUM_TESTS 1000
#define BJ_DBG_TOT_RNK_TESTS 400

#define BJ_DBG_TOT_INPUT_SORNODES 80
#define BJ_DBG_TOT_INPUT_RNKNODES 80
#define BJ_DBG_RNK_SZ_DIV 20

#define BJ_INVALID_IDX -1

#define bj_dbg_only_cod mc_mod1_cod
#define bj_dbg_only_dat mc_mod1_dat

#define bj_load_cod mc_mod2_cod
#define bj_load_dat mc_mod2_dat

#define bj_propag_cod mc_mod3_cod
#define bj_propag_dat mc_mod3_dat

#define bj_stabi_cod mc_mod4_cod
#define bj_stabi_dat mc_mod4_dat

#define bj_sornet_cod mc_mod5_cod
#define bj_sornet_dat mc_mod5_dat

#define bj_nervenet_cod 
#define bj_nervenet_dat 
#define bj_nervenet_mem mc_mod0_cod

typedef unsigned long u_num_nod_t;
typedef long num_nod_t;
typedef uint8_t num_syn_t;
typedef uint32_t num_tier_t;
typedef uint32_t num_pulse_t;
typedef uint32_t dbg_consec_t;

#define BJ_INVALID_NUM_NODE ((num_nod_t)(-1))
#define BJ_INVALID_NUM_SYNAPSE ((num_syn_t)(~((num_syn_t)0x0)))
#define BJ_INVALID_NUM_TIER ((num_tier_t)(~((num_tier_t)0x0)))


#define BJ_LAST_TIER (BJ_INVALID_NUM_TIER - 1)

#define BJ_MAX_NODE_SZ mc_maxof(num_syn_t)

#define MAGIC_VAL 987654

enum node_kind_t : uint8_t {
	nd_invalid = 0,
	nd_pos,
	nd_neg,
	nd_neu
};

#define bj_is_pol(ki) ((ki == nd_pos) || (ki == nd_neg))


#endif		// SOLVER_H


