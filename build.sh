#!/bin/bash

# set -e

cd maker
make
cd ..

cd src/tests
make
rm ./bin/log_core_*
cd ../..

PROG=src/tests/bin/send_msg_eph.elf
e-objdump -D $PROG > send_msg_code.s
e-objdump -h $PROG > send_msg_sizes.txt



