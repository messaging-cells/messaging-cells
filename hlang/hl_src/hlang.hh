

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

#include <algorithm>
#include <type_traits>
#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
#include <list>

#include "dbg_util.h"

bool file_rename(hl_string& old_pth, hl_string& nw_pth);
bool file_exists(hl_string th_pth);
bool file_touch(hl_string the_pth);
bool file_newer_than(hl_string the_pth, time_t tm1);
bool make_dir(hl_string the_pth, mode_t mod = 0700);
bool change_dir(hl_string the_pth);
hl_string path_get_running_path();
hl_string path_to_absolute_path(hl_string pth);
bool path_create(hl_string n_pth);
bool path_begins_with(hl_string the_pth, hl_string the_beg);
bool path_ends_with(hl_string& the_str, hl_string& the_suf);
hl_string path_get_directory(hl_string the_pth, bool add_last_dir_sep);
hl_string path_get_name(hl_string the_pth);
hl_string get_errno_str(long val_errno);

typedef uint64_t hl_token_t;
typedef uint64_t hl_value_t;
typedef uint64_t hl_reference_t;

typedef int64_t hc_chip_idx;
#define hl_tok_last 0

class hc_system;
class hc_term;
class hc_mth_def;
class hcell;

typedef void (*hc_caller_t)();


class hclass_reg {
public:
	hl_string nam;
	std::map<hl_string, hc_term*> values;
	std::map<hl_string, hc_term*> references;
	std::list<hc_mth_def*> methods;
	hc_mth_def* nucleus = hl_null;
	hc_caller_t initer = hl_null;
	
	hclass_reg(){
		nucleus = hl_null;
		initer = hl_null;
	}

	virtual ~hclass_reg(){}

	bool has_value(const char* attr);
	bool has_reference(const char* attr);
	
	hl_string get_tmp_hh_name(){
		return nam + "_tmp.hh";
	}
	
	hl_string get_hh_name(){
		return nam + ".hh";
	}
	
	hl_string get_hh_define_str(){
		hl_string out = nam;
		std::transform(out.begin(), out.end(), out.begin(), ::toupper);
		out += "_HH_FILE";
		return out;
	}
	
	FILE* open_hh_file(const char* nm){
		FILE* ff = fopen(nm, "w+");
		if(ff == NULL){
			fprintf(stderr, "Cannot open file %s\n", nm);
			hl_abort_func(0, "ABORTING. Cannot open file.\n");
		}
		return ff;
	}
	
	void print_hh_file();

	void call_all_methods();
};

extern hc_system& HLANG_SYS();

class hc_system {
public:
	std::map<hl_string, hclass_reg*> all_classes;
	std::map<hl_string, hc_term*> all_const;
	std::map<hl_string, hc_term*> all_token;
	std::map<hl_string, hc_term*> all_external;
	
	hl_string project_nam;

	hc_system(){
		init_me();
	}

	virtual ~hc_system(){}
	
	hclass_reg* get_class_reg(const char* cls, hc_caller_t the_initer = hl_null);
	void register_method(const char* cls, hc_mth_def* mth, bool is_nucl);
	void register_value(hcell* obj, hc_term* attr);
	void register_reference(hcell* obj, hc_term* attr);

	bool has_token(const char* attr);
	bool has_const(const char* attr);
	bool has_external(const char* attr);

	void register_token(hc_term* attr);
	void register_const(hc_term* attr);
	void register_external(hc_term* attr);
	
	void init_all_token();
	void init_all_attributes();
	void call_all_registered_methods();
	
	void init_sys(){
		init_all_attributes();
		init_all_token();
		call_all_registered_methods();
	}

	void generate_hh_files();
	void generate_cpp_code();
	
	hl_string get_cpp_dir_nam(){
		return project_nam + "_cpp";
	}
	
	virtual
	void init_me(int caller = 0){
		project_nam = "hl_generated_output";
	}
	
};


template <bool> struct HC_ILLEGAL_USE_OF_OBJECT;
template <> struct HC_ILLEGAL_USE_OF_OBJECT<true>{};
#define HC_OBJECT_COPY_ERROR HC_ILLEGAL_USE_OF_OBJECT<false>()

#define hc_xstr(a) hc_str(a)
#define hc_str(a) #a

// ~,|,&,^,==, >>, <<, >, <,?,

enum	hc_syntax_op_t {
	hc_invalid_op,

	hc_dbg_op,
	
	hc_send_op,	// hsend
	hc_tell_op,	// htell
	
