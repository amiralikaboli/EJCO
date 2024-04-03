import os

import pandas as pd

if __name__ == '__main__':
    SF = "3"
    for filename in os.listdir(SF):
        if filename[-8:] == "_0_0.csv":
            print(filename, "-->", f"{str.lower(filename[:-8])}.csv")
            pd.read_csv(f"{SF}/{filename}", delimiter="|").to_csv(f"{SF}/{str.lower(filename[:-8])}.csv", sep="|", index=False)
