
`include "hglobal.v"


`default_nettype	none


module pakout
#(parameter 
	PSZ=`NS_PACKET_SIZE, 
	FSZ=`NS_PACKOUT_FSZ, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE
)(
	input wire i_clk,
	input wire reset,
	output wire ready,
	
	`NS_DECLARE_PAKOUT_CHNL(snd0),
	`NS_DECLARE_IN_CHNL(rcv0),
	
	`NS_DECLARE_DBG_CHNL(dbg)
);
	parameter RCV_REQ_CKS = `NS_REQ_CKS;
	parameter SND_ACK_CKS = `NS_ACK_CKS;
	
	`NS_DEBOUNCER_ACK(i_clk, snd0)
	`NS_DEBOUNCER_REQ(i_clk, rcv0)

	localparam TOT_PKS = ((`NS_FULL_MSG_SZ / PSZ) + 1);
	localparam FIFO_IDX_WIDTH = ((($clog2(FSZ)-1) >= 0)?($clog2(FSZ)-1):(0));
	localparam PACKETS_IDX_WIDTH = ((($clog2(TOT_PKS)-1) >= 0)?($clog2(TOT_PKS)-1):(0));
	
	`NS_DECLARE_REG_DBG(rg_dbg)
	
	reg [0:0] rg_rdy = `NS_OFF;
	
	// out0 regs
	`NS_DECLARE_REG_PAKOUT(rgo0)
	reg [0:0] rgo0_req = `NS_OFF;

	// inp0 regs
	reg [0:0] rgi0_ack = `NS_OFF;

	// fifos
	`NS_DECLARE_FIFO(bf0)
	
	reg [0:0] added_hd = `NS_OFF;


	always @(posedge i_clk)
	begin
		if(reset) begin
			rg_rdy <= `NS_OFF;
		end
		if(! reset && ! rg_rdy) begin
			rg_rdy <= `NS_ON;
			
			`NS_PACKOUT_INIT(rgo0)
			rgo0_req <= `NS_OFF;
			
			rgi0_ack <= `NS_OFF;
			
			`NS_FIFO_INIT(bf0);
		end
		if(! reset && rg_rdy) begin
			if(! added_hd) begin
				if(rcv0_req && (! rgi0_ack)) begin
					`NS_FIFO_TRY_INC_HEAD(bf0, rcv0, rgi0_ack);
				end
			end
			if((! rcv0_req) && rgi0_ack) begin
				rgi0_ack <= `NS_OFF;
			end

			`NS_FIFO_TO_PAKS_TRY_INC_TAIL(bf0, rgo0)
			else
			`NS_PACKOUT_TRY_INC(rgo0, snd0_ack, rgo0_req)
		end
	end

	
	always @(posedge dbg_clk)
	begin
		if(rgo0_pkio_busy && dbg_doit) begin
			case(dbg_case) 
			8'h20: begin
				//rg_dbg_disp0 = rgo0_pakio[PSZ-1:4];
				rg_dbg_disp1[PSZ-1:0] <= rgo0_pakio; 
			end
			default: begin
			end
			endcase
		end
		rg_dbg_leds[0:0] <= 0;
		rg_dbg_leds[1:1] <= 0;
		rg_dbg_leds[2:2] <= 0;
		rg_dbg_leds[3:3] <= rgo0_pkio_busy;
	end
	
	
	assign ready = rg_rdy;
	
	//out1
	assign snd0_pakio = rgo0_pakio;
	assign snd0_req = rgo0_req;

	//inp0
	assign rcv0_ack = rgi0_ack;

	`NS_ASSIGN_OUT_DBG(dbg, rg_dbg)
	
endmodule

