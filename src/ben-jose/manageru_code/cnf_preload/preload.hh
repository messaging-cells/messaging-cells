

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

preload.hh

Declaration of functions to preload cnfs in dimacs files.

--------------------------------------------------------------*/

#ifndef PRELOAD_CNF_H
#define PRELOAD_CNF_H

#include "cell.hh"
#include "solver.hh"

class pre_sornode;
class pre_cnf_node;
class pre_cnf_net;
class pre_load_cnf;

extern grip ava_pre_sornode;
extern grip ava_pre_cnf_node;
extern grip ava_pre_cnf_net;

typedef unsigned long pre_node_sz_t;

enum sornod_kind_t : uint8_t {
	snod_invalid,
	snod_half,
	snod_alte
};

enum connect_kind_t : uint8_t {
	conn_invalid,
	conn_up,
	conn_down
};

struct mc_aligned sornet_prms {
public:
	num_nod_t tot_nods = 0;
	pre_sornode** arr_nods = mc_null;

	num_nod_t tot_lvs = 0;
	mc_workeru_nn_t* arr_lvs = mc_null;

	num_nod_t curr_nod_id = 0;
};

/*! \class pre_sornode
\brief Class for sornet nodes to load.

*/
class mc_aligned pre_sornode : public agent_grp {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(pre_sornode, bj_load_cod)

	num_nod_t	 	nod_id;
	num_nod_t 		level;

	mc_workeru_nn_t	nod_nn;

	num_nod_t 		up_idx;
	connect_kind_t	up_conn;
	pre_sornode* 	out_up;

	num_nod_t 		down_idx;
	connect_kind_t	down_conn;
	pre_sornode* 	out_down;

	void* 			loaded;

	pre_sornode(){
		nod_id = 0;
		level = 0;

		nod_nn = MC_INVALID_WORKERU_NN;

		up_idx = 0;
		up_conn = conn_invalid;
		out_up = mc_null;

		down_idx = 0;
		down_conn = conn_invalid;
		out_down = mc_null;

		loaded = mc_null;
	}

	~pre_sornode(){}

	connect_kind_t	get_conn_kind(num_nod_t conn_idx){
		if(conn_idx == up_idx){ return conn_up; }
		if(conn_idx == down_idx){ return conn_down; }
		PTD_CK(false);
		return conn_invalid;
	}
};

/*! \class pre_cnf_node
\brief Class for neurons and polarons to load. All refs are in all_agts (inherited from agent_grp).

*/
class mc_aligned pre_cnf_node : public agent_grp {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(pre_cnf_node, bj_load_cod)
	
	node_kind_t 	ki;
	long			id;
	pre_node_sz_t	pre_sz;
	pre_cnf_node* 	opp_nod;
	void* 			loaded;

	pre_cnf_node(){
		ki = nd_invalid;
		id = 0;
		pre_sz = 0;
		opp_nod = mc_null;
		loaded = mc_null;
	}

	~pre_cnf_node(){}
};

/*! \class pre_cnf_net
\brief Class per workeru cnf section to load in workeru. 

*/
class mc_aligned pre_cnf_net : public agent_grp {
public:
	MCK_DECLARE_MEM_METHODS_AND_GET_AVA(pre_cnf_net, bj_load_cod)

	num_nod_t tot_pre_neus;
	num_nod_t tot_pre_vars;
	num_nod_t tot_pre_lits;
	num_nod_t tot_pre_rels;

	grip	all_pre_neu;
	grip	all_pre_pos;
	grip	all_pre_neg;

	// sornet info

	num_nod_t tot_pre_sornods;
	grip	all_pre_sornods;

	num_nod_t tmp_nod_idx;

	/*
	num_nod_t tot_pre_sorinput_nod;
	pre_sornode**	all_pre_sorinput_nod;
	
	num_nod_t tot_pre_sorinput_pol;
	pre_sornode**	all_pre_sorinput_pol;

	num_nod_t tot_pre_sorinput_neu;
	pre_sornode**	all_pre_sorinput_neu;	
	*/
	
	pre_cnf_net(){
		tot_pre_neus = 0;
		tot_pre_vars = 0;
		tot_pre_lits = 0;
		tot_pre_rels = 0;

		// sornet info
		tot_pre_sornods = 0;

		tmp_nod_idx = 0;

		/*
		tot_pre_sorinput_nod = 0;
		all_pre_sorinput_nod = mc_null;
		tot_pre_sorinput_pol = 0;
		all_pre_sorinput_pol = mc_null;
		tot_pre_sorinput_neu = 0;
		all_pre_sorinput_neu = mc_null;
		*/
	}

	~pre_cnf_net(){}
};

typedef int (*cmp_fn)(const void *, const void *);

/*! \class pre_load_cnf
\brief Class full cnf to load in workerus. 

*/
class mc_aligned pre_load_cnf {
public:
	long MAGIC;

	unsigned long max_nod_sz;

	num_nod_t tot_ccls;
	num_nod_t tot_vars;
	num_nod_t tot_lits;

	pre_cnf_node**	all_ccl;
	pre_cnf_node**	all_pos;
	pre_cnf_node**	all_neg;

	num_nod_t tot_tmp_pre_load_nods;
	pre_cnf_node**	all_tmp_pre_load_nods;

	num_nod_t tot_pre_sorinput_nod;
	pre_sornode**	all_pre_sorinput_nod;

	long tot_workerus;
	pre_cnf_net*		all_cnf;	//!< Array of \ref pre_cnf_net s to load in each workeru.

	pre_load_cnf(){
		MAGIC = MAGIC_VAL;

		max_nod_sz = 0;

		tot_ccls = 0;
		tot_vars = 0;
		tot_lits = 0;

		all_ccl = mc_null;
		all_pos = mc_null;
		all_neg = mc_null;

		tot_tmp_pre_load_nods = 0;
		all_tmp_pre_load_nods = mc_null;

		tot_pre_sorinput_nod = 0;
		all_pre_sorinput_nod = mc_null;

		tot_workerus = 0;
		all_cnf = mc_null;
	}

	~pre_load_cnf(){}
};

extern pre_load_cnf* THE_CNF;

void preload_cnf(long sz, const long* arr);

void manageru_print_nods();

void print_cnf();
void print_pre_cnf_nets();

num_nod_t
get_bigger_pow2(num_nod_t nn);

num_nod_t
get_tot_levels(num_nod_t nn);

void
create_sornet(num_nod_t num_to_sort);


#endif		// PRELOAD_CNF_H


