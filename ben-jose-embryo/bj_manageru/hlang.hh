

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

hlang.hh

hlang declarations.

--------------------------------------------------------------*/

#ifndef HLANG_H
#define HLANG_H

#include <type_traits>
#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
#include <list>

//include "tools.h"
#include "stack_trace.h"
#include "nervenet.hh"
//include "booter.h"
#include "cell.hh"

typedef int64_t hc_chip_idx;

class hc_term;
class hc_mth_def;
class hcell;

typedef void (*hc_caller_t)();

struct hclass_reg {
	std::string nam;
	std::map<std::string, hc_term*> attributes;
	std::list<hc_mth_def*> methods;
	hc_caller_t initer = mc_null;

	bool has_attribute(const char* attr);
	
	void call_all_methods();
};

class hlang_sys {
public:
	std::map<std::string, hclass_reg*> all_classes;

	hlang_sys(){
		init_me();
	}

	virtual ~hlang_sys(){}
	
	hclass_reg* get_class_reg(const char* cls, hc_caller_t the_initer = mc_null);
	void register_method(const char* cls, hc_mth_def* mth);
	void register_attribute(hcell* obj, hc_term* attr);
	
	void init_all_attributes();
	void call_all_registered_methods();

	virtual
	void init_me(int caller = 0){
	}
	
};

extern hlang_sys HC_THE_HLANG_SYS;

template <bool> struct HC_ILLEGAL_USE_OF_OBJECT;
template <> struct HC_ILLEGAL_USE_OF_OBJECT<true>{};
#define HC_OBJECT_COPY_ERROR HC_ILLEGAL_USE_OF_OBJECT<false>()

#define hc_xstr(a) hc_str(a)
#define hc_str(a) #a

// ~,|,&,^,==, >>, <<, >, <,?,

enum	hc_syntax_op_t {
	hc_invalid_op,
	
	hc_member_op,	// ->
	
	hc_comma_op,	// ,
	hc_switch_then_op,	// >>=
	hc_then_op,	// >>
	
	hc_hme_op,	// hme
	hc_hif_op,	// hif
	hc_helse_op,	// helse
	hc_helif_op,	// helif
	hc_hfor_op,	// hfor
	hc_hwhile_op,	// hwhile
	hc_hswitch_op,	// hswitch
	hc_hcase_op,	// hcase
	hc_hbreak_op,	// hbreak
	hc_hcontinue_op,	// hcontinue
	hc_hreturn_op,	// hreturn
	
	hc_assig_op1,	// =
	hc_assig_op2,	// =
	hc_assig_op3,	// =
	hc_assig_op4,	// =
	hc_assig_op5,	// =
	
	hc_less_than_op,	// <
	hc_more_than_op,	// >
	hc_less_equal_than_op,	// <=
	hc_more_equal_than_op,	// >=
	hc_equal_op,	// ==
	hc_not_equal_op,	// !=
	hc_and_op,	// &&
	hc_or_op,	// ||
	hc_bit_and_op,	// &
	hc_bit_or_op,	// |
	
	hc_not_op,	// !
	hc_bit_not_op,	// ~

	hc_plus_op,	// +
	hc_minus_op,	// -
	
	hc_pre_inc_op,	// ++
	hc_pre_dec_op,	// --
	hc_post_inc_op,	// ++
	hc_post_dec_op,	// --
	
	hc_total_num_op
};

const char*
hc_get_token(hc_syntax_op_t op);

enum	hc_term_kind_t {
	hc_invalid_kind,
	hc_value_kind,
	hc_reference_kind,
	hc_call_kind,
	hc_unary_kind,
	hc_binary_kind
};


#define HC_DEFINE_BINARY_OP_BASE(the_code) \
	hc_term* tm = new hc_binary_term(the_code, this, &o1); \
	return *tm; \

// end_define

#define HC_DEFINE_BINARY_OP(the_op, the_code) \
hc_term& hc_term::operator the_op (hc_term& o1) { \
	HC_DEFINE_BINARY_OP_BASE(the_code) \
} \

// end_define

#define HC_DEFINE_UNARY_OP_BASE(the_code) \
	hc_term* tm = new hc_unary_term(the_code, this); \

// end_define

