#!/bin/bash

set -euo pipefail

MODE=${1:-gj}
RESULTS_FILE=${2:-results/results-$MODE.txt}

python3 scripts/validation.py $RESULTS_FILE

python3 ../free-join/scripts/plot_sep.py $MODE
