import os

from cpp_gen import CPPGenerator
from parser import PlanParser
from var_mng import VariableManager

if __name__ == '__main__':
	queries = []
	for filename in os.listdir(os.path.join(os.path.dirname(__file__), "plans", "raw")):
		queries.append(filename[:-4])

	var_mng = VariableManager()
	parser = PlanParser(var_mng)
	cpp_gen = CPPGenerator(var_mng)
	for query in queries:
		var_mng.clear()
		parser.clear()
		cpp_gen.clear()

		plans = parser.parse(query, use_cache=False)
		cpp_gen.generate(query, plans)
		cpp_gen.generate_load_file(query)

	cpp_gen.generate_build_file()
