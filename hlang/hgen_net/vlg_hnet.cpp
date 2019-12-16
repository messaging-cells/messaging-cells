
#include "hgen_net.h"

using namespace std;


void 
gh_verilog_write_module_lognet_1to2_node(FILE* ff){
	const char* nm1 = "HOLA";
	const char* nm2 = "JOSE";
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
	output wire [ASZ-1:0] o_0_addr,
	output wire [DSZ-1:0] o_0_dat,
	output wire o_0_req,
	input wire i_0_ack,
	
	// out1
	output wire [ASZ-1:0] o_1_addr,
	output wire [DSZ-1:0] o_1_dat,
	output wire o_1_req,
	input wire i_1_ack,
	
	// in
	input wire [ASZ-1:0] i_addr,
	input wire [DSZ-1:0] i_dat,
	input wire i_req,
	output wire o_ack
	
);
 
	// out1 regs
	reg [ASZ-1:0] r_0_addr = 0;
	reg [DSZ-1:0] r_0_dat = 0;
	reg [0:0] r_0_req = `OFF;

	// out2 regs
	reg [ASZ-1:0] r_1_addr = 0;
	reg [DSZ-1:0] r_1_dat = 0;
	reg [0:0] r_1_req = `OFF;

	// inp regs
	reg [0:0] r_ack = `OFF;
	
	always @(posedge i_clk)
	begin
		if(i_req && (! r_ack)) begin
			if(`RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, i_addr, OPER_2, REF_VAL_2, i_addr)) begin
				if(! r_0_req && ! i_0_ack) begin
					`COPY_MSG(i_addr, i_dat, r_0_addr, r_0_dat)
					r_0_req <= `ON;
					r_ack <= `ON;
				end 
			end else begin
				if(! r_1_req && ! i_1_ack) begin
					`COPY_MSG(i_addr, i_dat, r_1_addr, r_1_dat)
					r_1_req <= `ON;
					r_ack <= `ON;
				end 
			end
		end
		
		if((! i_req) && r_ack) begin
			r_ack <= `OFF;
		end
		if(r_0_req && i_0_ack) begin
			r_0_req <= `OFF;
		end
		if(r_1_req && i_1_ack) begin
			r_1_req <= `OFF;
		end
	end
	
	//out1
	assign o_0_addr = r_0_addr;
	assign o_0_dat = r_0_dat;
	assign o_0_req = r_0_req;

	//out2
	assign o_1_addr = r_1_addr;
	assign o_1_dat = r_1_dat;
	assign o_1_req = r_1_req;

	//inp
	assign o_ack = r_ack;
	
endmodule

// %s %s
	
)base", nm1, nm2);
	
}

gh_string_t
hnode::get_verilog_send_node_interface_name(hnode* out){
	gh_string_t o_str = get_verilog_id() + "_" + out->get_verilog_id();
	return o_str;
}

gh_string_t
hnode::get_verilog_receive_node_interface_name(hnode* in){
	gh_string_t o_str = in->get_verilog_id() + "_" + get_verilog_id();
	return o_str;
}

void
hnode_box::print_verilog_send_interface(FILE* ff, gh_string_t itf_nm){
	itf_nm = gh_vl_snd + itf_nm;
	
	verilog_interface itf;
	itf.init_verilog_interface(itf_nm);
	
	fprintf(ff, "\t output wire [ASZ-1:0] %s,\n", itf.src.c_str());
	fprintf(ff, "\t output wire [ASZ-1:0] %s,\n", itf.dst.c_str());
	fprintf(ff, "\t output wire [DSZ-1:0] %s,\n", itf.dat.c_str());
	fprintf(ff, "\t output wire %s,\n", itf.req.c_str());
	fprintf(ff, "\t input wire %s,\n", itf.ack.c_str());
}

void
hnode_box::print_verilog_receive_interface(FILE* ff, gh_string_t itf_nm){
	itf_nm = gh_vl_rcv + itf_nm;
	
	verilog_interface itf;
	itf.init_verilog_interface(itf_nm);
	
	fprintf(ff, "\t input wire [ASZ-1:0] %s,\n", itf.src.c_str());
	fprintf(ff, "\t input wire [ASZ-1:0] %s,\n", itf.dst.c_str());
	fprintf(ff, "\t input wire [DSZ-1:0] %s,\n", itf.dat.c_str());
	fprintf(ff, "\t input wire %s,\n", itf.req.c_str());
	fprintf(ff, "\t output wire %s,\n", itf.ack.c_str());
}

void
hnode::print_verilog_declare_link_interface(FILE* ff, gh_string_t itf_nm){
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
hnode_2to1::print_verilog_2to1_instance(FILE* ff){
	gh_string_t i0_itf_nm = get_verilog_receive_node_interface_name(in0);
	gh_string_t i1_itf_nm = get_verilog_receive_node_interface_name(in1);
	gh_string_t o0_itf_nm = get_verilog_send_node_interface_name(out0);
	
	print_verilog_declare_link_interface(ff, i0_itf_nm);
	print_verilog_declare_link_interface(ff, i1_itf_nm);
	print_verilog_declare_link_interface(ff, o0_itf_nm);
	
	verilog_interface i0;
	verilog_interface i1;
	verilog_interface o0;
	
	i0.init_verilog_interface(i0_itf_nm);
	i1.init_verilog_interface(i1_itf_nm);
	o0.init_verilog_interface(o0_itf_nm);
	
	fprintf(ff, R"base(
	ln_2to1 
	gt2to1 (
		.i_clk(i_clk),
		// out0
		.o_addr(%s),
		.o_dat(%s),
		.o_req(%s),
		.i_ack(%s),
		// in_0
		.i_0_addr(%s),
		.i_0_dat(%s),
		.i_0_req(%s),
		.o_0_ack(%s),
		// in_1
		.i_1_addr(%s),
		.i_1_dat(%s),
		.i_1_req(%s),
		.o_1_ack(%s),
	);
	
)base", 
//	o0.src.c_str(),
	o0.dst.c_str(),
	o0.dat.c_str(),
	o0.req.c_str(),
	o0.ack.c_str(),
	
//	i0.src.c_str(),
	i0.dst.c_str(),
	i0.dat.c_str(),
	i0.req.c_str(),
	i0.ack.c_str(),

//	i1.src.c_str(),
	i1.dst.c_str(),
	i1.dat.c_str(),
	i1.req.c_str(),
	i1.ack.c_str()
	
	);
	
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
	gh_string_t i0_itf_nm = get_verilog_receive_node_interface_name(in0);
	gh_string_t o0_itf_nm = get_verilog_send_node_interface_name(out0);
	gh_string_t o1_itf_nm = get_verilog_send_node_interface_name(out1);
	
	print_verilog_declare_link_interface(ff, i0_itf_nm);
	print_verilog_declare_link_interface(ff, o0_itf_nm);
	print_verilog_declare_link_interface(ff, o1_itf_nm);
	
	verilog_interface i0;
	verilog_interface o0;
	verilog_interface o1;
	
	i0.init_verilog_interface(i0_itf_nm);
	o0.init_verilog_interface(o0_itf_nm);
	o1.init_verilog_interface(o1_itf_nm);
	
	gh_string_t op1 = get_verilog_oper_1();
	gh_string_t val1 = get_verilog_ref_val_1();
	gh_string_t is_rng = get_verilog_is_range();
	gh_string_t op2 = get_verilog_oper_2();
	gh_string_t val2 = get_verilog_ref_val_2();
	
	fprintf(ff, R"base(
	ln_1to2 #(.OPER_1(`%s), .REF_VAL_1(%s), .IS_RANGE(`%s), .OPER_2(`%s), .REF_VAL_2(%s))
	gt1to2 (
		.i_clk(i_clk),
		// out0
		.o_0_addr(%s),
		.o_0_dat(%s),
		.o_0_req(%s),
		.i_0_ack(%s),
		// out1
		.o_1_addr(%s),
		.o_1_dat(%s),
		.o_1_req(%s),
		.i_1_ack(%s),
		// in
		.i_addr(%s),
		.i_dat(%s),
		.i_req(%s),
		.o_ack(%s),
	);

)base", 
	op1.c_str(),
	val1.c_str(),
	is_rng.c_str(),
	op2.c_str(),
	val2.c_str(),

//	o0.src.c_str(),
	o0.dst.c_str(),
	o0.dat.c_str(),
	o0.req.c_str(),
	o0.ack.c_str(),
	
//	o1.src.c_str(),
	o1.dst.c_str(),
	o1.dat.c_str(),
	o1.req.c_str(),
	o1.ack.c_str(),
	
//	i0.src.c_str(),
	i0.dst.c_str(),
	i0.dat.c_str(),
	i0.req.c_str(),
	i0.ack.c_str()

	);
	
}

