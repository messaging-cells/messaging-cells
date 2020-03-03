
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
`define NS_REDUN_SIZE 3 // MUST BE LESS THAN the full message size ((NS_ADDRESS_SIZE * 2) + NS_DATA_SIZE) 

`define NS_PACKET_SIZE 3 // MUST BE LESS THAN the full message size ((NS_ADDRESS_SIZE * 2) + NS_DATA_SIZE) 

`define NS_MESSAGE_FIFO_SIZE 2  // 1, 2 or 4 ***ONLY***

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


`define NS_FULL_MSG_SZ  (ASZ + ASZ + DSZ + RSZ)


`define NS_DECLARE_REG_MSG(mg) \
	reg [ASZ-1:0] mg``_src = 0; \
	reg [ASZ-1:0] mg``_dst = 0; \
	reg [DSZ-1:0] mg``_dat = 0; \
	reg [RSZ-1:0] mg``_red = 0; \


`define NS_DECLARE_IN_MSG(mg) \
	input wire [ASZ-1:0] mg``_src, \
	input wire [ASZ-1:0] mg``_dst, \
	input wire [DSZ-1:0] mg``_dat, \
	input wire [RSZ-1:0] mg``_red, \


`define NS_DECLARE_OUT_MSG(mg) \
	output wire [ASZ-1:0] mg``_src, \
	output wire [ASZ-1:0] mg``_dst, \
	output wire [DSZ-1:0] mg``_dat, \
	output wire [RSZ-1:0] mg``_red, \


`define NS_ASSIGN_OUT_MSG(ou, mg) \
	assign ou``_src = mg``_src; \
	assign ou``_dst = mg``_dst; \
	assign ou``_dat = mg``_dat; \
	assign ou``_red = mg``_red; \


`define NS_DECLARE_OUT_CHNL(nam) \
	`NS_DECLARE_OUT_MSG(nam) \
	output wire nam``_req, \
	input wire nam``_ack, 


`define NS_DECLARE_IN_CHNL(nam) \
	`NS_DECLARE_IN_MSG(nam) \
	input wire nam``_req, \
	output wire nam``_ack, 


`define NS_DECLARE_LINK(lnk) \
	wire [ASZ-1:0] lnk``_src; \
	wire [ASZ-1:0] lnk``_dst; \
	wire [DSZ-1:0] lnk``_dat; \
	wire [RSZ-1:0] lnk``_red; \
	wire lnk``_req; \
	wire lnk``_ack; 

	
`define NS_INSTA_CHNL(chn, lnk) \
	.chn``_src(lnk``_src), \
	.chn``_dst(lnk``_dst), \
	.chn``_dat(lnk``_dat), \
	.chn``_red(lnk``_red), \
	.chn``_req(lnk``_req), \
	.chn``_ack(lnk``_ack), 

	
`define NS_REG_MSG_INIT(mg) \
	mg``_src <= 0; \
	mg``_dst <= 0; \
	mg``_dat <= 0; \
	mg``_red <= 0; \


// ASZ + ASZ + DSZ
`define NS_MG_SRC_SECTION  ((ASZ + ASZ + DSZ + RSZ)-1):(ASZ + DSZ + RSZ)
`define NS_MG_DST_SECTION  ((ASZ + DSZ + RSZ)-1):(DSZ + RSZ)
`define NS_MG_DAT_SECTION  ((DSZ + RSZ)-1):RSZ
`define NS_MG_RED_SECTION  (RSZ-1):0

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



`define NS_GET_SEQ_MSG(chn) {chn``_src, chn``_dst, chn``_dat, chn``_red}


`define NS_FIFO_SET_IDX(chn, fif, idx) fif``_data[idx] <= `NS_GET_SEQ_MSG(chn);

/*
`define NS_FIFO_SET_IDX(chn, fif, idx) \
	fif``_data[idx][`NS_MG_SRC_SECTION] <= chn``_src; \
	fif``_data[idx][`NS_MG_DST_SECTION] <= chn``_dst; \
	fif``_data[idx][`NS_MG_DAT_SECTION] <= chn``_dat; \

*/