#define HC_DEFINE_UNARY_OP(the_op, the_code) \
hc_term& hc_term::operator the_op (){ \
	HC_DEFINE_UNARY_OP_BASE(the_code) \
	return *tm; \
} \

// end_define

#define HC_DEFINE_FUNC_OP(the_op, the_code) \
hc_term& \
the_op(hc_term& o1){ \
	hc_term* tm = new hc_unary_term(the_code, &o1); \
	return *tm; \
} \

// end_define


class hc_term {
public:
	static hc_term	HC_NULL_TERM;
	
	// constructors
	hc_term(){}

	virtual	~hc_term(){
		//printf("%s \n", STACK_STR.c_str());
		//bj_abort_func(0, "func: 'hc_term::~hc_term'"); 
	}

	// Don't allow copying (error prone):
	// force use of referenced rows
	
	hc_term(hc_term& other){ 
		mch_abort_func(0, mc_cstr("func: 'hc_term(hc_term&)' \n"));
		//mck_abort(0, mc_cstr("func: 'hc_term(hc_term&)' \n"));
		//HC_OBJECT_COPY_ERROR;
	}

	hc_term&  operator , (hc_term& o1);
	hc_term&	operator >>= (hc_term& o1);
	hc_term&	operator >> (hc_term& o1);
	
	hc_term&	operator = (hc_term& o1);
	
	hc_term&	operator < (hc_term& o1);
	hc_term&	operator > (hc_term& o1);
	hc_term&	operator <= (hc_term& o1);
	hc_term&	operator >= (hc_term& o1);
	hc_term&	operator == (hc_term& o1);
	hc_term&	operator != (hc_term& o1);
	hc_term&	operator && (hc_term& o1);
	hc_term&	operator || (hc_term& o1);
	hc_term&	operator & (hc_term& o1);
	hc_term&	operator | (hc_term& o1);

	hc_term&	operator + (hc_term& o1);
	hc_term&	operator - (hc_term& o1);

	hc_term&	operator ! ();
	hc_term&	operator ~ ();
	
	hc_term&	operator ++ ();
	hc_term&	operator ++ (int xx);
	hc_term&	operator -- ();
	hc_term&	operator -- (int xx);
	
	virtual 
	hc_term_kind_t	get_term_kind(){
		return hc_invalid_kind;
	}
	
	bool is_null(){
		return (this == &HC_NULL_TERM);
	}
	
	friend
	hc_term&	hif(hc_term& o1);

	friend
	hc_term&	helif(hc_term& o1);

	friend
	hc_term&	hfor(hc_term& o1);

	friend
	hc_term&	hwhile(hc_term& o1);

	friend
	hc_term&	hswitch(hc_term& o1);

	friend
	hc_term&	hcase(hc_term& o1);
	
	friend
	void		hfunction(const char* nam, hc_term& o1);
	
	virtual 
	hc_term*	get_src(){
		return this;
	}
	
	virtual 
	void print_term();

	virtual 
	void print_code(){
		mch_abort_func(0, mc_cstr("Invalid call to 'print_code()'. " 
				"NOT_A_METHOD. It has no code to print.\n"));
	}
	
	bool is_value(){
		return (get_term_kind() == hc_value_kind);
	}

	bool is_reference(){
		return (get_term_kind() == hc_reference_kind);
	}

	bool is_call(){
		return (get_term_kind() == hc_call_kind);
	}

	virtual 
	const char*	get_name(){
		return "INVALID_NAME";
	}
	
	void dbg_func();
};

class hc_unary_term : public hc_term {
public:
	hc_syntax_op_t op;
	hc_term* prm;
	
	virtual	~hc_unary_term(){
		if(prm != mc_null){
			delete prm;
			prm = mc_null;
		}
	}

	hc_unary_term(hc_syntax_op_t pm_op, hc_term* pm_val){
		init_unary_term(pm_op, pm_val);
	}

	void init_unary_term(hc_syntax_op_t pm_op = hc_invalid_op, 
						  hc_term* pm_val = mc_null)
	{
		op = pm_op;
		if(pm_val != mc_null){
			pm_val = pm_val->get_src();
		}
		prm = pm_val;
	}
	
	virtual 
	hc_term_kind_t	get_term_kind(){
		return hc_unary_kind;
	}
	
	virtual 
	const char*	get_name(){
		return hc_get_token(op);
	}
	
