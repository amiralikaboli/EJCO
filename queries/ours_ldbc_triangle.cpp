#include "../include/parallel_hashmap/phmap.h"
#include "../include/high_precision_timer.h"
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>

using namespace std;

void load(string path, phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>> &trie) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	getline(in, line);  // skip the first line
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		auto lll = stol(token);
		getline(ss, token, '|');
		auto rrr = stol(token);
		trie[lll][rrr] = true;
	}
	in.close();
}

int main() {
	srand(time(0));

	auto R_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {y -> 1}}
	auto S_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {y -> {z -> 1}}
	auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {z -> 1}}

	load("../data/LDBC/Comment_replyOf_Post.csv", R_trie);
	load("../data/LDBC/Post_hasTag_Tag.csv", S_trie);
	load("../data/LDBC/Comment_hasTag_Tag.csv", T_trie);

	auto timer = HighPrecisionTimer();
	auto cnt = 100;
	while (cnt--) {
		auto res = phmap::flat_hash_map<tuple<long, long, long>, bool>();
		for (auto &R_ent: R_trie) {
			auto a = R_ent.first;
			auto R_prime = R_ent.second;
			if (T_trie.contains(a)) {
				auto T_prime = T_trie.at(a);
				for (auto &r_ent: R_prime) {
					auto b = r_ent.first;
					if (S_trie.contains(b)) {
						auto S_prime = S_trie.at(b);
						for (auto &s_ent: S_prime) {
							auto c = s_ent.first;
							if (T_prime.contains(c))
								res[make_tuple(a, b, c)] = true;
						}
					}
				}
			}
		}
	}
	timer.PrintElapsedTimeAndReset("Triangle");

//	cout << res.size() << endl;
//	for (auto &ent: res) {
//		auto [a, b, c] = ent.first;
//		cout << a << " " << b << " " << c << endl;
//	}
}
