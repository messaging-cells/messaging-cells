
#include <stdio.h>

#include "cell.hh"
#include "preload.hh"
#include "hlang.hh"


hc_term		hc_term::HC_NULL_TERM{};

const char*
hc_get_token(hc_syntax_op_t op){
	const char* tok = "INVALID_TOKEN";
	switch(op){
		case hc_comma_op:
			tok = ",";
		break;
		case hc_switch_then_op:
			tok = ">>=";
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
HC_DEFINE_BINARY_OP(>>=, hc_switch_then_op)

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
hc_init_keywords(){
	helse.val = hc_helse_op;
	hbreak.val = hc_hbreak_op;
	hcontinue.val = hc_hcontinue_op;
	hreturn.val = hc_hreturn_op;
}

void 
hc_term::print_term(){
	printf("%s \n", STACK_STR.c_str());
	printf("INVALID_TERM!!!!\n");
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
		printf("%s ", tok);
		if(rgt != mc_null){ rgt->print_term(); }
	break;
	default:
		printf("(");
		if(lft != mc_null){ lft->print_term(); }
		printf(" %s ", tok);
		if(rgt != mc_null){ rgt->print_term(); }
		printf(")");
	break;
	}
}

int func_01(const char* nam, void*){ 
	printf("declar attr = %s \n", nam);
	return 567; 
};

void
pru_hcell::handler(missive* msv){
}

void
hc_term::dbg_func(){
	printf("%s %d\n", __PRETTY_FUNCTION__, __LINE__);
}

std::map<std::string, hdecl_class*> HC_ALL_CLASSES;

//hmethod_def(cls_A1::mth01, hc_term::HC_NULL_TERM);

//hmethod_def(cls_A1, mth01, r1);

//hmethod_def(cls_A1, mth01, (r1 + r2));

hmethod_def(cls_A1, mth01, (
	(r1 = (o1 + o2)),
	(o2 = (r2 + r1)),
	(r1 = r2) = (r4 + r5),
	(o1 = o2) = (o4 + o5),
	o4, o5, 
	hswitch(o1) >>= (
		hcase(o2) >> o3++, 
		hcase(o4) >> ++o5,
		hcase(o1) >> o2
	),
	hif(o3) >> (~ o1 + ! o2),
	helif(o4) >> (o5 && o3),
	hfor(o4) >> (o2 || o3),
	hwhile(o4) >> (o1 & o3),
	hreturn,
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
	(o2 = (r2 + r1))
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
	aa2 = aa3, 
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
	
	hc_init_keywords();
	
	std::cout << "a2b: " << std::is_base_of<CLS_AA, CLS_BB>::value << '\n';
	std::cout << "b2a: " << std::is_base_of<CLS_BB, CLS_AA>::value << '\n';

	cls_A1 aa;
	cls_A2 bb;
	cls_A3 cc;
	
	//CLS_AA AA1;
	CLS_BB BB1;
	
	hc_reference<CLS_AA> ref1{"CLS_AA", "ref1"};
	ref1 = &BB1;
	hc_reference<CLS_BB> ref2{"CLS_BB", "ref2"};
	ref2 = &BB1;
	hc_reference<CLS_BB> ref3{"CLS_BB", "ref3"};
	ref3 = hcast<CLS_AA, CLS_BB>(ref1);
	
	aa.mth01().print_code();
	bb.r1 = &aa;
	bb.rr2 = &aa;
	cc.r3 = &bb;
	cc.rr2 = &bb;
	bb.mth01().print_code();
	cc.mth01().print_code();
	
	printf("IN_MAIN. %s %d\n", __PRETTY_FUNCTION__, __LINE__);
	
	//long xx = o1;
	//printf("\n\n %ld \n", xx);
	
	std::map<std::string, std::string> m;
	std::string s1 = "1";
	std::string s2 = "A";

	m.insert(std::pair<std::string, std::string>(s1, s2)); //Error
	
	//HC_ALL_CLASSES.insert(std::pair<std::string, hdecl_class*>("pru_hcell", (hdecl_class*)mc_null));

	/*
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

grip ava_pru_hcell;

MCK_DEFINE_MEM_METHODS(pru_hcell, 32, ava_pru_hcell, 0)

void pru_hcell_init_mem_funcs(){
	bj_mgr_all_ava[bj_cell_id(pru_hcell)] = &(ava_pru_hcell);
	bj_mgr_all_acq[bj_cell_id(pru_hcell)] = (mc_alloc_kernel_func_t)pru_hcell::acquire_alloc;
	bj_mgr_all_sep[bj_cell_id(pru_hcell)] = (mc_alloc_kernel_func_t)pru_hcell::separate;
	
	PTD_CK(pru_hcell::ck_cell_id(bj_cell_id(pru_hcell)));
}
