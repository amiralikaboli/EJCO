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

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>>();
		build_trie_bool(ci_trie0, ci_person_role_id, ci_role_id, ci_person_id, ci_movie_id);
		auto chn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(chn_trie0, chn_id);
		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(rt_trie0, rt_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto pi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(pi_trie0, pi_person_id, pi_info_type_id);
		auto an_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(an_trie0, an_person_id);
		auto it3_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it3_trie0, it3_id);
		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mi_trie0, mi_info_type_id, mi_movie_id);
		auto it_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it_trie0, it_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(k_trie0, k_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mc_trie0, mc_company_id, mc_movie_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cn_trie0, cn_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto cc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(cc_trie0, cc_subject_id, cc_status_id, cc_movie_id);
		auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cct1_trie0, cct1_id);
		auto cct2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cct2_trie0, cct2_id);
		timer.StoreElapsedTime(0);

		string mn_chn_name = "zzzzzzzz";
		string mn_n_name = "zzzzzzzz";
		string mn_t_title = "zzzzzzzz";
		for (const auto &[x0, cct1_trie1]: cct1_trie0) {
			if (cc_trie0.contains(x0)) {
				auto &cc_trie1 = cc_trie0.at(x0);
				for (const auto &[x1, cct2_trie1]: cct2_trie0) {
					if (cc_trie1.contains(x1)) {
						auto &cc_trie2 = cc_trie1.at(x1);
						for (const auto &[x2, t_trie1]: t_trie0) {
							if (cc_trie2.contains(x2)) {
								auto &cc_trie3 = cc_trie2.at(x2);
								for (const auto &[x3, cn_trie1]: cn_trie0) {
									if (mc_trie0.contains(x3)) {
										auto &mc_trie1 = mc_trie0.at(x3);
										if (mc_trie1.contains(x2)) {
											auto &mc_trie2 = mc_trie1.at(x2);
											for (const auto &[x5, k_trie1]: k_trie0) {
												if (mk_trie0.contains(x5)) {
													auto &mk_trie1 = mk_trie0.at(x5);
													if (mk_trie1.contains(x2)) {
														auto &mk_trie2 = mk_trie1.at(x2);
														for (const auto &[x7, it_trie1]: it_trie0) {
															if (mi_trie0.contains(x7)) {
																auto &mi_trie1 = mi_trie0.at(x7);
																if (mi_trie1.contains(x2)) {
																	auto &mi_trie2 = mi_trie1.at(x2);
																	for (const auto &[x9, an_trie1]: an_trie0) {
																		if (pi_trie0.contains(x9)) {
																			auto &pi_trie1 = pi_trie0.at(x9);
																			for (const auto &[x10, it3_trie1]: it3_trie0) {
																				if (pi_trie1.contains(x10)) {
																					auto &pi_trie2 = pi_trie1.at(x10);
																					if (n_trie0.contains(x9)) {
																						auto &n_trie1 = n_trie0.at(x9);
																						for (const auto &[x12, chn_trie1]: chn_trie0) {
																							if (ci_trie0.contains(x12)) {
																								auto &ci_trie1 = ci_trie0.at(x12);
																								for (const auto &[x13, rt_trie1]: rt_trie0) {
																									if (ci_trie1.contains(x13)) {
																										auto &ci_trie2 = ci_trie1.at(x13);
																										if (ci_trie2.contains(x9)) {
																											auto &ci_trie3 = ci_trie2.at(x9);
																											if (ci_trie3.contains(x2)) {
																												auto &ci_trie4 = ci_trie3.at(x2);
																												for (const auto &chn_off: chn_trie1) {
																													mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
																												}
																												for (const auto &n_off: n_trie1) {
																													mn_n_name = min(mn_n_name, n_name[n_off]);
																												}
																												for (const auto &t_off: t_trie1) {
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
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_chn_name << " | " << mn_n_name << " | " << mn_t_title << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
