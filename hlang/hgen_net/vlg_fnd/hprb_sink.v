
`include "hglobal.v"

`default_nettype	none

module hprg_sink
#(parameter 
	MY_LOCAL_ADDR=0, 
	PRB_SRC_ADDR=0, 
	ASZ=`NS_ADDRESS_SIZE, 
	DSZ=`NS_DATA_SIZE, 
	RSZ=`NS_REDUN_SIZE
)(
	`NS_DECLARE_GLB_CHNL(gch),
	
	// SNK_0
	`NS_DECLARE_IN_CHNL(rcv0),
	
	`NS_DECLARE_DBG_ERR_CHNL(err0)
);

	parameter RCV_REQ_CKS = `NS_REQ_CKS;
	
	`NS_DEBOUNCER_REQ(gch_clk, gch_reset, rcv0)

	reg [0:0] rg_rdy = `NS_OFF;
	
	// SNK_0 regs
	reg [0:0] has_inp0 = `NS_OFF;
	reg [0:0] inp0_has_redun = `NS_OFF;
	reg [0:0] inp0_done_cks = `NS_OFF;
	`NS_DECLARE_REG_MSG(inp0)
	wire [RSZ-1:0] inp0_calc_redun;
	reg [RSZ-1:0] inp0_redun = 0;
	calc_redun #(.ASZ(ASZ), .DSZ(DSZ), .RSZ(RSZ)) 
		md_calc_red0 (inp0_src, inp0_dst, inp0_dat, inp0_calc_redun);
	
	
	reg [0:0] inp0_ack = `NS_OFF;
	reg [DSZ-1:0] inp0_back_dat = 15;
	reg [0:0] inp0_err = `NS_OFF;
	
	`NS_DECLARE_REG_DBG_ERR(inp0_err)  // inp0_err_error
	
	//SNK_0
	always @(posedge snk0_clk)
	begin
		if(gch_reset) begin
			rg_rdy <= `NS_OFF;
		end
		if(! gch_reset && ! rg_rdy) begin
			rg_rdy <= ! rg_rdy;
			
			has_inp0 = `NS_OFF;
			inp0_has_redun = `NS_OFF;
			inp0_done_cks = `NS_OFF;
			`NS_REG_MSG_INIT(inp0)
			inp0_redun = 0;
			
			inp0_ack = `NS_OFF;
			inp0_back_dat = 15;
			
			`NS_REG_DBG_ERR_INIT(inp0_err)

		end
		if(! gch_reset && rg_rdy) begin
			if(rcv0_ckd_req && (! inp0_ack)) begin
				if(! has_inp0) begin
					has_inp0 <= `NS_ON;
					`NS_MOV_REG_MSG(inp0, rcv0)
				end
				else
				if(! inp0_has_redun) begin
					inp0_has_redun <= `NS_ON;
					inp0_redun <= inp0_calc_redun;
				end
				else
				if(! inp0_done_cks) begin
					inp0_done_cks <= `NS_ON;
					if(! inp0_err_error) begin
						if(inp0_dst != MY_LOCAL_ADDR) begin
							inp0_err_error <= `NS_ON;
							`NS_MOV_REG_MSG(inp0_err, inp0)
						end 
						else
						if(inp0_src != PRB_SRC_ADDR) begin
							inp0_err_error <= `NS_ON;
							`NS_MOV_REG_MSG(inp0_err, inp0)
						end
						else
						if(inp0_red != inp0_redun) begin
							inp0_err_error <= `NS_ON;
							`NS_MOV_REG_MSG(inp0_err, inp0)
						end
						//else
						if((inp0_back_dat <= 14) && ((inp0_back_dat + 1) != inp0_dat)) begin
							inp0_err_error <= `NS_ON;
							`NS_MOV_REG_MSG(inp0_err, inp0)
						end 
						else 
						begin 
							inp0_back_dat <= inp0_dat;
						end
					end
				end
				if(inp0_done_cks) begin
					has_inp0 <= `NS_OFF;
					inp0_has_redun <= `NS_OFF;
					inp0_done_cks <= `NS_OFF;
					
					inp0_ack <= `NS_ON;
				end
			end
			else
			if((! rcv0_ckd_req) && inp0_ack) begin
				inp0_ack <= `NS_OFF;
			end
		end
	end
	
	assign gch_ready = rg_rdy && rcv0_rdy;
	
	//SNK_0
	assign rcv0_ack_out = inp0_ack;
	
	`NS_ASSIGN_DBG_ERR(err0, inp0_err, MY_LOCAL_ADDR)
	
endmodule
