
#include <stdio.h>

#include "cell.hh"
#include "preload.hh"
#include "hlang.hh"

hc_system 	HLANG_SYS;
hc_term		hc_term::HC_NULL_TERM{};
long	hc_term::HC_PRT_TERM_INDENT = 0;

hclass_reg*
hc_system::get_class_reg(const char* cls, hc_caller_t the_initer){
	std::map<std::string, hclass_reg*>::iterator it;
	it = all_classes.find(cls);
	bool added = false;
	if(it == all_classes.end()){
		all_classes[cls] = new hclass_reg();
		added = true;
		printf("ADDING_CLASS %s\n", cls);
	}
	hclass_reg* cls_reg = all_classes[cls];
	if(added){
		cls_reg->nam = cls;
	}
	if((the_initer != mc_null) && (cls_reg->initer == mc_null)){
		cls_reg->initer = the_initer;
	}
	return cls_reg;
}

void
hc_system::register_method(const char* cls, hc_mth_def* mth){
	PTD_CK(cls != mc_null);
	PTD_CK(mth != mc_null);
	hclass_reg* cls_reg = get_class_reg(cls);
	cls_reg->methods.push_front(mth);
	printf("ADDING_METHOD %s.%s\n", cls_reg->nam.c_str(), mth->nam);
}

bool
hclass_reg::has_value(const char* attr){
	std::map<std::string, hc_term*>::iterator it;
	it = values.find(attr);
	return (it != values.end());
}

void
hc_system::register_value(hcell* obj, hc_term* attr){
	PTD_CK(obj != mc_null);
	PTD_CK(attr != mc_null);
	hclass_reg* cls_reg = get_class_reg(obj->get_class_name());
	if(! cls_reg->has_value(attr->get_name())){
		(cls_reg->values)[attr->get_name()] = attr;
		printf("ADDING_VALUE %s.%s\n", cls_reg->nam.c_str(), attr->get_name());
	}
}

bool
hclass_reg::has_reference(const char* attr){
	std::map<std::string, hc_term*>::iterator it;
	it = references.find(attr);
	return (it != references.end());
}

void
hc_system::register_reference(hcell* obj, hc_term* attr){
	PTD_CK(obj != mc_null);
	PTD_CK(attr != mc_null);
	hclass_reg* cls_reg = get_class_reg(obj->get_class_name());
	if(! cls_reg->has_reference(attr->get_name())){
		(cls_reg->references)[attr->get_name()] = attr;
		printf("ADDING_REFERENCE %s.%s\n", cls_reg->nam.c_str(), attr->get_name());
	}
}

bool
hc_system::has_const(const char* attr){
	std::map<std::string, hc_term*>::iterator it;
	it = all_const.find(attr);
	return (it != all_const.end());
}

void
hc_system::register_const(hc_term* attr){
	PTD_CK(attr != mc_null);
	if(! has_const(attr->get_name())){
		all_const[attr->get_name()] = attr;
		printf("ADDING_CONST %s\n", attr->get_name());
	}
}

bool
hc_system::has_external(const char* attr){
	std::map<std::string, hc_term*>::iterator it;
	it = all_external.find(attr);
	return (it != all_external.end());
}

void
hc_system::register_external(hc_term* attr){
	PTD_CK(attr != mc_null);
	if(! has_external(attr->get_name())){
		all_external[attr->get_name()] = attr;
		printf("ADDING_EXTERNAL %s\n", attr->get_name());
	}
}

void
hclass_reg::call_all_methods(){
	auto it = methods.begin();
	for(; it != methods.end(); ++it){
		hc_mth_def* mth_df = (*it);
		std::cout << "\tCALLING METHOD " << mth_df->nam << '\n';
		hc_caller_t cr = mth_df->caller;
		(*cr)();
		
		mth_df->print_code();

		std::cout << "-------------------------------\n";
	}
}

