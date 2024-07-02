import os
import sys

from consts import JoinMode, plans_path
from cpp_gen import CppGenerator
from parser import PlanParser
from sdql_gen import SDQLGenerator
from var_mng import VariableManager

if __name__ == '__main__':
	args = sys.argv[1:]
	mode = JoinMode(args[0] if args else JoinMode.GJ)
	print(f"JoinMode: {mode}")

	queries = []
	for filename in os.listdir(os.path.join(plans_path, "raw")):
		queries.append(filename[:-4])

	var_mng = VariableManager()
	parser = PlanParser(var_mng)
	sdql_gen = SDQLGenerator(mode, var_mng)
	cpp_gen = CppGenerator(mode, var_mng)
	for query in queries:
		var_mng.clear()
		parser.clear()
		sdql_gen.clear()
		cpp_gen.clear()

		plans = parser.parse(query, use_cache=False)
		# sdql_gen.generate(query, plans)
		cpp_gen.generate(query, plans)
		cpp_gen.generate_load_file(query)
	# cpp_gen.generate_build_file()
