#include <iostream>
#include <vector>
#include "parallel_hashmap/phmap.h"
#include "small_vector.h"
#include "small_vector2.h"

using namespace std;

void build_trie(phmap::flat_hash_map<int, int> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]] = i;
}

void build_trie(phmap::flat_hash_map<int, vector<int>> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]].push_back(i);
}

template<int N>
void build_trie(phmap::flat_hash_map<int, sv::small_vector<int, N>> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]].push_back(i);
}

template<int N>
void build_trie(phmap::flat_hash_map<int, small_vector_array<int, N>> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, small_vector_tuple<int>> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, small_vector_fields<int>> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, bool> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]] = true;
}
