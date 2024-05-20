#include <iostream>
#include <limits>
#include "load/12c.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/mi.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/mi_idx.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/it1.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mi_trie0, mi_movie_id, mi_info_type_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id, mi_idx_info_type_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(mc_trie0, mc_movie_id, mc_company_type_id, mc_company_id);
		auto it2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it2_trie0, it2_id);
		auto it1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it1_trie0, it1_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		string mn_mi_idx_info = "zzzzzzzz";
		string mn_cn_name = "zzzzzzzz";
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (mi_idx_trie0.contains(x0) && mi_trie0.contains(x0) && mc_trie0.contains(x0)) {
				auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
				auto &mi_trie1 = mi_trie0.at(x0);
				auto &mc_trie1 = mc_trie0.at(x0);
				for (const auto &[x1, mi_idx_trie2]: mi_idx_trie1) {
					if (it2_trie0.contains(x1)) {
						auto &it2_trie1 = it2_trie0.at(x1);
						for (const auto &[x2, mi_trie2]: mi_trie1) {
							if (it1_trie0.contains(x2)) {
								auto &it1_trie1 = it1_trie0.at(x2);
								for (const auto &[x3, mc_trie2]: mc_trie1) {
									if (ct_trie0.contains(x3)) {
										auto &ct_trie1 = ct_trie0.at(x3);
										for (const auto &[x4, mc_trie3]: mc_trie2) {
											if (cn_trie0.contains(x4)) {
												auto &cn_trie1 = cn_trie0.at(x4);
												for (const auto &t_off: t_trie1) {
													mn_t_title = min(mn_t_title, t_title[t_off]);
												}
												for (const auto &mi_idx_off: mi_idx_trie2) {
													mn_mi_idx_info = min(mn_mi_idx_info, mi_idx_info[mi_idx_off]);
												}
												for (const auto &cn_off: cn_trie1) {
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
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_t_title << " | " << mn_mi_idx_info << " | " << mn_cn_name << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
