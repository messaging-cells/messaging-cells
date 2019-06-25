
`include "hglobal.v"

`default_nettype	none

module formal_top ();
 
	wire cn_clk;
	wire cn_req;
	wire cn_ack;
	wire [`ADDRESS_SIZE-1:0] cn_addr;
	wire [`DATA_SIZE-1:0] cn_data;
	wire cn_err;
	
	wire [`DATA_SIZE-1:0] cn_o_data;

	cellnet_source cn_src_1 (
		.i_clk(cn_clk),
		.o_addr(cn_addr),
		.o_dat(cn_data),
		.o_req(cn_req),
		.i_ack(cn_ack)
	);

	cellnet_sink cn_snk_1 (
		.i_clk(cn_clk),
		.i_addr(cn_addr),
		.i_dat(cn_data),
		.i_req(cn_req),
		.o_ack(cn_ack),
		.o_dat(cn_o_data),
		.o_err(cn_err)
	);

	`ifdef	FORMAL
		initial assert(cn_req == `OFF);
	`endif
	
     
endmodule
