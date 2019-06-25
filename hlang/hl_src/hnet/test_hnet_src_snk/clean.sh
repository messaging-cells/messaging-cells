#!/bin/bash

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Cleaning" $(basename $SCRIPT_DIR)

cd $SCRIPT_DIR
rm *.blif
rm *.bin
rm *.routed
rm *.asc
rm *.json
rm *.log
cd $CURR_DIR