	hc_member_op,	// ->
	
	hc_comma_op,	// ,
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

	hc_async_asig_op,	// <<=
	
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
	static long	HC_PRT_TERM_INDENT;
	
	// constructors
	hc_term(){}

	virtual	~hc_term(){
		//printf("%s \n", STACK_STR.c_str());
		//bj_abort_func(0, "func: 'hc_term::~hc_term'"); 
	}

	// Don't allow copying (error prone):
	// force use of referenced rows
	
	hc_term(hc_term& other){ 
		hl_abort_func(0, "func: 'hc_term(hc_term&)' \n");
		//HC_OBJECT_COPY_ERROR;
	}

	hc_term&  operator , (hc_term& o1);
	hc_term&	operator >> (hc_term& o1);
	
	hc_term&	operator = (hc_term& o1);
	hc_term&	operator <<= (hc_term& o1);
	
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
	hc_term*	get_src(){
		return this;
	}
	
	virtual 
	void print_term();

	virtual 
	void print_code(){
		hl_abort_func(0, "Invalid call to 'print_code()'. " 
				"NOT_A_METHOD. It has no code to print.\n");
	}

	static
	void print_indent();
	
	virtual 
	hc_syntax_op_t	get_oper(){
		return hc_invalid_op;
	}
	
	virtual 
	const char*	get_name(){
		return "INVALID_NAME";
	}	

	virtual 
	bool	is_compound(){
		return false;
	}
};

hc_term&	hif(hc_term& o1);
hc_term&	helif(hc_term& o1);
hc_term&	hfor(hc_term& o1);
hc_term&	hwhile(hc_term& o1);
hc_term&	hswitch(hc_term& o1);
hc_term&	hcase(hc_term& o1);
hc_term&	hdbg(const char* cod);

class hc_unary_term : public hc_term {
public:
	hc_syntax_op_t op;
	hc_term* prm;
	
	virtual	~hc_unary_term(){
		if((prm != hl_null) && prm->is_compound()){
			delete prm;
			prm = hl_null;
		}
	}

	hc_unary_term(hc_syntax_op_t pm_op, hc_term* pm_val){
		init_unary_term(pm_op, pm_val);
	}

	void init_unary_term(hc_syntax_op_t pm_op = hc_invalid_op, 
						  hc_term* pm_val = hl_null)
	{
		op = pm_op;
		if(pm_val != hl_null){
			pm_val = pm_val->get_src();
		}
		prm = pm_val;
	}
	
	virtual 
	hc_syntax_op_t	get_oper(){
		return op;
	}
	
	virtual 
	const char*	get_name(){
		return hc_get_token(op);
	}
	
	virtual 
	void print_term();

	virtual 
	bool	is_compound(){
		return true;
	}
};

class hc_binary_term : public hc_term {
public:
	hc_syntax_op_t op;
	hc_term* lft;
	hc_term* rgt;
	
	virtual	~hc_binary_term(){
		if((lft != hl_null) && lft->is_compound()){
			delete lft;
			lft = hl_null;
		}
		if((rgt != hl_null) && rgt->is_compound()){
			delete rgt;
			rgt = hl_null;
		}
	}
	
	hc_binary_term(hc_syntax_op_t pm_op, hc_term* pm_lft, hc_term* pm_rgt){
		init_binary_term(pm_op, pm_lft, pm_rgt);
	}
	
	void init_binary_term(hc_syntax_op_t pm_op = hc_invalid_op, 
						  hc_term* pm_lft = hl_null, hc_term* pm_rgt = hl_null)
	{
		op = pm_op;
		if(op != hc_member_op){
			if(pm_lft != hl_null){
				pm_lft = pm_lft->get_src();
			}
			if(pm_rgt != hl_null){
				pm_rgt = pm_rgt->get_src();
			}
		}
		lft = pm_lft;
		rgt = pm_rgt;
	}
	
	virtual 
	hc_syntax_op_t	get_oper(){
		return op;
	}
	
	virtual 
	const char*	get_name(){
		return hc_get_token(op);
	}
	
	virtual 
	void print_term();

	virtual 
	bool	is_compound(){
		return true;
	}
};

class hc_send_term : public hc_term {
public:
	hc_syntax_op_t op;
	hc_term* snd_dst;
	hc_term* snd_tok;
	hc_term* snd_att;
	
