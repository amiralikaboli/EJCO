import os

from parser import PlanParser
from translator import Plan2CPPTranslator
from var_mng import VariableManager

if __name__ == '__main__':
	queries = []
	for filename in os.listdir(os.path.join(os.path.dirname(__file__), "plans", "raw")):
		queries.append(filename[:-4])

	var_mng = VariableManager()
	parser = PlanParser(var_mng)
	translator = Plan2CPPTranslator(var_mng)
	for query in queries:
		var_mng.clear()
		parser.clear()
		translator.clear()

		plans = parser.parse(query, use_cache=False)
		translator.translate(query, plans)
		translator.translate_load_file(query)

	translator.translate_build_file()
