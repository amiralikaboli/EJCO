#include <iostream>
#include <limits>
#include "load/1b.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1b/mc.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1b/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1b/it.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1b/ct.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_type_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mi_idx_trie0, mi_idx_movie_id, mi_idx_info_type_id);
		auto it_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it_trie0, it_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(ct_trie0, ct_id);
		timer.StoreElapsedTime(0);

		string mn_mc_note = "zzzzzzzz";
		string mn_t_title = "zzzzzzzz";
		int mn_t_production_year = numeric_limits<int>::max();
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
										mn_mc_note = min(mn_mc_note, mc_note[mc_off]);
									}
									for (const auto &t_off: t_trie1) {
										mn_t_title = min(mn_t_title, t_title[t_off]);
										mn_t_production_year = min(mn_t_production_year, t_production_year[t_off]);
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
			cout << mn_mc_note << " | " << mn_t_title << " | " << mn_t_production_year << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
