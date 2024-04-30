#include <iostream>
#include <vector>
#include "parallel_hashmap/phmap.h"

using namespace std;

void build_trie(phmap::flat_hash_map<int, vector<int>> &trie, vector<int> &attr0) {
	vector<int> off(attr0.size());
	for (int i = 0; i < attr0.size(); ++i)
		off[i] = i;
	sort(off.begin(), off.end(), [&attr0](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else return false;
	});
	for (int i = 0; i < off.size(); ++i) {
		const auto &o = off[i];
		trie[attr0[o]].push_back(o);
	}
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>> &trie, vector<int> &attr0, vector<int> &attr1) {
	vector<int> off(attr0.size());
	for (int i = 0; i < attr0.size(); ++i)
		off[i] = i;
	sort(off.begin(), off.end(), [&attr0, &attr1](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else if (attr0[i] > attr0[j]) return false;
		if (attr1[i] < attr1[j]) return true;
		else return false;
	});
	for (int i = 0; i < off.size(); ++i) {
		const auto &o = off[i];
		trie[attr0[o]][attr1[o]].push_back(o);
	}
}

void build_trie(phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>> &trie, vector<int> &attr0, vector<int> &attr1, vector<int> &attr2) {
	vector<int> off(attr0.size());
	for (int i = 0; i < attr0.size(); ++i)
		off[i] = i;
	sort(off.begin(), off.end(), [&attr0, &attr1, &attr2](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else if (attr0[i] > attr0[j]) return false;
		if (attr1[i] < attr1[j]) return true;
		else if (attr1[i] > attr1[j]) return false;
		if (attr2[i] < attr2[j]) return true;
		else return false;
	});
	for (int i = 0; i < off.size(); ++i) {
		const auto &o = off[i];
		trie[attr0[o]][attr1[o]][attr2[o]].push_back(o);
	}
}
