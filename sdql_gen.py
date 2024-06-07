import os
from collections import defaultdict
from typing import List, Tuple

from consts import generated_dir_path, preprocessed_data_path, raw_data_path, abbr2rel, rel_wo_idx, rel2col2type, \
	JoinMode
from var_mng import VariableManager


class SDQLGenerator:
	def __init__(self, mode: JoinMode, var_mng: VariableManager):
		self.mode = mode
		self.var_mng = var_mng
		self.save_path = os.path.join(generated_dir_path, "sdql", self.mode.value)
		self.indent = 0
		self.available_tuples = set()

	def clear(self):
		self.indent = 0
		self.available_tuples.clear()

	def call_func(self, func_name: str, *args):
		for s in getattr(self, f"_{self.mode.value}_{func_name}")(*args):
			yield s

	def generate(self, query: str, plans: List[Tuple[Tuple[str, List, List], List, List]]):
		with open(os.path.join(self.save_path, f"{query}.sdql"), "w") as sdql_file:
			for line in self._generate(query, plans):
				sdql_file.write('\t' * self.indent + line)

	def _generate(self, query: str, plans: List[Tuple[Tuple[str, List, List], List, List]]):
		for _, build_plan, _ in plans:
			for line in self._generate_loads(query, build_plan):
				yield line
		yield "\n"

		for node, build_plan, compiled_plan in plans:
			for line in self._generate_subquery(node, build_plan, compiled_plan):
				yield line
			self.indent = 0
			yield "\n"

	def _generate_loads(self, query: str, build_plan: List[Tuple[str, List[str], List[str]]]):
		for rel, _, _ in build_plan:
			if self.var_mng.is_interm_rel(rel):
				continue
			path = os.path.join(preprocessed_data_path, query, f"{rel}.csv")
			if not os.path.exists(path):
				path = os.path.join(raw_data_path, f"{abbr2rel[rel_wo_idx(rel)]}.csv")
			path = os.path.normpath(path)
			yield f'let {rel} = load[{{<{", ".join([f"{col_n}: {col_t}" for col_n, col_t in rel2col2type[rel_wo_idx(rel)].items()])}> -> int}}]("{path}")\n'

	def _generate_subquery(
			self,
			node: Tuple[str, List[Tuple[int, Tuple[str, str]]], List[int]],
			build_plan: List[Tuple[str, List[str], List[str]]],
			compiled_plan: List[List[Tuple[str, str]]]
	):
		for s in self.call_func("build_tries", build_plan, compiled_plan):
			yield s

		interm, interm_cols, interm_trie_cols = node

		if not self.var_mng.is_root_rel(interm):
			yield f"let {self.var_mng.trie_var(interm)} = "

		else_cases = list()
		for idx, eq_cols in enumerate(compiled_plan):
			rel_it, col_it = eq_cols[0]
			for s in self.call_func("attr_iteration", rel_it, col_it, idx):
				yield s

			for rel, col in eq_cols[1:]:
				yield f"let {self.var_mng.next_trie_var(rel)} = {self.var_mng.trie_var(rel)}({self.var_mng.x_var(idx)}) in\n"
				self.var_mng.next_trie_var(rel, inplace=True)

			conditions = []
			for rel, col in eq_cols[1:]:
				conditions.append(f"{self.var_mng.trie_var(rel)} != {{}}")
			yield f"if ({' && '.join(conditions)}) then\n"
			self.indent += 1
			else_cases.append(('{}', self.indent))

		if self.var_mng.is_root_rel(interm):
			interm_col2idx = {rel_col: interm_col_idx for interm_col_idx, rel_col in interm_cols}
			elems = list()
			for rel, _, proj_cols in build_plan:
				for col in proj_cols:
					for s in self.call_func("min", rel, col):
						yield s
					elems.append((self.var_mng.interm_col(interm_col2idx[(rel, col)]), self.var_mng.mn_var(rel, col)))
			yield f"<{', '.join([f'{elem_key}={elem_val}' for elem_key, elem_val in elems])}>\n"
			else_cases[-1] = (f"<{', '.join([f'{elem_key}={{}}' for elem_key, _ in elems])}>", self.indent)
		else:
			interm_rel2cols = defaultdict(list)
			for _, (rel, col) in interm_cols:
				interm_rel2cols[rel].append(col)
			for rel, cols in interm_rel2cols.items():
				for s in self.call_func("tuple_iteration", rel):
					yield s
			new2old_map = {
				self.var_mng.interm_col(idx): f"{self.var_mng.tuple_var(rel)}.{col}"
				for idx, (rel, col) in interm_cols
			}
			tuple_value = f"<{', '.join([f'{new_col}={old_col}' for new_col, old_col in new2old_map.items()])}>"
			trie_value = f"{{ {tuple_value} -> 1 }}"
			for idx in interm_trie_cols[::-1]:
				trie_value = f"{{ {new2old_map[self.var_mng.interm_col(idx)]} -> {trie_value} }}"
			yield f'{trie_value}\n'

		for else_case, indent in else_cases[::-1]:
			self.indent = indent - 1
			yield f"else\n"
			self.indent += 1
			yield f"{else_case}\n"

		if not self.var_mng.is_root_rel(interm):
			self.indent = 0
			yield f"in\n"

	def _gj_build_tries(self, build_plan, compiled_plan):
		for rel, join_cols, _ in build_plan:
			if self.var_mng.is_interm_rel(rel):
				continue
			tuple_var = self.var_mng.tuple_var(rel)
			trie_value = f"{{ {tuple_var} -> 1 }}"
			for col in join_cols[::-1]:
				trie_value = f"{{ {tuple_var}.{col} -> {trie_value} }}"
			yield f"let {self.var_mng.trie_var(rel)} = sum(<{tuple_var}, _> <- {rel}) {trie_value} in\n"

	def _fj_build_tries(self, build_plan, compiled_plan):
		rel2trie_levels = defaultdict(list)
		iter_rels = set()
		for eq_cols in compiled_plan:
			rel_it, _ = eq_cols[0]
			iter_rels.add(rel_it)
			for rel, col in eq_cols[1:]:
				if rel not in iter_rels:
					rel2trie_levels[rel].append(col)

		for rel, trie_levels in rel2trie_levels.items():
			tuple_var = self.var_mng.tuple_var(rel)
			trie_value = f"{{ {tuple_var} -> 1 }}"
			for col in trie_levels[::-1]:
				trie_value = f"{{ {tuple_var}.{col} -> {trie_value} }}"
			yield f"let {self.var_mng.trie_var(rel)} = sum(<{tuple_var}, _> <- {rel}) {trie_value} in\n"

	def _gj_attr_iteration(self, rel_it, col_it, idx):
		yield f"sum(<{self.var_mng.x_var(idx)}, {self.var_mng.next_trie_var(rel_it)}> <- {self.var_mng.trie_var(rel_it)})\n"
		self.var_mng.next_trie_var(rel_it, inplace=True)
		self.indent += 1

	def _fj_attr_iteration(self, rel_it, col_it, idx):
		if rel_it not in self.available_tuples:
			yield f"{self._tuple_iteration(rel_it)}\n"
			self.indent += 1
		yield f"let {self.var_mng.x_var(idx)} = {self.var_mng.tuple_var(rel_it)}.{col_it} in\n"
		self.available_tuples.add(rel_it)

	def _gj_min(self, rel, col):
		yield f"let {self.var_mng.mn_var(rel, col)} = {self._tuple_iteration(rel)} {self.var_mng.tuple_var(rel)}.{col} in\n"

	def _fj_min(self, rel, col):
		if rel not in self.available_tuples:
			let_value = f"{self._tuple_iteration(rel)} {self.var_mng.tuple_var(rel)}.{col}"
		else:
			let_value = f"{self.var_mng.tuple_var(rel)}.{col}"
		yield f"let {self.var_mng.mn_var(rel, col)} = {let_value} in\n"

	def _gj_tuple_iteration(self, rel):
		yield f"{self._tuple_iteration(rel)}\n"
		self.indent += 1

	def _fj_tuple_iteration(self, rel):
		if rel not in self.available_tuples:
			yield f"{self._tuple_iteration(rel)}\n"
			self.indent += 1

	def _tuple_iteration(self, rel):
		return f"sum(<{self.var_mng.tuple_var(rel)}, _> <- {self.var_mng.tuples_var(rel)})"
