
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

	
`define DECLARE_REG_MSG(mg) \
	reg [ASZ-1:0] mg``_src = 0; \
	reg [ASZ-1:0] mg``_dst = 0; \
	reg [DSZ-1:0] mg``_dat = 0; \
	
	
`define COPY_MSG(src_mg, dst_mg) \
	dst_mg``_src <= src_mg``_src; \
	dst_mg``_dst <= src_mg``_dst; \
	dst_mg``_dat<= src_mg``_dat; \

	
`define ASSING_OUT_MSG(ou, mg) \
	assign ou``_src = mg``_src; \
	assign ou``_dst = mg``_dst; \
	assign ou``_dat = mg``_dat; \

	
`define DECLARE_OUT_CHNL(nam) \
	output wire [ASZ-1:0] nam``_src, \
	output wire [ASZ-1:0] nam``_dst, \
	output wire [DSZ-1:0] nam``_dat, \
	output wire nam``_req, \
	input wire nam``_ack, \

	
`define DECLARE_IN_CHNL(nam) \
	input wire [ASZ-1:0] nam``_src, \
	input wire [ASZ-1:0] nam``_dst, \
	input wire [DSZ-1:0] nam``_dat, \
	input wire nam``_req, \
	output wire nam``_ack, \


`define DECLARE_LINK(lnk) \
	wire [ASZ-1:0] lnk``_src; \
	wire [ASZ-1:0] lnk``_dst; \
	wire [DSZ-1:0] lnk``_dat; \
	wire lnk``_req; \
	wire lnk``_ack; \

	
`define INSTA_CHNL(chn, lnk) \
	.chn``_src(lnk``_src), \
	.chn``_dst(lnk``_dst), \
	.chn``_dat(lnk``_dat), \
	.chn``_req(lnk``_req), \
	.chn``_ack(lnk``_ack), \
	
	
//--------------------------------------------
`endif // HGLOBAL_V_FILE
