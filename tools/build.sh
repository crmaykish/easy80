#!/bin/bash

echo "Building everything..."

mkdir -p build
cd build
cmake -G 'Unix Makefiles' ..
make -j4
cd ..