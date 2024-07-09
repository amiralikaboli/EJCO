import math
import os
from collections import defaultdict
from typing import List, Tuple

from consts import preprocessed_data_path, raw_data_path, include_dir_path, generated_cpp_path, rel_wo_idx, abbr2rel, \
	rel2col2type, inf_values, JoinMode
from var_mng import VariableManager


class CppGenerator:
	def __init__(self, mode: JoinMode, var_mng: VariableManager):
		self.trie_types = set()
		self.resolved_attrs = set()
		self.involved_cols = set()
		self.loaded_rels = set()
		self.available_tuples = set()

		self.mode = mode
		self.var_mng = var_mng
		self.save_path = os.path.join(generated_cpp_path, self.mode.value)

	def clear(self):
		self.resolved_attrs = set()
		self.involved_cols = set()
		self.loaded_rels = set()
		self.available_tuples = set()

	def call_func(self, func_name: str, *args):
		return getattr(self, f"_{self.mode.value}_{func_name}")(*args)

	def generate(self, query: str, plans: List[Tuple[Tuple[str, List, List], List, List]]):
		for idx, (node, build_plan, compiled_plan) in enumerate(plans):
			plans[idx] = (node, self._make_join_cols_order_consistent(build_plan, compiled_plan), compiled_plan)

		with open(os.path.join(self.save_path, f"{query}.cpp"), 'w') as cpp_file:
			cpp_file.write("#include <iostream>\n")
			cpp_file.write("#include <limits>\n")
			cpp_file.write(f'#include "load/{query}.h"\n')
			cpp_file.write('#include "../../../include/build.h"\n')
			cpp_file.write('#include "../../../include/high_precision_timer.h"\n\n')
			cpp_file.write('using namespace std;\n\n')
			cpp_file.write('int main() {\n')
			cpp_file.write('HighPrecisionTimer timer;\n\n')

			for _, build_plan, _ in plans:
				cpp_file.write(self._generate_load_funcs(query, build_plan))
			cpp_file.write('cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;\n')
			cpp_file.write('\n')

			cpp_file.write('for (int z = 0; z < 1 + 5; ++z) {\n')
			if self.mode == JoinMode.FJ:
				cpp_file.write(f'int {self.var_mng.cnt_var()};\n')
			cpp_file.write('timer.Reset();\n\n')

			for idx, (node, build_plan, compiled_plan) in enumerate(plans):
				cpp_file.write(self._generate_build_tries(node, build_plan, compiled_plan))
				cpp_file.write(f'timer.StoreElapsedTime({2 * idx});\n\n')

				cpp_file.write(self._generate_subquery(node, build_plan, compiled_plan))
				cpp_file.write(f'timer.StoreElapsedTime({2 * idx + 1});\n\n')

			root_build_plan = plans[-1][1]
			cpp_file.write('if (z == 0)\n')
			proj_relcols, _ = self._find_all_proj_cols_and_types(root_build_plan)
			delimiter = ' << " | " << '
			cpp_file.write(f'cout << {delimiter.join([self.var_mng.mn_rel_col_var(rel, col) for rel, col in proj_relcols])} << endl;\n')
			cpp_file.write('cout << "*" << " " << flush;\n')

			cpp_file.write('}\n')
			cpp_file.write('cout << endl;\n')
			cpp_file.write('\n')

			cpp_file.write('vector<double> tm{0};\n')
			cpp_file.write(f'for (int i = 0; i < 2 * {len(plans)}; ++i)\n')
			cpp_file.write('tm.push_back(timer.GetMean(i));\n')
			cpp_file.write(f'for (int i = 0; i < 2 * {len(plans)}; i += 2) {{\n')
			cpp_file.write(f'cout << tm[i + 1] - tm[i] << " + ";\n')
			cpp_file.write(f'cout << tm[i + 2] - tm[i + 1] << " = ";\n')
			cpp_file.write(f'cout << tm[i + 2] - tm[i] << " ms" << endl;\n')
			cpp_file.write('}\n')
			cpp_file.write(f'cout << tm[2 * {len(plans)}] << " ms" << endl;\n')

			cpp_file.write('}\n')

	def _generate_load_funcs(self, query: str, build_plan: List[Tuple[str, List[str], List[str]]]):
		content = str()
		for rel, join_cols, proj_cols in build_plan:
			if self.var_mng.is_interm_rel(rel):
				continue
			self.loaded_rels.add(rel)
			path = os.path.join(preprocessed_data_path, query, f"{rel}.csv")
			if not os.path.exists(path):
				path = os.path.join(raw_data_path, f"{abbr2rel[rel_wo_idx(rel)]}.csv")
			content += f'{self.var_mng.load_func(rel)}("{os.path.normpath(path)}");\n'
			for col in join_cols + proj_cols:
				self.involved_cols.add((rel, col))
		return content

	def _generate_build_tries(
			self,
			node: Tuple[str, List[Tuple[str, str]], List[int]],
			build_plan: List[Tuple[str, List[str], List[str]]],
			compiled_plan: List[List[Tuple[str, str]]]
	):
		interm, interm_cols, _ = node
		return self.call_func("build_tries", interm_cols, build_plan, compiled_plan)

	def _generate_subquery(
			self,
			node: Tuple[str, List[Tuple[str, str]], List[int]],
			build_plan: List[Tuple[str, List[str], List[str]]],
			compiled_plan: List[List[Tuple[str, str]]]
	):
		content = str()
		brackets = 0

		interm, interm_cols, _ = node

		if self.var_mng.is_root_rel(interm):
			proj_relcols, proj_col_types = self._find_all_proj_cols_and_types(build_plan)
			for (rel, col), col_type in zip(proj_relcols, proj_col_types):
				content += f'{col_type} {self.var_mng.mn_rel_col_var(rel, col)} = {inf_values[col_type]};\n'
		else:
			for idx, (rel, col) in interm_cols:
				content += f'vector<{rel2col2type[rel_wo_idx(rel)][col]}> {self.var_mng.rel_col_var(interm, self.var_mng.interm_col(idx))};\n'
			if self.mode == JoinMode.FJ:
				content += f'vector<int> {self.var_mng.offsets_var(interm)};\n'
			if self.mode == JoinMode.FJ:
				content += f'{self.var_mng.cnt_var()} = 0;\n'

		join_attrs_order = {rel: {col: math.inf for col in join_cols} for rel, join_cols, _ in build_plan}
		for idx, eq_cols in enumerate(compiled_plan):
			min_idx = min(idx, *[join_attrs_order[rel][col] for rel, col in eq_cols])
			for rel, col in eq_cols:
				join_attrs_order[rel][col] = min_idx
		for idx, eq_cols in enumerate(compiled_plan):
			rel_it, col_it = eq_cols[0]
			if join_attrs_order[rel_it][col_it] == idx:
				attr_iteration_content = self.call_func("attr_iteration", rel_it, col_it, idx)
				brackets += ("for" in attr_iteration_content)
				content += attr_iteration_content
				self.resolved_attrs.add(eq_cols[0])
				start_offset = 1
			elif eq_cols[0] in self.resolved_attrs:
				start_offset = 1
			else:
				start_offset = 0

			conditions = []
			for rel, col in eq_cols[start_offset:]:
				conditions.append(
					f"{self.var_mng.trie_var(rel)}.contains({self.var_mng.x_var(join_attrs_order[rel][col])})"
				)
			content += f"if ({' && '.join(conditions)}) {{\n"
			brackets += 1

			for rel, col in eq_cols[start_offset:]:
				content += f"auto &{self.var_mng.next_trie_var(rel)} = {self.var_mng.trie_var(rel)}.at({self.var_mng.x_var(join_attrs_order[rel][col])});\n"
				self.var_mng.next_trie_var(rel, inplace=True)
				self.resolved_attrs.add((rel, col))

		if self.var_mng.is_root_rel(interm):
			rel2proj_cols = {rel: proj_cols for rel, _, proj_cols in build_plan if proj_cols}
			for rel, proj_cols in rel2proj_cols.items():
				content += self.call_func("min", rel, proj_cols)
		else:
			interm_rel2cols = defaultdict(list)
			for _, (rel, col) in interm_cols:
				interm_rel2cols[rel].append(col)
			rel2col2type[interm] = dict()
			for rel, cols in interm_rel2cols.items():
				offset_iteration_content = self.call_func("offset_iteration", rel)
				brackets += ("for" in offset_iteration_content)
				content += offset_iteration_content
			for idx, (rel, col) in interm_cols:
				interm_col = self.var_mng.interm_col(idx)
				interm_col_type = rel2col2type[rel_wo_idx(rel)][col]
				rel2col2type[interm][interm_col] = interm_col_type
				content += f'{self.var_mng.rel_col_var(interm, interm_col)}.push_back({self.var_mng.rel_col_var(rel, col)}[{self.var_mng.off_var(rel)}]);\n'
			if self.mode == JoinMode.FJ:
				content += f'{self.var_mng.offsets_var(interm)}.push_back({self.var_mng.cnt_var()}++);\n'
		content += '}\n' * brackets
		return content

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
						trie_type = self.var_mng.trie_def(level_types)
					else:
						trie_type = self.var_mng.trie_def(level_types, "bool")
					cpp_file.write(
						f"void {self.var_mng.build_func()}({trie_type} &trie, "
						f"{', '.join([f'vector<{ttt}> &{self.var_mng.attr_var(idx)}' for idx, ttt in enumerate(level_types)])}){{\n"
					)
					cpp_file.write(f"for (int i = 0; i < {self.var_mng.attr_var(0)}.size(); ++i)\n")
					trie_var = f"trie{''.join(f'[{self.var_mng.attr_var(idx)}[i]]' for idx in range(len(level_types)))}"
					if is_for_proj:
						cpp_file.write(f"{trie_var}.push_back(i);\n")
					else:
						cpp_file.write(f"{trie_var} = true;\n")
					cpp_file.write(f"}}\n")

	def generate_load_file(self, query: str):
		with open(os.path.join(self.save_path, "load", f"{query}.h"), "w") as cpp_file:
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
				cpp_file.write(f'vector<int> {self.var_mng.offsets_var(rel)};\n')
				cpp_file.write(f"void {self.var_mng.load_func(rel)}(const string path) {{\n")
				cpp_file.write(f"ifstream in(path);\n")
				cpp_file.write(f"if (!in)\nthrow path;\n")
				cpp_file.write(f"string line;\n")
				cpp_file.write(f"string token;\n")
				cpp_file.write(f"int {self.var_mng.cnt_var()} = 0;\n")
				cpp_file.write(f"while (getline(in, line)) {{\n")
				cpp_file.write(f"stringstream ss(line);\n")

				for col_n, col_t in rel2col2type[rel_wo_idx(rel)].items():
					cpp_file.write(f"getline(ss, token, '|');\n")

					if col_n in rel_involved_cols:
						if col_t == "int":
							cpp_file.write(f"{self.var_mng.rel_col_var(rel, col_n)}.push_back(stoi(token));\n")
						elif col_t == "string":
							cpp_file.write(f"{self.var_mng.rel_col_var(rel, col_n)}.push_back(token);\n")
						else:
							raise ValueError(f"Unknown type: {col_t}")

					if col_n == rel_involved_cols[-1]:
						break
				cpp_file.write(f"{self.var_mng.offsets_var(rel)}.push_back({self.var_mng.cnt_var()}++);\n")

				cpp_file.write(f"}}\n")
				cpp_file.write(f"in.close();\n")
				cpp_file.write(f"}}\n")

	def _gj_build_tries(self, interm_cols, build_plan, compiled_plan):
		content = str()
		rels_in_interm_cols = set(rel for _, (rel, _) in interm_cols)
		for rel, join_cols, proj_cols in build_plan:
			content += self._build_trie(rel, join_cols, rel in rels_in_interm_cols)
		return content

	def _fj_build_tries(self, interm_cols, build_plan, compiled_plan):
		content = str()
		rel2trie_levels = defaultdict(list)
		iter_rels = set()
		for eq_cols in compiled_plan:
			rel_it, _ = eq_cols[0]
			iter_rels.add(rel_it)
			for rel, col in eq_cols[1:]:
				if rel not in iter_rels:
					rel2trie_levels[rel].append(col)

		rels_in_interm_cols = set(rel for _, (rel, _) in interm_cols)
		for rel, trie_levels in rel2trie_levels.items():
			is_vector_needed = rel in rels_in_interm_cols or rel in iter_rels
			content += self._build_trie(rel, trie_levels, is_vector_needed)
		return content

	def _build_trie(self, rel, join_cols, is_vector_needed):
		content = str()
		level_types = tuple([rel2col2type[rel_wo_idx(rel)][join_col] for join_col in join_cols])
		self.trie_types.add(level_types)
		if is_vector_needed:
			content += f"auto {self.var_mng.trie_var(rel)} = {self.var_mng.trie_def(level_types)}();\n"
		else:
			content += f"auto {self.var_mng.trie_var(rel)} = {self.var_mng.trie_def(level_types, 'bool')}();\n"
		content += f"{self.var_mng.build_func()}({self.var_mng.trie_var(rel)}, {', '.join([self.var_mng.rel_col_var(rel, join_col) for join_col in join_cols])});\n"
		return content

	def _gj_attr_iteration(self, rel_it, col_it, idx):
		content = f"for (const auto &[{self.var_mng.x_var(idx)}, {self.var_mng.next_trie_var(rel_it)}]: {self.var_mng.trie_var(rel_it)}) {{\n"
		self.var_mng.next_trie_var(rel_it, inplace=True)
		return content

	def _fj_attr_iteration(self, rel_it, col_it, idx):
		content = str()
		if rel_it not in self.available_tuples:
			content += f"{self._offset_iteration(rel_it)} {{\n"
		content += f"auto {self.var_mng.x_var(idx)} = {self.var_mng.rel_col_var(rel_it, col_it)}[{self.var_mng.off_var(rel_it)}];\n"
		self.available_tuples.add(rel_it)
		return content

	def _offset_iteration(self, rel):
		return f"for (const auto &{self.var_mng.off_var(rel)}: {self.var_mng.offsets_var(rel, it=True)})"

	def _gj_min(self, rel, proj_cols):
		content = f"{self._offset_iteration(rel)} {{\n"
		for col in proj_cols:
			content += f'{self.var_mng.mn_rel_col_var(rel, col)} = min({self.var_mng.mn_rel_col_var(rel, col)}, {self.var_mng.rel_col_var(rel, col)}[{self.var_mng.off_var(rel)}]);\n'
		content += '}\n'
		return content

	def _fj_min(self, rel, proj_cols):
		content = str()
		is_available = rel in self.available_tuples
		if not is_available:
			content += f"{self._offset_iteration(rel)} {{\n"
		for col in proj_cols:
			content += f'{self.var_mng.mn_rel_col_var(rel, col)} = min({self.var_mng.mn_rel_col_var(rel, col)}, {self.var_mng.rel_col_var(rel, col)}[{self.var_mng.off_var(rel)}]);\n'
		if not is_available:
			content += '}\n'
		return content

	def _gj_offset_iteration(self, rel):
		return f"{self._offset_iteration(rel)} {{\n"

	def _fj_offset_iteration(self, rel):
		if rel not in self.available_tuples:
			return f"{self._offset_iteration(rel)} {{\n"
		return ""
