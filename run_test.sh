#!/bin/bash

mkdir ./test/build
cd ./test/build
cmake ..
cmake --build .
ctest