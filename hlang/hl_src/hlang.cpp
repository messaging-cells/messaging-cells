
#include <stdio.h>
#include <string.h>
#include "dbg_util.h"
#include "hlang.hh"

long	hc_term::HC_PRT_TERM_INDENT = 0;

long hc_token_current_val = 11;
const char* hc_token_type_nam = "hl_token_t";


hc_system& HLANG_SYS(){
	static hc_system the_sys;
	return the_sys;
}

hclass_reg*
hc_system::get_class_reg(const char* cls, hc_caller_t the_initer){
	std::map<std::string, hclass_reg*>::iterator it;
	it = all_classes.find(cls);
	bool added = false;
	if(it == all_classes.end()){
		hclass_reg* nr = new hclass_reg();
		all_classes[cls] = nr;
		added = true;
		printf("ADDING_CLASS %s\n", cls);
	}
	hclass_reg* cls_reg = all_classes[cls];
	if(added){
		cls_reg->nam = cls;
	}
	if((the_initer != hl_null) && (cls_reg->initer == hl_null)){
		cls_reg->initer = the_initer;
	}
	return cls_reg;
}

void
hc_system::register_method(const char* cls, hc_mth_def* mth, bool is_nucl){
	HL_CK(cls != hl_null);
	HL_CK(mth != hl_null);
	hclass_reg* cls_reg = get_class_reg(cls);
	if(is_nucl){
		if(cls_reg->nucleus != hl_null){
			printf("Nucleus for class %s alredy defined as %s \n", cls_reg->nam.c_str(), mth->get_name()); 
			hl_abort_func(0, "Aborting. Nucleus alredy defined. \n");
		}
		cls_reg->nucleus = mth;
	} else {
		cls_reg->methods.push_front(mth);
	}
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
	HL_CK(obj != hl_null);
	HL_CK(attr != hl_null);
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
	HL_CK(obj != hl_null);
	HL_CK(attr != hl_null);
	hclass_reg* cls_reg = get_class_reg(obj->get_class_name());
	if(! cls_reg->has_reference(attr->get_name())){
		(cls_reg->references)[attr->get_name()] = attr;
		printf("ADDING_REFERENCE %s.%s\n", cls_reg->nam.c_str(), attr->get_name());
	}
}

bool
hc_system::has_token(const char* attr){
	std::map<std::string, hc_term*>::iterator it;
	it = all_token.find(attr);
	return (it != all_token.end());
}

