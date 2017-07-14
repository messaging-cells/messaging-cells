

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

class pre_cnf_node;

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

class mc_aligned nervenode : public agent_grp {
public:
	node_kind_t 	ki;
	long			id;
	long			sz;

	nervenode() bj_load_cod;
	~nervenode() bj_load_cod;

	void init_with(pre_cnf_node* nod) bj_load_cod;
};

class mc_aligned neupole : public nervenode {
public:
	MCK_DECLARE_MEM_METHODS(neupole, bj_load_cod)
	
	neupole*		opp;

	neupole() bj_load_cod;
	~neupole() bj_load_cod;

};

class mc_aligned neuron : public nervenode {
public:
	MCK_DECLARE_MEM_METHODS(neuron, bj_load_cod)
	
	neuron() bj_load_cod;
	~neuron() bj_load_cod;
};

#define MAGIC_VAL 987654

class mc_aligned nervenet {
public:
	MCK_DECLARE_MEM_METHODS(nervenet, bj_load_cod)

	long MAGIC;

	grip		ava_neupoles;
	grip		ava_neurons;
	nervenet*	shd_cnf;

	long tot_neus;
	long tot_vars;
	long tot_lits;
	long tot_rels;

	grip	all_neu;
	grip	all_pos;
	grip	all_neg;

	nervenet() bj_load_cod;
	~nervenet() bj_load_cod;
};

void bj_load_main() bj_load_cod;

#define bj_nervenet ((nervenet*)(kernel::get_sys()->user_data))
#define bj_ava_neupoles (bj_nervenet->ava_neupoles)
#define bj_ava_neurons (bj_nervenet->ava_neurons)

#define BJ_DEFINE_nervenet_methods() \
nervenet::nervenet(){ \
		MAGIC = MAGIC_VAL; \
\
		shd_cnf = mc_null; \
\
		tot_neus = 0; \
		tot_vars = 0; \
		tot_lits = 0; \
		tot_rels = 0; \
	} \
\
nervenet::~nervenet(){} \

// end of BJ_DEFINE_LOAD_CNF_FUNCS

void bj_load_poles(grip& all_pol) bj_load_cod;
void bj_load_shd_cnf() bj_load_cod;
void bj_print_loaded_poles(grip& all_pol, node_kind_t ki) mc_external_code_ram;
void bj_print_loaded_cnf() mc_external_code_ram;

#endif		// LOAD_CNF_H


