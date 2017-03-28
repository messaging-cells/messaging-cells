#!/bin/bash

set -e

cd maker
make
cd ..

PROG=bin/bj-core-actor.elf

e-objdump -D $PROG > code_prog.s
e-objdump -h $PROG > sizes.txt
e-nm bin/bj-core-actor.elf | grep test_link_shd_code > bin/addr_func_test_link_shd_code.txt

rm ./bin/log*

