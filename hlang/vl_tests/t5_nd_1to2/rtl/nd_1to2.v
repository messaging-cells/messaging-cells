
`include "hglobal.v"

`default_nettype	none

module nd_1to2
#(parameter 
	OPER_1=`GT_OP, REF_VAL_1=0, IS_RANGE=`FALSE, 
	OPER_2=`GT_OP, REF_VAL_2=0, ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	
	`DECLARE_OUT_CHNL(snd0)
	`DECLARE_OUT_CHNL(snd1)
	`DECLARE_IN_CHNL(rcv0)
	
);
 
	// out1 regs
	`DECLARE_REG_MSG(rgo0)
	reg [0:0] rgo0_req = `OFF;

	// out2 regs
	`DECLARE_REG_MSG(rgo1)
	reg [0:0] rgo1_req = `OFF;

	// inp regs
	reg [0:0] rgi0_ack = `OFF;

	// fifos
	`DECLARE_FIFO(bf0)
	`DECLARE_FIFO(bf1)
	
	always @(posedge i_clk)
	begin
		if(rcv0_req && (! rgi0_ack)) begin
			if(`RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, rcv0_dst, OPER_2, REF_VAL_2, rcv0_dst)) begin
				`TRY_INC_HEAD(bf0, rcv0, rgi0_ack);
				//run_head_queue_simu(buff0, *in_msg0, ack0);
			end else begin
				`TRY_INC_HEAD(bf1, rcv0, rgi0_ack);
				//run_head_queue_simu(buff1, *in_msg0, ack0);
			end
		end
		
		`TRY_INC_TAIL(bf0, rgo0, snd0_ack, rgo0_req);
		`TRY_INC_TAIL(bf1, rgo1, snd1_ack, rgo1_req);
		//run_tail_queue_simu(buff0, msg0, *out0, req0);
		//run_tail_queue_simu(buff1, msg1, *out1, req1);
		
		if((! rcv0_req) && rgi0_ack) begin
			rgi0_ack <= `OFF;
		end
		if(rgo0_req && snd0_ack) begin
			rgo0_req <= `OFF;
		end
		if(rgo1_req && snd1_ack) begin
			rgo1_req <= `OFF;
		end
	end

	//out1
	`ASSIGN_OUT_MSG(snd0, rgo0)
	//assign snd0_dst = rgo0_dst;
	//assign snd0_dat = rgo0_dat;
	assign snd0_req = rgo0_req;

	//out2
	`ASSIGN_OUT_MSG(snd1, rgo1)
	//assign snd1_dst = rgo1_dst;
	//assign snd1_dat = rgo1_dat;
	assign snd1_req = rgo1_req;

	//inp
	assign rcv0_ack = rgi0_ack;
	
endmodule

