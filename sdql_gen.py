import math
import os
import re
from collections import defaultdict
from typing import List, Tuple, Set, Union

from consts import generated_sdql_path, preprocessed_data_path, abbr2rel, rel_wo_idx, rel2col2type, JoinMode
from var_mng import VariableManager


class AbstractSDQLGenerator:
	def __init__(self, var_mng: VariableManager):
		self.resolved_attrs = set()
		self.available_tuples = set()
		self.indent = 0

		self.var_mng = var_mng
		self.save_path = str()

	def clear(self):
		self.indent = 0
		self.resolved_attrs.clear()
		self.available_tuples.clear()

	def generate(self, query: str, plans: List[Tuple[Tuple[str, List, List], List, List]]):
		with open(os.path.join(self.save_path, f"{query}.sdql"), "w") as sdql_file:
			for _, build_plan, _ in plans:
				for line in self._generate_loads(query, build_plan):
					sdql_file.write('\t' * self.indent + line)
			sdql_file.write("\n")

			for i, (node, build_plan, compiled_plan) in enumerate(plans):
				# look ahead to the next compiled plan - to see which columns are needed for intermediate variable
				if re.search(r"interm\d", node[0]) is not None:
					lookup_cols = self.get_include_cols(plans[i+1][2], node[0])
				else:
					lookup_cols = None

				for line in self._generate_subquery(node, build_plan, compiled_plan, lookup_cols):
					sdql_file.write('\t' * self.indent + line)
				self.indent = 0
				sdql_file.write("\n")

	def _generate_loads(self, query: str, build_plan: List[Tuple[str, List[str], List[str]]]):
		for rel, _, _ in build_plan:
			if self.var_mng.is_interm_rel(rel):
				continue
			if os.path.exists(os.path.join(preprocessed_data_path, query, f"{rel}.csv")):
				path = f"datasets/job/{query}/{rel}.csv"
			else:
				path = f"datasets/job/{abbr2rel[rel_wo_idx(rel)]}.csv"
			path = os.path.normpath(path)
			yield f'let {rel} = load[<{", ".join([f"{col_n}: @vec {{int -> {col_t}}}" for col_n, col_t in rel2col2type[rel_wo_idx(rel)].items()])}, size: int>]("{path}")\n'

	def _generate_subquery(
			self,
			node: Tuple[str, List[Tuple[int, Tuple[str, str]]], List[int]],
			build_plan: List[Tuple[str, List[str], List[str]]],
			compiled_plan: List[List[Tuple[str, str]]],
			lookup_cols = None,
	):
		raise NotImplementedError

	def _tuple_iteration(self, rel):
		if self.var_mng.is_interm_rel(rel):
			return f"sum(<{self.var_mng.tuple_var(rel)}, _> <- {self.var_mng.tuples_var(rel)})"
		else:
			return f"sum(<{self.var_mng.off_var(rel)}, _> <- {self.var_mng.tuples_var(rel)})"

	def _tuple_col_var(self, rel, col):
		if self.var_mng.is_interm_rel(rel):
			return f"{self.var_mng.tuple_var(rel)}.{col}"
		else:
			return f"{rel}.{col}({self.var_mng.off_var(rel)})"

	@staticmethod
	def get_include_cols(compiled_plan: List, target: str) -> Union[None, Set[int]]:
		rel2trie_levels = defaultdict(list)
		iter_rels = set()
		for eq_cols in compiled_plan:
			rel_it, _ = eq_cols[0]
			iter_rels.add(rel_it)
			for rel, col in eq_cols[1:]:
				if rel not in iter_rels:
					rel2trie_levels[rel].append(col)

		res = next((v for k, v in rel2trie_levels.items() if k == target), None)
		return None if res is None else set(int(x[3:]) for x in res)