void
hc_system::call_all_registered_methods(){
	std::cout << "---------------------------------------------------------------\n";
	auto it = all_classes.begin();
	for(; it != all_classes.end(); ++it){
		std::cout << "CALLING METHODS FOR CLASS " << it->first << '\n';
		it->second->call_all_methods();
		std::cout << "===========================================================\n";
	}
}

void
hc_system::init_all_attributes(){
	std::cout << "---------------------------------------------------------------\n";
	auto it = all_classes.begin();
	for(; it != all_classes.end(); ++it){
		std::cout << "ADDING ATTRIBUTES FOR CLASS " << it->first << '\n';
		hc_caller_t cr = it->second->initer;
		if(cr != mc_null){
			(*cr)();
		}
	}
}

const char*
hc_get_token(hc_syntax_op_t op){
	const char* tok = "INVALID_TOKEN";
	switch(op){
		case hc_comma_op:
			tok = ",";
		break;
		case hc_async_asig_op:
			tok = "<<=";
		break;
		case hc_then_op:
			tok = ">>";
		break;
		case hc_hme_op:
			tok = "hme";
		break;
		case hc_hif_op:
			tok = "hif";
		break;
		case hc_helse_op:
			tok = "helse";
		break;
		case hc_helif_op:
			tok = "helif";
		break;
		case hc_hfor_op:
			tok = "hfor";
		break;
		case hc_hwhile_op:
			tok = "hwhile";
		break;
		case hc_hswitch_op:
			tok = "hswitch";
		break;
		case hc_hcase_op:
			tok = "hcase";
		break;
		case hc_hbreak_op:
			tok = "hbreak";
		break;
		case hc_hcontinue_op:
			tok = "hcontinue";
		break;
		case hc_hreturn_op:
			tok = "hreturn";
		break;
		case hc_member_op:
			tok = "->";
		break;
		case hc_assig_op1:
			tok = "=1";
		break;
		case hc_assig_op2:
			tok = "=2";
		break;
		case hc_assig_op3:
			tok = "=3";
		break;
		case hc_assig_op4:
			tok = "=4";
		break;
		case hc_assig_op5:
			tok = "=5";
		break;
		case hc_less_than_op:
			tok = "<";
		break;
		case hc_more_than_op:
			tok = ">";
		break;
		case hc_less_equal_than_op:
			tok = "<=";
		break;
		case hc_more_equal_than_op:
			tok = ">=";
		break;
		case hc_equal_op:
			tok = "==";
		break;
		case hc_not_equal_op:
			tok = "!=";
		break;
		case hc_and_op:
			tok = "&&";
		break;
		case hc_or_op:
			tok = "||";
		break;
		case hc_not_op:
			tok = "!";
		break;
		case hc_bit_and_op:
			tok = "&";
		break;
		case hc_bit_or_op:
			tok = "|";
		break;
		case hc_bit_not_op:
			tok = "~";
		break;

		case hc_plus_op:
			tok = "+";
		break;
		case hc_post_inc_op:
			tok = "++";
		break;
		case hc_pre_inc_op:
			tok = "++";
		break;
		case hc_minus_op:
			tok = "-";
		break;
		case hc_post_dec_op:
			tok = "--";
		break;
		case hc_pre_dec_op:
			tok = "--";
		break;
		default:
		break;
	}
	return tok;
}

hc_term& hc_term::operator , (hc_term& o1) { 
	HC_DEFINE_BINARY_OP_BASE(hc_comma_op);
}

HC_DEFINE_BINARY_OP(>>, hc_then_op)
HC_DEFINE_BINARY_OP(<<=, hc_async_asig_op)

HC_DEFINE_BINARY_OP(=, hc_assig_op1)

HC_DEFINE_BINARY_OP(+, hc_plus_op)
HC_DEFINE_BINARY_OP(-, hc_minus_op)

