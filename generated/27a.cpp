#include <iostream>
#include <limits>
#include "load/27a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/mi.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/k.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/mc.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/cn.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/t.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/cct2.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/lt.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(mi_trie0, mi_movie_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(k_trie0, k_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(mc_trie0, mc_company_type_id, mc_company_id, mc_movie_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto cc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(cc_trie0, cc_subject_id, cc_status_id, cc_movie_id);
		auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cct1_trie0, cct1_id);
		auto cct2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cct2_trie0, cct2_id);
		auto ml_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(ml_trie0, ml_link_type_id, ml_movie_id);
		auto lt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(lt_trie0, lt_id);
		timer.StoreElapsedTime(0);

		string mn_cn_name = "zzzzzzzz";
		string mn_t_title = "zzzzzzzz";
		string mn_lt_link = "zzzzzzzz";
		for (const auto &[x0, ml_trie1]: ml_trie0) {
			if (lt_trie0.contains(x0)) {
				auto &lt_trie1 = lt_trie0.at(x0);
				for (const auto &[x1, cc_trie1]: cc_trie0) {
					if (cct1_trie0.contains(x1)) {
						auto &cct1_trie1 = cct1_trie0.at(x1);
						for (const auto &[x2, cc_trie2]: cc_trie1) {
							if (cct2_trie0.contains(x2)) {
								auto &cct2_trie1 = cct2_trie0.at(x2);
								for (const auto &[x3, cc_trie3]: cc_trie2) {
									if (ml_trie1.contains(x3) && t_trie0.contains(x3)) {
										auto &ml_trie2 = ml_trie1.at(x3);
										auto &t_trie1 = t_trie0.at(x3);
										for (const auto &[x4, mc_trie1]: mc_trie0) {
											if (ct_trie0.contains(x4)) {
												auto &ct_trie1 = ct_trie0.at(x4);
												for (const auto &[x5, mc_trie2]: mc_trie1) {
													if (cn_trie0.contains(x5)) {
														auto &cn_trie1 = cn_trie0.at(x5);
														if (mc_trie2.contains(x3)) {
															auto &mc_trie3 = mc_trie2.at(x3);
															for (const auto &[x7, mk_trie1]: mk_trie0) {
																if (k_trie0.contains(x7)) {
																	auto &k_trie1 = k_trie0.at(x7);
																	if (mk_trie1.contains(x3) && mi_trie0.contains(x3)) {
																		auto &mk_trie2 = mk_trie1.at(x3);
																		auto &mi_trie1 = mi_trie0.at(x3);
																		for (const auto &cn_off: cn_trie1) {
																			mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
																		}
																		for (const auto &t_off: t_trie1) {
																			mn_t_title = min(mn_t_title, t_title[t_off]);
																		}
																		for (const auto &lt_off: lt_trie1) {
																			mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
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
			cout << mn_cn_name << " | " << mn_t_title << " | " << mn_lt_link << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
