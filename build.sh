#!/bin/bash

# set -e

cd maker
make
cd ..

PROG=bin/send_msg.elf

e-objdump -D $PROG > code_prog.s
e-objdump -h $PROG > sizes.txt

rm ./bin/log*

