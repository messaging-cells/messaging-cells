
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
hnode::get_verilog_send_interface_prefix(int num_itf){
	gh_string_t o_str = "snd_" + num_itf;
	return o_str;
}

gh_string_t
hnode::get_verilog_receive_interface_prefix(int num_itf){
	gh_string_t o_str = "rcv_" + num_itf;
	return o_str;
}

gh_string_t
hnode::get_verilog_send_node_interface_prefix(hnode* out){
	gh_string_t o_str = get_verilog_id() + "_" + out->get_verilog_id();
	return o_str;
}

gh_string_t
hnode::get_verilog_receive_node_interface_prefix(hnode* in){
	gh_string_t o_str = in->get_verilog_id() + "_" + get_verilog_id();
	return o_str;
}

gh_string_t
hnode::get_verilog_snd_src(int num_itf, bool rg){
	const char* suf = (rg)?("reg"):("out");
	gh_string_t o_str = get_verilog_send_interface_prefix(num_itf) + "_source_" + suf;
	return o_str;
}
	
gh_string_t
hnode::get_verilog_snd_dst(int num_itf, bool rg){
	const char* suf = (rg)?("reg"):("out");
	gh_string_t o_str = get_verilog_send_interface_prefix(num_itf) + "_destination_" + suf;
	return o_str;
}
	
gh_string_t
hnode::get_verilog_snd_dat(int num_itf, bool rg){
	const char* suf = (rg)?("reg"):("out");
	gh_string_t o_str = get_verilog_send_interface_prefix(num_itf) + "_data_" + suf;
	return o_str;
}
	
gh_string_t
hnode::get_verilog_snd_req(int num_itf, bool rg){
	const char* suf = (rg)?("reg"):("out");
	gh_string_t o_str = get_verilog_send_interface_prefix(num_itf) + "_request_" + suf;
	return o_str;
}
	
gh_string_t
hnode::get_verilog_snd_ack(int num_itf){
	gh_string_t o_str = get_verilog_send_interface_prefix(num_itf) + "_acknowledgement_in";
	return o_str;
}
	
gh_string_t
hnode::get_verilog_rcv_src(int num_itf){
	gh_string_t o_str = get_verilog_receive_interface_prefix(num_itf) + "_source_in";
	return o_str;
}
	
gh_string_t
hnode::get_verilog_rcv_dst(int num_itf){
	gh_string_t o_str = get_verilog_receive_interface_prefix(num_itf) + "_destination_in";
	return o_str;
}
	
gh_string_t
hnode::get_verilog_rcv_dat(int num_itf){
	gh_string_t o_str = get_verilog_receive_interface_prefix(num_itf) + "_data_in";
	return o_str;
}
	
gh_string_t
hnode::get_verilog_rcv_req(int num_itf){
	gh_string_t o_str = get_verilog_receive_interface_prefix(num_itf) + "_request_in";
	return o_str;
}
	
gh_string_t
hnode::get_verilog_rcv_ack(int num_itf, bool rg){
	const char* suf = (rg)?("reg"):("out");
	gh_string_t o_str = get_verilog_receive_interface_prefix(num_itf) + "_acknowledgement_" + suf;
	return o_str;
}
	
void
hnode::print_verilog_send_interface(FILE* ff, int num_itf){
	fprintf(ff, "\t output wire [ASZ-1:0] %s,\n", get_verilog_snd_src(num_itf, false).c_str());
	fprintf(ff, "\t output wire [ASZ-1:0] %s,\n", get_verilog_snd_dst(num_itf, false).c_str());
	fprintf(ff, "\t output wire [DSZ-1:0] %s,\n", get_verilog_snd_dat(num_itf, false).c_str());
	fprintf(ff, "\t output wire %s,\n", get_verilog_snd_req(num_itf, false).c_str());
	fprintf(ff, "\t input wire %s,\n", get_verilog_snd_ack(num_itf).c_str());
}

void
hnode::print_verilog_receive_interface(FILE* ff, int num_itf){
	fprintf(ff, "\t input wire [ASZ-1:0] %s,\n", get_verilog_rcv_src(num_itf).c_str());
	fprintf(ff, "\t input wire [ASZ-1:0] %s,\n", get_verilog_rcv_dst(num_itf).c_str());
	fprintf(ff, "\t input wire [DSZ-1:0] %s,\n", get_verilog_rcv_dat(num_itf).c_str());
	fprintf(ff, "\t input wire %s,\n", get_verilog_rcv_req(num_itf).c_str());
	fprintf(ff, "\t output wire %s,\n", get_verilog_rcv_ack(num_itf, false).c_str());
}

void
hnode::print_verilog_send_registers(FILE* ff, int num_itf){
	fprintf(ff, "\t reg [ASZ-1:0] %s,\n", get_verilog_snd_src(num_itf).c_str());
	fprintf(ff, "\t reg [ASZ-1:0] %s,\n", get_verilog_snd_dst(num_itf).c_str());
	fprintf(ff, "\t reg [DSZ-1:0] %s,\n", get_verilog_snd_dat(num_itf).c_str());
	fprintf(ff, "\t reg [0:0] %s,\n", get_verilog_snd_req(num_itf).c_str());
	
}

void
hnode::print_verilog_receive_registers(FILE* ff, int num_itf){
	fprintf(ff, "\t reg [0:0] %s,\n", get_verilog_rcv_ack(num_itf).c_str());
}

void
hnode::print_verilog_send_node_interface(FILE* ff, hnode* out){
}

void
hnode::print_verilog_receive_node_interface(FILE* ff, hnode* out){
}


