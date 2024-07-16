#include <iostream>
#include <vector>
#include <unordered_map>
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

template <int N>
void build_trie(phmap::flat_hash_map<int, small_vector_vecptr<int, N>> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]].push_back(i);
}

void build_trie(phmap::flat_hash_map<int, bool> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]] = true;
}

void build_trie(unordered_multimap<int, int> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie.emplace(attr0[i], i);
}

void build_trie(unordered_map<int, int> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie.emplace(attr0[i], i);
}

void build_trie(unordered_map<int, bool> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie.emplace(attr0[i], true);
}

void build_trie(phmap::flat_hash_map<int, bool> &trie, vector<int> &off, vector<int> &attr0) {
	sort(off.begin(), off.end(), [&attr0](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else return false;
	});
	for (int i = 1; i < off.size(); ++i)
		if (attr0[off[i]] != attr0[off[i - 1]])
			trie[attr0[off[i - 1]]] = true;
	trie[attr0[off.back()]] = true;
}

void build_trie(phmap::flat_hash_map<int, vector<int>> &trie, vector<int> &off, vector<int> &attr0) {
	sort(off.begin(), off.end(), [&attr0](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else return false;
	});
	auto last_val = attr0[off[0]];
	int last_idx = 0;
	for (int i = 1; i < off.size(); ++i)
		if (attr0[off[i]] != last_val) {
			trie.emplace(last_val, vector<int>(off.begin() + last_idx, off.begin() + i));
			last_val = attr0[off[i]];
			last_idx = i;
		}
	trie.emplace(last_val, vector<int>(off.begin() + last_idx, off.end()));
}

void build_trie(phmap::flat_hash_map<int, pair<int, int>> &trie, vector<int> &off, vector<int> &attr0) {
	sort(off.begin(), off.end(), [&attr0](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else return false;
	});
	auto last_val = attr0[off[0]];
	int last_idx = 0;
	for (int i = 1; i < off.size(); ++i)
		if (attr0[off[i]] != last_val) {
			trie.emplace(last_val, make_pair(last_idx, i));
			last_val = attr0[off[i]];
			last_idx = i;
		}
	trie.emplace(last_val, make_pair(last_idx, off.size()));
}


bool build_trie(phmap::flat_hash_map<int, vector<int>> &vtrie, phmap::flat_hash_map<int, int> &itrie, vector<int> &off, vector<int> &attr0) {
	sort(off.begin(), off.end(), [&attr0](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else return false;
	});
	bool isUnique = true;
	for (int i = 1; i < off.size(); ++i)
		if (attr0[off[i]] == attr0[off[i - 1]]) {
			isUnique = false;
			break;
		}
	if (isUnique) {
		for (int i = 0; i < attr0.size(); ++i)
			itrie[attr0[i]] = i;
	} else {
		auto last_val = attr0[off[0]];
		int last_idx = 0;
		for (int i = 1; i < off.size(); ++i)
			if (attr0[off[i]] != last_val) {
				vtrie.emplace(last_val, vector<int>(off.begin() + last_idx, off.begin() + i));
				last_val = attr0[off[i]];
				last_idx = i;
			}
		vtrie.emplace(last_val, vector<int>(off.begin() + last_idx, off.end()));
	}
	return isUnique;
}

bool build_trie(phmap::flat_hash_map<int, pair<int, int>> &vtrie, phmap::flat_hash_map<int, int> &itrie, vector<int> &off, vector<int> &attr0) {
	sort(off.begin(), off.end(), [&attr0](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else return false;
	});
	bool isUnique = true;
	for (int i = 1; i < off.size(); ++i)
		if (attr0[off[i]] == attr0[off[i - 1]]) {
			isUnique = false;
			break;
		}
	if (isUnique) {
		for (int i = 0; i < attr0.size(); ++i)
			itrie[attr0[i]] = i;
	} else {
		auto last_val = attr0[off[0]];
		int last_idx = 0;
		for (int i = 1; i < off.size(); ++i)
			if (attr0[off[i]] != last_val) {
				vtrie.emplace(last_val, make_pair(last_idx, i));
				last_val = attr0[off[i]];
				last_idx = i;
			}
		vtrie.emplace(last_val, make_pair(last_idx, off.size()));
	}
	return isUnique;
}
