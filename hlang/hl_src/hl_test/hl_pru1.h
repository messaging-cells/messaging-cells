

#ifndef TEST_PRU1_H
#define TEST_PRU1_H

#include "hlang.hh"

// ==================================================================
// TEST CODE
// TEST CODE
// TEST CODE
// TEST CODE
// TEST CODE
// TEST CODE

enum pru_tok_t : hl_token_t {
	bj_tok_pru_invalid = hl_tok_last + 1,
	bj_tok_pru_get,
	bj_tok_pru_set,
	bj_tok_pru_end
};

class cls_A2;
class cls_A3;

class msv_1 : public hcell {
public:
	hmissive_class(msv_1);
	
	hchar(a1);
	hmethod(mth01);
};


class cls_A1 : public hcell {
public:
	hcell_class(cls_A1);

	hbool(b1);
	hbool(b2);
	hbool(b3);
	hbool(b4);
	hchar(v1);
	hint(v2);
	hlong(o1);
	hlong(o2);
	hlong(o3);
	//hlong(o4);
	//hlong(o5);
	//hsafe_long(o4);
	//hsafe_long(o5);
	hreference(msv_1, o4);
	hreference(msv_1, o5);
	hint8_t(o6);
	huint8_t(o7);

	hreference(cls_A2, rA2);
	hreference(cls_A3, rA3);

	hnucleus(central);
	
	hmethod(mth01);
	hmethod(mth02);
	hmethod(mth03);
	hmethod(mth04);
	
	cls_A1(){
		o1 = 1;
		o2 = 2;
		o3 = 3;
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
	hmethod(mth02);
	hmethod(mth03);
	hmethod(mth04);
	hmethod(mth05);

	hnucleus(nucl_A2);
	
};

class cls_A3 : public hcell {
public:
	hcell_class(cls_A3);
	
	hlong(o1);
	hlong(o2);
	hlong(o3);
	//hsafe_long(o4);
	hreference(msv_1, o4);
	
	hint(xx1);
	hchar(v1);
	hint(v2);
	hreference(cls_A2, rr2);
	hreference(cls_A2, r3);

	hreference(cls_A1, aa1);
	hreference(cls_A2, aa2);
	hreference(cls_A3, aa3);
	
	hmethod(mth01);
	hmethod(mth02);

	hnucleus(nucl_A3);
};

class cls_A4 : public hcell {
public:
	hcell_class(cls_A4);
	
	hchar(a1);
	hreference(msv_1, r1);

	hnucleus(nucl_A4);
};

//hcell(name);
//hmissive(name);

//hreference(class, name);


//HC_ALL_CLASSES.insert(std::pair<std::string, hdecl_class*>("pru_hcell", (hdecl_class*)hl_null));

/*
class pru_hcell : public cell {
public:
	MCK_DECLARE_MEM_METHODS(pru_hcell)
	
	static
	const char* get_cls_nam(){
		return "pru_hcell";
	}
	
	pru_hcell(){
		init_pru_hcell();
	}

	~pru_hcell(){}

	void init_pru_hcell(){
		handler_idx = bj_cell_id(pru_hcell);
	}

	void handler(missive* msv);
	
	//int attr_03 = func_01(pru_hcell::get_cls_nam(), (void*)(&pru_hcell::handler));
	int attr_01 = func_01("name_attr_01", hl_null);
	int attr_02 = func_01("name_attr_02", hl_null);
	
};
*/

void hl_test_1(int argc, char *argv[]);

// _Generic
//static const char* get_str(){ return typeid(obj_t).name(); }

#endif		// TEST_PRU1_H

