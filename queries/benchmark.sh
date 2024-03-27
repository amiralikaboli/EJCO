#!/bin/bash

set -e

echo "Kuzu: "
python kuzu_ldbc_triangle.py

echo "###############"
sleep 5

echo "Ours: "
g++ ours_ldbc_triangle.cpp -O3 -std=c++17 && ./a.out
