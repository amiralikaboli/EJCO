import math
import os
import re
from typing import List, Tuple, Dict

from consts import plans_path
from var_mng import VariableManager


class PlanParser:
	def __init__(self, var_mng: VariableManager):
		self.var_mng = var_mng

	def parse(self, query: str, use_cache: bool = False) -> List[Tuple[Tuple[str, List], List, List]]:
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
		if len(parsed_plans) > 2:
			return None

		parsed_plans = self._resolve_intermediate_stuff(parsed_plans)

		with open(os.path.join(plans_path, "parsed", f"{query}.log"), 'w') as log_file:
			for node, build_plan, compiled_plan in parsed_plans:
				log_file.write(f"{node}\n")
				log_file.write(f"{build_plan}\n")
				log_file.write(f"{compiled_plan}\n")
				log_file.write(f"{'#' * 200}\n")

		return parsed_plans

	def _parse_build_plan(self, build_plan: str) -> List[Tuple[str, List[str], List[str]]]:
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

	def _parse_compiled_plan(self, compiled_plan: str):
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
			parsed_plans: List[Tuple[str, List, List]]
	) -> List[Tuple[Tuple[str, List], List, List]]:
		for u_idx in range(len(parsed_plans) - 1):
			found = False

			u_node, u_build, u_compiled = parsed_plans[u_idx]

			interm_rel = self.var_mng.interm_rel(u_idx)
			interm_cols = self.intermediate_columns_list(u_build, u_compiled)
			u_bags = [set([relcol]) for relcol in interm_cols]
			for eq_cols in u_compiled:
				for bag_idx in range(len(u_bags)):
					if u_bags[bag_idx].intersection(set(eq_cols)):
						u_bags[bag_idx].update(eq_cols)
						break

			for d_idx in range(u_idx + 1, len(parsed_plans)):
				d_node, d_build, d_compiled = parsed_plans[d_idx]
				for d_build_idx in range(len(d_build)):
					if d_build[d_build_idx][0] == u_node:
						d_build[d_build_idx] = (
							interm_rel,
							[self.var_mng.interm_col(u_col_idx) for u_col_idx in d_build[d_build_idx][1]],
							[self.var_mng.interm_col(u_col_idx) for u_col_idx in d_build[d_build_idx][2]]
						)
						found = True
						break

				if found:
					for d_compiled_idx in range(len(d_compiled)):
						eq_cols = d_compiled[d_compiled_idx]
						for eq_cols_idx in range(len(eq_cols)):
							rel, col = eq_cols[eq_cols_idx]
							for bag_idx, bag in enumerate(u_bags):
								if (rel, col) in bag:
									d_compiled[d_compiled_idx][eq_cols_idx] = (
										interm_rel, self.var_mng.interm_col(bag_idx))
					break

				parsed_plans[d_idx] = (d_node, d_build, d_compiled)

			parsed_plans[u_idx] = ((interm_rel, interm_cols), u_build, u_compiled)

		parsed_plans[-1] = (('root', []), parsed_plans[-1][1], parsed_plans[-1][2])
		return parsed_plans

	@staticmethod
	def intermediate_columns_list(build_plan: List, compiled_plan: List) -> List[Tuple[str, str]]:
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

	@staticmethod
	def order_join_cols_based_on_compiled_plan(
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
