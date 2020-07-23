#!/bin/bash

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Cleaning" $(basename $SCRIPT_DIR)

cd $SCRIPT_DIR
rm -rf build
if [ -f rtl/calc_redun.json ]; then
	rm -rf rtl/calc_redun.json
	rm -rf rtl/calc_redun.svg
fi
cd $CURR_DIR


