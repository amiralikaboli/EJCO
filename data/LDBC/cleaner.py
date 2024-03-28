import os

import pandas as pd

if __name__ == '__main__':
    SF = "3"
    for filename in os.listdir(SF):
        if filename[-8:] == "_0_0.csv":
            print(filename, "-->", f"{str.lower(filename[:-8])}.csv")
            pd.read_csv(f"{SF}/{filename}", delimiter="|").to_csv(f"{SF}/{str.lower(filename[:-8])}.csv", sep="|", index=False)

    df = pd.read_csv(f"{SF}/comment.csv", delimiter="|")
    date_col = df.columns[1]
    df[date_col] = df.apply(lambda x: x[date_col].replace("-", "").replace("+0000", "").replace("T", "").replace(":", "").replace(".", ""), axis=1)
    df.to_csv(f"{SF}/comment.csv", sep="|", index=False)

    df = pd.read_csv(f"{SF}/post.csv", delimiter="|")
    date_col = df.columns[2]
    df[date_col] = df.apply(lambda x: x[date_col].replace("-", "").replace("+0000", "").replace("T", "").replace(":", "").replace(".", ""), axis=1)
    df.to_csv(f"{SF}/post.csv", sep="|", index=False)