`define NS_FIFO_GET_IDX(chn, fif, idx) \
	chn``_src <= fif``_data[idx][`NS_MG_SRC_SECTION]; \
	chn``_dst <= fif``_data[idx][`NS_MG_DST_SECTION]; \
	chn``_dat <= fif``_data[idx][`NS_MG_DAT_SECTION]; \
	chn``_red <= fif``_data[idx][`NS_MG_RED_SECTION]; \
	

`define NS_INC_IDX(idx, the_sz) \
	if(idx == (the_sz-1)) begin \
		idx <= 0; \
	end else begin \
		idx <= idx + 1; \
	end 


`define NS_TRY_INC_HEAD(fif, mg_in, the_ack) \
	if(! fif``_busy[fif``_hd_idx]) begin \
		fif``_busy[fif``_hd_idx] <= `NS_ON; \
		`NS_FIFO_SET_IDX(mg_in, fif, fif``_hd_idx); \
		`NS_INC_IDX(fif``_hd_idx, FSZ); \
		the_ack <= `NS_ON; \
	end 


/*
`define NS_TRY_INC_TAIL(fif, mg_out, the_out_ack, the_req) \
	if(fif``_busy[fif``_tl_idx]) begin \
		if(! the_req && ! the_out_ack) begin \
			fif``_busy[fif``_tl_idx] <= `NS_OFF; \
			`NS_FIFO_GET_IDX(mg_out, fif, fif``_tl_idx); \
			`NS_INC_IDX(fif``_tl_idx); \
			the_req <= `NS_ON; \
		end \
	end 
*/


`define NS_TRY_SET_OUT(fif, mg_out, the_out_ack, the_req, out_is_busy) \
	if(fif``_busy[fif``_tl_idx] && ! out_is_busy) begin \
		fif``_busy[fif``_tl_idx] <= `NS_OFF; \
		out_is_busy <= `NS_ON; \
		`NS_FIFO_GET_IDX(mg_out, fif, fif``_tl_idx); \
		`NS_INC_IDX(fif``_tl_idx); \
	end \
	if(! the_req && ! the_out_ack && out_is_busy) begin \
		the_req <= `NS_ON; \
	end \
	if(the_req && the_out_ack) begin \
		if(out_is_busy) begin \
			out_is_busy <= `NS_OFF; \
		end \
		the_req <= `NS_OFF; \
	end


`define NS_TOT_PACKETS ((`NS_FULL_MSG_SZ / PSZ) + 1)


