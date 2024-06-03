import os

from parser import PlanParser
from sdql_gen import SDQLGenerator
from var_mng import VariableManager

if __name__ == '__main__':
	queries = []
	for filename in os.listdir(os.path.join(os.path.dirname(__file__), "plans", "raw")):
		queries.append(filename[:-4])

	var_mng = VariableManager()
	parser = PlanParser(var_mng)
	sdql_gen = SDQLGenerator(var_mng)
	for query in queries:
		var_mng.clear()
		parser.clear()
		sdql_gen.clear()

		plans = parser.parse(query, use_cache=False)
		sdql_program = sdql_gen.generate(query, plans)
