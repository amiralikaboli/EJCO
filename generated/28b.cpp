#include <iostream>
#include <limits>
#include "load/28b.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/mi.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/it1.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/k.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/mc.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/cn.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/t.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/kt.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/mi_idx.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/it2.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28b/cct2.csv");
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
		build_trie_bool(mc_trie0, mc_company_id, mc_company_type_id, mc_movie_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(ct_trie0, ct_id);
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

		string mn_cn_name = "zzzzzzzz";
		string mn_t_title = "zzzzzzzz";
		string mn_mi_idx_info = "zzzzzzzz";
		for (const auto &[x0, cct1_trie1]: cct1_trie0) {
			if (cc_trie0.contains(x0)) {
				auto &cc_trie1 = cc_trie0.at(x0);
				for (const auto &[x1, cc_trie2]: cc_trie1) {
					if (cct2_trie0.contains(x1)) {
						auto &cct2_trie1 = cct2_trie0.at(x1);
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
													for (const auto &[x6, mc_trie1]: mc_trie0) {
														if (cn_trie0.contains(x6)) {
															auto &cn_trie1 = cn_trie0.at(x6);
															for (const auto &[x7, mc_trie2]: mc_trie1) {
																if (ct_trie0.contains(x7)) {
																	auto &ct_trie1 = ct_trie0.at(x7);
																	if (mc_trie2.contains(x3)) {
																		auto &mc_trie3 = mc_trie2.at(x3);
																		for (const auto &[x9, k_trie1]: k_trie0) {
																			if (mk_trie0.contains(x9)) {
																				auto &mk_trie1 = mk_trie0.at(x9);
																				if (mk_trie1.contains(x3)) {
																					auto &mk_trie2 = mk_trie1.at(x3);
																					for (const auto &[x11, it1_trie1]: it1_trie0) {
																						if (mi_trie0.contains(x11)) {
																							auto &mi_trie1 = mi_trie0.at(x11);
																							if (mi_trie1.contains(x3)) {
																								auto &mi_trie2 = mi_trie1.at(x3);
																								for (const auto &cn_off: cn_trie1) {
																									mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
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
				}
			}
		}
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_cn_name << " | " << mn_t_title << " | " << mn_mi_idx_info << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
