#!/bin/bash

# set -e

cd maker
make
cd ..

cd src/tests
make
rm ./bin/log_core_*
cd ../..

cd src/ben-jose
make
rm ./bin/log_core_*
cd ../..


