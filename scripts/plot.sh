#!/bin/bash

set -euo pipefail

RESULTS_FILE=${1:-results/results-gj.txt}

python3 scripts/validation.py $RESULTS_FILE

python3 ../free-join/scripts/plot_sep.py
