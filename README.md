# EJCO: Efficient Binary and Worst-Case Optimal Join Processing via Compilation

## Generating Intermediate Representation (IR)
To generate IR files using EJCO, use the following commands:
- For Generic Join (GJ):
```bash
python main.py gj
```
- For Free Join (FJ):
```bash
python main.py fj
```

To generate IR files with specific optimizations (e.g., O1, O2, O3, etc.) for ablation studies, include the optimization level as an argument. For example, to generate IR for FJ with O2:
```bash
python main.py fj 2
```

## Generating C++ Code
To compile IR into C++ code, we use the [SDQL code generator](https://github.com/edin-dal/sdql).
This tool has been extended in this project to support features required for EJCO. Please refer to the linked repository for setup and usage instructions.

## Running Benchmarks
To run benchmarks and reproduce the results presented in the paper, please use our dedicated benchmarking repository, [EJCO-Benchmark](https://github.com/amiralikaboli/EJCO-Benchmark).