
`include "hglobal.v"

`default_nettype	none

module ln_2to1
#(parameter ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	
	// out
	output wire [ASZ-1:0] o_addr,
	output wire [DSZ-1:0] o_dat,
	output wire o_req,
	input wire i_ack,
	
	// in_0
	input wire [ASZ-1:0] i_0_addr,
	input wire [DSZ-1:0] i_0_dat,
	input wire i_0_req,
	output wire o_0_ack,
	
	// in_1
	input wire [ASZ-1:0] i_1_addr,
	input wire [DSZ-1:0] i_1_dat,
	input wire i_1_req,
	output wire o_1_ack
	
);
 
	// out regs
	reg [ASZ-1:0] r_addr = 0;
	reg [DSZ-1:0] r_dat = 0;
	reg [0:0] r_req = `OFF;

	// in_0 regs
	reg [0:0] r_0_ack = `OFF;
	
	// in_1 regs
	reg [0:0] r_1_ack = `OFF;
	
	reg [0:0] choose_0 = `TRUE;
	
	wire in0_rq = (i_0_req && ! r_0_ack);
	wire in1_rq = (i_1_req && ! r_1_ack);
	
	//out
	always @(posedge i_clk)
	begin
		if((! r_req) && (! i_ack)) begin
			if(in0_rq && in1_rq) begin
				if(choose_0) begin
					choose_0 <= `FALSE;
					`COPY_MSG(i_0_addr, i_0_dat, r_addr, r_dat)
					r_req <= `ON;
					r_0_ack <= `ON;
				end else begin
					choose_0 <= `TRUE;
					`COPY_MSG(i_1_addr, i_1_dat, r_addr, r_dat)
					r_req <= `ON;
					r_1_ack <= `ON;
				end
			end
			if(in0_rq && ! in1_rq) begin
				`COPY_MSG(i_0_addr, i_0_dat, r_addr, r_dat)
				r_req <= `ON;
				r_0_ack <= `ON;
			end
			if(! in0_rq && in1_rq) begin
				`COPY_MSG(i_1_addr, i_1_dat, r_addr, r_dat)
				r_req <= `ON;
				r_1_ack <= `ON;
			end
		end 
		
		if((! i_0_req) && r_0_ack) begin
			r_0_ack <= `OFF;
		end
		if((! i_1_req) && r_1_ack) begin
			r_1_ack <= `OFF;
		end
		if(r_req && i_ack) begin
			r_req <= `OFF;
		end
	end
		
	//out
	assign o_addr = r_addr;
	assign o_dat = r_dat;
	assign o_req = r_req;

	//in_0
	assign o_0_ack = r_0_ack;
	
	//in_1
	assign o_1_ack = r_1_ack;
	
endmodule
