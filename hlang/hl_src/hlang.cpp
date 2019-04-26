
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>

#include "sha2.h"
#include "dbg_util.h"
#include "hlang.hh"

#define HL_PATH_MAX PATH_MAX


// =======================================================================================
// GLOBAL

hc_mth_def*	hcell::defining_mth = hl_null;
long	hc_term::HC_PRT_TERM_INDENT = 0;
long	hc_term::HC_NUM_LABEL = 0;

htoken(htk_set);
htoken(htk_get);

// =======================================================================================
// FILE_FUNCTIONS

char PROC_LINK_BUFF[MAX_BUFF_SZ];
char FILE_NAME_BUFF[MAX_BUFF_SZ];

char*
get_file_path(FILE* fp){
	HL_CK(fp != NULL);
	int fno = fileno(fp);
	sprintf(PROC_LINK_BUFF, "/proc/self/fd/%d", fno);
	ssize_t r_sz = readlink(PROC_LINK_BUFF, FILE_NAME_BUFF, MAX_BUFF_SZ);
	if (r_sz < 0){
		fprintf(stderr, "failed to readlink\n");
		exit(1);
	}
	FILE_NAME_BUFF[r_sz] = '\0';
	return strdup(FILE_NAME_BUFF);
}

FILE*
file_open(const char* nm){
	FILE* ff = fopen(nm, "w+");
	if(ff == NULL){
		hl_abort("Cannot open file %s\n", nm);
	}
	return ff;
}

bool
file_rename(hl_string& old_pth, hl_string& nw_pth){
	int ok = rename(old_pth.c_str(), nw_pth.c_str());
	if(ok != 0){
		hl_abort("Cannot rename file %s  to %s \n", old_pth.c_str(), nw_pth.c_str());
	}
	return (ok == 0);
}

bool
file_remove(hl_string& pth){
	int ok = remove(pth.c_str());
	if(ok != 0){
		hl_abort("Cannot remove file %s \n", pth.c_str());
	}
	return (ok == 0);
}

bool
file_exists(hl_string th_pth){
	const char* fname = th_pth.c_str();
	
	bool ff_exists = (access(fname, F_OK) != -1);
	return ff_exists;
}

bool 
file_touch(hl_string the_pth){
	int ok1 = utimensat(AT_FDCWD, the_pth.c_str(), NULL, 0);
	return (ok1 == 0);
}

bool
file_newer_than(hl_string the_pth, time_t tm1){
	struct stat sf1;

	int resp1 = stat(the_pth.c_str(), &sf1);
	bool ok1 = (resp1 == 0);

	double dtm = difftime(sf1.st_mtime, tm1);

	bool nwr_than = ok1 && (dtm > 0);
	return nwr_than;
}

void
file_update(hl_string& tmp_nm, hl_string& hh_nm){
	if(! file_exists(hh_nm)){
		fprintf(stdout, "CREATING FILE: %s \n\n", hh_nm.c_str());
		file_rename(tmp_nm, hh_nm); 
	} else {
		hl_uchar_t tmp_sh2[NUM_BYTES_SHA2];
		hl_memset(tmp_sh2, 0, NUM_BYTES_SHA2);
		
		int ok = sha2_file(tmp_nm.c_str(), tmp_sh2, 0);
		if(ok != 0){
			hl_abort("Cannot calc sha2 of file %s\n", tmp_nm.c_str());
		}
		
		hl_uchar_t old_sh2[NUM_BYTES_SHA2];
		hl_memset(old_sh2, 0, NUM_BYTES_SHA2);
		
		int ok2 = sha2_file(hh_nm.c_str(), old_sh2, 0);
		if(ok2 != 0){
			hl_abort("Cannot calc sha2 of file %s\n", hh_nm.c_str());
		}
		
		int cmp_val = memcmp(tmp_sh2, old_sh2, NUM_BYTES_SHA2);
		if(cmp_val != 0){
			fprintf(stdout, "FILES: \n %s \n %s \n DIFFER. REPLACING old file.\n", 
					tmp_nm.c_str(), hh_nm.c_str());
			
			file_rename(tmp_nm, hh_nm); 
		} else {
			fprintf(stdout, "SKIPPING FILE: %s (IDENTICAL)\n", hh_nm.c_str());
		}
	}
}

bool
make_dir(hl_string the_pth, mode_t mod){
	int resp = mkdir(the_pth.c_str(), mod);
	if(resp != 0){
		hl_abort("Cannot make dir %s \n", the_pth.c_str());
	}
	return (resp == 0);
}

bool
change_dir(hl_string the_pth){
	int resp = chdir(the_pth.c_str());
	if(resp != 0){
		hl_abort("Cannot change dir to %s \n", the_pth.c_str());
	}
	return (resp == 0);
}

hl_string
path_get_running_path(){
	char exepath[HL_PATH_MAX] = {0};
	readlink("/proc/self/exe", exepath, sizeof(exepath) - 1);
	hl_string the_pth = exepath;
	return the_pth;
}

hl_string
path_to_absolute_path(hl_string pth){
	if(pth.size() >= (HL_PATH_MAX - 1)){
		hl_abort("Path %s too long\n", pth.c_str());
	}
	
	char rpath[HL_PATH_MAX];

	char* rr = realpath(pth.c_str(), rpath);
	if(rr == rpath){ 
		hl_string real_pth = rpath;
		return real_pth;
	}
	return pth;
}

bool
path_create(hl_string n_pth){
	int eos = (int)hl_string::npos;
	int pos1 = n_pth.find('/');
	bool path_ok = true;
	while((pos1 == eos) || (pos1 < (int)n_pth.size())){
		if(pos1 == eos){
			pos1 = (int)n_pth.size();
		}

		hl_string nm_dir = n_pth.substr(0, pos1);
		if(nm_dir.size() > 0){
			path_ok = make_dir(nm_dir, 0700);
			/*
			resp = mkdir(nm_dir.c_str(), 0700);
			//path_ok = ((resp == 0) || (errno == EEXIST));
			path_ok = (resp == 0);
			*/
		}

		if((pos1 + 1) < (int)n_pth.size()){
			pos1 = n_pth.find('/', pos1 + 1);
		} else {
			pos1 = (int)n_pth.size();
		}
	}

	return path_ok;
}

bool
path_begins_with(hl_string the_pth, hl_string the_beg){
	if(the_pth.size() < the_beg.size()){ 
		return false; 
	}

	hl_string pref_str = the_pth.substr(0, the_beg.size());
	if(pref_str != the_beg){ 
		return false; 
	}
	return true;
}

bool
path_ends_with(hl_string& the_str, hl_string& the_suf){
	if(the_str.size() < the_suf.size()){
		return false;
	}
	hl_str_pos_t pos1 = the_str.size() - the_suf.size();
	hl_string sub_str = the_str.substr(pos1);
	if(sub_str == the_suf){
		return true;
	}
	return false;
}

hl_string
path_get_directory(hl_string the_pth, bool add_last_dir_sep){
	long pos = (long)the_pth.rfind('/');
	hl_string the_dir = the_pth.substr(0, pos);
	if(add_last_dir_sep){
		the_dir = the_dir + '/';
	}
	return the_dir;
}

hl_string
path_get_name(hl_string the_pth){
	long eos = (long)hl_string::npos;
	long pos = (long)the_pth.rfind('/');
	if(pos == eos){
		return the_pth;
	}
	hl_string the_nm = the_pth.substr(pos + 1);
	return the_nm;
}

hl_string
get_errno_str(long val_errno){
	hl_string out_str = "?ERROR?";
	switch(val_errno){
	case EACCES:		out_str = "EACCES";		break;
	case EBUSY:		out_str = "EBUSY";		break;
	case EFAULT:		out_str = "EFAULT";		break;
	case EINVAL:		out_str = "EINVAL";		break;
	case EISDIR:		out_str = "EISDIR";		break;
	case ELOOP:		out_str = "ELOOP";		break;
	case EMLINK:		out_str = "EMLINK";		break;
	case ENAMETOOLONG:	out_str = "ENAMETOOLONG";	break;
	case ENOENT:		out_str = "ENOENT";		break;
	case ENOMEM:		out_str = "ENOMEM";		break;
	case ENOSPC:		out_str = "ENOSPC";		break;
	case ENOTDIR:		out_str = "ENOTDIR";		break;
	case ENOTEMPTY:		out_str = "ENOTEMPTY";		break;
	case EEXIST:		out_str = "EEXIST";		break;
	case EPERM:		out_str = "EPERM";		break;
	case EROFS:		out_str = "EROFS";		break;
	case EXDEV:		out_str = "EXDEV";		break;
	case EIO:		out_str = "EIO";		break;
	};
	return out_str;
}

// =======================================================================================
// HLANG_SYNTAX_FUNCTIONS

hl_string 
get_upper_str(const hl_string& nam){
	hl_string out = nam;
	std::transform(out.begin(), out.end(), out.begin(), ::toupper);
	return out;
}

