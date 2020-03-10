# verilog_defaults -add -I./cell_src_snk/
yosys -import
read_verilog bin_to_disp.v; 
read_verilog debouncer.v; 
read_verilog pakout.v; 
read_verilog pakout_io.v; 
read_verilog b_fifo.v;
synth_ice40 -top test_top -blif ../$::env(BUILD_DIR)/b_fifo.blif;
synth_ice40 -top test_top -json ../$::env(BUILD_DIR)/b_fifo.json;
