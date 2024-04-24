import re
import os
from typing import List, Tuple, Dict

freejoin_path = os.path.join(os.path.dirname(__file__), "..", "..", "free-join")
preprocessed_data_path = os.path.join(freejoin_path, "queries", "preprocessed", "join-order-benchmark", "data")
raw_data_path = os.path.join(freejoin_path, "data", "imdb_csv")

rel_abbrs = {
	"a": "aka_name",
	"an": "aka_name",
	"at": "aka_title",
	"ci": "cast_info",
	"chn": "char_name",
	"cct": "comp_cast_type",
	"cn": "company_name",
	"ct": "company_type",
	"cc": "complete_cast",
	"it": "info_type",
	"k": "keyword",
	"kt": "kind_type",
	"lt": "link_type",
	"mc": "movie_companies",
	"mi": "movie_info",
	"miidx": "movie_info_idx",
	"mi_idx": "movie_info_idx",
	"mk": "movie_keyword",
	"ml": "movie_link",
	"n": "name",
	"pi": "person_info",
	"rt": "role_type",
	"t": "title"
}

rel_types = {
	"mk": {
		"id": "int",
		"movie_id": "int",
		"keyword_id": "int"
	},
	"mi": {
		"id": "int",
		"movie_id": "int",
		"info_type_id": "int",
		"info": "string",
		"note": "string"
	},
	"t": {
		"id": "int",
		"title": "string",
		"kind_id": "int",
		"production_year": "int",
		"imdb_index": "string",
		"phonetic_code": "string",
		"episode_of_id": "int",
		"season_nr": "int",
		"episode_nr": "int",
		"series_years": "string",
		"md5sum": "string"
	},
	"k": {
		"id": "int",
		"keyword": "string",
		"phonetic_code": "string"
	}
}


class Plan2CPPTranslator:
	def __init__(self):
		self.parser = PlanParser()

		self.var_mng = VariableManager()
		self.indent = 1

	def translate(self, queries: List[str]):
		for query in queries:
			self._translate(query)

	def _translate(self, query: str):
		build_plan, compiled_plan = self.parser.parse(query)

		with open(f"generated/{query}.cpp", 'w') as cpp_file:
			cpp_file.write("#include <iostream>\n")
			cpp_file.write('#include "../../include/load.h"\n')
			cpp_file.write('#include "../../include/build.h"\n\n')
			cpp_file.write('using namespace std;\n\n')
			cpp_file.write('int main() {\n')

			for line in self._translate_build_plan(query, build_plan):
				cpp_file.write('\t' * self.indent + line)
			cpp_file.write('\n')

			for line in self._translate_compiled_plan(build_plan, compiled_plan):
				cpp_file.write('\t' * self.indent + line)
			while self.indent > 1:
				self.indent -= 1
				cpp_file.write('\t' * self.indent + '}\n')

			cpp_file.write(f'\tcerr << {self.var_mng.res_var()}.size() << endl;\n')

			cpp_file.write('}\n')

	def _translate_build_plan(self, query: str, build_plan: List[Tuple]):
		for rel_name, join_cols, proj_cols in build_plan:
			path = os.path.join(raw_data_path, f"{rel_abbrs[rel_name]}.csv")
			if os.path.exists(os.path.join(preprocessed_data_path, query, f"{rel_name}.csv")):
				path = os.path.join(preprocessed_data_path, query, f"{rel_name}.csv")
			yield f'load_{rel_name}("{os.path.normpath(path)}");\n'
		yield '\n'

		for rel_name, join_cols, proj_cols in build_plan:
			level_types = [rel_types[rel_name][join_col] for join_col in join_cols]
			trie_type = f"{''.join([f'phmap::flat_hash_map<{ttt}, ' for ttt in level_types])}vector<int>{'>' * len(join_cols)}"
			yield f"auto {self.var_mng.trie_var(rel_name)} = {trie_type}();\n"

			yield f"build_trie({self.var_mng.trie_var(rel_name)}, {', '.join([self.var_mng.rel_col_var(rel_name, join_col) for join_col in join_cols])});\n"

	def _translate_compiled_plan(self, build_plan: List[Tuple], compiled_plan: List[List[str]]):
		build_plan = self._add_join_idx_to_build_plan(build_plan, compiled_plan)

		col_types, res_attrs = self._find_res_types_and_attrs(build_plan)
		yield f"vector<tuple<{', '.join(col_types)}>> {self.var_mng.res_var()};\n"

		for idx, eq_cols in enumerate(compiled_plan):
			rel_it = eq_cols[0][0]
			yield f"for (const auto &[{self.var_mng.x_var(idx)}, {self.var_mng.next_trie_var(rel_it)}]: {self.var_mng.trie_var(rel_it)}) {{\n"
			self.var_mng.next_trie_var(rel_it, inplace=True)
			self.indent += 1

			conditions = []
			assignments = []
			for rel, _ in eq_cols[1:]:
				conditions.append(f"{self.var_mng.trie_var(rel)}.contains({self.var_mng.x_var(idx)})")
				assignments.append(
					f"auto &{self.var_mng.next_trie_var(rel)} = {self.var_mng.trie_var(rel)}.at({self.var_mng.x_var(idx)});\n"
				)
				self.var_mng.next_trie_var(rel, inplace=True)

			yield f"if ({' && '.join(conditions)}) {{\n"
			self.indent += 1
			for assignment in assignments:
				yield assignment

		for rel, cols in build_plan.items():
			yield f"for (const auto &{self.var_mng.offset_var(rel)}: {self.var_mng.trie_var(rel)}) {{\n"
			self.indent += 1

		yield f"{self.var_mng.res_var()}.push_back({{{', '.join(res_attrs)}}});\n"

	def _add_join_idx_to_build_plan(
			self, build_plan: List[Tuple], compiled_plan: List[List[str]]
	) -> Dict[str, Tuple[List[Tuple[str, int]], List[str]]]:
		# rel -> ([(join_col, idx)], [proj_col])
		build_plan = {
			rel_name: ([(join_col, -1) for join_col in join_cols], proj_cols)
			for rel_name, join_cols, proj_cols in build_plan
		}
		for idx, eq_cols in enumerate(compiled_plan):
			for rel, col in eq_cols:
				for i in range(len(build_plan[rel][0])):
					if build_plan[rel][0][i][0] == col:
						build_plan[rel][0][i] = (col, idx)
		return build_plan

	def _find_res_types_and_attrs(self, build_plan: Dict[str, Tuple[List[Tuple[str, int]], List[str]]]):
		col_types = []
		res_attrs = []
		last_join_idx = -1
		for rel, cols in build_plan.items():
			for col, idx in cols[0]:
				if last_join_idx < idx:
					col_types.append(rel_types[rel][col])
					res_attrs.append(self.var_mng.x_var(idx))
					last_join_idx = idx
			for col in cols[1]:
				col_types.append(rel_types[rel][col])
				res_attrs.append(f"{self.var_mng.rel_col_var(rel, col)}[{self.var_mng.offset_var(rel)}]")
		return col_types, res_attrs