hc_system& 
HLANG_SYS(){
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
		fprintf(stdout, "ADDING_CLASS %s\n", cls);
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
	
	HL_CK(mth->my_cls == hl_null);
	mth->my_cls = cls_reg;
	
	if(is_nucl){
		if(cls_reg->nucleus != hl_null){
			hl_abort("Nucleus for class %s alredy defined as %s \n", 
						  cls_reg->nam.c_str(), mth->get_name());
		}
		cls_reg->nucleus = mth;
	} else {
		cls_reg->methods.push_back(mth);
	}
	fprintf(stdout, "ADDING_METHOD %s.%s\n", cls_reg->nam.c_str(), mth->nam);
}

void
hc_system::register_value(hcell* obj, hc_term* attr){
	HL_CK(obj != hl_null);
	HL_CK(attr != hl_null);
	hclass_reg* cls_reg = get_class_reg(obj->get_class_name());
	if(! cls_reg->has_attribute(attr->get_name())){
		if(attr->get_has_safe()){
			cls_reg->safe_values.push_back(attr);
			cls_reg->tot_safe_attrs++;
			attr->set_safe_idx(cls_reg->tot_safe_attrs);
		} else {
			cls_reg->values.push_back(attr);
		}
		fprintf(stdout, "ADDING_VALUE %s.%s\n", cls_reg->nam.c_str(), attr->get_name());
	}
}

void
hc_system::register_reference(hcell* obj, hc_term* attr){
	HL_CK(obj != hl_null);
	HL_CK(attr != hl_null);
	hclass_reg* cls_reg = get_class_reg(obj->get_class_name());
	if(! cls_reg->has_attribute(attr->get_name())){
		if(attr->get_has_safe()){
			cls_reg->safe_references.push_back(attr);
			cls_reg->tot_safe_attrs++;
			attr->set_safe_idx(cls_reg->tot_safe_attrs);
		} else {
			cls_reg->references.push_back(attr);
		}
		fprintf(stdout, "ADDING_REFERENCE %s.%s\n", cls_reg->nam.c_str(), attr->get_name());
	}
}

bool
hc_system::has_address(const char* attr){
	std::map<std::string, hc_term*>::iterator it;
	it = all_glb_address.find(attr);
	return (it != all_glb_address.end());
}

void
hc_system::register_address(hc_term* attr){
	HL_CK(attr != hl_null);
	if(! has_address(attr->get_name())){
		all_glb_address[attr->get_name()] = attr;
		fprintf(stdout, "ADDING_ADDRESS %s\n", attr->get_name());
	}
}

hc_term&
hc_system::add_tok(const char* nm){
	HL_CK(nm != hl_null);
	hc_global* pt_glb = hl_null;
	
	auto it = all_glb_token.find(nm);
	if(it != all_glb_token.end()){
		hl_abort("Token already added %s\n", nm);
	}
	pt_glb = new hc_global(nm);
	all_glb_token[nm] = pt_glb;
	fprintf(stdout, "ADDING_GLB_TOKEN %s\n", nm);
	return *pt_glb;
}

hc_term&
hc_system::get_tok(const char* nm){
	HL_CK(nm != hl_null);
	hc_global* pt_glb = hl_null;
	
	auto it = all_glb_token.find(nm);
	if(it == all_glb_token.end()){
		hl_abort("Token %s not existant. Maybe try without quotes?\n", nm);
	} 
	pt_glb = it->second;
	return *pt_glb;
}

hc_term&
hc_system::add_con(const char* nm, const char* val){
	HL_CK(nm != hl_null);
	hc_global* pt_glb = hl_null;
	
	auto it = all_glb_const.find(nm);
	if(it != all_glb_const.end()){
		hl_abort("Constant already added %s\n", nm);
		//return false;
	}
	pt_glb = new hc_global(nm);
	pt_glb->val = val;
	all_glb_const[nm] = pt_glb;
	fprintf(stdout, "ADDING_GLB_CONSTANT %s\n", nm);
	return *pt_glb;
}

hc_term&
hc_system::get_con(const char* nm){
	HL_CK(nm != hl_null);
	hc_global* pt_glb = hl_null;
	
	auto it = all_glb_const.find(nm);
	if(it == all_glb_const.end()){
		hl_abort("Constant %s not existant. Maybe try without quotes?\n", nm);
	} 
	pt_glb = it->second;
	return *pt_glb;
}

void
hclass_reg::call_all_methods(){
	tot_steps = 0;

	hc_term::HC_NUM_LABEL++;
	HL_CK(mth_handler_return_step == 0);
	mth_handler_return_step = hc_term::HC_NUM_LABEL;
	
	hc_term::HC_NUM_LABEL++;
	HL_CK(mth_safe_wait_step == 0);
	mth_safe_wait_step = hc_term::HC_NUM_LABEL;
	
	hc_term::HC_NUM_LABEL++;
	HL_CK(mth_call_num_step == 0);
	mth_call_num_step = hc_term::HC_NUM_LABEL;
	
	hc_term::HC_NUM_LABEL++;
	HL_CK(mth_ret_num_step == 0);
	mth_ret_num_step = hc_term::HC_NUM_LABEL;
	
	auto it = methods.begin();
	for(; it != methods.end(); ++it){
		hc_mth_def* mth_df = (*it);
		hc_caller_t cr = mth_df->caller;
		(*cr)();
		
		mth_df->set_num_label();
		
		mth_df->print_text_code(stdout);

		tot_steps += mth_df->num_steps;
		fprintf(stdout, "-------------------------------------------(%ld steps)\n", mth_df->num_steps);
	}
	if(nucleus != hl_null){
		fprintf(stdout, "\tCALLING NUCLEUS %s\n", nucleus->nam);
		hc_caller_t cr = nucleus->caller;
		(*cr)();
		
		nucleus->set_num_label();
		
		nucleus->print_text_code(stdout);

		tot_steps += nucleus->num_steps;
		fprintf(stdout, "-------------------------------------------(%ld steps)\n", nucleus->num_steps);
	}
}

void
hc_system::call_all_registered_methods(){
	auto it = all_classes.begin();
	for(; it != all_classes.end(); ++it){
		fprintf(stdout, "===========================================================\n");
		hclass_reg* cls_reg = it->second;
		
		fprintf(stdout, "CALLING METHODS FOR CLASS %s\n", it->first.c_str());
		cls_reg->call_all_methods();
		
		cls_reg->init_depth();
		fprintf(stdout, "---- %s depth %ld tot_steps %ld\n", 
				it->first.c_str(), cls_reg->depth, cls_reg->tot_steps);
	}
	fprintf(stdout, "===========================================================\n");
}

void
hc_system::init_sys(){
	init_all_attributes();
	init_all_token();
	call_all_registered_methods();
}

void
hc_system::init_all_token(){
	fprintf(stdout, "---------------------------------------------------------------\n");;
	long token_current_val = first_token_val;
	auto it = all_glb_token.begin();
	for(; it != all_glb_token.end(); ++it){
		token_current_val++;
		hc_global* tok = (hc_global*)(it->second);
		tok->val = std::to_string(token_current_val);
		fprintf(stdout, "INITING TOKEN  %s = %ld \n", it->first.c_str(), token_current_val);
	}
}

void
hc_system::init_all_attributes(){
	fprintf(stdout, "---------------------------------------------------------------\n");
	auto it = all_classes.begin();
	for(; it != all_classes.end(); ++it){
		fprintf(stdout, "ADDING ATTRIBUTES FOR CLASS %s \n", it->first.c_str());
		hc_caller_t cr = it->second->initer;
		if(cr != hl_null){
			(*cr)();
		}
	}
}

bool
hc_is_cond_oper(hc_syntax_op_t op){
	bool is_co = false;
	switch(op){
		case hc_hfor_op:
		case hc_hwhile_op:
		case hc_hif_op:
		case hc_helif_op:
		case hc_helse_op:
		case hc_hswitch_op:
		case hc_hcase_op:
		case hc_hdefault_op:
			is_co = true;
		break;
		default:
		break;
	}
	return is_co;
}

bool
hc_can_start_cond_steps(hc_syntax_op_t op1){
	bool can_strt = false;
	switch(op1){
		case hc_hfor_op:
		case hc_hwhile_op:
		case hc_hif_op:
		case hc_hswitch_op:
		case hc_hcase_op:
			can_strt = true;
			break;
		default:
		break;
	}
	return can_strt;
}

bool
hc_can_add_cond_opers(hc_syntax_op_t op1, hc_syntax_op_t op2){
	bool can_add = false;
	switch(op1){
		case hc_hfor_op:
		case hc_hwhile_op:
		case hc_helse_op:
		case hc_hswitch_op:
		case hc_hdefault_op:
			break;
		case hc_hif_op:
		case hc_helif_op:
			can_add = ((op2 == hc_helif_op) || (op2 == hc_helse_op));
			break;
		case hc_hcase_op:
			can_add = ((op2 == hc_hcase_op) || (op2 == hc_hdefault_op));
			break;
		default:
		break;
	}
	return can_add;
}

bool
hc_is_assig_oper(hc_syntax_op_t op){
	bool is_as = false;
	switch(op){
		case hc_assig_op1:
		case hc_assig_op2:
		case hc_assig_op3:
		case hc_assig_op4:
		case hc_assig_op5:
			is_as = true;
		break;
		default:
		break;
	}
	return is_as;
}