HC_DEFINE_BINARY_OP(<, hc_less_than_op)
HC_DEFINE_BINARY_OP(>, hc_more_than_op)
HC_DEFINE_BINARY_OP(<=, hc_less_equal_than_op)
HC_DEFINE_BINARY_OP(>=, hc_more_equal_than_op)
HC_DEFINE_BINARY_OP(==, hc_equal_op)
HC_DEFINE_BINARY_OP(!=, hc_not_equal_op)
HC_DEFINE_BINARY_OP(&&, hc_and_op)
HC_DEFINE_BINARY_OP(||, hc_or_op)
HC_DEFINE_BINARY_OP(&, hc_bit_and_op)
HC_DEFINE_BINARY_OP(|, hc_bit_or_op)

HC_DEFINE_UNARY_OP(!, hc_not_op)
HC_DEFINE_UNARY_OP(~, hc_bit_not_op)

HC_DEFINE_UNARY_OP(++, hc_pre_inc_op)
HC_DEFINE_UNARY_OP(--, hc_pre_dec_op)

hc_term& hc_term::operator ++ (int){
	hc_term* tm = new hc_unary_term(hc_post_inc_op, this);
	return *tm;
}

hc_term& hc_term::operator -- (int){
	hc_term* tm = new hc_unary_term(hc_post_dec_op, this);
	return *tm;
}

HC_DEFINE_FUNC_OP(hif, hc_hif_op)
HC_DEFINE_FUNC_OP(helif, hc_helif_op)
HC_DEFINE_FUNC_OP(hfor, hc_hfor_op)
HC_DEFINE_FUNC_OP(hwhile, hc_hwhile_op)
HC_DEFINE_FUNC_OP(hswitch, hc_hswitch_op)
HC_DEFINE_FUNC_OP(hcase, hc_hcase_op)

hkeyword(helse);
hkeyword(hbreak);
hkeyword(hcontinue);
hkeyword(hreturn);

void 
hc_term::print_term(){
	printf("%s \n", STACK_STR.c_str());
	printf("INVALID_TERM!!!!\n");
}


void //static
hc_term::print_indent(){
	PTD_CK(HC_PRT_TERM_INDENT >= 0);
	for(long aa = 0; aa < HC_PRT_TERM_INDENT; aa++){
		printf("\t");
	}
}

void 
hc_unary_term::print_term(){
	const char* tok = hc_get_token(op);
	printf("%s", tok);
	printf("(");
	if(prm != mc_null){ prm->print_term(); }
	printf(")");
}

void 
hc_binary_term::print_term(){
	const char* tok = hc_get_token(op);
	switch(op){
	case hc_comma_op:
		if(lft != mc_null){ lft->print_term(); }
		printf("%s\n", tok); print_indent();
		if(rgt != mc_null){ rgt->print_term(); }
	break;
	default:
		hc_syntax_op_t lft_op = lft->get_oper();
		hc_syntax_op_t rgt_op = rgt->get_oper();
		printf("("); 
		HC_PRT_TERM_INDENT++;
		
		if(lft_op == hc_comma_op){ printf("("); }
		if(lft != mc_null){ lft->print_term(); }
		if(lft_op == hc_comma_op){ printf(")"); }
		
		printf(" %s ", tok);
		
		if(rgt_op == hc_comma_op){ printf("("); }
		if(rgt != mc_null){ rgt->print_term(); }
		if(rgt_op == hc_comma_op){ printf(")"); }
		
		HC_PRT_TERM_INDENT--;
		printf(")");
	break;
	}
}

hc_term&
hcell::hsend(hc_term& dst, hc_term& tok, hc_term& att){
	mch_abort_func(0, mc_cstr("FIX_THIS_CODE' \n"));
	return hme();
}

hc_term&
hcell::htell(hc_term& dst, hc_term& tok, hc_term& att){
	mch_abort_func(0, mc_cstr("FIX_THIS_CODE' \n"));
	return hme();
}

//////////// EXAMPLE CODE
//////////// EXAMPLE CODE
//////////// EXAMPLE CODE

