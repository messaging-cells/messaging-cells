#!/bin/bash

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Cleaning" $(basename $SCRIPT_DIR)

cd $SCRIPT_DIR
hl_maker/hclean.sh
hl_src/hnet/clean.sh
cd $CURR_DIR

