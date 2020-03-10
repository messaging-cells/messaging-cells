# verilog_defaults -add -I./cell_src_snk/
yosys -import
read_verilog b_align.v;
synth_ice40 -top test_top -blif ../$::env(BUILD_DIR)/b_align.blif;
synth_ice40 -top test_top -json ../$::env(BUILD_DIR)/b_align.json;
