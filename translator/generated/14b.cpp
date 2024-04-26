#include <iostream>
#include "../../include/load.h"
#include "../../include/build.h"
#include "../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/mi.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/mi_idx.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/kt.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/k.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/it1.csv");

	timer.Reset();
	auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
	build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
	auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
	build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
	auto t_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
	build_trie(t_trie0, t_id, t_kind_id);
	auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
	build_trie(mi_idx_trie0, mi_idx_movie_id, mi_idx_info_type_id);
	auto kt_trie0 = phmap::flat_hash_map<int, vector<int>>();
	build_trie(kt_trie0, kt_id);
	auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
	build_trie(k_trie0, k_id);
	auto it2_trie0 = phmap::flat_hash_map<int, vector<int>>();
	build_trie(it2_trie0, it2_id);
	auto it1_trie0 = phmap::flat_hash_map<int, vector<int>>();
	build_trie(it1_trie0, it1_id);

	vector<tuple<int, int, string, string>> res;
	for (const auto &[x0, mi_trie1]: mi_trie0) {
		if (t_trie0.contains(x0) && mk_trie0.contains(x0) && mi_idx_trie0.contains(x0)) {
			auto &t_trie1 = t_trie0.at(x0);
			auto &mk_trie1 = mk_trie0.at(x0);
			auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
			for (const auto &[x1, t_trie2]: t_trie1) {
				if (kt_trie0.contains(x1)) {
					auto &kt_trie1 = kt_trie0.at(x1);
					for (const auto &[x2, mk_trie2]: mk_trie1) {
						if (k_trie0.contains(x2)) {
							auto &k_trie1 = k_trie0.at(x2);
							for (const auto &[x3, mi_idx_trie2]: mi_idx_trie1) {
								if (it2_trie0.contains(x3)) {
									auto &it2_trie1 = it2_trie0.at(x3);
									for (const auto &[x4, mi_trie2]: mi_trie1) {
										if (it1_trie0.contains(x4)) {
											auto &it1_trie1 = it1_trie0.at(x4);
											for (const auto &mi_off: mi_trie2) {
												for (const auto &mk_off: mk_trie2) {
													for (const auto &t_off: t_trie2) {
														for (const auto &mi_idx_off: mi_idx_trie2) {
															for (const auto &kt_off: kt_trie1) {
																for (const auto &k_off: k_trie1) {
																	for (const auto &it2_off: it2_trie1) {
																		for (const auto &it1_off: it1_trie1) {
																			res.push_back({x0, x4, t_title[t_off], mi_idx_info[mi_idx_off]});
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
	cout << timer.GetElapsedTime() << " ms" << endl;

	cout << res.size() << endl;
}
