import json
import math
import os
from typing import List, Tuple, Dict

from consts import PlanNode, freejoin_path, plans_path


class PlanParser:
	def parse(self, query: str, use_cache: bool = False) -> Tuple[List, List]:  # (build_plan, compiled_plan)
		if use_cache and os.path.exists(os.path.join(plans_path, "fused", f"{query}.log")):
			with open(os.path.join(plans_path, "fused", f"{query}.log"), 'r') as log_file:
				return [eval(line.strip()) for line in log_file.readlines()]

		with open(os.path.join(freejoin_path, "logs", "plan-profiles", f"{query}.json"), 'r') as json_file:
			tree_plan = json.load(json_file)
		fused_compiled_plan = self._fuse_compiled_plan(tree_plan)

		with open(os.path.join(plans_path, "raw", f"{query}.log"), 'r') as log_file:
			lines = log_file.readlines()
		node_build_plans = [
			(lines[i + 1].strip(), self._parse_build_plan(lines[i + 2].strip()))
			for i in range(0, len(lines), 4)
		]
		fused_build_plan = self._fuse_build_plans(node_build_plans, fused_compiled_plan)

		with open(os.path.join(plans_path, "fused", f"{query}.log"), 'w') as log_file:
			log_file.write(f"{fused_build_plan}\n")
			log_file.write(f"{fused_compiled_plan}\n")

		return fused_build_plan, fused_compiled_plan

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
	def _fuse_build_plans(
			node_build_plans: List[Tuple[str, List[Tuple[str, List[str], List[str]]]]],
			fused_compiled_plan: List[List[Tuple[str, str]]]
	) -> List[Tuple[str, List[str], List[str]]]:
		node2plans = {node: build_plan for node, build_plan in node_build_plans}
		for node, build_plan in node_build_plans:
			fused_build_plan = []
			for child, join_cols, proj_cols in build_plan:
				if child in node2plans.keys():
					fused_build_plan.extend(node2plans[child])
				else:
					fused_build_plan.append((child, join_cols, proj_cols))
			node2plans[node] = fused_build_plan

		fused_build_plan = node2plans[node_build_plans[-1][0]]
		rels2cols = {rel: ([], proj_cols) for rel, join_cols, proj_cols in fused_build_plan}
		for eq_cols in fused_compiled_plan:
			for rel, col in eq_cols:
				if col not in rels2cols[rel][0]:
					rels2cols[rel][0].append(col)
				if col in rels2cols[rel][1]:
					rels2cols[rel][1].remove(col)
		return [(rel, rels2cols[rel][0], rels2cols[rel][1]) for rel in rels2cols.keys()]

	def _fuse_compiled_plan(self, tree_plan: Dict) -> List[List[Tuple[str, str]]]:
		compiled_plan = self._linearize_plan_tree(tree_plan)
		duplicates = [[] for _ in compiled_plan]
		for r_i in range(len(compiled_plan)):
			for relcol in compiled_plan[r_i]:
				for l_i in range(r_i):
					if relcol in compiled_plan[l_i]:
						duplicates[r_i].append(relcol)
						break
		for eq_cols, dups in zip(compiled_plan, duplicates):
			for dup in dups[1:]:
				eq_cols.remove(dup)
		return compiled_plan

	def _linearize_plan_tree(self, node) -> List[List[Tuple[str, str]]]:
		for child in node["children"]:
			if child["name"] == PlanNode.ChunkScan.value:
				node["children"].remove(child)

		if len(node["children"]) == 0:
			return []
		if len(node["children"]) == 1:
			return self._linearize_plan_tree(node["children"][0])

		left_child_plan = self._linearize_plan_tree(node["children"][0])
		right_child_plan = self._linearize_plan_tree(node["children"][1])
		plan = left_child_plan + right_child_plan
		if node["name"] == PlanNode.HashJoin.value:
			eqs = [tuple(side.strip() for side in eq.split(" = ")) for eq in node["extra_info"][5:].strip().split("\n")]
			for eq in eqs:
				left_side, right_side = eq
				left_attr, right_attr = tuple(left_side.split('.')), tuple(right_side.split('.'))

				if not plan:
					plan.append([left_attr, right_attr])
				elif left_attr in plan[-1] and right_attr in plan[-1]:
					pass
				elif left_attr in plan[-1]:
					plan[-1].append(right_attr)
				elif right_attr in plan[-1]:
					plan[-1].append(left_attr)
				else:
					plan.append([left_attr, right_attr])
		else:
			raise ValueError(f"Unknown node type: {node['name']}")
		return plan

	@staticmethod
	def find_join_attrs_order(
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
