#include <iostream>
#include "../include/load.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/31b/ci.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/31b/n.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/31b/mi.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/31b/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/31b/mc.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/31b/k.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/31b/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/31b/it1.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/31b/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(ci_trie0, ci_person_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id, mi_idx_info_type_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto it2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it2_trie0, it2_id);
		auto it1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it1_trie0, it1_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, int, int, int, int, string, string, string, string>> res;
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
				for (const auto &[x1, mk_trie1]: mk_trie0) {
					if (t_trie0.contains(x1) && mi_idx_trie0.contains(x1)) {
						auto &t_trie1 = t_trie0.at(x1);
						auto &mi_idx_trie1 = mi_idx_trie0.at(x1);
						if (mi_trie0.contains(x1) && mc_trie0.contains(x1)) {
							auto &mi_trie1 = mi_trie0.at(x1);
							auto &mc_trie1 = mc_trie0.at(x1);
							for (const auto &[x3, mk_trie2]: mk_trie1) {
								if (k_trie0.contains(x3)) {
									auto &k_trie1 = k_trie0.at(x3);
									for (const auto &[x4, mi_idx_trie2]: mi_idx_trie1) {
										if (it2_trie0.contains(x4)) {
											auto &it2_trie1 = it2_trie0.at(x4);
											for (const auto &[x5, mi_trie2]: mi_trie1) {
												if (it1_trie0.contains(x5)) {
													auto &it1_trie1 = it1_trie0.at(x5);
													for (const auto &[x6, mc_trie2]: mc_trie1) {
														if (cn_trie0.contains(x6)) {
															auto &cn_trie1 = cn_trie0.at(x6);
															if (ci_trie1.contains(x1)) {
																auto &ci_trie2 = ci_trie1.at(x1);
																for (const auto &ci_off: ci_trie2) {
																	for (const auto &n_off: n_trie1) {
																		for (const auto &mi_off: mi_trie2) {
																			for (const auto &mk_off: mk_trie2) {
																				for (const auto &t_off: t_trie1) {
																					for (const auto &mi_idx_off: mi_idx_trie2) {
																						for (const auto &mc_off: mc_trie2) {
																							for (const auto &k_off: k_trie1) {
																								for (const auto &it2_off: it2_trie1) {
																									for (const auto &it1_off: it1_trie1) {
																										for (const auto &cn_off: cn_trie1) {
																											res.push_back({x0, x1, x3, x4, x5, x6, n_name[n_off], mi_info[mi_off], t_title[t_off], mi_idx_info[mi_idx_off]});
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
