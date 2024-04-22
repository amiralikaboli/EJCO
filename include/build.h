#include "parallel_hashmap/phmap.h"
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

void build_trie(phmap::flat_hash_map<int, vector<int>> &trie, vector<int> &vec) {
	for (int i = 0; i < vec.size(); i++)
		trie[vec[i]].push_back(i);
}