	virtual 
	void print_term();
};

class hc_binary_term : public hc_term {
public:
	hc_syntax_op_t op;
	hc_term* lft;
	hc_term* rgt;
	
	virtual	~hc_binary_term(){
		if(lft != mc_null){
			delete lft;
			lft = mc_null;
		}
		if(rgt != mc_null){
			delete rgt;
			rgt = mc_null;
		}
	}
	
	hc_binary_term(hc_syntax_op_t pm_op, hc_term* pm_lft, hc_term* pm_rgt){
		init_binary_term(pm_op, pm_lft, pm_rgt);
	}
	
	void init_binary_term(hc_syntax_op_t pm_op = hc_invalid_op, 
						  hc_term* pm_lft = mc_null, hc_term* pm_rgt = mc_null)
	{
		op = pm_op;
		if(op != hc_member_op){
			if(pm_lft != mc_null){
				pm_lft = pm_lft->get_src();
			}
			if(pm_rgt != mc_null){
				pm_rgt = pm_rgt->get_src();
			}
		}
		lft = pm_lft;
		rgt = pm_rgt;
	}
	
	virtual 
	hc_term_kind_t	get_term_kind(){
		return hc_binary_kind;
	}
	
	virtual 
	const char*	get_name(){
		return hc_get_token(op);
	}
	
	virtual 
	void print_term();
};

template<class obj_t>
class hc_value : public hc_term {
public:
	static hc_value<obj_t>	HC_NULL_VALUE;

	const char* typ;
	const char* nam;
	obj_t	val;
	hcell*	owner;
	
	virtual	~hc_value(){}
	
	hc_value(const char* the_typ, const char* the_nam, hcell* the_owner = mc_null){
		PTD_CK(! std::is_pointer<obj_t>::value);
		PTD_CK(! std::is_class<obj_t>::value);
		typ = the_typ;
		nam = the_nam;
		val = obj_t();
		owner = the_owner;
		if(owner != mc_null){
			HC_THE_HLANG_SYS.register_attribute(owner, this);
		}
		//printf("caller=%s \n", the_caller);
	}
	
	hc_value(hc_value<obj_t>& other){ 
		HC_OBJECT_COPY_ERROR; 
	}

	hc_value(hc_term& other){ 
		HC_OBJECT_COPY_ERROR; 
	}
	
	hc_term&	operator = (hc_term& o1){
		HC_DEFINE_BINARY_OP_BASE(hc_assig_op2);
	}

	hc_term&	operator = (hc_value<obj_t>& o1) { 
		HC_DEFINE_BINARY_OP_BASE(hc_assig_op3);
	}

	void operator ()(obj_t aa) { val = aa; }	// as unary func. used as init func
	hc_term& operator ()() { return *get_src(); }	// as empty func
	
	void  operator = (obj_t aa) { 
		val = aa;
	}

	bool is_null(){
		return (this == &HC_NULL_VALUE);
	}

	//operator obj_t() { return ref; }		// cast op
	 
	virtual 
	hc_term_kind_t	get_term_kind(){
		return hc_value_kind;
	}
	
	virtual 
	const char*	get_name(){
		return nam;
	}
	
	virtual 
	void print_term(){
		std::cout << ' ' << nam << ' ';
		//printf(" VAL ");
	}

	virtual 
	hc_term*	get_src();
};

template<class obj_t>
hc_value<obj_t> hc_value<obj_t>::HC_NULL_VALUE{};

class hc_keyword : public hc_value<hc_syntax_op_t> {
public:
	virtual	~hc_keyword(){}
	
	hc_keyword(const char* the_nam) : hc_value("hc_keyword", the_nam){
	}
		
	virtual 
	void print_term(){
		std::cout << ' ' << nam << ' ';
	}
};

template<class obj_t>
class hc_reference : public hc_term {
public:
	static obj_t*	HC_GLB_REF;
	
	const char* typ;
	const char* nam;
	obj_t*	ref;
	hcell*	owner;
	
	virtual	~hc_reference(){}
	
