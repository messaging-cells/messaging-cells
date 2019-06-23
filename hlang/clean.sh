#!/bin/bash

echo "Clean all hlang" 

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $SCRIPT_DIR
hl_maker/hclean.sh
hl_src/fpga_tests/clean.sh
cd $CURR_DIR

