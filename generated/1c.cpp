#include <iostream>
#include "../include/load.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1c/mc.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1c/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1c/it.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1c/ct.csv");
	cout << timer.GetElapsedTime() << " ms" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_type_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id, mi_idx_info_type_id);
		auto it_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it_trie0, it_id);
		auto ct_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ct_trie0, ct_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, int, string, string, int>> res;
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (mi_idx_trie0.contains(x0)) {
				auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
				if (mc_trie0.contains(x0)) {
					auto &mc_trie1 = mc_trie0.at(x0);
					for (const auto &[x2, mi_idx_trie2]: mi_idx_trie1) {
						if (it_trie0.contains(x2)) {
							auto &it_trie1 = it_trie0.at(x2);
							for (const auto &[x3, mc_trie2]: mc_trie1) {
								if (ct_trie0.contains(x3)) {
									auto &ct_trie1 = ct_trie0.at(x3);
									for (const auto &mc_off: mc_trie2) {
										for (const auto &t_off: t_trie1) {
											for (const auto &mi_idx_off: mi_idx_trie2) {
												for (const auto &it_off: it_trie1) {
													for (const auto &ct_off: ct_trie1) {
														res.push_back({x0, x2, x3, mc_note[mc_off], t_title[t_off], t_production_year[t_off]});
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