	hc_reference(const char* the_typ, const char* the_nam, hcell* the_owner = mc_null){
		PTD_CK(! std::is_pointer<obj_t>::value);
		PTD_CK(std::is_class<obj_t>::value);
		//PTD_CK((std::is_base_of<hcell, obj_t>::value));
		typ = the_typ;
		nam = the_nam;
		ref = mc_null;
		owner = the_owner;
		if(owner != mc_null){
			HC_THE_HLANG_SYS.register_attribute(owner, this);
		}
	}
	
	hc_reference(hc_reference<obj_t>& other){ 
		HC_OBJECT_COPY_ERROR; 
	}

	hc_reference(hc_term& other){ 
		HC_OBJECT_COPY_ERROR; 
	}
	
	hc_term&	operator = (hc_term& o1){
		HC_DEFINE_BINARY_OP_BASE(hc_assig_op4);
	}

	hc_term&  operator = (hc_reference<obj_t>& o1) { 
		HC_DEFINE_BINARY_OP_BASE(hc_assig_op5);
	}

	void operator ()(obj_t* aa) { // as unary func. used as init func
		ref = aa; 
	}	
	hc_term& operator ()() { return *get_src(); }	// as empty func. top member calls with this.
	
	void  operator = (obj_t* aa) { 
		ref = aa;
	}
	
	static
	obj_t* get_glb_ref(){
		if(HC_GLB_REF == mc_null){
			HC_GLB_REF = new obj_t();
		}
		return HC_GLB_REF;
	}
	
	obj_t const *	operator -> () const {
		if(ref == mc_null){
			ref = get_glb_ref();
			//ref = new obj_t();
		}
		if(ref->src_term != mc_null){ 
			PTD_PRT("\nCannot have recursive referencing in hlang.\n"); 
		}
		ref->src_term = this;
		return ref;
	}
	
    obj_t*	operator -> () {
		if(ref == mc_null){
			ref = get_glb_ref();
			//ref = new obj_t();
		}
		if(ref->src_term != mc_null){ 
			PTD_PRT("\nCannot have recursive referencing in hlang.\n"); 
		}
		ref->src_term = this;
		return ref;
	}
	
	bool is_null(){
		return (ref == mc_null);
	}

	//operator obj_t() { return ref; }		// cast op
	
	virtual 
	hc_term_kind_t	get_term_kind(){
		return hc_reference_kind;
	}
	
	virtual 
	const char*	get_name(){
		return nam;
	}
	
	virtual 
	void print_term(){
		std::cout << ' ' << nam << ' ';
		//printf(" %p ", ref);
	}

	virtual 
	hc_term*	get_src();
};

template<class obj_t>
obj_t* hc_reference<obj_t>::HC_GLB_REF = mc_null;

class hcell {
public:
	hc_chip_idx		my_id = -1;
	hc_term* src_term = mc_null;
	
	hcell(){
		init_me();
	}

	
	virtual ~hcell(){}

	virtual
	void init_me(int caller = 0){
		src_term = mc_null;
	}
	
    hc_reference<hcell>&	hme(){
		hc_reference<hcell>* pt_me = new hc_reference<hcell>("hcell", "hme", this);
		pt_me->ref = this;
		return *pt_me;
	}

	virtual
	const char* get_class_name(){
		return "hcell";
	}
};

#define hcell_class(cls) \
	static const char* hc_class_name; \
	static hclass_reg* hc_register_ ## cls; \
	virtual	const char* get_class_name();

// end_define

#define hcell_class_def(cls) \
	void cls ## _ref_initer(); \
	hclass_reg* cls::hc_register_ ## cls = HC_THE_HLANG_SYS.get_class_reg(#cls, cls ## _ref_initer); \
	const char* cls::hc_class_name = #cls; \
	const char* \
	cls::get_class_name(){ \
		return cls::hc_class_name; \
	} \
	void cls ## _ref_initer(){ \
		hc_reference<cls>::get_glb_ref(); \
	} \

// end_define

#define HC_GET_SOURCE() \
	hc_term* src = this; \
	if((owner != mc_null) && (owner->src_term != mc_null)){ \
		hc_term* tmp = owner->src_term; \
		owner->src_term = mc_null; \
		tmp = tmp->get_src(); \
		src = new hc_binary_term(hc_member_op, tmp, this); \
	} \
	return src; \

// end_define

template<class obj_t>
hc_term*	
hc_value<obj_t>::get_src(){
	HC_GET_SOURCE();
}

