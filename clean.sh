#!/bin/bash

echo "Messagging Cells FULL clean" 

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $SCRIPT_DIR
rm -rf ./bin
rm -rf ./tmp-build
ben-jose-embryo/bj_maker/clean.sh
cd $CURR_DIR