`define NS_DECLARE_REG_PAKOUT(pks) \
	integer pks``ii=0; \
	reg [0:0] pks``_busy = 0; \
	reg [PSZ-1:0] pks``_packets[`NS_TOT_PACKETS-1:0]; \
	reg [$clog2(`NS_TOT_PACKETS):0] pks``_pks_idx = 0; \
	reg [0:0] pks``_out_busy = 0; \
	reg [PSZ-1:0] pks``_out_pak = 0;


`define NS_DECLARE_PAKOUT_CHNL(nam) \
	output wire [PSZ-1:0] nam``_out_pak, \
	output wire nam``_req, \
	input wire nam``_ack, 


`define NS_DECLARE_PAKIN_CHNL(nam) \
	input wire [PSZ-1:0] nam``_out_pak, \
	input wire nam``_req, \
	output wire nam``_ack, 


`define NS_DECLARE_PKA_LINK(lnk) \
	wire [PSZ-1:0] lnk``_out_pak; \
	wire lnk``_req; \
	wire lnk``_ack; 


`define NS_INSTA_PAK_CHNL(chn, lnk) \
	.chn``_out_pak(lnk``_out_pak), \
	.chn``_req(lnk``_req), \
	.chn``_ack(lnk``_ack), 


`define NS_PACKETS_INIT(pks) \
	pks``_busy = 0; \
	for(pks``ii = 0; pks``ii < `NS_TOT_PACKETS; pks``ii = pks``ii+1) begin \
		pks``_packets[pks``ii] <= 0; \
	end \
	pks``_pks_idx <= 0; \
	pks``_out_busy = 0; \
	pks``_out_pak <= 0;


`define NS_MG_PAK(ii) (((ii+1)*PSZ)-1):(ii*PSZ)

`define NS_MG_LST_PAK (`NS_FULL_MSG_SZ-1):((`NS_TOT_PACKETS-1)*PSZ)

`define NS_FIFO_GET_IDX_PAKS(pks, fif, idx) \
	for(pks``ii = 0; pks``ii < `NS_TOT_PACKETS-1; pks``ii = pks``ii+1) begin \
		pks``_packets[pks``ii] <= fif``_data[idx][`NS_MG_PAK(pks``ii)]; \
	end \
	if((`NS_FULL_MSG_SZ % PSZ) > 0) begin \
		pks``_packets[`NS_TOT_PACKETS-1][(`NS_FULL_MSG_SZ % PSZ)-1:0] <= fif``_data[idx][`NS_MG_LST_PAK]; \
	end else begin \
		pks``_packets[`NS_TOT_PACKETS-1] <= 0; \
	end


`define NS_FIFO_SET_IDX_PAKS(in, fif, idx) \
	for(in``ii = 0; in``ii < `NS_TOT_PACKETS-1; in``ii = in``ii+1) begin \
		fif``_data[idx][`NS_MG_PAK(in``ii)] <= in``_packets[in``ii]; \
	end \
	if((`NS_FULL_MSG_SZ % PSZ) > 0) begin \
		fif``_data[idx][`NS_MG_LST_PAK] <= in``_packets[`NS_TOT_PACKETS-1][(`NS_FULL_MSG_SZ % PSZ)-1:0]; \
	end


`define NS_FIFO_TRY_INC_TAIL_PAKS(fif, pks) \
	if(fif``_busy[fif``_tl_idx] && ! pks``_busy) begin \
		fif``_busy[fif``_tl_idx] <= `NS_OFF; \
		`NS_FIFO_GET_IDX_PAKS(pks, fif, fif``_tl_idx); \
		`NS_INC_IDX(fif``_tl_idx, FSZ); \
		pks``_busy <= `NS_ON; \
	end 


`define NS_PACKETS_TRY_INC_TAIL(pks, the_out_ack, the_req) \
	if(pks``_busy) begin \
		if(! pks``_out_busy) begin \
			pks``_out_busy <= `NS_ON; \
			pks``_out_pak <= pks``_packets[pks``_pks_idx]; \
			`NS_INC_IDX(pks``_pks_idx, `NS_TOT_PACKETS); \
		end \
		if(! the_req && ! the_out_ack && pks``_out_busy) begin \
			the_req <= `NS_ON; \
		end \
		if(the_req && the_out_ack) begin \
			if(pks``_out_busy) begin \
				pks``_out_busy <= `NS_OFF; \
				if(pks``_pks_idx == 0) begin \
					pks``_busy <= `NS_OFF; \
				end \
			end \
			the_req <= `NS_OFF; \
		end \
	end 

/*
`define NS_TOT_CHECK_PARTS ((`NS_FULL_MSG_SZ / CKSZ) + 1)

`define NS_MG_CHECK_PART(ii) (((ii+1)*CKSZ)-1):(ii*CKSZ)

`define NS_CALC_CHECK_BITS(mg, fif, idx) \
	for(pks``ii = 0; pks``ii < `NS_TOT_PACKETS-1; pks``ii = pks``ii+1) begin \
		pks``_packets[pks``ii] <= fif``_data[idx][`NS_MG_PAK(pks``ii)]; \
	end \
	pks``_packets[pks``ii][(`NS_FULL_MSG_SZ % CKSZ):0] <= fif``_data[idx][`NS_MG_LST_PAK];
*/


//--------------------------------------------
`endif // HGLOBAL_V_FILE