#!/bin/bash

echo "Tests clean" 

rm -rf ./bin
rm -rf ./build

cd ./backtrace
clean.sh
cd ..

