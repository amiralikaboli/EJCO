#include <iostream>
#include <vector>
#include "parallel_hashmap/phmap.h"

using namespace std;

void build_trie(phmap::flat_hash_map<int, vector<int>> &trie, vector<int> &vec0){
	for (int i = 0; i < vec0.size(); ++i)
		trie[vec0[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>> &trie, vector<int> &vec0, vector<int> &vec1){
	for (int i = 0; i < vec0.size(); ++i)
		trie[vec0[i]][vec1[i]].push_back(i);
}
