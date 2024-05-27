import enum
import json
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


def rel_wo_idx(rel):
	if rel[-1].isdigit():
		return rel[:-1]
	return rel


def perm2str(perm):
	return ", ".join(perm)


with open("utils/abbr2rel.json", 'r') as json_file:
	abbr2rel = json.load(json_file)
with open("utils/rel2col2type.json", 'r') as json_file:
	rel2col2type = json.load(json_file)
with open("results/stats.json", 'r') as json_file:
	query2rel2perm2stats = json.load(json_file)

inf_values = {
	"int": "numeric_limits<int>::max()",
	"string": '"zzzzzzzz"'
}
