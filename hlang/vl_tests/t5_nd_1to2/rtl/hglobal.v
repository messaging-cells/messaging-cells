
`ifndef HGLOBAL_V_FILE
`define HGLOBAL_V_FILE 1
//--------------------------------------------

`define NS_ON 1
`define NS_OFF 0

`define NS_TRUE 1
`define NS_FALSE 0

`define ns_bit_toggle(bb) bb <= ~bb

`define ns_f_10HZ 1250000
`define ns_f_5HZ 2500000
`define ns_f_2HZ 6250000
`define ns_f_1HZ 12500000
	
`define NS_ADDRESS_SIZE 6
`define NS_DATA_SIZE 4

`define NS_MESSAGE_FIFO_SIZE 1  // 1, 2 or 4 ***ONLY***

`define NS_GT_OP 1
`define NS_GTE_OP 2
`define NS_LT_OP 3
`define NS_LTE_OP 4
`define NS_EQ_OP 5


`define NS_CMP_OP(op, pm1, pm2) ( \
	(op == `NS_GT_OP)? \
		((pm1) > (pm2)):( \
	(op == `NS_GTE_OP)? \
		((pm1) >= (pm2)):( \
	(op == `NS_LT_OP)? \
		((pm1) < (pm2)):( \
	(op == `NS_LTE_OP)? \
		((pm1) <= (pm2)):( \
		(pm1) == (pm2) \
	))))) 


