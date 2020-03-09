
`include "hglobal.v"

`default_nettype	none

`define NS_NUM_TEST 5
`define NS_TEST_MIN_ADDR 0
`define NS_TEST_MAX_ADDR 55
`define NS_TEST_REF_ADDR 23

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

	
	debounce but1_fixed(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_1),
		.o_Switch(w_Switch_1)
	);
	
	debounce but2_fixed(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_2),
		.o_Switch(w_Switch_2)
	);
	
	debounce but3_fixed(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_3),
		.o_Switch(w_Switch_3)
	);
	
	debounce but4_fixed(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_4),
		.o_Switch(w_Switch_4)
	);
	
	reg [2:0] c_src = 0;
	reg [6:0] c_snk = 0;
	
	reg clk_src = `NS_OFF;
	reg clk_snk = `NS_OFF;

	reg clk0 = `NS_OFF;
	reg clk1 = `NS_OFF;
	reg clk2 = `NS_OFF;
	reg clk3 = `NS_OFF;
	
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

	always @(posedge i_clk)
	begin
		if(c_src == 0) begin
			c_src <= 1;
			`ns_bit_toggle(clk_src);
		end
		else  begin
			c_src <= (c_src << 1);
		end
		if(c_snk == 0) begin
			c_snk <= 1;
			`ns_bit_toggle(clk_snk);
		end
		else  begin
			c_snk <= (c_snk << 1);
		end
	end
	
	nd_1to2 #(.OPER_1(`NS_GT_OP), .REF_VAL_1(`NS_TEST_REF_ADDR))
	gt1to2 (
		//.i_clk(i_clk),
		.i_clk(clk_src),
		
		.reset(the_reset),
		.ready(the_all_ready),
		
		//.i_clk(i_clk),
		// out0
		`NS_INSTA_CHNL(snd0, lnk_0)
		// out1
		`NS_INSTA_CHNL(snd1, lnk_1)
		// in
		`NS_INSTA_CHNL(rcv0, lnk_2)
	);

	io_1to2 #(.MIN_ADDR(`NS_TEST_MIN_ADDR), .MAX_ADDR(`NS_TEST_MAX_ADDR), .OPER_1(`NS_GT_OP), .REF_VAL_1(`NS_TEST_REF_ADDR))
	io_t3 (
		//.i_clk(i_clk),
		.i_clk(clk_snk),
		
		// SRC
		`NS_INSTA_CHNL(o0, lnk_2)
		// SNK0
		`NS_INSTA_CHNL(i0, lnk_0)
		// SNK1
		`NS_INSTA_CHNL(i1, lnk_1)
		
		`NS_INSTA_DBG_CHNL(dbg, dbg1, i_clk)
	);
	
	wire sw1_ON = ((w_Switch_1 == `NS_ON) && (r_Switch_1 == `NS_OFF));
	wire sw1_OFF = ((w_Switch_1 == `NS_OFF) && (r_Switch_1 == `NS_ON));
	always @(posedge i_clk)
	begin
		r_Switch_1 <= w_Switch_1;
		
		if(sw1_ON)
		begin
			`ns_bit_toggle(clk2);
		end
		else 
		if(sw1_OFF)
		begin
			`ns_bit_toggle(clk2);
		end
	end

	wire sw2_ON = ((w_Switch_2 == `NS_ON) && (r_Switch_2 == `NS_OFF));
	wire sw2_OFF = ((w_Switch_2 == `NS_OFF) && (r_Switch_2 == `NS_ON));
	always @(posedge i_clk)
	begin
		r_Switch_2 <= w_Switch_2;
		
		if(sw2_ON)
		begin
			`ns_bit_toggle(clk3);
		end
		if(sw2_OFF)
		begin
			`ns_bit_toggle(clk3);
		end
	end

	wire sw3_ON = ((w_Switch_3 == `NS_ON) && (r_Switch_3 == `NS_OFF));
	wire sw3_OFF = ((w_Switch_3 == `NS_OFF) && (r_Switch_3 == `NS_ON));
	
	wire sw4_ON = ((w_Switch_4 == `NS_ON) && (r_Switch_4 == `NS_OFF));
	wire sw4_OFF = ((w_Switch_4 == `NS_OFF) && (r_Switch_4 == `NS_ON));
	
	reg selecting = `NS_OFF;
	reg was_both_on = `NS_OFF;
	reg updating = `NS_OFF;
	
	always @(posedge i_clk)
	begin
		r_Switch_3 <= w_Switch_3;
		r_Switch_4 <= w_Switch_4;
		
		if(sw3_OFF && ! r_Switch_4)
		begin
			if(was_both_on) begin
				was_both_on <= `NS_OFF;
			end else begin
				selecting <= `NS_ON;
				`NS_INC_IDX(dbg_case_hi, 16);
			end
		end
		else
		if(sw4_OFF && ! r_Switch_3)
		begin
			if(was_both_on) begin
				was_both_on <= `NS_OFF;
			end else begin
				selecting <= `NS_ON;
				`NS_INC_IDX(dbg_case_lo, 16);
			end
		end
		else 
		if((sw3_OFF && r_Switch_4) || (sw4_OFF && r_Switch_3) || (sw3_OFF && sw4_OFF))
		begin
			was_both_on <= `NS_ON;
			selecting <= `NS_OFF;
			updating = `NS_ON;
		end
		
		if(selecting)
		begin
			io_leds <= 0;
			io_disp0 <= dbg_case_hi;
			io_disp1 <= dbg_case_lo;
		end
		if(updating)
		begin
			updating <= `NS_OFF;
			if((io_leds == 0) && (io_disp0 == dbg_case_hi) && (io_disp1 == dbg_case_lo))
			begin
				//`NS_MOV_REG_DBG(io, dbg0)
				`NS_MOV_REG_DBG(io, dbg1)
			end else begin
				selecting <= `NS_ON;
			end
		end
	end

	bin_to_disp Id0(
	.i_Clk(i_clk),
	.i_Binary_Num(io_disp0),
	.o_Segment_A(w_Segment1_A),
	.o_Segment_B(w_Segment1_B),
	.o_Segment_C(w_Segment1_C),
	.o_Segment_D(w_Segment1_D),
	.o_Segment_E(w_Segment1_E),
	.o_Segment_F(w_Segment1_F),
	.o_Segment_G(w_Segment1_G)
	);
	
	// Instantiate Binary to 7-Segment Converter
	bin_to_disp Id1(
	.i_Clk(i_clk),
	.i_Binary_Num(io_disp1),
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

	/*
	wire [3:0] tl = 4'b1100;

	assign o_LED_1 = tl[0:0];
	assign o_LED_2 = tl[1:1];
	assign o_LED_3 = tl[2:2];
	assign o_LED_4 = tl[3:3];
	*/

	assign o_LED_1 = dbg1_leds[0:0];
	assign o_LED_2 = dbg1_leds[1:1];
	assign o_LED_3 = dbg1_leds[2:2];
	assign o_LED_4 = dbg1_leds[3:3];

endmodule
