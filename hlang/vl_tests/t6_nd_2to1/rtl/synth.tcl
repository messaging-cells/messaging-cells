# verilog_defaults -add -I./cell_src_snk/
yosys -import
read_verilog bin_to_disp.v; 
read_verilog debouncer.v; 
read_verilog nd_2to1.v; 
read_verilog io_2to1.v; 
read_verilog test_6.v;
synth_ice40 -blif ../$::env(BUILD_DIR)/test_6.blif;
synth_ice40 -json ../$::env(BUILD_DIR)/test_6.json;
