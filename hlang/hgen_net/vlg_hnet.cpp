
#include "hgen_net.h"

using namespace std;

//--------------------------------------------------------------------------------
// tester of verilog module printer

void
runner_print_verilog_target_box::print_help(){
	GH_GLOBALS.compl_sys.print_last_complete_arg();
	FILE* of = GH_GLOBALS.compl_sys.args_compl_output;
	fprintf(of, "<num_in> <num_out> [-o <out_file_name>] [-w <num_direct_chnls> <num_direct_paks> <wrapper_file_name>] [-pb <pw_base>] \n");
}
bool

runner_print_verilog_target_box::get_args(gh_str_list_t& lt_args){
	GH_CK(! lt_args.empty());
	GH_CK(lt_args.front() == "print_verilog_target_box");
	
	bool is_cmpl = GH_GLOBALS.compl_sys.args_orig_has_compl;
	int tot_params = lt_args.size();
	tot_params--;
	if(is_cmpl){
		tot_params--;
	}
	if(tot_params < 2){
		if(! is_cmpl){
			fprintf(stdout, "following args must have the form:\n\t");
		}
		print_help();
		return false;
	}
	
	gh_dec_args(lt_args);
	
	gh_string_t the_arg = lt_args.front(); gh_dec_args(lt_args);
	num_in = atol(the_arg.c_str());
	
	the_arg = lt_args.front(); gh_dec_args(lt_args);
	num_out = atol(the_arg.c_str());
	
	bool did_some = true;
	while(did_some && ! lt_args.empty()){
		did_some = false;
		the_arg = lt_args.front();
		if((the_arg == "-pb") && (lt_args.size() > 1)){
			gh_dec_args(lt_args); did_some = true;

			the_arg = lt_args.front(); gh_dec_args(lt_args);
			pw_base = atol(the_arg.c_str());
		}
		else if((the_arg == "-o") && (lt_args.size() > 1)){
			gh_dec_args(lt_args); did_some = true;

			out_file_name = lt_args.front(); gh_dec_args(lt_args);
		}
		else if((the_arg == "-w") && (lt_args.size() > 3)){
			gh_dec_args(lt_args); did_some = true;

			the_arg = lt_args.front(); gh_dec_args(lt_args);
			num_direct_channels = atol(the_arg.c_str());
			
			the_arg = lt_args.front(); gh_dec_args(lt_args);
			num_direct_packets = atol(the_arg.c_str());
			
			wrapper_file_name = lt_args.front(); gh_dec_args(lt_args);
		}
	}
	
	return true;
}

int
runner_print_verilog_target_box::run_test(gh_str_list_t& lt_args){
	bool go_on = get_args(lt_args);
	if(! go_on){
		return -1;
	}
	bool is_cmpl = GH_GLOBALS.compl_sys.args_orig_has_compl;
	if(is_cmpl){ return -1; }
	
	long bb = pw_base;
	long nin = num_in;
	long nout = num_out;
	
	FILE* ff = stdout;
	if(out_file_name != ""){
		ff = fopen(out_file_name.c_str(), "w");
		if(ff == NULL){
			fprintf(stderr, "Cannot open file %s for writing !!\n", out_file_name.c_str());
			return -1;
		}
	}
	
	FILE* ffw = NULL;
	if(wrapper_file_name != ""){
		ffw = fopen(wrapper_file_name.c_str(), "w");
		if(ffw == NULL){
			fprintf(stderr, "Cannot open file %s for writing !!\n", wrapper_file_name.c_str());
			return -1;
		}
	}
	
	
	fprintf(ff, "// test_get_target base=%ld #in=%ld #out=%ld\n", bb, nin, nout);

	htarget_box* bx = new htarget_box(bb);
	
	long tg_idx = 0;
	long tgs_sz = 0;
	gh_dbg_calc_idx_and_sz(nin, nout, bb, tg_idx, tgs_sz);
	
	slice_vec all_addr;
	bx->init_target_box(tg_idx, nin, nout, all_addr, tgs_sz);

	GH_GLOBALS.CK_LINK_MODE = gh_valid_self_ck_mod;

	fprintf(ff, "/*\n");
	fprintf(ff, "---------------------------------------------\n");
	bx->print_box(ff, gh_full_prt);
	fprintf(ff, "---------------------------------------------\n");
	fprintf(ff, "*/\n");
	
	
	
	bx->print_verilog_module_lognet_target_box(ff);
	
	if(ffw != NULL){
		bx->print_verilog_module_lognet_target_wrapper_box(ffw, num_direct_channels, num_direct_packets);
	}
	
	delete bx;
	return 0;
}



