import os
import sys

from consts import JoinMode, plans_path
from cpp_gen import GJCppGenerator, FJCppGenerator
from optimisation import MAX_OPTIMISATION, Optimisation
from parser import PlanParser
from sdql_gen import GJSDQLGenerator, FJSDQLGenerator
from var_mng import VariableManager

if __name__ == '__main__':
	args = sys.argv[1:]
	mode = JoinMode(args[0]) if args else JoinMode.FJ
	print(f"JoinMode: {mode}")
	optimisation = Optimisation(args[1]) if len(args) > 1 else MAX_OPTIMISATION

	queries = []
	for filename in os.listdir(os.path.join(plans_path, mode.value, "raw")):
		queries.append(filename[:-4])

	var_mng = VariableManager()
	assert mode == JoinMode.FJ or optimisation == MAX_OPTIMISATION, "GJ doesn't support ablations"
	parser = PlanParser(mode, var_mng, optimisation)
	sdql_gen = GJSDQLGenerator(var_mng) if mode == JoinMode.GJ else FJSDQLGenerator(var_mng, optimisation)
	cpp_gen = GJCppGenerator(var_mng) if mode == JoinMode.GJ else FJCppGenerator(var_mng)
	for query in queries:
		var_mng.clear()
		parser.clear()
		sdql_gen.clear()
		cpp_gen.clear()

		plans = parser.parse(query, use_cache=False)
		sdql_gen.generate(query, plans)
		# cpp_gen.generate(query, plans)
		# cpp_gen.generate_load_file(query)
	# cpp_gen.generate_build_file()
