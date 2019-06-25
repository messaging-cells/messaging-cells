
`include "hglobal.v"

module hnet_top (
	input  i_clk,      // Main Clock (25 MHz)
	input  i_Switch_1, 
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
	
	reg [`DATA_SIZE-1:0] disp_i_data = 1;
	reg [`DATA_SIZE-1:0] disp_o_data = 2;
	
	reg r_LED_1 = `OFF;
	reg r_LED_2 = `OFF;
	reg r_LED_3 = `OFF;
	reg r_LED_4 = `OFF;
  
	wire cn_req;
	wire cn_ack;
	wire [`ADDRESS_SIZE-1:0] cn_addr;
	wire [`DATA_SIZE-1:0] cn_data;
	wire cn_err;
	
	//reg [`DATA_SIZE-1:0] cn_i_data = 0;
	wire [`DATA_SIZE-1:0] cn_o_data;

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
	
	cellnet_source cn_src_1 (
		.i_clk(clk_src),
		//.i_clk(i_clk),
		.o_addr(cn_addr),
		.o_dat(cn_data),
		.o_req(cn_req),
		.i_ack(cn_ack)
	);

	cellnet_sink cn_snk_1 (
		.i_clk(clk_snk),
		//.i_clk(i_clk),
		.i_addr(cn_addr),
		.i_dat(cn_data),
		.i_req(cn_req),
		.o_ack(cn_ack),
		.o_dat(cn_o_data),
		.o_err(cn_err)
	);
     
	// Instantiate Debounce Filter
	debounce Debounce_Switch_Inst(
		.i_Clk(i_clk),
		.i_Switch(i_Switch_1),
		.o_Switch(w_Switch_1)
	);
		
	// Purpose: When Switch is pressed, update display i_data and o_data
	always @(posedge i_clk)
	begin
		r_Switch_1 <= w_Switch_1;
		
		if((w_Switch_1 == `ON) && (r_Switch_1 == `OFF))
		begin
			disp_i_data <= cn_data;
			disp_o_data <= cn_o_data;
		end
	end

	// CHECK err line
	always @(posedge i_clk)
	begin
		if(cn_err == `ON) begin
			r_LED_1 <= `ON;
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

	assign o_LED_1 = r_LED_1;
	assign o_LED_2 = r_LED_2;
	assign o_LED_3 = r_LED_3;
	assign o_LED_4 = r_LED_4;

endmodule
