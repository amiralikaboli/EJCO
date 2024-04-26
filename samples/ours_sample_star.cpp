#include "../include/parallel_hashmap/phmap.h"
#include <iostream>
#include <tuple>

using namespace std;

/*
R_trie = sum(<x, a> in R) {x -> {a -> 1}}
S_trie = sum(<x, b> in S) {x -> {b -> 1}}
T_trie = sum(<x, c> in T) {x -> {c -> 1}}
sum(<x, R’> in R_trie)
	let S' = S_trie(x)
 	let T' = T_trie(x)
	sum(<a, R_v> in R’)
 		sum(<b, S_v> in S’)
			sum(<c, T_v> in T’)
				{ <a, b, c> -> R_v * S_v * T_v }
*/

int main() {
	srand(time(0));

	auto R_trie = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();  // {x -> {a -> 1}}
	auto S_trie = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();  // {x -> {b -> 1}}
	auto T_trie = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();  // {x -> {c -> 1}}

	for (int i = 0; i < 100; ++i) {
		R_trie[rand() % 100][rand() % 100] = true;
		S_trie[rand() % 100][rand() % 100] = true;
		T_trie[rand() % 100][rand() % 100] = true;
	}

	auto res = phmap::flat_hash_map<tuple<int, int, int, int>, bool>();
	for (auto &R_ent: R_trie) {
		auto x = R_ent.first;
		auto R_prime = R_ent.second;
		if (S_trie.contains(x) && T_trie.contains(x)) {
			auto S_prime = S_trie.at(x);
			auto T_prime = T_trie.at(x);
			for (auto &r_ent: R_prime) {
				auto a = r_ent.first;
				for (auto &s_ent: S_prime) {
					auto b = s_ent.first;
					for (auto &t_ent: T_prime) {
						auto c = t_ent.first;
						res[make_tuple(x, a, b, c)] = true;
					}
				}
			}
		}
	}

	cout << res.size() << endl;
	for (auto &ent: res) {
		auto [x, a, b, c] = ent.first;
		cout << x << " " << a << " " << b << " " << c << endl;
	}
}
