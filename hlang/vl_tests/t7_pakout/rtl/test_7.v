
`include "hglobal.v"

`default_nettype	none

`define NS_NUM_TEST 7
`define NS_TEST_MIN_ADDR 1
`define NS_TEST_MAX_ADDR 14
`define NS_TEST_REF_ADDR 23

`define NS_NUM_DBG_CASES 12


module test_top 
#(parameter 
	PSZ=`NS_PACKET_SIZE, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE
)(
	input  i_clk,      
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
	but1_fixed(
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

	reg [2:0] clk_0_cnt = 0;
	reg [6:0] clk_1_cnt = 0;
	
	reg clk0 = `NS_OFF;
	reg clk1 = `NS_OFF;
	reg clk2 = `NS_OFF;
	reg clk3 = `NS_OFF;
	
	reg [3:0] io_leds = 0;
	reg [3:0] io_disp0 = `NS_NUM_TEST;
	reg [3:0] io_disp1 = `NS_NUM_TEST;
	
	//reg r_LED_1 = `NS_OFF;
  
	reg dbg_selecting_case = `NS_OFF;
	reg  [3:0] dbg_case_hi = 0;
	reg  [3:0] dbg_case_lo = 0;

	reg updating = `NS_OFF;	// UPDATING DBG_CASE
	reg selecting = `NS_OFF;
	reg was_both_on = `NS_OFF;
	
	`NS_DECLARE_DBG_LINK(dbg0)
	`NS_DECLARE_DBG_LINK(dbg1)
	
	assign dbg0_case = {dbg_case_hi, dbg_case_lo};
	assign dbg0_doit = was_both_on;
	assign dbg1_case = {dbg_case_hi, dbg_case_lo};
	assign dbg1_doit = was_both_on;
	
	// LNK_0
	`NS_DECLARE_PAKIO_LINK(lnk_0)
	
	// LNK_1_
	`NS_DECLARE_LINK(lnk_1)
  
	// LNK_2
	`NS_DECLARE_LINK(lnk_2)

	always @(posedge i_clk)
	begin
		if(clk_0_cnt == 0) begin
			clk_0_cnt <= 1;
			`ns_bit_toggle(clk0);
		end
		else  begin
			clk_0_cnt <= (clk_0_cnt << 1);
		end
		
		if(clk_1_cnt == 0) begin
			clk_1_cnt <= 1;
			`ns_bit_toggle(clk1);
		end
		else  begin
			clk_1_cnt <= (clk_1_cnt << 1);
		end
		
	end
	
	pakout 
	gt_01 (
		.i_clk(i_clk),
		//.i_clk(clk2),
		
		.reset(the_reset),
		.ready(the_all_ready),
		
		//.i_clk(i_clk),
		// out0
		`NS_INSTA_SND_PAKIO_CHNL(snd0, lnk_0),
		// in0
		`NS_INSTA_RCV_CHNL(rcv0, lnk_1),
		
		`NS_INSTA_DBG_CHNL(dbg, dbg0, i_clk)
	);

	pakout_io #(.MIN_ADDR(`NS_TEST_MIN_ADDR), .MAX_ADDR(`NS_TEST_MAX_ADDR))
	gt_02 (
		.i_clk(i_clk),
		.src_clk(clk1),
		.snk_clk(clk1),
		
		// SRC0
		`NS_INSTA_SND_CHNL(o0, lnk_1),
		
		// SNK0
		`NS_INSTA_RCV_PAKIO_CHNL(i0, lnk_0),

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
			updating <= `NS_ON;
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
				//`NS_MOV_REG_DBG(io, dbg1)
			end else begin
				selecting <= `NS_ON;
			end
		end
	end

	bin_to_disp disp_0(
	.i_Clk(i_clk),
	.i_Binary_Num(dbg1_disp0),
	.o_Segment_A(w_Segment1_A),
	.o_Segment_B(w_Segment1_B),
	.o_Segment_C(w_Segment1_C),
	.o_Segment_D(w_Segment1_D),
	.o_Segment_E(w_Segment1_E),
	.o_Segment_F(w_Segment1_F),
	.o_Segment_G(w_Segment1_G)
	);
	
	// Instantiate Binary to 7-Segment Converter
	bin_to_disp disp1(
	.i_Clk(i_clk),
	.i_Binary_Num(dbg1_disp1),
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

	assign o_LED_1 = dbg1_leds[0:0];
	assign o_LED_2 = dbg1_leds[1:1];
	assign o_LED_3 = dbg1_leds[2:2];
	assign o_LED_4 = dbg1_leds[3:3];

endmodule
