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

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> mi_idx_trie0 = {0, mi_idx_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		pair<int, int> it_trie0 = {0, it_offsets.size() - 1};
		build_trie(k_offsets, k_id);
		build_trie(mi_idx_offsets, mi_idx_movie_id);
		build_trie(t_offsets, t_id);
		build_trie(it_offsets, it_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		string mn_mi_idx_info = "zzzzzzzz";
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_keyword_id[mk_off];
			auto k_trie1 = find_range(k_offsets, k_id, x0, k_trie0);
			if (k_trie1.first != -1) {
				auto x1 = mk_movie_id[mk_off];
				auto mi_idx_trie1 = find_range(mi_idx_offsets, mi_idx_movie_id, x1, mi_idx_trie0);
				auto t_trie1 = find_range(t_offsets, t_id, x1, t_trie0);
				if (mi_idx_trie1.first != -1 && t_trie1.first != -1) {
					for (int mi_idx_i = mi_idx_trie1.first; mi_idx_i <= mi_idx_trie1.second; ++mi_idx_i) {
						const auto &mi_idx_off = mi_idx_offsets[mi_idx_i];
						auto x2 = mi_idx_info_type_id[mi_idx_off];
						auto it_trie1 = find_range(it_offsets, it_id, x2, it_trie0);
						if (it_trie1.first != -1) {
							for (int t_i = t_trie1.first; t_i <= t_trie1.second; ++t_i) {
								const auto &t_off = t_offsets[t_i];
								mn_t_title = min(mn_t_title, t_title[t_off]);
							}
							mn_mi_idx_info = min(mn_mi_idx_info, mi_idx_info[mi_idx_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		if (z == 0)
			cout << mn_t_title << " | " << mn_mi_idx_info << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 1; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 1; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 1] << " ms" << endl;
}