class GJSDQLGenerator(AbstractSDQLGenerator):
	def __init__(self, var_mng: VariableManager):
		super().__init__(var_mng)
		self.save_path = os.path.join(generated_sdql_path, "gj")

	def _generate_subquery(
			self,
			node: Tuple[str, List[Tuple[int, Tuple[str, str]]], List[int]],
			build_plan: List[Tuple[str, List[str], List[str]]],
			compiled_plan: List[List[Tuple[str, str]]],
			lookup_cols = Union[None, Set[int]],
	):
		interm, interm_cols, interm_trie_cols = node

		rels_in_interm_cols = set(rel for _, (rel, _) in interm_cols)
		for rel, join_cols, proj_cols in build_plan:
			if self.var_mng.is_interm_rel(rel):
				continue
			if rel in rels_in_interm_cols:
				trie_value = f"@smallvecdict(0) {{ i -> 1 }}"
			else:
				trie_value = "1"
			for col in join_cols[::-1]:
				trie_value = f"{{ {rel}.{col}(i) -> {trie_value} }}"
			yield f"let {self.var_mng.trie_var(rel)} = sum(<i, _> <- range({rel}.size)) {trie_value} in\n"

		if not self.var_mng.is_root_rel(interm):
			yield f"let {self.var_mng.trie_var(interm)} = "

		join_attrs_order = {rel: {col: math.inf for col in join_cols} for rel, join_cols, _ in build_plan}
		for idx, eq_cols in enumerate(compiled_plan):
			min_idx = min(idx, *[join_attrs_order[rel][col] for rel, col in eq_cols])
			for rel, col in eq_cols:
				join_attrs_order[rel][col] = min_idx
		for idx, eq_cols in enumerate(compiled_plan):
			rel_it, col_it = eq_cols[0]
			if join_attrs_order[rel_it][col_it] == idx:
				yield f"sum(<{self.var_mng.x_var(idx)}, {self.var_mng.next_trie_var(rel_it)}> <- {self.var_mng.trie_var(rel_it)})\n"
				self.var_mng.next_trie_var(rel_it, inplace=True)
				self.indent += 1
				self.resolved_attrs.add(eq_cols[0])
				start_offset = 1
			elif eq_cols[0] in self.resolved_attrs:
				start_offset = 1
			else:
				start_offset = 0

			for rel, col in eq_cols[start_offset:]:
				yield f"if ({self.var_mng.x_var(join_attrs_order[rel][col])} ∈ {self.var_mng.trie_var(rel)}) then\n"
				self.indent += 1

			for rel, col in eq_cols[start_offset:]:
				yield f"let {self.var_mng.next_trie_var(rel)} = {self.var_mng.trie_var(rel)}({self.var_mng.x_var(join_attrs_order[rel][col])}) in\n"
				self.var_mng.next_trie_var(rel, inplace=True)

		if self.var_mng.is_root_rel(interm):
			interm_col2idx = {rel_col: interm_col_idx for interm_col_idx, rel_col in interm_cols}
			elems = list()
			for rel, _, proj_cols in build_plan:
				if proj_cols:
					yield f"let {self.var_mng.mn_rel_var(rel)} = {self._tuple_iteration(rel)} promote[min_sum](<{', '.join(f'{col}={self._tuple_col_var(rel, col)}' for col in proj_cols)}>) in\n"
				for col in proj_cols:
					elems.append(
						(self.var_mng.interm_col(interm_col2idx[(rel, col)]), f'{self.var_mng.mn_rel_var(rel)}.{col}'))
			yield f"promote[min_sum](<{', '.join([f'{elem_key}={elem_val}' for elem_key, elem_val in elems])}>)\n"
		else:
			interm_rel2cols = defaultdict(list)
			for _, (rel, col) in interm_cols:
				interm_rel2cols[rel].append(col)
			for rel, cols in interm_rel2cols.items():
				yield f"{self._tuple_iteration(rel)}\n"
				self.indent += 1
			new2old_map = {
				self.var_mng.interm_col(idx): self._tuple_col_var(rel, col)
				for idx, (rel, col) in interm_cols
			}
			tuple_value = f"<{', '.join([f'{new_col}={old_col}' for new_col, old_col in new2old_map.items()])}>"
			trie_value = f"@smallvecdict(0) {{ {tuple_value} -> 1 }}"
			for idx in interm_trie_cols[::-1]:
				trie_value = f"{{ {new2old_map[self.var_mng.interm_col(idx)]} -> {trie_value} }}"
			yield f'{trie_value}\n'

		rel2col2type[interm] = dict()
		for interm_col_idx, (rel, col) in interm_cols:
			rel2col2type[interm][self.var_mng.interm_col(interm_col_idx)] = rel2col2type[rel_wo_idx(rel)][col]

		if not self.var_mng.is_root_rel(interm):
			self.indent = 0
			yield f"in\n"


