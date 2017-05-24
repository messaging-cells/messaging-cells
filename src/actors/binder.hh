

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

/*
class bj_aligned epiphany_binder {
public:
	uint16_t	bn_left;
	uint16_t	bn_right;
};

class bj_aligned host_binder {
public:
	binder*	bn_left;
	binder*	bn_right;
};

#ifdef BJ_IS_EPH_CODE
	typedef uint16_t bjk_sptr_t;
	#define bjk_pt_to_binderpt(pt) ((binder*)(bj_addr_t)(pt))
	#define bjk_binderpt_to_pt(bptr) ((uintptr_t)(bptr))
	#define bj_binder_base epiphany_binder
#else
	typedef binder* bjk_sptr_t;
	#define bjk_pt_to_binderpt(pt) (pt)
	#define bjk_binderpt_to_pt(bptr) (bptr)
	#define bj_binder_base host_binder
#endif

//class bj_aligned binder : public bj_binder_base {
//class binder {
*/

typedef binder* bjk_sptr_t;
#define bjk_pt_to_binderpt(pt) (pt)
#define bjk_binderpt_to_pt(bptr) (bptr)

class bj_aligned binder {
public:
	bjk_sptr_t	bn_left;
	bjk_sptr_t	bn_right;

	binder(){
		init_binder();
	}

	~binder(){
	}

	bj_opt_sz_fn
	void		init_binder(){
		bn_left = bjk_binderpt_to_pt(this);
		bn_right = bjk_binderpt_to_pt(this);
	}

	bj_opt_sz_fn
	bool	is_alone(){
		return ((bn_left == bjk_binderpt_to_pt(this)) && (bn_right == bjk_binderpt_to_pt(this)));
	}

	bj_opt_sz_fn //virtual // mem expensive
	void	let_go(){
		bjk_pt_to_binderpt(bn_left)->bn_right = bn_right;
		bjk_pt_to_binderpt(bn_right)->bn_left = bn_left;
		bn_left = bjk_binderpt_to_pt(this);
		bn_right = bjk_binderpt_to_pt(this);
	}

	bj_opt_sz_fn
	bool	ck_binder(){
		BINDER_CK(bn_right->bn_left == bjk_binderpt_to_pt(this));
		BINDER_CK(bn_left->bn_right == bjk_binderpt_to_pt(this));
		return true;
	}

	bj_opt_sz_fn
	binder&	get_right(){
		return *bjk_pt_to_binderpt(bn_right);
	}

	bj_opt_sz_fn
	binder&	get_left(){
		return *bjk_pt_to_binderpt(bn_left);
	}

	bj_opt_sz_fn
	binder*	get_right_pt(){
		return bjk_pt_to_binderpt(bn_right);
	}

	bj_opt_sz_fn
	binder*	get_left_pt(){
		return bjk_pt_to_binderpt(bn_left);
	}

	bj_opt_sz_fn
	void	bind_to_my_right(binder& the_rgt){
		BINDER_CK(the_rgt.is_alone());
		BINDER_CK(ck_binder());

		the_rgt.bn_right = bn_right;
		the_rgt.bn_left = bjk_binderpt_to_pt(this);
		bjk_pt_to_binderpt(bn_right)->bn_left = bjk_binderpt_to_pt(&the_rgt);
		bn_right = bjk_binderpt_to_pt(&the_rgt);

		BINDER_CK(the_rgt.ck_binder());
		BINDER_CK(ck_binder());
	}

	bj_opt_sz_fn
	void	bind_to_my_left(binder& the_lft){
		BINDER_CK(the_lft.is_alone());
		BINDER_CK(ck_binder());

		the_lft.bn_left = bn_left;
		the_lft.bn_right = bjk_binderpt_to_pt(this);
		bjk_pt_to_binderpt(bn_left)->bn_right = bjk_binderpt_to_pt(&the_lft);
		bn_left = bjk_binderpt_to_pt(&the_lft);

		BINDER_CK(the_lft.ck_binder());
		BINDER_CK(ck_binder());
	}

