
`include "hglobal.v"

`default_nettype	none

`define NS_DBG_NXT_ADDR(adr)  ((adr >= MAX_ADDR)?(MIN_ADDR):(adr + 1))


module io_1to2
#(parameter MIN_ADDR=1, MAX_ADDR=1, 
	OPER_1=`NS_GT_OP, REF_VAL_1=0, IS_RANGE=`NS_FALSE, 
	OPER_2=`NS_GT_OP, REF_VAL_2=0, ASZ=`NS_ADDRESS_SIZE, DSZ=`NS_DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	
	// SRC
	`NS_DECLARE_OUT_CHNL(o0)
	output wire o0_err,
	
	// SNK_0
	`NS_DECLARE_IN_CHNL(i0)
	output wire [DSZ-1:0] o_0_ck_dat,
	output wire o_0_err,
	
	// SNK_1
	`NS_DECLARE_IN_CHNL(i1)
	output wire [DSZ-1:0] o_1_ck_dat,
	output wire o_1_err,
	
	output wire [DSZ-1:0] fst_err_0_inp,
	output wire [DSZ-1:0] fst_err_0_dat,
	output wire [DSZ-1:0] fst_err_1_inp,
	output wire [DSZ-1:0] fst_err_1_dat,
	
);
 
	reg [3:0] cnt_0 = 0;
	reg [3:0] cnt_1 = 0;

	reg [DSZ-1:0] r_dat1 = 0;
	
	// SRC regs
	reg [ASZ-1:0] r_src = 0;
	reg [DSZ-1:0] r_dat = 10;
	reg [ASZ-1:0] r_dst = MIN_ADDR;
	reg [0:0] r_req = `NS_OFF;

	reg [0:0] r_err = `NS_OFF;
	
	// SNK_0 regs
	reg [0:0] r_0_ack = `NS_OFF;
	reg [DSZ-1:0] r_0_ck_dat = 15;
	reg [0:0] r_0_err = `NS_OFF;
	
	// SNK_1 regs
	reg [0:0] r_1_ack = `NS_OFF;
	reg [DSZ-1:0] r_1_ck_dat = 15;
	reg [0:0] r_1_err = `NS_OFF;

	reg r_curr_src = 0;

	reg [0:0] r_fst_err_0_flg = `NS_OFF;
	reg [DSZ-1:0] r_fst_err_0_inp = 3;
	reg [DSZ-1:0] r_fst_err_0_dat = 4;
	
	reg [0:0] r_fst_err_1_flg = `NS_OFF;
	reg [DSZ-1:0] r_fst_err_1_inp = 5;
	reg [DSZ-1:0] r_fst_err_1_dat = 6;
	
	//SRC
	always @(posedge i_clk)
	begin
		if((! r_req) && (! o0_ack)) begin
			if(r_dat > 15) begin
				r_err <= `NS_ON;
			end
			if(r_dat < 0) begin
				r_err <= `NS_ON;
			end
			if(! `NS_RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, r_dst, OPER_2, REF_VAL_2, r_dst)) begin
				r_dat[3:0] <= cnt_0;
				cnt_0 <= cnt_0 + 1;
			end else begin
				r_dat[3:0] <= cnt_1;
				cnt_1 <= cnt_1 + 1;
			end
			r_req <= `NS_ON;
		end else 
		if(r_req && o0_ack) begin
			r_dst <= `NS_DBG_NXT_ADDR(r_dst);
			r_req <= `NS_OFF;
		end
	end
		
	//SNK_0
	always @(posedge i_clk)
	begin
		if(i0_req && (! r_0_ack)) begin
			if(! `NS_RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, i0_dst, OPER_2, REF_VAL_2, i0_dst)) begin
				r_0_err <= `NS_ON;
			end 
			if(i0_dat > 15) begin
				r_0_err <= `NS_ON;
			end
			if(i0_dat < 0) begin
				r_0_err <= `NS_ON;
			end
			if((r_0_ck_dat <= 14) && ((r_0_ck_dat + 1) != i0_dat)) begin
				r_0_err <= `NS_ON;
				if(! r_fst_err_0_flg) begin
					r_fst_err_0_flg <= `NS_ON;
					r_fst_err_0_inp <= i0_dat;
					r_fst_err_0_dat <= r_0_ck_dat;
				end
			end 
			r_0_ck_dat <= i0_dat;
			r_0_ack <= `NS_ON;
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
			if(`NS_RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, i1_dst, OPER_2, REF_VAL_2, i1_dst)) begin
				r_1_err <= `NS_ON;
			end 
			if(i1_dat > 15) begin
				r_1_err <= `NS_ON;
			end
			if(i1_dat < 0) begin
				r_1_err <= `NS_ON;
			end
			if((r_1_ck_dat <= 14) && ((r_1_ck_dat + 1) != i1_dat)) begin
				r_1_err <= `NS_ON;
				if(! r_fst_err_1_flg) begin
					r_fst_err_1_flg <= `NS_ON;
					r_fst_err_1_inp <= i1_dat;
					r_fst_err_1_dat <= r_1_ck_dat;
				end
			end 
			r_1_ck_dat <= i1_dat;
			r_1_ack <= `NS_ON;
		end
		else
		if((! i1_req) && r_1_ack) begin
			r_1_ack <= `NS_OFF;
		end
	end
	
	//SRC
	`NS_ASSIGN_OUT_MSG(o0, r)
	assign o0_req = r_req;
	assign o0_err = r_err;

	//SNK_0
	assign i0_ack = r_0_ack;
	assign o_0_ck_dat = r_0_ck_dat;
	assign o_0_err = r_0_err;
	
	//SNK_1
	assign i1_ack = r_1_ack;
	assign o_1_ck_dat = r_1_ck_dat;
	assign o_1_err = r_1_err;

	assign fst_err_0_inp = r_fst_err_0_inp;
	assign fst_err_0_dat = r_fst_err_0_dat;
	assign fst_err_1_inp = r_fst_err_1_inp;
	assign fst_err_1_dat = r_fst_err_1_dat;
	
endmodule
