
`include "hglobal.v"

`default_nettype	none

`define NS_DBG_NXT_ADDR(adr)  ((adr >= MAX_ADDR)?(MIN_ADDR):(adr + 1))

`define NS_DBG_SRC_ADDR 3

`define NS_DBG_INIT_CK 14

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
	// SNK_0
	`NS_DECLARE_PAKIN_CHNL(i0)

	`NS_DECLARE_DBG_CHNL(dbg)
);
 
	reg [3:0] cnt_0 = 0;
	reg [3:0] cnt_1 = 0;

	// SRC regs
	reg [0:0] ro0_busy = `NS_OFF;
	reg [ASZ-1:0] ro0_src = `NS_DBG_SRC_ADDR;
	reg [ASZ-1:0] ro0_dst = MIN_ADDR;
	reg [DSZ-1:0] ro0_dat = 0;
	reg [RSZ-1:0] ro0_red = `NS_DBG_INIT_RED;
	reg [0:0] ro0_req = `NS_OFF;
	
	// SNK_0 regs
	reg [0:0] inp0_busy = `NS_OFF;
	reg [0:0] inp0_err_0 = `NS_OFF;
	reg [0:0] inp0_err_1 = `NS_OFF;
	reg [0:0] inp0_err_2 = `NS_OFF;
	reg [0:0] inp0_err_3 = `NS_OFF;
	
	//wire [0:0] inp0_has_err;	
	//assign inp0_has_err = (inp0_err_0 || inp0_err_1 || inp0_err_2);

	reg [0:0] sink_started = 0;
	
	`NS_DECLARE_REG_MSG(inp0)
	`NS_DECLARE_FIFO(bf0)
	`NS_DECLARE_REG_PACKETS(rgi0)
	reg [0:0] rgi0_ack = `NS_OFF;

	reg [DSZ-1:0] inp0_bak_dat = 15;
	
	reg [ASZ-1:0] rg_info_0 = `NS_DBG_INIT_CK;
	reg [ASZ-1:0] rg_info_1 = `NS_DBG_INIT_CK;

	`NS_DECLARE_REG_DBG(rg0)
	`NS_DECLARE_REG_DBG(rg1)
	`NS_DECLARE_REG_DBG(rg_dbg)
	
	/*
	wire [RSZ-1:0] redun_out;
	wire [RSZ-1:0] redun_inp;

	calc_redun #(.ASZ(ASZ), .DSZ(DSZ), .RSZ(RSZ)) 
		r1 (ro0_src, ro0_dst, ro0_dat, redun_out);
	
	calc_redun #(.ASZ(ASZ), .DSZ(DSZ), .RSZ(RSZ)) 
		r2 (inp0_src, inp0_dst, inp0_dat, redun_inp);
	*/
		
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
		
	//SNK_0
	always @(posedge snk_clk)
	begin
		if(! sink_started) begin
			sink_started <= 1;
			
			inp0_busy <= `NS_OFF;
			`NS_FIFO_INIT(bf0)
			`NS_PACKETS_INIT(rgi0, `NS_ON)
			rgi0_ack = `NS_OFF;
		end else begin
	
			`NS_PACKIN_TRY_INC(rgi0, i0, bf0, rgi0_ack)
			
			`NS_FIFO_TRY_INC_TAIL(bf0, inp0, inp0_busy)
			else if(inp0_busy) begin
				inp0_busy <= `NS_OFF;
				
				if(! inp0_err_0) begin
					if(inp0_src != `NS_DBG_SRC_ADDR) begin
						inp0_err_0 <= `NS_ON;
						rg_info_0 <= inp0_src;
					end
					else
					if(inp0_dat > 15) begin
						inp0_err_0 <= `NS_ON;
					end
					else
					if(inp0_dat < 0) begin
						inp0_err_0 <= `NS_ON;
					end
				end
				
				if(! inp0_err_1) begin 
					if((inp0_bak_dat <= 14) && ((inp0_bak_dat + 1) != inp0_dat)) begin
						inp0_err_1 <= `NS_ON;
						rg_info_1 <= inp0_dst[DSZ-1:0];
					end else begin 
						inp0_bak_dat <= inp0_dat;
					end
				end

				if(! inp0_err_2) begin
					if(inp0_red != `NS_DBG_INIT_RED) begin
						inp0_err_2 <= `NS_ON;
						//rg_info_0 <= inp0_red;
					end
				end
				
				inp0_err_3 <= `NS_ON;
			end
			//rg1_leds <= {inp0_err_0, inp0_err_1, inp0_err_2, inp0_err_3};
			//rg1_disp0 = rg_info_0[3:0];
			//rg1_disp1 = rg_info_1[3:0];
			
		end
		rg1_leds <= 6;
		rg1_disp0 = 7;
		rg1_disp1 = 8;
	end

	//DBG
	always @(posedge i_clk)
	begin
		if(dbg_case < `NS_DBG_MAX_SRC_CASE) begin
			rg_dbg_leds <= rg0_leds;
			rg_dbg_disp0 <= rg0_disp0;
			rg_dbg_disp1 <= rg0_disp1;
		end else begin
			rg_dbg_leds <= rg1_leds;
			rg_dbg_disp0 <= rg1_disp0;
			rg_dbg_disp1 <= rg1_disp1;
		end
	end
	
	//SRC_0
	`NS_ASSIGN_OUT_MSG(o0, ro0)
	assign o0_req = ro0_req;

	//SNK_0
	assign i0_ack = rgi0_ack;

	`NS_ASSIGN_OUT_DBG(dbg, rg_dbg)
	
endmodule


