

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

load_cnf.hh

Declaration of functions to load cnfs in the core.

--------------------------------------------------------------*/

#ifndef LOAD_CNF_H
#define LOAD_CNF_H

#include "cell.hh"

//define bj_load_cod mc_external_code_ram
//define bj_load_dat mc_external_data_ram

#define bj_load_cod mc_mod1_cod
#define bj_load_dat mc_mod1_dat

enum node_kind_t : uint8_t {
	nd_invalid = 0,
	nd_pos,
	nd_neg,
	nd_ccl
};

class mc_aligned cnf_node : public agent_grp {
public:
	MCK_DECLARE_MEM_METHODS(cnf_node, bj_load_cod)
	
	node_kind_t 	ki;
	long			id;
	long			sz;

	cnf_node() bj_load_cod;
	~cnf_node() bj_load_cod;

};

#define MAGIC_VAL 987654

class mc_aligned core_cnf {
public:
	MCK_DECLARE_MEM_METHODS(core_cnf, bj_load_cod)

	long MAGIC;

	grip		ava_cnf_node;
	core_cnf*	shd_cnf;

	long tot_ccls;
	long tot_vars;
	long tot_lits;
	long tot_rels;

	grip	all_ccl;
	grip	all_pos;
	grip	all_neg;

	core_cnf();
	~core_cnf();
};

void bj_load_main() bj_load_cod;

#define bj_core_cnf ((core_cnf*)(kernel::get_sys()->user_data))
#define bj_ava_cnf_nodes (bj_core_cnf->ava_cnf_node)

#define BJ_DEFINE_LOAD_CNF_FUNCS() \
cnf_node::cnf_node(){ \
		ki = nd_invalid; \
		id = 0; \
		sz = 0; \
	} \
\
cnf_node::~cnf_node(){} \
\
core_cnf::core_cnf(){ \
		MAGIC = MAGIC_VAL; \
\
		shd_cnf = mc_null; \
\
		tot_ccls = 0; \
		tot_vars = 0; \
		tot_lits = 0; \
		tot_rels = 0; \
	} \
\
core_cnf::~core_cnf(){} \

// end of BJ_DEFINE_CNF_NODE_FUNCS


#endif		// LOAD_CNF_H


