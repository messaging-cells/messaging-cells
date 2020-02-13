
`include "hglobal.v"

`default_nettype	none

module nd_1to2
#(parameter 
	OPER_1=`NS_GT_OP, REF_VAL_1=0, IS_RANGE=`NS_FALSE, 
	OPER_2=`NS_GT_OP, REF_VAL_2=0, ASZ=`NS_ADDRESS_SIZE, DSZ=`NS_DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	input wire reset,	// Main Clock (25 MHz)
	output wire ready,	// Main Clock (25 MHz)
	
	`NS_DECLARE_OUT_CHNL(snd0)
	`NS_DECLARE_OUT_CHNL(snd1)
	`NS_DECLARE_IN_CHNL(rcv0)
	
);
 
	reg [0:0] rg_rdy = `NS_OFF;
	
	// out1 regs
	`NS_DECLARE_REG_MSG(rgo0)
	reg [0:0] rgo0_req = `NS_OFF;

	// out2 regs
	`NS_DECLARE_REG_MSG(rgo1)
	reg [0:0] rgo1_req = `NS_OFF;

	// inp regs
	reg [0:0] rgi0_ack = `NS_OFF;

	// fifos
	`NS_DECLARE_FIFO(bf0)
	`NS_DECLARE_FIFO(bf1)
	
	always @(posedge i_clk)
	begin
		if(reset) begin
			rg_rdy <= `NS_OFF;
		end
		if(! reset && ! rg_rdy) begin
			rg_rdy <= `NS_ON;
			
			`NS_REG_MSG_INIT(rgo0)
			rgo0_req <= `NS_OFF;
			`NS_REG_MSG_INIT(rgo1)
			rgo1_req <= `NS_OFF;
			rgi0_ack <= `NS_OFF;
			
			`NS_FIFO_INIT(bf0)
			`NS_FIFO_INIT(bf1)
		end
		if(! reset && rg_rdy) begin
			if(rcv0_req && (! rgi0_ack)) begin
				if(`NS_RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, rcv0_dst, OPER_2, REF_VAL_2, rcv0_dst)) begin
					`NS_TRY_INC_HEAD(bf0, rcv0, rgi0_ack);
					//run_head_queue_simu(buff0, *in_msg0, ack0);
				end else begin
					`NS_TRY_INC_HEAD(bf1, rcv0, rgi0_ack);
					//run_head_queue_simu(buff1, *in_msg0, ack0);
				end
			end
			
			`NS_TRY_INC_TAIL(bf0, rgo0, snd0_ack, rgo0_req);
			`NS_TRY_INC_TAIL(bf1, rgo1, snd1_ack, rgo1_req);
			//run_tail_queue_simu(buff0, msg0, *out0, req0);
			//run_tail_queue_simu(buff1, msg1, *out1, req1);
			
			if((! rcv0_req) && rgi0_ack) begin
				rgi0_ack <= `NS_OFF;
			end
			if(rgo0_req && snd0_ack) begin
				rgo0_req <= `NS_OFF;
			end
			if(rgo1_req && snd1_ack) begin
				rgo1_req <= `NS_OFF;
			end
		end
	end

	assign ready = rg_rdy;
	
	//out1
	`NS_ASSIGN_OUT_MSG(snd0, rgo0)
	//assign snd0_dst = rgo0_dst;
	//assign snd0_dat = rgo0_dat;
	assign snd0_req = rgo0_req;

	//out2
	`NS_ASSIGN_OUT_MSG(snd1, rgo1)
	//assign snd1_dst = rgo1_dst;
	//assign snd1_dat = rgo1_dat;
	assign snd1_req = rgo1_req;

	//inp
	assign rcv0_ack = rgi0_ack;
	
endmodule

