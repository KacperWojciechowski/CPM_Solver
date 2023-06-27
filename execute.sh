#! /bin/sh

rm stdout.out err.out;
mkdir build;
cd build;
cmake ..;
make;
cp CPMSolver ../;
cd ..;
`./CPMSolver >stdout.out 2>err.out`;
