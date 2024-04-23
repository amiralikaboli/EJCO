#include "parallel_hashmap/phmap.h"
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

void build_trie(phmap::flat_hash_map<int, vector<int>> &trie, vector<int> &vec) {
	for (int i = 0; i < vec.size(); i++)
		trie[vec[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>> &trie, vector<int> &vec1, vector<int> &vec2) {
	for (int i = 0; i < vec1.size(); i++)
		trie[vec1[i]][vec2[i]].push_back(i);
}
