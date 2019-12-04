
`include "hglobal.v"

`default_nettype	none

module hnet_top 
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
	
	reg [DSZ-1:0] disp_i_data = 2;
	reg [DSZ-1:0] disp_o_data = 2;
	
	reg r_LED_1 = `OFF;
	reg r_LED_2 = `OFF; // `CMP_OP(`LT_OP, 1, 2);
	reg r_LED_3 = `OFF; // `CMP_OP(`LT_OP, 3, 2);
	reg r_LED_4 = `OFF; // `CMP_OP(`LT_OP, 5, 5);
  
	wire err_1;
	wire err_2;
	
	// LNK_1
	wire [ASZ-1:0] lnk_1_addr;
	wire [DSZ-1:0] lnk_1_dat;
	wire lnk_1_req;
	wire lnk_1_ack;
	wire [DSZ-1:0] lnk_1_ck_dat;
	
	// LNK_
	wire [ASZ-1:0] lnk_2_addr;
	wire [DSZ-1:0] lnk_2_dat;
	wire lnk_2_req;
	wire lnk_2_ack;
	wire [DSZ-1:0] lnk_2_ck_dat;
  
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
	
	ln_tgt #(.LOCAL_ADDR(0), .MIN_ADDR(1), .MAX_ADDR(1))
	tg_1 (
		.i_clk(clk_src),
		//.i_clk(i_clk),
		// SRC_io
		.o_addr(lnk_1_addr),
		.o_dat(lnk_1_dat),
		.o_req(lnk_1_req),
		.i_ack(lnk_1_ack),
		// SNK_io
		.i_addr(lnk_2_addr),
		.i_dat(lnk_2_dat),
		.i_req(lnk_2_req),
		.o_ack(lnk_2_ack),
		.o_ck_dat(lnk_2_ck_dat),
		.o_err(err_1)
	);

	ln_tgt #(.LOCAL_ADDR(1), .MIN_ADDR(0), .MAX_ADDR(0))
	tg_2 (
		.i_clk(clk_snk),
		//.i_clk(i_clk),
		// SRC_io
		.o_addr(lnk_2_addr),
		.o_dat(lnk_2_dat),
		.o_req(lnk_2_req),
		.i_ack(lnk_2_ack),
		// SNK_io
		.i_addr(lnk_1_addr),
		.i_dat(lnk_1_dat),
		.i_req(lnk_1_req),
		.o_ack(lnk_1_ack),
		.o_ck_dat(lnk_1_ck_dat),
		.o_err(err_2)
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
		
		//if((w_Switch_1 == `ON) && (r_Switch_1 == `OFF))
		if(`CMP_OP(`EQ_OP, w_Switch_1, `ON) && `CMP_OP(`EQ_OP, r_Switch_1, `OFF))
		begin
			disp_i_data <= lnk_1_dat;
			disp_o_data <= lnk_1_ck_dat;
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

	assign o_LED_1 = (err_1 || err_2);
	assign o_LED_2 = r_LED_2;
	assign o_LED_3 = r_LED_3;
	assign o_LED_4 = r_LED_4;

endmodule
