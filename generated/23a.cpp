#include <iostream>
#include <limits>
#include "load/23a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/mi.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/it1.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/data/imdb_csv/keyword.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/cn.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/t.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/kt.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/cct1.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mi_trie0, mi_info_type_id, mi_movie_id);
		auto it1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it1_trie0, it1_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(k_trie0, k_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(mc_trie0, mc_company_type_id, mc_company_id, mc_movie_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cn_trie0, cn_id);
		auto t_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(t_trie0, t_kind_id, t_id);
		auto kt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(kt_trie0, kt_id);
		auto cc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(cc_trie0, cc_status_id, cc_movie_id);
		auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cct1_trie0, cct1_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		string mn_kt_kind = "zzzzzzzz";
		for (const auto &[x0, cct1_trie1]: cct1_trie0) {
			if (cc_trie0.contains(x0)) {
				auto &cc_trie1 = cc_trie0.at(x0);
				for (const auto &[x1, kt_trie1]: kt_trie0) {
					if (t_trie0.contains(x1)) {
						auto &t_trie1 = t_trie0.at(x1);
						for (const auto &[x2, cc_trie2]: cc_trie1) {
							if (t_trie1.contains(x2)) {
								auto &t_trie2 = t_trie1.at(x2);
								for (const auto &[x3, ct_trie1]: ct_trie0) {
									if (mc_trie0.contains(x3)) {
										auto &mc_trie1 = mc_trie0.at(x3);
										for (const auto &[x4, mc_trie2]: mc_trie1) {
											if (cn_trie0.contains(x4)) {
												auto &cn_trie1 = cn_trie0.at(x4);
												if (mc_trie2.contains(x2)) {
													auto &mc_trie3 = mc_trie2.at(x2);
													for (const auto &[x6, k_trie1]: k_trie0) {
														if (mk_trie0.contains(x6)) {
															auto &mk_trie1 = mk_trie0.at(x6);
															if (mk_trie1.contains(x2)) {
																auto &mk_trie2 = mk_trie1.at(x2);
																for (const auto &[x8, it1_trie1]: it1_trie0) {
																	if (mi_trie0.contains(x8)) {
																		auto &mi_trie1 = mi_trie0.at(x8);
																		if (mi_trie1.contains(x2)) {
																			auto &mi_trie2 = mi_trie1.at(x2);
																			for (const auto &t_off: t_trie2) {
																				mn_t_title = min(mn_t_title, t_title[t_off]);
																			}
																			for (const auto &kt_off: kt_trie1) {
																				mn_kt_kind = min(mn_kt_kind, kt_kind[kt_off]);
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
			cout << mn_t_title << " | " << mn_kt_kind << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
