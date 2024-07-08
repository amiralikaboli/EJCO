#include <iostream>
#include <limits>
#include "load/14b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/mi_idx.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/mi.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/kt.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/k.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/it1.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> mi_idx_trie0 = {0, mi_idx_offsets.size() - 1};
		build_trie(t_offsets, t_id);
		build_trie(mi_idx_offsets, mi_idx_movie_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_col3;
		vector<int> interm0_col4;
		vector<string> interm0_col5;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_movie_id[mk_off];
			auto t_trie1 = find_range(t_offsets, t_id, x0, t_trie0);
			auto mi_idx_trie1 = find_range(mi_idx_offsets, mi_idx_movie_id, x0, mi_idx_trie0);
			if (t_trie1.first != -1 && mi_idx_trie1.first != -1) {
				for (int t_i = t_trie1.first; t_i <= t_trie1.second; ++t_i) {
					const auto &t_off = t_offsets[t_i];
					for (int mi_idx_i = mi_idx_trie1.first; mi_idx_i <= mi_idx_trie1.second; ++mi_idx_i) {
						const auto &mi_idx_off = mi_idx_offsets[mi_idx_i];
						interm0_col0.push_back(mk_movie_id[mk_off]);
						interm0_col1.push_back(mk_keyword_id[mk_off]);
						interm0_col2.push_back(t_title[t_off]);
						interm0_col3.push_back(t_kind_id[t_off]);
						interm0_col4.push_back(mi_idx_info_type_id[mi_idx_off]);
						interm0_col5.push_back(mi_idx_info[mi_idx_off]);
						interm0_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> mi_trie0 = {0, mi_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> kt_trie0 = {0, kt_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		pair<int, int> it2_trie0 = {0, it2_offsets.size() - 1};
		pair<int, int> it1_trie0 = {0, it1_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col0);
		build_trie(kt_offsets, kt_id);
		build_trie(k_offsets, k_id);
		build_trie(it2_offsets, it2_id);
		build_trie(it1_offsets, it1_id);
		timer.StoreElapsedTime(2);

		string mn_interm0_col2 = "zzzzzzzz";
		string mn_interm0_col5 = "zzzzzzzz";
		for (int mi_i = mi_trie0.first; mi_i <= mi_trie0.second; ++mi_i) {
			const auto &mi_off = mi_offsets[mi_i];
			auto x0 = mi_movie_id[mi_off];
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x0, interm0_trie0);
			if (interm0_trie1.first != -1) {
				for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
					const auto &interm0_off = interm0_offsets[interm0_i];
					auto x1 = interm0_col3[interm0_off];
					auto kt_trie1 = find_range(kt_offsets, kt_id, x1, kt_trie0);
					if (kt_trie1.first != -1) {
						auto x2 = interm0_col1[interm0_off];
						auto k_trie1 = find_range(k_offsets, k_id, x2, k_trie0);
						if (k_trie1.first != -1) {
							auto x3 = interm0_col4[interm0_off];
							auto it2_trie1 = find_range(it2_offsets, it2_id, x3, it2_trie0);
							if (it2_trie1.first != -1) {
								auto x4 = mi_info_type_id[mi_off];
								auto it1_trie1 = find_range(it1_offsets, it1_id, x4, it1_trie0);
								if (it1_trie1.first != -1) {
									mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
									mn_interm0_col5 = min(mn_interm0_col5, interm0_col5[interm0_off]);
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_interm0_col2 << " | " << mn_interm0_col5 << endl;
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
