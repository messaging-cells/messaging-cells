#!/bin/bash

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Cleaning" $(basename $SCRIPT_DIR)

cd $SCRIPT_DIR
peg_clone/clean.sh
rm -rf src_vpp/peg_output.c
rm -rf build
cd $CURR_DIR

