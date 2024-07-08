#include <iostream>
#include <limits>
#include "load/23a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/cct1.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/t.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/kt.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/cn.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/data/imdb_csv/keyword.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/mi.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/it1.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> cc_trie0 = {0, cc_offsets.size() - 1};
		pair<int, int> cct1_trie0 = {0, cct1_offsets.size() - 1};
		build_trie(cct1_offsets, cct1_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int cc_i = cc_trie0.first; cc_i <= cc_trie0.second; ++cc_i) {
			const auto &cc_off = cc_offsets[cc_i];
			auto x0 = cc_status_id[cc_off];
			auto cct1_trie1 = find_range(cct1_offsets, cct1_id, x0, cct1_trie0);
			if (cct1_trie1.first != -1) {
				interm0_col0.push_back(cc_status_id[cc_off]);
				interm0_col1.push_back(cc_movie_id[cc_off]);
				interm0_offsets.push_back(cnt++);
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> kt_trie0 = {0, kt_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		build_trie(kt_offsets, kt_id);
		build_trie(interm0_offsets, interm0_col1);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<string> interm1_col2;
		vector<string> interm1_col3;
		vector<int> interm1_offsets;
		cnt = 0;
		for (int t_i = t_trie0.first; t_i <= t_trie0.second; ++t_i) {
			const auto &t_off = t_offsets[t_i];
			auto x0 = t_kind_id[t_off];
			auto kt_trie1 = find_range(kt_offsets, kt_id, x0, kt_trie0);
			if (kt_trie1.first != -1) {
				auto x1 = t_id[t_off];
				auto interm0_trie1 = find_range(interm0_offsets, interm0_col1, x1, interm0_trie0);
				if (interm0_trie1.first != -1) {
					for (int kt_i = kt_trie1.first; kt_i <= kt_trie1.second; ++kt_i) {
						const auto &kt_off = kt_offsets[kt_i];
						interm1_col0.push_back(t_kind_id[t_off]);
						interm1_col1.push_back(t_id[t_off]);
						interm1_col2.push_back(t_title[t_off]);
						interm1_col3.push_back(kt_kind[kt_off]);
						interm1_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> ct_trie0 = {0, ct_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		pair<int, int> interm1_trie0 = {0, interm1_offsets.size() - 1};
		build_trie(ct_offsets, ct_id);
		build_trie(interm1_offsets, interm1_col1);
		build_trie(cn_offsets, cn_id);
		timer.StoreElapsedTime(4);

		vector<int> interm2_col0;
		vector<int> interm2_col1;
		vector<int> interm2_col2;
		vector<string> interm2_col4;
		vector<string> interm2_col5;
		vector<int> interm2_offsets;
		cnt = 0;
		for (int mc_i = mc_trie0.first; mc_i <= mc_trie0.second; ++mc_i) {
			const auto &mc_off = mc_offsets[mc_i];
			auto x0 = mc_company_type_id[mc_off];
			auto ct_trie1 = find_range(ct_offsets, ct_id, x0, ct_trie0);
			if (ct_trie1.first != -1) {
				auto x1 = mc_movie_id[mc_off];
				auto interm1_trie1 = find_range(interm1_offsets, interm1_col1, x1, interm1_trie0);
				if (interm1_trie1.first != -1) {
					auto x2 = mc_company_id[mc_off];
					auto cn_trie1 = find_range(cn_offsets, cn_id, x2, cn_trie0);
					if (cn_trie1.first != -1) {
						for (int interm1_i = interm1_trie1.first; interm1_i <= interm1_trie1.second; ++interm1_i) {
							const auto &interm1_off = interm1_offsets[interm1_i];
							interm2_col0.push_back(mc_company_type_id[mc_off]);
							interm2_col1.push_back(mc_company_id[mc_off]);
							interm2_col2.push_back(mc_movie_id[mc_off]);
							interm2_col4.push_back(interm1_col2[interm1_off]);
							interm2_col5.push_back(interm1_col3[interm1_off]);
							interm2_offsets.push_back(cnt++);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		pair<int, int> interm2_trie0 = {0, interm2_offsets.size() - 1};
		build_trie(interm2_offsets, interm2_col2);
		build_trie(k_offsets, k_id);
		timer.StoreElapsedTime(6);

		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<string> interm3_col5;
		vector<string> interm3_col6;
		vector<int> interm3_offsets;
		cnt = 0;
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_movie_id[mk_off];
			auto interm2_trie1 = find_range(interm2_offsets, interm2_col2, x0, interm2_trie0);
			if (interm2_trie1.first != -1) {
				auto x1 = mk_keyword_id[mk_off];
				auto k_trie1 = find_range(k_offsets, k_id, x1, k_trie0);
				if (k_trie1.first != -1) {
					for (int interm2_i = interm2_trie1.first; interm2_i <= interm2_trie1.second; ++interm2_i) {
						const auto &interm2_off = interm2_offsets[interm2_i];
						interm3_col0.push_back(mk_keyword_id[mk_off]);
						interm3_col1.push_back(mk_movie_id[mk_off]);
						interm3_col5.push_back(interm2_col4[interm2_off]);
						interm3_col6.push_back(interm2_col5[interm2_off]);
						interm3_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(7);

		pair<int, int> mi_trie0 = {0, mi_offsets.size() - 1};
		pair<int, int> it1_trie0 = {0, it1_offsets.size() - 1};
		pair<int, int> interm3_trie0 = {0, interm3_offsets.size() - 1};
		build_trie(it1_offsets, it1_id);
		build_trie(interm3_offsets, interm3_col1);
		timer.StoreElapsedTime(8);

		string mn_interm3_col5 = "zzzzzzzz";
		string mn_interm3_col6 = "zzzzzzzz";
		for (int mi_i = mi_trie0.first; mi_i <= mi_trie0.second; ++mi_i) {
			const auto &mi_off = mi_offsets[mi_i];
			auto x0 = mi_info_type_id[mi_off];
			auto it1_trie1 = find_range(it1_offsets, it1_id, x0, it1_trie0);
			if (it1_trie1.first != -1) {
				auto x1 = mi_movie_id[mi_off];
				auto interm3_trie1 = find_range(interm3_offsets, interm3_col1, x1, interm3_trie0);
				if (interm3_trie1.first != -1) {
					for (int interm3_i = interm3_trie1.first; interm3_i <= interm3_trie1.second; ++interm3_i) {
						const auto &interm3_off = interm3_offsets[interm3_i];
						mn_interm3_col5 = min(mn_interm3_col5, interm3_col5[interm3_off]);
						mn_interm3_col6 = min(mn_interm3_col6, interm3_col6[interm3_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(9);

		if (z == 0)
			cout << mn_interm3_col5 << " | " << mn_interm3_col6 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 5; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 5; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 5] << " ms" << endl;
}
