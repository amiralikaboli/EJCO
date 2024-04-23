#include <iostream>
#include "../../include/load.h"
#include "../../include/build.h"
#include "../../include/parallel_hashmap/phmap.h"

using namespace std;

int main() {
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3a/mi.csv");
	auto mi_trie0 = phmap::flat_hash_map<int, vector<int>>();
	build_trie(mi_trie0, mi_movie_id);
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
	build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3a/t.csv");
	auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
	build_trie(t_trie0, t_id);
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3a/k.csv");
	auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
	build_trie(k_trie0, k_id);
	vector<tuple < int, int, string>> res;
	for (const auto &[x0, mi_trie1]: mi_trie0) {
		if (mk_trie0.contains(x0) && t_trie0.contains(x0)) {
			auto &mk_trie1 = mk_trie0.at(x0);
			auto &t_trie1 = t_trie0.at(x0);
			for (const auto &[x1, mk_trie2]: mk_trie1) {
				if (k_trie0.contains(x1)) {
					auto &k_trie1 = k_trie0.at(x1);
					for (const auto &mi_off: mi_trie1) {
						for (const auto &mk_off: mk_trie2) {
							for (const auto &t_off: t_trie1) {
								for (const auto &k_off: k_trie1) {
									res.push_back({x0, x1, t_title[t_off]});
								}
							}
						}
					}
				}
			}
		}
	}
	cerr << res.size() << endl;
}
