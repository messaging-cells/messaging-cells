
`include "hglobal.v"

`default_nettype	none


module nd_2to1
#(parameter 
	FSZ=`NS_2to1_FSZ, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE)
(
	input wire i_clk,
	input wire reset,
	output wire ready,
	
	`NS_DECLARE_OUT_CHNL(snd0)
	`NS_DECLARE_IN_CHNL(rcv0)
	`NS_DECLARE_IN_CHNL(rcv1)
	
);
 
	reg [0:0] rg_rdy = `NS_OFF;
	
	// out0 regs
	`NS_DECLARE_REG_MSG(rgo0)
	reg [0:0] rgo0_req = `NS_OFF;
	reg [0:0] rgo0_busy = `NS_OFF;

	// inp0 regs
	reg [0:0] rgi0_ack = `NS_OFF;

	// inp1 regs
	reg [0:0] rgi1_ack = `NS_OFF;

	// fifos
	`NS_DECLARE_FIFO(bf0)
	
	reg [0:0] choose_0 = `NS_TRUE;
	
	wire in0_rq = (rcv0_req && (! rgi0_ack));
	wire in1_rq = (rcv1_req && (! rgi1_ack));

	always @(posedge i_clk)
	begin
		if(reset) begin
			rg_rdy <= `NS_OFF;
		end
		if(! reset && ! rg_rdy) begin
			rg_rdy <= `NS_ON;
			
			`NS_REG_MSG_INIT(rgo0)
			rgo0_req <= `NS_OFF;
			
			rgi0_ack <= `NS_OFF;
			rgi1_ack <= `NS_OFF;
			
			`NS_FIFO_INIT(bf0);
			
			choose_0 = `NS_TRUE;
		end
		if(! reset && rg_rdy) begin
			if(in0_rq && in1_rq) begin
				if(choose_0) begin
					choose_0 = `NS_FALSE;
					`NS_FIFO_TRY_INC_HEAD(bf0, rcv0, rgi0_ack);
					//run_head_queue_simu(buff0, *in_msg0, ack0);
				end else begin
					choose_0 = `NS_TRUE;
					`NS_FIFO_TRY_INC_HEAD(bf0, rcv1, rgi1_ack);
					//run_head_queue_simu(buff0, *in_msg1, ack1);
				end
			end
			if(in0_rq && ! in1_rq) begin
				`NS_FIFO_TRY_INC_HEAD(bf0, rcv0, rgi0_ack);
			end
			if(! in0_rq && in1_rq) begin
				`NS_FIFO_TRY_INC_HEAD(bf0, rcv1, rgi1_ack);
			end
			
			`NS_FIFO_TRY_SET_OUT(bf0, rgo0, snd0_ack, rgo0_req, rgo0_busy);
			
			if((! rcv0_req) && rgi0_ack) begin
				rgi0_ack <= `NS_OFF;
			end
			if((! rcv1_req) && rgi1_ack) begin
				rgi1_ack <= `NS_OFF;
			end
		end
	end

	assign ready = rg_rdy;
	
	//out1
	`NS_ASSIGN_OUT_MSG(snd0, rgo0)
	assign snd0_req = rgo0_req;

	//inp0
	assign rcv0_ack = rgi0_ack;
	
	//inp1
	assign rcv1_ack = rgi1_ack;
	
endmodule

