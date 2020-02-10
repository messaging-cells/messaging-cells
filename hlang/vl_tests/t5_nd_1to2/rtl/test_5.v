
`include "hglobal.v"

`default_nettype	none

module test_5_top 
#(parameter ASZ=`ADDRESS_SIZE, DSZ=`DATA_SIZE)
(
	input  i_clk,      // Main Clock (25 MHz)
	input  i_Switch_3, 
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
 
	wire w_Switch_1;
	reg  r_Switch_1 = `OFF;

	reg [2:0] c_src = 0;
	reg [6:0] c_snk = 0;
	
	reg clk_src = `OFF;
	reg clk_snk = `OFF;
	
	reg [DSZ-1:0] disp_i_data = 3;
	reg [DSZ-1:0] disp_o_data = 3;
	
	//reg r_LED_1 = `OFF;
	//reg r_LED_2 = `OFF;
	reg r_LED_3 = `OFF;
	reg r_LED_4 = `OFF;
  
	wire err_0;
	wire err_1;
	
	// LNK_0
	`DECLARE_LINK(lnk_0)
	wire [DSZ-1:0] lnk_0_ck_dat;
	
	// LNK_1_
	`DECLARE_LINK(lnk_1)
	wire [DSZ-1:0] lnk_1_ck_dat;
  
	// LNK_2
	`DECLARE_LINK(lnk_2)
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
			`bit_toggle(clk_src);
		end
		else  begin
			c_src <= (c_src << 1);
		end
		if(c_snk == 0) begin
			c_snk <= 1;
			`bit_toggle(clk_snk);
		end
		else  begin
			c_snk <= (c_snk << 1);
		end
	end
	
	nd_1to2 #(.OPER_1(`GT_OP), .REF_VAL_1(3))
	gt1to2 (
		.i_clk(clk_src),
		//.i_clk(i_clk),
		// out0
		`INSTA_CHNL(snd0, lnk_0)
		// out1
		`INSTA_CHNL(snd1, lnk_1)
		// in
		`INSTA_CHNL(rcv0, lnk_2)
	);

	io_1to2 #(.MIN_ADDR(0), .MAX_ADDR(5), .OPER_1(`GT_OP), .REF_VAL_1(3))
	io_t3 (
		.i_clk(clk_snk),
		//.i_clk(i_clk),
		// SRC
		`INSTA_CHNL(o0, lnk_2)
		// SNK0
		`INSTA_CHNL(i0, lnk_0)
		.o_0_ck_dat(lnk_0_ck_dat),
		.o_0_err(err_0),
		// SNK1
		`INSTA_CHNL(i1, lnk_1)
		.o_1_ck_dat(lnk_1_ck_dat),
		.o_1_err(err_1)
	);
	
	// Instantiate Debounce Filter
	debounce Debounce_Switch_Inst(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_3),
		.o_Switch(w_Switch_1)
	);
		
	// Purpose: When Switch is pressed, update display i_data and o_data
	always @(posedge i_clk)
	begin
		r_Switch_1 <= w_Switch_1;
		
		if((w_Switch_1 == `ON) && (r_Switch_1 == `OFF))
		begin
			disp_i_data <= lnk_0_dat;
			disp_o_data <= lnk_0_ck_dat;
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
	assign o_LED_3 = r_LED_3;
	assign o_LED_4 = r_LED_4;

endmodule