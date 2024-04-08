#include "parallel_hashmap/phmap.h"
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int partition(pair<vector<long>, vector<long>> &tuples, int low, int high) {
	int pivot_idx = (high + low) >> 1;
	long pivot = tuples.first[pivot_idx];
	swap(tuples.first[pivot_idx], tuples.first[high]);
	swap(tuples.second[pivot_idx], tuples.second[high]);
	int i = low - 1;

	for (int j = low; j <= high - 1; ++j) {
		if (tuples.first[j] < pivot) {
			++i;
			swap(tuples.first[i], tuples.first[j]);
			swap(tuples.second[i], tuples.second[j]);
		}
	}
	swap(tuples.first[i + 1], tuples.first[high]);
	swap(tuples.second[i + 1], tuples.second[high]);
	return i + 1;
}

void insertion_sort(std::pair<std::vector<long>, std::vector<long>>& tuples, int low, int high) {
	for (int i = low + 1; i <= high; i++) {
		long key1 = tuples.first[i];
		long key2 = tuples.second[i];
		int j = i - 1;
		while (j >= low && tuples.first[j] > key1) {
			tuples.first[j + 1] = tuples.first[j];
			tuples.second[j + 1] = tuples.second[j];
			j--;
		}
		tuples.first[j + 1] = key1;
		tuples.second[j + 1] = key2;
	}
}

void sort(pair<vector<long>, vector<long>> &tuples, int low, int high) {
	if (high - low < 50) {
		insertion_sort(tuples, low, high);
	} else {
		int pi = partition(tuples, low, high);
		sort(tuples, low, pi - 1);
		sort(tuples, pi + 1, high);
	}
}

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

bool cmp(const pair<long, long> &a, const pair<long, long> &b) {
	return a.first < b.first;
}

void build_trie(vector<pair<long, long>> &tuples, phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>> &trie) {
	for (auto &ent: tuples)
		trie[ent.first][ent.second] = true;
}

void build_trie(vector<pair<long, long>> &tuples, phmap::flat_hash_map<long, vector<long>> &trie, bool sorted = true) {
	if (sorted) {
		sort(tuples.begin(), tuples.end(), cmp);
		long last_key = -1;
		vector<long> *last_vec = nullptr;
		for (auto &ent: tuples) {
			if (ent.first != last_key) {
				last_key = ent.first;
				last_vec = &trie[last_key];
			}
			last_vec->push_back(ent.second);
		}
	} else {
		for (auto &ent: tuples)
			trie[ent.first].push_back(ent.second);
	}
}

void build_trie(vector<pair<long, long>> &tuples, vector<pair<long, vector<long>>> &trie, bool flag = false) {
	sort(tuples.begin(), tuples.end(), cmp);
	if (flag) {
		long last_key = -1;
		vector<long> *last_vec = nullptr;
		for (auto &ent: tuples) {
			if (ent.first != last_key) {
				last_key = ent.first;
				trie.push_back({last_key, {}});
				last_vec = &trie.back().second;
			}
			last_vec->push_back(ent.second);
		}
	} else {
		trie.push_back({tuples[0].first, {tuples[0].second}});
		for (int i = 1; i < tuples.size(); ++i) {
			if (tuples[i].first == tuples[i - 1].first)
				trie.back().second.push_back(tuples[i].second);
			else
				trie.push_back({tuples[i].first, {tuples[i].second}});
		}
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