	virtual	~hc_send_term(){
		if((snd_dst != hl_null) && snd_dst->is_compound()){
			delete snd_dst;
			snd_dst = hl_null;
		}
		if((snd_tok != hl_null) && snd_tok->is_compound()){
			delete snd_tok;
			snd_tok = hl_null;
		}
		if((snd_att != hl_null) && snd_att->is_compound()){
			delete snd_att;
			snd_att = hl_null;
		}
	}
	
	hc_send_term(hc_syntax_op_t pm_op, hc_term* pm_dst, hc_term* pm_tok, hc_term* pm_att){
		init_send_term(pm_op, pm_dst, pm_tok, pm_att);
	}
	
	void init_send_term(hc_syntax_op_t pm_op = hc_invalid_op, 
						hc_term* pm_dst = hl_null, hc_term* pm_tok = hl_null,
						hc_term* pm_att = hl_null)
	{
		op = pm_op;
		if(pm_dst != hl_null){
			pm_dst = pm_dst->get_src();
		}
		if(pm_tok != hl_null){
			pm_tok = pm_tok->get_src();
		}
		if(pm_att != hl_null){
			pm_att = pm_att->get_src();
		}
		snd_dst = pm_dst;
		snd_tok = pm_tok;
		snd_att = pm_att;
	}
	
	virtual 
	hc_syntax_op_t	get_oper(){
		return op;
	}
	
	virtual 
	const char*	get_name(){
		return hc_get_token(op);
	}
	
	virtual 
	void print_term();

	virtual 
	bool	is_compound(){
		return true;
	}
};

extern long hc_token_current_val;
extern const char* hc_token_type_nam;

template<class obj_t>
class hc_value : public hc_term {
public:
	static hc_value<obj_t>	HC_MSV_VAL;
	static hc_value<obj_t>	HC_MSV_TOK;

	const char* typ;
	const char* nam;
	obj_t	val;
	hcell*	owner;
	
	virtual	~hc_value(){}
	
	hc_value(const char* the_typ, const char* the_nam, 
			 hcell* the_owner = hl_null, obj_t the_val = obj_t())
	{
		typ = hl_null;
		nam = hl_null;
		owner = hl_null;
		init_val(the_typ, the_nam, true, the_owner, the_val);
	}
	
