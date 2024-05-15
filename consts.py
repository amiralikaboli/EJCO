import enum
import os

freejoin_path = os.path.join(os.path.dirname(__file__), "..", "free-join")
preprocessed_data_path = os.path.join(freejoin_path, "queries", "preprocessed", "join-order-benchmark", "data")
raw_data_path = os.path.join(freejoin_path, "data", "imdb_csv")
include_dir_path = os.path.join(os.path.dirname(__file__), "include")
generated_dir_path = os.path.join(os.path.dirname(__file__), "generated")
plans_path = os.path.join(os.path.dirname(__file__), "plans")


class HashTable(enum.Enum):
	# (hash_map_type, include_path)
	PHMAP = ("phmap::flat_hash_map", "parallel_hashmap/phmap.h")
	EMHASH6 = ("emhash6::HashMap", "emhash6.hpp")


class PlanNode(enum.Enum):
	Query = "Query"
	HashJoin = "HASH_JOIN"
	SeqScan = "SEQ_SCAN"
	Projection = "PROJECTION"
	Filter = "FILTER"
	Aggregate = "SIMPLE_AGGREGATE"
	ChunkScan = "CHUNK_SCAN"
