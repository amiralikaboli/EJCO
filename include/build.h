#include "parallel_hashmap/phmap.h"
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<pair<long, long>> load(string path, bool skip_first_line = false) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	if (skip_first_line)
		getline(in, line);
	vector<pair<long, long>> tuples;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		auto lll = stol(token);
		getline(ss, token, '|');
		auto rrr = stol(token);
		tuples.push_back({lll, rrr});
	}
	in.close();
	return tuples;
}

void build_trie(vector<pair<long, long>> &tuples, phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>> &trie) {
	for (auto &ent: tuples)
		trie[ent.first][ent.second] = true;
}

void build_trie(vector<pair<long, long>> &tuples, phmap::flat_hash_map<long, vector<long>> &trie, bool sorted = true) {
	if (sorted) {
		sort(tuples.begin(), tuples.end());
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

void build_trie(vector<pair<long, long>> &tuples, vector<pair<long, vector<long>>> &trie) {
	sort(tuples.begin(), tuples.end());
	trie.push_back({tuples[0].first, {tuples[0].second}});
	for (int i = 1; i < tuples.size(); ++i) {
		if (tuples[i].first == tuples[i - 1].first)
			trie.back().second.push_back(tuples[i].second);
		else
			trie.push_back({tuples[i].first, {tuples[i].second}});
	}
}