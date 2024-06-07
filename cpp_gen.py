import os
from collections import defaultdict
from typing import List, Tuple

from consts import preprocessed_data_path, raw_data_path, include_dir_path, generated_dir_path, rel_wo_idx, abbr2rel, \
	rel2col2type, inf_values
from var_mng import VariableManager


class CppGenerator:
	def __init__(self, var_mng: VariableManager):
		self.trie_types = set()
		self.involved_cols = set()
		self.loaded_rels = set()
		self.indent = 1

		self.var_mng = var_mng

	def clear(self):
		self.indent = 1
		self.involved_cols = set()
		self.loaded_rels = set()

	def generate(self, query: str, plans: List[Tuple[Tuple[str, List, List], List, List]]):
		for idx, (node, build_plan, compiled_plan) in enumerate(plans):
			plans[idx] = (node, self._make_join_cols_order_consistent(build_plan, compiled_plan), compiled_plan)

		with open(os.path.join(generated_dir_path, f"{query}.cpp"), 'w') as cpp_file:
			cpp_file.write("#include <iostream>\n")
			cpp_file.write("#include <limits>\n")
			cpp_file.write(f'#include "load/{query}.h"\n')
			cpp_file.write('#include "../include/build.h"\n')
			cpp_file.write('#include "../include/high_precision_timer.h"\n\n')
			cpp_file.write('using namespace std;\n\n')
			cpp_file.write('int main() {\n')
			cpp_file.write('\tHighPrecisionTimer timer;\n\n')

			for _, build_plan, _ in plans:
				for line in self._generate_load_funcs(query, build_plan):
					cpp_file.write('\t' * self.indent + line)
			cpp_file.write('\tcout << timer.GetElapsedTime() / 1000.0 << " s" << endl;\n')
			cpp_file.write('\n')

			cpp_file.write('\tfor (int z = 0; z < 1 + 5; ++z) {\n')
			self.indent += 1
			cpp_file.write('\t' * self.indent + 'timer.Reset();\n\n')

			for idx, (node, build_plan, compiled_plan) in enumerate(plans):
				interm_rel, _, _ = node
				for line in self._generate_build_plan(interm_rel, build_plan):
					cpp_file.write('\t' * self.indent + line)
				cpp_file.write('\t' * self.indent + f'timer.StoreElapsedTime({idx * 2});\n')
				cpp_file.write('\n')

				for line in self._generate_compiled_plan(node, build_plan, compiled_plan):
					cpp_file.write('\t' * self.indent + line)
				while self.indent > 2:
					self.indent -= 1
					cpp_file.write('\t' * self.indent + '}\n')
				cpp_file.write('\t' * self.indent + f'timer.StoreElapsedTime({idx * 2 + 1});\n')
				cpp_file.write('\n')

			root_build_plan = plans[-1][1]
			cpp_file.write('\t' * self.indent + 'if (z == 0)\n')
			proj_relcols, _ = self._find_all_proj_cols_and_types(root_build_plan)
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

			cpp_file.write('\tvector<double> tm{0};\n')
			cpp_file.write(f'\tfor (int i = 0; i < {len(plans)} * 2; ++i)\n')
			cpp_file.write('\t\ttm.push_back(timer.GetMean(i));\n')
			cpp_file.write(f'\tfor (int i = 0; i < 2 * {len(plans)}; i += 2)\n')
			cpp_file.write(
				f'\t\tcout << tm[i + 1] - tm[i] << " + " << tm[i + 2] - tm[i + 1] << " = " << tm[i + 2] - tm[i] << " ms" << endl;\n')
			cpp_file.write(f'\tcout << tm[{len(plans) * 2}] << " ms" << endl;\n')

			cpp_file.write('}\n')

	def _generate_load_funcs(self, query: str, build_plan: List[Tuple[str, List[str], List[str]]]):
		for rel, join_cols, proj_cols in build_plan:
			if self.var_mng.is_interm_rel(rel):
				continue
			self.loaded_rels.add(rel)
			path = os.path.join(preprocessed_data_path, query, f"{rel}.csv")
			if not os.path.exists(path):
				path = os.path.join(raw_data_path, f"{abbr2rel[rel_wo_idx(rel)]}.csv")
			yield f'{self.var_mng.load_func(rel)}("{os.path.normpath(path)}");\n'
			for col in join_cols + proj_cols:
				self.involved_cols.add((rel, col))

	def _generate_build_plan(self, interm_rel: str, build_plan: List[Tuple[str, List[str], List[str]]]):
		for rel, join_cols, proj_cols in build_plan:
			level_types = tuple([rel2col2type[rel_wo_idx(rel)][join_col] for join_col in join_cols])
			self.trie_types.add(level_types)
			if self.var_mng.is_interm_rel(interm_rel) or proj_cols:
				yield f"auto {self.var_mng.trie_var(rel)} = {self.var_mng.trie_def(level_types)}();\n"
				yield f"{self.var_mng.build_func()}({self.var_mng.trie_var(rel)}, {', '.join([self.var_mng.rel_col_var(rel, join_col) for join_col in join_cols])});\n"
			else:
				yield f"auto {self.var_mng.trie_var(rel)} = {self.var_mng.trie_def(level_types, 'bool')}();\n"
				yield f"{self.var_mng.build_bool_func()}({self.var_mng.trie_var(rel)}, {', '.join([self.var_mng.rel_col_var(rel, join_col) for join_col in join_cols])});\n"

	def _generate_compiled_plan(
			self,
			node: Tuple[str, List[Tuple[str, str]], List[int]],
			build_plan: List[Tuple[str, List[str], List[str]]],
			compiled_plan: List[List[Tuple[str, str]]]
	):
		interm_rel, interm_cols, _ = node

		if self.var_mng.is_root_rel(interm_rel):
			proj_relcols, proj_col_types = self._find_all_proj_cols_and_types(build_plan)
			for (rel, col), col_type in zip(proj_relcols, proj_col_types):
				yield f'{col_type} {self.var_mng.mn_var(rel, col)} = {inf_values[col_type]};\n'
		else:
			for idx, (rel, col) in interm_cols:
				yield f'vector<{rel2col2type[rel_wo_idx(rel)][col]}> {self.var_mng.rel_col_var(interm_rel, self.var_mng.interm_col(idx))};\n'

		for idx, eq_cols in enumerate(compiled_plan):
			rel_it, _ = eq_cols[0]
			yield f"for (const auto &[{self.var_mng.x_var(idx)}, {self.var_mng.next_trie_var(rel_it)}]: {self.var_mng.trie_var(rel_it)}) {{\n"
			self.var_mng.next_trie_var(rel_it, inplace=True)
			self.indent += 1

			conditions = []
			for rel, col in eq_cols[1:]:
				conditions.append(
					f"{self.var_mng.trie_var(rel)}.contains({self.var_mng.x_var(idx)})"
				)
			yield f"if ({' && '.join(conditions)}) {{\n"
			self.indent += 1

			for rel, col in eq_cols[1:]:
				yield f"auto &{self.var_mng.next_trie_var(rel)} = {self.var_mng.trie_var(rel)}.at({self.var_mng.x_var(idx)});\n"
				self.var_mng.next_trie_var(rel, inplace=True)

		if self.var_mng.is_root_rel(interm_rel):
			rel2proj_cols = {rel: proj_cols for rel, _, proj_cols in build_plan if proj_cols}
			for rel, proj_cols in rel2proj_cols.items():
				yield f"for (const auto &{self.var_mng.offset_var(rel)}: {self.var_mng.trie_var(rel)}) {{\n"
				self.indent += 1
				for col in proj_cols:
					yield f'{self.var_mng.mn_var(rel, col)} = min({self.var_mng.mn_var(rel, col)}, {self.var_mng.rel_col_var(rel, col)}[{self.var_mng.offset_var(rel)}]);\n'
				self.indent -= 1
				yield '}\n'
		else:
			interm_rel2cols = defaultdict(list)
			for _, (rel, col) in interm_cols:
				interm_rel2cols[rel].append(col)
			rel2col2type[interm_rel] = dict()
			for rel, cols in interm_rel2cols.items():
				yield f"for (const auto &{self.var_mng.offset_var(rel)}: {self.var_mng.trie_var(rel)}) {{\n"
				self.indent += 1
			for idx, (rel, col) in interm_cols:
				interm_col = self.var_mng.interm_col(idx)
				interm_col_type = rel2col2type[rel_wo_idx(rel)][col]
				rel2col2type[interm_rel][interm_col] = interm_col_type
				yield f'{self.var_mng.rel_col_var(interm_rel, interm_col)}.push_back({self.var_mng.rel_col_var(rel, col)}[{self.var_mng.offset_var(rel)}]);\n'
			for _ in range(len(interm_rel2cols)):
				self.indent -= 1
				yield '}\n'

	def _find_all_proj_cols_and_types(self, build_plan: List[Tuple[str, List[str], List[str]]]):
		relcols, col_types = [], []
		for rel, _, proj_cols in build_plan:
			for col in proj_cols:
				relcols.append((rel, col))
				col_types.append(rel2col2type[rel_wo_idx(rel)][col])
		return relcols, col_types

	def _make_join_cols_order_consistent(self, build_plan, compiled_plan):
		rel2join_cols = defaultdict(list)
		for eq_cols in compiled_plan:
			for rel, col in eq_cols:
				if col not in rel2join_cols[rel]:
					rel2join_cols[rel].append(col)
		return [(rel, rel2join_cols[rel], proj_cols) for rel, _, proj_cols in build_plan]

	def generate_build_file(self):
		with open(os.path.join(include_dir_path, "build.h"), "w") as cpp_file:
			cpp_file.write('#include <iostream>\n')
			cpp_file.write('#include <vector>\n')
			cpp_file.write(f'#include "parallel_hashmap/phmap.h"\n\n')
			cpp_file.write('using namespace std;\n')

			for is_for_proj in [True, False]:
				for level_types in sorted(self.trie_types):
					cpp_file.write("\n")
					if is_for_proj:
						build_func = self.var_mng.build_func()
						trie_type = self.var_mng.trie_def(level_types)
					else:
						build_func = self.var_mng.build_bool_func()
						trie_type = self.var_mng.trie_def(level_types, "bool")
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

	def _generate_build_file_using_sort(self):
		with open(os.path.join(include_dir_path, "build.h"), "w") as cpp_file:
			cpp_file.write('#include <iostream>\n')
			cpp_file.write('#include <vector>\n')
			cpp_file.write(f'#include "parallel_hashmap/phmap.h"\n\n')
			cpp_file.write('using namespace std;\n')

			for is_for_proj in [True, False]:
				for level_types in sorted(self.trie_types):
					cpp_file.write("\n")
					if is_for_proj:
						build_func = self.var_mng.build_func()
						trie_type = self.var_mng.trie_def(level_types)
					else:
						build_func = self.var_mng.build_bool_func()
						trie_type = self.var_mng.trie_def(level_types, "bool")
					cpp_file.write(
						f"void {build_func}({trie_type} &trie, "
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
					if is_for_proj:
						cpp_file.write(f"\tauto start_idx = 0;\n")
					cpp_file.write(f"\tfor (int i = 1; i < off.size(); ++i) {{\n")
					cpp_file.write(f"\t\tconst auto &o = off[i];\n")
					cpp_file.write(
						f"\t\tif ({' || '.join([f'{self.var_mng.attr_var(idx)}[o] != last_{self.var_mng.attr_var(idx)}' for idx in range(len(level_types))])}) {{\n"
					)
					if is_for_proj:
						action = "vector<int>(off.begin() + start_idx, off.begin() + i)"
					else:
						action = "true"
					cpp_file.write(
						f"\t\t\ttrie{''.join([f'[last_{self.var_mng.attr_var(idx)}]' for idx in range(len(level_types))])} = {action};\n"
					)
					for idx in range(len(level_types)):
						cpp_file.write(f"\t\t\tlast_{self.var_mng.attr_var(idx)} = {self.var_mng.attr_var(idx)}[o];\n")
					if is_for_proj:
						cpp_file.write(f"\t\t\tstart_idx = i;\n")
					cpp_file.write(f"\t\t}}\n")
					cpp_file.write(f"\t}}\n")
					if is_for_proj:
						action = "vector<int>(off.begin() + start_idx, off.end())"
					else:
						action = "true"
					cpp_file.write(
						f"\ttrie{''.join([f'[last_{self.var_mng.attr_var(idx)}]' for idx in range(len(level_types))])} = {action};\n"
					)
					cpp_file.write(f"}}\n")

	def generate_load_file(self, query: str):
		with open(os.path.join(generated_dir_path, "load", f"{query}.h"), "w") as cpp_file:
			cpp_file.write('#include <iostream>\n')
			cpp_file.write('#include <fstream>\n')
			cpp_file.write('#include <sstream>\n')
			cpp_file.write('#include <vector>\n\n')
			cpp_file.write('using namespace std;\n')

			for rel in sorted(self.loaded_rels):
				rel_involved_cols = [
					col
					for col, _ in rel2col2type[rel_wo_idx(rel)].items()
					if (rel, col) in self.involved_cols
				]

				cpp_file.write('\n')
				for col_n, col_t in rel2col2type[rel_wo_idx(rel)].items():
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

				for col_n, col_t in rel2col2type[rel_wo_idx(rel)].items():
					cpp_file.write(f"\t\tgetline(ss, token, '|');\n")

					if col_n in rel_involved_cols:
						if col_t == "int":
							cpp_file.write(f"\t\t{self.var_mng.rel_col_var(rel, col_n)}.push_back(stoi(token));\n")
						elif col_t == "string":
							cpp_file.write(f"\t\t{self.var_mng.rel_col_var(rel, col_n)}.push_back(token);\n")
						else:
							raise ValueError(f"Unknown type: {col_t}")

					if col_n == rel_involved_cols[-1]:
						break

				cpp_file.write(f"\t}}\n")
				cpp_file.write(f"\tin.close();\n")
				cpp_file.write(f"}}\n")