template<class obj_t>
hc_term*	
hc_reference<obj_t>::get_src(){
	HC_GET_SOURCE();
}

template<class cl1_t, class cl2_t>
cl2_t*
hcast(hc_reference<cl1_t>& o1){
	return (cl2_t*)(o1.ref);
}

//define hglb_pt_nam(nn) nn ## _global_pt

#define hkeyword(nn) hc_keyword nn(#nn)

#define hvalue(tt, nn) hc_value<tt> nn{#tt, #nn, this}

#define hreference(tt, nn) hc_reference<tt> nn{#tt, #nn, this}

#define hchar(nn) hvalue(char, nn)
#define hint(nn) hvalue(int, nn)
#define hlong(nn) hvalue(long, nn)
#define hint8_t(nn) hvalue(int8_t, nn)
#define hint16_t(nn) hvalue(int16_t, nn)
#define hint32_t(nn) hvalue(int32_t, nn)
#define hint64_t(nn) hvalue(int64_t, nn)
#define huint8_t(nn) hvalue(uint8_t, nn)
#define huint16_t(nn) hvalue(uint16_t, nn)
#define huint32_t(nn) hvalue(uint32_t, nn)
#define huint64_t(nn) hvalue(uint64_t, nn)

extern hc_keyword helse;
extern hc_keyword hbreak;
extern hc_keyword hcontinue;
extern hc_keyword hreturn;

//void
//hc_init_keywords();

class hc_mth_def : public hc_term {
public:
	const char* cls = mc_null;
	const char* nam = mc_null;
	hc_term* cod = mc_null;
	bool defining = false;
	hc_caller_t caller = mc_null;
	
	virtual	~hc_mth_def(){}
	
	hc_mth_def(const char* the_cls, const char* the_nam, hc_caller_t the_cllr = mc_null){
		cls = the_cls;
		nam = the_nam;
		caller = the_cllr;
		HC_THE_HLANG_SYS.register_method(the_cls, this);
	}

	virtual 
	hc_term_kind_t	get_term_kind(){
		return hc_call_kind;
	}
	
	virtual 
	const char*	get_name(){
		return nam;
	}
	
	virtual 
	void print_term(){
		std::cout << ' ' << get_name() << "() ";
	}

	virtual 
	void print_code(){
		printf("\nCODE_FOR %s\n", get_name());
		if(cod == mc_null){
			printf("EMPTY_COD for mth\n");
		} else {
			cod->print_term();
			printf("\n");
		}
	}
	
};

class hc_mth_call : public hc_term {
public:
	hc_mth_def* the_mth = mc_null;
	
	virtual	~hc_mth_call(){}
	
	hc_mth_call(hc_mth_def* mthdef){
		PTD_CK(mthdef != mc_null);
		the_mth = mthdef;
	}

	virtual 
	hc_term_kind_t	get_term_kind(){
		return hc_call_kind;
	}
	
	virtual 
	const char*	get_name(){
		PTD_CK(the_mth != mc_null);
		return the_mth->get_name();
	}
	
	virtual 
	void print_term(){
		std::cout << ' ' << get_name() << "() ";
	}

	virtual 
	void print_code(){
		PTD_CK(the_mth != mc_null);
		the_mth->print_code();
	}
	
};

typedef hc_term& (hcell::*pt_mth_t)();

template<class cl1_t>
bool 
hcall_mth(hc_term& (cl1_t::*mth_pt)() = mc_null){
	cl1_t oo1;
	if(mth_pt != mc_null){
		//(oo1.*mth_pt)();
	}
	return true;
}

#define hmethod(mth) \
	static hc_mth_def mth ## _def_reg; \
	hc_term& mth(); \

// end_define

