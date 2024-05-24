#include <iostream>
#include <limits>
#include "load/5c.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/mi.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/mc.csv");
	load_it("/Users/s2522996/Documents/free-join/data/imdb_csv/info_type.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/ct.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mi_trie0, mi_movie_id, mi_info_type_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mc_trie0, mc_movie_id, mc_company_type_id);
		auto it_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it_trie0, it_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(ct_trie0, ct_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		for (const auto &[x0, mc_trie1]: mc_trie0) {
			if (mi_trie0.contains(x0) && t_trie0.contains(x0)) {
				auto &mi_trie1 = mi_trie0.at(x0);
				auto &t_trie1 = t_trie0.at(x0);
				for (const auto &[x1, mi_trie2]: mi_trie1) {
					if (it_trie0.contains(x1)) {
						auto &it_trie1 = it_trie0.at(x1);
						for (const auto &[x2, ct_trie1]: ct_trie0) {
							if (mc_trie1.contains(x2)) {
								auto &mc_trie2 = mc_trie1.at(x2);
								for (const auto &t_off: t_trie1) {
									mn_t_title = min(mn_t_title, t_title[t_off]);
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_t_title << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
