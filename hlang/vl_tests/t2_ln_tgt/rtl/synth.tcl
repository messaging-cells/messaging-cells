# verilog_defaults -add -I./cell_src_snk/
yosys -import
read_verilog bin_to_disp.v; 
read_verilog debouncer.v; 
read_verilog ln_tgt.v; 
read_verilog hnet.v;
synth_ice40 -blif ../$::env(BUILD_DIR)/hnet.blif;
synth_ice40 -json ../$::env(BUILD_DIR)/hnet.json;
