

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

#include <iostream>
#include <stdio.h>
#include <map>
#include <string>

#include "stack_trace.h"
#include "nervenet.hh"
//include "booter.h"
#include "cell.hh"

struct hdecl_method {
	std::string mth_name;
};

struct hdecl_attribute {
	std::string att_name;
	std::string type;
};

struct hdecl_class {
	std::string cls_name;
	std::map<std::string, hdecl_attribute*> attributes;
	std::map<std::string, hdecl_method*> methods;
};

extern std::map<std::string, hdecl_class*> HC_ALL_CLASSES;

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
	
	hc_assig_op,	// =
	
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

class hc_term;

#define HC_DEFINE_BINARY_OP_BASE(the_code) \
	PTD_CK(is_top() || o1.is_top()); \
	hc_term* tm = new hc_binary_term(the_code, this, &o1); \
	hc_term::HC_TOP_TERM = tm; \
	return *tm; \

// end_define

#define HC_DEFINE_BINARY_OP(the_op, the_code) \
hc_term& hc_term::operator the_op (hc_term& o1) { \
	HC_DEFINE_BINARY_OP_BASE(the_code) \
} \

// end_define

#define HC_DEFINE_UNARY_OP_BASE(the_code) \
	PTD_CK(is_top()); \
	hc_term* tm = new hc_unary_term(the_code, this); \
	hc_term::HC_TOP_TERM = tm; \

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
	hc_term::HC_TOP_TERM = tm; \
	return *tm; \
} \

// end_define


class hc_term {
public:
	static hc_term	HC_NULL_TERM;
	static hc_term* HC_TOP_TERM;
	
	// constructors
	hc_term(){}

	virtual	~hc_term(){
		//printf("%s \n", STACK_STR.c_str());
		//bj_abort_func(0, "func: 'hc_term::~hc_term'"); 
	}

	// Don't allow copying (error prone):
	// force use of referenced rows
	
