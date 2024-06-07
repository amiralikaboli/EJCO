import os

from consts import JoinMode, plans_path
from cpp_gen import CppGenerator
from parser import PlanParser
from sdql_gen import SDQLGenerator
from var_mng import VariableManager

if __name__ == '__main__':
	queries = []
	for filename in os.listdir(os.path.join(plans_path, "raw")):
		queries.append(filename[:-4])

	var_mng = VariableManager()
	parser = PlanParser(var_mng)
	gj_sdql_gen = SDQLGenerator(JoinMode.GJ, var_mng)
	fj_sdql_gen = SDQLGenerator(JoinMode.FJ, var_mng)
	cpp_gen = CppGenerator(var_mng)
	for query in queries:
		var_mng.clear()
		parser.clear()
		gj_sdql_gen.clear()
		fj_sdql_gen.clear()
		cpp_gen.clear()

		plans = parser.parse(query, use_cache=False)
		# gj_sdql_gen.generate(query, plans)
		fj_sdql_gen.generate(query, plans)
	# 	cpp_gen.generate(query, plans)
	# 	cpp_gen.generate_load_file(query)
	# cpp_gen.generate_build_file()
