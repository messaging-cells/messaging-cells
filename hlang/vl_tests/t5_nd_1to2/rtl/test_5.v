
`include "hglobal.v"

`default_nettype	none

`define NS_NUM_TEST 5
`define NS_TEST_MIN_ADDR 0
`define NS_TEST_MAX_ADDR 55
`define NS_TEST_REF_ADDR 23


`define NS_DECLARE_CLK(nam, idx, lim) \
	reg [1:0] clk_idx_``nam = idx; \
	reg [CLK_WDH-1:0] lim_clk_``nam = lim; \
	reg [CLK_WDH-1:0] cnt_clk_``nam = 1; \
	reg clk_``nam = 0;


`define NS_INC_CLK(nam, base_clk) \
	always @(posedge base_clk) \
	begin \
		if((cnt_clk_``nam == 0) || (cnt_clk_``nam == lim_clk_``nam)) begin \
			cnt_clk_``nam <= 1; \
			`ns_bit_toggle(clk_``nam); \
		end \
		else  begin \
			cnt_clk_``nam <= (cnt_clk_``nam << 1); \
		end \
	end



`define NS_INC_IDX_IN_ARR(idxs_arr, max_idx, ii, func) \
	if(idxs_arr[ii] == max_idx) begin \
		idxs_arr[ii] <= 0; \
		func \
	end \
	else \
	begin \
		idxs_arr[ii] <= idxs_arr[ii] + 1; \
	end


`define NS_INIT_ARR_IDXS(idxs_arr) \
		idxs_arr[0] <= 0; \
		idxs_arr[1] <= 0; \
		idxs_arr[2] <= 0; \
		idxs_arr[3] <= 0; 


`define NS_INC_ARR3(idxs_arr, max_idx) \
	if(idxs_arr[3] == max_idx) begin \
		`NS_INIT_ARR_IDXS(idxs_arr) \
	end \
	else \
	begin \
		idxs_arr[3] <= idxs_arr[3] + 1; \
	end


`define NS_INC_ARR2(idxs_arr, max_idx) \
	if(idxs_arr[2] == max_idx) begin \
		idxs_arr[2] <= 0; \
		`NS_INC_ARR3(idxs_arr, max_idx) \
	end \
	else \
	begin \
		idxs_arr[2] <= idxs_arr[2] + 1; \
	end


`define NS_INC_ARR1(idxs_arr, max_idx) \
	if(idxs_arr[1] == max_idx) begin \
		idxs_arr[1] <= 0; \
		`NS_INC_ARR2(idxs_arr, max_idx) \
	end \
	else \
	begin \
		idxs_arr[1] <= idxs_arr[1] + 1; \
	end


`define NS_INC_ARR0(idxs_arr, max_idx) \
	if(idxs_arr[0] == max_idx) begin \
		idxs_arr[0] <= 0; \
		`NS_INC_ARR1(idxs_arr, max_idx) \
	end \
	else \
	begin \
		idxs_arr[0] <= idxs_arr[0] + 1; \
	end


`define NS_INC_ARR(idxs_arr, max_idx) `NS_INC_ARR0(idxs_arr, max_idx)


`define NS_SET_LIM_CLK(nam, lims_arr, idxs_arr) lim_clk_``nam <= lims_arr[idxs_arr[clk_idx_``nam]];



