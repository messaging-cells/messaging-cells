
`include "hglobal.v"

`define MSG_DAT_0 5
`define MSG_DAT_1 7

`default_nettype	none

module io_2to1
#(parameter MIN_ADDR=1, MAX_ADDR=1, ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	
	// SRC_0
	output wire [ASZ-1:0] o_0_addr,
	output wire [DSZ-1:0] o_0_dat,
	output wire o_0_req,
	input wire i_0_ack,
	
	// SRC_1
	output wire [ASZ-1:0] o_1_addr,
	output wire [DSZ-1:0] o_1_dat,
	output wire o_1_req,
	input wire i_1_ack,
	
	// SNK
	input wire [ASZ-1:0] i_addr,
	input wire [DSZ-1:0] i_dat,
	input wire i_req,
	output wire o_ack,
	output wire o_err
	
);
 
	// SRC_0 regs
	reg [ASZ-1:0] r_0_addr = MIN_ADDR;
	reg [DSZ-1:0] r_0_dat = 0;
	reg [0:0] r_0_req = `OFF;

	// SRC_1 regs
	reg [ASZ-1:0] r_1_addr = MIN_ADDR;
	reg [DSZ-1:0] r_1_dat = 0;
	reg [0:0] r_1_req = `OFF;

	// SNK regs
	reg [0:0] r_ack = `OFF;
	reg [ASZ-1:0] r_0_ck_addr = 0;
	reg [ASZ-1:0] r_1_ck_addr = 0;
	reg [0:0] r_err = `OFF;
	
	//SRC_0
	always @(posedge i_clk)
	begin
		if((! r_0_req) && (! i_0_ack)) begin
			if(r_0_addr == MAX_ADDR) begin
				r_0_addr <= MIN_ADDR;
			end
			else begin
				r_0_addr <= r_0_addr + 1;
			end
			r_0_dat <= `MSG_DAT_0;
			r_0_req <= `ON;
		end else 
		if(r_0_req && i_0_ack) begin
			r_0_req <= `OFF;
		end
	end
		
	//SRC_1
	always @(posedge i_clk)
	begin
		if((! r_1_req) && (! i_1_ack)) begin
			if(r_1_addr == MAX_ADDR) begin
				r_1_addr <= MIN_ADDR;
			end
			else begin
				r_1_addr <= r_1_addr + 1;
			end
			r_1_dat <= `MSG_DAT_1;
			r_1_req <= `ON;
		end else 
		if(r_1_req && i_1_ack) begin
			r_1_req <= `OFF;
		end
	end
		
	//SNK
	always @(posedge i_clk)
	begin
		if(i_req && (! r_ack)) begin
			if(i_dat == `MSG_DAT_0) begin
				if((i_addr > MIN_ADDR) && ((r_0_ck_addr + 1) != i_addr)) begin
					r_err <= `ON;
				end else begin
					r_0_ck_addr <= i_addr;
				end
			end 
			if(i_dat == `MSG_DAT_1) begin
				if((i_addr > MIN_ADDR) && ((r_1_ck_addr + 1) != i_addr)) begin
					r_err <= `ON;
				end else begin
					r_1_ck_addr <= i_addr;
				end
			end 
			r_ack <= `ON;
		end
		else
		if((! i_req) && r_ack) begin
			r_ack <= `OFF;
		end
	end
	
	//SRC_0
	assign o_0_addr = r_0_addr;
	assign o_0_dat = r_0_dat;
	assign o_0_req = r_0_req;

	//SRC_1
	assign o_1_addr = r_1_addr;
	assign o_1_dat = r_1_dat;
	assign o_1_req = r_1_req;

	//SNK
	assign o_ack = r_ack;
	assign o_err = r_err;
	
endmodule
