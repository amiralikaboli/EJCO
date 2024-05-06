#include <iostream>
#include <limits>
#include "load/15c.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15c/mi.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15c/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_k("/Users/s2522996/Documents/free-join/data/imdb_csv/keyword.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15c/it1.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15c/cn.csv");
	load_at("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_title.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_type_id, mc_company_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto it1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it1_trie0, it1_id);
		auto ct_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto at_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(at_trie0, at_movie_id);
		timer.StoreElapsedTime(0);

		string mn_mi_info = "zzzzz";
		string mn_t_title = "zzzzz";
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (t_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				if (mi_trie0.contains(x0) && mc_trie0.contains(x0)) {
					auto &mi_trie1 = mi_trie0.at(x0);
					auto &mc_trie1 = mc_trie0.at(x0);
					for (const auto &[x2, mk_trie2]: mk_trie1) {
						if (k_trie0.contains(x2)) {
							auto &k_trie1 = k_trie0.at(x2);
							for (const auto &[x3, mi_trie2]: mi_trie1) {
								if (it1_trie0.contains(x3)) {
									auto &it1_trie1 = it1_trie0.at(x3);
									for (const auto &[x4, mc_trie2]: mc_trie1) {
										if (ct_trie0.contains(x4)) {
											auto &ct_trie1 = ct_trie0.at(x4);
											for (const auto &[x5, mc_trie3]: mc_trie2) {
												if (cn_trie0.contains(x5)) {
													auto &cn_trie1 = cn_trie0.at(x5);
													if (at_trie0.contains(x0)) {
														auto &at_trie1 = at_trie0.at(x0);
														for (const auto &mi_off: mi_trie2) {
															for (const auto &mk_off: mk_trie2) {
																for (const auto &t_off: t_trie1) {
																	for (const auto &mc_off: mc_trie3) {
																		for (const auto &k_off: k_trie1) {
																			for (const auto &it1_off: it1_trie1) {
																				for (const auto &ct_off: ct_trie1) {
																					for (const auto &cn_off: cn_trie1) {
																						for (const auto &at_off: at_trie1) {
																							mn_mi_info = min(mn_mi_info, mi_info[mi_off]);
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
		timer.StoreElapsedTime(1);
		cerr << "*" << " ";
		if (z == 0)
			cout << mn_mi_info << " | " << mn_t_title << endl;
	}
	cerr << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
