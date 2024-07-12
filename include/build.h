#include <iostream>
#include <vector>
#include "parallel_hashmap/phmap.h"
#include "small_vector.h"

using namespace std;

void build_trie(phmap::flat_hash_map<int, vector<int>> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]].push_back(i);
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

template<int N>
void build_trie(phmap::flat_hash_map<int, sv::small_vector<int, N>> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]].push_back(i);
}

template<int N>
void build_trie(phmap::flat_hash_map<int, sv::small_vector<int, N>> &trie, vector<int> &off, vector<int> &attr0) {
	sort(off.begin(), off.end(), [&attr0](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else return false;
	});
	auto last_val = attr0[off[0]];
	auto last_idx = 0;
	for (int i = 1; i < off.size(); ++i)
		if (attr0[off[i]] != last_val) {
			trie.emplace(last_val, sv::small_vector<int, N>(off.begin() + last_idx, off.begin() + i));
			last_val = attr0[off[i]];
			last_idx = i;
		}
	trie.emplace(last_val, sv::small_vector<int, N>(off.begin() + last_idx, off.end()));
}

void build_trie(phmap::flat_hash_map<int, bool> &trie, vector<int> &attr0) {
	for (int i = 0; i < attr0.size(); ++i)
		trie[attr0[i]] = true;
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
