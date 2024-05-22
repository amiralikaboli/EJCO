#include <iostream>
#include <limits>
#include "load/26b.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_chn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26b/chn.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26b/k.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26b/t.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26b/kt.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26b/mi_idx.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26b/it2.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26b/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26b/cct2.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(ci_trie0, ci_person_id, ci_person_role_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(n_trie0, n_id);
		auto chn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(chn_trie0, chn_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(k_trie0, k_id);
		auto t_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(t_trie0, t_kind_id, t_id);
		auto kt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(kt_trie0, kt_id);
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

		string mn_chn_name = "zzzzzzzz";
		string mn_t_title = "zzzzzzzz";
		string mn_mi_idx_info = "zzzzzzzz";
		for (const auto &[x0, cct1_trie1]: cct1_trie0) {
			if (cc_trie0.contains(x0)) {
				auto &cc_trie1 = cc_trie0.at(x0);
				for (const auto &[x1, cct2_trie1]: cct2_trie0) {
					if (cc_trie1.contains(x1)) {
						auto &cc_trie2 = cc_trie1.at(x1);
						for (const auto &[x2, it2_trie1]: it2_trie0) {
							if (mi_idx_trie0.contains(x2)) {
								auto &mi_idx_trie1 = mi_idx_trie0.at(x2);
								for (const auto &[x3, cc_trie3]: cc_trie2) {
									if (mi_idx_trie1.contains(x3)) {
										auto &mi_idx_trie2 = mi_idx_trie1.at(x3);
										for (const auto &[x4, kt_trie1]: kt_trie0) {
											if (t_trie0.contains(x4)) {
												auto &t_trie1 = t_trie0.at(x4);
												if (t_trie1.contains(x3)) {
													auto &t_trie2 = t_trie1.at(x3);
													for (const auto &[x6, k_trie1]: k_trie0) {
														if (mk_trie0.contains(x6)) {
															auto &mk_trie1 = mk_trie0.at(x6);
															if (mk_trie1.contains(x3)) {
																auto &mk_trie2 = mk_trie1.at(x3);
																for (const auto &[x8, n_trie1]: n_trie0) {
																	if (ci_trie0.contains(x8)) {
																		auto &ci_trie1 = ci_trie0.at(x8);
																		for (const auto &[x9, ci_trie2]: ci_trie1) {
																			if (chn_trie0.contains(x9)) {
																				auto &chn_trie1 = chn_trie0.at(x9);
																				if (ci_trie2.contains(x3)) {
																					auto &ci_trie3 = ci_trie2.at(x3);
																					for (const auto &chn_off: chn_trie1) {
																						mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
																					}
																					for (const auto &t_off: t_trie2) {
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
		}
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_chn_name << " | " << mn_t_title << " | " << mn_mi_idx_info << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
