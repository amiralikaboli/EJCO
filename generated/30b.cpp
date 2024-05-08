#include <iostream>
#include <limits>
#include "load/30b.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30b/ci.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30b/n.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30b/mi.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30b/it1.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30b/k.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30b/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30b/it2.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30b/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30b/cct2.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(ci_trie0, ci_person_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_info_type_id, mi_movie_id);
		auto it1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it1_trie0, it1_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(k_trie0, k_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx_trie0, mi_idx_info_type_id, mi_idx_movie_id);
		auto it2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it2_trie0, it2_id);
		auto cc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(cc_trie0, cc_subject_id, cc_status_id, cc_movie_id);
		auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cct1_trie0, cct1_id);
		auto cct2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cct2_trie0, cct2_id);
		timer.StoreElapsedTime(0);

		string mn_n_name = "zzzzzzzz";
		string mn_mi_info = "zzzzzzzz";
		string mn_t_title = "zzzzzzzz";
		string mn_mi_idx_info = "zzzzzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
				for (const auto &[x1, mi_trie1]: mi_trie0) {
					if (it1_trie0.contains(x1)) {
						auto &it1_trie1 = it1_trie0.at(x1);
						for (const auto &[x2, mk_trie1]: mk_trie0) {
							if (k_trie0.contains(x2)) {
								auto &k_trie1 = k_trie0.at(x2);
								for (const auto &[x3, mi_idx_trie1]: mi_idx_trie0) {
									if (it2_trie0.contains(x3)) {
										auto &it2_trie1 = it2_trie0.at(x3);
										for (const auto &[x4, cc_trie1]: cc_trie0) {
											if (cct1_trie0.contains(x4)) {
												auto &cct1_trie1 = cct1_trie0.at(x4);
												for (const auto &[x5, cc_trie2]: cc_trie1) {
													if (cct2_trie0.contains(x5)) {
														auto &cct2_trie1 = cct2_trie0.at(x5);
														for (const auto &[x6, mi_idx_trie2]: mi_idx_trie1) {
															if (cc_trie2.contains(x6)) {
																auto &cc_trie3 = cc_trie2.at(x6);
																if (t_trie0.contains(x6)) {
																	auto &t_trie1 = t_trie0.at(x6);
																	if (mk_trie1.contains(x6)) {
																		auto &mk_trie2 = mk_trie1.at(x6);
																		if (mi_trie1.contains(x6)) {
																			auto &mi_trie2 = mi_trie1.at(x6);
																			if (ci_trie1.contains(x6)) {
																				auto &ci_trie2 = ci_trie1.at(x6);
																				for (const auto &n_off: n_trie1) {
																					mn_n_name = min(mn_n_name, n_name[n_off]);
																				}
																				for (const auto &mi_off: mi_trie2) {
																					mn_mi_info = min(mn_mi_info, mi_info[mi_off]);
																				}
																				for (const auto &t_off: t_trie1) {
																					mn_t_title = min(mn_t_title, t_title[t_off]);
																				}
																				for (const auto &mi_idx_off: mi_idx_trie2) {
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
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_n_name << " | " << mn_mi_info << " | " << mn_t_title << " | " << mn_mi_idx_info << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
