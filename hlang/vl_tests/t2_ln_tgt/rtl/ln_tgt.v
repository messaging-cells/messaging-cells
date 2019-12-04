
`include "hglobal.v"

`default_nettype	none

module ln_tgt
#(parameter LOCAL_ADDR=1, MIN_ADDR=1, MAX_ADDR=1, ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	
	// SRC
	output wire [ASZ-1:0] o_addr,
	output wire [DSZ-1:0] o_dat,
	output wire o_req,
	input wire i_ack,
	
	// SNK
	input wire [ASZ-1:0] i_addr,
	input wire [DSZ-1:0] i_dat,
	input wire i_req,
	output wire o_ack,
	output wire [DSZ-1:0] o_ck_dat,
	output wire o_err
	
);
 
	// SRC regs
	reg [ASZ-1:0] r_addr = MIN_ADDR;
	reg [DSZ-1:0] r_dat = 0;
	reg [0:0] r_req = `OFF;

	// SNK regs
	reg [0:0] r_ack = `OFF;
	reg [DSZ-1:0] r_ck_dat = 0;
	reg [0:0] r_err = `OFF;
	
	//SRC
	always @(posedge i_clk)
	begin
		if((! r_req) && (! i_ack)) begin
			if(r_addr == MAX_ADDR) begin
				if(LOCAL_ADDR != MIN_ADDR) begin
					r_addr <= MIN_ADDR;
				end else begin
					r_addr <= MIN_ADDR + 1;
				end
			end
			else begin
				if(LOCAL_ADDR != r_addr + 1) begin
					r_addr <= r_addr + 1;
				end else begin
					r_addr <= r_addr + 2;
				end
			end
			r_dat <= r_dat + 1;
			r_req <= `ON;
		end else 
		if(r_req && i_ack) begin
			r_req <= `OFF;
		end
	end
		
	//SNK
	always @(posedge i_clk)
	begin
		if(i_req && (! r_ack)) begin
			if( (i_addr != LOCAL_ADDR) || ((i_dat > 0) && ((r_ck_dat + 1) != i_dat)) ) begin
			//if(i_addr != LOCAL_ADDR) begin
				r_err <= `ON;
			end else begin
				r_ck_dat <= i_dat;
				r_ack <= `ON;
			end
		end
		else
		if((! i_req) && r_ack) begin
			r_ack <= `OFF;
		end
	end
	
	//SRC
	assign o_addr = r_addr;
	assign o_dat = r_dat;
	assign o_req = r_req;

	//SNK
	assign o_ack = r_ack;
	assign o_ck_dat = r_ck_dat;
	assign o_err = r_err;
	
endmodule
