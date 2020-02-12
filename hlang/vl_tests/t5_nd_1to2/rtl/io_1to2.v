
`include "hglobal.v"

`default_nettype	none

module io_1to2
#(parameter MIN_ADDR=1, MAX_ADDR=1, 
	OPER_1=`GT_OP, REF_VAL_1=0, IS_RANGE=`FALSE, 
	OPER_2=`GT_OP, REF_VAL_2=0, ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input wire i_clk,	// Main Clock (25 MHz)
	
	// SRC
	`DECLARE_OUT_CHNL(o0)
	
	// SNK_0
	`DECLARE_IN_CHNL(i0)
	output wire [DSZ-1:0] o_0_ck_dat,
	output wire o_0_err,
	
	// SNK_1
	`DECLARE_IN_CHNL(i1)
	output wire [DSZ-1:0] o_1_ck_dat,
	output wire o_1_err
);
 
	// SRC regs
	reg [ASZ-1:0] r_src = 0;
	reg [ASZ-1:0] r_dst = MIN_ADDR;
	reg [DSZ-1:0] r_dat = 0;
	reg [0:0] r_req = `OFF;

	// SNK_0 regs
	reg [0:0] r_0_ack = `OFF;
	reg [DSZ-1:0] r_0_ck_dat = 0;
	reg [0:0] r_0_err = `OFF;
	
	// SNK_1 regs
	reg [0:0] r_1_ack = `OFF;
	reg [DSZ-1:0] r_1_ck_dat = 0;
	reg [0:0] r_1_err = `OFF;

	reg r_curr_src = 0;
	
	//SRC
	always @(posedge i_clk)
	begin
		if((! r_req) && (! o0_ack)) begin
			if(r_dst >= MAX_ADDR) begin
				r_dst <= MIN_ADDR;
			end else begin
				r_dst <= r_dst + 1;
			end
			r_dat <= r_dat + 1;
			r_req <= `ON;
		end else 
		if(r_req && o0_ack) begin
			r_req <= `OFF;
		end
	end
		
	//SNK_0
	always @(posedge i_clk)
	begin
		if(i0_req && (! r_0_ack)) begin
			if(! `RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, i0_dst, OPER_2, REF_VAL_2, i0_dst)) begin
				r_0_err <= `ON;
			//end else if((i0_dat > 0) && ((r_0_ck_dat + 2) != i0_dat)) begin
			//	r_0_err <= `ON;
			end else begin
				r_0_ck_dat <= i0_dat;
				r_0_ack <= `ON;
			end
		end
		else
		if((! i0_req) && r_0_ack) begin
			r_0_ack <= `OFF;
		end
	end
	
	//SNK_1
	always @(posedge i_clk)
	begin
		if(i1_req && (! r_1_ack)) begin
			if(`RANGE_CMP_OP(IS_RANGE, OPER_1, REF_VAL_1, i1_dst, OPER_2, REF_VAL_2, i1_dst)) begin
				r_1_err <= `ON;
			//end else if((i1_dat > 0) && ((r_1_ck_dat + 2) != i1_dat)) begin
			//	r_1_err <= `ON;
			end else begin
				r_1_ck_dat <= i1_dat;
				r_1_ack <= `ON;
			end
		end
		else
		if((! i1_req) && r_1_ack) begin
			r_1_ack <= `OFF;
		end
	end
	
	//SRC
	`ASSIGN_OUT_MSG(o0, r)
	assign o0_req = r_req;

	//SNK_0
	assign i0_ack = r_0_ack;
	assign o_0_ck_dat = r_0_ck_dat;
	assign o_0_err = r_0_err;
	
	//SNK_1
	assign i1_ack = r_1_ack;
	assign o_1_ck_dat = r_1_ck_dat;
	assign o_1_err = r_1_err;
	
endmodule
