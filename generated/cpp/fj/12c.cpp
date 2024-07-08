#include <iostream>
#include <limits>
#include "load/12c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/mi_idx.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/mi.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/it1.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/cn.csv");
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
		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> it2_trie0 = {0, it2_offsets.size() - 1};
		pair<int, int> it1_trie0 = {0, it1_offsets.size() - 1};
		pair<int, int> ct_trie0 = {0, ct_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col0);
		build_trie(mc_offsets, mc_movie_id);
		build_trie(it2_offsets, it2_id);
		build_trie(it1_offsets, it1_id);
		build_trie(ct_offsets, ct_id);
		build_trie(cn_offsets, cn_id);
		timer.StoreElapsedTime(2);

		string mn_interm0_col1 = "zzzzzzzz";
		string mn_interm0_col3 = "zzzzzzzz";
		string mn_cn_name = "zzzzzzzz";
		for (int mi_i = mi_trie0.first; mi_i <= mi_trie0.second; ++mi_i) {
			const auto &mi_off = mi_offsets[mi_i];
			auto x0 = mi_movie_id[mi_off];
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x0, interm0_trie0);
			auto mc_trie1 = find_range(mc_offsets, mc_movie_id, x0, mc_trie0);
			if (interm0_trie1.first != -1 && mc_trie1.first != -1) {
				for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
					const auto &interm0_off = interm0_offsets[interm0_i];
					auto x1 = interm0_col2[interm0_off];
					auto it2_trie1 = find_range(it2_offsets, it2_id, x1, it2_trie0);
					if (it2_trie1.first != -1) {
						auto x2 = mi_info_type_id[mi_off];
						auto it1_trie1 = find_range(it1_offsets, it1_id, x2, it1_trie0);
						if (it1_trie1.first != -1) {
							for (int mc_i = mc_trie1.first; mc_i <= mc_trie1.second; ++mc_i) {
								const auto &mc_off = mc_offsets[mc_i];
								auto x3 = mc_company_type_id[mc_off];
								auto ct_trie1 = find_range(ct_offsets, ct_id, x3, ct_trie0);
								if (ct_trie1.first != -1) {
									auto x4 = mc_company_id[mc_off];
									auto cn_trie1 = find_range(cn_offsets, cn_id, x4, cn_trie0);
									if (cn_trie1.first != -1) {
										mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
										mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
										for (int cn_i = cn_trie1.first; cn_i <= cn_trie1.second; ++cn_i) {
											const auto &cn_off = cn_offsets[cn_i];
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
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_interm0_col1 << " | " << mn_interm0_col3 << " | " << mn_cn_name << endl;
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