class VariableManager:
	def __init__(self):
		self._trie_vars = dict()
		self._last_x_var = 0

	def trie_var(self, rel_name: str):
		if rel_name not in self._trie_vars.keys():
			self._trie_vars[rel_name] = f"{rel_name}_trie0"
		return self._trie_vars[rel_name]

	def next_trie_var(self, rel_name: str, inplace: bool = False):
		trie_var = self._trie_vars[rel_name]
		trie_level = int(trie_var[-1]) + 1
		next_level_trie = f"{rel_name}_trie{trie_level}"
		if inplace:
			self._trie_vars[rel_name] = next_level_trie
		return next_level_trie

	def x_var(self, idx: int):
		return f"x{idx}"

	def rel_col_var(self, rel_name: str, col: str):
		return f"{rel_name}_{col}"

	def offset_var(self, rel_name: str):
		return f"{rel_name}_off"

	def res_var(self):
		return "res"


class PlanParser:
	def parse(self, query: str) -> Tuple[List, List]:  # (fused_build_plan, fused_compiled_plan)
		with open(os.path.join(os.path.dirname(__file__), "plans", f"{query}.log"), 'r') as log_file:
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
					l_col, r_col = eq.strip().split(" = ")
					if idx == 0:
						eq_cols.append(tuple(l_col[4:].split(".")))
					eq_cols.append(tuple(r_col[4:].split(".")))
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

					for idx, par_attr in enumerate(compiled_plan):
						for child_attr in child_compiled_plan:
							intersect = set(par_attr).intersection(child_attr)
							if intersect:
								# TODO: the order might need more consideration
								for col in child_attr:
									if col not in intersect:
										fused_compiled_plan[idx].append(col)
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


if __name__ == '__main__':
	queries = ["3a"]

	translator = Plan2CPPTranslator()
	translator.translate(queries)
