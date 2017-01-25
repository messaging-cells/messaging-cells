#!/bin/bash

set -e

cd maker
make
cd ..

PROG=`ls bin/e_prog*`

e-objdump -D $PROG > code_prog.s
e-objdump -h $PROG > sizes.txt


