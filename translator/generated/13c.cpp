#include <iostream>
#include "../../include/load.h"
#include "../../include/build.h"
#include "../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/t.csv");
	load_miidx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/kt.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/it2.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/it.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/cn.csv");

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
		auto t_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(t_trie0, t_id, t_kind_id);
		auto miidx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(miidx_trie0, miidx_movie_id, miidx_info_type_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_type_id, mc_company_id);
		auto kt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(kt_trie0, kt_id);
		auto it2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it2_trie0, it2_id);
		auto it_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it_trie0, it_id);
		auto ct_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, string, int, string, int, int, string>> res;
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (t_trie0.contains(x0) && mc_trie0.contains(x0) && miidx_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				auto &mc_trie1 = mc_trie0.at(x0);
				auto &miidx_trie1 = miidx_trie0.at(x0);
				for (const auto &[x1, t_trie2]: t_trie1) {
					if (kt_trie0.contains(x1)) {
						auto &kt_trie1 = kt_trie0.at(x1);
						for (const auto &[x2, mi_trie2]: mi_trie1) {
							if (it2_trie0.contains(x2)) {
								auto &it2_trie1 = it2_trie0.at(x2);
								for (const auto &[x3, miidx_trie2]: miidx_trie1) {
									if (it_trie0.contains(x3)) {
										auto &it_trie1 = it_trie0.at(x3);
										for (const auto &[x4, mc_trie2]: mc_trie1) {
											if (ct_trie0.contains(x4)) {
												auto &ct_trie1 = ct_trie0.at(x4);
												for (const auto &[x5, mc_trie3]: mc_trie2) {
													if (cn_trie0.contains(x5)) {
														auto &cn_trie1 = cn_trie0.at(x5);
														for (const auto &mi_off: mi_trie2) {
															for (const auto &t_off: t_trie2) {
																for (const auto &miidx_off: miidx_trie2) {
																	for (const auto &mc_off: mc_trie3) {
																		for (const auto &kt_off: kt_trie1) {
																			for (const auto &it2_off: it2_trie1) {
																				for (const auto &it_off: it_trie1) {
																					for (const auto &ct_off: ct_trie1) {
																						for (const auto &cn_off: cn_trie1) {
																							res.push_back({x0, x2, t_title[t_off], x3, miidx_info[miidx_off], x4, x5, cn_name[cn_off]});
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
			cout << res.size() << endl;
	}

	cout << timer.GetMean(0) << " ms" << endl;
	cout << timer.GetMean(1) << " ms" << endl;
}
