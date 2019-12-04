# verilog_defaults -add -I./cell_src_snk/
yosys -import
read_verilog bin_to_disp.v; 
read_verilog debouncer.v; 
read_verilog ln_1to2.v; 
read_verilog io_1to2.v; 
read_verilog test_3.v;
synth_ice40 -blif ../$::env(BUILD_DIR)/test_3.blif;
synth_ice40 -json ../$::env(BUILD_DIR)/test_3.json;