class FJSDQLGenerator(AbstractSDQLGenerator):
	def __init__(self, var_mng: VariableManager):
		super().__init__(var_mng)
		self.save_path = os.path.join(generated_sdql_path, "fj")

	def _generate_subquery(
			self,
			node: Tuple[str, List[Tuple[int, Tuple[str, str]]], List[int]],
			build_plan: List[Tuple[str, List[str], List[str]]],
			compiled_plan: List[List[Tuple[str, str]]],
			lookup_cols = Union[None, Set[int]],
	):
		interm, interm_cols, interm_trie_cols = node

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
			if self.var_mng.is_interm_rel(rel):
				continue
			if rel in rels_in_interm_cols or rel in iter_rels:
				trie_value = f"@smallvecdict(4) {{ i -> 1 }}"
			else:
				trie_value = "1"
			for i, col in enumerate(trie_levels[::-1]):
				# i check isn't needed as FJ queries have 1 level of nesting - keeping it for robustness/correctness
				hint = "" if i > 0 else f"@phmap({rel}.size) "
				trie_value = f"{hint}{{ unique({rel}.{col}(i)) -> {trie_value} }}"
			yield f"let {self.var_mng.trie_var(rel)} = sum(<i, _> <- range({rel}.size)) {trie_value} in\n"

		if not self.var_mng.is_root_rel(interm):
			yield f"let {self.var_mng.trie_var(interm)} = "

		join_attrs_order = {rel: {col: math.inf for col in join_cols} for rel, join_cols, _ in build_plan}
		for idx, eq_cols in enumerate(compiled_plan):
			min_idx = min(idx, *[join_attrs_order[rel][col] for rel, col in eq_cols])
			for rel, col in eq_cols:
				join_attrs_order[rel][col] = min_idx
		for idx, eq_cols in enumerate(compiled_plan):
			rel_it, col_it = eq_cols[0]
			if join_attrs_order[rel_it][col_it] == idx:
				if rel_it not in self.available_tuples:
					yield f"{self._tuple_iteration(rel_it)}\n"
					self.indent += 1
				yield f"let {self.var_mng.x_var(idx)} = {self._tuple_col_var(rel_it, col_it)} in\n"
				self.available_tuples.add(rel_it)
				self.resolved_attrs.add(eq_cols[0])
				start_offset = 1
			elif eq_cols[0] in self.resolved_attrs:
				start_offset = 1
			else:
				start_offset = 0

			for rel, col in eq_cols[start_offset:]:
				yield f"if ({self.var_mng.x_var(join_attrs_order[rel][col])} ∈ {self.var_mng.trie_var(rel)}) then\n"
				self.indent += 1

			for rel, col in eq_cols[start_offset:]:
				yield f"let {self.var_mng.next_trie_var(rel)} = {self.var_mng.trie_var(rel)}({self.var_mng.x_var(join_attrs_order[rel][col])}) in\n"
				self.var_mng.next_trie_var(rel, inplace=True)

		if self.var_mng.is_root_rel(interm):
			interm_col2idx = {rel_col: interm_col_idx for interm_col_idx, rel_col in interm_cols}
			elems = list()
			for rel, _, proj_cols in build_plan:
				if proj_cols:
					let_value = f"<{', '.join(f'{col}={self._tuple_col_var(rel, col)}' for col in proj_cols)}>"
					if rel not in self.available_tuples:
						let_value = f"{self._tuple_iteration(rel)} promote[min_sum]({let_value})"
					yield f"let {self.var_mng.mn_rel_var(rel)} = {let_value} in\n"
				for col in proj_cols:
					elems.append(
						(self.var_mng.interm_col(interm_col2idx[(rel, col)]), f'{self.var_mng.mn_rel_var(rel)}.{col}'))
			yield f"promote[min_sum](<{', '.join([f'{elem_key}={elem_val}' for elem_key, elem_val in elems])}>)\n"
		else:
			interm_rel2cols = defaultdict(list)
			for _, (rel, col) in interm_cols:
				interm_rel2cols[rel].append(col)
			for rel, cols in interm_rel2cols.items():
				if rel not in self.available_tuples:
					yield f"{self._tuple_iteration(rel)}\n"
					self.indent += 1
			new2old_map = {
				self.var_mng.interm_col(idx): self._tuple_col_var(rel, col)
				for idx, (rel, col) in interm_cols
			}
			# columns that are used for lookup aren't needed inside the tuple
			cols = [f'{new_col}={old_col}' for new_col, old_col in new2old_map.items() if (
				lookup_cols is None or int(new_col[3:]) not in lookup_cols
			)]
			tuple_value = f"<{', '.join(cols)}>"
			trie_value = f"@smallvecdict(4) {{ {tuple_value} -> 1 }}"
			# i check isn't needed as FJ queries have 1 level of nesting - keeping it for robustness/correctness
			i = 0
			for idx in interm_trie_cols[::-1]:
				# exclude columns that won't be used for lookup
				if lookup_cols is not None and idx not in lookup_cols:
					continue
				field = new2old_map[self.var_mng.interm_col(idx)]
				(orig, _) = field.split(".", 1)
				if i > 0:
					hint = ""
				else:
					if orig.endswith("_tuple"):
						# TODO handle FJ 33a,b,c without hardcoding value
						hint = "@phmap(1000) "
					else:
						hint = f"@phmap(sum(<k, _> <- {{1000000, {orig}.size}}) promote[min_sum](k)) "
				i += 1
				trie_value = f"{hint}{{ {field} -> {trie_value} }}"
			yield f'{trie_value}\n'

		rel2col2type[interm] = dict()
		for interm_col_idx, (rel, col) in interm_cols:
			rel2col2type[interm][self.var_mng.interm_col(interm_col_idx)] = rel2col2type[rel_wo_idx(rel)][col]

		if not self.var_mng.is_root_rel(interm):
			self.indent = 0
			yield f"in\n"
