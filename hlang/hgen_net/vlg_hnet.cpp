
#include "hgen_net.h"

using namespace std;


void 
gh_verilog_write_module_lognet_1to2_node(FILE* ff){
	fprintf(ff, R"base(

`include "hglobal.v"

`default_nettype	none

module lognet_1to2_node
#(parameter 
	OPER_1=`GT_OP, REF_VAL_1=0, IS_RANGE=`FALSE, 
	OPER_2=`GT_OP, REF_VAL_2=0, ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	
	// out0
	output wire [ASZ-1:0] snd0_dst,
	output wire [DSZ-1:0] snd0_dat,
	output wire snd0_req,
	input wire snd0_ack,
	
	// out1
	output wire [ASZ-1:0] snd1_dst,
	output wire [DSZ-1:0] snd1_dat,
	output wire snd1_req,
	input wire snd1_ack,
	
	// in
	input wire [ASZ-1:0] rcv0_dst,
	input wire [DSZ-1:0] rcv0_dat,
	input wire rcv0_req,
	output wire rcv0_ack
	
);
 
	// out0 regs
	reg [ASZ-1:0] r_0_addr = 0;
	reg [DSZ-1:0] r_0_dat = 0;
	reg [0:0] r_0_req = `OFF;

	// out1 regs
	reg [ASZ-1:0] r_1_addr = 0;
	reg [DSZ-1:0] r_1_dat = 0;
	reg [0:0] r_1_req = `OFF;

	// in0 regs
	reg [0:0] r_ack = `OFF;
	
	always @(posedge i_clk)
	begin
		if(rcv0_req && (! r_ack)) begin
			if(`RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, rcv0_dst, OPER_2, REF_VAL_2, rcv0_dst)) begin
				if(! r_0_req && ! snd0_ack) begin
					`COPY_MSG(rcv0_dst, rcv0_dat, r_0_addr, r_0_dat)
					r_0_req <= `ON;
					r_ack <= `ON;
				end 
			end else begin
				if(! r_1_req && ! snd1_ack) begin
					`COPY_MSG(rcv0_dst, rcv0_dat, r_1_addr, r_1_dat)
					r_1_req <= `ON;
					r_ack <= `ON;
				end 
			end
		end
		
		if((! rcv0_req) && r_ack) begin
			r_ack <= `OFF;
		end
		if(r_0_req && snd0_ack) begin
			r_0_req <= `OFF;
		end
		if(r_1_req && snd1_ack) begin
			r_1_req <= `OFF;
		end
	end
	
	//out1
	assign snd0_dst = r_0_addr;
	assign snd0_dat = r_0_dat;
	assign snd0_req = r_0_req;

	//out2
	assign snd1_dst = r_1_addr;
	assign snd1_dat = r_1_dat;
	assign snd1_req = r_1_req;

	//inp
	assign rcv0_ack = r_ack;
	
endmodule

)base");
	
}

gh_string_t
hnode::get_verilog_send_node_interface_name(hnode** ppout){
	GH_CK(ppout != gh_null);
	GH_CK(*ppout != gh_null);
	if(*ppout == this){
		hnode* nd = get_out0();
		if(&nd == ppout){
			gh_string_t o_str = get_verilog_id() + gh_vl_out0;
			return o_str;
		} 
		nd = get_out1();
		GH_CK(&nd == ppout);
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
		hnode* nd = get_in0();
		if(&nd == ppin){
			gh_string_t o_str = gh_vl_in0 + get_verilog_id();
			return o_str;
		} 
		nd = get_in1();
		GH_CK(&nd == ppin);
		gh_string_t o_str = gh_vl_in1 + get_verilog_id();
		return o_str;
	}
	gh_string_t o_str = (*ppin)->get_verilog_id() + gh_vl_sep + get_verilog_id();
	return o_str;
}

void
gh_print_verilog_send_interface(FILE* ff, gh_string_t itf_nm, bool with_final_comma){
	verilog_interface itf;
	itf.init_verilog_interface(itf_nm);
	
	fprintf(ff, "\t output wire [ASZ-1:0] %s,\n", itf.src.c_str());
	fprintf(ff, "\t output wire [ASZ-1:0] %s,\n", itf.dst.c_str());
	fprintf(ff, "\t output wire [DSZ-1:0] %s,\n", itf.dat.c_str());
	fprintf(ff, "\t output wire %s,\n", itf.req.c_str());
	fprintf(ff, "\t input wire %s", itf.ack.c_str());
	if(with_final_comma){
		fprintf(ff, ",");
	}
	fprintf(ff, "\n");
}

void
gh_print_verilog_receive_interface(FILE* ff, gh_string_t itf_nm, bool with_final_comma){
	verilog_interface itf;
	itf.init_verilog_interface(itf_nm);
	
	fprintf(ff, "\t input wire [ASZ-1:0] %s,\n", itf.src.c_str());
	fprintf(ff, "\t input wire [ASZ-1:0] %s,\n", itf.dst.c_str());
	fprintf(ff, "\t input wire [DSZ-1:0] %s,\n", itf.dat.c_str());
	fprintf(ff, "\t input wire %s,\n", itf.req.c_str());
	fprintf(ff, "\t output wire %s", itf.ack.c_str());
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
	
	verilog_interface itf;
	itf.init_verilog_interface(itf_nm);

	fprintf(ff, "\t wire [ASZ-1:0] %s,\n", itf.src.c_str());
	fprintf(ff, "\t wire [ASZ-1:0] %s,\n", itf.dst.c_str());
	fprintf(ff, "\t wire [DSZ-1:0] %s,\n", itf.dat.c_str());
	fprintf(ff, "\t wire %s,\n", itf.req.c_str());
	fprintf(ff, "\t wire %s,\n", itf.ack.c_str());
}

void
gh_print_verilog_assign_interface(FILE* ff, gh_string_t itf_nm_1, gh_string_t itf_nm_2){
	gh_str_set_t all_itf = GH_GLOBALS.all_verilog_declared_interfaces;
	auto it = all_itf.find(itf_nm_2);
	if(it == all_itf.end()){
		return;
	}
	all_itf.insert(itf_nm_2);
	
	verilog_interface itf_1;
	itf_1.init_verilog_interface(itf_nm_1);

	verilog_interface itf_2;
	itf_2.init_verilog_interface(itf_nm_2);
	
	fprintf(ff, "\t assign %s = %s;\n", itf_1.src.c_str(), itf_2.src.c_str());
	fprintf(ff, "\t assign %s = %s;\n", itf_1.dst.c_str(), itf_2.dst.c_str());
	fprintf(ff, "\t assign %s = %s;\n", itf_1.dat.c_str(), itf_2.dat.c_str());
	fprintf(ff, "\t assign %s = %s;\n", itf_1.req.c_str(), itf_2.req.c_str());
	fprintf(ff, "\t assign %s = %s;\n", itf_1.ack.c_str(), itf_2.ack.c_str());
	
	fprintf(ff, "\n");
}

void
gh_print_verilog_instance_interface(FILE* ff, gh_string_t itf_nm_1, gh_string_t itf_nm_2, bool with_final_comma){
	verilog_interface itf_1;
	itf_1.init_verilog_interface(itf_nm_1);

	verilog_interface itf_2;
	itf_2.init_verilog_interface(itf_nm_2);
	
	fprintf(ff, "\t .%s(%s),\n", itf_1.src.c_str(), itf_2.src.c_str());
	fprintf(ff, "\t .%s(%s),\n", itf_1.dst.c_str(), itf_2.dst.c_str());
	fprintf(ff, "\t .%s(%s),\n", itf_1.dat.c_str(), itf_2.dat.c_str());
	fprintf(ff, "\t .%s(%s),\n", itf_1.req.c_str(), itf_2.req.c_str());
	fprintf(ff, "\t .%s(%s)", itf_1.ack.c_str(), itf_2.ack.c_str());
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

	fprintf(ff, "ln_2to1 \n gt2to1 (\n\t .i_clk(i_clk), \n");
	
	gh_print_verilog_instance_interface(ff, gh_vl_snd0, o0_itf_nm);
	gh_print_verilog_instance_interface(ff, gh_vl_rcv0, i0_itf_nm);
	gh_print_verilog_instance_interface(ff, gh_vl_rcv1, i1_itf_nm, false);
	
	fprintf(ff, "); \n\n");
	
}

gh_string_t
edge::get_verilog_oper(){
	gh_string_t op = "INVALID_OPER";
	if(is_gt()){
		if(is_eq()){
			op = "GTE_OP";
			return op;
		}
		op = "GT_OP";
		return op;
	}
	if(is_eq()){
		op = "LTE_OP";
		return op;
	}
	op = "LT_OP";
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
	gh_string_t is_rng = "FALSE";
	bool has_udf = selector.lft.is_undef() || selector.rgt.is_undef();
	if(is_itv && ! has_udf){
		is_rng = "TRUE";
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
	ln_1to2 #(.OPER_1(`%s), .REF_VAL_1(%s), .IS_RANGE(`%s), .OPER_2(`%s), .REF_VAL_2(%s))
	gt1to2 (
		.i_clk(i_clk),
)base", 
	op1.c_str(),
	val1.c_str(),
	is_rng.c_str(),
	op2.c_str(),
	val2.c_str()
	);
	
	gh_print_verilog_instance_interface(ff, gh_vl_snd0, o0_itf_nm);
	gh_print_verilog_instance_interface(ff, gh_vl_snd1, o1_itf_nm);
	gh_print_verilog_instance_interface(ff, gh_vl_rcv0, i0_itf_nm, false);
	
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
htarget_box::print_verilog_base_code(FILE* ff){
	
	fprintf(ff, R"base(
`include "hglobal.v"

`default_nettype	none

module lognet_1to2_node
#(parameter ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,
	
	
);
 
	
endmodule

)base");
	
	
}