int test_verilog(gh_str_list_t& lt_args){
	//bool is_cmpl = GH_GLOBALS.compl_sys.args_orig_has_compl;
	int resp = -1;
			
	gh_str_set_t lv_commds;
	
	lv_commds.insert("print_verilog_target_box");
	
	std::string cho;
	bool ok1 = gh_args_select_one_of(lt_args, lv_commds, cho);
	if(! ok1){
		return -1;
	}

	bool done = false;
	if(! done && (cho == "print_verilog_target_box")){
		resp = GH_GLOBALS.rnr_print_verilog_target_box.run_test(lt_args);
		done = true;
	}
	
	return resp;
}

//--------------------------------------------------------------------------------
// verilog module printer

gh_string_t
hnode::get_verilog_id(){
	gh_string_t o_str = "gh_invalid_verilog_id";
	if(is_1to1()){
		hnode_1to1* th_nd = (hnode_1to1*)this;
		gh_1t1_kind_t k1t1 = th_nd->get_1t1_kind();
		GH_CK(k1t1 == gh_target_1t1);
		
		hnode_target* tg = (hnode_target*)th_nd;
		o_str = gh_vl_tgt + gh_long_to_string(tg->bx_idx);
	} else {
		o_str = gh_vl_nod + gh_long_to_string(addr);
	}
	return o_str;
}

gh_string_t
hnode::get_verilog_send_node_interface_name(hnode** ppout){
	GH_CK(ppout != gh_null);
	GH_CK(*ppout != gh_null);
	gh_string_t nd_id = get_verilog_id();
	if(*ppout == this){
		hnode** pnd = get_pt_out0();
		if(pnd == ppout){
			gh_string_t o_str = nd_id + gh_vl_out0;
			return o_str;
		} 
		pnd = get_pt_out1();
		GH_CK(pnd == ppout);
		gh_string_t o_str = nd_id + gh_vl_out1;
		return o_str;
	}
	//GH_CK((nd_id == dbg_get__in0_verilog_id()) || (nd_id == dbg_get__in1_verilog_id()));
	
	gh_string_t o_str = nd_id + gh_vl_sep + (*ppout)->get_verilog_id();
	return o_str;
}

gh_string_t
hnode::get_verilog_receive_node_interface_name(hnode** ppin){
	GH_CK(ppin != gh_null);
	GH_CK(*ppin!= gh_null);
	gh_string_t nd_id = get_verilog_id();
	if(*ppin == this){
		hnode** pnd = get_pt_in0();
		if(pnd == ppin){
			gh_string_t o_str = gh_vl_in0 + nd_id;
			return o_str;
		} 
		pnd = get_pt_in1();
		GH_CK(pnd == ppin);
		gh_string_t o_str = gh_vl_in1 + nd_id;
		return o_str;
	}
	//GH_CK((nd_id == dbg_get__out0_verilog_id()) || (nd_id == dbg_get__out1_verilog_id()));
	
	gh_string_t o_str = (*ppin)->get_verilog_id() + gh_vl_sep + nd_id;
	return o_str;
}

void
gh_print_verilog_declare_out_channel(FILE* ff, gh_string_t itf_nm, bool with_final_comma){
	fprintf(ff, "\t");
	fprintf(ff, "`NS_DECLARE_OUT_CHNL(%s)", itf_nm.c_str());
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
}

void
gh_print_verilog_declare_in_channel(FILE* ff, gh_string_t itf_nm, bool with_final_comma){
	fprintf(ff, "\t");
	fprintf(ff, "`NS_DECLARE_IN_CHNL(%s)", itf_nm.c_str());
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
}

void
gh_print_verilog_declare_pakout(FILE* ff, gh_string_t itf_nm, bool with_final_comma){
	fprintf(ff, "\t");
	fprintf(ff, "`NS_DECLARE_PAKOUT_CHNL(%s)", itf_nm.c_str());
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
}

