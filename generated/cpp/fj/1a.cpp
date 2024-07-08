#include <iostream>
#include <limits>
#include "load/1a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1a/mc.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1a/it.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1a/ct.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> mi_idx_trie0 = {0, mi_idx_offsets.size() - 1};
		build_trie(mi_idx_offsets, mi_idx_movie_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_col3;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int t_i = t_trie0.first; t_i <= t_trie0.second; ++t_i) {
			const auto &t_off = t_offsets[t_i];
			auto x0 = t_id[t_off];
			auto mi_idx_trie1 = find_range(mi_idx_offsets, mi_idx_movie_id, x0, mi_idx_trie0);
			if (mi_idx_trie1.first != -1) {
				for (int mi_idx_i = mi_idx_trie1.first; mi_idx_i <= mi_idx_trie1.second; ++mi_idx_i) {
					const auto &mi_idx_off = mi_idx_offsets[mi_idx_i];
					interm0_col0.push_back(t_id[t_off]);
					interm0_col1.push_back(t_title[t_off]);
					interm0_col2.push_back(t_production_year[t_off]);
					interm0_col3.push_back(mi_idx_info_type_id[mi_idx_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> it_trie0 = {0, it_offsets.size() - 1};
		pair<int, int> ct_trie0 = {0, ct_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col0);
		build_trie(it_offsets, it_id);
		build_trie(ct_offsets, ct_id);
		timer.StoreElapsedTime(2);

		string mn_mc_note = "zzzzzzzz";
		string mn_interm0_col1 = "zzzzzzzz";
		int mn_interm0_col2 = numeric_limits<int>::max();
		for (int mc_i = mc_trie0.first; mc_i <= mc_trie0.second; ++mc_i) {
			const auto &mc_off = mc_offsets[mc_i];
			auto x0 = mc_movie_id[mc_off];
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x0, interm0_trie0);
			if (interm0_trie1.first != -1) {
				for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
					const auto &interm0_off = interm0_offsets[interm0_i];
					auto x1 = interm0_col3[interm0_off];
					auto it_trie1 = find_range(it_offsets, it_id, x1, it_trie0);
					if (it_trie1.first != -1) {
						auto x2 = mc_company_type_id[mc_off];
						auto ct_trie1 = find_range(ct_offsets, ct_id, x2, ct_trie0);
						if (ct_trie1.first != -1) {
							mn_mc_note = min(mn_mc_note, mc_note[mc_off]);
							mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
							mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_mc_note << " | " << mn_interm0_col1 << " | " << mn_interm0_col2 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 2; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 2; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 2] << " ms" << endl;
}
