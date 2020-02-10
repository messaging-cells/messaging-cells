#!/bin/bash

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Cleaning" $(basename $SCRIPT_DIR)

cd $SCRIPT_DIR
t1_src-snk/clean.sh
t2_ln_tgt/clean.sh
t3_ln_1to2/clean.sh
t4_ln_2to1/clean.sh
t5_nd_1to2/clean.sh
cd $CURR_DIR