void
gh_print_verilog_declare_pakin(FILE* ff, gh_string_t itf_nm, bool with_final_comma){
	fprintf(ff, "\t");
	fprintf(ff, "`NS_DECLARE_PAKIN_CHNL(%s)", itf_nm.c_str());
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
}

void 
gh_print_tabs(FILE* ff, long num_tabs){
	for(long aa = 0; aa < num_tabs; aa++){
		fprintf(ff, "\t");
	}
}

void
gh_print_verilog_declare_link_interface(FILE* ff, long num_tabs, gh_string_t itf_nm){
	gh_str_set_t& all_itf = GH_GLOBALS.all_verilog_declared_interfaces;
	auto it = all_itf.find(itf_nm);
	if(it != all_itf.end()){
		GH_CK(*it == itf_nm);
		return;
	}
	all_itf.insert(itf_nm);
	
	gh_print_tabs(ff, num_tabs);
	fprintf(ff, "`NS_DECLARE_LINK(%s)\n", itf_nm.c_str());
}

void
gh_print_verilog_assign_interface(FILE* ff, long num_tabs, gh_string_t itf_nm_1, gh_string_t itf_nm_2){
	gh_str_set_t& all_itf = GH_GLOBALS.all_verilog_assigned_interfaces;
	auto it = all_itf.find(itf_nm_1);
	if(it != all_itf.end()){
		GH_CK(*it == itf_nm_1);
		return;
	}
	all_itf.insert(itf_nm_1);
	
	gh_print_tabs(ff, num_tabs);
	fprintf(ff, "`NS_ASSIGN_MSG(%s, %s)\n", itf_nm_1.c_str(), itf_nm_2.c_str());
}

void
gh_print_verilog_instance_send_interface(FILE* ff, long num_tabs, gh_string_t itf_nm_1, gh_string_t itf_nm_2, bool with_final_comma){
	gh_print_tabs(ff, num_tabs);
	fprintf(ff, "`NS_INSTA_SND_CHNL(%s, %s)", itf_nm_1.c_str(), itf_nm_2.c_str());
	
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
}

void
gh_print_verilog_instance_receive_interface(FILE* ff, long num_tabs, gh_string_t itf_nm_1, gh_string_t itf_nm_2, bool with_final_comma){
	gh_print_tabs(ff, num_tabs);
	fprintf(ff, "`NS_INSTA_RCV_CHNL(%s, %s)", itf_nm_1.c_str(), itf_nm_2.c_str());
	
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
}

void
hnode_2to1::print_verilog_2to1_instance(FILE* ff, long idx){
	gh_string_t i0_itf_nm = get_verilog_receive_node_interface_name(&in0);
	gh_string_t i1_itf_nm = get_verilog_receive_node_interface_name(&in1);
	gh_string_t o0_itf_nm = get_verilog_send_node_interface_name(&out0);
	
	gh_print_verilog_declare_link_interface(ff, 1, i0_itf_nm);
	gh_print_verilog_declare_link_interface(ff, 1, i1_itf_nm);
	gh_print_verilog_declare_link_interface(ff, 1, o0_itf_nm);

	fprintf(ff, R"base(
	nd_2to1
	it_nd_2to1_%ld (
		`NS_INSTA_GLB_CHNL(gch, gch),
)base", idx);
	
	gh_print_verilog_instance_send_interface(ff, 2, gh_vl_snd0, o0_itf_nm);
	gh_print_verilog_instance_receive_interface(ff, 2, gh_vl_rcv0, i0_itf_nm);
	gh_print_verilog_instance_receive_interface(ff, 2, gh_vl_rcv1, i1_itf_nm, false);
	
	fprintf(ff, "\t); \n\n");
	
}

gh_string_t
edge::get_verilog_oper(){
	gh_string_t op = "INVALID_OPER";
	if(is_gt()){
		if(is_eq()){
			op = "`GTE_OP";
			return op;
		}
		op = "`GT_OP";
		return op;
	}
	if(is_eq()){
		op = "`LTE_OP";
		return op;
	}
	op = "`LT_OP";
	return op;
}

gh_string_t
edge::get_verilog_ref_val(){
	return gh_long_to_string(slc_edge);
}

