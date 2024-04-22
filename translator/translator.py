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

		# TODO: iterate over all plans
		print(*plan[0], sep="\n")
		print("=" * 100)
		print(self._translate_build(query, plan[0][1]))
		print(self._translate_compiled(plan[0][2]))

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
			self.rel_schemas[rel_name] = (join_cols, proj_cols)

		return code

	def _translate_compiled(self, compiled_plan: List[List[str]]):
		code = ""

		# TODO: debug this
		for eq_cols in compiled_plan:
			for relcol in eq_cols:
				rel, col = relcol.split(".")
				depth = len(self.rel_schemas[rel][0])
				code += f"auto {rel}_trie = "
				code += "phmap::flat_hash_map<int, " * depth
				code += "vector<int>"
				code += ">" * depth
				code += "();\n"

				code += f"build_trie({rel}_trie, {rel}_{col});\n"

			code += f"vector<tuple<{', '.join(['int'] * len(eq_cols))}>> res;\n"
			code += f"for (auto& [x, off1] : {eq_cols[0].split('.')[0]}_trie) {{\n"
			code += f"if ({eq_cols[1].split('.')[0]}_trie.contains(x)) {{\n"
			code += f"auto &off2 = {eq_cols[1].split('.')[0]}_trie.at(x);\n"
			code += f"for (auto &o1 : off1) {{\n"
			code += f"for (auto &o2 : off2) {{\n"
			code += f"res.push_back(make_tuple(o1, o2));\n"
			code += f"}}\n"
			code += f"}}\n"
			code += f"}}\n"
			code += f"}}\n"


		return code


class VariableManager:
	def __init__(self):
		self.var_num = 1
		self.var_map = dict()

	@staticmethod
	def var(self, name):
		if name in self.var_map:
			return self.var_map[name]
		else:
			var_name = f"x{self.var_num}"
			self.var_num += 1
			self.var_map[name] = var_name
			return var_name

class PlanParser:
	def parse(self, query: str) -> List[Tuple]:  # (node, build_plan, compiled_plan)
		with open(os.path.join(freejoin_path, "logs", "gj_plans", f"{query}.log"), 'r') as log_file:
			lines = log_file.readlines()

		return [
			(
				lines[i + 1].strip(),
				self._parse_build_plan(lines[i + 2].strip()),
				self._parse_compiled_plan(lines[i + 3].strip())
			)
			for i in range(0, len(lines), 4)
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
						eq_cols.append(l_col[4:])
						eq_cols.append(r_col[4:])
					else:
						eq_cols.append(r_col[4:])
				parsed_plan.append(eq_cols)
			elif op[:9] == "Intersect":
				op = op[11:-3]
				if len(op.split("),")) > 2:
					raise NotImplementedError(op)
				parsed_plan.append([side[:-4] for side in op.split("),")])
			else:
				raise ValueError(f"Unknown operation: {op}")
		return parsed_plan


if __name__ == '__main__':
	queries = ["3a"]

	translator = Plan2CPPTranslator()
	translator.translate(queries)
