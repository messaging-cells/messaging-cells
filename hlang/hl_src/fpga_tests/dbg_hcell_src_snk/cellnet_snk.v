
`include "global.v"

// `ifdef

module cellnet_sink
#(parameter LOCAL_ADDR=1, ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	input wire [ASZ-1:0] i_addr,
	input wire [DSZ-1:0] i_dat,
	input wire i_req,
	output wire o_ack,
	output wire [DSZ-1:0] o_dat
);
	
	reg [DSZ-1:0] r_dat = 0;
	reg [0:0] r_ack = `OFF;
 
	always @(posedge i_clk)
	begin
		if(i_addr == LOCAL_ADDR) begin
			if(i_req && (! r_ack)) begin
				r_dat <= i_dat;
				r_ack <= `ON;
			end
			else
			if((! i_req) && r_ack) begin
				r_ack <= `OFF;
			end
		end
	end
	
	assign o_ack = r_ack;
	assign o_dat = r_dat;
   
endmodule
