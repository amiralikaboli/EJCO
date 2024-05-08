#!/bin/bash

set -euo pipefail

python3 validation.py

python3 ../free-join/scripts/plot_sep.py
