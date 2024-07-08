#include <iostream>
#include <vector>
#include "parallel_hashmap/phmap.h"

using namespace std;

void build_trie(phmap::flat_hash_map<int, vector<int>> &trie, vector<int> &attr0){
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>> &trie, vector<int> &attr0, vector<int> &attr1){
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]][attr1[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>> &trie, vector<int> &attr0, vector<int> &attr1, vector<int> &attr2){
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]][attr1[i]][attr2[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>> &trie, vector<int> &attr0, vector<int> &attr1, vector<int> &attr2, vector<int> &attr3){
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]][attr1[i]][attr2[i]][attr3[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, bool> &trie, vector<int> &attr0){
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]] = true;
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>> &trie, vector<int> &attr0, vector<int> &attr1){
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]][attr1[i]] = true;
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>> &trie, vector<int> &attr0, vector<int> &attr1, vector<int> &attr2){
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]][attr1[i]][attr2[i]] = true;
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>> &trie, vector<int> &attr0, vector<int> &attr1, vector<int> &attr2, vector<int> &attr3){
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]][attr1[i]][attr2[i]][attr3[i]] = true;
}
