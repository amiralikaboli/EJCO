#include <iostream>
#include <limits>
#include "load/25b.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/ci.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/n.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/mi.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/k.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/it1.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(ci_trie0, ci_person_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id, mi_idx_info_type_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto it2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it2_trie0, it2_id);
		auto it1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it1_trie0, it1_id);
		timer.StoreElapsedTime(0);

		string mn_n_name = "zzzzz";
		string mn_mi_info = "zzzzz";
		string mn_t_title = "zzzzz";
		string mn_mi_idx_info = "zzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
				for (const auto &[x1, mk_trie1]: mk_trie0) {
					if (t_trie0.contains(x1) && mi_idx_trie0.contains(x1)) {
						auto &t_trie1 = t_trie0.at(x1);
						auto &mi_idx_trie1 = mi_idx_trie0.at(x1);
						if (mi_trie0.contains(x1)) {
							auto &mi_trie1 = mi_trie0.at(x1);
							for (const auto &[x3, mk_trie2]: mk_trie1) {
								if (k_trie0.contains(x3)) {
									auto &k_trie1 = k_trie0.at(x3);
									for (const auto &[x4, mi_idx_trie2]: mi_idx_trie1) {
										if (it2_trie0.contains(x4)) {
											auto &it2_trie1 = it2_trie0.at(x4);
											for (const auto &[x5, mi_trie2]: mi_trie1) {
												if (it1_trie0.contains(x5)) {
													auto &it1_trie1 = it1_trie0.at(x5);
													if (ci_trie1.contains(x1)) {
														auto &ci_trie2 = ci_trie1.at(x1);
														for (const auto &ci_off: ci_trie2) {
															for (const auto &n_off: n_trie1) {
																for (const auto &mi_off: mi_trie2) {
																	for (const auto &mk_off: mk_trie2) {
																		for (const auto &t_off: t_trie1) {
																			for (const auto &mi_idx_off: mi_idx_trie2) {
																				for (const auto &k_off: k_trie1) {
																					for (const auto &it2_off: it2_trie1) {
																						for (const auto &it1_off: it1_trie1) {
																							mn_n_name = min(mn_n_name, n_name[n_off]);
																							mn_mi_info = min(mn_mi_info, mi_info[mi_off]);
																							mn_t_title = min(mn_t_title, t_title[t_off]);
																							mn_mi_idx_info = min(mn_mi_idx_info, mi_idx_info[mi_idx_off]);
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
					}
				}
			}
		}
		timer.StoreElapsedTime(1);
		cerr << "*" << " ";
		if (z == 0)
			cout << mn_n_name << " | " << mn_mi_info << " | " << mn_t_title << " | " << mn_mi_idx_info << endl;
	}
	cerr << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
