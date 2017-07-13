

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

preload_cnf.hh

Declaration of functions to preload cnfs in dimacs files.

--------------------------------------------------------------*/

#ifndef PRELOAD_CNF_H
#define PRELOAD_CNF_H

#include "cell.hh"

#include "load_cnf.hh"

class pre_cnf_node;
class pre_load_cnf;

extern grip ava_pre_cnf_node;

class mc_aligned pre_cnf_node : public cnf_node {
public:
	MCK_DECLARE_MEM_METHODS(pre_cnf_node, bj_load_cod)
	
	pre_cnf_node* 	loaded;

	pre_cnf_node(){
		loaded = mc_null;
	}

	~pre_cnf_node(){}

};

typedef int (*cmp_fn)(const void *, const void *);

class mc_aligned pre_load_cnf {
public:
	long MAGIC;

	long tot_ccls;
	long tot_vars;
	long tot_lits;

	pre_cnf_node**	all_ccl;
	pre_cnf_node**	all_pos;
	pre_cnf_node**	all_neg;

	long tot_sort_nods;
	pre_cnf_node**	all_sort_nods;

	long tot_cores;
	core_cnf*		all_cnf;

	pre_load_cnf(){
		MAGIC = MAGIC_VAL;

		tot_ccls = 0;
		tot_vars = 0;
		tot_lits = 0;

		all_ccl = mc_null;
		all_pos = mc_null;
		all_neg = mc_null;

		tot_sort_nods = 0;
		all_sort_nods = mc_null;

		tot_cores = 0;
		all_cnf = mc_null;
	}

	~pre_load_cnf(){}
};

extern pre_load_cnf* THE_CNF;

void preload_cnf(long sz, const long* arr);
void print_cnf();
void print_nods();
void print_core_cnfs();


#endif		// PRELOAD_CNF_H


