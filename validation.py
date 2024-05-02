import json
import os

freejoin_path = os.path.join(os.path.dirname(__file__), "..", "free-join")

if __name__ == '__main__':
	with open("results.txt", "r") as txt_file:
		stats = [res.strip().split("\n") for res in txt_file.read().split("-" * 20)[:-1]]

	mx_len = max(len(lines) for lines in stats)
	times = []
	timeouts = []
	invalids = []
	for lines in stats:
		query = lines[0][:-4]
		if len(lines) == mx_len:
			count_res = int(lines[2])
			with open(os.path.join(freejoin_path, "logs", "plan-profiles", f"{query}.json"), "r") as json_file:
				plan_profile = json.load(json_file)
			if count_res != plan_profile["children"][0]["children"][0]["cardinality"]:
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
