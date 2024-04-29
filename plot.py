import json
import os

if __name__ == '__main__':
	results = []
	with open("results.txt", "r") as txt_file:
		for res in txt_file.read().split("-" * 20)[:-1]:
			lines = res.strip().split("\n")
			results.append({"query": lines[0][:-4], "time": float(lines[-1][:-3]) / 1000})

	gj_json_path = os.path.join(os.path.dirname(__file__), "..", "free-join", "gj", "gj.json")
	with open(gj_json_path, "r") as json_file:
		gj_results = json.load(json_file)
	gj_results["ours"] = results
	with open(gj_json_path, "w") as json_file:
		json.dump(gj_results, json_file, indent=2)
