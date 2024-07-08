#include <iostream>
#include <limits>
#include "load/5c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

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
		int cnt;
		timer.Reset();

		pair<int, int> mi_trie0 = {0, mi_offsets.size() - 1};
		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> it_trie0 = {0, it_offsets.size() - 1};
		pair<int, int> ct_trie0 = {0, ct_offsets.size() - 1};
		build_trie(it_offsets, it_id);
		build_trie(mc_offsets, mc_movie_id);
		build_trie(t_offsets, t_id);
		build_trie(ct_offsets, ct_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		for (int mi_i = mi_trie0.first; mi_i <= mi_trie0.second; ++mi_i) {
			const auto &mi_off = mi_offsets[mi_i];
			auto x0 = mi_info_type_id[mi_off];
			auto it_trie1 = find_range(it_offsets, it_id, x0, it_trie0);
			if (it_trie1.first != -1) {
				auto x1 = mi_movie_id[mi_off];
				auto mc_trie1 = find_range(mc_offsets, mc_movie_id, x1, mc_trie0);
				auto t_trie1 = find_range(t_offsets, t_id, x1, t_trie0);
				if (mc_trie1.first != -1 && t_trie1.first != -1) {
					for (int mc_i = mc_trie1.first; mc_i <= mc_trie1.second; ++mc_i) {
						const auto &mc_off = mc_offsets[mc_i];
						auto x2 = mc_company_type_id[mc_off];
						auto ct_trie1 = find_range(ct_offsets, ct_id, x2, ct_trie0);
						if (ct_trie1.first != -1) {
							for (int t_i = t_trie1.first; t_i <= t_trie1.second; ++t_i) {
								const auto &t_off = t_offsets[t_i];
								mn_t_title = min(mn_t_title, t_title[t_off]);
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