module test_top 
#(parameter ASZ=`NS_ADDRESS_SIZE, DSZ=`NS_DATA_SIZE, RSZ=`NS_REDUN_SIZE)
(
	input  i_clk,      // Main Clock (25 MHz)
	input  i_Switch_1, 
	input  i_Switch_2, 
	input  i_Switch_3, 
	input  i_Switch_4, 
	
	output o_Segment1_A,
	output o_Segment1_B,
	output o_Segment1_C,
	output o_Segment1_D,
	output o_Segment1_E,
	output o_Segment1_F,
	output o_Segment1_G,
	
	output o_Segment2_A,
	output o_Segment2_B,
	output o_Segment2_C,
	output o_Segment2_D,
	output o_Segment2_E,
	output o_Segment2_F,
	output o_Segment2_G,
	output o_LED_1,
	output o_LED_2,
	output o_LED_3,
	output o_LED_4
	);

	reg [0:0] the_reset = 0;
	wire the_all_ready;
	
	wire w_Switch_1;
	reg  r_Switch_1 = `NS_OFF;
	wire w_Switch_2;
	reg  r_Switch_2 = `NS_OFF;
	wire w_Switch_3;
	reg  r_Switch_3 = `NS_OFF;
	wire w_Switch_4;
	reg  r_Switch_4 = `NS_OFF;

	localparam TOT_DEBOUNCE_CLICK = 250000;  // 10 ms at 25 MHz
	
	debouncer #(.TOT_CKS(TOT_DEBOUNCE_CLICK))
	but1_fixed (
		.i_Clk(i_clk),
		.i_Switch(i_Switch_1),
		.o_Switch(w_Switch_1)
	);
	
	debouncer #(.TOT_CKS(TOT_DEBOUNCE_CLICK))
	but2_fixed(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_2),
		.o_Switch(w_Switch_2)
	);
	
	debouncer #(.TOT_CKS(TOT_DEBOUNCE_CLICK))
	but3_fixed(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_3),
		.o_Switch(w_Switch_3)
	);
	
	debouncer #(.TOT_CKS(TOT_DEBOUNCE_CLICK))
	but4_fixed(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_4),
		.o_Switch(w_Switch_4)
	);
	
	localparam CLK_WDH = 17;
	localparam CLK_IDX_WDH = 2;

	reg [CLK_WDH-1:0] lim_clks_arr [6:0];  // 2, 3, 5, 7, 11, 13, 17
	reg [CLK_IDX_WDH:0] lims_idxs [3:0];

	reg clk_lims_inited = 0;
	
	`NS_DECLARE_CLK(kl0, 0, 2)
	`NS_DECLARE_CLK(kl1, 1, 3)
	`NS_DECLARE_CLK(kl2, 2, 5)
	`NS_DECLARE_CLK(kl3, 3, 7)

	`NS_INC_CLK(kl0, i_clk)
	`NS_INC_CLK(kl1, i_clk)
	`NS_INC_CLK(kl2, i_clk)
	`NS_INC_CLK(kl3, i_clk)
	
	always @(posedge i_clk)
	begin
		if(! clk_lims_inited) begin
			clk_lims_inited <= 1;
			lim_clks_arr[0] <= 17'b00000000000000010;
			lim_clks_arr[1] <= 17'b00000000000000100;
			lim_clks_arr[2] <= 17'b00000000000010000;
			lim_clks_arr[3] <= 17'b00000000001000000;
			lim_clks_arr[4] <= 17'b00000010000000000;
			lim_clks_arr[5] <= 17'b00001000000000000;
			lim_clks_arr[6] <= 17'b10000000000000000;
		end
	end
	
	reg [3:0] io_leds = 0;
	reg [3:0] io_disp0 = `NS_NUM_TEST;
	reg [3:0] io_disp1 = `NS_NUM_TEST;

	reg dbg_selecting_case = `NS_OFF;
	reg  [3:0] dbg_case_hi = 0;
	reg  [3:0] dbg_case_lo = 0;
	
	`NS_DECLARE_DBG_LINK(dbg0)
	`NS_DECLARE_DBG_LINK(dbg1)
	
	assign dbg0_case = {dbg_case_hi, dbg_case_lo};
	assign dbg1_case = {dbg_case_hi, dbg_case_lo};
	
	// LNK_0
	`NS_DECLARE_LINK(lnk_0)
	wire [DSZ-1:0] lnk_0_ck_dat;
	
	// LNK_1_
	`NS_DECLARE_LINK(lnk_1)
	wire [DSZ-1:0] lnk_1_ck_dat;
  
	// LNK_2
	`NS_DECLARE_LINK(lnk_2)
	//wire [DSZ-1:0] lnk_2_ck_dat;

	wire w_Segment1_A;
	wire w_Segment1_B;
	wire w_Segment1_C;
	wire w_Segment1_D;
	wire w_Segment1_E;
	wire w_Segment1_F;
	wire w_Segment1_G;
	
	wire w_Segment2_A;
	wire w_Segment2_B;
	wire w_Segment2_C;
	wire w_Segment2_D;
	wire w_Segment2_E;
	wire w_Segment2_F;
	wire w_Segment2_G;
	
	nd_1to2 #(.OPER_1(`NS_GT_OP), .REF_VAL_1(`NS_TEST_REF_ADDR))
	gt1to2 (
		.i_clk(i_clk),
		// i_clk clk_kl3
		
		.reset(the_reset),
		.ready(the_all_ready),
		
		//.i_clk(i_clk),
		// out0
		`NS_INSTA_SND_CHNL(snd0, lnk_0),
		// out1
		`NS_INSTA_SND_CHNL(snd1, lnk_1),
		// in
		`NS_INSTA_RCV_CHNL(rcv0, lnk_2)
	);

	io_1to2 #(.MIN_ADDR(`NS_TEST_MIN_ADDR), .MAX_ADDR(`NS_TEST_MAX_ADDR), .OPER_1(`NS_GT_OP), .REF_VAL_1(`NS_TEST_REF_ADDR))
	io_t3 (
		.src0_clk(clk_kl0),
		.snk0_clk(clk_kl1),
		.snk1_clk(clk_kl2),
		//i_clk, clk_0, clk_1
		// clk 0, 1, 1 fails
		// clk 0, 2, 2 fails
		
		// SRC
		`NS_INSTA_SND_CHNL(o0, lnk_2),
		// SNK0
		`NS_INSTA_RCV_CHNL(i0, lnk_0),
		// SNK1
		`NS_INSTA_RCV_CHNL(i1, lnk_1),
		
		`NS_INSTA_DBG_CHNL(dbg, dbg1, i_clk)
	);

	wire sw1_ON = ((w_Switch_1 == `NS_ON) && (r_Switch_1 == `NS_OFF));
	wire sw1_OFF = ((w_Switch_1 == `NS_OFF) && (r_Switch_1 == `NS_ON));
	always @(posedge i_clk)
	begin
		r_Switch_1 <= w_Switch_1;
		
		if(sw1_ON)
		begin
			if(clk_lims_inited) begin
				`NS_INC_ARR(lims_idxs, 6)
				`NS_SET_LIM_CLK(kl0, lim_clks_arr, lims_idxs)
				`NS_SET_LIM_CLK(kl1, lim_clks_arr, lims_idxs)
				`NS_SET_LIM_CLK(kl2, lim_clks_arr, lims_idxs)
				`NS_SET_LIM_CLK(kl3, lim_clks_arr, lims_idxs)
			end
		end
	end

	/*
	`NS_DECLARE_REG_DBG(rg_dbg)
	
	wire sw2_ON = ((w_Switch_2 == `NS_ON) && (r_Switch_2 == `NS_OFF));
	wire sw2_OFF = ((w_Switch_2 == `NS_OFF) && (r_Switch_2 == `NS_ON));
	always @(posedge i_clk)
	begin
		r_Switch_2 <= w_Switch_2;
		
		if(sw2_ON)
		begin
			rg_dbg_disp0 <= dbg1_disp0;
			rg_dbg_disp1 <= dbg1_disp1;
		end
	end

	
	bin_to_disp Id0(
	.i_Clk(i_clk),
	.i_Binary_Num(rg_dbg_disp0),
	//.i_Binary_Num(dbg1_disp0),
	.o_Segment_A(w_Segment1_A),
	.o_Segment_B(w_Segment1_B),
	.o_Segment_C(w_Segment1_C),
	.o_Segment_D(w_Segment1_D),
	.o_Segment_E(w_Segment1_E),
	.o_Segment_F(w_Segment1_F),
	.o_Segment_G(w_Segment1_G)
	);
	
	bin_to_disp Id1(
	.i_Clk(i_clk),
	.i_Binary_Num(rg_dbg_disp1),
	//.i_Binary_Num(dbg1_disp1),
	.o_Segment_A(w_Segment2_A),
	.o_Segment_B(w_Segment2_B),
	.o_Segment_C(w_Segment2_C),
	.o_Segment_D(w_Segment2_D),
	.o_Segment_E(w_Segment2_E),
	.o_Segment_F(w_Segment2_F),
	.o_Segment_G(w_Segment2_G)
	);

	assign o_Segment1_A = ~w_Segment1_A;
	assign o_Segment1_B = ~w_Segment1_B;
	assign o_Segment1_C = ~w_Segment1_C;
	assign o_Segment1_D = ~w_Segment1_D;
	assign o_Segment1_E = ~w_Segment1_E;
	assign o_Segment1_F = ~w_Segment1_F;
	assign o_Segment1_G = ~w_Segment1_G;
	
	assign o_Segment2_A = ~w_Segment2_A;
	assign o_Segment2_B = ~w_Segment2_B;
	assign o_Segment2_C = ~w_Segment2_C;
	assign o_Segment2_D = ~w_Segment2_D;
	assign o_Segment2_E = ~w_Segment2_E;
	assign o_Segment2_F = ~w_Segment2_F;
	assign o_Segment2_G = ~w_Segment2_G;
	*/
	
	
	assign o_Segment1_A = ~(lims_idxs[0][0]);
	assign o_Segment1_B = ~(lims_idxs[0][1]);
	assign o_Segment1_C = ~(lims_idxs[0][2]);
	assign o_Segment1_D = ~(lims_idxs[1][0]);
	assign o_Segment1_E = ~(lims_idxs[1][1]);
	assign o_Segment1_F = ~(lims_idxs[1][2]);
	assign o_Segment1_G = 1;
	
	assign o_Segment2_A = ~(lims_idxs[2][0]);
	assign o_Segment2_B = ~(lims_idxs[2][1]);
	assign o_Segment2_C = ~(lims_idxs[2][2]);
	assign o_Segment2_D = ~(lims_idxs[3][0]);
	assign o_Segment2_E = ~(lims_idxs[3][1]);
	assign o_Segment2_F = ~(lims_idxs[3][2]);
	assign o_Segment2_G = 1;
	
	
	assign o_LED_1 = dbg1_leds[0:0];
	assign o_LED_2 = dbg1_leds[1:1];
	assign o_LED_3 = dbg1_leds[2:2];
	assign o_LED_4 = dbg1_leds[3:3];

endmodule
