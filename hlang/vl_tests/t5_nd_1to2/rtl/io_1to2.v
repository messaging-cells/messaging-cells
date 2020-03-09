
`include "hglobal.v"

`default_nettype	none

`define NS_DBG_NXT_ADDR(adr)  ((adr >= MAX_ADDR)?(MIN_ADDR):(adr + 1))

`define NS_DBG_SRC 9

`define NS_DBG_RED 10


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


module io_1to2
#(parameter 
	MIN_ADDR=1, 
	MAX_ADDR=1, 
	OPER_1=`NS_GT_OP, 
	REF_VAL_1=0, 
	IS_RANGE=`NS_FALSE, 
	OPER_2=`NS_GT_OP, 
	REF_VAL_2=0, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE
)(
	input wire i_clk,	// Main Clock (25 MHz)
	
	// SRC
	`NS_DECLARE_OUT_CHNL(o0)
	
	// SNK_0
	`NS_DECLARE_IN_CHNL(i0)
	
	// SNK_1
	`NS_DECLARE_IN_CHNL(i1)
	
	
	`NS_DECLARE_DBG_CHNL(dbg)
);
	`NS_DECLARE_REG_DBG(rg_dbg)
	`NS_DECLARE_REG_MSG(err_mg)
	reg [RSZ-1:0] err_mg_redun = 0;
 	reg [3:0] err_mg_case = 0;

	`NS_DECLARE_REG_MSG(bak_src_mg)
	reg [RSZ-1:0] bak_src_mg_redun = 0;
 	
	reg [3:0] cnt_0 = 0;
	reg [3:0] cnt_1 = 0;

	reg [DSZ-1:0] r_dat1 = 0;
	
	// SRC regs
	reg [0:0] ro0_busy = `NS_OFF;
	
	reg [ASZ-1:0] ro0_src = `NS_DBG_SRC;
	reg [DSZ-1:0] ro0_dat = 0;
	reg [ASZ-1:0] ro0_dst = MIN_ADDR;
	reg [RSZ-1:0] ro0_red = 0;
	
	reg [0:0] ro0_req = `NS_OFF;

	reg [0:0] r_err = `NS_OFF;
	
	// SNK_0 regs
	reg [0:0] r_0_ack = `NS_OFF;
	reg [DSZ-1:0] r_0_ck_dat = 15;
	reg [0:0] r_0_err = `NS_OFF;
	
	// SNK_1 regs
	reg [0:0] r_1_ack = `NS_OFF;
	reg [DSZ-1:0] r_1_ck_dat = 15;
	reg [0:0] r_1_err = `NS_OFF;

	//reg r_curr_src = 0;

	wire [RSZ-1:0] ro0_redun;
	
	reg [0:0] i0_has_redun = `NS_OFF;
	wire [RSZ-1:0] i0_redun;
	reg [RSZ-1:0] ri0_redun = 0;
	reg [0:0] i1_has_redun = `NS_OFF;
	wire [RSZ-1:0] i1_redun;
	reg [RSZ-1:0] ri1_redun = 0;

	calc_redun #(.ASZ(ASZ), .DSZ(DSZ), .RSZ(RSZ)) 
		r1 (ro0_src, ro0_dst, ro0_dat, ro0_redun);
	
	calc_redun #(.ASZ(ASZ), .DSZ(DSZ), .RSZ(RSZ)) 
		r2 (i0_src, i0_dst, i0_dat, i0_redun);
	
	calc_redun #(.ASZ(ASZ), .DSZ(DSZ), .RSZ(RSZ)) 
		r3 (i1_src, i1_dst, i1_dat, i1_redun);
	
	//SRC
	always @(posedge i_clk)
	begin
		if(! ro0_busy) begin
			ro0_busy <= `NS_ON;

			if(ro0_dat > 15) begin
				r_err <= `NS_ON;
			end
			if(ro0_dat < 0) begin
				r_err <= `NS_ON;
			end
			if(! `NS_RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, ro0_dst, OPER_2, REF_VAL_2, ro0_dst)) begin
				ro0_dat[3:0] <= cnt_0;
				cnt_0 <= cnt_0 + 1;
			end else begin
				ro0_dat[3:0] <= cnt_1;
				cnt_1 <= cnt_1 + 1;
			end
		end
		else
		if((! ro0_req) && (! o0_ack) && ro0_busy) begin
			ro0_red <= ro0_redun;
			
			if(`NS_REG_MSG_EQ(ro0, `NS_DBG_SRC, 1, 3)) begin
				`NS_MOV_REG_MSG(bak_src_mg, ro0)
				bak_src_mg_red <= ro0_redun;
				bak_src_mg_redun <= ro0_redun;
			end
			
			ro0_req <= `NS_ON;
		end 
		else 
		if(ro0_req && o0_ack) begin
			ro0_dst <= `NS_DBG_NXT_ADDR(ro0_dst);
			
			if(ro0_busy) begin
				ro0_busy <= `NS_OFF;
			end
			ro0_req <= `NS_OFF;
		end
	end
		
	//SNK_0
	always @(posedge i_clk)
	begin
		if(i0_req && (! r_0_ack)) begin
			if(! i0_has_redun) begin
				i0_has_redun <= `NS_ON;
				ri0_redun <= i0_redun;
			end
			else
			begin
				i0_has_redun <= `NS_OFF;
				if(! r_0_err) begin
					if(! `NS_RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, i0_dst, OPER_2, REF_VAL_2, i0_dst)) begin
						r_0_err <= `NS_ON;
						err_mg_case <= 1;
					end 
					else
					if(i0_src != `NS_DBG_SRC) begin
						r_0_err <= `NS_ON;
						err_mg_case <= 2;
					end
					else
					if(i0_dat > 15) begin
						r_0_err <= `NS_ON;
						err_mg_case <= 3;
					end
					else
					if(i0_dat < 0) begin
						r_0_err <= `NS_ON;
						err_mg_case <= 4;
					end
					else
					if(i0_red != ri0_redun) begin
						r_0_err <= `NS_ON;
						err_mg_case <= 5;
						`NS_MOV_REG_MSG(err_mg, i0)
						err_mg_redun <= ri0_redun;
					end
					else
					if((r_0_ck_dat <= 14) && ((r_0_ck_dat + 1) != i0_dat)) begin
						r_0_err <= `NS_ON;
						err_mg_case <= 6;
					end 
					else 
					begin 
						r_0_ck_dat <= i0_dat;
						r_0_ack <= `NS_ON;
					end
				end
				else
				begin
					r_0_ack <= `NS_ON;
				end
			end
		end
		else
		if((! i0_req) && r_0_ack) begin
			r_0_ack <= `NS_OFF;
		end
	end
	
	//SNK_1
	always @(posedge i_clk)
	begin
		if(i1_req && (! r_1_ack)) begin
			if(! i1_has_redun) begin
				i1_has_redun <= `NS_ON;
				ri1_redun <= i1_redun;
			end
			else
			begin
				i1_has_redun <= `NS_OFF;
				if(! r_1_err) begin
					if(`NS_RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, i1_dst, OPER_2, REF_VAL_2, i1_dst)) begin
						r_1_err <= `NS_ON;
					end
					else
					if(i1_src != `NS_DBG_SRC) begin
						r_1_err <= `NS_ON;
					end
					else
					if(i1_dat > 15) begin
						r_1_err <= `NS_ON;
					end
					else
					if(i1_dat < 0) begin
						r_1_err <= `NS_ON;
					end
					else
					if(i1_red != ri1_redun) begin
						r_1_err <= `NS_ON;
					end
					//else
					if((r_1_ck_dat <= 14) && ((r_1_ck_dat + 1) != i1_dat)) begin
						r_1_err <= `NS_ON;
					end 
					else 
					begin
						r_1_ck_dat <= i1_dat;
						r_1_ack <= `NS_ON;
					end
				end
				else
				begin
					r_1_ack <= `NS_ON;
				end
			end
		end
		else
		if((! i1_req) && r_1_ack) begin
			r_1_ack <= `NS_OFF;
		end
	end
	
	//DBG
	always @(posedge i_clk)
	begin
		case(dbg_case)
			8'h30 :
			begin
				rg_dbg_disp0 <= 0;
				rg_dbg_disp1 <= err_mg_case;
			end
			`NS_DBG_MSG_CASES(3, err_mg)
			`NS_DBG_MSG_CASES(4, bak_src_mg)
			/*
			8'h31 :
			begin
				rg_dbg_disp0 <= err_mg_src[ASZ-1:4];
				rg_dbg_disp1 <= err_mg_src[3:0];
			end
			8'h32 :
			begin
				rg_dbg_disp0 <= err_mg_dst[ASZ-1:4];
				rg_dbg_disp1 <= err_mg_dst[3:0];
			end
			8'h33 :
			begin
				//rg_dbg_disp0 <= err_mg_dat[DSZ-1:4];
				rg_dbg_disp0 <= 0;
				rg_dbg_disp1 <= err_mg_dat[3:0];
			end
			8'h34 :
			begin
				rg_dbg_disp0 <= err_mg_redun;
				rg_dbg_disp1 <= err_mg_red;
			end
			*/
		endcase
	end
	
	//SRC
	`NS_ASSIGN_OUT_MSG(o0, ro0)
	assign o0_req = ro0_req;

	//SNK_0
	assign i0_ack = r_0_ack;
	
	//SNK_1
	assign i1_ack = r_1_ack;
	
	//`NS_ASSIGN_OUT_DBG(dbg, rg_dbg)
	assign dbg_leds[0:0] = r_0_err;
	assign dbg_leds[1:1] = r_1_err;
	assign dbg_leds[2:2] = r_err;
	assign dbg_leds[3:3] = 0;
	assign dbg_disp0 = rg_dbg_disp0;
	assign dbg_disp1 = rg_dbg_disp1;
	
endmodule
