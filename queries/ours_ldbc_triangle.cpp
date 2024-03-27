#include "../include/parallel_hashmap/phmap.h"
#include "../include/high_precision_timer.h"
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<pair<long, long>> load(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	getline(in, line);  // skip the first line
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

void load(string path, phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>> &trie) {
	auto tuples = load(path);
	for (auto &ent: tuples) {
		auto [l, r] = ent;
		trie[l][r] = true;
	}
}

void load(string path, phmap::flat_hash_map<long, vector<long>> &trie) {
	auto tuples = load(path);
	for (auto &ent: tuples) {
		auto [l, r] = ent;
		trie[l].push_back(r);
	}
}

void load(string path, vector<pair<long, vector<long>>> &trie) {
	auto tuples = load(path);
	sort(tuples.begin(), tuples.end());
	trie.push_back({tuples[0].first, {tuples[0].second}});
	for (int i = 1; i < tuples.size(); ++i) {
		if (tuples[i].first == tuples[i - 1].first)
			trie.back().second.push_back(tuples[i].second);
		else
			trie.push_back({tuples[i].first, {tuples[i].second}});
	}
}

int main() {
	srand(time(0));

	vector<pair<long, vector<long>>> R_trie;  // {x -> {y -> 1}}
	auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {y -> {z -> 1}}
	auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {z -> 1}}

	load("../data/LDBC/Comment_replyOf_Post.csv", R_trie);
	load("../data/LDBC/Post_hasTag_Tag.csv", S_trie);
	load("../data/LDBC/Comment_hasTag_Tag.csv", T_trie);

	auto timer = HighPrecisionTimer();
	auto iters = 10;
	for (int i = 0; i < iters; ++i) {
		timer.Reset();
		vector<tuple<long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &a = R_ent.first;
			auto &R_prime = R_ent.second;
			if (T_trie.contains(a)) {
				auto &T_prime = T_trie.at(a);
				for (auto &b: R_prime)
					if (S_trie.contains(b)) {
						auto &S_prime = S_trie.at(b);
						for (auto &c: S_prime)
							if (T_prime.contains(c))
								res.push_back(make_tuple(a, b, c));
					}
			}
		}
		timer.StoreElapsedTime(0);
	}
	cout << round(timer.GetMean(0)) << " ms" << endl;

//	cout << res.size() << endl;
//	for (auto &ent: res) {
//		auto [a, b, c] = ent.first;
//		cout << a << " " << b << " " << c << endl;
//	}
}
