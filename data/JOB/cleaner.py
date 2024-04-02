import pandas as pd

if __name__ == '__main__':
	df = pd.read_csv("title.csv", sep='|', header=None)
	df[[df.columns[0], df.columns[3]]].to_csv("title_compact.csv", sep='|', header=False, index=False)

	df = pd.read_csv("movie_companies.csv", sep='|', header=None)
	df[[df.columns[1], df.columns[0]]].to_csv("movie_companies_compact.csv", sep='|', header=False, index=False)

	df = pd.read_csv("movie_info_idx.csv", sep='|', header=None)
	df[[df.columns[1], df.columns[0]]].to_csv("movie_info_idx_compact.csv", sep='|', header=False, index=False)
