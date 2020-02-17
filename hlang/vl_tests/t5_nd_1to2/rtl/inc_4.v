
`default_nettype	none

module inc_4
  (input  i_Clk,      // Main Clock (25 MHz)
   input  [3:0] i_Binary_Num, 
   output [3:0] o_Binary_Num, 
   );

   reg [3:0] inc_num = 4'b0000;
   
	always @(posedge i_Clk)
	begin
		case (i_Binary_Num)
		4'b0000: inc_num <= 4'b0001;
		4'b0001: inc_num <= 4'b0010;
		4'b0010: inc_num <= 4'b0011;
		4'b0011: inc_num <= 4'b0100;
		4'b0100: inc_num <= 4'b0101;
		4'b0101: inc_num <= 4'b0110;
		4'b0110: inc_num <= 4'b0111;
		4'b0111: inc_num <= 4'b1000;
		4'b1000: inc_num <= 4'b1001;
		4'b1001: inc_num <= 4'b1010;
		4'b1010: inc_num <= 4'b1011;
		4'b1011: inc_num <= 4'b1100;
		4'b1100: inc_num <= 4'b1101;
		4'b1101: inc_num <= 4'b1110;
		4'b1110: inc_num <= 4'b1111;
		4'b1111: inc_num <= 4'b0000;
		endcase
	end   

  assign o_Binary_Num = inc_num;
   
endmodule
	
	
