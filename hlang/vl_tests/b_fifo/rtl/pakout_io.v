
`include "hglobal.v"

`default_nettype	none

`define NS_DBG_NXT_ADDR(adr)  ((adr >= MAX_ADDR)?(MIN_ADDR):(adr + 1))

`define NS_DBG_SRC_ADDR 3

`define NS_DBG_INIT_CK 14

`define NS_DBG_INIT_DAT 5

`define NS_DBG_INIT_RED 15

`define NS_DBG_MAX_SRC_CASE 4

module pakout_io
#(parameter 
	MIN_ADDR=1, 
	MAX_ADDR=1, 
	PSZ=`NS_PACKET_SIZE, 
	FSZ=`NS_PACKIN_FSZ, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE,
)(
	input wire i_clk,
	input wire src_clk,
	input wire snk_clk,
	
	// SRC_0
	`NS_DECLARE_OUT_CHNL(o0)
);
 
	reg [3:0] cnt_0 = `NS_DBG_INIT_DAT;

	// SRC regs
	reg [0:0] ro0_busy = `NS_OFF;
	reg [ASZ-1:0] ro0_src = `NS_DBG_SRC_ADDR;
	reg [ASZ-1:0] ro0_dst = MIN_ADDR;
	reg [DSZ-1:0] ro0_dat = `NS_DBG_INIT_DAT;
	reg [RSZ-1:0] ro0_red = `NS_DBG_INIT_RED;
	reg [0:0] ro0_req = `NS_OFF;
	
	`NS_DECLARE_REG_DBG(rg0)
		
	//SRC_0
	always @(posedge src_clk)
	begin
		if(! ro0_busy) begin
			ro0_busy <= `NS_ON;

			ro0_dst <= `NS_DBG_NXT_ADDR(ro0_dst);
			ro0_dat[3:0] <= cnt_0;
			cnt_0 <= cnt_0 + 1;
			
		end
		else
		if((! ro0_req) && (! o0_ack) && ro0_busy) begin
			//ro0_red <= redun_out;
			ro0_red <= `NS_DBG_INIT_RED;
			
			ro0_req <= `NS_ON;
		end 
		else 
		if(ro0_req && o0_ack) begin
			if(ro0_busy) begin
				ro0_busy <= `NS_OFF;
			end
			ro0_req <= `NS_OFF;
		end
		rg0_leds <= 3;
		rg0_disp0 = 4;
		rg0_disp1 = 5;
	end
	
	//SRC_0
	`NS_ASSIGN_OUT_MSG(o0, ro0)
	assign o0_req = ro0_req;

endmodule


