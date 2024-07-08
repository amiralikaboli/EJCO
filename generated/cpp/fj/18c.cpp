#include <iostream>
#include <limits>
#include "load/18c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/mi.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/it1.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/ci.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/n.csv");
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
		vector<string> interm0_col3;
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
					interm0_col2.push_back(mi_idx_info_type_id[mi_idx_off]);
					interm0_col3.push_back(mi_idx_info[mi_idx_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> mi_trie0 = {0, mi_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> it2_trie0 = {0, it2_offsets.size() - 1};
		pair<int, int> it1_trie0 = {0, it1_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col0);
		build_trie(it2_offsets, it2_id);
		build_trie(it1_offsets, it1_id);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<string> interm1_col2;
		vector<int> interm1_col3;
		vector<string> interm1_col4;
		vector<string> interm1_col5;
		vector<int> interm1_offsets;
		cnt = 0;
		for (int mi_i = mi_trie0.first; mi_i <= mi_trie0.second; ++mi_i) {
			const auto &mi_off = mi_offsets[mi_i];
			auto x0 = mi_movie_id[mi_off];
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x0, interm0_trie0);
			if (interm0_trie1.first != -1) {
				for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
					const auto &interm0_off = interm0_offsets[interm0_i];
					auto x1 = interm0_col2[interm0_off];
					auto it2_trie1 = find_range(it2_offsets, it2_id, x1, it2_trie0);
					if (it2_trie1.first != -1) {
						auto x2 = mi_info_type_id[mi_off];
						auto it1_trie1 = find_range(it1_offsets, it1_id, x2, it1_trie0);
						if (it1_trie1.first != -1) {
							interm1_col0.push_back(mi_movie_id[mi_off]);
							interm1_col1.push_back(mi_info_type_id[mi_off]);
							interm1_col2.push_back(mi_info[mi_off]);
							interm1_col3.push_back(interm0_col2[interm0_off]);
							interm1_col4.push_back(interm0_col1[interm0_off]);
							interm1_col5.push_back(interm0_col3[interm0_off]);
							interm1_offsets.push_back(cnt++);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		pair<int, int> ci_trie0 = {0, ci_offsets.size() - 1};
		pair<int, int> n_trie0 = {0, n_offsets.size() - 1};
		pair<int, int> interm1_trie0 = {0, interm1_offsets.size() - 1};
		build_trie(interm1_offsets, interm1_col0);
		build_trie(n_offsets, n_id);
		timer.StoreElapsedTime(4);

		string mn_interm1_col2 = "zzzzzzzz";
		string mn_interm1_col4 = "zzzzzzzz";
		string mn_interm1_col5 = "zzzzzzzz";
		for (int ci_i = ci_trie0.first; ci_i <= ci_trie0.second; ++ci_i) {
			const auto &ci_off = ci_offsets[ci_i];
			auto x0 = ci_movie_id[ci_off];
			auto interm1_trie1 = find_range(interm1_offsets, interm1_col0, x0, interm1_trie0);
			if (interm1_trie1.first != -1) {
				auto x1 = ci_person_id[ci_off];
				auto n_trie1 = find_range(n_offsets, n_id, x1, n_trie0);
				if (n_trie1.first != -1) {
					for (int interm1_i = interm1_trie1.first; interm1_i <= interm1_trie1.second; ++interm1_i) {
						const auto &interm1_off = interm1_offsets[interm1_i];
						mn_interm1_col2 = min(mn_interm1_col2, interm1_col2[interm1_off]);
						mn_interm1_col4 = min(mn_interm1_col4, interm1_col4[interm1_off]);
						mn_interm1_col5 = min(mn_interm1_col5, interm1_col5[interm1_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		if (z == 0)
			cout << mn_interm1_col2 << " | " << mn_interm1_col4 << " | " << mn_interm1_col5 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 3; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 3; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 3] << " ms" << endl;
}
