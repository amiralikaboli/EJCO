#include "../include/parallel_hashmap/phmap.h"
#include <iostream>
#include <tuple>

using namespace std;

/*
R_trie = sum(<x, y> in R) {x -> {y -> 1}}
S_trie = sum(<y, z> in S) {y -> {z -> 1}}
T_trie = sum(<x, z> in T) {x -> {z -> 1}}
sum(<a, R’> in R_trie)
	let T’ = T_trie(a)
	sum(<b, R_v> in R’)
		let S’ = S_trie(b)
		sum(<c, S_v> in S’)
			let T_v = T’(c)
			{ <a, b, c> -> R_v * S_v * T_v }
*/

int main() {
	srand(time(0));

	auto R_trie = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();  // {x -> {y -> 1}}
	auto S_trie = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();  // {y -> {z -> 1}}
	auto T_trie = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();  // {x -> {z -> 1}}

	for (int i = 0; i < 100; ++i) {
		R_trie[rand() % 100][rand() % 100] = true;
		S_trie[rand() % 100][rand() % 100] = true;
		T_trie[rand() % 100][rand() % 100] = true;
	}

	auto res = phmap::flat_hash_map<tuple<int, int, int>, bool>();
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

	cout << res.size() << endl;
	for (auto &ent: res) {
		auto [a, b, c] = ent.first;
		cout << a << " " << b << " " << c << endl;
	}
}
