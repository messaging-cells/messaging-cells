#!/bin/bash

# set -e

cd maker
make
cd ..

cd src/tests
make
cd ../..

cd ben-jose-embryo/bj_maker
make
cd ../..


