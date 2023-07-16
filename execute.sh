#! /bin/sh

if [ -f "./stdout.out" ]
then
    rm stdout.out;
fi
if [ -f "./err.out" ]
then
    rm err.out;
fi 
if [ ! -d "./build" ]
then
    mkdir build;
fi
cd build;
cmake ..;
make;
cd ..;
`build/CPMSolver >./stdout.out 2>./err.out`;