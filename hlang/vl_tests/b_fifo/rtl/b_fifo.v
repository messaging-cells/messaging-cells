
`include "hglobal.v"

`default_nettype	none

`define NS_NUM_TEST 10
`define NS_TEST_MIN_ADDR 1
`define NS_TEST_MAX_ADDR 14
//`define NS_TEST_MAX_ADDR 1

module test_top 
#(parameter 
	PSZ=`NS_PACKET_SIZE, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE
)(
	input  i_clk,      // Main Clock (25 MHz)

	output o_LED_1,
	output o_LED_2,
	output o_LED_3,
	output o_LED_4
);

	`NS_DECLARE_LINK(lnk_1)
	
	wire has_err;

	pakout 
	gt_01 (
		.i_clk(i_clk),
		
		`NS_INSTA_CHNL(rcv0, lnk_1)
		
		.has_err(has_err),
	);

	wire is_busy;
	
	pakout_io #(.MIN_ADDR(`NS_TEST_MIN_ADDR), .MAX_ADDR(`NS_TEST_MAX_ADDR))
	//pakout_io
	gt_02 (
		.i_clk(i_clk),
		
		`NS_INSTA_CHNL(o0, lnk_1)
		
		.dbg_busy(is_busy),
	);
	
	assign o_LED_1 = has_err;
	assign o_LED_2 = lnk_1_req;
	assign o_LED_3 = is_busy;
	assign o_LED_4 = lnk_1_ack;

endmodule
