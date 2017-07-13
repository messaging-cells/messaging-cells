#!/bin/bash

echo "Ben Jose clean" 

CURR_DIR=$(pwd)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASE_DIR=$SCRIPT_DIR/../..

cd $SCRIPT_DIR
rm -rf $BASE_DIR/bin/ben-jose
rm -rf $BASE_DIR/tmp-build/ben-jose
cd $CURR_DIR

