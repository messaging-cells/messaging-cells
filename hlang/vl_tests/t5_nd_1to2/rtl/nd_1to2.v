
`include "hglobal.v"

`default_nettype	none

module nd_1to2
#(parameter 
	OPER_1=`NS_GT_OP, REF_VAL_1=0, IS_RANGE=`NS_FALSE, 
	OPER_2=`NS_GT_OP, REF_VAL_2=0, FSZ=`NS_MESSAGE_FIFO_SIZE, ASZ=`NS_ADDRESS_SIZE, DSZ=`NS_DATA_SIZE, RSZ=`NS_REDUN_SIZE)
(
	input wire i_clk,
	input wire reset,
	output wire ready,
	
	`NS_DECLARE_OUT_CHNL(snd0)
	`NS_DECLARE_OUT_CHNL(snd1)
	`NS_DECLARE_IN_CHNL(rcv0)
	
);
 
	reg [0:0] rg_rdy = `NS_OFF;
	
	// out1 regs
	`NS_DECLARE_REG_MSG(rgo0)
	reg [0:0] rgo0_req = `NS_OFF;
	reg [0:0] rgo0_busy = `NS_OFF;

	// out2 regs
	`NS_DECLARE_REG_MSG(rgo1)
	reg [0:0] rgo1_req = `NS_OFF;
	reg [0:0] rgo1_busy = `NS_OFF;

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
					`NS_FIFO_TRY_INC_HEAD(bf0, rcv0, rgi0_ack);
				end else begin
					`NS_FIFO_TRY_INC_HEAD(bf1, rcv0, rgi0_ack);
				end
			end
			
			/*`NS_TRY_INC_TAIL(bf0, rgo0, snd0_ack, rgo0_req);
			`NS_TRY_INC_TAIL(bf1, rgo1, snd1_ack, rgo1_req);
			if(rgo0_req && snd0_ack) begin
				rgo0_req <= `NS_OFF;
			end
			if(rgo1_req && snd1_ack) begin
				rgo1_req <= `NS_OFF;
			end*/
			
			
			`NS_FIFO_TRY_SET_OUT(bf0, rgo0, snd0_ack, rgo0_req, rgo0_busy);
			`NS_FIFO_TRY_SET_OUT(bf1, rgo1, snd1_ack, rgo1_req, rgo1_busy);
			
			
			if((! rcv0_req) && rgi0_ack) begin
				rgi0_ack <= `NS_OFF;
			end
		end
	end

	assign ready = rg_rdy;
	
	//out1
	`NS_ASSIGN_OUT_MSG(snd0, rgo0)
	assign snd0_req = rgo0_req;

	//out2
	`NS_ASSIGN_OUT_MSG(snd1, rgo1)
	assign snd1_req = rgo1_req;

	//inp0
	assign rcv0_ack = rgi0_ack;
	
endmodule

