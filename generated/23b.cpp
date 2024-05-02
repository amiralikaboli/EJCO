#include <iostream>
#include "../include/load.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23b/mi.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23b/it1.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23b/k.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23b/cn.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23b/t.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23b/kt.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23b/cct1.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_info_type_id, mi_movie_id);
		auto it1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it1_trie0, it1_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(mc_trie0, mc_company_type_id, mc_company_id, mc_movie_id);
		auto ct_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto t_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(t_trie0, t_kind_id, t_id);
		auto kt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(kt_trie0, kt_id);
		auto cc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(cc_trie0, cc_status_id, cc_movie_id);
		auto cct1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cct1_trie0, cct1_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, int, int, int, int, int, string, string>> res;
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (it1_trie0.contains(x0)) {
				auto &it1_trie1 = it1_trie0.at(x0);
				for (const auto &[x1, mk_trie1]: mk_trie0) {
					if (k_trie0.contains(x1)) {
						auto &k_trie1 = k_trie0.at(x1);
						for (const auto &[x2, mc_trie1]: mc_trie0) {
							if (ct_trie0.contains(x2)) {
								auto &ct_trie1 = ct_trie0.at(x2);
								for (const auto &[x3, mc_trie2]: mc_trie1) {
									if (cn_trie0.contains(x3)) {
										auto &cn_trie1 = cn_trie0.at(x3);
										for (const auto &[x4, t_trie1]: t_trie0) {
											if (kt_trie0.contains(x4)) {
												auto &kt_trie1 = kt_trie0.at(x4);
												for (const auto &[x5, cc_trie1]: cc_trie0) {
													if (cct1_trie0.contains(x5)) {
														auto &cct1_trie1 = cct1_trie0.at(x5);
														for (const auto &[x6, t_trie2]: t_trie1) {
															if (cc_trie1.contains(x6)) {
																auto &cc_trie2 = cc_trie1.at(x6);
																if (mc_trie2.contains(x6)) {
																	auto &mc_trie3 = mc_trie2.at(x6);
																	if (mk_trie1.contains(x6)) {
																		auto &mk_trie2 = mk_trie1.at(x6);
																		if (mi_trie1.contains(x6)) {
																			auto &mi_trie2 = mi_trie1.at(x6);
																			for (const auto &mi_off: mi_trie2) {
																				for (const auto &it1_off: it1_trie1) {
																					for (const auto &mk_off: mk_trie2) {
																						for (const auto &k_off: k_trie1) {
																							for (const auto &mc_off: mc_trie3) {
																								for (const auto &ct_off: ct_trie1) {
																									for (const auto &cn_off: cn_trie1) {
																										for (const auto &t_off: t_trie2) {
																											for (const auto &kt_off: kt_trie1) {
																												for (const auto &cc_off: cc_trie2) {
																													for (const auto &cct1_off: cct1_trie1) {
																														res.push_back({x0, x1, x2, x3, x4, x5, x6, t_title[t_off], kt_kind[kt_off]});
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
