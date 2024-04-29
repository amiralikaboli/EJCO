import json
import os
from typing import List, Tuple, Dict

from parser import PlanParser
from var_mng import VariableManager

freejoin_path = os.path.join(os.path.dirname(__file__), "..", "free-join")
preprocessed_data_path = os.path.join(freejoin_path, "queries", "preprocessed", "join-order-benchmark", "data")
raw_data_path = os.path.join(freejoin_path, "data", "imdb_csv")
include_dir_path = os.path.join(os.path.dirname(__file__), "include")


class Plan2CPPTranslator:
	def __init__(self):
		self.parser = PlanParser()
		with open("rel_abbrs.json", 'r') as json_file:
			self.rel_abbrs = json.load(json_file)
		with open("rel_col_types.json", 'r') as json_file:
			self.rel_col_types = json.load(json_file)

		self.trie_types = set()
		self.loading_rels = set()

		self.var_mng = VariableManager()
		self.indent = 1

	def translate(self, queries: List[str]):
		for query in queries:
			self.var_mng = VariableManager()
			self._translate(query)

		self._translate_includes()

	def _translate(self, query: str):
		build_plan, compiled_plan = self.parser.parse(query)

		with open(f"generated/{query}.cpp", 'w') as cpp_file:
			cpp_file.write("#include <iostream>\n")
			cpp_file.write('#include "../../include/load.h"\n')
			cpp_file.write('#include "../../include/build.h"\n')
			cpp_file.write('#include "../../include/high_precision_timer.h"\n\n')
			cpp_file.write('using namespace std;\n\n')
			cpp_file.write('int main() {\n')
			cpp_file.write('\tHighPrecisionTimer timer;\n\n')

			for line in self._translate_loads(query, build_plan):
				cpp_file.write('\t' * self.indent + line)
			cpp_file.write('\n')

			cpp_file.write('\tfor (int z = 0; z < 1 + 5; ++z) {\n')
			self.indent += 1
			cpp_file.write('\t' * self.indent + 'timer.Reset();\n\n')
			for line in self._translate_build_plan(build_plan):
				cpp_file.write('\t' * self.indent + line)
			cpp_file.write('\t' * self.indent + 'timer.StoreElapsedTime(0);\n')
			cpp_file.write('\n')

			for line in self._translate_compiled_plan(build_plan, compiled_plan):
				cpp_file.write('\t' * self.indent + line)

			while self.indent > 2:
				self.indent -= 1
				cpp_file.write('\t' * self.indent + '}\n')

			cpp_file.write('\t' * self.indent + 'timer.StoreElapsedTime(1);\n')
			cpp_file.write('\t' * self.indent + 'if (z == 0)\n')
			cpp_file.write('\t' * (self.indent + 1) + f'cout << {self.var_mng.res_var()}.size() << endl;\n')
			self.indent -= 1

			cpp_file.write('\t}\n')
			cpp_file.write('\n')

			cpp_file.write('\tcout << timer.GetMean(0) << " ms" << endl;\n')
			cpp_file.write('\tcout << timer.GetMean(1) << " ms" << endl;\n')

			cpp_file.write('}\n')

	def _translate_loads(self, query: str, build_plan: List[Tuple]):
		for rel_name, join_cols, proj_cols in build_plan:
			self.loading_rels.add(rel_name)
			path = os.path.join(preprocessed_data_path, query, f"{rel_name}.csv")
			if not os.path.exists(path):
				path = os.path.join(
					raw_data_path, f"{self.rel_abbrs[rel_name[:-1] if rel_name[-1].isdigit() else rel_name]}.csv"
				)
			yield f'load_{rel_name}("{os.path.normpath(path)}");\n'

	def _translate_build_plan(self, build_plan: List[Tuple]):
		for rel_name, join_cols, proj_cols in build_plan:
			level_types = tuple([
				self.rel_col_types[rel_name[:-1] if rel_name[-1].isdigit() else rel_name][join_col]
				for join_col in join_cols
			])
			self.trie_types.add(level_types)
			yield f"auto {self.var_mng.trie_var(rel_name)} = {self.var_mng.trie_type(level_types)}();\n"

			yield f"build_trie({self.var_mng.trie_var(rel_name)}, {', '.join([self.var_mng.rel_col_var(rel_name, join_col) for join_col in join_cols])});\n"

	def _translate_compiled_plan(self, build_plan: List[Tuple], compiled_plan: List[List[str]]):
		build_plan = self.parser.add_join_idx_to_build_plan(build_plan, compiled_plan)

		col_types, res_attrs = self._find_res_types_and_attrs(build_plan)
		yield f"vector<tuple<{', '.join(col_types)}>> {self.var_mng.res_var()};\n"

		for idx, eq_cols in enumerate(compiled_plan):
			rel_it = eq_cols[0][0]
			yield f"for (const auto &[{self.var_mng.x_var(idx)}, {self.var_mng.next_trie_var(rel_it)}]: {self.var_mng.trie_var(rel_it)}) {{\n"
			self.var_mng.next_trie_var(rel_it, inplace=True)
			self.indent += 1

			conditions = []
			assignments = []
			for rel, _ in eq_cols[1:]:
				conditions.append(f"{self.var_mng.trie_var(rel)}.contains({self.var_mng.x_var(idx)})")
				assignments.append(
					f"auto &{self.var_mng.next_trie_var(rel)} = {self.var_mng.trie_var(rel)}.at({self.var_mng.x_var(idx)});\n"
				)
				self.var_mng.next_trie_var(rel, inplace=True)

			yield f"if ({' && '.join(conditions)}) {{\n"
			self.indent += 1
			for assignment in assignments:
				yield assignment

		for rel, _ in build_plan.items():
			yield f"for (const auto &{self.var_mng.offset_var(rel)}: {self.var_mng.trie_var(rel)}) {{\n"
			self.indent += 1

		yield f"{self.var_mng.res_var()}.push_back({{{', '.join(res_attrs)}}});\n"

	def _find_res_types_and_attrs(self, build_plan: Dict[str, Tuple[List[Tuple[str, int]], List[str]]]):
		col_types = []
		res_attrs = []
		last_join_idx = -1
		for rel, cols in build_plan.items():
			for col, idx in cols[0]:
				if last_join_idx < idx:
					col_types.append(self.rel_col_types[rel][col])
					res_attrs.append(self.var_mng.x_var(idx))
					last_join_idx = idx
			for col in cols[1]:
				col_types.append(self.rel_col_types[rel[:-1] if rel[-1].isdigit() else rel][col])
				res_attrs.append(f"{self.var_mng.rel_col_var(rel, col)}[{self.var_mng.offset_var(rel)}]")
		return col_types, res_attrs

	def _translate_includes(self):
		with open(os.path.join(include_dir_path, "build.h"), "w") as cpp_file:
			cpp_file.write('#include <iostream>\n')
			cpp_file.write('#include <vector>\n')
			cpp_file.write('#include "parallel_hashmap/phmap.h"\n\n')
			cpp_file.write('using namespace std;\n')

			for level_types in sorted(self.trie_types):
				cpp_file.write("\n")
				cpp_file.write(
					f"void build_trie({self.var_mng.trie_type(level_types)} &trie, "
					f"{', '.join([f'vector<{ttt}> &vec{idx}' for idx, ttt in enumerate(level_types)])}){{\n"
				)

				cpp_file.write(f"\tfor (int i = 0; i < vec0.size(); ++i)\n")
				cpp_file.write(
					f"\t\ttrie{''.join(f'[vec{idx}[i]]' for idx in range(len(level_types)))}.push_back(i);\n")
				cpp_file.write(f"}}\n")

		with open(os.path.join(include_dir_path, "load.h"), "w") as cpp_file:
			cpp_file.write('#include <iostream>\n')
			cpp_file.write('#include <fstream>\n')
			cpp_file.write('#include <sstream>\n')
			cpp_file.write('#include <vector>\n\n')
			cpp_file.write('using namespace std;\n')

			for rel in sorted(self.loading_rels):
				cpp_file.write('\n')
				for col_n, col_t in self.rel_col_types[rel[:-1] if rel[-1].isdigit() else rel].items():
					cpp_file.write(f"vector<{col_t}> {self.var_mng.rel_col_var(rel, col_n)};\n")
				cpp_file.write("\n")
				cpp_file.write(f"void load_{rel}(const string path) {{\n")
				cpp_file.write(f"\tifstream in(path);\n")
				cpp_file.write(f"\tif (!in)\n\t\t throw path;\n")
				cpp_file.write(f"\tstring line;\n")
				cpp_file.write(f"\tstring token;\n")
				cpp_file.write(f"\twhile (getline(in, line)) {{\n")
				cpp_file.write(f"\t\tstringstream ss(line);\n")
				for col_n, col_t in self.rel_col_types[rel[:-1] if rel[-1].isdigit() else rel].items():
					cpp_file.write(f"\t\tgetline(ss, token, '|');\n")
					if col_t == "int":
						cpp_file.write(
							f"\t\ttry {{ {self.var_mng.rel_col_var(rel, col_n)}.push_back(stoi(token)); }} "
							f"catch (...) {{ {self.var_mng.rel_col_var(rel, col_n)}.push_back(-1); }}\n"
						)
					elif col_t == "string":
						cpp_file.write(f"\t\t{self.var_mng.rel_col_var(rel, col_n)}.push_back(token);\n")
					else:
						raise ValueError(f"Unknown type: {col_t}")
				cpp_file.write(f"\t}}\n")
				cpp_file.write(f"\tin.close();\n")
				cpp_file.write(f"}}\n")


if __name__ == '__main__':
	queries = []
	for filename in os.listdir(os.path.join(os.path.dirname(__file__), "plans", "raw")):
		if int(filename[:-5]) in [1, 2, 3, 4, 5, 11, 12, 13, 14, 21, 32]:
			queries.append(filename[:-4])

	translator = Plan2CPPTranslator()
	translator.translate(queries)
