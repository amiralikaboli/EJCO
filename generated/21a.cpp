#include <iostream>
#include <limits>
#include "load/21a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21a/mi.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21a/t.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21a/mc.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21a/lt.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21a/k.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21a/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21a/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mi_trie0, mi_movie_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto ml_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(ml_trie0, ml_movie_id, ml_link_type_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_type_id, mc_company_id);
		auto lt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(lt_trie0, lt_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto ct_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzz";
		string mn_lt_link = "zzzzz";
		string mn_cn_name = "zzzzz";
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (ml_trie0.contains(x0)) {
				auto &ml_trie1 = ml_trie0.at(x0);
				if (mk_trie0.contains(x0)) {
					auto &mk_trie1 = mk_trie0.at(x0);
					if (mi_trie0.contains(x0) && mc_trie0.contains(x0)) {
						auto &mi_trie1 = mi_trie0.at(x0);
						auto &mc_trie1 = mc_trie0.at(x0);
						for (const auto &[x3, ml_trie2]: ml_trie1) {
							if (lt_trie0.contains(x3)) {
								auto &lt_trie1 = lt_trie0.at(x3);
								for (const auto &[x4, mk_trie2]: mk_trie1) {
									if (k_trie0.contains(x4)) {
										auto &k_trie1 = k_trie0.at(x4);
										for (const auto &[x5, mc_trie2]: mc_trie1) {
											if (ct_trie0.contains(x5)) {
												auto &ct_trie1 = ct_trie0.at(x5);
												for (const auto &[x6, mc_trie3]: mc_trie2) {
													if (cn_trie0.contains(x6)) {
														auto &cn_trie1 = cn_trie0.at(x6);
														for (const auto &mi_off: mi_trie1) {
															for (const auto &mk_off: mk_trie2) {
																for (const auto &t_off: t_trie1) {
																	for (const auto &ml_off: ml_trie2) {
																		for (const auto &mc_off: mc_trie3) {
																			for (const auto &lt_off: lt_trie1) {
																				for (const auto &k_off: k_trie1) {
																					for (const auto &ct_off: ct_trie1) {
																						for (const auto &cn_off: cn_trie1) {
																							mn_t_title = min(mn_t_title, t_title[t_off]);
																							mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
																							mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
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
			cout << mn_t_title << " | " << mn_lt_link << " | " << mn_cn_name << endl;
	}
	cerr << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
