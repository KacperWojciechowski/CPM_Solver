#!/bin/sh

mkdir build
cd build
cmake ..
make ut
cd ut_runtimes
for FILE in *;
do
    ./$FILE
done
cd ../..