int func_01(const char* nam, void*){ 
	printf("declar attr = %s \n", nam);
	return 567; 
};

void
hc_term::dbg_func(){
	printf("%s %d\n", __PRETTY_FUNCTION__, __LINE__);
}

//std::map<std::string, hdecl_class*> HC_ALL_CLASSES;

//hmethod_def(cls_A1::mth01, hc_term::HC_NULL_TERM);

//hmethod_def(cls_A1, mth01, r1);

//hmethod_def(cls_A1, mth01, (r1 + r2));

hcell_class_def(cls_A1);
hcell_class_def(cls_A2);
hcell_class_def(cls_A3);
hcell_class_def(cls_A4);

hmethod_def(cls_A1, mth01, (
	(t1 = bj_tok_pru_get),
	(r1 = (o1 + o2)),
	(o2 = (r2 + r1)),
	(r1 = r2) = (r4 + r5),
	(o1 = o2) <<= (o4 + o5),
	(o1 <<= o2),
	o4, o5, 
	hswitch(o1) >> (
		hcase(o2) >> o3++, 
		hcase(o4) >> ++o5,
		hcase(o1) >> o2
	),
	hif(o3) >> (~ o1 + ! o2),
	helif(o4) >> (o5 && o3),
	hfor(o4) >> (o2 || o3),
	hwhile(o4) >> (o1 & o3),
	hreturn,
	//mth02(), 
	hcontinue,
	hbreak,
	helse >> o2,
	((o1 < o2) <= (o3 > o4)),
	o4
));

hmethod_def(cls_A1, mth02, (
	(r1 = (o1 + o2)),
	mth01(), 
	hreturn
));

hmethod_def(cls_A1, mth03, (
	hif(o3) >> (~ o1 + ! o2),
	(o2 = (r2 + r1)),
	(o2 <<= (r2 + r1)),
	r1 = hme()
));

hmethod_def(cls_A2, mth01, (
	hif(v1) >> (~ o1 + ! o2),
	(r1->o4) + v2
));

hmethod_def(cls_A3, mth01, (
	r3->r1->o4(), 
	r3->r1->mth02(), 
	r3->r1->o4(),
	aa1 = aa2, 
	aa2 <<= aa3, 
	aa3 = aa1
));

/*
	v1 = r3->r1->mth02()
	
	r3->r1->mth02()
	
	r3->r1->o4(), 
	r3->r1->mth02(), 
	r3->r1->o4()
	
	r3->r1->o4(), 
	r3->r1->o4()
	
	r3->r1->o4() = rr2->rr2->o5()
	
	(v1 = (r3->r1->o4)), 
	hif(rr2->rr2->o5)
	
	
	v1 = r3->r1->o4(), 
	rr2->rr2->o5(),
	r3->r1->o4() = v1,
	r3 = r3 -> r1 -> o4()
*/

class CLS_AA {};
class CLS_BB : public CLS_AA {};
class CLS_CC : public CLS_BB {};

