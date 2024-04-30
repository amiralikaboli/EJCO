#include <iostream>
#include "../include/load.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t1("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_t2("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_lt("/Users/s2522996/Documents/free-join/data/imdb_csv/link_type.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/32b/k.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t1_trie0, t1_id);
		auto ml_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(ml_trie0, ml_movie_id, ml_linked_movie_id, ml_link_type_id);
		auto t2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t2_trie0, t2_id);
		auto lt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(lt_trie0, lt_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, int, int, string, string, string>> res;
		for (const auto &[x0, t1_trie1]: t1_trie0) {
			if (ml_trie0.contains(x0)) {
				auto &ml_trie1 = ml_trie0.at(x0);
				for (const auto &[x1, ml_trie2]: ml_trie1) {
					if (t2_trie0.contains(x1)) {
						auto &t2_trie1 = t2_trie0.at(x1);
						if (mk_trie0.contains(x0)) {
							auto &mk_trie1 = mk_trie0.at(x0);
							for (const auto &[x3, ml_trie3]: ml_trie2) {
								if (lt_trie0.contains(x3)) {
									auto &lt_trie1 = lt_trie0.at(x3);
									for (const auto &[x4, mk_trie2]: mk_trie1) {
										if (k_trie0.contains(x4)) {
											auto &k_trie1 = k_trie0.at(x4);
											for (const auto &mk_off: mk_trie2) {
												for (const auto &t1_off: t1_trie1) {
													for (const auto &ml_off: ml_trie3) {
														for (const auto &t2_off: t2_trie1) {
															for (const auto &lt_off: lt_trie1) {
																for (const auto &k_off: k_trie1) {
																	res.push_back({x0, x1, x3, x4, t1_title[t1_off], t2_title[t2_off], lt_link[lt_off]});
																}
															}
														}
													}
												}
											}
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
