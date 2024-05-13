#include <iostream>
#include <limits>
#include "load/3a.h"
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

		auto mi_trie0 = emhash6::HashMap<int, bool>();
		build_trie_bool(mi_trie0, mi_movie_id);
		auto mk_trie0 = emhash6::HashMap<int, emhash6::HashMap<int, bool>>();
		build_trie_bool(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = emhash6::HashMap<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto k_trie0 = emhash6::HashMap<int, bool>();
		build_trie_bool(k_trie0, k_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		for (const auto &[mk_trie1, _, x0]: mk_trie0) {
			if (t_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				if (mi_trie0.contains(x0)) {
					auto &mi_trie1 = mi_trie0.at(x0);
					for (const auto &[mk_trie2, _, x2]: mk_trie1) {
						if (k_trie0.contains(x2)) {
							auto &k_trie1 = k_trie0.at(x2);
							for (const auto &t_off: t_trie1) {
								mn_t_title = min(mn_t_title, t_title[t_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_t_title << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
