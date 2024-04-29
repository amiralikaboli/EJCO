import math
import os
from typing import List, Tuple, Dict
import re


class PlanParser:
	def parse(self, query: str) -> Tuple[List, List]:  # (fused_build_plan, fused_compiled_plan)
		plans_path = os.path.join(os.path.dirname(__file__), "plans")

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

		fused_plan = self._fuse_plans(parsed_plans)
		with open(os.path.join(plans_path, "fused", f"{query}.log"), 'w') as log_file:
			log_file.write(f"{fused_plan[0]}\n")
			log_file.write(f"{fused_plan[1]}\n")

		return fused_plan

	def _parse_build_plan(self, build_plan: str):
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

	def _fuse_plans(self, plans: List[Tuple[str, List, List]]):
		node2plans = {node: (build_plan, compiled_plan) for node, build_plan, compiled_plan in plans}
		for node, build_plan, compiled_plan in plans:
			fused_build_plan = []
			fused_compiled_plan = compiled_plan
			for child, join_cols, proj_cols in build_plan:
				if child in node2plans.keys():
					child_build_plan, child_compiled_plan = node2plans[child]
					fused_build_plan.extend(child_build_plan)

					last_idx = -1
					for child_attr in child_compiled_plan:
						found = False
						for idx, par_attr in enumerate(fused_compiled_plan):
							intersect = set(par_attr).intersection(child_attr)
							if intersect:
								# TODO: the order might need to be different
								for col in child_attr:
									if col not in intersect:
										fused_compiled_plan[idx].append(col)
								last_idx = idx
								found = True
								break
						if not found:
							# TODO: the order might need to be different
							fused_compiled_plan = fused_compiled_plan[:last_idx + 1] + \
												  [child_attr] + \
												  fused_compiled_plan[last_idx + 1:]
				else:
					fused_build_plan.append((child, join_cols, proj_cols))
			node2plans[node] = (fused_build_plan, fused_compiled_plan)

		final_fused_build_plan, final_fused_compiled_plan = node2plans[plans[-1][0]]
		for idx, elem in enumerate(final_fused_build_plan):
			rel, join_cols, proj_cols = elem
			for proj_col in proj_cols:
				for eq_attrs in final_fused_compiled_plan:
					if (rel, proj_col) in eq_attrs:
						final_fused_build_plan[idx][2].remove(proj_col)
						final_fused_build_plan[idx][1].append(proj_col)
						break

		return final_fused_build_plan, final_fused_compiled_plan

	def find_join_attrs_order(
			self, build_plan: List[Tuple[str, List[str], List[str]]], compiled_plan: List[List[str]]
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
