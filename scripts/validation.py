import json
import os
import re
import sys
from typing import Dict, Set

from consts import freejoin_path


def normalize(text: str) -> str:
	return text.replace('"', "").replace("\\", "")


if __name__ == '__main__':
	args = sys.argv[1:]
	results_file = args[0]
	check_validity = True
	skip_queries = ["7c"]

	with open(results_file, "r") as txt_file:
		stats = [res.strip().split("\n") for res in txt_file.read().split("-" * 20)[:-1]]
	with open(os.path.join(freejoin_path, "gj.log"), "r") as txt_file:
		gj_log = txt_file.read()
	gj_outputs: Dict[str, Set[str]] = dict()
	for query_log in gj_log.strip().split("running query")[1:]:
		newline_idx = query_log.find("\n")
		output = set()
		for elem in re.findall("output.*\n", query_log[newline_idx + 1:])[0][6:].strip()[1:-1].split("),"):
			elem = elem.strip()
			if elem[-1] != ")":
				elem = f"{elem})"
			output.add(normalize(elem[4:-1]))
		gj_outputs[query_log[:newline_idx].strip()] = output

	times = []
	timeouts = []
	invalids = []
	for lines in stats:
		query = lines[0][:-4]
		if len(lines) > 4:
			query_res = set(normalize(elem.strip()) for elem in lines[2].split(' | '))
			if check_validity and query not in skip_queries and not query_res >= gj_outputs[query]:
				invalids.append(query)
			else:
				times.append({"query": query, "time": float(lines[-1][:-3]) / 1000})
		else:
			timeouts.append(query)

	if not times:
		raise ValueError("No valid results found")

	gj_json_path = os.path.join(freejoin_path, "gj", "gj.json")
	with open(gj_json_path, "r") as json_file:
		gj_results = json.load(json_file)
	gj_results["ours"] = times
	with open(gj_json_path, "w") as json_file:
		json.dump(gj_results, json_file, indent=2)

	print("# Valid:", len(times))
	print("Invalid:", invalids)
	print("Timeout:", timeouts)
