import json
import os
from collections import defaultdict
from typing import List, Tuple

from parser import PlanParser
from var_mng import VariableManager

freejoin_path = os.path.join(os.path.dirname(__file__), "..", "free-join")
preprocessed_data_path = os.path.join(freejoin_path, "queries", "preprocessed", "join-order-benchmark", "data")
raw_data_path = os.path.join(freejoin_path, "data", "imdb_csv")
include_dir_path = os.path.join(os.path.dirname(__file__), "include")
generated_dir_path = os.path.join(os.path.dirname(__file__), "generated")


class Plan2CPPTranslator:
	def __init__(self):
		self.parser = PlanParser()
		with open("rel_abbrs.json", 'r') as json_file:
			self.rel_abbrs = json.load(json_file)
		with open("rel_col_types.json", 'r') as json_file:
			self.rel_col_types = json.load(json_file)

		self.trie_types = set()

		self.var_mng = VariableManager()
		self.resolved_attrs = set()
		self.involved_cols = set()
		self.loading_rels = set()
		self.indent = 1

	def _clear_per_query(self):
		self.var_mng = VariableManager()
		self.resolved_attrs = set()
		self.involved_cols = set()
		self.loading_rels = set()

	def translate(self, queries: List[str], use_cache: bool = False):
		for query in queries:
			self._clear_per_query()
			self._translate(query, use_cache)
			self._translate_load_files(query)

		self._translate_build_file()

	def _translate(self, query: str, use_cache: bool = False):
		build_plan, compiled_plan = self.parser.parse(query, use_cache)
		build_plan = self._make_join_cols_order_consistent(build_plan, compiled_plan)

		with open(os.path.join(generated_dir_path, f"{query}.cpp"), 'w') as cpp_file:
			cpp_file.write("#include <iostream>\n")
			cpp_file.write("#include <limits>\n")
			cpp_file.write(f'#include "load/{query}.h"\n')
			cpp_file.write('#include "../include/build.h"\n')
			cpp_file.write('#include "../include/high_precision_timer.h"\n\n')
			cpp_file.write('using namespace std;\n\n')
			cpp_file.write('int main() {\n')
			cpp_file.write('\tHighPrecisionTimer timer;\n\n')

			for line in self._translate_loads(query, build_plan):
				cpp_file.write('\t' * self.indent + line)
			cpp_file.write('\tcout << timer.GetElapsedTime() / 1000.0 << " s" << endl;\n')
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
			proj_relcols, _ = self._find_all_proj_cols_and_types(build_plan)
			delimiter = ' << " | " << '
			cpp_file.write(
				'\t' * (self.indent + 1) +
				f'cout << {delimiter.join([self.var_mng.mn_var(rel, col) for rel, col in proj_relcols])} << endl;\n'
			)
			cpp_file.write('\t' * self.indent + 'cout << "*" << " " << flush;\n')
			self.indent -= 1

			cpp_file.write('\t}\n')
			cpp_file.write('\tcout << endl;\n')
			cpp_file.write('\n')

			cpp_file.write('\tauto build_time = timer.GetMean(0);\n')
			cpp_file.write('\tauto total_time = timer.GetMean(1);\n')
			cpp_file.write('\tcout << build_time << " ms" << endl;\n')
			cpp_file.write('\tcout << total_time - build_time << " ms" << endl;\n')
			cpp_file.write('\tcout << total_time << " ms" << endl;\n')

			cpp_file.write('}\n')

	def _translate_loads(self, query: str, build_plan: List[Tuple]):
		for rel, join_cols, proj_cols in build_plan:
			self.loading_rels.add(rel)
			path = os.path.join(preprocessed_data_path, query, f"{rel}.csv")
			if not os.path.exists(path):
				path = os.path.join(raw_data_path, f"{self.rel_abbrs[self.rel_wo_idx(rel)]}.csv")
			yield f'{self.var_mng.load_func(rel)}("{os.path.normpath(path)}");\n'
			for col in join_cols + proj_cols:
				self.involved_cols.add((rel, col))

	def _translate_build_plan(self, build_plan: List[Tuple[str, List[str], List[str]]]):
		for rel, join_cols, proj_cols in build_plan:
			level_types = tuple([
				self.rel_col_types[self.rel_wo_idx(rel)][join_col][0]
				for join_col in join_cols
			])
			self.trie_types.add(level_types)
			if proj_cols:
				yield f"auto {self.var_mng.trie_var(rel)} = {self.var_mng.trie_type(level_types)}();\n"
				yield f"{self.var_mng.build_func()}({self.var_mng.trie_var(rel)}, {', '.join([self.var_mng.rel_col_var(rel, join_col) for join_col in join_cols])});\n"
			else:
				yield f"auto {self.var_mng.trie_var(rel)} = {self.var_mng.trie_bool_type(level_types)}();\n"
				yield f"{self.var_mng.build_bool_func()}({self.var_mng.trie_var(rel)}, {', '.join([self.var_mng.rel_col_var(rel, join_col) for join_col in join_cols])});\n"

	def _translate_compiled_plan(
			self, build_plan: List[Tuple[str, List[str], List[str]]], compiled_plan: List[List[str]]
	):
		join_attrs_order = self.parser.find_join_attrs_order(build_plan, compiled_plan)

		proj_relcols, proj_col_types = self._find_all_proj_cols_and_types(build_plan)
		for (rel, col), col_type in zip(proj_relcols, proj_col_types):
			inf_val = "numeric_limits<int>::max()" if col_type == "int" else '"zzzzzzzz"'
			yield f'{col_type} {self.var_mng.mn_var(rel, col)} = {inf_val};\n'

		for idx, eq_cols in enumerate(compiled_plan):
			rel_0, col_0 = eq_cols[0]
			if join_attrs_order[rel_0][col_0] == idx:
				yield f"for (const auto &[{self.var_mng.x_var(idx)}, {self.var_mng.next_trie_var(rel_0)}]: {self.var_mng.trie_var(rel_0)}) {{\n"
				self.var_mng.next_trie_var(rel_0, inplace=True)
				self.indent += 1
				self.resolved_attrs.add(eq_cols[0])
				start_offset = 1
			else:
				start_offset = 0

			conditions = []
			assignments = []
			for rel_col in eq_cols[start_offset:]:
				if rel_col in self.resolved_attrs:
					continue

				rel, col = rel_col
				conditions.append(
					f"{self.var_mng.trie_var(rel)}.contains({self.var_mng.x_var(join_attrs_order[rel][col])})"
				)
				assignments.append(
					f"auto &{self.var_mng.next_trie_var(rel)} = "
					f"{self.var_mng.trie_var(rel)}.at({self.var_mng.x_var(join_attrs_order[rel][col])});\n"
				)
				self.var_mng.next_trie_var(rel, inplace=True)
				self.resolved_attrs.add(rel_col)

			yield f"if ({' && '.join(conditions)}) {{\n"
			self.indent += 1
			for assignment in assignments:
				yield assignment

		rel2proj_cols = {rel: proj_cols for rel, _, proj_cols in build_plan if proj_cols}
		for rel, proj_cols in rel2proj_cols.items():
			yield f"for (const auto &{self.var_mng.offset_var(rel)}: {self.var_mng.trie_var(rel)}) {{\n"
			self.indent += 1
			for col in proj_cols:
				yield f'{self.var_mng.mn_var(rel, col)} = min({self.var_mng.mn_var(rel, col)}, {self.var_mng.rel_col_var(rel, col)}[{self.var_mng.offset_var(rel)}]);\n'
			self.indent -= 1
			yield '}\n'

	def _find_all_proj_cols_and_types(self, build_plan: List[Tuple[str, List[str], List[str]]]):
		relcols, col_types = [], []
		for rel, _, proj_cols in build_plan:
			for col in proj_cols:
				relcols.append((rel, col))
				col_types.append(self.rel_col_types[self.rel_wo_idx(rel)][col][0])
		return relcols, col_types

	def _make_join_cols_order_consistent(self, build_plan, compiled_plan):
		rel2join_cols = defaultdict(list)
		for eq_cols in compiled_plan:
			for rel, col in eq_cols:
				if col not in rel2join_cols[rel]:
					rel2join_cols[rel].append(col)
		return [(rel, rel2join_cols[rel], proj_cols) for rel, _, proj_cols in build_plan]

	def _translate_build_file(self):
		with open(os.path.join(include_dir_path, "build.h"), "w") as cpp_file:
			cpp_file.write('#include <iostream>\n')
			cpp_file.write('#include <vector>\n')
			cpp_file.write('#include "parallel_hashmap/phmap.h"\n\n')
			cpp_file.write('using namespace std;\n')

			for is_for_proj in [True, False]:
				for level_types in sorted(self.trie_types):
					cpp_file.write("\n")
					if is_for_proj:
						build_func = self.var_mng.build_func()
						trie_type = self.var_mng.trie_type(level_types)
					else:
						build_func = self.var_mng.build_bool_func()
						trie_type = self.var_mng.trie_bool_type(level_types)
					cpp_file.write(
						f"void {build_func}({trie_type} &trie, "
						f"{', '.join([f'vector<{ttt}> &{self.var_mng.attr_var(idx)}' for idx, ttt in enumerate(level_types)])}){{\n"
					)
					cpp_file.write(f"\tfor (int i = 0; i < {self.var_mng.attr_var(0)}.size(); ++i)\n")
					trie_var = f"trie{''.join(f'[{self.var_mng.attr_var(idx)}[i]]' for idx in range(len(level_types)))}"
					if is_for_proj:
						cpp_file.write(f"\t\t{trie_var}.push_back(i);\n")
					else:
						cpp_file.write(f"\t\t{trie_var} = true;\n")
					cpp_file.write(f"}}\n")

	def _translate_build_file_using_sort(self):
		with open(os.path.join(include_dir_path, "build.h"), "w") as cpp_file:
			cpp_file.write('#include <iostream>\n')
			cpp_file.write('#include <vector>\n')
			cpp_file.write('#include "parallel_hashmap/phmap.h"\n\n')
			cpp_file.write('using namespace std;\n')

			for level_types in sorted(self.trie_types):
				cpp_file.write("\n")
				cpp_file.write(
					f"void {self.var_mng.build_func()}({self.var_mng.trie_type(level_types)} &trie, "
					f"{', '.join([f'vector<{ttt}> &{self.var_mng.attr_var(idx)}' for idx, ttt in enumerate(level_types)])}) {{\n"
				)
				cpp_file.write(f"\tvector<int> off({self.var_mng.attr_var(0)}.size());\n")
				cpp_file.write(f"\tfor (int i = 0; i < {self.var_mng.attr_var(0)}.size(); ++i)\n")
				cpp_file.write(f"\t\toff[i] = i;\n")
				cpp_file.write(
					f"\tsort(off.begin(), off.end(), "
					f"[{', '.join([f'&{self.var_mng.attr_var(idx)}' for idx in range(len(level_types))])}](const auto &i, const auto &j) {{\n"
				)
				for idx in range(len(level_types) - 1):
					cpp_file.write(
						f"\t\tif ({self.var_mng.attr_var(idx)}[i] < {self.var_mng.attr_var(idx)}[j]) return true;\n"
					)
					cpp_file.write(
						f"\t\telse if ({self.var_mng.attr_var(idx)}[i] > {self.var_mng.attr_var(idx)}[j]) return false;\n"
					)
				cpp_file.write(
					f"\t\tif ({self.var_mng.attr_var(len(level_types) - 1)}[i] < {self.var_mng.attr_var(len(level_types) - 1)}[j]) return true;\n"
				)
				cpp_file.write(f"\t\telse return false;\n")
				cpp_file.write(f"\t}});\n")
				for idx in range(len(level_types)):
					cpp_file.write(
						f"\tauto last_{self.var_mng.attr_var(idx)} = {self.var_mng.attr_var(idx)}[off[0]];\n"
					)
				cpp_file.write(f"\tauto start_idx = 0;\n")
				cpp_file.write(f"\tfor (int i = 1; i < off.size(); ++i) {{\n")
				cpp_file.write(f"\t\tconst auto &o = off[i];\n")
				cpp_file.write(
					f"\t\tif ({' || '.join([f'{self.var_mng.attr_var(idx)}[o] != last_{self.var_mng.attr_var(idx)}' for idx in range(len(level_types))])}) {{\n"
				)
				cpp_file.write(
					f"\t\t\ttrie{''.join([f'[last_{self.var_mng.attr_var(idx)}]' for idx in range(len(level_types))])} = "
					f"vector<int>(off.begin() + start_idx, off.begin() + i);\n"
				)
				for idx in range(len(level_types)):
					cpp_file.write(f"\t\t\tlast_{self.var_mng.attr_var(idx)} = {self.var_mng.attr_var(idx)}[o];\n")
				cpp_file.write(f"\t\t\tstart_idx = i;\n")
				cpp_file.write(f"\t\t}}\n")
				cpp_file.write(f"\t}}\n")
				cpp_file.write(
					f"\ttrie{''.join([f'[last_{self.var_mng.attr_var(idx)}]' for idx in range(len(level_types))])} = "
					f"vector<int>(off.begin() + start_idx, off.end());\n"
				)
				cpp_file.write(f"}}\n")

	def _translate_load_files(self, query: str):
		with open(os.path.join(generated_dir_path, "load", f"{query}.h"), "w") as cpp_file:
			cpp_file.write('#include <iostream>\n')
			cpp_file.write('#include <fstream>\n')
			cpp_file.write('#include <sstream>\n')
			cpp_file.write('#include <vector>\n\n')
			cpp_file.write('using namespace std;\n')

			for rel in sorted(self.loading_rels):
				rel_involved_cols = [
					col
					for col, _ in self.rel_col_types[self.rel_wo_idx(rel)].items()
					if (rel, col) in self.involved_cols
				]

				cpp_file.write('\n')
				for col_n, col_t_nnull in self.rel_col_types[self.rel_wo_idx(rel)].items():
					col_t, _ = col_t_nnull
					if col_n in rel_involved_cols:
						cpp_file.write(f"vector<{col_t}> {self.var_mng.rel_col_var(rel, col_n)};\n")
				cpp_file.write("\n")
				cpp_file.write(f"void {self.var_mng.load_func(rel)}(const string path) {{\n")
				cpp_file.write(f"\tifstream in(path);\n")
				cpp_file.write(f"\tif (!in)\n\t\t throw path;\n")
				cpp_file.write(f"\tstring line;\n")
				cpp_file.write(f"\tstring token;\n")
				cpp_file.write(f"\twhile (getline(in, line)) {{\n")
				cpp_file.write(f"\t\tstringstream ss(line);\n")

				for col_n, col_t_nnull in self.rel_col_types[self.rel_wo_idx(rel)].items():
					col_t, is_not_null = col_t_nnull
					cpp_file.write(f"\t\tgetline(ss, token, '|');\n")

					if col_n in rel_involved_cols:
						if col_t == "int":
							if is_not_null:
								cpp_file.write(f"\t\t{self.var_mng.rel_col_var(rel, col_n)}.push_back(stoi(token));\n")
							else:
								cpp_file.write(
									f"\t\ttry {{ {self.var_mng.rel_col_var(rel, col_n)}.push_back(stoi(token)); }} "
									f"catch (...) {{ {self.var_mng.rel_col_var(rel, col_n)}.push_back(-1); }}\n"
								)
						elif col_t == "string":
							cpp_file.write(f"\t\t{self.var_mng.rel_col_var(rel, col_n)}.push_back(token);\n")
						else:
							raise ValueError(f"Unknown type: {col_t}")

					if col_n == rel_involved_cols[-1]:
						break

				cpp_file.write(f"\t}}\n")
				cpp_file.write(f"\tin.close();\n")
				cpp_file.write(f"}}\n")

	@staticmethod
	def rel_wo_idx(rel):
		if rel[-1].isdigit():
			return rel[:-1]
		return rel


if __name__ == '__main__':
	queries = []
	for filename in os.listdir(os.path.join(os.path.dirname(__file__), "plans", "raw")):
		queries.append(filename[:-4])

	translator = Plan2CPPTranslator()
	translator.translate(queries, use_cache=True)
