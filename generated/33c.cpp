#include <iostream>
#include <limits>
#include "load/33c.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mc2("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn2("/Users/s2522996/Documents/free-join/data/imdb_csv/company_name.csv");
	load_mc1("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33c/cn1.csv");
	load_t2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33c/t2.csv");
	load_kt2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33c/kt2.csv");
	load_t1("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_kt1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33c/kt1.csv");
	load_mi_idx2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33c/mi_idx2.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33c/it2.csv");
	load_mi_idx1("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33c/it1.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33c/lt.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mc2_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mc2_trie0, mc2_company_id, mc2_movie_id);
		auto cn2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn2_trie0, cn2_id);
		auto mc1_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mc1_trie0, mc1_company_id, mc1_movie_id);
		auto cn1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn1_trie0, cn1_id);
		auto t2_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(t2_trie0, t2_kind_id, t2_id);
		auto kt2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(kt2_trie0, kt2_id);
		auto t1_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(t1_trie0, t1_kind_id, t1_id);
		auto kt1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(kt1_trie0, kt1_id);
		auto mi_idx2_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx2_trie0, mi_idx2_info_type_id, mi_idx2_movie_id);
		auto it2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it2_trie0, it2_id);
		auto mi_idx1_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx1_trie0, mi_idx1_info_type_id, mi_idx1_movie_id);
		auto it1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it1_trie0, it1_id);
		auto ml_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(ml_trie0, ml_link_type_id, ml_movie_id, ml_linked_movie_id);
		auto lt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(lt_trie0, lt_id);
		timer.StoreElapsedTime(0);

		string mn_cn2_name = "zzzzzzzz";
		string mn_cn1_name = "zzzzzzzz";
		string mn_t2_title = "zzzzzzzz";
		string mn_t1_title = "zzzzzzzz";
		string mn_mi_idx2_info = "zzzzzzzz";
		string mn_mi_idx1_info = "zzzzzzzz";
		for (const auto &[x0, mc2_trie1]: mc2_trie0) {
			if (cn2_trie0.contains(x0)) {
				auto &cn2_trie1 = cn2_trie0.at(x0);
				for (const auto &[x1, mc1_trie1]: mc1_trie0) {
					if (cn1_trie0.contains(x1)) {
						auto &cn1_trie1 = cn1_trie0.at(x1);
						for (const auto &[x2, t2_trie1]: t2_trie0) {
							if (kt2_trie0.contains(x2)) {
								auto &kt2_trie1 = kt2_trie0.at(x2);
								for (const auto &[x3, t1_trie1]: t1_trie0) {
									if (kt1_trie0.contains(x3)) {
										auto &kt1_trie1 = kt1_trie0.at(x3);
										for (const auto &[x4, mi_idx2_trie1]: mi_idx2_trie0) {
											if (it2_trie0.contains(x4)) {
												auto &it2_trie1 = it2_trie0.at(x4);
												for (const auto &[x5, mi_idx1_trie1]: mi_idx1_trie0) {
													if (it1_trie0.contains(x5)) {
														auto &it1_trie1 = it1_trie0.at(x5);
														for (const auto &[x6, ml_trie1]: ml_trie0) {
															if (lt_trie0.contains(x6)) {
																auto &lt_trie1 = lt_trie0.at(x6);
																for (const auto &[x7, mi_idx1_trie2]: mi_idx1_trie1) {
																	if (ml_trie1.contains(x7)) {
																		auto &ml_trie2 = ml_trie1.at(x7);
																		for (const auto &[x8, mi_idx2_trie2]: mi_idx2_trie1) {
																			if (ml_trie2.contains(x8)) {
																				auto &ml_trie3 = ml_trie2.at(x8);
																				if (t1_trie1.contains(x7)) {
																					auto &t1_trie2 = t1_trie1.at(x7);
																					if (t2_trie1.contains(x8)) {
																						auto &t2_trie2 = t2_trie1.at(x8);
																						if (mc1_trie1.contains(x7)) {
																							auto &mc1_trie2 = mc1_trie1.at(x7);
																							if (mc2_trie1.contains(x8)) {
																								auto &mc2_trie2 = mc2_trie1.at(x8);
																								for (const auto &cn2_off: cn2_trie1) {
																									mn_cn2_name = min(mn_cn2_name, cn2_name[cn2_off]);
																								}
																								for (const auto &cn1_off: cn1_trie1) {
																									mn_cn1_name = min(mn_cn1_name, cn1_name[cn1_off]);
																								}
																								for (const auto &t2_off: t2_trie2) {
																									mn_t2_title = min(mn_t2_title, t2_title[t2_off]);
																								}
																								for (const auto &t1_off: t1_trie2) {
																									mn_t1_title = min(mn_t1_title, t1_title[t1_off]);
																								}
																								for (const auto &mi_idx2_off: mi_idx2_trie2) {
																									mn_mi_idx2_info = min(mn_mi_idx2_info, mi_idx2_info[mi_idx2_off]);
																								}
																								for (const auto &mi_idx1_off: mi_idx1_trie2) {
																									mn_mi_idx1_info = min(mn_mi_idx1_info, mi_idx1_info[mi_idx1_off]);
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
			}
		}
		timer.StoreElapsedTime(1);
		cerr << "*" << " ";
		if (z == 0)
			cout << mn_cn2_name << " | " << mn_cn1_name << " | " << mn_t2_title << " | " << mn_t1_title << " | " << mn_mi_idx2_info << " | " << mn_mi_idx1_info << endl;
	}
	cerr << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
