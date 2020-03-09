
`include "hglobal.v"

`default_nettype	none

`define NS_DBG_NXT_ADDR(adr)  ((adr >= MAX_ADDR)?(MIN_ADDR):(adr + 1))


module io_2to1
#(parameter 
	MIN_ADDR=1, 
	MAX_ADDR=1, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE
)(
	input wire i_clk,	// Main Clock (25 MHz)
	
	// SRC_0
	`NS_DECLARE_OUT_CHNL(o0)
	output wire o0_err,
	
	// SRC_1
	`NS_DECLARE_OUT_CHNL(o1)
	output wire o1_err,
	
	// SNK_0
	`NS_DECLARE_IN_CHNL(i0)
	output wire [DSZ-1:0] i0_ck_dat, // i0_ck_dat
	output wire i0_err, // i0_err
	
	output wire [DSZ-1:0] fst_err_0_inp,
	output wire [DSZ-1:0] fst_err_0_dat,
);
 
	reg [3:0] cnt_0 = 0;
	reg [3:0] cnt_1 = 0;

	// SRC regs
	reg [ASZ-1:0] ro0_src = 0;
	reg [ASZ-1:0] ro0_dst = MIN_ADDR;
	reg [DSZ-1:0] ro0_dat = 0;
	reg [RSZ-1:0] ro0_red = 0;
	reg [0:0] ro0_req = `NS_OFF;
	reg [0:0] ro0_err = `NS_OFF;
	
	// SRC regs
	reg [ASZ-1:0] ro1_src = 1;
	reg [ASZ-1:0] ro1_dst = MIN_ADDR;
	reg [DSZ-1:0] ro1_dat = 0;
	reg [RSZ-1:0] ro1_red = 0;
	reg [0:0] ro1_req = `NS_OFF;
	reg [0:0] ro1_err = `NS_OFF;
	
	// SNK_0 regs
	reg [0:0] ri0_ack = `NS_OFF; // ri0_ack
	reg [DSZ-1:0] ri0_ck_dat = 0;
	
	// CHECK regs
	reg [DSZ-1:0] r_0_ck_dat = 15;
	reg [DSZ-1:0] r_1_ck_dat = 15;
	reg [0:0] r_0_err = `NS_OFF;
	reg [0:0] r_1_err = `NS_OFF;
	reg [0:0] r_2_err = `NS_OFF;
	
	reg [0:0] r_fst_err_0_flg = `NS_OFF;
	reg [DSZ-1:0] r_fst_err_0_inp = 0;
	reg [DSZ-1:0] r_fst_err_0_dat = 0;
	
	//SRC_0
	always @(posedge i_clk)
	begin
		if((! ro0_req) && (! o0_ack)) begin
			if(ro0_dat > 15) begin
				ro0_err <= `NS_ON;
			end
			if(ro0_dat < 0) begin
				ro0_err <= `NS_ON;
			end
			
			ro0_dat[3:0] <= cnt_0;
			cnt_0 <= cnt_0 + 1;
			
			ro0_req <= `NS_ON;
		end else 
		if(ro0_req && o0_ack) begin
			ro0_dst <= `NS_DBG_NXT_ADDR(ro0_dst);
			ro0_req <= `NS_OFF;
		end
	end
		
	//SRC_1
	always @(posedge i_clk)
	begin
		if((! ro1_req) && (! o1_ack)) begin
			if(ro1_dat > 15) begin
				ro1_err <= `NS_ON;
			end
			if(ro1_dat < 0) begin
				ro1_err <= `NS_ON;
			end
			
			ro1_dat[3:0] <= cnt_1;
			cnt_1 <= cnt_1 + 1;
			
			ro1_req <= `NS_ON;
		end else 
		if(ro1_req && o1_ack) begin
			ro1_dst <= `NS_DBG_NXT_ADDR(ro1_dst);
			ro1_req <= `NS_OFF;
		end
	end
		
	//SNK_0
	always @(posedge i_clk)
	begin
		if(i0_req && (! ri0_ack)) begin
			if(i0_dat > 15) begin
				r_2_err <= `NS_ON;
			end
			if(i0_dat < 0) begin
				r_2_err <= `NS_ON;
			end
			if(i0_src == 0) begin
				if((r_0_ck_dat <= 14) && ((r_0_ck_dat + 1) != i0_dat)) begin
					r_0_err <= `NS_ON;
					if(! r_fst_err_0_flg) begin
						r_fst_err_0_flg <= `NS_ON;
						r_fst_err_0_inp <= i0_dat;
						r_fst_err_0_dat <= r_0_ck_dat;
					end
				end else begin 
					r_0_ck_dat <= i0_dat;
				end
			end else begin
				if((r_1_ck_dat <= 14) && ((r_1_ck_dat + 1) != i0_dat)) begin
					r_1_err <= `NS_ON;
					if(! r_fst_err_0_flg) begin
						r_fst_err_0_flg <= `NS_ON;
						r_fst_err_0_inp <= i0_dat;
						r_fst_err_0_dat <= r_0_ck_dat;
					end
				end else begin 
					r_1_ck_dat <= i0_dat;
				end
			end
			ri0_ack <= `NS_ON;
			ri0_ck_dat <= i0_dat;
		end
		else
		if((! i0_req) && ri0_ack) begin
			ri0_ack <= `NS_OFF;
		end
	end
	
	//SRC_0
	`NS_ASSIGN_OUT_MSG(o0, ro0)
	assign o0_req = ro0_req;
	assign o0_err = r_0_err;

	//SRC_1
	`NS_ASSIGN_OUT_MSG(o1, ro1)
	assign o1_req = ro1_req;
	assign o1_err = r_1_err;

	//SNK_0
	assign i0_ack = ri0_ack;
	assign i0_ck_dat = ri0_ck_dat;
	assign i0_err = (ro0_err || ro1_err || r_2_err);
	
	assign fst_err_0_inp = r_fst_err_0_inp;
	assign fst_err_0_dat = r_fst_err_0_dat;
	
endmodule
