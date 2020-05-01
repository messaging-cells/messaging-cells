#!/bin/bash

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Cleaning" $(basename $SCRIPT_DIR)

cd $SCRIPT_DIR
rm -rf gh_build
rm -f hgen_lognet
rm -f autocomplete_choices.txt
cd $CURR_DIR


