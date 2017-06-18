

/*------------------------------------------------------------

binder.h

binder class and related.

--------------------------------------------------------------*/

#ifndef BINDER_H
#define BINDER_H

#include "shared.h"

//define BINDER_CK(prm) 	DBG_CK(prm)
#define BINDER_CK(prm) EMU_CK(prm)

//=================================================================
// binder

class binder;

typedef binder* bjk_sptr_t;
//define bjk_pt_to_binderpt(pt) (pt)
//define bjk_binderpt_to_pt(bptr) (bptr)

class mc_aligned binder {
public:
	bjk_sptr_t	bn_left;
	bjk_sptr_t	bn_right;

	binder(){
		init_binder();
	}

	~binder(){
	}

	mc_opt_sz_fn
	void		init_binder(){
		bn_left = this;
		bn_right = this;
	}

	mc_opt_sz_fn
	bool	is_alone(){
		return ((bn_left == this) && (bn_right == this));
	}

	mc_opt_sz_fn //virtual // mem expensive
	void	let_go(){
		bn_left->bn_right = bn_right;
		bn_right->bn_left = bn_left;
		bn_left = this;
		bn_right = this;
	}

	mc_opt_sz_fn
	bool	ck_binder(){
		BINDER_CK(bn_right->bn_left == this);
		BINDER_CK(bn_left->bn_right == this);
		return true;
	}

	mc_opt_sz_fn
	binder&	get_right(){
		return *bn_right;
	}

	mc_opt_sz_fn
	binder&	get_left(){
		return *bn_left;
	}

	mc_opt_sz_fn
	binder*	get_right_pt(){
		return bn_right;
	}

	mc_opt_sz_fn
	binder*	get_left_pt(){
		return bn_left;
	}

	mc_opt_sz_fn
	void	bind_to_my_right(binder& the_rgt){
		BINDER_CK(the_rgt.is_alone());
		BINDER_CK(ck_binder());

		the_rgt.bn_right = bn_right;
		the_rgt.bn_left = this;
		bn_right->bn_left = &the_rgt;
		bn_right = &the_rgt;

		BINDER_CK(the_rgt.ck_binder());
		BINDER_CK(ck_binder());
	}

	mc_opt_sz_fn
	void	bind_to_my_left(binder& the_lft){
		BINDER_CK(the_lft.is_alone());
		BINDER_CK(ck_binder());

		the_lft.bn_left = bn_left;
		the_lft.bn_right = this;
		bn_left->bn_right = &the_lft;
		bn_left = &the_lft;

		BINDER_CK(the_lft.ck_binder());
		BINDER_CK(ck_binder());
	}

	mc_opt_sz_fn
	bool	is_single(){
		return (! is_alone() && (bn_left == bn_right));
	}

	mc_opt_sz_fn
	bool	is_multiple(){
		return (! is_alone() && ! is_single());
	}

	mc_opt_sz_fn
	void	move_all_to_my_right(binder& grp){
		if(grp.is_alone()){
			return;
		}

		BINDER_CK(ck_binder());

		binder* new_rgt = grp.bn_right;
		binder* new_mid = grp.bn_left;
		binder* old_rgt = bn_right;

		grp.bn_right = &grp;
		grp.bn_left = &grp;

		bn_right = new_rgt;
		bn_right->bn_left = this;

		new_mid->bn_right = old_rgt;
		new_mid->bn_right->bn_left = new_mid;

		BINDER_CK(grp.is_alone());
		BINDER_CK(new_rgt->ck_binder());
		BINDER_CK(new_mid->ck_binder());
		BINDER_CK(old_rgt->ck_binder());
		BINDER_CK(ck_binder());
	}

	mc_opt_sz_fn
	void	move_all_to_my_left(binder& grp){
		if(grp.is_alone()){
			return;
		}

		BINDER_CK(ck_binder());

		binder* new_lft = grp.bn_left;
		binder* new_mid = grp.bn_right;
		binder* old_lft = bn_left;

		grp.bn_right = &grp;
		grp.bn_left = &grp;

		bn_left = new_lft;
		bn_left->bn_right = this;

		new_mid->bn_left = old_lft;
		new_mid->bn_left->bn_right = new_mid;

		BINDER_CK(grp.is_alone());
		BINDER_CK(new_lft->ck_binder());
		BINDER_CK(new_mid->ck_binder());
		BINDER_CK(old_lft->ck_binder());
		BINDER_CK(ck_binder());
	}

	mc_opt_sz_fn
	void 	let_all_go(){
		while(! is_alone()){
			bn_right->let_go();
		}
	}

	mc_size_t	calc_size() mc_external_code_ram;
};

typedef binder grip;

#ifdef __cplusplus
mc_c_decl {
#endif

#ifdef __cplusplus
}
#endif


#endif		// BINDER_H


/*
	host_binder() mc_external_code_ram;
	~host_binder() mc_external_code_ram;
	void	init_host_binder() mc_external_code_ram;
	bool	is_alone() mc_external_code_ram;
	void	let_go() mc_external_code_ram;
	bool	ck_binder() mc_external_code_ram;
	binder&	get_right() mc_external_code_ram;
	binder&	get_left() mc_external_code_ram;
	binder*	get_right_pt() mc_external_code_ram;
	binder*	get_left_pt() mc_external_code_ram;
	void	bind_to_my_right(binder& the_rgt) mc_external_code_ram;
	void	bind_to_my_left(binder& the_lft) mc_external_code_ram;
	bool	is_single() mc_external_code_ram;
	bool	is_multiple() mc_external_code_ram;
	void	move_all_to_my_right(binder& grp) mc_external_code_ram;
	void	move_all_to_my_left(binder& grp) mc_external_code_ram;
	void 	let_all_go() mc_external_code_ram;
*/
