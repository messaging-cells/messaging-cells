

/*------------------------------------------------------------

binder.h

binder class and related.

--------------------------------------------------------------*/

#ifndef BINDER_H
#define BINDER_H

#include "kptr.hh"

//define BINDER_CK(prm) 	DBG_CK(prm)
#define BINDER_CK(prm) 	

//=================================================================
// binder

class binder;

extern const uint8_t* BINDER_BASE_POINTER;

typedef kptr<binder, BINDER_BASE_POINTER> bjk_pt_t;

typedef uint8_t bjk_flags_t;

class binder {
public:
	bjk_pt_t	bn_left;
	bjk_pt_t	bn_right;

	binder(){
		init_binder();
	}

	~binder(){
	}

	bj_opt_sz_fn
	void		init_binder(){
		bn_left = this;
		bn_right = this;
	}

	bj_opt_sz_fn
	bool	is_alone(){
		return ((bn_left == this) && (bn_right == this));
	}

	bj_opt_sz_fn //virtual // mem expensive
	void	let_go(){
		bn_left->bn_right = bn_right;
		bn_right->bn_left = bn_left;
		bn_left = this;
		bn_right = this;
	}

	bool	ck_binder(){
		BINDER_CK(bn_right->bn_left == this);
		BINDER_CK(bn_left->bn_right == this);
		return true;
	}

	bj_opt_sz_fn
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

	bj_opt_sz_fn
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

	bj_opt_sz_fn
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

	bj_opt_sz_fn
	void 	let_all_go(){
		while(! is_alone()){
			bn_right->let_go();
		}
	}

};

typedef binder grip;

//=================================================================
// receptor

template<class obj_t1>
class receptor : public binder {
public:
	obj_t1*		re_me;
	//kptr<obj_t1>	re_me;

	receptor(){
		init_receptor();
	}

	~receptor(){
	}

	void	init_receptor(){
		re_me = bj_null;
	}

	receptor(obj_t1& tgt){
		re_me = &tgt;
	}

	receptor(obj_t1* tgt){
		re_me = tgt;
	}

	operator obj_t1* () {
		return re_me;
	}

	operator obj_t1& () {
		BINDER_CK(re_me != bj_null);
		return *re_me;
	}
};

//=================================================================
// TEMPLATE DEFS

template<class obj_t1>
obj_t1&
rcp_as(binder* bdr){
	BINDER_CK(bdr != bj_null);

	receptor<obj_t1>& rcp = *((receptor<obj_t1>*)(bdr));
	BINDER_CK(rcp.re_me != bj_null);

	obj_t1& obj_1 = rcp;
	return obj_1;
}

/*
template<class obj_t1>
void
grip::append_all_as(row<obj_t1*>& rr, bool clr){
	if(clr){
		rr.clear();
	}

	binder* fst_bdr = bn_right;
	binder* lst_bdr = this;
	for(binder* bdr_1 = fst_bdr; bdr_1 != lst_bdr; bdr_1 = bdr_1->bn_right){
		obj_t1& ob_1 = rcp_as<obj_t1>(bdr_1);
		rr.push(&ob_1);
	}
}

*/

//================================================================
// bind_iter

class bind_iter {
public:
	grip& 	the_grip;
	binder*	the_ref;

	bind_iter(grip& gp) : the_grip(gp){
		the_ref = &the_grip;
	}
	bind_iter(bind_iter& bn_it): the_grip(bn_it.the_grip){
		the_ref = &the_grip;
	}
	~bind_iter(){
	}

	void	go_first_right(){
		the_ref = the_grip.bn_right;
	}

	void	go_first_left(){
		the_ref = the_grip.bn_left;
	}

	binder&	get_binder(){
		return *the_ref;
	}

	template<class obj_t>
	obj_t&
	get(){
		obj_t* obj = (obj_t*)the_ref;
		return *obj;
	}
	
	bool 	in_last(){
		return (the_ref == &the_grip);
	}

	void	go_left(){
		the_ref = the_ref->bn_left;
	}

	void	go_right(){
		the_ref = the_ref->bn_right;
	}

	binder* 	get_ref(){
		return the_ref;
	}

	void 	operator ++ (){
		go_right();
	}

	void 	operator -- (){
		go_left();
	}

	void 	operator ++ (int aa) { ++(*this); }

	void 	operator -- (int aa) { --(*this); }
};

/*
#pragma GCC diagnostic push
#pragma GCC diagnostic warning "-fpermissive"

static void
__static_initialization_and_destruction_0(int, int) bj_code_dram;

#pragma GCC diagnostic pop
*/

#endif		// BINDER_H


