#!/bin/bash

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Cleaning" $(basename $SCRIPT_DIR)

cd $SCRIPT_DIR
pulses/clean.sh
t0_fifo/clean.sh
t1_src_snk/clean.sh
t5_nd_1to2/clean.sh
t6_nd_2to1/clean.sh
t7_pakout/clean.sh
t8_pakin/clean.sh
cd $CURR_DIR