const char*
hc_get_token(hc_syntax_op_t op){
	const char* tok = "INVALID_TOKEN";
	switch(op){
		case hc_safe_check_op:
			tok = "hc_safe_check_op";
		break;
		case hc_hmsg_tok_op:
			tok = "hc_hmsg_tok_op";
		break;
		case hc_hmsg_val_op:
			tok = "hc_hmsg_val_op";
		break;
		case hc_mth_call_op:
			tok = "hc_mth_call_op";
		break;
		case hc_mth_def_op:
			tok = "hc_mth_def_op";
		break;
		case hc_mth_ret_op:
			tok = "hc_mth_ret_op";
		break;
		case hc_dbg_op:
			tok = "hdbg";
		break;
		case hc_send_op:
			tok = "hsend";
		break;
		case hc_safe_send_op:
			tok = "hsafe_send";
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
		case hc_hfor_op:
			tok = "hfor";
		break;
		case hc_hwhile_op:
			tok = "hwhile";
		break;
		case hc_hif_op:
			tok = "hif";
		break;
		case hc_helif_op:
			tok = "helif";
		break;
		case hc_helse_op:
			tok = "helse";
		break;
		case hc_hswitch_op:
			tok = "hswitch";
		break;
		case hc_hcase_op:
			tok = "hcase";
		break;
		case hc_hdefault_op:
			tok = "hdefault";
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
		case hc_habort_op:
			tok = "habort";
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

const char*
hc_get_cpp_token(hc_syntax_op_t op){
	const char* tok = "INVALID_TOKEN";
	switch(op){
		case hc_safe_check_op:
			tok = "hc_safe_check_op";
		break;
		case hc_hmsg_tok_op:
			tok = "hmsg_tok";
		break;
		case hc_hmsg_val_op:
			tok = "hmsg_val";
		break;
		case hc_mth_call_op:
			tok = "hc_mth_call_op";
		break;
		case hc_mth_def_op:
			tok = "hc_mth_def_op";
		break;
		case hc_mth_ret_op:
			tok = "hc_mth_ret_op";
		break;
		case hc_dbg_op:
			tok = "hdbg";
		break;
		case hc_send_op:
			tok = "send_val";
		break;
		case hc_safe_send_op:
			tok = "safe_send_val";
		break;
		case hc_member_op:
			tok = "->";
		break;
		case hc_comma_op:
			tok = "; /* , */";
		break;
		case hc_then_op:
			tok = "/* >> */";
		break;
		case hc_hme_op:
			tok = "hme";
		break;
		case hc_hfor_op:
			tok = "/* hfor */ if";
		break;
		case hc_hwhile_op:
			tok = "/* hwhile */ if";
		break;
		case hc_hif_op:
			tok = "/* hif */ if";
		break;
		case hc_helif_op:
			tok = "/* helif */ if";
		break;
		case hc_helse_op:
			tok = "/* helse */";
		break;
		case hc_hswitch_op:
			tok = "hswitch";
		break;
		case hc_hcase_op:
			tok = "/* hcase */ if";
		break;
		case hc_hdefault_op:
			tok = "/* hdefault */";
		break;
		case hc_hbreak_op:
			tok = "/* hbreak */";
		break;
		case hc_hcontinue_op:
			tok = "/* hcontinue */";
		break;
		case hc_hreturn_op:
			tok = "/* hreturn */";
		break;
		case hc_habort_op:
			tok = "habort";
		break;
		case hc_assig_op1:
			tok = "/* =1 */ = ";
		break;
		case hc_assig_op2:
			tok = "/* =2 */ = ";
		break;
		case hc_assig_op3:
			tok = "/* =3 */ = ";
		break;
		case hc_assig_op4:
			tok = "/* =4 */ = ";
		break;
		case hc_assig_op5:
			tok = "/* =5 */ = ";
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

int
hc_get_num_flag(hc_syntax_op_t op){
	int nf = hl_invalid_bit;
	switch(op){
		case hc_hbreak_op:
			nf = hl_has_break_bit;
		break;
		case hc_hcontinue_op:
			nf = hl_has_continue_bit;
		break;
		case hc_hreturn_op:
			nf = hl_has_return_bit;
		break;
		case hc_habort_op:
			nf = hl_has_abort_bit;
		break;
		case hc_hcase_op:
			nf = hl_has_case_bit;
		break;
		default:
		break;
	}
	HL_CK(nf != hl_invalid_bit);
	return nf;
}

void
ck_is_not_cond(hc_term& o1){
	if(hc_is_cond_oper(o1.get_oper())){
		fprintf(stderr, "---------------------------------------------------\n");
		fprintf(stderr, "NEAR\n");
		fprintf(stderr, "---------------------------------------------------\n");
		o1.print_term(stderr);
		fprintf(stderr, "---------------------------------------------------\n");
		hl_abort("Parameter %s to comma \",\" cannot be a conditional.\n", o1.get_name());
	}
}

void
hc_steps::set_back_next(hc_term& o1){
	HL_CK(! steps.empty());
	hc_term* lst = steps.back();
	lst->set_next(o1);
	if((first_if != hl_null) && o1.is_if_closer()){
		hc_term* fst_tm = first_if;
		first_if = hl_null;
		fst_tm->set_last(o1);
	}
}

void
hc_steps::append_safe_check(hc_term& stp_tm){
	
	hl_safe_bits_t safe_patt = 0;
	hcell* owr = hl_null;
	stp_tm.get_safe_attributes(safe_patt, owr);
	HL_CK(safe_patt != 0);
	HL_CK(owr != hl_null);
	
	hc_safe_check* ck_tm = new hc_safe_check(safe_patt, stp_tm, owr);
	
	if(! steps.empty()){
		set_back_next(*ck_tm);
	}
	steps.push_back(ck_tm);
	num_steps++;
}

hc_steps*
hc_term::to_steps(){
	if(! is_compound()){
		hl_abort("Step %s is not statement. A step must be a statement.\n", get_name());
	}
	hc_term* pt_tm = this;
	hc_steps* sts = hl_null;
	if(get_oper() == hc_comma_op){
		sts = (hc_steps*)pt_tm;
	} else {
		sts = new hc_steps(); 
		
		if(pt_tm->get_has_safe()){
			HL_CK(sts->steps.empty());
			sts->append_safe_check(*pt_tm);
			sts->set_back_next(*pt_tm);
		}
		
		sts->steps.push_back(pt_tm);
		sts->num_steps += num_steps + 1;
		if(pt_tm->get_cond_oper() == hc_hif_op){
			HL_CK(sts->first_if == hl_null);
			sts->first_if = pt_tm;
		}
	}
	HL_CK(sts != hl_null);
	return sts;
}

void
hc_steps::append_term(hc_term& o1){
	if(! o1.is_compound()){
		hl_abort("Step %s is not statement. A step must be a statement.\n", o1.get_name());
	}

	if(o1.get_has_safe()){
		HL_CK(! steps.empty());
		append_safe_check(o1);
	}
	
	set_back_next(o1);
	steps.push_back(&o1);
	num_steps += o1.num_steps + 1;
	if(o1.get_cond_oper() == hc_hif_op){
		HL_CK(first_if == hl_null);
		first_if = &o1;
	}
}

hc_term& 
hc_term::operator , (hc_term& o1) { 
	ck_is_not_cond(*this);
	ck_is_not_cond(o1);
	bool has_st;
	ck_closed_param(this, this, has_st);
	ck_closed_param(&o1, this, has_st);
	
	hc_steps* sts = to_steps();
	
	if(sts->is_cond() && o1.is_cond()){
		hc_syntax_op_t op1 = sts->get_cond_oper();
		hc_syntax_op_t op2 = o1.get_cond_oper();
		bool cadd = hc_can_add_cond_opers(op1, op2);
		if(! hc_can_start_cond_steps(op2) && ! cadd){
			hl_abort("Cannot add %s oper to %s oper.\n", hc_get_token(op2), hc_get_token(op1));
		}
	}
	
	sts->append_term(o1);
	
	return *sts; 
}

hc_term& 
hc_term::operator >> (hc_term& o1) { 
	if(! hc_is_cond_oper(get_oper())){
		fprintf(stderr, "---------------------------------------------------\n");
		fprintf(stderr, "NEAR\n");
		fprintf(stderr, "---------------------------------------------------\n");
		print_term(stderr);
		fprintf(stderr, "---------------------------------------------------\n");
		hl_abort("First parameter %s to then \">>\" must be a conditional.\n", get_name());
	}
	hc_steps* sts = o1.to_steps();
	hc_condition* tm = new hc_condition(this, sts);
	if(get_oper() == hc_hfor_op){
		hc_for_loop* for_tm = (hc_for_loop*)this;
		for_tm->owner = tm;
	}
	return *tm;
}


hc_term& 
hc_term::operator = (hc_term& o1) { 
	HC_DEFINE_ASSIG_BASE(hc_assig_op1);
}

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

hc_term& 
hc_term::operator ++ (int){
	hc_term* tm = new hc_unary_term(hc_post_inc_op, this);
	return *tm;
}

hc_term& 
hc_term::operator -- (int){
	hc_term* tm = new hc_unary_term(hc_post_dec_op, this);
	return *tm;
}

hc_term& 
hdbg(const char* the_code){ 
	hc_term* tm = new hc_dbg(the_code); 
	return *tm; 
} 

hc_term&
hfor(hc_term& the_cond, hc_term& the_end_each_loop){
	if(the_cond.has_statements()){
		hl_abort("Condition %s to hfor has statements. Invalid grammar.\n",
					the_cond.get_name());
	}
	
	hc_steps* sts_end = the_end_each_loop.to_steps();
	hc_term* tm = new hc_for_loop(&the_cond, sts_end);
	return *tm;
}


HC_DEFINE_FUNC_OP(hwhile, hc_unary_term, hc_hwhile_op)
HC_DEFINE_FUNC_OP(hif, hc_unary_term, hc_hif_op)
HC_DEFINE_FUNC_OP(helif, hc_unary_term, hc_helif_op)
HC_DEFINE_FUNC_OP(hswitch, hc_unary_term, hc_hswitch_op)
HC_DEFINE_FUNC_OP(hcase, hc_case_term, hc_hcase_op)

long 
hc_mth_def::calc_depth(){
	long maxd = 0;
	HL_CK(! defining);
	defining = true;
	auto it1 = calls.begin();
	for(; it1 != calls.end(); ++it1){
		hc_mth_def* cll = (*it1);
		if(cll->defining){
			hl_abort("Cannot have recursive methods in hlang. Already defining %s.\n", cll->get_name());
		}
		long dd = cll->calc_depth();
		if(dd > maxd){
			maxd = dd;
		}
	}
	defining = false;
	return (maxd + 1);
}

void
hclass_reg::init_depth(){
	long maxd = 0;
	auto it1 = methods.begin();
	for(; it1 != methods.end(); ++it1){
		hc_mth_def* cll = (*it1);
		long dd = cll->calc_depth();
		if(dd > maxd){
			maxd = dd;
		}
	}
	depth = maxd;
}

bool
hdbg_txt_pre_hh(const char* cls, const char* cod){
	HL_CK(cls != hl_null);
	hclass_reg* cls_reg = HLANG_SYS().get_class_reg(cls);
	if(cls_reg->pre_hh_cod == hl_null){
		cls_reg->pre_hh_cod = cod;
	} else {
		hl_abort("pre_hh_cod for %s already defined\n", cls);
	}
	return true;
}

bool
hdbg_txt_pos_hh(const char* cls, const char* cod){
	HL_CK(cls != hl_null);
	hclass_reg* cls_reg = HLANG_SYS().get_class_reg(cls);
	if(cls_reg->pos_hh_cod == hl_null){
		cls_reg->pos_hh_cod = cod;
	} else {
		hl_abort("pos_hh_cod for %s already defined\n", cls);
	}
	return true;
}

bool
hdbg_txt_pre_cpp(const char* cls, const char* cod){
	HL_CK(cls != hl_null);
	hclass_reg* cls_reg = HLANG_SYS().get_class_reg(cls);
	if(cls_reg->pre_cpp_cod == hl_null){
		cls_reg->pre_cpp_cod = cod;
	} else {
		hl_abort("pre_cpp_cod for %s already defined\n", cls);
	}
	return true;
}

bool
hdbg_txt_pos_cpp(const char* cls, const char* cod){
	HL_CK(cls != hl_null);
	hclass_reg* cls_reg = HLANG_SYS().get_class_reg(cls);
	if(cls_reg->pos_cpp_cod == hl_null){
		cls_reg->pos_cpp_cod = cod;
	} else {
		hl_abort("pos_cpp_cod for %s already defined\n", cls);
	}
	return true;
}

const char*
hcell::get_attr_nm(const char* pfix, const char* sfix){
	static hl_ostringstream result;
	result << pfix << get_class_name() << "_" << sfix;
	const char* rr = strdup(result.str().c_str());
	result.str("");
	return rr;
}

hc_term&
hcell::hsend(hc_term& dst, hc_term& tok, hc_term& att){
	hc_term* tm = new hc_send_term(hc_send_op, &dst, &tok, &att);
	return *tm;
}

hc_term&
hcell::hsafe_send(hc_term& dst, hc_term& tok, hc_term& att){
	hc_term* tm = new hc_send_term(hc_safe_send_op, &dst, &tok, &att);
	return *tm;
}

// =======================================================================================
// HLANG_TEXT_PRINTING

long
hc_term::get_num_label(){
	long num_lb = get_first_step()->num_label;
	HL_CK(num_lb != 0);
	return num_lb;
}

void
hc_term::print_label(FILE *st){
	//fprintf(st, "STEP_%ld", get_num_label());
	fprintf(st, "(%p)_%ld", (void*)get_first_step(), get_num_label());
}
	
int
hc_term::print_term(FILE *st){
	hl_abort("INVALID_TERM !!!!\n");
	return 0;
}

void // static
hc_term::print_new_line(FILE *st){
	fprintf(st, "\n");
}

void // static
hc_term::print_indent(FILE *st){
	HL_CK(HC_PRT_TERM_INDENT >= 0);
	for(long aa = 0; aa < HC_PRT_TERM_INDENT; aa++){
		fprintf(st, "\t");
	}
}

int
hc_unary_term::print_term(FILE *st){
	const char* tok = hc_get_token(op);
	fprintf(st, "%s", tok);
	fprintf(st, "(");
	HC_PRT_TERM_INDENT++;
	if(prm != hl_null){ prm->print_term(st); }
	HC_PRT_TERM_INDENT--;
	fprintf(st, ")");
	
	return 0;
}

int
hc_case_term::print_term(FILE *st){
	const char* tok = hc_get_token(op);
	HL_CK(prm != hl_null);

	fprintf(st, "%s", tok);
	fprintf(st, "(");
	HC_PRT_TERM_INDENT++;
	if(prm != hl_null){ prm->print_term(st); }
	fprintf(st, " sw== ");
	
	if(the_sw_eq == hl_null){
		hl_abort("\n\n hcase outside of a hswitch.\n");
	}
	if(the_sw_eq != hl_null){ the_sw_eq->print_term(st); }
	HC_PRT_TERM_INDENT--;
	fprintf(st, ")");
	
	return 0;
}

int
hc_steps::print_term(FILE *st){
	bool is_fst = true;
	//fprintf(st, "(");
	
	auto it = steps.begin();
	for(; it != steps.end(); ++it){
		if(is_fst){ is_fst = false; } 
		else { fprintf(st, " ,"); }
		hc_term* tm = (*it);
		HL_CK(tm != hl_null);
		
		print_new_line(st);
		tm->print_label(st);
		bool hsf = tm->get_has_safe();
		if(hsf){
			fprintf(st, "#");
		} else {
			fprintf(st, ":");
		}
		fprintf(st, "\t");
		
		hc_term::print_indent(st);
		tm->print_term(st);
		
		hc_syntax_op_t c_op = tm->get_oper();
		if(c_op != hc_then_op){
			fprintf(st, "\t[");
			if(tm->next != hl_null){
				tm->next->print_label(st);
			}
			fprintf(st, "]");
		}
	}
	//fprintf(st, ")");
	return 0;
}

void
hc_steps::set_num_label(){
	auto it = steps.begin();
	for(; it != steps.end(); ++it){
		hc_term* tm = (*it);
		HL_CK(tm != hl_null);
		hc_term::HC_NUM_LABEL++;
		tm->num_label = hc_term::HC_NUM_LABEL;
		tm->set_num_label();
	}
}

int
hc_condition::print_term(FILE *st){
	const char* tok = hc_get_token(hc_then_op);
	hc_term* tm1 = cond;
	hc_term* tm2 = if_true;
	
	HL_CK(tm1 != hl_null);
	HL_CK(tm2 != hl_null);
	
	fprintf(st, "("); 
	hc_term::HC_PRT_TERM_INDENT++;
	
	tm1->print_term(st);
	
	fprintf(st, " %s ", tok);
	fprintf(st, " T[");
	if_true->print_label(st);
	fprintf(st, "]");
	fprintf(st, " F[");
	if(next != hl_null){
		next->print_label(st);
	}
	fprintf(st, "]");
	
	
	tm2->print_term(st);
	
	hc_term::HC_PRT_TERM_INDENT--;
	fprintf(st, ")");
	
	return 0;
}

int
hc_for_loop::print_term(FILE *st){
	const char* tok = hc_get_token(get_oper());
	HL_CK(owner != hl_null);
	HL_CK(cond != hl_null);
	HL_CK(end_each_loop != hl_null);
	
	fprintf(st, "%s", tok);
	fprintf(st, "(");
	HC_PRT_TERM_INDENT++;
	cond->print_term(st);
	fprintf(st, "  _,_  ");
	end_each_loop->print_term(st);
	HC_PRT_TERM_INDENT--;
	fprintf(st, ")");

	return 0;
}

int
hc_binary_term::print_term(FILE *st){
	const char* tok = hc_get_token(op);
	HL_CK(lft != hl_null);
	HL_CK(rgt != hl_null);
	HL_CK(op != hc_comma_op);
	HL_CK(op != hc_then_op);
	
	fprintf(st, "("); 
	hc_term::HC_PRT_TERM_INDENT++;
	
	lft->print_term(st);
	
	fprintf(st, " %s ", tok);
	
	rgt->print_term(st);
	
	hc_term::HC_PRT_TERM_INDENT--;
	fprintf(st, ")");

	return 0;
}


int
hc_send_term::print_term(FILE *st){
	HL_CK((op == hc_send_op) || (op == hc_safe_send_op));
	
	const char* tok_str = hc_get_token(op);
	
	fprintf(st, " %s", tok_str);
	
	fprintf(st, "("); 
	HC_PRT_TERM_INDENT++;
	
	if(snd_dst != hl_null){ snd_dst->print_term(st); }
	
	fprintf(st, ", ");
	
	if(snd_tok != hl_null){ snd_tok->print_term(st); }

	fprintf(st, ", ");
	
	if(snd_att != hl_null){ snd_att->print_term(st); }

	HC_PRT_TERM_INDENT--;
	fprintf(st, ")");

	return 0;
}

// =======================================================================================
// LINK_CONTROL_STRUCTURES

void
hc_steps::set_next(hc_term& nxt){
	HL_CK(! steps.empty());
	hc_term* tm = steps.back();
	tm->set_next(nxt);
	//fprintf(stdout, "\n setting_back_next for %p with %p \n", (void*)tm, (void*)(&nxt));
	//fprintf(stdout, "%s \n", HL_STACK_STR.c_str());
}

void
hc_steps::set_last(hc_term& nxt){
	if(get_has_last()){
		return;
	}
	set_has_last();
	
	auto it = steps.begin();
	for(; it != steps.end(); ++it){
		hc_term* tm = (*it);
		HL_CK(tm != hl_null);
		tm->set_last(nxt);
	}
	set_next(nxt);
}

void
hc_term::set_next(hc_term& nxt){
	HL_CK_PRT((next == hl_null), "%d\n", (printf("GGGGG"), print_term(stderr)));
	HL_CK(next == hl_null);
	next = &nxt;
}
	
void
hc_term::set_last(hc_term& nxt){
	// Leave empty
}

void
hc_condition::set_next(hc_term& nxt){
	hc_syntax_op_t op = get_cond_oper();
	hc_term& th = *this;
	switch(op){
		case hc_hfor_op:{
			next = &nxt;
			
			HL_CK(cond != hl_null);
			hc_for_loop& for_cond = *((hc_for_loop*)cond);
			HL_CK(for_cond.end_each_loop != hl_null);
			hc_term& for_end = *(for_cond.end_each_loop);
			
			for_end.set_last(th);
			
			HL_CK(if_true != hl_null);
			if_true->set_last(for_end);
			
			if_true->set_jumps(hc_hbreak_op, nxt);
			if_true->set_jumps(hc_hcontinue_op, th);
		}
		break;
		case hc_hwhile_op:{
			next = &nxt;
			HL_CK(if_true != hl_null);
			if_true->set_last(th);

			if_true->set_jumps(hc_hbreak_op, nxt);
			if_true->set_jumps(hc_hcontinue_op, th);
		}
		break;
		case hc_hif_op:
		case hc_helif_op:
		case hc_helse_op:
			next = &nxt;
		break;
		case hc_hswitch_op:{
			HL_CK(if_true != hl_null);
			if_true->set_last(nxt);
			
			HL_CK(cond != hl_null);
			hc_unary_term* cnd = (hc_unary_term*)cond;
			HL_CK(cnd->prm != hl_null);
			
			if_true->set_jumps(hc_hcase_op, *(cnd->prm));
		}
		break;
		case hc_hcase_op:
		case hc_hdefault_op:
			next = &nxt;
		break;
		default:
		break;
	}
}

void
hc_safe_check::set_next(hc_term& nxt){
	HL_CK(next != hl_null);
}

void
hc_safe_check::set_last(hc_term& nxt){
	HL_CK(next != hl_null);
	hc_syntax_op_t op = next->get_cond_oper();
	if((op == hc_helif_op) || (op == hc_helse_op)){
		fprintf(stdout, "\n setting_safe_nxt_last %p with %p \n", (void*)next, (void*)(&nxt));
		next->set_last(nxt);
	}
}

void
hc_condition::set_last(hc_term& nxt){
	if(get_has_last()){
		return;
	}
	set_has_last();

	hc_syntax_op_t op = get_cond_oper();
	switch(op){
		case hc_hif_op:
		case hc_helif_op:
		case hc_helse_op:
			if_true->set_last(nxt);
			if(next != &nxt){
				HL_CK(next != hl_null);
				HL_CK(next->is_cond());
				next->set_last(nxt);
			}
		break;
		case hc_hswitch_op:
		case hc_hcase_op:
		case hc_hdefault_op:
			HL_CK(if_true != hl_null);
			if_true->set_last(nxt);
		break;
		case hc_hwhile_op:
		case hc_hfor_op:
		default:
		break;
	}
}

void
hc_term::set_jumps(hc_syntax_op_t the_op, hc_term& nxt){
	// Leave empty
}
	
void
hc_steps::set_jumps(hc_syntax_op_t the_op, hc_term& nxt){
	int flg = hc_get_num_flag(the_op);
	if(get_flag(flg)){
		return;
	}
	set_flag(flg);
	
	auto it = steps.begin();
	for(; it != steps.end(); ++it){
		hc_term* tm = (*it);
		HL_CK(tm != hl_null);
		tm->set_jumps(the_op, nxt);
	}
}

void
hc_case_term::set_jumps(hc_syntax_op_t the_op, hc_term& nxt){
	if(the_op != hc_hcase_op){
		return;
	}
	
	int flg = hc_get_num_flag(the_op);
	if(get_flag(flg)){
		return;
	}
	set_flag(flg);
	
	HL_CK(get_oper() == hc_hcase_op);
	HL_CK(the_sw_eq == hl_null);
	the_sw_eq = &nxt;
}

void
hc_condition::set_jumps(hc_syntax_op_t the_op, hc_term& nxt){
	int flg = hc_get_num_flag(the_op);
	if(get_flag(flg)){
		return;
	}
	set_flag(flg);
	
	if(get_cond_oper() == hc_hcase_op){
		cond->set_jumps(the_op, nxt);
		return;
	}
	
	if_true->set_jumps(the_op, nxt);
}

void
hc_keyword::set_jumps(hc_syntax_op_t the_op, hc_term& nxt){
	if(the_op != op){
		return;
	}
	if(the_op == hc_hcase_op){
		return;
	}
	
	int flg = hc_get_num_flag(the_op);
	if(get_flag(flg)){
		return;
	}
	set_flag(flg);

	fprintf(stderr, "SETTING %s to %s \n", hc_get_token(op), nxt.get_name());
	
	next = &nxt;
}
	
hc_mth_ret::hc_mth_ret(hc_mth_def* mthdef){
	HL_CK(mthdef != hl_null);
	the_mth = mthdef;
	nam = "ret_";
	nam.append(the_mth->get_name());
}

const char*
hc_mth_ret::get_name(){
	return nam.c_str();
}

// =======================================================================================
// CPP_CODE_GENERATION

void
hc_system::generate_hh_files(){
	auto it = all_classes.begin();
	for(; it != all_classes.end(); ++it){
		it->second->print_hh_file();
	}
}

void
hc_system::generate_cpp_files(){
	auto it = all_classes.begin();
	for(; it != all_classes.end(); ++it){
		it->second->print_cpp_file();
	}
}

void
hc_system::generate_cpp_code(){
	hl_string cpp_dr = get_cpp_dir_name();
	if(! file_exists(cpp_dr)){
		make_dir(cpp_dr);
	}
	change_dir(cpp_dr);
	print_hh_file();
	print_glbs_hh_file();
	print_glbs_cpp_file();
	generate_hh_files();
	generate_cpp_files();
}

void
hc_system::print_hh_file(){
	hl_string tmp_nm = get_tmp_hh_name();
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
	FILE* ff = file_open(tmp_nm.c_str());
	hl_string df_str = get_hh_define_str().c_str();

	fprintf(ff, "#ifndef %s\n", df_str.c_str());
	fprintf(ff, "#define %s\n", df_str.c_str());
		
	fprintf(ff, "\n");
	auto it = all_classes.begin();
	for(; it != all_classes.end(); ++it){
		hclass_reg* cls_rg = it->second;
		hl_string hh_nm = cls_rg->get_hh_name();
		fprintf(ff, "#include \"%s\"\n", hh_nm.c_str());
	}
	fprintf(ff, "\n");
	
	fprintf(ff, "#endif // %s\n", df_str.c_str());
	
	fclose(ff);
	
	hl_string hh_nm = get_hh_name();
	file_update(tmp_nm, hh_nm);
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
}

void
hc_system::print_glbs_hh_file(){
	hl_string tmp_nm = get_glbs_tmp_hh_name();
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
	FILE* ff = file_open(tmp_nm.c_str());
	hl_string df_str = get_glbs_hh_define_str().c_str();

	fprintf(ff, "#ifndef %s\n", df_str.c_str());
	fprintf(ff, "#define %s\n", df_str.c_str());
	
	fprintf(ff, "\n");
	fprintf(ff, "#include \"cell.hh\"\n");
		
	fprintf(ff, "\n");
	auto it1 = all_classes.begin();
	for(; it1 != all_classes.end(); ++it1){
		const char* cls_nm = it1->first.c_str();
		fprintf(ff, "class %s;\n", cls_nm);
	}
	fprintf(ff, "\n");

	fprintf(ff, R"base(
#define hg_inline_fn mc_inline_fn
		
class hg_missive;
		
typedef mck_token_t hg_token_t;
typedef uint64_t hg_replies_bits_t;
typedef uint64_t hg_value_t; 
typedef long hg_id_t; 
typedef long hg_step_t; 
typedef uint8_t hg_bit_t; 
typedef uint8_t hg_idx_t; 
typedef uint8_t hg_flags_t; 

class mc_aligned hg_cell_base : public cell {
public:
	hg_cell_base* hg_next_msg = mc_null;
	
	hg_cell_base* hmsg_src = mc_null;
	hg_token_t hmsg_tok = 0;
	
	hg_flags_t hg_msg_flags = 0;
	hg_value_t hmsg_val = 0;
	hg_cell_base* hmsg_ref = mc_null;
	hg_id_t hg_msg_att_id = 0;
	hg_bit_t hg_msg_reply_bit = 0;
	
	hg_replies_bits_t hg_pending_replies = 0;
	hg_replies_bits_t hg_needed_replies = 0;
	hg_idx_t hg_stack_idx = 0;
	
	hg_step_t hg_step = 0;
	hg_step_t hg_ret_step = 0;
	hg_step_t hg_cll_step = 0;
	
	hg_cell_base(){
		hg_next_msg = mc_null;
	
		hmsg_src = mc_null;
		hmsg_tok = 0;
		
		hg_msg_flags = 0;
		hmsg_val = 0;
		hmsg_ref = mc_null;
		hg_msg_att_id = 0;
		hg_msg_reply_bit = 0;
		
		hg_pending_replies = 0;
		hg_needed_replies = 0;
		hg_step = 0;
		hg_stack_idx = 0;
		hg_ret_step = 0;
		hg_cll_step = 0;
	}

	~hg_cell_base(){}
	
	void
	send_val(hg_cell_base* des, hg_token_t tok, hg_value_t val);

};

#define hg_missive_acquire_arr(num) ((hg_missive *)(kernel::do_acquire(idx_hg_missive, num)))
#define hg_missive_acquire() hg_missive_acquire_arr(1)
	
class mc_aligned hg_missive : public missive {
public:
	MCK_DECLARE_MEM_METHODS(hg_missive)
	
	hg_flags_t	flags = 0;
	hg_value_t	val = 0;
	hg_id_t 	att_id = 0;
	hg_bit_t 	reply_bit = 0;
	
	hg_missive(){
		flags = 0;
		val = 0;
		att_id = 0;
		reply_bit = 0;
	}

	~hg_missive(){}
};

)base");

	const char* prj_nam = project_nam.c_str();
	
	hl_string idx_tot_str = get_cpp_idx_total_str();
	const char* idx_tot = idx_tot_str.c_str();

	fprintf(ff, "enum %s_idx_t : mck_handler_idx_t {\n", prj_nam);
	fprintf(ff, "\tidx_invalid = %s,\n", first_handler_idx.c_str());
	fprintf(ff, "\tidx_hg_missive,\n");
	it1 = all_classes.begin();
	for(; it1 != all_classes.end(); ++it1){
		const char* cls_nm = it1->first.c_str();
		fprintf(ff, "\tidx_%s,\n", cls_nm);
	}
	fprintf(ff, "\t%s\n", idx_tot);
	fprintf(ff, "};\n");
	fprintf(ff, "\n");
	
	
	fprintf(ff, R"base(
		
		
class mc_aligned hg_glbs_%s : public agent {
public:
	MCK_DECLARE_MEM_METHODS(hg_glbs_%s)
	
	missive_handler_t all_net_handlers[%s];
	
	grip* all_ava[%s];
	mc_alloc_kernel_func_t all_acq[%s];
	mc_alloc_kernel_func_t all_sep[%s];

	grip	ava_hg_missives;

	void	init_mem_funcs();
	
)base", prj_nam, prj_nam, idx_tot, idx_tot, idx_tot, idx_tot);
	
	fprintf(ff, "\n");
	it1 = all_classes.begin();
	for(; it1 != all_classes.end(); ++it1){
		const char* cls_nm = it1->first.c_str();
		fprintf(ff, "\tgrip\tava_%ss;\n", cls_nm);
	}
	fprintf(ff, "\n");
	fprintf(ff, "};\n");
	fprintf(ff, "\n\n");

	fprintf(ff, "#define hg_globals ((hg_glbs_%s *)(kernel::get_sys()->user_data))\n", prj_nam);
	fprintf(ff, "#define hg_handlers (hg_globals->all_net_handlers)\n");
	fprintf(ff, "#define hg_missives_ava (hg_globals->ava_hg_missives\n");
	fprintf(ff, "\n\n");

	it1 = all_classes.begin();
	for(; it1 != all_classes.end(); ++it1){
		const char* cls_nm = it1->first.c_str();
		fprintf(ff, "#define hg_ava_%ss (hg_globals->ava_%ss)\n", cls_nm, cls_nm);
	}
	fprintf(ff, "\n");
	
	auto it2 = all_glb_token.begin();
	for(; it2 != all_glb_token.end(); ++it2){
		hc_global* tok = (hc_global*)(it2->second);
		fprintf(ff, "#define %s %s \n", it2->first.c_str(), tok->val.c_str());
	}
	fprintf(ff, "\n\n");
	
	auto it3 = all_glb_const.begin();
	for(; it3 != all_glb_const.end(); ++it3){
		hc_global* con = (hc_global*)(it3->second);
		fprintf(ff, "#define %s %s \n", it3->first.c_str(), con->val.c_str());
	}
	fprintf(ff, "\n");
	
	//fprintf(ff, "#define HG_LN0(nn) case nn: {\n");
	fprintf(ff, "#define HG_LN(nn) } break; case nn: {\n");
	//fprintf(ff, "#define HG_LNL() } break; default: break;\n");
	
	fprintf(ff, "\n\n");
	
	fprintf(ff, "#endif // %s\n", df_str.c_str());
	
	fclose(ff);
	
	hl_string hh_nm = get_glbs_hh_name();
	file_update(tmp_nm, hh_nm);
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
}

void
hc_system::print_glbs_cpp_file(){
	hl_string tmp_nm = get_glbs_tmp_cpp_name();
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
	FILE* ff = file_open(tmp_nm.c_str());
	hl_string pr_glbs_hh_str = HLANG_SYS().get_glbs_hh_name();
	
	const char* prj_nam = project_nam.c_str();

	fprintf(ff, "\n\n");
	fprintf(ff, "#include \"%s\"\n", pr_glbs_hh_str.c_str());
	fprintf(ff, "\n\n");
	
	//fprintf(ff, "MCK_DEFINE_ACQUIRE_ALLOC(hg_glbs_%s, 32);\n\n", prj_nam);
	//fprintf(ff, "MCK_DEFINE_MEM_METHODS(hg_missive, 32, hg_missives_ava, 0);\n");
	fprintf(ff, "\n\n");
	
	hl_string idx_tot_str = get_cpp_idx_total_str();
	const char* idx_tot = idx_tot_str.c_str();
	
	fprintf(ff, R"base(
void
hg_glbs_%s::init_mem_funcs(){
	mc_init_arr_vals(%s, all_ava, mc_null);
	mc_init_arr_vals(%s, all_acq, mc_null);
	mc_init_arr_vals(%s, all_sep, mc_null);
	kernel::set_cell_mem_funcs(all_ava, all_acq, all_sep);
}
		
void
hg_cell_base::send_val(hg_cell_base* des, hg_token_t tok, hg_value_t val){
	hg_missive* msv = hg_missive_acquire();
	
	msv->src = this;
	msv->dst = des;
	msv->tok = tok;
	msv->val = val;
	msv->send();
}

)base", prj_nam, idx_tot, idx_tot, idx_tot);
	
	
	fclose(ff);
	
	hl_string cpp_nm = get_glbs_cpp_name();
	file_update(tmp_nm, cpp_nm);
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
}

void
hclass_reg::print_hh_file(){
	hl_string tmp_nm = get_tmp_hh_name();
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
	FILE* ff = file_open(tmp_nm.c_str());
	hl_string df_str = get_hh_define_str();
	hl_string pr_glbs_hh_str = HLANG_SYS().get_glbs_hh_name();
	fprintf(ff, R"(
#ifndef %s
#define %s
		
#include "%s"
)", df_str.c_str(), df_str.c_str(), pr_glbs_hh_str.c_str());
	
	fprintf(ff, "\n\n\n");
	if(pre_hh_cod != hl_null){
		fprintf(ff, "%s\n", pre_hh_cod);
		fprintf(ff, "\n\n\n");
	}
	
	print_hh_class_top_decl(ff);
	print_hh_class_decl_content(ff);
	fprintf(ff, "};\n");
	
	fprintf(ff, "\n\n\n");
	if(pos_hh_cod != hl_null){
		fprintf(ff, "%s\n", pos_hh_cod);
		fprintf(ff, "\n\n\n");
	}
	
	fprintf(ff, R"(
#endif // %s
)", df_str.c_str());
	
	fclose(ff);
	
	hl_string hh_nm = get_hh_name();
	file_update(tmp_nm, hh_nm);
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
}

void
hclass_reg::print_hh_class_top_decl(FILE* ff){
	
	const char* cls_nm = nam.c_str();
	fprintf(ff, R"(
void %s_handler(hg_missive* msv);
void hg_%s_init_mem_funcs();
		
#define hg_%s_acquire_arr(num) ((%s*)(kernel::do_acquire(idx_%s, num)))
#define hg_%s_acquire() hg_%s_acquire_arr(1)
	
class mc_aligned %s : public hg_cell_base {
public:
	MCK_DECLARE_MEM_METHODS(%s)
	
	//virtual mc_opt_sz_fn 
	//mck_handler_idx_t	get_cell_id(){
	//	return idx_%s;
	//}

	%s(){
		handler_idx = idx_%s;
	}

	~%s(){}

	void handler(hg_missive* msv);
	
)", 
cls_nm, cls_nm,
cls_nm, cls_nm, cls_nm, cls_nm, cls_nm, 
cls_nm, cls_nm, cls_nm, cls_nm, cls_nm, cls_nm);

	fprintf(ff, "\n\n");
	
}

void
hclass_reg::print_hh_class_decl_content(FILE* ff){
	
	fprintf(ff, "\tlong hg_stack_arr[%ld];\n", depth);

	fprintf(ff, "\n\n");
	fprintf(ff, "\t/* VALUES */\n");
	
	auto it1 = values.begin();
	for(; it1 != values.end(); ++it1){
		hc_term* trm = (*it1);
		fprintf(ff, "\t%s %s = 0;\n", trm->get_type(), trm->get_name());
	}
	fprintf(ff, "\n\n");
	fprintf(ff, "\t/* SAFE_VALUES */\n");
	
	it1 = safe_values.begin();
	for(; it1 != safe_values.end(); ++it1){
		hc_term* trm = (*it1);
		fprintf(ff, "\t%s %s = 0;\n", trm->get_type(), trm->get_name());
	}
	fprintf(ff, "\n\n");
	fprintf(ff, "\t/* REFERENCES */\n");
	
	auto it2 = references.begin();
	for(; it2 != references.end(); ++it2){
		hc_term* trm = (*it2);
		fprintf(ff, "\t%s* %s = mc_null;\n", trm->get_type(), trm->get_name());
	}
	fprintf(ff, "\n\n");
	fprintf(ff, "\t/* SAFE_REFERENCES */\n");
	
	it2 = safe_references.begin();
	for(; it2 != safe_references.end(); ++it2){
		hc_term* trm = (*it2);
		fprintf(ff, "\t%s* %s = mc_null;\n", trm->get_type(), trm->get_name());
	}
	fprintf(ff, "\n\n");
	fprintf(ff, "\t/* METHODS */\n");
	
	auto it3 = methods.begin();
	for(; it3 != methods.end(); ++it3){
		hc_mth_def* mth = (*it3);
		fprintf(ff, "\tvoid %s();\n", mth->get_name());
	}
	fprintf(ff, "\n\n");
}

void
hclass_reg::print_cpp_file(){
	hl_string tmp_nm = get_tmp_cpp_name();
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
	FILE* ff = file_open(tmp_nm.c_str());
	hl_string hh_nm = HLANG_SYS().get_hh_name();
	
	fprintf(ff, "\n\n");
	fprintf(ff, "#include \"%s\"\n", hh_nm.c_str());
	fprintf(ff, "\n\n");

	const char* cls_nam = nam.c_str();

	fprintf(ff, "MCK_DEFINE_MEM_METHODS(%s, 32, hg_ava_%ss, 0)\n", cls_nam, cls_nam);
	
	fprintf(ff, R"base(
void 
hg_%s_init_mem_funcs(){
	(hg_globals->all_ava)[idx_%s] = &(hg_ava_%ss);
	(hg_globals->all_acq)[idx_%s] = (mc_alloc_kernel_func_t)%s::acquire_alloc;
	(hg_globals->all_sep)[idx_%s] = (mc_alloc_kernel_func_t)%s::separate;
	PTD_CK(%s::ck_cell_id(idx_%s));
}

)base",
cls_nam, cls_nam, cls_nam,
cls_nam, cls_nam, cls_nam, cls_nam, cls_nam, cls_nam
	);
	
	fprintf(ff, "\n\n");
	if(pre_cpp_cod != hl_null){
		fprintf(ff, "%s\n", pre_cpp_cod);
		fprintf(ff, "\n\n");
	}
	
	print_cpp_class_defs(ff);
	
	fprintf(ff, "\n\n");
	if(pos_cpp_cod != hl_null){
		fprintf(ff, "%s\n", pos_cpp_cod);
		fprintf(ff, "\n\n");
	}
	
	fclose(ff);
	
	hl_string cpp_nm = get_cpp_name();
	file_update(tmp_nm, cpp_nm);
	if(file_exists(tmp_nm)){
		file_remove(tmp_nm);
	}
}

void
hclass_reg::print_all_cpp_methods(FILE *st){
	if(nucleus == hl_null){
		//fprintf(st, "// CLASS_WITHOUT_NUCLEUS !!!!\n");
		hl_abort("Error. hcell class %s without nucleus.\n", nam.c_str());
		return;
	}
	//tot_steps = 0;
	fprintf(st, R"(
void
%s::handler(hg_missive* msv){
PTD_CK(msv != mc_null);
hmsg_src = (hg_cell_base*)(msv->src);
hmsg_tok = (hg_token_t)(msv->tok);
hmsg_val = msv->val;
hmsg_ref = (hg_cell_base*)(msv->val);

if((hmsg_tok == htk_get) || (hmsg_tok == htk_set)){
	if(hmsg_tok == htk_get){
	} else {
		PTD_CK(hmsg_tok == htk_set);
		//send_val( src ,  pr_tok_snd_val1 ,  k1 );
	}
	return;
}

)", nam.c_str());
	
	fprintf(st, "while(true){\n");
	fprintf(st, "switch(hg_step){\n");
	fprintf(st, "case 0: {\n");
	fprintf(st, "\thg_step = %ld;\n", nucleus->get_num_label());
	fprintf(st, "\n");
	
	print_cpp_handler_return_code(st);
	print_cpp_call_wait_safe_code(st);
	print_cpp_call_mth_code(st);
	print_cpp_ret_mth_code(st);
	
	auto it = methods.begin();
	for(; it != methods.end(); ++it){
		hc_mth_def* mth_df = (*it);

		mth_df->print_cpp_code(st);
	}
	if(nucleus != hl_null){
		fprintf(st, "\t/* THE_NUCLEUS %s */\n", nucleus->nam);
		
		nucleus->print_cpp_code(st);
	}

	fprintf(st, "} break;\n");
	fprintf(st, "default:\n");
	fprintf(st, "break;\n");
	fprintf(st, "\n");
	fprintf(st, "} // closes switch\n");
	fprintf(st, "} // closes while\n");
	fprintf(st, "} // closes handler\n");
	fprintf(st, "\n");
		
}

void
hclass_reg::print_cpp_class_defs(FILE* st){
	print_all_cpp_methods(st);
}

int
hc_term::print_cpp_term(FILE *st){
	hl_abort("INVALID_TERM !!!!\n");
	return 0;
}

int
hc_unary_term::print_cpp_term(FILE *st){
	hc_syntax_op_t c_op = get_oper();
	HL_CK(c_op != hc_hcase_op);
	if(c_op == hc_hswitch_op){
		fprintf(st, "/*");
	}
	
	const char* tok = hc_get_cpp_token(op);
	HL_CK(prm != hl_null);
	fprintf(st, "%s", tok);
	fprintf(st, "(");
	HC_PRT_TERM_INDENT++;
	prm->print_cpp_term(st);
	HC_PRT_TERM_INDENT--;
	fprintf(st, ")");

	if(c_op == hc_hswitch_op){
		fprintf(st, "*/");
	}
	
	return 0;
}

int
hc_case_term::print_cpp_term(FILE *st){
	hc_syntax_op_t c_op = get_oper();
	HL_CK(c_op == hc_hcase_op);
	
	const char* tok = hc_get_cpp_token(op);
	HL_CK(prm != hl_null);
	fprintf(st, "%s", tok);
	fprintf(st, "(");
	HC_PRT_TERM_INDENT++;
	prm->print_cpp_term(st);
	fprintf(st, " == ");
	if(the_sw_eq != hl_null){ the_sw_eq->print_cpp_term(st); }
	HC_PRT_TERM_INDENT--;
	fprintf(st, ")");

	return 0;
}

int
hc_steps::print_cpp_term(FILE *st){
	bool is_fst = true;
	
	auto it = steps.begin();
	for(; it != steps.end(); ++it){
		if(is_fst){ is_fst = false; } 
		else { fprintf(st, " ;"); }
		hc_term* tm = (*it);
		HL_CK(tm != hl_null);
		
		print_new_line(st);
		fprintf(st, "HG_LN(%ld)\t", tm->get_num_label());
		
		hc_term::print_indent(st);
		tm->print_cpp_term(st);
		
		hc_syntax_op_t c_op = tm->get_oper();
		if(		(c_op != hc_then_op) && 
				(c_op != hc_mth_call_op) && 
				(c_op != hc_mth_ret_op) &&
				(c_op != hc_safe_check_op)
		  )
		{
			HL_CK_PRT((tm->next != hl_null), 
				"DURING %s writing file:\n %s\n", hc_get_token(c_op), get_file_path(st));
			fprintf(st, ";\thg_step = %ld;", tm->next->get_num_label());
		}
	}
	
	return 0;
}

int
hc_condition::print_cpp_term(FILE *st){
	const char* tok = hc_get_cpp_token(hc_then_op);
	hc_term* tm1 = cond;
	hc_term* tm2 = if_true;
	
	HL_CK(tm1 != hl_null);
	HL_CK(tm2 != hl_null);
	
	fprintf(st, "/*(*/"); 
	hc_term::HC_PRT_TERM_INDENT++;

	tm1->print_cpp_term(st);

	hc_syntax_op_t c_op = tm1->get_oper();
	if(c_op == hc_hswitch_op){
		fprintf(st, "hg_step = %ld;", if_true->get_num_label());
	} else if(c_op != hc_hfor_op){
		HL_CK(next != hl_null);
		fprintf(st, "{ hg_step = %ld; } else { hg_step = %ld; }",
			if_true->get_num_label(),
			next->get_num_label()
		);
	}
	fprintf(st, " %s ", tok);
	
	tm2->print_cpp_term(st);
	
	hc_term::HC_PRT_TERM_INDENT--;
	fprintf(st, "/*)*/");
	
	return 0;
}

int
hc_for_loop::print_cpp_term(FILE *st){
	const char* tok = hc_get_cpp_token(get_oper());
	HL_CK(owner != hl_null);
	HL_CK(cond != hl_null);
	HL_CK(end_each_loop != hl_null);
	
	fprintf(st, "%s", tok);
	fprintf(st, "/*(*/");
	HC_PRT_TERM_INDENT++;
	cond->print_cpp_term(st);
	
	fprintf(st, "{ hg_step = %ld; } else { hg_step = %ld; }",
		owner->if_true->get_num_label(),
		owner->next->get_num_label()
	);
	
	fprintf(st, "/*  _,_  */");
	end_each_loop->print_cpp_term(st);
	HC_PRT_TERM_INDENT--;
	fprintf(st, "/*)*/");

	return 0;
}

int
hc_binary_term::print_cpp_term(FILE *st){
	const char* tok = hc_get_cpp_token(op);
	HL_CK(lft != hl_null);
	HL_CK(rgt != hl_null);
	HL_CK(op != hc_comma_op);
	HL_CK(op != hc_then_op);
	
	fprintf(st, "("); 
	hc_term::HC_PRT_TERM_INDENT++;
	
	lft->print_cpp_term(st);
	
	fprintf(st, " %s ", tok);
	
	rgt->print_cpp_term(st);
	
	hc_term::HC_PRT_TERM_INDENT--;
	fprintf(st, ")");

	return 0;
}

int
hc_send_term::print_cpp_term(FILE *st){
	HL_CK((op == hc_send_op) || (op == hc_safe_send_op));
	
	const char* tok_str = hc_get_cpp_token(op);
	
	fprintf(st, " %s", tok_str);
	
	fprintf(st, "("); 
	HC_PRT_TERM_INDENT++;
	
	if(snd_dst != hl_null){ snd_dst->print_cpp_term(st); }
	
	fprintf(st, ", ");
	
	if(snd_tok != hl_null){ snd_tok->print_cpp_term(st); }

	fprintf(st, ", ");
	
	if(snd_att != hl_null){ snd_att->print_cpp_term(st); }

	HC_PRT_TERM_INDENT--;
	fprintf(st, ")");
	
	return 0;
}

int
hc_mth_ret::print_cpp_term(FILE *st){
	HL_CK(the_mth != hl_null);
	hc_syntax_op_t c_op = get_oper();
	HL_CK(c_op == hc_mth_ret_op);
	fprintf(st, "/* %s() %s */", get_name(), hc_get_cpp_token(c_op));
	HL_CK(the_mth->my_cls != hl_null);
	fprintf(st, "hg_step = %ld; ", the_mth->my_cls->mth_ret_num_step);
	return 0;
}

int
hc_mth_call::print_cpp_term(FILE *st){
	HL_CK(the_mth != hl_null);
	hc_syntax_op_t c_op = get_oper();
	HL_CK(c_op == hc_mth_call_op);
	fprintf(st, "/* %s() %s */", get_name(), hc_get_cpp_token(c_op));
	//HL_CK_PRT((next != hl_null), "DURING_CALL_TO %s in file:\n %s\n", get_name(), get_file_path(st));
	
	if(next != hl_null){
		HL_CK(the_mth->my_cls != hl_null);
		fprintf(st, "hg_ret_step = %ld; hg_cll_step = %ld; hg_step = %ld; ", 
			next->get_num_label(), the_mth->get_num_label(), the_mth->my_cls->mth_call_num_step
		);
	}
	return 0;
}

void
hclass_reg::print_cpp_call_mth_case(FILE* st, long idx){
	long idx_inc = idx + 1;
	fprintf(st, "\t\tcase %ld:\n", idx);
	fprintf(st, "\t\t\thg_stack_arr[%ld] = hg_ret_step;\n", idx);
	fprintf(st, "\t\t\thg_stack_idx = %ld;\n", idx_inc);
	fprintf(st, "\t\t\thg_step = hg_cll_step;\n");
	fprintf(st, "\t\tbreak;\n");
}

void
hclass_reg::print_cpp_ret_mth_case(FILE* st, long idx){
	long idx_dec = idx - 1;
	fprintf(st, "\t\tcase %ld:\n", idx);
	fprintf(st, "\t\t\thg_stack_idx = %ld;\n", idx_dec);
	fprintf(st, "\t\t\thg_step = hg_stack_arr[%ld];\n", idx_dec);
	fprintf(st, "\t\t\thg_stack_arr[%ld] = 0;\n", idx_dec);
	fprintf(st, "\t\tbreak;\n");
}

void
hclass_reg::print_cpp_handler_return_code(FILE* st){
	HL_CK(nucleus != hl_null);
	fprintf(st, "// print_cpp_handler_return_code\n");
	fprintf(st, "HG_LN(%ld)\n", mth_handler_return_step);
	fprintf(st, "\thg_step = %ld;\n", nucleus->get_num_label());
	fprintf(st, "\treturn;\n");
	fflush(st);
}

void
hclass_reg::print_cpp_call_wait_safe_code(FILE* st){
	fprintf(st, "// print_cpp_call_wait_safe_code\n");
	fprintf(st, "HG_LN(%ld)\n", mth_safe_wait_step);
	
	fprintf(st, "\tif((hg_pending_replies & hg_needed_replies) == 0){ hg_step = hg_ret_step; }");
	fprintf(st, "\n");
	fprintf(st, "\telse { return; }");
	fprintf(st, "\n");
	fflush(st);
}

void
hclass_reg::print_cpp_call_mth_code(FILE* st){
	fprintf(st, "// print_cpp_call_mth_code\n");
	fprintf(st, "HG_LN(%ld)\n", mth_call_num_step);
	fprintf(st, "\tswitch(hg_stack_idx){\n");
	
	for(long aa = 0; aa < depth; aa++){
		print_cpp_call_mth_case(st, aa);
	}
	
	fprintf(st, "\t\tdefault:\n");
	fprintf(st, "\t\tbreak;\n");
	fprintf(st, "\t};\n");
	fprintf(st, "\n");
	fprintf(st, "\n");
	fflush(st);
}

void
hclass_reg::print_cpp_ret_mth_code(FILE* st){
	fprintf(st, "// print_cpp_ret_mth_code\n");
	fprintf(st, "HG_LN(%ld)\n", mth_ret_num_step);
	fprintf(st, "\tswitch(hg_stack_idx){\n");
	
	fprintf(st, "\t\tcase 0:\n");
	fprintf(st, "\t\t\thg_step = %ld;\n", mth_handler_return_step);
	fprintf(st, "\t\tbreak;\n");
	
	for(long aa = 1; aa <= depth; aa++){
		print_cpp_ret_mth_case(st, aa);
	}
	
	fprintf(st, "\t\tdefault:\n");
	fprintf(st, "\t\tbreak;\n");
	fprintf(st, "\t};\n");
	fprintf(st, "\n");
	fprintf(st, "\n");
	fflush(st);
}

int
hc_safe_check::print_cpp_term(FILE *st){
	HL_CK(next != hl_null);
	HL_CK(owner != hl_null);
	hclass_reg* creg = owner->get_class_reg();
	HL_CK(creg != hl_null);
	
	fprintf(st, "if((hg_pending_replies & %#lx) == 0){ hg_step = %ld; }", 
			safe_pattern,
			next->get_num_label());
	
	fprintf(st, "\n");
	fprintf(st, "/*     */\t");
	hc_term::print_indent(st);
	
	//fprintf(st, " ");
	fprintf(st, "else { hg_ret_step = %ld; hg_needed_replies = %#lx; hg_step = %ld; }", 
		next->get_num_label(), safe_pattern, creg->mth_safe_wait_step
	);
	return 0;
}

