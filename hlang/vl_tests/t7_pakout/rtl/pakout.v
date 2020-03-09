
`include "hglobal.v"

`default_nettype	none

`define NS_DBG_MSG_CASES(num, mg) \
	8'h``num``1 : \
	begin \
		rg_dbg_disp0 <= mg``_src[ASZ-1:4]; \
		rg_dbg_disp1 <= mg``_src[3:0]; \
	end \
	8'h``num``2 : \
	begin \
		rg_dbg_disp0 <= mg``_dst[ASZ-1:4]; \
		rg_dbg_disp1 <= mg``_dst[3:0]; \
	end \
	8'h``num``3 : \
	begin \
		rg_dbg_disp0 <= 0; \
		rg_dbg_disp1 <= mg``_dat[3:0]; \
	end \
	8'h``num``4 : \
	begin \
		rg_dbg_disp0 <= mg``_redun; \
		rg_dbg_disp1 <= mg``_red; \
	end \



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
			
			`NS_FIFO_TO_PAKS_TRY_INC_TAIL(bf0, rgo0)
			else
			`NS_PACKOUT_TRY_INC(rgo0, snd0_ack, rgo0_req)
		end
	end
	
	
	`NS_DECLARE_REG_MSG(dbg_fif)
	wire [RSZ-1:0] dbg_fif_calc_redun;
	reg [RSZ-1:0] dbg_fif_redun = 0;

	calc_redun #(.ASZ(ASZ), .DSZ(DSZ), .RSZ(RSZ)) 
		obj1 (dbg_fif_src, dbg_fif_dst, dbg_fif_dat, dbg_fif_calc_redun);

	wire [RSZ-1:0] rcv0_redun;
	calc_redun #(.ASZ(ASZ), .DSZ(DSZ), .RSZ(RSZ)) 
		obj2 (rcv0_src, rcv0_dst, rcv0_dat, rcv0_redun);
		
	always @(posedge dbg_clk)
	begin
		/*
		if(! reset && rg_rdy) begin
		end
		*/
		case(dbg_case)
			8'h20 :
			begin
				`NS_FIFO_GET_IDX(dbg_fif, bf0, 0)
				dbg_fif_redun <= dbg_fif_calc_redun;
				rg_dbg_disp0 <= 0; \
				rg_dbg_disp1 <= 0; \
			end
			8'h21 :
			begin
				rg_dbg_disp0 <= bf0_hd_idx;
				rg_dbg_disp1 <= bf0_tl_idx;
			end
			8'h22 :
			begin
				rg_dbg_disp0 <= 0;
				rg_dbg_disp1 <= FSZ;
			end
			8'h23 :
			begin
				rg_dbg_disp0 <= bf0_busy[bf0_hd_idx];
				rg_dbg_disp1 <= bf0_busy[bf0_tl_idx];
			end
			`NS_DBG_MSG_CASES(3, dbg_fif) 
			`NS_DBG_MSG_CASES(4, rcv0) 
			/*8'h51 :
			begin
				rg_dbg_disp0 <= 0;
				rg_dbg_disp1[PSZ-1:0] <= snd0_pakio;
			end*/
			
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

	`NS_ASSIGN_OUT_DBG(dbg, rg_dbg)
	
endmodule

