
`default_nettype	none

module debouncer 
(	input i_Clk,
	input i_Switch,
	output o_Switch
);
 
	parameter TOT_CKS = 250000;

	reg [$clog2(TOT_CKS):0] r_Count = 0;
	reg r_State = 1'b0;
 
	always @(posedge i_Clk)
	begin
		// Switch input is different than internal switch value, so an input is
		// changing.  Increase the counter until it is stable for enough time.  
		if (i_Switch !== r_State && r_Count < TOT_CKS) begin
			r_Count <= r_Count + 1;
		end
		// End of counter reached, switch is stable, register it, reset counter
		else if (r_Count == TOT_CKS) 
		begin
			r_State <= i_Switch;
			r_Count <= 0;
		end 
		// Switches are the same state, reset the counter
		else 
		begin
			r_Count <= 0;
		end
	end
 
	// Assign internal register to output (debounced!)
	assign o_Switch = r_State;
 
endmodule