void
hc_system::register_token(hc_term* attr){
	HL_CK(attr != hl_null);
	if(! has_token(attr->get_name())){
		all_token[attr->get_name()] = attr;
		printf("ADDING_TOKEN %s\n", attr->get_name());
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
	HL_CK(attr != hl_null);
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
	HL_CK(attr != hl_null);
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
	if(nucleus != hl_null){
		std::cout << "\tCALLING NUCLEUS " << nucleus->nam << '\n';
		hc_caller_t cr = nucleus->caller;
		(*cr)();
		
		nucleus->print_code();

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
hc_system::init_all_token(){
	std::cout << "---------------------------------------------------------------\n";
	auto it = all_token.begin();
	for(; it != all_token.end(); ++it){
		hc_token_current_val++;
		hc_value<hl_token_t>* tok = (hc_value<hl_token_t>*)(it->second);
		tok->val = hc_token_current_val;
		printf("INITING TOKEN  %s = %ld \n", it->first.c_str(), hc_token_current_val);
		//std::cout << "INITING TOKEN " << it->first << '\n';
	}
}

void
hc_system::init_all_attributes(){
	std::cout << "---------------------------------------------------------------\n";
	auto it = all_classes.begin();
	for(; it != all_classes.end(); ++it){
		std::cout << "ADDING ATTRIBUTES FOR CLASS " << it->first << '\n';
		hc_caller_t cr = it->second->initer;
		if(cr != hl_null){
			(*cr)();
		}
	}
}

const char*
hc_get_token(hc_syntax_op_t op){
	const char* tok = "INVALID_TOKEN";
	switch(op){
		case hc_send_op:
			tok = "hsend";
		break;
		case hc_tell_op:
			tok = "htell";
		break;
		case hc_member_op:
			tok = "->";
		break;
		case hc_comma_op:
			tok = ",";
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
		case hc_async_asig_op:
			tok = "<<=";
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
	//printf("%s \n", STACK_STR.c_str());
	printf("INVALID_TERM!!!!\n");
}


void //static
hc_term::print_indent(){
	HL_CK(HC_PRT_TERM_INDENT >= 0);
	for(long aa = 0; aa < HC_PRT_TERM_INDENT; aa++){
		printf("\t");
	}
}

void 
hc_unary_term::print_term(){
	const char* tok = hc_get_token(op);
	printf("%s", tok);
	printf("(");
	HC_PRT_TERM_INDENT++;
	if(prm != hl_null){ prm->print_term(); }
	HC_PRT_TERM_INDENT--;
	printf(")");
}

void 
hc_binary_term::print_term(){
	const char* tok = hc_get_token(op);
	switch(op){
	case hc_comma_op:
		if(lft != hl_null){ lft->print_term(); }
		printf("%s\n", tok); print_indent();
		if(rgt != hl_null){ rgt->print_term(); }
	break;
	default:
		hc_syntax_op_t lft_op = lft->get_oper();
		hc_syntax_op_t rgt_op = rgt->get_oper();
		printf("("); 
		HC_PRT_TERM_INDENT++;
		
		if(lft_op == hc_comma_op){ printf("("); }
		if(lft != hl_null){ lft->print_term(); }
		if(lft_op == hc_comma_op){ printf(")"); }
		
		printf(" %s ", tok);
		
		if(rgt_op == hc_comma_op){ printf("("); }
		if(rgt != hl_null){ rgt->print_term(); }
		if(rgt_op == hc_comma_op){ printf(")"); }
		
		HC_PRT_TERM_INDENT--;
		printf(")");
	break;
	}
}

void 
hc_send_term::print_term(){
	HL_CK((op == hc_send_op) || (op == hc_tell_op));
	
	const char* tok_str = hc_get_token(op);
	hc_syntax_op_t dst_op = snd_dst->get_oper();
	hc_syntax_op_t tok_op = snd_tok->get_oper();
	hc_syntax_op_t att_op = snd_att->get_oper();
	
	printf(" %s", tok_str);
	
	printf("("); 
	HC_PRT_TERM_INDENT++;
	
	if(dst_op == hc_comma_op){ printf("("); }
	if(snd_dst != hl_null){ snd_dst->print_term(); }
	if(dst_op == hc_comma_op){ printf(")"); }
	
	printf(", ");
	
	if(tok_op == hc_comma_op){ printf("("); }
	if(snd_tok != hl_null){ snd_tok->print_term(); }
	if(tok_op == hc_comma_op){ printf(")"); }

	printf(", ");
	
	if(att_op == hc_comma_op){ printf("("); }
	if(snd_att != hl_null){ snd_att->print_term(); }
	if(att_op == hc_comma_op){ printf(")"); }

	HC_PRT_TERM_INDENT--;
	printf(")");
}

const char*
hcell::get_attr_nm(const char* pfix, const char* sfix){
	static hl_ostringstream result;
	result << pfix << get_class_name() << "_" << sfix;
	const char* rr = strdup(result.str().c_str());
	result.str("");
	//printf("TOK_NM= %s\n", rr);
	return rr;
}

hc_term&
hcell::hsend(hc_term& dst, hc_term& tok, hc_term& att){
	hc_term* tm = new hc_send_term(hc_send_op, &dst, &tok, &att);
	return *tm;
}

hc_term&
hcell::htell(hc_term& dst, hc_term& tok, hc_term& att){
	hc_term* tm = new hc_send_term(hc_tell_op, &dst, &tok, &att);
	return *tm;
}

