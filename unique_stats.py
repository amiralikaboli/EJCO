import json
import os

import pandas as pd

from consts import raw_data_path, preprocessed_data_path

if __name__ == '__main__':
	stats = dict()

	for filename in sorted(os.listdir(raw_data_path)):
		if filename.endswith('.csv'):
			filepath = os.path.normpath(os.path.join(raw_data_path, filename))
			stats[filename[:-4]] = list(pd.read_csv(filepath, sep='|', header=None, low_memory=False).nunique())
			print(filepath)

	for query in sorted(os.listdir(preprocessed_data_path)):
		dirpath = os.path.normpath(os.path.join(preprocessed_data_path, query))
		if os.path.isdir(dirpath):
			for filename in sorted(os.listdir(dirpath)):
				if filename.endswith('.csv'):
					filepath = os.path.normpath(os.path.join(dirpath, filename))
					stats[f"{query}/{filename[:-4]}"] = list(pd.read_csv(filepath, sep='|', header=None, low_memory=False).nunique())
					print(filepath)

	with open('utils/unique_stats.json', 'w') as json_file:
		json.dump(stats, json_file, indent=2)
