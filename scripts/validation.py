import json
import os
import re
import sys
from typing import Dict, Set

freejoin_path = os.path.join(os.path.dirname(__file__), "..", "..", "free-join")

if __name__ == '__main__':
	args = sys.argv[1:]
	results_file = args[0]
	check_validity = True

	with open(results_file, "r") as txt_file:
		stats = [res.strip().split("\n") for res in txt_file.read().split("-" * 20)[:-1]]
	with open("gj.log", "r") as txt_file:
		gj_log = txt_file.read()
	gj_outputs: Dict[str, Set[str]] = dict()
	for query_log in gj_log.strip().split("running query")[1:]:
		newline_idx = query_log.find("\n")
		output = set()
		for elem in re.findall("output.*\n", query_log[newline_idx + 1:])[0][6:].strip()[1:-1].split("),"):
			elem = elem.strip()
			if elem[-1] != ")":
				elem = f"{elem})"
			elem = elem[4:-1]
			elem = elem.replace('"', "").replace("\\", "")
			output.add(elem)
		gj_outputs[query_log[:newline_idx].strip()] = output

	times = []
	timeouts = []
	invalids = []
	for lines in stats:
		query = lines[0][:-4]
		if len(lines) > 4:
			query_res = set(elem.strip().replace('"', "").replace("\\", "") for elem in lines[2].split(' | '))
			if check_validity and not gj_outputs[query].issubset(query_res):
				invalids.append(query)
			else:
				times.append({"query": query, "time": float(lines[-1][:-3]) / 1000})
		else:
			timeouts.append(query)

	gj_json_path = os.path.join(freejoin_path, "gj", "gj.json")
	with open(gj_json_path, "r") as json_file:
		gj_results = json.load(json_file)
	gj_results["ours"] = times
	with open(gj_json_path, "w") as json_file:
		json.dump(gj_results, json_file, indent=2)

	print("# Valid:", len(times))
	print("Invalid:", invalids)
	print("Timeout:", timeouts)
