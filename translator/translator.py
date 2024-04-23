import re
import os
from typing import List, Tuple

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

		self.rel_schemas = dict()
		self.var_mng = VariableManager()

	def translate(self, queries: List[str]):
		for query in queries:
			self._translate(query)

	def _translate(self, query: str):
		plan = self.parser.parse(query)

		for p in plan:
			print(*p, sep="\n")
			print("=" * 100)

		# TODO: iterate over all plans
		with open(f"generated/{query}.cpp", 'w') as cpp_file:
			cpp_file.write("#include <iostream>\n")
			cpp_file.write('#include "../../include/load.h"\n')
			cpp_file.write('#include "../../include/build.h"\n')
			cpp_file.write('#include "../../include/parallel_hashmap/phmap.h"\n')
			cpp_file.write('using namespace std;\n')
			cpp_file.write('int main(){\n')
			cpp_file.write(self._translate_build(query, plan[0][1]))
			cpp_file.write('\n')
			cpp_file.write(self._translate_compiled(plan[0][1], plan[0][2]))
			cpp_file.write('\n')
			cpp_file.write('cerr << res.size() << endl;\n')
			cpp_file.write('}\n')

	def _translate_build(self, query: str, build_plan: List[Tuple]):
		code = ""
		for rel_name, join_cols, proj_cols in build_plan:
			if rel_name in self.rel_schemas.keys():
				continue

			if os.path.exists(os.path.join(preprocessed_data_path, query, f"{rel_name}.csv")):
				path = os.path.join(preprocessed_data_path, query, f"{rel_name}.csv")
			else:
				path = os.path.join(raw_data_path, f"{rel_abbrs[rel_name]}.csv")

			code += f'load_{rel_name}("{os.path.normpath(path)}");\n'
			code += f"auto {self.var_mng.trie_var(rel_name)} = "
			code += "phmap::flat_hash_map<int, " * len(join_cols)  # TODO: fix types
			code += "vector<int>"
			code += ">" * len(join_cols)
			code += "();\n"
			code += f"build_trie({self.var_mng.trie_var(rel_name)}, {', '.join([f'{rel_name}_{join_col}' for join_col in join_cols])});\n"
			self.rel_schemas[rel_name] = (join_cols, proj_cols)

		return code

	def _translate_compiled(self, build_plan: List[Tuple], compiled_plan: List[List[str]]):
		build_plan = {
			rel_name: ([(join_col, -1) for join_col in join_cols], proj_cols)
			for rel_name, join_cols, proj_cols in build_plan
		}  # rel -> ([(join_col, idx)], [proj_col])
		for idx, eq_cols in enumerate(compiled_plan):
			for rel, col in eq_cols:
				for i in range(len(build_plan[rel][0])):
					if build_plan[rel][0][i][0] == col:
						build_plan[rel][0][i] = (col, idx)
		print(build_plan)

		col_types = []
		for rel, cols in build_plan.items():
			for col, idx in cols[0]:
				if len(col_types) == idx:
					col_types.append(rel_types[rel][col])
		for rel, cols in build_plan.items():
			for col in cols[1]:
				col_types.append(rel_types[rel][col])
		code = f"vector<tuple<{', '.join(col_types)}>> res;\n"
		open_brackets = 0
		for idx, eq_cols in enumerate(compiled_plan):
			rel_it = eq_cols[0][0]
			code += f"for (const auto& [{self.var_mng.x_var(idx)}, {self.var_mng.next_trie_var(rel_it)}] : {self.var_mng.trie_var(rel_it)}) {{\n"
			self.var_mng.next_trie_var(rel_it, inplace=True)
			open_brackets += 1
			conditions = []
			assignments = []
			for rel, _ in eq_cols[1:]:
				conditions.append(f"{self.var_mng.trie_var(rel)}.contains({self.var_mng.x_var(idx)})")
				assignments.append(
					f"auto& {self.var_mng.next_trie_var(rel)} = {self.var_mng.trie_var(rel)}.at({self.var_mng.x_var(idx)});\n")
				self.var_mng.next_trie_var(rel, inplace=True)
			code += "if ("
			code += ' && '.join(conditions)
			code += ") {\n"
			open_brackets += 1
			code += ''.join(assignments)

		for rel, cols in build_plan.items():
			code += f"for (const auto& {self.var_mng.offset_var(rel)} : {self.var_mng.trie_var(rel)}) {{\n"
			open_brackets += 1

		code += "res.push_back({"
		code += ", ".join([f"{self.var_mng.x_var(idx)}" for idx in range(len(compiled_plan))])
		code += ", "
		code += ", ".join([
			f"{self.var_mng.rel_col_var(rel, col)}[{self.var_mng.offset_var(rel)}]"
			for rel, cols in build_plan.items() for col in cols[1]
		])
		code += "});\n"
		code += "}" * open_brackets
		code += "\n"

		return code


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


class PlanParser:
	def parse(self, query: str) -> List[Tuple]:  # (node, build_plan, compiled_plan)
		# with open(os.path.join(freejoin_path, "logs", "gj_plans", f"{query}.log"), 'r') as log_file:
		# 	lines = log_file.readlines()
		#
		# return [
		# 	(
		# 		lines[i + 1].strip(),
		# 		self._parse_build_plan(lines[i + 2].strip()),
		# 		self._parse_compiled_plan(lines[i + 3].strip())
		# 	)
		# 	for i in range(0, len(lines), 4)
		# ]
		return [
			(
				"3a",
				[('mi', ['movie_id'], []), ('mk', ['movie_id', 'keyword_id'], []), ('t', ['id'], ['title']),
				 ('k', ['id'], [])],
				[[('mi', 'movie_id'), ('mk', 'movie_id'), ('t', 'id')], [('mk', 'keyword_id'), ('k', 'id')]]
			)
		]

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


if __name__ == '__main__':
	queries = ["3a"]

	translator = Plan2CPPTranslator()
	translator.translate(queries)
