#!/bin/bash

echo "Clean fpga_tests" 

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $SCRIPT_DIR
dbg_hcell_src_snk/clean.sh
cd $CURR_DIR

