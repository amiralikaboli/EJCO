#include <iostream>
#include "load/24b.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/ci.csv");
	load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/rt.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/n.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/mi.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/k.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/it.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/cn.csv");
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
		auto an_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an_trie0, an_person_id);
		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto it_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it_trie0, it_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, int, int, int, int, int, string, string, string>> res;
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (chn_trie0.contains(x0)) {
				auto &chn_trie1 = chn_trie0.at(x0);
				for (const auto &[x1, ci_trie2]: ci_trie1) {
					if (rt_trie0.contains(x1)) {
						auto &rt_trie1 = rt_trie0.at(x1);
						for (const auto &[x2, n_trie1]: n_trie0) {
							if (an_trie0.contains(x2)) {
								auto &an_trie1 = an_trie0.at(x2);
								if (ci_trie2.contains(x2)) {
									auto &ci_trie3 = ci_trie2.at(x2);
									for (const auto &[x4, mk_trie1]: mk_trie0) {
										if (t_trie0.contains(x4)) {
											auto &t_trie1 = t_trie0.at(x4);
											if (mi_trie0.contains(x4) && mc_trie0.contains(x4)) {
												auto &mi_trie1 = mi_trie0.at(x4);
												auto &mc_trie1 = mc_trie0.at(x4);
												for (const auto &[x6, mk_trie2]: mk_trie1) {
													if (k_trie0.contains(x6)) {
														auto &k_trie1 = k_trie0.at(x6);
														for (const auto &[x7, mi_trie2]: mi_trie1) {
															if (it_trie0.contains(x7)) {
																auto &it_trie1 = it_trie0.at(x7);
																for (const auto &[x8, mc_trie2]: mc_trie1) {
																	if (cn_trie0.contains(x8)) {
																		auto &cn_trie1 = cn_trie0.at(x8);
																		if (ci_trie3.contains(x4)) {
																			auto &ci_trie4 = ci_trie3.at(x4);
																			for (const auto &ci_off: ci_trie4) {
																				for (const auto &chn_off: chn_trie1) {
																					for (const auto &rt_off: rt_trie1) {
																						for (const auto &n_off: n_trie1) {
																							for (const auto &an_off: an_trie1) {
																								for (const auto &mi_off: mi_trie2) {
																									for (const auto &mk_off: mk_trie2) {
																										for (const auto &t_off: t_trie1) {
																											for (const auto &mc_off: mc_trie2) {
																												for (const auto &k_off: k_trie1) {
																													for (const auto &it_off: it_trie1) {
																														for (const auto &cn_off: cn_trie1) {
																															res.push_back({x0, x1, x2, x4, x6, x7, x8, chn_name[chn_off], n_name[n_off], t_title[t_off]});
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
			cout << res.size() << endl;
	}

	cerr << endl;
	cout << timer.GetMean(0) << " ms" << endl;
	cout << timer.GetMean(1) << " ms" << endl;
}