	hc_value& 
	init_val(const char* the_typ, const char* the_nam, bool is_first = false, 
			 hcell* the_owner = hl_null, obj_t the_val = obj_t())
	{
		if((typ == hl_null) && (the_typ != hl_null)){
			HL_CK(! std::is_pointer<obj_t>::value);
			HL_CK(! std::is_class<obj_t>::value);
			typ = the_typ;
			nam = the_nam;
			val = the_val;
			owner = the_owner;
			if(owner != hl_null){
				HLANG_SYS().register_value(owner, this);
			} else {
				if(typ == hc_token_type_nam){
					HLANG_SYS().register_token(this);
				} else {
					HLANG_SYS().register_const(this);
				}
			}
		} 
		return *this;
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

	//operator obj_t() { return ref; }		// cast op
	 
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
hc_value<obj_t> hc_value<obj_t>::HC_MSV_VAL{hl_null, hl_null};

template<class obj_t>
hc_value<obj_t> hc_value<obj_t>::HC_MSV_TOK{hl_null, hl_null};

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
	static hc_reference<obj_t>	HC_MSV_REF;
	static obj_t*	HC_GLB_REF;
	
	const char* typ;
	const char* nam;
	obj_t*	ref;
	hcell*	owner;
	
	virtual	~hc_reference(){}
	
	hc_reference(const char* the_typ, const char* the_nam, hcell* the_owner = hl_null){
		HL_CK(! std::is_pointer<obj_t>::value);
		HL_CK(std::is_class<obj_t>::value);
		//HL_CK((std::is_base_of<hcell, obj_t>::value));
		typ = the_typ;
		nam = the_nam;
		ref = hl_null;
		owner = the_owner;
		if(owner != hl_null){
			HLANG_SYS().register_reference(owner, this);
		} else {
			HLANG_SYS().register_external(this);
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
		if(HC_GLB_REF == hl_null){
			HC_GLB_REF = new obj_t();
		}
		return HC_GLB_REF;
	}
	
	obj_t const *	operator -> () const {
		if(ref == hl_null){
			ref = get_glb_ref();
			//ref = new obj_t();
		}
		if(ref->rf_src_tm != hl_null){ 
			HL_PRT("\nCannot have recursive referencing in hlang.\n"); 
		}
		ref->rf_src_tm = this;
		return ref;
	}
	
    obj_t*	operator -> () {
		if(ref == hl_null){
			ref = get_glb_ref();
			//ref = new obj_t();
		}
		if(ref->rf_src_tm != hl_null){ 
			HL_PRT("\nCannot have recursive referencing in hlang.\n"); 
		}
		ref->rf_src_tm = this;
		return ref;
	}
	
	bool is_null(){
		return (ref == hl_null);
	}

	//operator obj_t() { return ref; }		// cast op
	
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
obj_t* hc_reference<obj_t>::HC_GLB_REF = hl_null;

template<class obj_t>
hc_reference<obj_t> hc_reference<obj_t>::HC_MSV_REF{"hc_reference", "msv_ref"};

template<class cl1_t, class cl2_t>
cl2_t*
hcast(hc_reference<cl1_t>& o1){
	return (cl2_t*)(o1.ref);
}

#define htok_get(nn, obj) \
	hc_value<hl_token_t> tk_get_ ## nn{hc_token_type_nam, obj->get_attr_nm("tk_get_", #nn), hl_null} 

#define htok_set(nn, obj) \
	hc_value<hl_token_t> tk_set_ ## nn{hc_token_type_nam, obj->get_attr_nm("tk_set_", #nn), hl_null} 

#define htoks_att(nn, obj) htok_get(nn, this); htok_set(nn, this); 

#define htok_base(nn, obj) hc_value<hl_token_t> nn{hc_token_type_nam, #nn, obj} 

#define htoken(nn) htok_base(nn, hl_null)

#define hvalue(tt, nn) htoks_att(nn, this); hc_value<tt> nn{#tt, #nn, this}

#define hreference(tt, nn) htoks_att(nn, this); hc_reference<tt> nn{#tt, #nn, this}

#define hkeyword(nn) hc_keyword nn(#nn)

#define hconst(tt, nn, vv) hc_value<tt> nn{#tt, #nn, hl_null, vv}

#define hexternal(tt, nn) hc_reference<tt> nn{#tt, #nn}

#define htok(nn) htok_base(nn, this)
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


class hc_mth_def : public hc_term {
public:
	const char* cls = hl_null;
	const char* nam = hl_null;
	hc_term* cod = hl_null;
	bool defining = false;
	hc_caller_t caller = hl_null;
	
	virtual	~hc_mth_def(){}
	
	hc_mth_def(const char* the_cls, const char* the_nam, 
			   hc_caller_t the_cllr, bool is_nucl = false)
	{
		cls = the_cls;
		nam = the_nam;
		caller = the_cllr;
		HLANG_SYS().register_method(the_cls, this, is_nucl);
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
		printf("\tCODE_FOR %s\n", get_name());
		if(cod == hl_null){
			printf("EMPTY_COD for mth\n");
		} else {
			cod->print_term();
			printf("\n");
		}
	}
	
};

class hc_mth_call : public hc_term {
public:
	hc_mth_def* the_mth = hl_null;
	
	virtual	~hc_mth_call(){}
	
	hc_mth_call(hc_mth_def* mthdef){
		HL_CK(mthdef != hl_null);
		the_mth = mthdef;
	}

	virtual 
	const char*	get_name(){
		HL_CK(the_mth != hl_null);
		return the_mth->get_name();
	}
	
	virtual 
	void print_term(){
		std::cout << ' ' << get_name() << "() ";
	}

	virtual 
	void print_code(){
		HL_CK(the_mth != hl_null);
		the_mth->print_code();
	}
	
};

typedef hc_term& (hcell::*pt_mth_t)();

template<class cl1_t>
bool 
hcall_mth(hc_term& (cl1_t::*mth_pt)() = hl_null){
	cl1_t oo1;
	if(mth_pt != hl_null){
		//(oo1.*mth_pt)();
	}
	return true;
}

#define hmethod(mth) \
	static hc_mth_def mth ## _def_reg; \
	hc_term& mth(); \

// end_define

#define hnucleus(mth) hmethod(mth)


#define hmethod_def_base(cls, mth, code, is_nucl) \
	void cls ## _ ## mth ## _ ## caller(); \
	hc_mth_def cls::mth ## _def_reg{#cls, #mth, cls ## _ ## mth ## _ ## caller, is_nucl}; \
	hc_term& \
	cls::mth(){ \
		hc_term* mc = new hc_mth_call(&cls::mth ## _def_reg); \
		hc_term* rr = mc; \
		if(rf_src_tm != hl_null){ \
			hc_term* tmp = rf_src_tm; \
			rf_src_tm = hl_null; \
			tmp = tmp->get_src(); \
			rr = new hc_binary_term(hc_member_op, tmp, mc); \
		} \
		if(cls::mth ## _def_reg.cod == hl_null){ \
			if(cls::mth ## _def_reg.defining){ \
				HL_PRT("\nCannot have recursive methods in hlang.\nBad definition of %s.\n", \
					#cls "::" #mth \
				); \
				hl_abort_func(0, "BAD hlang METHOD DEFINITION \n"); \
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

#define hmethod_def(cls, mth, code) hmethod_def_base(cls, mth, code, false)

#define hnucleus_def(cls, mth, code) hmethod_def_base(cls, mth, code, true)

class hc_dbg : public hc_term {
public:
	hl_string dbg_cod;
	
	virtual	~hc_dbg(){}
	
	hc_dbg(hl_string the_cod){
		dbg_cod = the_cod;
	}

	virtual 
	const char*	get_name(){
		return "hc_dbg";
	}
	
	virtual 
	void print_term(){
		std::cout << "hdbg_start(" << dbg_cod << ")hdbg_end\n";
	}

	virtual 
	void print_code(){
		print_term();
	}

	virtual 
	hc_syntax_op_t	get_oper(){
		return hc_dbg_op;
	}
};

/*
class hmissive {
public:
	hmissive(){
		init_me();
	}

	virtual ~hmissive(){}

	virtual
	void init_me(int caller = 0){}
	
};
*/

#define hme_def(cls) \
    virtual	hc_term&	hme(){ \
		if(hc_pt_me == hl_null){ \
			hc_reference<cls>* tmp = new hc_reference<cls>(#cls, "hme_" #cls, this); \
			tmp->ref = this; \
			hc_pt_me = tmp; \
		} \
		return *hc_pt_me; \
	} \

// end_define


class hcell {
public:
	hc_chip_idx		hc_my_id = -1;
	hc_term* 		hc_pt_me = hl_null;
	hc_term* 		rf_src_tm = hl_null;

	hl_reference_t 	msv_src;
	hl_token_t 		msv_tok;
	hl_value_t 		msv_val;
	
	hcell(){
		init_me();
	}
	
	virtual ~hcell(){}

	virtual
	void init_me(int caller = 0){
		rf_src_tm = hl_null;
	}

	virtual
	const char* get_class_name(){
		return "hcell";
	}

	const char* get_attr_nm(const char* pfix, const char* sfix);
	
	hme_def(hcell);
	
	hc_term& hsend(hc_term& dst, hc_term& tok, hc_term& att);
	hc_term& htell(hc_term& dst, hc_term& tok, hc_term& att);
};

#define hcell_class(cls) \
	static const char* hc_class_name; \
	static hclass_reg* hc_register_ ## cls; \
	static hc_reference<cls>& get_msg_ref(); \
	static hc_reference<cls>& get_msg_src(); \
	virtual	const char* get_class_name(); \
	hme_def(cls); \

// end_define

#define hcell_class_def(cls) \
	void cls ## _ref_initer(); \
	hclass_reg* cls::hc_register_ ## cls = HLANG_SYS().get_class_reg(#cls, cls ## _ref_initer); \
	const char* cls::hc_class_name = #cls; \
	const char* \
	cls::get_class_name(){ \
		return cls::hc_class_name; \
	} \
	void cls ## _ref_initer(){ \
		hc_reference<cls>::get_glb_ref(); \
	} \
	hc_reference<cls>& cls::get_msg_ref(){ \
		static hc_reference<cls> gref{#cls, "hmsg_ref_" #cls}; \
		return gref; \
	} \
	hc_reference<cls>& cls::get_msg_src(){ \
		static hc_reference<cls> gref{#cls, "hmsg_src_" #cls}; \
		return gref; \
	} \

// end_define


#define HC_GET_SOURCE() \
	hc_term* src = this; \
	if((owner != hl_null) && (owner->rf_src_tm != hl_null)){ \
		hc_term* tmp = owner->rf_src_tm; \
		owner->rf_src_tm = hl_null; \
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

#define hmsg_src(cls) (cls::get_msg_src())
#define hmsg_ref(cls) (cls::get_msg_ref())
#define hmsg_val(typ) (hc_value<typ>::HC_MSV_VAL.init_val(#typ, "hmsg_val_" #typ))
#define hmsg_tok(typ) (hc_value<typ>::HC_MSV_TOK.init_val(#typ, "hmsg_tok_" #typ))

#endif		// HLANG_H


