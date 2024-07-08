#include <iostream>
#include <limits>
#include "load/15a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15a/t.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15a/mi.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15a/mc.csv");
	load_k("/Users/s2522996/Documents/free-join/data/imdb_csv/keyword.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15a/it1.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15a/cn.csv");
	load_at("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_title.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		build_trie(t_offsets, t_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_movie_id[mk_off];
			auto t_trie1 = find_range(t_offsets, t_id, x0, t_trie0);
			if (t_trie1.first != -1) {
				for (int t_i = t_trie1.first; t_i <= t_trie1.second; ++t_i) {
					const auto &t_off = t_offsets[t_i];
					interm0_col0.push_back(mk_movie_id[mk_off]);
					interm0_col1.push_back(mk_keyword_id[mk_off]);
					interm0_col2.push_back(t_title[t_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> mi_trie0 = {0, mi_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		pair<int, int> it1_trie0 = {0, it1_offsets.size() - 1};
		pair<int, int> ct_trie0 = {0, ct_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		pair<int, int> at_trie0 = {0, at_offsets.size() - 1};
		build_trie(mc_offsets, mc_movie_id);
		build_trie(interm0_offsets, interm0_col0);
		build_trie(k_offsets, k_id);
		build_trie(it1_offsets, it1_id);
		build_trie(ct_offsets, ct_id);
		build_trie(cn_offsets, cn_id);
		build_trie(at_offsets, at_movie_id);
		timer.StoreElapsedTime(2);

		string mn_mi_info = "zzzzzzzz";
		string mn_interm0_col2 = "zzzzzzzz";
		for (int mi_i = mi_trie0.first; mi_i <= mi_trie0.second; ++mi_i) {
			const auto &mi_off = mi_offsets[mi_i];
			auto x0 = mi_movie_id[mi_off];
			auto mc_trie1 = find_range(mc_offsets, mc_movie_id, x0, mc_trie0);
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x0, interm0_trie0);
			if (mc_trie1.first != -1 && interm0_trie1.first != -1) {
				for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
					const auto &interm0_off = interm0_offsets[interm0_i];
					auto x1 = interm0_col1[interm0_off];
					auto k_trie1 = find_range(k_offsets, k_id, x1, k_trie0);
					if (k_trie1.first != -1) {
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
										auto at_trie1 = find_range(at_offsets, at_movie_id, x0, at_trie0);
										if (at_trie1.first != -1) {
											mn_mi_info = min(mn_mi_info, mi_info[mi_off]);
											mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
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
			cout << mn_mi_info << " | " << mn_interm0_col2 << endl;
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
