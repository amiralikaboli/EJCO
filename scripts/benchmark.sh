#!/bin/bash

MODE=${1:-gj}
RESULTS_FILE=${2:-results/results-$MODE.txt}

rm -rf generated/cpp/$MODE/*.cpp
rm -rf generated/cpp/$MODE/load/*.h

python3 main.py $MODE

cd generated/cpp/$MODE
for cpp_file in *.cpp; do
    echo $cpp_file
    clang++ $cpp_file -O3 -std=c++17 -march=native -mtune=native -Wno-narrowing -ftree-vectorize
    ./a.out
    echo "--------------------"
done | tee ../../../$RESULTS_FILE

#cd ../../../../free-join && rm -rf gj/gj.json && make gj/gj.json > gj.log
