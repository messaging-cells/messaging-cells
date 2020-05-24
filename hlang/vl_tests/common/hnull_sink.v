
`include "hglobal.v"

`default_nettype	none

module hnull_sink
#(parameter 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE
)(
	`NS_DECLARE_GLB_CHNL(gch),
	`NS_DECLARE_IN_CHNL(rcv0)
	
);

	parameter RCV_REQ_CKS = `NS_REQ_CKS;
	
	`NS_DEBOUNCER_REQ(gch_clk, gch_reset, rcv0)
	
	reg [0:0] rg_rdy = `NS_OFF;
	
	// inp regs
	reg [0:0] rgi0_ack = `NS_OFF;

	always @(posedge gch_clk)
	begin
		if(gch_reset) begin
			rg_rdy <= `NS_OFF;
		end
		if(! gch_reset && ! rg_rdy) begin
			rg_rdy <= `NS_ON;
			
			rgi0_ack <= `NS_OFF;
		end
		if(! gch_reset && rg_rdy) begin
			if(rcv0_ckd_req && (! rgi0_ack)) begin
				rgi0_ack <= `NS_ON;
			end
			if((! rcv0_ckd_req) && rgi0_ack) begin
				rgi0_ack <= `NS_OFF;
			end
		end
	end

	assign gch_ready = rg_rdy && rcv0_rdy;
	
	//inp0
	assign rcv0_ack = rgi0_ack;
	
endmodule

