#include "parallel_hashmap/phmap.h"
#include "sorting.h"
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void load(string path, vector<pair<long, long>> &tuples, bool reversed = false, bool skip_first_line = false) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	if (skip_first_line)
		getline(in, line);
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		auto lll = stol(token);
		getline(ss, token, '|');
		auto rrr = stol(token);
		if (reversed)
			tuples.push_back({rrr, lll});
		else
			tuples.push_back({lll, rrr});
	}
	in.close();
}

void load(string path, pair<vector<long>, vector<long>> &tuples, bool reversed = false, bool skip_first_line = false) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	if (skip_first_line)
		getline(in, line);
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		auto lll = stol(token);
		getline(ss, token, '|');
		auto rrr = stol(token);
		if (reversed) {
			tuples.first.push_back(rrr);
			tuples.second.push_back(lll);
		} else {
			tuples.first.push_back(lll);
			tuples.second.push_back(rrr);
		}
	}
	in.close();
}

void build_trie(vector<pair<long, long>> &tuples, phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>> &trie) {
	for (auto &ent: tuples)
		trie[ent.first][ent.second] = true;
}

void build_trie(vector<pair<long, long>> &tuples, phmap::flat_hash_map<long, vector<long>> &trie, const size_t size_hint = 0) {
	sort(tuples.begin(), tuples.end(), cmp);
	long last_key = -1;
	vector<long> *last_vec = nullptr;
	for (auto &ent: tuples) {
		if (ent.first != last_key) {
			last_key = ent.first;
			last_vec = &trie[last_key];
			if (size_hint)
				last_vec->reserve(size_hint);
		}
		last_vec->push_back(ent.second);
	}
}

void build_trie(vector<pair<long, long>> &tuples, vector<pair<long, vector<long>>> &trie, const size_t size_hint = 0) {
	sort(tuples.begin(), tuples.end(), cmp);
	long last_key = -1;
	vector<long> *last_vec = nullptr;
	for (auto &ent: tuples) {
		if (ent.first != last_key) {
			last_key = ent.first;
			if (size_hint)
				trie.push_back({last_key, vector<long>(size_hint)});
			else
				trie.push_back({last_key, {}});
			last_vec = &trie.back().second;
		}
		last_vec->push_back(ent.second);
	}
}

void build_trie(vector<pair<long, long>> &tuples, vector<pair<long, long>> &trie) {
	sort(tuples.begin(), tuples.end(), cmp);
	trie = tuples;
}

void build_trie(vector<pair<long, long>> &tuples, phmap::flat_hash_map<long, long> &trie) {
	for (auto &ent: tuples)
		trie[ent.first] = ent.second;
}

void build_trie(vector<pair<long, long>> &tuples, phmap::flat_hash_map<long, pair<int, int>> &trie) {
	sort(tuples.begin(), tuples.end(), cmp);
	auto &last_key = tuples[0].first;
	auto last_i = 0;
	for (int i = 1; i < tuples.size(); ++i) {
		if (tuples[i].first != last_key) {
			trie[last_key] = {last_i, i};
			last_key = tuples[i].first;
			last_i = i;
		}
	}
	trie[last_key] = {last_i, tuples.size()};
}

void build_trie(vector<pair<long, long>> &tuples, vector<tuple<long, int, int>> &trie) {
	sort(tuples.begin(), tuples.end(), cmp);
	auto &last_key = tuples[0].first;
	auto last_i = 0;
	for (int i = 1; i < tuples.size(); ++i) {
		if (tuples[i].first != last_key) {
			trie.push_back({last_key, last_i, i});
			last_key = tuples[i].first;
			last_i = i;
		}
	}
	trie.push_back({last_key, last_i, tuples.size()});
}

void build_trie(pair<vector<long>, vector<long>> &tuples, phmap::flat_hash_map<long, pair<int, int>> &trie) {
	sort(tuples, 0, tuples.first.size() - 1);
	auto &last_key = tuples.first[0];
	auto last_i = 0;
	for (int i = 1; i < tuples.first.size(); ++i) {
		if (tuples.first[i] != last_key) {
			trie[last_key] = {last_i, i};
			last_key = tuples.first[i];
			last_i = i;
		}
	}
	trie[last_key] = {last_i, tuples.first.size()};
}

void build_trie(pair<vector<long>, vector<long>> &tuples, vector<tuple<long, int, int>> &trie) {
	sort(tuples, 0, tuples.first.size() - 1);
	auto &last_key = tuples.first[0];
	auto last_i = 0;
	for (int i = 1; i < tuples.first.size(); ++i) {
		if (tuples.first[i] != last_key) {
			trie.push_back({last_key, last_i, i});
			last_key = tuples.first[i];
			last_i = i;
		}
	}
	trie.push_back({last_key, last_i, tuples.first.size()});
}

void build_trie(pair<vector<long>, vector<long>> &tuples, vector<pair<long, long>> &trie) {
	sort(tuples, 0, tuples.first.size() - 1);
	for (int i = 0; i < tuples.first.size(); ++i)
		trie.push_back({tuples.first[i], tuples.second[i]});
}

void build_trie(pair<vector<long>, vector<long>> &tuples, phmap::flat_hash_map<long, long> &trie) {
	for (int i = 0; i < tuples.first.size(); ++i)
		trie[tuples.first[i]] = tuples.second[i];
}
