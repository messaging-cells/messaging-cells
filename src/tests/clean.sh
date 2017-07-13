#!/bin/bash

echo "Tests clean" 

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASE_DIR=$SCRIPT_DIR/../..

cd $SCRIPT_DIR
rm -rf $BASE_DIR/bin/tests
rm -rf $BASE_DIR/tmp-build/tests
cd $CURR_DIR

