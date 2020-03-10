
`include "hglobal.v"

`default_nettype	none

`define NS_NUM_TEST 10
`define NS_TEST_MIN_ADDR 1
`define NS_TEST_MAX_ADDR 14
`define NS_TEST_REF_ADDR 23

`define NS_NUM_DBG_CASES 12


module test_top 
#(parameter 
	FSZ=`NS_PACKOUT_FSZ, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE
)( //==============================================
	input  i_clk,
	
	output o_LED_1,
	output o_LED_2,
	output o_LED_3,
	output o_LED_4
); //==============================================

	reg [3:0] io_leds = 0;

	reg [7:0] all_err = 0;
	

	`NS_DECLARE_REG_MSG(mg0)
	`NS_DECLARE_REG_MSG(mg1)
	`NS_DECLARE_REG_MSG(mg2)
	`NS_DECLARE_REG_MSG(mg3)
	`NS_DECLARE_REG_MSG(mg4)
	
	reg [`NS_FULL_MSG_SZ-1:0] mg_data;
	
	
	localparam ST_INI = 8'h20;
	localparam ST_SET = 8'h21;
	localparam ST_GET = 8'h22;
	localparam ST_CHK = 8'h23;

	reg [7:0] curr_state = ST_INI;
	`NS_DECLARE_FIFO(fif0)
	
	always @(posedge i_clk)
	begin
	case(curr_state)
		ST_INI:
		begin
			io_leds[0:0] <= `NS_ON;
			`NS_FIFO_INIT(fif0)
			mg0_src <= 1;
			mg0_dst <= 2;
			mg0_dat <= 3;
			mg0_red <= 4;
			curr_state <= ST_SET;
		end
		ST_SET:
		begin
			`NS_FIFO_SET_IDX(mg0, fif0, 0)
			`NS_MOV_REG_MSG(mg2, mg0)
			`NS_SEQ_SET(mg_data, mg0)
			curr_state <= ST_GET;
		end
		ST_GET:
		begin
			`NS_FIFO_GET_IDX(mg1, fif0, 0)
			`NS_MOV_REG_MSG(mg3, mg2)
			`NS_SEQ_GET(mg_data, mg4)
			curr_state <= ST_CHK;
		end
		ST_CHK:
		begin
			if(! `NS_REG_MSG_RED_EQ(mg0, 1, 2, 3, 4)) begin
				all_err[0:0] <= `NS_ON;
			end
			if(! `NS_REG_MSG_RED_EQ(mg1, 1, 2, 3, 4)) begin
				all_err[1:1] <= `NS_ON;
			end
			if(! `NS_REG_MSG_RED_EQ(mg2, 1, 2, 3, 4)) begin
				all_err[2:2] <= `NS_ON;
			end
			if(! `NS_REG_MSG_RED_EQ(mg3, 1, 2, 3, 4)) begin
				all_err[3:3] <= `NS_ON;
			end
			if(! `NS_REG_MSG_RED_EQ(mg4, 1, 2, 3, 4)) begin
				all_err[4:4] <= `NS_ON;
			end
			io_leds[1:1] <= `NS_ON;
		end
	endcase
	end
	
	assign o_LED_1 = io_leds[0:0];
	assign o_LED_2 = io_leds[1:1];
	assign o_LED_3 = io_leds[2:2];
	assign o_LED_4 = (|  all_err);

endmodule
