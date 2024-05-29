import enum
import json
import os
from typing import Dict, List

freejoin_path = os.path.join(os.path.dirname(__file__), "..", "free-join")
preprocessed_data_path = os.path.join(freejoin_path, "queries", "preprocessed", "join-order-benchmark", "data")
raw_data_path = os.path.join(freejoin_path, "data", "imdb_csv")
include_dir_path = os.path.join(os.path.dirname(__file__), "include")
generated_dir_path = os.path.join(os.path.dirname(__file__), "generated")
plans_path = os.path.join(os.path.dirname(__file__), "plans")


class Templates(enum.Enum):
	TrieVar = "trie"
	XVar = "x"
	OffsetVar = "off"
	AttrVar = "attr"
	MinVar = "mn"
	LoadFunc = "load"
	BuildFunc = "build_trie"
	IntermRel = "interm"
	IntermCol = "col"
	RootRel = "root"


def rel_wo_idx(rel: str) -> str:
	if Templates.IntermRel.value in rel:
		return rel
	if rel[-1].isdigit():
		return rel[:-1]
	return rel


def perm2str(perm: List) -> str:
	return ", ".join(perm)


with open("utils/abbr2rel.json", 'r') as json_file:
	abbr2rel: Dict[str, str] = json.load(json_file)
with open("utils/rel2col2type.json", 'r') as json_file:
	rel2col2type: Dict[str, Dict[str, str]] = json.load(json_file)
with open("results/stats.json", 'r') as json_file:
	query2rel2perm2stats: Dict[str, Dict[str, Dict[str, str]]] = json.load(json_file)

inf_values: Dict[str, str] = {
	"int": "numeric_limits<int>::max()",
	"string": '"zzzzzzzz"'
}
