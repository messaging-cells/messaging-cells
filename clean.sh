#!/bin/bash

rm -rf ./bin
rm -rf ./maker/build

rm ./send_msg_code.s
rm ./send_msg_sizes.txt

cd ./src/tests
clean.sh
cd ../..
