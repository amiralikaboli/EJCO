#include <iostream>
#include <limits>
#include "load/4c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4c/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4c/mi_idx.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4c/k.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4c/it.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto it_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it_trie0, it_id);
		string mn_t_title = "zzzzzzzz";
		string mn_mi_idx_info = "zzzzzzzz";
		for (const auto &mk_off: mk_offsets) {
			auto x0 = mk_movie_id[mk_off];
			if (t_trie0.contains(x0) && mi_idx_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
				auto x1 = mk_keyword_id[mk_off];
				if (k_trie0.contains(x1)) {
					auto &k_trie1 = k_trie0.at(x1);
					for (const auto &mi_idx_off: mi_idx_trie1) {
						auto x2 = mi_idx_info_type_id[mi_idx_off];
						if (it_trie0.contains(x2)) {
							auto &it_trie1 = it_trie0.at(x2);
							for (const auto &t_off: t_trie1) {
								mn_t_title = min(mn_t_title, t_title[t_off]);
							}
							mn_mi_idx_info = min(mn_mi_idx_info, mi_idx_info[mi_idx_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		if (z == 0)
			cout << mn_t_title << " | " << mn_mi_idx_info << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 1; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 1; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[1] << " ms" << endl;
}
