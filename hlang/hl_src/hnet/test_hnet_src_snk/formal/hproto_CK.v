
	always @(posedge i_clk)
	begin
		if(i_addr !== LOCAL_ADDR) begin
			assert(r_dat == 0);
		end
	end
	
	