	hc_term(hc_term& other){ 
		//mch_abort_func(0, mc_cstr("func: 'hc_term(hc_term&)' \n"));
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
	void print_term();
	
	bool is_value(){
		return (get_term_kind() == hc_value_kind);
	}

	bool is_reference(){
		return (get_term_kind() == hc_reference_kind);
	}

	bool is_call(){
		return (get_term_kind() == hc_call_kind);
	}

	bool is_top(){
		return (is_value() || is_reference() || is_call() || (this == HC_TOP_TERM));
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
	
	hc_binary_term (hc_syntax_op_t pm_op, hc_term* pm_lft, hc_term* pm_rgt){
		init_binary_term(pm_op, pm_lft, pm_rgt);
	}
	
	void init_binary_term(hc_syntax_op_t pm_op = hc_invalid_op, 
						  hc_term* pm_lft = mc_null, hc_term* pm_rgt = mc_null)
	{
		op = pm_op;
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
	
	virtual	~hc_value(){}
	
	hc_value(const char* the_typ, const char* the_nam){
		PTD_CK(! std::is_pointer<obj_t>::value);
		PTD_CK(! std::is_class<obj_t>::value);
		typ = the_typ;
		nam = the_nam;
		val = obj_t();
	}
	
	hc_value(hc_value<obj_t>& other){ 
		HC_OBJECT_COPY_ERROR; 
	}

	hc_value(hc_term& other){ 
		HC_OBJECT_COPY_ERROR; 
	}
	
	hc_term&	operator = (hc_term& o1){
		HC_DEFINE_BINARY_OP_BASE(hc_assig_op);
	}

	hc_term&  operator = (hc_value<obj_t>& o1) { 
		HC_DEFINE_BINARY_OP_BASE(hc_assig_op);
	}

	void operator ()(obj_t aa) { val = aa; }	// as unary func. used as init func
	//hc_value<obj_t>* operator ()() { return this; }	// as empty func
	
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
	static hc_reference<obj_t>	HC_NULL_REFERENCE;

	const char* typ;
	const char* nam;
	obj_t*	ref;
	
	virtual	~hc_reference(){}
	
	hc_reference(const char* the_typ, const char* the_nam){
		PTD_CK(! std::is_pointer<obj_t>::value);
		PTD_CK(std::is_class<obj_t>::value);
		typ = the_typ;
		nam = the_nam;
		ref = mc_null;
	}
	
	hc_reference(hc_reference<obj_t>& other){ 
		HC_OBJECT_COPY_ERROR; 
	}

	hc_reference(hc_term& other){ 
		HC_OBJECT_COPY_ERROR; 
	}
	
	hc_term&	operator = (hc_term& o1){
		HC_DEFINE_BINARY_OP_BASE(hc_assig_op);
	}

	hc_term&  operator = (hc_reference<obj_t>& o1) { 
		HC_DEFINE_BINARY_OP_BASE(hc_assig_op);
	}

	/*hc_term&	operator = (hc_term& o1){
		HC_OBJECT_COPY_ERROR; 
		return HC_NULL_TERM;
	}

	hc_term&  operator = (hc_reference<obj_t>& o1) { 
		HC_DEFINE_BINARY_OP_BASE(hc_assig_op);
	}*/

	void operator ()(obj_t* aa) { ref = aa; }	// as unary func. used as init func
	//hc_reference<obj_t>* operator ()() { return this; }	// as empty func
	
	void  operator = (obj_t* aa) { 
		ref = aa;
	}

	hc_term const *	operator -> () const {
		HC_DEFINE_UNARY_OP_BASE(hc_member_op);
		return this;
	}
	
    hc_term*	operator -> () {
		HC_DEFINE_UNARY_OP_BASE(hc_member_op);
		return this;
	}
	
	bool is_null(){
		return (this == &HC_NULL_REFERENCE);
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
};

template<class obj_t>
hc_reference<obj_t> hc_reference<obj_t>::HC_NULL_REFERENCE{};

#define hkeyword(nn) hc_keyword nn(#nn)

#define hvalue(tt, nn) hc_value<tt> nn{#tt, #nn}
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

#define hreference(tt, nn) hc_reference<tt> nn{#tt, #nn}

extern hc_keyword helse;
extern hc_keyword hbreak;
extern hc_keyword hcontinue;
extern hc_keyword hreturn;

void
hc_init_keywords();

typedef void (hc_term::*hc_method_t)();

class hc_mth_call : public hc_term {
public:
	const char* nam = mc_null;
	hc_term* cod = mc_null;
	
	virtual	~hc_mth_call(){}
	
	hc_mth_call(const char* the_nam){
		nam = the_nam;
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
		std::cout << ' ' << nam << "() ";
	}
};

/*
#define hmethod(nn) \
	hc_mth_call nn ## _resp{#nn}; \
	hc_mth_call nn(); \

// end_define

#define hmethod_def(mth_nam, code) \
	hc_mth_call \
	mth_nam(){ \
		if(mth_nam ## _resp.cod == mc_null){ \
			(code); \
			PTD_CK(hc_term::HC_TOP_TERM != mc_null); \
			mth_nam ## _resp.cod = hc_term::HC_TOP_TERM; \
		} \
		return mth_nam ## _resp; \
	} \

// end_define
*/

#define hmethod(mth) \
	static hc_mth_call mth ## _resp; \
	hc_mth_call mth(); \

// end_define

#define hmethod_def(cls, mth, code) \
	hc_mth_call cls::mth ## _resp{#cls "_" #mth}; \
	hc_mth_call \
	cls::mth(){ \
		if(cls::mth ## _resp.cod == mc_null){ \
			(code); \
			PTD_CK(hc_term::HC_TOP_TERM != mc_null); \
			cls::mth ## _resp.cod = hc_term::HC_TOP_TERM; \
		} \
		return cls::mth ## _resp; \
	} \

// end_define


class hcell {
public:
	hcell(){
		init_me();
	}

	virtual ~hcell(){}

	virtual
	void init_me(int caller = 0){}
	
    /*hc_term*	hme() { 
		return this; 
	}*/
	
};

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

class CLS_A {};
class CLS_B {};
class CLS_C {};
class CLS_D {};
class CLS_E {};

class cls_A1 : public hcell {
public:
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
	
	hmethod(mth01);
};


//hcell(name);
//hmissive(name);

//hreference(class, name);


//HC_ALL_CLASSES.insert(std::pair<std::string, hdecl_class*>("pru_hcell", (hdecl_class*)mc_null));

int func_01(const char* nam, void*);
		 
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
	
	int attr_03 = func_01(pru_hcell::get_cls_nam(), (void*)(&pru_hcell::handler));
	int attr_01 = func_01("name_attr_01", mc_null);
	int attr_02 = func_01("name_attr_02", mc_null);
	
};


void bj_mc_test_5(int argc, char *argv[]);



#endif		// HLANG_H



// _Generic
//static const char* get_str(){ return typeid(obj_t).name(); }
