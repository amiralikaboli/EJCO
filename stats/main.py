import json
import os
from collections import defaultdict

import pandas as pd

if __name__ == '__main__':
	here_path = os.path.dirname(os.path.realpath(__file__))
	plans_path = os.path.join(here_path, "..", "plans", "fused")
	freejoin_path = os.path.join(here_path, "..", "..", "free-join")
	preprocessed_data_path = os.path.join(freejoin_path, "queries", "preprocessed", "join-order-benchmark", "data")
	raw_data_path = os.path.join(freejoin_path, "data", "imdb")

	with open(os.path.join(here_path, "..", "abbr2rel.json"), "r") as json_file:
		abbr2rel = json.load(json_file)

	for filename in os.listdir(plans_path):
		if filename.endswith(".log"):
			query = filename[:-4]
			print(query)
			with open(os.path.join(plans_path, filename), "r") as log_file:
				build_plan = eval(log_file.readlines()[0].strip())

			stats = defaultdict(dict)
			for rel, _, _ in build_plan:
				if os.path.exists(os.path.join(preprocessed_data_path, query, f"{rel}.csv")):
					df = pd.read_parquet(os.path.join(preprocessed_data_path, query, f"{rel}.parquet"))
				else:
					df = pd.read_parquet(
						os.path.join(raw_data_path, f"{abbr2rel[rel if not rel[-1].isdigit() else rel[:-1]]}.parquet")
					)

				stats[rel].update({col: int(num) for col, num in dict(df.nunique()).items()})
				stats[rel].update({"rows": len(df)})

			with open(os.path.join(here_path, f"{query}.json"), "w") as stats_file:
				json.dump(stats, stats_file, indent=2)
