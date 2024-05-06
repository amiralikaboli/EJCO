#include <iostream>
#include <limits>
#include "load/29b.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/ci.csv");
	load_chn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/chn.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/rt.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/n.csv");
	load_pi("/Users/s2522996/Documents/free-join/data/imdb_csv/person_info.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	load_it3("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/it3.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/mi.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/it.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/k.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/cn.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/t.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/cct2.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>>();
		build_trie(ci_trie0, ci_person_role_id, ci_role_id, ci_person_id, ci_movie_id);
		auto chn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(chn_trie0, chn_id);
		auto rt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(rt_trie0, rt_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto pi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(pi_trie0, pi_person_id, pi_info_type_id);
		auto an_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an_trie0, an_person_id);
		auto it3_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it3_trie0, it3_id);
		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_info_type_id, mi_movie_id);
		auto it_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it_trie0, it_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_company_id, mc_movie_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto cc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(cc_trie0, cc_subject_id, cc_status_id, cc_movie_id);
		auto cct1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cct1_trie0, cct1_id);
		auto cct2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cct2_trie0, cct2_id);
		timer.StoreElapsedTime(0);

		string mn_chn_name = "zzzzz";
		string mn_n_name = "zzzzz";
		string mn_t_title = "zzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (chn_trie0.contains(x0)) {
				auto &chn_trie1 = chn_trie0.at(x0);
				for (const auto &[x1, ci_trie2]: ci_trie1) {
					if (rt_trie0.contains(x1)) {
						auto &rt_trie1 = rt_trie0.at(x1);
						for (const auto &[x2, pi_trie1]: pi_trie0) {
							if (an_trie0.contains(x2)) {
								auto &an_trie1 = an_trie0.at(x2);
								for (const auto &[x3, pi_trie2]: pi_trie1) {
									if (it3_trie0.contains(x3)) {
										auto &it3_trie1 = it3_trie0.at(x3);
										if (n_trie0.contains(x2)) {
											auto &n_trie1 = n_trie0.at(x2);
											if (ci_trie2.contains(x2)) {
												auto &ci_trie3 = ci_trie2.at(x2);
												for (const auto &[x6, mi_trie1]: mi_trie0) {
													if (it_trie0.contains(x6)) {
														auto &it_trie1 = it_trie0.at(x6);
														for (const auto &[x7, mk_trie1]: mk_trie0) {
															if (k_trie0.contains(x7)) {
																auto &k_trie1 = k_trie0.at(x7);
																for (const auto &[x8, mc_trie1]: mc_trie0) {
																	if (cn_trie0.contains(x8)) {
																		auto &cn_trie1 = cn_trie0.at(x8);
																		for (const auto &[x9, cc_trie1]: cc_trie0) {
																			if (cct1_trie0.contains(x9)) {
																				auto &cct1_trie1 = cct1_trie0.at(x9);
																				for (const auto &[x10, cc_trie2]: cc_trie1) {
																					if (cct2_trie0.contains(x10)) {
																						auto &cct2_trie1 = cct2_trie0.at(x10);
																						for (const auto &[x11, t_trie1]: t_trie0) {
																							if (cc_trie2.contains(x11)) {
																								auto &cc_trie3 = cc_trie2.at(x11);
																								if (mc_trie1.contains(x11)) {
																									auto &mc_trie2 = mc_trie1.at(x11);
																									if (mk_trie1.contains(x11)) {
																										auto &mk_trie2 = mk_trie1.at(x11);
																										if (mi_trie1.contains(x11)) {
																											auto &mi_trie2 = mi_trie1.at(x11);
																											if (ci_trie3.contains(x11)) {
																												auto &ci_trie4 = ci_trie3.at(x11);
																												for (const auto &ci_off: ci_trie4) {
																													for (const auto &chn_off: chn_trie1) {
																														for (const auto &rt_off: rt_trie1) {
																															for (const auto &n_off: n_trie1) {
																																for (const auto &pi_off: pi_trie2) {
																																	for (const auto &an_off: an_trie1) {
																																		for (const auto &it3_off: it3_trie1) {
																																			for (const auto &mi_off: mi_trie2) {
																																				for (const auto &it_off: it_trie1) {
																																					for (const auto &mk_off: mk_trie2) {
																																						for (const auto &k_off: k_trie1) {
																																							for (const auto &mc_off: mc_trie2) {
																																								for (const auto &cn_off: cn_trie1) {
																																									for (const auto &t_off: t_trie1) {
																																										for (const auto &cc_off: cc_trie3) {
																																											for (const auto &cct1_off: cct1_trie1) {
																																												for (const auto &cct2_off: cct2_trie1) {
																																													mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
																																													mn_n_name = min(mn_n_name, n_name[n_off]);
																																													mn_t_title = min(mn_t_title, t_title[t_off]);
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
			cout << mn_chn_name << " | " << mn_n_name << " | " << mn_t_title << endl;
	}
	cerr << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
