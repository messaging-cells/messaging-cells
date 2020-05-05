
#include "hgen_net.h"

using namespace std;

gh_string_t
hnode::get_verilog_send_node_interface_name(hnode** ppout){
	GH_CK(ppout != gh_null);
	GH_CK(*ppout != gh_null);
	if(*ppout == this){
		hnode** pnd = get_pt_out0();
		if(pnd == ppout){
			gh_string_t o_str = get_verilog_id() + gh_vl_out0;
			return o_str;
		} 
		pnd = get_pt_out1();
		GH_CK(pnd == ppout);
		gh_string_t o_str = get_verilog_id() + gh_vl_out1;
		return o_str;
	}
	gh_string_t o_str = get_verilog_id() + gh_vl_sep + (*ppout)->get_verilog_id();
	return o_str;
}

gh_string_t
hnode::get_verilog_receive_node_interface_name(hnode** ppin){
	GH_CK(ppin != gh_null);
	GH_CK(*ppin!= gh_null);
	if(*ppin == this){
		hnode** pnd = get_pt_in0();
		if(pnd == ppin){
			gh_string_t o_str = gh_vl_in0 + get_verilog_id();
			return o_str;
		} 
		pnd = get_pt_in1();
		GH_CK(pnd == ppin);
		gh_string_t o_str = gh_vl_in1 + get_verilog_id();
		return o_str;
	}
	gh_string_t o_str = (*ppin)->get_verilog_id() + gh_vl_sep + get_verilog_id();
	return o_str;
}

void
gh_print_verilog_send_interface(FILE* ff, gh_string_t itf_nm, bool with_final_comma){
	fprintf(ff, "\t `NS_DECLARE_OUT_CHNL(%s)", itf_nm.c_str());
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
}

void
gh_print_verilog_receive_interface(FILE* ff, gh_string_t itf_nm, bool with_final_comma){
	fprintf(ff, "\t `NS_DECLARE_IN_CHNL(%s)", itf_nm.c_str());
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
}

void
gh_print_verilog_declare_link_interface(FILE* ff, gh_string_t itf_nm){
	gh_str_set_t all_itf = GH_GLOBALS.all_verilog_declared_interfaces;
	auto it = all_itf.find(itf_nm);
	if(it == all_itf.end()){
		return;
	}
	all_itf.insert(itf_nm);
	
	fprintf(ff, "\t `NS_DECLARE_LINK(%s)", itf_nm.c_str());
}

void
gh_print_verilog_assign_interface(FILE* ff, gh_string_t itf_nm_1, gh_string_t itf_nm_2){
	gh_str_set_t all_itf = GH_GLOBALS.all_verilog_declared_interfaces;
	auto it = all_itf.find(itf_nm_2);
	if(it == all_itf.end()){
		return;
	}
	all_itf.insert(itf_nm_2);
	
	fprintf(ff, "\t `NS_ASSIGN_OUT_MSG(%s, %s)", itf_nm_1.c_str(), itf_nm_2.c_str());
	
	fprintf(ff, "\n");
}

void
gh_print_verilog_instance_send_interface(FILE* ff, gh_string_t itf_nm_1, gh_string_t itf_nm_2, bool with_final_comma){
	fprintf(ff, "\t `NS_INSTA_SND_CHNL(%s, %s)", itf_nm_1.c_str(), itf_nm_2.c_str());
	
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
	fprintf(ff, "\n");
}

void
gh_print_verilog_instance_receive_interface(FILE* ff, gh_string_t itf_nm_1, gh_string_t itf_nm_2, bool with_final_comma){
	fprintf(ff, "\t `NS_INSTA_RCV_CHNL(%s, %s)", itf_nm_1.c_str(), itf_nm_2.c_str());
	
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
	fprintf(ff, "\n");
}

void
hnode_2to1::print_verilog_2to1_instance(FILE* ff){
	gh_string_t i0_itf_nm = get_verilog_receive_node_interface_name(&in0);
	gh_string_t i1_itf_nm = get_verilog_receive_node_interface_name(&in1);
	gh_string_t o0_itf_nm = get_verilog_send_node_interface_name(&out0);
	
	gh_print_verilog_declare_link_interface(ff, i0_itf_nm);
	gh_print_verilog_declare_link_interface(ff, i1_itf_nm);
	gh_print_verilog_declare_link_interface(ff, o0_itf_nm);

	fprintf(ff, "lognet_2to1_node \n gt2to1 (\n\t .i_clk(i_clk), \n");
	
	gh_print_verilog_instance_send_interface(ff, gh_vl_snd0, o0_itf_nm);
	gh_print_verilog_instance_receive_interface(ff, gh_vl_rcv0, i0_itf_nm);
	gh_print_verilog_instance_receive_interface(ff, gh_vl_rcv1, i1_itf_nm, false);
	
	fprintf(ff, "); \n\n");
	
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
	gh_string_t val = "" + slc_edge;
	return val;
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
hnode_1to2::print_verilog_1to2_instance(FILE* ff){
	gh_string_t i0_itf_nm = get_verilog_receive_node_interface_name(&in0);
	gh_string_t o0_itf_nm = get_verilog_send_node_interface_name(&out0);
	gh_string_t o1_itf_nm = get_verilog_send_node_interface_name(&out1);
	
	gh_print_verilog_declare_link_interface(ff, i0_itf_nm);
	gh_print_verilog_declare_link_interface(ff, o0_itf_nm);
	gh_print_verilog_declare_link_interface(ff, o1_itf_nm);
	
	gh_string_t op1 = get_verilog_oper_1();
	gh_string_t val1 = get_verilog_ref_val_1();
	gh_string_t is_rng = get_verilog_is_range();
	gh_string_t op2 = get_verilog_oper_2();
	gh_string_t val2 = get_verilog_ref_val_2();
	
	fprintf(ff, R"base(
	lognet_1to2_node #(.OPER_1(%s), .REF_VAL_1(%s), .IS_RANGE(%s), .OPER_2(%s), .REF_VAL_2(%s))
	gt1to2 (
		.i_clk(i_clk),
)base", 
	op1.c_str(),
	val1.c_str(),
	is_rng.c_str(),
	op2.c_str(),
	val2.c_str()
	);
	
	gh_print_verilog_instance_send_interface(ff, gh_vl_snd0, o0_itf_nm);
	gh_print_verilog_instance_send_interface(ff, gh_vl_snd1, o1_itf_nm);
	gh_print_verilog_instance_receive_interface(ff, gh_vl_rcv0, i0_itf_nm, false);
	
	fprintf(ff, "); \n\n");
	
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
			gh_print_verilog_declare_link_interface(ff, itf_nm);
			
			gh_string_t io_nm = get_verilog_io_name(ii, sd, iok);
			
			gh_print_verilog_assign_interface(ff, io_nm, itf_nm);
			
			fprintf(ff, "\n");
		} 
	}
	fflush(ff);
}