void bj_mc_test_5(int argc, char *argv[])
{
	printf("bj_mcbj_mc_test_5 \n");
	if(argc > 1){
		mch_epiphany_elf_path = argv[1];
		printf("Using workeru executable: %s \n", mch_epiphany_elf_path);
	}
	
	hexternal(CLS_A, e1);
	hconst(long, k1, 123);
	
	//hc_init_keywords();
	printf("######################################################\n");
	printf("######################################################\n");
	
	hc_system::get_sys().init_all_attributes();
	HLANG_SYS.call_all_registered_methods();
	
	/*
	
	std::cout << "a2b: " << std::is_base_of<CLS_AA, CLS_BB>::value << '\n';
	std::cout << "b2a: " << std::is_base_of<CLS_BB, CLS_AA>::value << '\n';

	cls_A1 aa;
	cls_A2 bb;
	cls_A3 cc;

	std::cout << "get_nam_aa=" << aa.get_class_name() << '\n';
	std::cout << "get_nam_bb=" << bb.get_class_name() << '\n';
	std::cout << "get_nam_cc=" << cc.get_class_name() << '\n';
	
	hc_term& (cls_A1::*mth_pt)() = &cls_A1::mth01;
	
	(aa.*mth_pt)().print_code();

	//aa.mth01().print_code();
	
	//bb.r1 = &aa;
	//bb.rr2 = &aa;
	//cc.r3 = &bb;
	//cc.rr2 = &bb;
	
	bb.mth01().print_code();
	cc.mth01().print_code();
	
	//CLS_AA AA1;
	CLS_BB BB1;
	
	hc_reference<CLS_AA> ref1{"CLS_AA", "ref1"};
	ref1 = &BB1;
	hc_reference<CLS_BB> ref2{"CLS_BB", "ref2"};
	ref2 = &BB1;
	hc_reference<CLS_BB> ref3{"CLS_BB", "ref3"};
	ref3 = hcast<CLS_AA, CLS_BB>(ref1);
	
	printf("IN_MAIN. %s %d\n", __PRETTY_FUNCTION__, __LINE__);
	
	//printf("cls_A3_mth01_called %d\n", cls_A3_mth01_called);
	
	//long xx = o1;
	//printf("\n\n %ld \n", xx);
	
	std::map<std::string, std::string> m;
	std::string s1 = "1";
	std::string s2 = "A";

	m.insert(std::pair<std::string, std::string>(s1, s2)); //Error
	
	//HC_ALL_CLASSES.insert(std::pair<std::string, hdecl_class*>("pru_hcell", (hdecl_class*)mc_null));

	std::cout << std::boolalpha;
	std::cout << "is_pt(CLS_A)" << std::is_pointer<CLS_A>::value << '\n';
	std::cout << "is_pt(CLS_A*)" << std::is_pointer<CLS_A*>::value << '\n';
	std::cout << "is_pt(float)" << std::is_pointer<float>::value << '\n';
	std::cout << "is_pt(int)" << std::is_pointer<int>::value << '\n';
	std::cout << "is_pt(int*)" << std::is_pointer<int*>::value << '\n';
	std::cout << "is_pt(int**)" << std::is_pointer<int**>::value << '\n' << "\n";
	
	std::cout << "is_cls(CLS_A)" << std::is_class<CLS_A>::value << '\n';
	std::cout << "is_cls(CLS_A*)" << std::is_class<CLS_A*>::value << '\n';
	std::cout << "is_cls(float)" << std::is_class<float>::value << '\n';
	std::cout << "is_cls(int)" << std::is_class<int>::value << '\n';
	std::cout << "is_cls(int*)" << std::is_class<int*>::value << '\n';
	std::cout << "is_cls(int**)" << std::is_class<int**>::value << '\n' << "\n";
	std::cout << "is_cls(cell)" << std::is_class<cell>::value << '\n';
	std::cout << "is_cls(hc_term)" << std::is_class<hc_term>::value << '\n';
	*/
	
	printf("\n End of Using bj_mcbj_mc_test_5\n");
}

/*
void
pru_hcell::handler(missive* msv){
}

grip ava_pru_hcell;

MCK_DEFINE_MEM_METHODS(pru_hcell, 32, ava_pru_hcell, 0)

void pru_hcell_init_mem_funcs(){
	bj_mgr_all_ava[bj_cell_id(pru_hcell)] = &(ava_pru_hcell);
	bj_mgr_all_acq[bj_cell_id(pru_hcell)] = (mc_alloc_kernel_func_t)pru_hcell::acquire_alloc;
	bj_mgr_all_sep[bj_cell_id(pru_hcell)] = (mc_alloc_kernel_func_t)pru_hcell::separate;
	
	PTD_CK(pru_hcell::ck_cell_id(bj_cell_id(pru_hcell)));
}
*/