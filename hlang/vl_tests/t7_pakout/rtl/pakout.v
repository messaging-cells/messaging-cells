
`include "hglobal.v"

`default_nettype	none


module pakout
#(parameter 
	PSZ=`NS_PACKET_SIZE, 
	FSZ=`NS_PACKOUT_FSZ, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE,
)(
	input wire i_clk,
	input wire reset,
	output wire ready,
	
	`NS_DECLARE_PAKOUT_CHNL(snd0)
	`NS_DECLARE_IN_CHNL(rcv0)
	
	`NS_DECLARE_DBG_CHNL(dbg)
);
	`NS_DECLARE_REG_DBG(rg_dbg)
	`NS_ASSIGN_OUT_DBG(dbg, rg_dbg)
	
	reg [0:0] rg_rdy = `NS_OFF;
	
	// out0 regs
	`NS_DECLARE_REG_PAKOUT(rgo0)
	reg [0:0] rgo0_req = `NS_OFF;

	// inp0 regs
	reg [0:0] rgi0_ack = `NS_OFF;

	// fifos
	`NS_DECLARE_FIFO(bf0)
	
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
			if(rcv0_req && (! rgi0_ack)) begin
				`NS_FIFO_TRY_INC_HEAD(bf0, rcv0, rgi0_ack);
			end
			if((! rcv0_req) && rgi0_ack) begin
				rgi0_ack <= `NS_OFF;
			end
			
			`NS_FIFO_TRY_INC_TAIL_PAKS(bf0, rgo0)
			else
			`NS_PACKOUT_TRY_INC(rgo0, snd0_ack, rgo0_req)
		end
	end
	
	
	`NS_DECLARE_REG_MSG(dbg_fif)

	always @(posedge dbg_clk)
	begin
		/*
		if(! reset && rg_rdy) begin
		end
		*/
		case(dbg_case)
			8'h31 :
			begin
				`NS_FIFO_GET_IDX(dbg_fif, bf0, 0)
			end
			8'h32 :
			begin
				rg_dbg_disp0 <= dbg_fif_src[ASZ-1:4];
				rg_dbg_disp1 <= dbg_fif_src[3:0];
			end
			8'h33 :
			begin
				rg_dbg_disp0 <= dbg_fif_dst[ASZ-1:4];
				rg_dbg_disp1 <= dbg_fif_dst[3:0];
			end
			8'h34 :
			begin
				//rg_dbg_disp0 <= dbg_fif_dat[DSZ-1:4];
				rg_dbg_disp1 <= dbg_fif_dat[3:0];
			end
			8'h35 :
			begin
				//rg_dbg_disp0 <= dbg_fif_dat[DSZ-1:4];
				rg_dbg_disp1 <= dbg_fif_red;
			end
			
			8'h42 :
			begin
				rg_dbg_disp0 <= rcv0_src[ASZ-1:4];
				rg_dbg_disp1 <= rcv0_src[3:0];
			end
			8'h43 :
			begin
				rg_dbg_disp0 <= rcv0_dst[ASZ-1:4];
				rg_dbg_disp1 <= rcv0_dst[3:0];
			end
			8'h44 :
			begin
				//rg_dbg_disp0 <= rcv0_dat[DSZ-1:4];
				rg_dbg_disp1 <= rcv0_dat[3:0];
			end
			8'h45 :
			begin
				//rg_dbg_disp0 <= rcv0_dat[DSZ-1:4];
				rg_dbg_disp1 <= rcv0_red;
			end
		endcase
		rg_dbg_leds[0:0] <= rg_rdy;
		rg_dbg_leds[1:1] <= ! rg_rdy;
		rg_dbg_leds[2:2] <= rcv0_req;
		rg_dbg_leds[3:3] <= rgi0_ack;
	end
	
	assign ready = rg_rdy;
	
	//out1
	assign snd0_pakio = rgo0_pakio;
	assign snd0_req = rgo0_req;

	//inp0
	assign rcv0_ack = rgi0_ack;
	
endmodule

