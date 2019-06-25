
`include "hglobal.v"

`default_nettype	none

module cellnet_source 
#(parameter MIN_ADDR=1, MAX_ADDR=1, ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	output wire [ASZ-1:0] o_addr,
	output wire [DSZ-1:0] o_dat,
	output wire o_req,
	input wire i_ack
);
 
	reg [ASZ-1:0] r_addr = MIN_ADDR;
	reg [DSZ-1:0] r_dat = 0;
	reg [0:0] r_req = `OFF;
 
	always @(posedge i_clk)
	begin
		if((! r_req) && (! i_ack)) begin
			if(r_addr == MAX_ADDR) begin
				r_addr <= MIN_ADDR;
				r_dat <= r_dat + 1;
			end
			else begin
				r_addr <= r_addr + 1;
			end
			r_req <= `ON;
		end 
		else
		if(r_req && i_ack) begin
			r_req <= `OFF;
		end
	end
	
	assign o_addr = r_addr;
	assign o_dat = r_dat;
	assign o_req = r_req;
   
endmodule
