import math
import os
import re
from typing import List, Tuple, Dict, Set

from consts import plans_path
from var_mng import VariableManager


class PlanParser:
	def __init__(self, var_mng: VariableManager):
		self.var_mng = var_mng
		self.bags: List[Set[Tuple[str, str]]] = list()

	def clear(self):
		self.bags = list()

	def parse(self, query: str, use_cache: bool = False) -> List[Tuple[Tuple[str, List, List], List, List]]:
		if use_cache and os.path.exists(os.path.join(plans_path, "parsed", f"{query}.log")):
			with open(os.path.join(plans_path, "parsed", f"{query}.log"), 'r') as log_file:
				lines = log_file.readlines()
			return [
				(eval(lines[i].strip()), eval(lines[i + 1].strip()), eval(lines[i + 2].strip()))
				for i in range(0, len(lines), 4)
			]

		with open(os.path.join(plans_path, "raw", f"{query}.log"), 'r') as log_file:
			lines = log_file.readlines()
		parsed_plans = [
			(
				lines[i + 1].strip(),
				self._parse_build_plan(lines[i + 2].strip()),
				self._parse_compiled_plan(lines[i + 3].strip())
			)
			for i in range(0, len(lines), 4)
		]

		parsed_plans = self._resolve_intermediate_stuff(parsed_plans)

		with open(os.path.join(plans_path, "parsed", f"{query}.log"), 'w') as log_file:
			for node, build_plan, compiled_plan in parsed_plans:
				log_file.write(f"{node}\n")
				log_file.write(f"{build_plan}\n")
				log_file.write(f"{compiled_plan}\n")
				log_file.write(f"{'#' * 200}\n")

		return parsed_plans

	@staticmethod
	def _parse_build_plan(build_plan: str) -> List[Tuple[str, List[str], List[str]]]:
		build_plan = build_plan[1:-1]
		parsed_plan = []
		for rel in build_plan.split("])")[:-1]:
			rel = f"{rel[3:]}" if rel[0] == "," else f"{rel[1:]}"
			rev_rel = rel[::-1]
			idx = rev_rel.find("[")
			proj_part = rev_rel[:idx][::-1]
			proj_cols = []
			if proj_part:
				for col in proj_part.split(","):
					col = col.strip()
					if col[:2] == "Id":
						proj_cols.append(int(col[3:-1]))
					elif col[:4] == "Name":
						proj_cols.append(col[6:-2])
					else:
						raise ValueError(f"Unknown column type: {col}")
			rev_rel = rev_rel[idx + 4:]
			idx = rev_rel.find("[")
			join_part = rev_rel[:idx][::-1]
			join_cols = []
			for col in join_part.split(","):
				col = col.strip()
				if col[:2] == "Na":
					join_cols.append(col[6:-2])
				else:
					join_cols.append(int(col[3:-1]))
			rev_rel = rev_rel[idx + 3:]
			rel_name = rev_rel[::-1][5:-1]
			rel_name = rel_name[1:-1] if rel_name[0] == '"' else rel_name
			parsed_plan.append((rel_name, join_cols, proj_cols))
		return parsed_plan

	@staticmethod
	def _parse_compiled_plan(compiled_plan: str):
		compiled_plan = compiled_plan[1:-1]
		idxs = sorted(
			[m.start() for m in re.finditer("Lookup", compiled_plan)] +
			[m.start() for m in re.finditer("Intersect", compiled_plan)]
		)
		idxs.append(len(compiled_plan))
		parsed_plan = []
		for i in range(len(idxs) - 1):
			op = compiled_plan[idxs[i]:idxs[i + 1]].strip()
			op = op[:-1] if op[-1] == "," else op
			if op[:6] == "Lookup":
				op = op[8:-3].replace(")", "")
				eqs = op.split(",")
				eq_cols = []
				for idx, eq in enumerate(eqs):
					l_side, r_side = eq.strip().split(" = ")
					l_rc, r_rc = tuple(l_side[4:].split(".")), tuple(r_side[4:].split("."))
					if idx == 0:
						eq_cols.append(l_rc)
						eq_cols.append(r_rc)
					elif l_rc in eq_cols:
						eq_cols.append(r_rc)
					elif r_rc in eq_cols:
						eq_cols.append(l_rc)
					else:
						parsed_plan.append(eq_cols)
						eq_cols = [l_rc, r_rc]
				parsed_plan.append(eq_cols)
			elif op[:9] == "Intersect":
				op = op[11:-3]
				if len(op.split("),")) > 2:
					raise NotImplementedError(op)
				parsed_plan.append([tuple(side[:-4].strip().split(".")) for side in op.split("),")])
			else:
				raise ValueError(f"Unknown operation: {op}")
		return parsed_plan

	# TODO: rename this function
	def _resolve_intermediate_stuff(
			self,
			plans: List[Tuple[str, List, List]]
	) -> List[Tuple[Tuple[str, List, List], List, List]]:
		for idx_u, (node_u, build_u, compiled_u) in enumerate(plans):
			interm_rel = self.var_mng.interm_rel(idx_u)
			interm_cols = self._intermediate_columns_list(build_u, compiled_u)
			interm_cols_enumerated = [(idx, rel_col) for idx, rel_col in enumerate(interm_cols)]
			interm_trie_levels = list()
			self._update_bags(compiled_u, interm_rel, interm_cols)

			found = False
			for idx_d, (node_d, build_d, compiled_d) in enumerate(plans[idx_u + 1:], start=idx_u + 1):
				for build_d_idx, (can_node_u, can_join_cols, can_proj_cols) in enumerate(build_d):
					if can_node_u == node_u:
						interm_trie_levels = can_join_cols
						build_d[build_d_idx] = (
							interm_rel,
							[self.var_mng.interm_col(i) for i in can_join_cols],
							[self.var_mng.interm_col(i) for i in can_proj_cols]
						)
						found = True
						break

				if found:
					for compiled_d_idx, eq_cols in enumerate(compiled_d):
						for eq_cols_idx, (rel_d, col_d) in enumerate(eq_cols):
							for bag in self.bags:
								if (rel_d, col_d) in bag:
									for rel_u, col_u in bag:
										if rel_u == interm_rel:
											compiled_d[compiled_d_idx][eq_cols_idx] = (rel_u, col_u)
					break

				plans[idx_d] = (node_d, build_d, compiled_d)
			plans[idx_u] = ((interm_rel, interm_cols_enumerated, interm_trie_levels), build_u, compiled_u)
		plans[-1] = (('root', plans[-1][0][1], []), plans[-1][1], plans[-1][2])
		return plans

	@staticmethod
	def _intermediate_columns_list(build_plan: List, compiled_plan: List) -> List[Tuple[str, str]]:
		columns = list()
		rel2join_cols = dict()
		for rel, join_cols, proj_cols in build_plan:
			rel2join_cols[rel] = join_cols + proj_cols
		for eq_cols in compiled_plan:
			for rel, col in eq_cols[1:]:
				rel2join_cols[rel].remove(col)
		for rel, _, _ in build_plan:
			for col in rel2join_cols[rel]:
				columns.append((rel, col))
		return columns

	def _update_bags(self, u_compiled, interm_rel, interm_cols):
		for eq_cols in u_compiled:
			new_bag = True
			for bag_idx in range(len(self.bags)):
				if self.bags[bag_idx].intersection(set(eq_cols)):
					self.bags[bag_idx].update(eq_cols)
					new_bag = False
					break
			if new_bag:
				self.bags.append(set(eq_cols))
		for idx, (rel, col) in enumerate(interm_cols):
			new_bag = True
			for bag_idx, bag in enumerate(self.bags):
				if (rel, col) in bag:
					self.bags[bag_idx].add((interm_rel, self.var_mng.interm_col(idx)))
					new_bag = False
					break
			if new_bag:
				self.bags.append({(rel, col), (interm_rel, self.var_mng.interm_col(idx))})


if __name__ == '__main__':
	queries = []
	for filename in os.listdir(os.path.join(os.path.dirname(__file__), "plans", "raw")):
		queries.append(filename[:-4])

	parser = PlanParser(VariableManager())
	for query in queries:
		parser.clear()
		parser.parse(query)
