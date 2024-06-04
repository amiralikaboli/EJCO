import math
import os.path
from collections import defaultdict
from typing import List, Tuple, Dict

from consts import generated_dir_path

from var_mng import VariableManager


class SDQLGenerator:
	def __init__(self, var_mng: VariableManager):
		self.var_mng = var_mng
		self.indent = 0
		self.resolved_attrs = set()

	def clear(self):
		self.indent = 0
		self.resolved_attrs = set()

	def generate(self, query: str, plans: List[Tuple[Tuple[str, List], List, List]]):
		with open(os.path.join(generated_dir_path, "sdql", f"{query}.sdql"), "w") as sdql_file:
			for node, build_plan, compiled_plan in plans:
				for line in self._generate_node(node, build_plan, compiled_plan):
					sdql_file.write('\t' * self.indent + line)
				sdql_file.write("\n")
				self.indent = 0

	def _generate_node(
			self,
			node: Tuple[str, List[Tuple[int, Tuple[str, str]]]],
			build_plan: List[Tuple[str, List[str], List[str]]],
			compiled_plan: List[List[Tuple[str, str]]]
	):
		interm_rel, interm_cols = node

		if not self.var_mng.is_root_rel(interm_rel):
			yield f"let {self.var_mng.trie_var(interm_rel)} = "

		else_cases = list()
		join_attrs_order = self._order_join_cols_based_on_compiled_plan(build_plan, compiled_plan)
		for idx, eq_cols in enumerate(compiled_plan):
			rel_0, col_0 = eq_cols[0]
			if join_attrs_order[rel_0][col_0] == idx:
				self.var_mng.trie_var(rel_0)
				yield f"sum(<{self.var_mng.x_var(idx)}, {self.var_mng.next_trie_var(rel_0)}> <- {self.var_mng.trie_var(rel_0)})\n"
				self.var_mng.next_trie_var(rel_0, inplace=True)
				self.indent += 1
				self.resolved_attrs.add(eq_cols[0])
				start_offset = 1
			elif eq_cols[0] in self.resolved_attrs:
				start_offset = 1
			else:
				start_offset = 0

			for rel, col in eq_cols[start_offset:]:
				self.var_mng.trie_var(rel)
				yield f"let {self.var_mng.next_trie_var(rel)} = {self.var_mng.trie_var(rel)}({self.var_mng.x_var(join_attrs_order[rel][col])}) in\n"
				self.var_mng.next_trie_var(rel, inplace=True)
				self.resolved_attrs.add((rel, col))

			conditions = []
			for rel, col in eq_cols[start_offset:]:
				conditions.append(f"{self.var_mng.trie_var(rel)} != {{}}")
			yield f"if ({' && '.join(conditions)}) then\n"
			self.indent += 1
			else_cases.append(('{}', self.indent))

		if self.var_mng.is_root_rel(interm_rel):
			interm_col2idx = {rel_col: interm_col_idx for interm_col_idx, rel_col in interm_cols}
			elems = list()
			for rel, _, proj_cols in build_plan:
				for col in proj_cols:
					yield f"let {self.var_mng.mn_var(rel, col)} = sum(<{self.var_mng.offset_var(rel)}, _> <- {self.var_mng.trie_var(rel)}) {{ {self.var_mng.rel_col_var(rel, col)}({self.var_mng.offset_var(rel)}) -> true }} in\n"
					elems.append((self.var_mng.interm_col(interm_col2idx[(rel, col)]), self.var_mng.mn_var(rel, col)))
			yield f"<{', '.join([f'{elem_key}={elem_val}' for elem_key, elem_val in elems])}>\n"
			else_cases[-1] = (f"<{', '.join([f'{elem_key}={{}}' for elem_key, _ in elems])}>", self.indent)
		else:
			interm_rel2cols = defaultdict(list)
			for _, (rel, col) in interm_cols:
				interm_rel2cols[rel].append(col)
			for rel, cols in interm_rel2cols.items():
				yield f"sum(<{self.var_mng.offset_var(rel)}, _> <- {self.var_mng.trie_var(rel)})\n"
				self.indent += 1
			final_attrs = []
			for idx, (rel, col) in interm_cols:
				final_attrs.append(
					f"{self.var_mng.interm_col(idx)}="
					f"{self.var_mng.rel_col_var(rel, col)}({self.var_mng.offset_var(rel)})"
				)
			yield f'{{ <{", ".join(final_attrs)}> -> true }}\n'

		for else_case, indent in else_cases[::-1]:
			self.indent = indent - 1
			yield f"else\n"
			self.indent += 1
			yield f"{else_case}\n"

		if not self.var_mng.is_root_rel(interm_rel):
			self.indent = 0
			yield f"in\n"


	@staticmethod
	def _order_join_cols_based_on_compiled_plan(
			build_plan: List[Tuple[str, List[str], List[str]]], compiled_plan: List[List[str]]
	) -> Dict[str, Dict[str, int]]:  # rel -> col -> idx
		join_attrs_order = {
			rel: {col: math.inf for col in join_cols}
			for rel, join_cols, _ in build_plan
		}
		for idx, eq_cols in enumerate(compiled_plan):
			min_idx = min(idx, *[join_attrs_order[rel][col] for rel, col in eq_cols])
			for rel, col in eq_cols:
				join_attrs_order[rel][col] = min_idx
		return join_attrs_order
