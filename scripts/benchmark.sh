#!/bin/bash

RESULTS_FILE=${1:-results/results.txt}

rm -rf generated/*.cpp
rm -rf generated/load/*.h

python3 main.py

cd generated
for cpp_file in *.cpp; do
    echo $cpp_file
    g++ $cpp_file -O3 -std=c++17
    timeout -v 120 ./a.out
    echo "--------------------"
done | tee ../$RESULTS_FILE

#cd ../../free-join && rm -rf gj/gj.json && make gj/gj.json > gj.log
