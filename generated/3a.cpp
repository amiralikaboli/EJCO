#include <iostream>
#include "../include/load.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3a/mi.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3a/t.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3a/k.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mi_trie0, mi_movie_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, string>> res;
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (t_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				if (mi_trie0.contains(x0)) {
					auto &mi_trie1 = mi_trie0.at(x0);
					for (const auto &[x2, mk_trie2]: mk_trie1) {
						if (k_trie0.contains(x2)) {
							auto &k_trie1 = k_trie0.at(x2);
							for (const auto &mi_off: mi_trie1) {
								for (const auto &mk_off: mk_trie2) {
									for (const auto &t_off: t_trie1) {
										for (const auto &k_off: k_trie1) {
											res.push_back({x0, x2, t_title[t_off]});
										}
									}
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);
		cerr << "*" << " ";
		if (z == 0)
			cout << res.size() << endl;
	}

	cerr << endl;
	cout << timer.GetMean(0) << " ms" << endl;
	cout << timer.GetMean(1) << " ms" << endl;
}