	bj_opt_sz_fn
	bool	is_single(){
		return (! is_alone() && (bn_left == bn_right));
	}

	bj_opt_sz_fn
	bool	is_multiple(){
		return (! is_alone() && ! is_single());
	}

	bj_opt_sz_fn
	void	move_all_to_my_right(binder& grp){
		if(grp.is_alone()){
			return;
		}

		BINDER_CK(ck_binder());

		binder* new_rgt = bjk_pt_to_binderpt(grp.bn_right);
		binder* new_mid = bjk_pt_to_binderpt(grp.bn_left);
		binder* old_rgt = bjk_pt_to_binderpt(bn_right);

		grp.bn_right = bjk_binderpt_to_pt(&grp);
		grp.bn_left = bjk_binderpt_to_pt(&grp);

		bn_right = bjk_binderpt_to_pt(new_rgt);
		bjk_pt_to_binderpt(bn_right)->bn_left = bjk_binderpt_to_pt(this);

		new_mid->bn_right = bjk_binderpt_to_pt(old_rgt);
		bjk_pt_to_binderpt(new_mid->bn_right)->bn_left = bjk_binderpt_to_pt(new_mid);

		BINDER_CK(grp.is_alone());
		BINDER_CK(new_rgt->ck_binder());
		BINDER_CK(new_mid->ck_binder());
		BINDER_CK(old_rgt->ck_binder());
		BINDER_CK(ck_binder());
	}

	bj_opt_sz_fn
	void	move_all_to_my_left(binder& grp){
		if(grp.is_alone()){
			return;
		}

		BINDER_CK(ck_binder());

		binder* new_lft = bjk_pt_to_binderpt(grp.bn_left);
		binder* new_mid = bjk_pt_to_binderpt(grp.bn_right);
		binder* old_lft = bjk_pt_to_binderpt(bn_left);

		grp.bn_right = bjk_binderpt_to_pt(&grp);
		grp.bn_left = bjk_binderpt_to_pt(&grp);

		bn_left = bjk_binderpt_to_pt(new_lft);
		bjk_pt_to_binderpt(bn_left)->bn_right = bjk_binderpt_to_pt(this);

		new_mid->bn_left = bjk_binderpt_to_pt(old_lft);
		bjk_pt_to_binderpt(new_mid->bn_left)->bn_right = bjk_binderpt_to_pt(new_mid);

		BINDER_CK(grp.is_alone());
		BINDER_CK(new_lft->ck_binder());
		BINDER_CK(new_mid->ck_binder());
		BINDER_CK(old_lft->ck_binder());
		BINDER_CK(ck_binder());
	}

	bj_opt_sz_fn
	void 	let_all_go(){
		while(! is_alone()){
			bjk_pt_to_binderpt(bn_right)->let_go();
		}
	}
};

typedef binder grip;

#ifdef __cplusplus
bj_c_decl {
#endif

#ifdef __cplusplus
}
#endif


#endif		// BINDER_H


/*
	host_binder() bj_external_code_ram;
	~host_binder() bj_external_code_ram;
	void	init_host_binder() bj_external_code_ram;
	bool	is_alone() bj_external_code_ram;
	void	let_go() bj_external_code_ram;
	bool	ck_binder() bj_external_code_ram;
	binder&	get_right() bj_external_code_ram;
	binder&	get_left() bj_external_code_ram;
	binder*	get_right_pt() bj_external_code_ram;
	binder*	get_left_pt() bj_external_code_ram;
	void	bind_to_my_right(binder& the_rgt) bj_external_code_ram;
	void	bind_to_my_left(binder& the_lft) bj_external_code_ram;
	bool	is_single() bj_external_code_ram;
	bool	is_multiple() bj_external_code_ram;
	void	move_all_to_my_right(binder& grp) bj_external_code_ram;
	void	move_all_to_my_left(binder& grp) bj_external_code_ram;
	void 	let_all_go() bj_external_code_ram;
*/
