#include <iostream>
#include "18b_load.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/ci.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/n.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/mi.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/mi_idx.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/it1.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(ci_trie0, ci_person_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id, mi_idx_info_type_id);
		auto it2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it2_trie0, it2_id);
		auto it1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it1_trie0, it1_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, int, int, string, string, string>> res;
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
				for (const auto &[x1, t_trie1]: t_trie0) {
					if (mi_idx_trie0.contains(x1)) {
						auto &mi_idx_trie1 = mi_idx_trie0.at(x1);
						if (mi_trie0.contains(x1)) {
							auto &mi_trie1 = mi_trie0.at(x1);
							for (const auto &[x3, mi_idx_trie2]: mi_idx_trie1) {
								if (it2_trie0.contains(x3)) {
									auto &it2_trie1 = it2_trie0.at(x3);
									for (const auto &[x4, mi_trie2]: mi_trie1) {
										if (it1_trie0.contains(x4)) {
											auto &it1_trie1 = it1_trie0.at(x4);
											if (ci_trie1.contains(x1)) {
												auto &ci_trie2 = ci_trie1.at(x1);
												for (const auto &ci_off: ci_trie2) {
													for (const auto &n_off: n_trie1) {
														for (const auto &mi_off: mi_trie2) {
															for (const auto &t_off: t_trie1) {
																for (const auto &mi_idx_off: mi_idx_trie2) {
																	for (const auto &it2_off: it2_trie1) {
																		for (const auto &it1_off: it1_trie1) {
																			res.push_back({x0, x1, x3, x4, mi_info[mi_off], t_title[t_off], mi_idx_info[mi_idx_off]});
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