`define NS_RANGE_CMP_OP(is_dbl, op1, pm1, pm2, op2, pm3, pm4) ( \
	(is_dbl == `NS_TRUE)?(`NS_CMP_OP(op1, pm1, pm2) && `NS_CMP_OP(op2, pm3, pm4)):(`NS_CMP_OP(op1, pm1, pm2)) )
	


`define NS_MSG_FIFO_IDX_SZ ((FSZ == 4)?(2):(1))


`define NS_FULL_MSG_SZ  (ASZ + ASZ + DSZ)
	
`define NS_DECLARE_REG_MSG(mg) \
	reg [ASZ-1:0] mg``_src = 0; \
	reg [ASZ-1:0] mg``_dst = 0; \
	reg [DSZ-1:0] mg``_dat = 0; \


`define NS_ASSIGN_OUT_MSG(ou, mg) \
	assign ou``_src = mg``_src; \
	assign ou``_dst = mg``_dst; \
	assign ou``_dat = mg``_dat; 


`define NS_DECLARE_OUT_CHNL(nam) \
	output wire [ASZ-1:0] nam``_src, \
	output wire [ASZ-1:0] nam``_dst, \
	output wire [DSZ-1:0] nam``_dat, \
	output wire nam``_req, \
	input wire nam``_ack, 


`define NS_DECLARE_IN_CHNL(nam) \
	input wire [ASZ-1:0] nam``_src, \
	input wire [ASZ-1:0] nam``_dst, \
	input wire [DSZ-1:0] nam``_dat, \
	input wire nam``_req, \
	output wire nam``_ack, 


`define NS_DECLARE_LINK(lnk) \
	wire [ASZ-1:0] lnk``_src; \
	wire [ASZ-1:0] lnk``_dst; \
	wire [DSZ-1:0] lnk``_dat; \
	wire lnk``_req; \
	wire lnk``_ack; 

	
`define NS_INSTA_CHNL(chn, lnk) \
	.chn``_src(lnk``_src), \
	.chn``_dst(lnk``_dst), \
	.chn``_dat(lnk``_dat), \
	.chn``_req(lnk``_req), \
	.chn``_ack(lnk``_ack), 

	
`define NS_REG_MSG_INIT(mg) \
	mg``_src <= 0; \
	mg``_dst <= 0; \
	mg``_dat <= 0; \


// ASZ + ASZ + DSZ
`define NS_MG_SRC_SECTION  ((ASZ + ASZ + DSZ)-1):(ASZ + DSZ)
`define NS_MG_DST_SECTION  ((ASZ + DSZ)-1):DSZ
`define NS_MG_DAT_SECTION  (DSZ-1):0

`define NS_DECLARE_FIFO(fif) \
	integer fif``ii=0; \
	reg [0:0] fif``_busy [FSZ-1:0]; \
	reg [`NS_FULL_MSG_SZ-1:0] fif``_data[FSZ-1:0]; \
	reg [`NS_MSG_FIFO_IDX_SZ-1:0] fif``_hd_idx = 0; \
	reg [`NS_MSG_FIFO_IDX_SZ-1:0] fif``_tl_idx = 0;


`define NS_FIFO_INIT(fif) \
	for(fif``ii = 0; fif``ii < FSZ; fif``ii = fif``ii+1) begin \
		fif``_busy[fif``ii] <= `NS_OFF; \
	end \
	for(fif``ii = 0; fif``ii < FSZ; fif``ii = fif``ii+1) begin \
		fif``_data[fif``ii] <= 0; \
	end \
	fif``_hd_idx <= 0; \
	fif``_tl_idx <= 0;


`define NS_FIFO_SET_IDX(chn, fif, idx) fif``_data[idx] <= {chn``_src, chn``_dst, chn``_dat};

/*
`define NS_FIFO_SET_IDX(chn, fif, idx) \
	fif``_data[idx][`NS_MG_SRC_SECTION] <= chn``_src; \
	fif``_data[idx][`NS_MG_DST_SECTION] <= chn``_dst; \
	fif``_data[idx][`NS_MG_DAT_SECTION] <= chn``_dat; \

*/

`define NS_FIFO_GET_IDX(chn, fif, idx) \
	chn``_src <= fif``_data[idx][`NS_MG_SRC_SECTION]; \
	chn``_dst <= fif``_data[idx][`NS_MG_DST_SECTION]; \
	chn``_dat <= fif``_data[idx][`NS_MG_DAT_SECTION]; 
	

`define NS_INC_IDX(idx) \
	if(idx == (FSZ-1)) begin \
		idx <= 0; \
	end else begin \
		idx <= idx + 1; \
	end 


`define NS_TRY_INC_HEAD(fif, mg_in, the_ack) \
	if(! fif``_busy[fif``_hd_idx]) begin \
		fif``_busy[fif``_hd_idx] <= `NS_ON; \
		`NS_FIFO_SET_IDX(mg_in, fif, fif``_hd_idx); \
		`NS_INC_IDX(fif``_hd_idx); \
		the_ack <= `NS_ON; \
	end 


`define NS_TRY_INC_TAIL(fif, mg_out, the_out_ack, the_req) \
	if(fif``_busy[fif``_tl_idx]) begin \
		if(! the_req && ! the_out_ack) begin \
			fif``_busy[fif``_tl_idx] <= `NS_OFF; \
			`NS_FIFO_GET_IDX(mg_out, fif, fif``_tl_idx); \
			`NS_INC_IDX(fif``_tl_idx); \
			the_req <= `NS_ON; \
		end \
	end 


/*
`define NS_TRY_SET_OUT(fif, mg_out, out_is_busy) \
	if(fif``_busy[fif``_tl_idx] && ! out_is_busy) begin \
		fif``_busy[fif``_tl_idx] <= `NS_OFF; \
		out_is_busy <= `NS_ON; \
		`NS_FIFO_GET_IDX(mg_out, fif, fif``_tl_idx); \
		`NS_INC_IDX(fif``_tl_idx); \
	end 


`define NS_TRY_SEND_OUT(out_is_busy, the_out_ack, the_req) \
	if(! the_req && ! the_out_ack && out_is_busy) begin \
		the_req <= `NS_ON; \
	end \
	if(the_req && the_out_ack) begin \
		if(out_is_busy) begin \
			out_is_busy <= `NS_OFF; \
		end \
		the_req <= `NS_OFF; \
	end
*/
	
//--------------------------------------------
`endif // HGLOBAL_V_FILE