gh_string_t
hnode_1to2::get_verilog_oper_1(){
	if(selector.lft.is_undef()){
		GH_CK(! selector.rgt.is_undef());
		return selector.rgt.get_verilog_oper();
	}
	return selector.lft.get_verilog_oper();
}

gh_string_t
hnode_1to2::get_verilog_ref_val_1(){
	if(selector.lft.is_undef()){
		GH_CK(! selector.rgt.is_undef());
		return selector.rgt.get_verilog_ref_val();
	}
	return selector.lft.get_verilog_ref_val();
}

gh_string_t
hnode_1to2::get_verilog_is_range(){
	bool is_itv = get_flag(gh_is_interval);
	gh_string_t is_rng = "`FALSE";
	bool has_udf = selector.lft.is_undef() || selector.rgt.is_undef();
	if(is_itv && ! has_udf){
		is_rng = "`TRUE";
	}
	return is_rng;
}

gh_string_t
hnode_1to2::get_verilog_oper_2(){
	return selector.rgt.get_verilog_oper();
}

gh_string_t
hnode_1to2::get_verilog_ref_val_2(){
	return selector.rgt.get_verilog_ref_val();
}

void
hnode_1to2::print_verilog_1to2_instance(FILE* ff, long idx){
	gh_string_t i0_itf_nm = get_verilog_receive_node_interface_name(&in0);
	gh_string_t o0_itf_nm = get_verilog_send_node_interface_name(&out0);
	gh_string_t o1_itf_nm = get_verilog_send_node_interface_name(&out1);
	
	gh_print_verilog_declare_link_interface(ff, 1, i0_itf_nm);
	gh_print_verilog_declare_link_interface(ff, 1, o0_itf_nm);
	gh_print_verilog_declare_link_interface(ff, 1, o1_itf_nm);
	
	gh_string_t op1 = get_verilog_oper_1();
	gh_string_t val1 = get_verilog_ref_val_1();
	gh_string_t is_rng = get_verilog_is_range();
	gh_string_t op2 = get_verilog_oper_2();
	gh_string_t val2 = get_verilog_ref_val_2();
	
	fprintf(ff, R"base(
	nd_1to2 #(.OPER_1(%s), .REF_VAL_1(%s), .IS_RANGE(%s), .OPER_2(%s), .REF_VAL_2(%s))
	it_nd_1to2_%ld (
		`NS_INSTA_GLB_CHNL(gch, gch),
)base", 
	op1.c_str(),
	val1.c_str(),
	is_rng.c_str(),
	op2.c_str(),
	val2.c_str(),
	idx
	);
	
	gh_print_verilog_instance_send_interface(ff, 2, gh_vl_snd0, o0_itf_nm);
	gh_print_verilog_instance_send_interface(ff, 2, gh_vl_snd1, o1_itf_nm);
	gh_print_verilog_instance_receive_interface(ff, 2, gh_vl_rcv0, i0_itf_nm, false);
	
	fprintf(ff, "\t); \n\n");
	
}

void
gh_print_verilog_assigns_for_ios(FILE* ff, ppnode_vec_t& all_io, gh_route_side_t sd, gh_io_kind_t iok){
	fflush(ff);
	for(long ii = 0; ii < (long)all_io.size(); ii++){
		hnode** ppi = all_io[ii];
		if(ppi != gh_null){
			hnode* pi = *ppi;
			GH_CK(pi != gh_null);

			gh_string_t itf_nm;
			if(iok == gh_in_kind){
				itf_nm = pi->get_verilog_receive_node_interface_name(ppi);
			} else {
				GH_CK(iok == gh_out_kind);
				itf_nm = pi->get_verilog_send_node_interface_name(ppi);
			}
			gh_print_verilog_declare_link_interface(ff, 1, itf_nm);
			
			gh_string_t io_nm = get_verilog_io_name(ii, sd, iok);
			
			if(iok == gh_in_kind){
				gh_print_verilog_assign_interface(ff, 1, itf_nm, io_nm);
			} else {
				GH_CK(iok == gh_out_kind);
				gh_print_verilog_assign_interface(ff, 1, io_nm, itf_nm);
			}
		} else {
			fprintf(ff, "// NULL io %ld \n", ii);
		}
	}
	fprintf(ff, "\n\n");
	fflush(ff);
}

void
gh_print_verilog_params_for_ios(FILE* ff, ppnode_vec_t& all_io, gh_route_side_t sd, gh_io_kind_t iok){
	fflush(ff);
	for(long ii = 0; ii < (long)all_io.size(); ii++){
		gh_string_t io_nm = get_verilog_io_name(ii, sd, iok);
		if(iok == gh_in_kind){
			gh_print_verilog_declare_in_channel(ff, io_nm);
		} else {
			GH_CK(iok == gh_out_kind);
			gh_print_verilog_declare_out_channel(ff, io_nm);
		}
	}
	fflush(ff);
}

void
gh_print_verilog_code_for_nodes(FILE* ff, pnode_vec_t& all_nd){
	for(long ii = 0; ii < (long)all_nd.size(); ii++){
		hnode* the_nd = all_nd[ii];
		GH_CK(the_nd != gh_null);
		fprintf(ff, "\t// node: (%p)\n", (void*)the_nd);
		if(the_nd->is_1to2()){
			hnode_1to2* nd = (hnode_1to2*)the_nd;
			nd->print_verilog_1to2_instance(ff, ii);
		} else {
			GH_CK(the_nd->is_2to1());
			hnode_2to1* nd = (hnode_2to1*)the_nd;
			nd->print_verilog_2to1_instance(ff, ii);
		}
	}
}

gh_string_t
htarget_box::get_verilog_module_name(){
	GH_CK(target != gh_null);
	gh_string_t ss = gh_vl_tg_mod + gh_long_to_string(target->bx_idx);
	return ss;
}

gh_string_t
htarget_box::get_verilog_target_param_name(gh_io_kind_t iok){
	gh_string_t iok_nm = get_verilog_io_kind(iok);
	GH_CK(target != gh_null);
	gh_string_t ss = gh_vl_tgt + iok_nm + gh_long_to_string(target->bx_idx);
	return ss;
}

void 
htarget_box::print_verilog_target_param(FILE* ff){
	gh_string_t itf_in_nm = get_verilog_target_param_name(gh_in_kind);
	gh_string_t itf_out_nm = get_verilog_target_param_name(gh_out_kind);
	gh_print_verilog_declare_in_channel(ff, itf_in_nm);
	gh_print_verilog_declare_out_channel(ff, itf_out_nm, false);
}

void
htarget_box::print_verilog_target_assign(FILE* ff){
	gh_string_t itf_in_nm = get_verilog_target_param_name(gh_in_kind);
	gh_string_t itf_out_nm = get_verilog_target_param_name(gh_out_kind);
	GH_CK(target != gh_null);
	gh_string_t tg_in_itf_nm = target->get_verilog_receive_node_interface_name(&(target->in0));
	gh_string_t tg_out_itf_nm = target->get_verilog_send_node_interface_name(&(target->out0));
	
	gh_print_verilog_assign_interface(ff, 1, itf_in_nm, tg_in_itf_nm);
	gh_print_verilog_assign_interface(ff, 1, itf_out_nm, tg_out_itf_nm);
}

void
htarget_box::print_verilog_module_lognet_target_box(FILE* ff){
	
	fprintf(ff, R"base(
`include "hglobal.v"

`default_nettype	none

module lognet_target_box_%ld
#(parameter ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	`NS_DECLARE_GLB_CHNL(gch),
)base", target->bx_idx);

	gh_print_verilog_params_for_ios(ff, lft_in, gh_left_side, gh_in_kind);
	gh_print_verilog_params_for_ios(ff, lft_out, gh_left_side, gh_out_kind);
	gh_print_verilog_params_for_ios(ff, rgt_in, gh_right_side, gh_in_kind);
	gh_print_verilog_params_for_ios(ff, rgt_out, gh_right_side, gh_out_kind);
	
	print_verilog_target_param(ff);

	fprintf(ff, ");\n");

	gh_print_verilog_assigns_for_ios(ff, lft_in, gh_left_side, gh_in_kind);
	gh_print_verilog_assigns_for_ios(ff, lft_out, gh_left_side, gh_out_kind);
	gh_print_verilog_assigns_for_ios(ff, rgt_in, gh_right_side, gh_in_kind);
	gh_print_verilog_assigns_for_ios(ff, rgt_out, gh_right_side, gh_out_kind);
	
	gh_print_verilog_code_for_nodes(ff, all_nodes);
	
	print_verilog_target_assign(ff);
	
	fprintf(ff, R"base(

 
endmodule

)base");
	
}

void
gh_print_verilog_params_for_direct_channels(FILE* ff, long tot_core_ios, long num_direct_ios, gh_route_side_t sd, gh_io_kind_t iok){
	fflush(ff);
	for(long ii = 0; ii < num_direct_ios; ii++){
		long id_io = tot_core_ios + ii;
		gh_string_t io_nm = get_verilog_io_name(id_io, sd, iok);
		if(iok == gh_in_kind){
			gh_print_verilog_declare_in_channel(ff, io_nm);
		} else {
			GH_CK(iok == gh_out_kind);
			gh_print_verilog_declare_out_channel(ff, io_nm);
		}
	}
	fflush(ff);
}

void
gh_print_verilog_params_for_direct_packets(FILE* ff, long tot_core_ios, long num_direct_ios, gh_route_side_t sd, gh_io_kind_t iok){
	fflush(ff);
	for(long ii = 0; ii < num_direct_ios; ii++){
		long id_io = tot_core_ios + ii;
		gh_string_t io_nm = get_verilog_io_name(id_io, sd, iok);
		if(iok == gh_in_kind){
			gh_print_verilog_declare_pakin(ff, io_nm);
		} else {
			GH_CK(iok == gh_out_kind);
			gh_print_verilog_declare_pakout(ff, io_nm);
		}
	}
	fflush(ff);
}

void
gh_print_verilog_assigns_for_direct_ios(FILE* ff, long tot_core_ios, long num_direct_chns, long num_direct_paks){
	fflush(ff);
	for(long ii = 0; ii < num_direct_chns; ii++){
		long id_io = tot_core_ios + ii;
		gh_string_t li = get_verilog_io_name(id_io, gh_left_side, gh_in_kind);
		gh_string_t lo = get_verilog_io_name(id_io, gh_left_side, gh_out_kind);
		gh_string_t ri = get_verilog_io_name(id_io, gh_right_side, gh_in_kind);
		gh_string_t ro = get_verilog_io_name(id_io, gh_right_side, gh_out_kind);
		
		gh_print_tabs(ff, 1);
		fprintf(ff, "`NS_ASSIGN_OUT_CHNL_FROM_IN_CHNL(%s, %s)\n", lo.c_str(), li.c_str());
		gh_print_tabs(ff, 1);
		fprintf(ff, "`NS_ASSIGN_OUT_CHNL_FROM_IN_CHNL(%s, %s)\n", ro.c_str(), ri.c_str());
	}
	for(long ii = 0; ii < num_direct_paks; ii++){
		long id_io = tot_core_ios + num_direct_chns + ii;
		gh_string_t li = get_verilog_io_name(id_io, gh_left_side, gh_in_kind);
		gh_string_t lo = get_verilog_io_name(id_io, gh_left_side, gh_out_kind);
		gh_string_t ri = get_verilog_io_name(id_io, gh_right_side, gh_in_kind);
		gh_string_t ro = get_verilog_io_name(id_io, gh_right_side, gh_out_kind);
		
		gh_print_tabs(ff, 1);
		fprintf(ff, "`NS_ASSIGN_PAKOUT_FROM_PAKIN(%s, %s)\n", lo.c_str(), li.c_str());
		gh_print_tabs(ff, 1);
		fprintf(ff, "`NS_ASSIGN_PAKOUT_FROM_PAKIN(%s, %s)\n", ro.c_str(), ri.c_str());
	}
	fprintf(ff, "\n\n");
	fflush(ff);
}

void
gh_print_verilog_instance_params_for_ios(FILE* ff, long tot_io, gh_route_side_t sd, gh_io_kind_t iok){
	fflush(ff);
	for(long ii = 0; ii < tot_io; ii++){
		gh_string_t io_nm = get_verilog_io_name(ii, sd, iok);
		gh_print_tabs(ff, 2);
		fprintf(ff, ".%s(%s)", io_nm.c_str(), io_nm.c_str());
		fprintf(ff, ",\n");
	}
	fflush(ff);
}

void
htarget_box::print_verilog_instance_lognet_target_box_for_wrapper(FILE* ff){
	fprintf(ff, R"base(
	lognet_target_box_%ld #(.ASZ(ASZ), .DSZ(DSZ))
	it_wrapper (
		`NS_INSTA_GLB_CHNL(gch, gch),
)base", target->bx_idx);
	
	gh_print_verilog_instance_params_for_ios(ff, (long)lft_in.size(), gh_left_side, gh_in_kind);
	gh_print_verilog_instance_params_for_ios(ff, (long)lft_out.size(), gh_left_side, gh_out_kind);
	gh_print_verilog_instance_params_for_ios(ff, (long)rgt_in.size(), gh_right_side, gh_in_kind);
	gh_print_verilog_instance_params_for_ios(ff, (long)rgt_out.size(), gh_right_side, gh_out_kind);
	
	gh_string_t itf_in_nm = get_verilog_target_param_name(gh_in_kind);
	gh_string_t itf_out_nm = get_verilog_target_param_name(gh_out_kind);
	
	gh_print_tabs(ff, 2);
	fprintf(ff, ".%s(%s)", itf_in_nm.c_str(), itf_in_nm.c_str());
	fprintf(ff, ",\n");
	
	gh_print_tabs(ff, 2);
	fprintf(ff, ".%s(%s)", itf_out_nm.c_str(), itf_out_nm.c_str());
	fprintf(ff, "\n");
	
	fprintf(ff, "\t); \n\n");
}

void
htarget_box::print_verilog_module_lognet_target_wrapper_box(FILE* ff, long num_direct_chns, long num_direct_paks){
	
	fprintf(ff, R"base(
`include "hglobal.v"

`default_nettype	none

module lognet_target_wrapper_box_%ld
#(parameter ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	`NS_DECLARE_GLB_CHNL(gch),
)base", target->bx_idx);
	
	bool can_have_direct = (lft_in.size() == lft_out.size());

	if(can_have_direct){
		GH_CK(rgt_in.size() == rgt_out.size());
		GH_CK(rgt_in.size() == lft_in.size());
		long tot_io = (long)lft_in.size();
		
		gh_print_verilog_params_for_direct_channels(ff, tot_io, num_direct_chns, gh_left_side, gh_in_kind);
		gh_print_verilog_params_for_direct_channels(ff, tot_io, num_direct_chns, gh_left_side, gh_out_kind);
		gh_print_verilog_params_for_direct_channels(ff, tot_io, num_direct_chns, gh_right_side, gh_in_kind);
		gh_print_verilog_params_for_direct_channels(ff, tot_io, num_direct_chns, gh_right_side, gh_out_kind);

		long tot_sd_chns = tot_io + num_direct_chns;
		gh_print_verilog_params_for_direct_packets(ff, tot_sd_chns, num_direct_paks, gh_left_side, gh_in_kind);
		gh_print_verilog_params_for_direct_packets(ff, tot_sd_chns, num_direct_paks, gh_left_side, gh_out_kind);
		gh_print_verilog_params_for_direct_packets(ff, tot_sd_chns, num_direct_paks, gh_right_side, gh_in_kind);
		gh_print_verilog_params_for_direct_packets(ff, tot_sd_chns, num_direct_paks, gh_right_side, gh_out_kind);
		
	}

	gh_print_verilog_params_for_ios(ff, lft_in, gh_left_side, gh_in_kind);
	gh_print_verilog_params_for_ios(ff, lft_out, gh_left_side, gh_out_kind);
	gh_print_verilog_params_for_ios(ff, rgt_in, gh_right_side, gh_in_kind);
	gh_print_verilog_params_for_ios(ff, rgt_out, gh_right_side, gh_out_kind);
	
	print_verilog_target_param(ff);

	fprintf(ff, ");\n");

	if(can_have_direct){
		long tot_io = (long)lft_in.size();
		
		gh_print_verilog_assigns_for_direct_ios(ff, tot_io, num_direct_chns, num_direct_paks);
	}
	
	print_verilog_instance_lognet_target_box_for_wrapper(ff);
	
	fprintf(ff, R"base(

 
endmodule

)base");
	
}

