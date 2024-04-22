import pandas as pd

if __name__ == '__main__':
	df = pd.read_parquet("../../free-join/queries/preprocessed/join-order-benchmark/data/12a/t.parquet")
	print(df.info())
