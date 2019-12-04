
`include "hglobal.v"

`default_nettype	none

module ln_1to2
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
