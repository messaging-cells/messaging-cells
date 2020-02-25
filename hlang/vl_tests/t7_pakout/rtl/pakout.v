
`include "hglobal.v"

`default_nettype	none


module pakout
#(parameter PSZ=`NS_PACKET_SIZE, FSZ=`NS_MESSAGE_FIFO_SIZE, ASZ=`NS_ADDRESS_SIZE, DSZ=`NS_DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	input wire reset,	// Main Clock (25 MHz)
	output wire ready,	// Main Clock (25 MHz)
	
	`NS_DECLARE_PAKOUT_CHNL(snd0)
	`NS_DECLARE_IN_CHNL(rcv0)
	
);
	reg [0:0] rg_rdy = `NS_OFF;
	
	// out0 regs
	`NS_DECLARE_REG_PAKOUT(rgo0)
	reg [0:0] rgo0_req = `NS_OFF;

	// inp0 regs
	reg [0:0] rgi0_ack = `NS_OFF;

	// fifos
	`NS_DECLARE_FIFO(bf0)
	
	wire in0_rq = (rcv0_req && (! rgi0_ack));

	always @(posedge i_clk)
	begin
		if(reset) begin
			rg_rdy <= `NS_OFF;
		end
		if(! reset && ! rg_rdy) begin
			rg_rdy <= `NS_ON;
			
			`NS_PACKETS_INIT(rgo0)
			rgo0_req <= `NS_OFF;
			
			rgi0_ack <= `NS_OFF;
			
			`NS_FIFO_INIT(bf0);
		end
		if(! reset && rg_rdy) begin
			if(in0_rq) begin
				`NS_TRY_INC_HEAD(bf0, rcv0, rgi0_ack);
			end
			
			`NS_FIFO_TRY_INC_TAIL_PAKS(bf0, rgo0);

			`NS_PACKETS_TRY_INC_TAIL(rgo0, snd0_ack, rgo0_req);
			
			if((! rcv0_req) && rgi0_ack) begin
				rgi0_ack <= `NS_OFF;
			end
			if(rgo0_req && snd0_ack) begin
				rgo0_req <= `NS_OFF;
			end
		end
	end

	assign ready = rg_rdy;
	
	//out1
	assign snd0_out_pak = rgo0_out_pak;
	assign snd0_req = rgo0_req;

	//inp0
	assign rcv0_ack = rgi0_ack;
	
endmodule

