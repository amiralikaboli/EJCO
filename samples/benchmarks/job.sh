#!/bin/bash

set -euo pipefail

g++ ../queries/ours_job_star.cpp -O3 -std=c++17 -o ours_job_star.out && ./ours_job_star.out

echo "-------------------------------------------"
sleep 2

cd ../../free-join && rm -rf gj/gj.json && make gj/gj.json > /dev/null && python3 ./scripts/mean.py
