#!/bin/bash

# set -e

cd maker
make
cd ..

cd src/tests
make
cd ../..

cd src/ben-jose
make
cd ../..


