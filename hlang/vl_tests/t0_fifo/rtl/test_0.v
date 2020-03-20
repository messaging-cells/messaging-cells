
`include "hglobal.v"

`default_nettype	none

`define NS_NUM_TEST 0
`define NS_TEST_MIN_ADDR 0
`define NS_TEST_MAX_ADDR 55
`define NS_TEST_REF_ADDR 23

module test_top 
#(parameter ASZ=`NS_ADDRESS_SIZE, DSZ=`NS_DATA_SIZE, RSZ=`NS_REDUN_SIZE)
(
	input  i_clk,      // Main Clock (25 MHz)
	input  i_Switch_1, 
	input  i_Switch_2, 
	
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

	reg [2:0] cnt_clk0 = 0;
	reg [3:0] cnt_clk1 = 0;
	reg [5:0] cnt_clk2 = 0;
	reg [7:0] cnt_clk3 = 0;
	
	reg clk_0 = `NS_OFF;
	reg clk_1 = `NS_OFF;
	reg clk_2 = `NS_OFF;
	reg clk_3 = `NS_OFF;
	
	reg [DSZ-1:0] disp_i_data = `NS_NUM_TEST;
	reg [DSZ-1:0] disp_o_data = `NS_NUM_TEST;
	
	//reg r_LED_1 = `NS_OFF;
	reg r_LED_2 = `NS_OFF;
	reg r_LED_3 = `NS_OFF;
	reg r_LED_4 = `NS_OFF;
  
	wire err_0;
	wire err_1;
	wire err_2;

	wire [DSZ-1:0] fst_err_0_inp;
	wire [DSZ-1:0] fst_err_0_dat;
	wire [DSZ-1:0] fst_err_1_inp;
	wire [DSZ-1:0] fst_err_1_dat;
	
	// LNK_0
	`NS_DECLARE_LINK(lnk_0)
	wire [DSZ-1:0] lnk_0_ck_dat;
	
	// LNK_1_
	`NS_DECLARE_LINK(lnk_1)
	wire [DSZ-1:0] lnk_1_ck_dat;
  
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
		// clk_0
		if(cnt_clk0 == 0) begin
			cnt_clk0 <= 1;
			`ns_bit_toggle(clk_0);
		end
		else  begin
			cnt_clk0 <= (cnt_clk0 << 1);
		end
		// clk_1
		if(cnt_clk1 == 0) begin
			cnt_clk1 <= 1;
			`ns_bit_toggle(clk_1);
		end
		else  begin
			cnt_clk1 <= (cnt_clk1 << 1);
		end
		// clk_2
		if(cnt_clk2 == 0) begin
			cnt_clk2 <= 1;
			`ns_bit_toggle(clk_2);
		end
		else  begin
			cnt_clk2 <= (cnt_clk2 << 1);
		end
		// clk_3
		if(cnt_clk3 == 0) begin
			cnt_clk3 <= 1;
			`ns_bit_toggle(clk_3);
		end
		else  begin
			cnt_clk3 <= (cnt_clk3 << 1);
		end
	end
	
	nd_fifo
	gtfifo (
		.i_clk(clk_2),
		//i_clk, clk_0, clk_1
		
		.reset(the_reset),
		.ready(the_all_ready),
		
		//.i_clk(i_clk),
		// out0
		`NS_INSTA_CHNL(snd0, lnk_0)
		// in0
		`NS_INSTA_CHNL(rcv0, lnk_1)
	);

	io_fifo #(.MIN_ADDR(`NS_TEST_MIN_ADDR), .MAX_ADDR(`NS_TEST_MAX_ADDR))
	io_t0 (
		.src_clk(clk_3),
		.snk_clk(clk_1),
		//i_clk, clk_0, clk_1
		
		// SRC0
		`NS_INSTA_CHNL(o0, lnk_1)
		// SNK0
		`NS_INSTA_CHNL(i0, lnk_0)
		
		.err_0(err_0),
		.err_1(err_1),
		
		.i0_ck_dat(lnk_0_ck_dat),
		.fst_err0_inp(fst_err_0_inp),
		.fst_err0_dat(fst_err_0_dat),
	);
	
	// Instantiate Debounce Filter
	debounce sw1_inst(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_1),
		.o_Switch(w_Switch_1)
	);
	
	// Purpose: When Switch is pressed, update display i_data and o_data
	always @(posedge i_clk)
	begin
		r_Switch_1 <= w_Switch_1;
		
		if((w_Switch_1 == `NS_ON) && (r_Switch_1 == `NS_OFF))
		begin
			if(err_0 || err_1) begin
				disp_i_data <= fst_err_0_inp;
				disp_o_data <= fst_err_0_dat;
			end else begin
				disp_i_data <= lnk_0_dat;
				disp_o_data <= lnk_0_ck_dat;
			end
		end
	end

	bin_to_disp disp_1(
	.i_Clk(i_clk),
	.i_Binary_Num(disp_i_data),
	.o_Segment_A(w_Segment1_A),
	.o_Segment_B(w_Segment1_B),
	.o_Segment_C(w_Segment1_C),
	.o_Segment_D(w_Segment1_D),
	.o_Segment_E(w_Segment1_E),
	.o_Segment_F(w_Segment1_F),
	.o_Segment_G(w_Segment1_G)
	);
	
	// Instantiate Binary to 7-Segment Converter
	bin_to_disp disp2(
	.i_Clk(i_clk),
	.i_Binary_Num(disp_o_data),
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

	assign o_LED_1 = err_0;
	assign o_LED_2 = err_1;
	assign o_LED_3 = 0;
	assign o_LED_4 = 0;

endmodule
