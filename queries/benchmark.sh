#!/bin/bash

set -euo pipefail

g++ ours_ldbc_triangle.cpp -O3 -std=c++17 -o ours_ldbc_triangle.out

SFs=(0.1 1 3)
for SF in "${SFs[@]}"
do
    echo "SF = $SF"

    echo "Kuzu"
    python kuzu_ldbc_triangle.py $SF

    echo "###############"
    sleep 2

    echo "Ours"
    ./ours_ldbc_triangle.out $SF

    echo "------------------------------"
done