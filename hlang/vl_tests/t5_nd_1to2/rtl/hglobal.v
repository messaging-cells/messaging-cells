
`ifndef HGLOBAL_V_FILE
`define HGLOBAL_V_FILE 1
//--------------------------------------------

`define ON 1
`define OFF 0

`define TRUE 1
`define FALSE 0

`define bit_toggle(bb) bb <= ~bb

`define f_10HZ 1250000
`define f_5HZ 2500000
`define f_2HZ 6250000
`define f_1HZ 12500000
	
`define ADDRESS_SIZE 6
`define DATA_SIZE 4

`define MSG_DATA_1 5
`define MSG_DATA_2 7

`define GT_OP 1
`define GTE_OP 2
`define LT_OP 3
`define LTE_OP 4
`define EQ_OP 5


`define CMP_OP(op, pm1, pm2) ( \
	(op == `GT_OP)? \
		((pm1) > (pm2)):( \
	(op == `GTE_OP)? \
		((pm1) >= (pm2)):( \
	(op == `LT_OP)? \
		((pm1) < (pm2)):( \
	(op == `LTE_OP)? \
		((pm1) <= (pm2)):( \
		(pm1) == (pm2) \
	))))) 


`define RANGE_CMP_OP(is_dbl, op1, pm1, pm2, op2, pm3, pm4) ( \
	(is_dbl == `TRUE)?(`CMP_OP(op1, pm1, pm2) && `CMP_OP(op2, pm3, pm4)):(`CMP_OP(op1, pm1, pm2)) )
	

// 1, 2 or 4
`define MSG_BUFF_SZ  1

`define MSG_BUFF_IDX_SZ ((`MSG_BUFF_SZ == 4)?(2):(1))


`define FULL_MSG_SZ  (ASZ + ASZ + DSZ)
	
`define DECLARE_REG_MSG(mg) \
	reg [ASZ-1:0] mg``_src = 0; \
	reg [ASZ-1:0] mg``_dst = 0; \
	reg [DSZ-1:0] mg``_dat = 0; \


`define COPY_MSG(src_mg, dst_mg) \
	dst_mg``_src <= src_mg``_src; \
	dst_mg``_dst <= src_mg``_dst; \
	dst_mg``_dat<= src_mg``_dat; 


`define ASSIGN_OUT_MSG(ou, mg) \
	assign ou``_src = mg``_src; \
	assign ou``_dst = mg``_dst; \
	assign ou``_dat = mg``_dat; 


`define DECLARE_OUT_CHNL(nam) \
	output wire [ASZ-1:0] nam``_src, \
	output wire [ASZ-1:0] nam``_dst, \
	output wire [DSZ-1:0] nam``_dat, \
	output wire nam``_req, \
	input wire nam``_ack, 


`define DECLARE_IN_CHNL(nam) \
	input wire [ASZ-1:0] nam``_src, \
	input wire [ASZ-1:0] nam``_dst, \
	input wire [DSZ-1:0] nam``_dat, \
	input wire nam``_req, \
	output wire nam``_ack, 


`define DECLARE_LINK(lnk) \
	wire [ASZ-1:0] lnk``_src; \
	wire [ASZ-1:0] lnk``_dst; \
	wire [DSZ-1:0] lnk``_dat; \
	wire lnk``_req; \
	wire lnk``_ack; 

	
`define INSTA_CHNL(chn, lnk) \
	.chn``_src(lnk``_src), \
	.chn``_dst(lnk``_dst), \
	.chn``_dat(lnk``_dat), \
	.chn``_req(lnk``_req), \
	.chn``_ack(lnk``_ack), 

	
// ASZ + ASZ + DSZ
`define MG_SRC_SECTION  ((ASZ + ASZ + DSZ)-1):(ASZ + DSZ)
`define MG_DST_SECTION  ((ASZ + DSZ)-1):DSZ
`define MG_DAT_SECTION  (DSZ-1):0

`define DECLARE_FIFO(fif) \
	reg [0:0] fif``_busy [`MSG_BUFF_SZ-1:0]; \
	reg [`FULL_MSG_SZ-1:0] fif``_data[`MSG_BUFF_SZ-1:0]; \
	reg [`MSG_BUFF_IDX_SZ-1:0] fif``_hd_idx = 0; \
	reg [`MSG_BUFF_IDX_SZ-1:0] fif``_tl_idx = 0;


`define FIFO_SET_IDX(chn, fif, idx) fif``_data[idx] <= {chn``_src, chn``_dst, chn``_dat};

/*
`define FIFO_SET_IDX(chn, fif, idx) \
	fif``_data[idx][`MG_SRC_SECTION] <= chn``_src; \
	fif``_data[idx][`MG_DST_SECTION] <= chn``_dst; \
	fif``_data[idx][`MG_DAT_SECTION] <= chn``_dat; \

*/

`define FIFO_GET_IDX(chn, fif, idx) \
	chn``_src <= fif``_data[idx][`MG_SRC_SECTION]; \
	chn``_dst <= fif``_data[idx][`MG_DST_SECTION]; \
	chn``_dat <= fif``_data[idx][`MG_DAT_SECTION]; 
	

`define INC_IDX(idx) \
	if(idx == (`MSG_BUFF_SZ-1)) begin \
		idx <= 0; \
	end else begin \
		idx <= idx + 1; \
	end 


`define TRY_INC_HEAD(fif, mg_in, the_ack) \
	if(! fif``_busy[fif``_hd_idx]) begin \
		fif``_busy[fif``_hd_idx] <= `ON; \
		`FIFO_SET_IDX(mg_in, fif, fif``_hd_idx); \
		`INC_IDX(fif``_hd_idx); \
		the_ack <= `ON; \
	end 


`define TRY_INC_TAIL(fif, mg_out, the_out_ack, the_req) \
	if(fif``_busy[fif``_tl_idx]) begin \
		if(! the_req && ! the_out_ack) begin \
			fif``_busy[fif``_tl_idx] <= `OFF; \
			`FIFO_GET_IDX(mg_out, fif, fif``_tl_idx); \
			`INC_IDX(fif``_tl_idx); \
			the_req <= `ON; \
		end \
	end 

	
//--------------------------------------------
`endif // HGLOBAL_V_FILE