#define hmethod_def(cls, mth, code) \
	void cls ## _ ## mth ## _ ## caller(); \
	hc_mth_def cls::mth ## _def_reg{#cls, #mth, cls ## _ ## mth ## _ ## caller}; \
	hc_term& \
	cls::mth(){ \
		hc_term* mc = new hc_mth_call(&cls::mth ## _def_reg); \
		hc_term* rr = mc; \
		if(src_term != mc_null){ \
			hc_term* tmp = src_term; \
			src_term = mc_null; \
			tmp = tmp->get_src(); \
			rr = new hc_binary_term(hc_member_op, tmp, mc); \
		} \
		if(cls::mth ## _def_reg.cod == mc_null){ \
			if(cls::mth ## _def_reg.defining){ \
				PTD_PRT("\nCannot have recursive methods in hlang.\nBad definition of %s.\n", \
					#cls "::" #mth \
				); \
				mch_abort_func(0, mc_cstr("BAD hlang METHOD DEFINITION \n")); \
			} \
			cls::mth ## _def_reg.defining = true; \
			hc_term& tm = (code); \
			cls::mth ## _def_reg.defining = false; \
			cls::mth ## _def_reg.cod = tm.get_src(); \
		} \
		return *rr; \
	} \
	void cls ## _ ## mth ## _ ## caller(){ \
		cls* obj = hc_reference<cls>::get_glb_ref(); \
		obj->cls::mth(); \
	} \

// end_define

class hmissive {
public:
	hmissive(){
		init_me();
	}

	virtual ~hmissive(){}

	virtual
	void init_me(int caller = 0){}
	
};


// ==================================================================
// TEST CODE
// TEST CODE
// TEST CODE
// TEST CODE
// TEST CODE
// TEST CODE

int func_01(const char* nam, void*);

class CLS_A {};
class CLS_B {};
class CLS_C {};
class CLS_D {};
class CLS_E {};

//hclass(
class cls_A2;
class cls_A3;

class cls_A1 : public hcell {
public:
	hcell_class(cls_A1);
	
	hchar(v1);
	hint(v2);
	hlong(o1);
	hlong(o2);
	hlong(o3);
	hlong(o4);
	hlong(o5);
	hint8_t(o6);
	huint8_t(o7);
	hreference(CLS_A, r1);
	hreference(CLS_B, r2);
	hreference(CLS_C, r3);
	hreference(CLS_D, r4);
	hreference(CLS_A, r5);

	hreference(cls_A2, rA2);
	hreference(cls_A3, rA3);
	
	hmethod(mth01);
	hmethod(mth02);
	hmethod(mth03);
	
	cls_A1(){
		o1 = 1;
		o2 = 2;
		o3 = 3;
		o4 = 4;
		o5 = 5;
	}

	~cls_A1(){}
	
};


class cls_A2 : public hcell {
public:
	hcell_class(cls_A2);
	
	hchar(v1);
	hint(v2);
	hlong(o1);
	hlong(o2);
	
	hreference(cls_A1, r1);
	hreference(cls_A1, rr2);
	
	hmethod(mth01);
};

class cls_A3 : public hcell {
public:
	hcell_class(cls_A3);
	
	hchar(v1);
	hint(v2);
	hreference(cls_A2, rr2);
	hreference(cls_A2, r3);

	hreference(cls_A1, aa1);
	hreference(cls_A2, aa2);
	hreference(cls_A3, aa3);
	
	hmethod(mth01);

	int attr_01 = func_01("name_attr_01", mc_null);
	int attr_02 = func_01(__PRETTY_FUNCTION__, mc_null);
	
};

class cls_A4 : public hcell {
public:
	hcell_class(cls_A4);
	
	hchar(a1);
};


//hcell(name);
//hmissive(name);

//hreference(class, name);


//HC_ALL_CLASSES.insert(std::pair<std::string, hdecl_class*>("pru_hcell", (hdecl_class*)mc_null));

		 
class pru_hcell : public cell {
public:
	MCK_DECLARE_MEM_METHODS(pru_hcell)
	
	static
	const char* get_cls_nam(){
		return "pru_hcell";
	}
	
	//operator obj_t() { return val; }
	
	//hattribute(int, nam);

	//hmethod(nam);
	
	pru_hcell(){
		init_pru_hcell();
	}

	~pru_hcell(){}

	void init_pru_hcell(){
		handler_idx = bj_cell_id(pru_hcell);
	}

	void handler(missive* msv);
	
	//int attr_03 = func_01(pru_hcell::get_cls_nam(), (void*)(&pru_hcell::handler));
	int attr_01 = func_01("name_attr_01", mc_null);
	int attr_02 = func_01("name_attr_02", mc_null);
	
};


void bj_mc_test_5(int argc, char *argv[]);



#endif		// HLANG_H



// _Generic
//static const char* get_str(){ return typeid(obj_t).name(); }
