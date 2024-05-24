import itertools
import json
import os
from typing import List

from consts import preprocessed_data_path, raw_data_path, abbr2rel, rel_wo_idx, perm2str
from var_mng import VariableManager as Vm

root_path = os.path.join(os.path.dirname(__file__))
plans_path = os.path.join(root_path, "plans", "fused")

cpp_filename = "tmp.cpp"
stats_file = "results/stats.json"


def cpp_generator(query: str, rel: str, join_cols: List[str]):
	with open(cpp_filename, "w") as cpp_file:
		cpp_file.write(f'#include "generated/load/{query}.h"\n')
		cpp_file.write('#include "include/build_stats.h"\n\n')
		cpp_file.write('using namespace std;\n\n')
		cpp_file.write('int main() {\n')

		data_path = os.path.join(preprocessed_data_path, query, f"{rel}.csv")
		if not os.path.exists(data_path):
			data_path = os.path.join(raw_data_path, f"{abbr2rel[rel_wo_idx(rel)]}.csv")
		cpp_file.write(f'\t{Vm.load_func(rel)}("{os.path.normpath(data_path)}");\n')

		for perm in itertools.permutations(join_cols):
			cpp_file.write(f'\tcout << "{perm2str(perm)}" << ": ";\n')
			cpp_file.write(f'\tcalc_stats({", ".join([Vm.rel_col_var(rel, col) for col in perm])});\n')
		cpp_file.write('\n')

		cpp_file.write('}\n')

	return cpp_filename


if __name__ == '__main__':
	total_stats = dict()

	for filename in sorted(os.listdir(plans_path)):
		if not filename.endswith(".log"):
			continue

		query = filename[:-4]
		print(query)
		with open(os.path.join(plans_path, filename), "r") as txt_file:
			build_plan = eval(txt_file.readline().strip())

		query_stats = dict()
		for rel, join_cols, _ in build_plan:
			cpp_filename = cpp_generator(query, rel, join_cols)
			res = os.popen(f"g++ {cpp_filename} -O3 -std=c++17 && ./a.out").read().strip()
			rel_stats = dict()
			for line in res.split("\n"):
				perm, stats = line.split(":")
				perm = perm.strip().split(", ")
				stats = [[int(x) for x in op_stats.strip().split(" ")] for op_stats in stats.strip().split(" | ")]
				rel_stats[perm2str(perm)] = {"avg": stats[0], "max": stats[1]}
			query_stats[rel] = rel_stats

		total_stats[query] = query_stats
		with open(stats_file, "w") as json_file:
			json.dump(total_stats, json_file, indent=2)

	os.remove(cpp_filename)
