#include <iostream>
#include <limits>
#include "load/13c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/t.csv");
	load_miidx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_mi("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/kt.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/it2.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/it.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13c/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> miidx_trie0 = {0, miidx_offsets.size() - 1};
		build_trie(miidx_offsets, miidx_movie_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		vector<string> interm0_col3;
		vector<int> interm0_col4;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int t_i = t_trie0.first; t_i <= t_trie0.second; ++t_i) {
			const auto &t_off = t_offsets[t_i];
			auto x0 = t_id[t_off];
			auto miidx_trie1 = find_range(miidx_offsets, miidx_movie_id, x0, miidx_trie0);
			if (miidx_trie1.first != -1) {
				for (int miidx_i = miidx_trie1.first; miidx_i <= miidx_trie1.second; ++miidx_i) {
					const auto &miidx_off = miidx_offsets[miidx_i];
					interm0_col0.push_back(t_id[t_off]);
					interm0_col1.push_back(t_title[t_off]);
					interm0_col2.push_back(t_kind_id[t_off]);
					interm0_col3.push_back(miidx_info[miidx_off]);
					interm0_col4.push_back(miidx_info_type_id[miidx_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> mi_trie0 = {0, mi_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> kt_trie0 = {0, kt_offsets.size() - 1};
		pair<int, int> it2_trie0 = {0, it2_offsets.size() - 1};
		pair<int, int> it_trie0 = {0, it_offsets.size() - 1};
		pair<int, int> ct_trie0 = {0, ct_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col0);
		build_trie(mc_offsets, mc_movie_id);
		build_trie(kt_offsets, kt_id);
		build_trie(it2_offsets, it2_id);
		build_trie(it_offsets, it_id);
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
					auto kt_trie1 = find_range(kt_offsets, kt_id, x1, kt_trie0);
					if (kt_trie1.first != -1) {
						auto x2 = mi_info_type_id[mi_off];
						auto it2_trie1 = find_range(it2_offsets, it2_id, x2, it2_trie0);
						if (it2_trie1.first != -1) {
							auto x3 = interm0_col4[interm0_off];
							auto it_trie1 = find_range(it_offsets, it_id, x3, it_trie0);
							if (it_trie1.first != -1) {
								for (int mc_i = mc_trie1.first; mc_i <= mc_trie1.second; ++mc_i) {
									const auto &mc_off = mc_offsets[mc_i];
									auto x4 = mc_company_type_id[mc_off];
									auto ct_trie1 = find_range(ct_offsets, ct_id, x4, ct_trie0);
									if (ct_trie1.first != -1) {
										auto x5 = mc_company_id[mc_off];
										auto cn_trie1 = find_range(cn_offsets, cn_id, x5, cn_trie0);
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
