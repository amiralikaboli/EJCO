#!/bin/bash

set -euo pipefail

rm -rf generated/*

python3 translator.py

cd generated
for cpp_file in *.cpp; do
    echo $cpp_file
    g++ $cpp_file -O3 -std=c++17 && ./a.out
    echo "--------------------"
done | tee ../results.txt

cd ../../free-join && rm -rf gj/gj.json && make gj/gj.json > /dev/null
