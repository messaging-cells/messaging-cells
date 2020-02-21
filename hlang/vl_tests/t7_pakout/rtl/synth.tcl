# verilog_defaults -add -I./cell_src_snk/
yosys -import
read_verilog bin_to_disp.v; 
read_verilog debouncer.v; 
read_verilog pakout.v; 
read_verilog pakout_io.v; 
read_verilog test_7.v;
synth_ice40 -blif ../$::env(BUILD_DIR)/test_7.blif;
synth_ice40 -json ../$::env(BUILD_DIR)/test_7.json;