void
gh_print_verilog_params_for_ios(FILE* ff, ppnode_vec_t& all_io, gh_route_side_t sd, gh_io_kind_t iok){
	fflush(ff);
	for(long ii = 0; ii < (long)all_io.size(); ii++){
		gh_string_t io_nm = get_verilog_io_name(ii, sd, iok);
		if(iok == gh_in_kind){
			gh_print_verilog_receive_interface(ff, io_nm);
		} else {
			GH_CK(iok == gh_out_kind);
			gh_print_verilog_send_interface(ff, io_nm);
		}
	}
	fflush(ff);
}

void
gh_print_verilog_code_for_nodes(FILE* ff, pnode_vec_t& all_nd){
	for(long ii = 0; ii < (long)all_nd.size(); ii++){
		hnode* the_nd = all_nd[ii];
		GH_CK(the_nd != gh_null);
		if(the_nd->is_1to2()){
			hnode_1to2* nd = (hnode_1to2*)the_nd;
			nd->print_verilog_1to2_instance(ff);
		} else {
			GH_CK(the_nd->is_2to1());
			hnode_2to1* nd = (hnode_2to1*)the_nd;
			nd->print_verilog_2to1_instance(ff);
		}
	}
}

gh_string_t
htarget_box::get_verilog_module_name(){
	GH_CK(target != gh_null);
	gh_string_t ss = gh_vl_tg_mod + long_to_string(target->bx_idx);
	return ss;
}

gh_string_t
htarget_box::get_verilog_target_param_name(gh_io_kind_t iok){
	gh_string_t iok_nm = get_verilog_io_kind(iok);
	GH_CK(target != gh_null);
	gh_string_t ss = gh_vl_tgt + iok_nm + long_to_string(target->bx_idx);
	return ss;
}

void 
htarget_box::print_verilog_target_param(FILE* ff){
	gh_string_t itf_in_nm = get_verilog_target_param_name(gh_in_kind);
	gh_string_t itf_out_nm = get_verilog_target_param_name(gh_out_kind);
	gh_print_verilog_receive_interface(ff, itf_in_nm);
	gh_print_verilog_send_interface(ff, itf_out_nm, false);
}

void
htarget_box::print_verilog_target_assign(FILE* ff){
	gh_string_t itf_in_nm = get_verilog_target_param_name(gh_in_kind);
	gh_string_t itf_out_nm = get_verilog_target_param_name(gh_out_kind);
	GH_CK(target != gh_null);
	gh_string_t tg_in_itf_nm = target->get_verilog_receive_node_interface_name(&(target->in0));
	gh_string_t tg_out_itf_nm = target->get_verilog_send_node_interface_name(&(target->out0));
	
	gh_print_verilog_assign_interface(ff, itf_in_nm, tg_in_itf_nm);
	gh_print_verilog_assign_interface(ff, itf_out_nm, tg_out_itf_nm);
}

void
htarget_box::print_verilog_module_lognet_target_box(FILE* ff){
	
	fprintf(ff, R"base(
`include "hglobal.v"

`default_nettype	none

module lognet_target_box_%ld
#(parameter ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,
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
runner_print_verilog_target_box::print_help(){
	GH_GLOBALS.compl_sys.print_last_complete_arg();
	FILE* of = GH_GLOBALS.compl_sys.args_compl_output;
	fprintf(of, "<num_in> <num_out> [-pb <pw_base>] \n");
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
	fprintf(stdout, "// test_get_target base=%ld #in=%ld #out=%ld\n", bb, nin, nout);

	htarget_box* bx = new htarget_box(bb);
	
	long tg_idx = 0;
	long tgs_sz = 0;
	gh_dbg_calc_idx_and_sz(nin, nout, bb, tg_idx, tgs_sz);
	
	slice_vec all_addr;
	bx->init_target_box(tg_idx, nin, nout, all_addr, tgs_sz);

	fprintf(stdout, "// ===========\n");
	
	GH_GLOBALS.CK_LINK_MODE = gh_valid_self_ck_mod;

	bx->print_box(stdout, gh_full_prt);
	
	fprintf(stdout, "// ===========\n");
	fprintf(stdout, "// ===========\n");
	fprintf(stdout, "// ===========\n");
	
	bx->print_verilog_module_lognet_target_box(stdout);
	
	delete bx;
	return 0;
}



int test_verilog(gh_str_list_t& lt_args){
	bool is_cmpl = GH_GLOBALS.compl_sys.args_orig_has_compl;
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
	if(! is_cmpl){
		fprintf(stdout, "ENDING_VERILOG_TESTS______________________\n");
	}
	return resp;
}

