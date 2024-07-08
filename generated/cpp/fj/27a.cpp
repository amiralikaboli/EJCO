#include <iostream>
#include <limits>
#include "load/27a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/lt.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/cct2.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/mc.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/cn.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/k.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27a/mi.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> ml_trie0 = {0, ml_offsets.size() - 1};
		pair<int, int> lt_trie0 = {0, lt_offsets.size() - 1};
		build_trie(lt_offsets, lt_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int ml_i = ml_trie0.first; ml_i <= ml_trie0.second; ++ml_i) {
			const auto &ml_off = ml_offsets[ml_i];
			auto x0 = ml_link_type_id[ml_off];
			auto lt_trie1 = find_range(lt_offsets, lt_id, x0, lt_trie0);
			if (lt_trie1.first != -1) {
				for (int lt_i = lt_trie1.first; lt_i <= lt_trie1.second; ++lt_i) {
					const auto &lt_off = lt_offsets[lt_i];
					interm0_col0.push_back(ml_link_type_id[ml_off]);
					interm0_col1.push_back(ml_movie_id[ml_off]);
					interm0_col2.push_back(lt_link[lt_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> cc_trie0 = {0, cc_offsets.size() - 1};
		pair<int, int> cct1_trie0 = {0, cct1_offsets.size() - 1};
		pair<int, int> cct2_trie0 = {0, cct2_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		build_trie(cct2_offsets, cct2_id);
		build_trie(cct1_offsets, cct1_id);
		build_trie(interm0_offsets, interm0_col1);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<int> interm1_col2;
		vector<string> interm1_col4;
		vector<int> interm1_offsets;
		cnt = 0;
		for (int cc_i = cc_trie0.first; cc_i <= cc_trie0.second; ++cc_i) {
			const auto &cc_off = cc_offsets[cc_i];
			auto x0 = cc_status_id[cc_off];
			auto cct2_trie1 = find_range(cct2_offsets, cct2_id, x0, cct2_trie0);
			if (cct2_trie1.first != -1) {
				auto x1 = cc_subject_id[cc_off];
				auto cct1_trie1 = find_range(cct1_offsets, cct1_id, x1, cct1_trie0);
				if (cct1_trie1.first != -1) {
					auto x2 = cc_movie_id[cc_off];
					auto interm0_trie1 = find_range(interm0_offsets, interm0_col1, x2, interm0_trie0);
					if (interm0_trie1.first != -1) {
						for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
							const auto &interm0_off = interm0_offsets[interm0_i];
							interm1_col0.push_back(cc_subject_id[cc_off]);
							interm1_col1.push_back(cc_status_id[cc_off]);
							interm1_col2.push_back(cc_movie_id[cc_off]);
							interm1_col4.push_back(interm0_col2[interm0_off]);
							interm1_offsets.push_back(cnt++);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> interm1_trie0 = {0, interm1_offsets.size() - 1};
		build_trie(interm1_offsets, interm1_col2);
		timer.StoreElapsedTime(4);

		vector<int> interm2_col0;
		vector<string> interm2_col1;
		vector<string> interm2_col5;
		vector<int> interm2_offsets;
		cnt = 0;
		for (int t_i = t_trie0.first; t_i <= t_trie0.second; ++t_i) {
			const auto &t_off = t_offsets[t_i];
			auto x0 = t_id[t_off];
			auto interm1_trie1 = find_range(interm1_offsets, interm1_col2, x0, interm1_trie0);
			if (interm1_trie1.first != -1) {
				for (int interm1_i = interm1_trie1.first; interm1_i <= interm1_trie1.second; ++interm1_i) {
					const auto &interm1_off = interm1_offsets[interm1_i];
					interm2_col0.push_back(t_id[t_off]);
					interm2_col1.push_back(t_title[t_off]);
					interm2_col5.push_back(interm1_col4[interm1_off]);
					interm2_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(5);

		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> ct_trie0 = {0, ct_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		pair<int, int> interm2_trie0 = {0, interm2_offsets.size() - 1};
		build_trie(ct_offsets, ct_id);
		build_trie(interm2_offsets, interm2_col0);
		build_trie(cn_offsets, cn_id);
		timer.StoreElapsedTime(6);

		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<int> interm3_col2;
		vector<string> interm3_col3;
		vector<string> interm3_col4;
		vector<string> interm3_col8;
		vector<int> interm3_offsets;
		cnt = 0;
		for (int mc_i = mc_trie0.first; mc_i <= mc_trie0.second; ++mc_i) {
			const auto &mc_off = mc_offsets[mc_i];
			auto x0 = mc_company_type_id[mc_off];
			auto ct_trie1 = find_range(ct_offsets, ct_id, x0, ct_trie0);
			if (ct_trie1.first != -1) {
				auto x1 = mc_movie_id[mc_off];
				auto interm2_trie1 = find_range(interm2_offsets, interm2_col0, x1, interm2_trie0);
				if (interm2_trie1.first != -1) {
					auto x2 = mc_company_id[mc_off];
					auto cn_trie1 = find_range(cn_offsets, cn_id, x2, cn_trie0);
					if (cn_trie1.first != -1) {
						for (int cn_i = cn_trie1.first; cn_i <= cn_trie1.second; ++cn_i) {
							const auto &cn_off = cn_offsets[cn_i];
							for (int interm2_i = interm2_trie1.first; interm2_i <= interm2_trie1.second; ++interm2_i) {
								const auto &interm2_off = interm2_offsets[interm2_i];
								interm3_col0.push_back(mc_company_type_id[mc_off]);
								interm3_col1.push_back(mc_company_id[mc_off]);
								interm3_col2.push_back(mc_movie_id[mc_off]);
								interm3_col3.push_back(cn_name[cn_off]);
								interm3_col4.push_back(interm2_col1[interm2_off]);
								interm3_col8.push_back(interm2_col5[interm2_off]);
								interm3_offsets.push_back(cnt++);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(7);

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		pair<int, int> interm3_trie0 = {0, interm3_offsets.size() - 1};
		build_trie(k_offsets, k_id);
		build_trie(interm3_offsets, interm3_col2);
		timer.StoreElapsedTime(8);

		vector<int> interm4_col0;
		vector<int> interm4_col1;
		vector<string> interm4_col4;
		vector<string> interm4_col5;
		vector<string> interm4_col9;
		vector<int> interm4_offsets;
		cnt = 0;
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_keyword_id[mk_off];
			auto k_trie1 = find_range(k_offsets, k_id, x0, k_trie0);
			if (k_trie1.first != -1) {
				auto x1 = mk_movie_id[mk_off];
				auto interm3_trie1 = find_range(interm3_offsets, interm3_col2, x1, interm3_trie0);
				if (interm3_trie1.first != -1) {
					for (int interm3_i = interm3_trie1.first; interm3_i <= interm3_trie1.second; ++interm3_i) {
						const auto &interm3_off = interm3_offsets[interm3_i];
						interm4_col0.push_back(mk_keyword_id[mk_off]);
						interm4_col1.push_back(mk_movie_id[mk_off]);
						interm4_col4.push_back(interm3_col3[interm3_off]);
						interm4_col5.push_back(interm3_col4[interm3_off]);
						interm4_col9.push_back(interm3_col8[interm3_off]);
						interm4_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(9);

		pair<int, int> mi_trie0 = {0, mi_offsets.size() - 1};
		pair<int, int> interm4_trie0 = {0, interm4_offsets.size() - 1};
		build_trie(interm4_offsets, interm4_col1);
		timer.StoreElapsedTime(10);

		string mn_interm4_col4 = "zzzzzzzz";
		string mn_interm4_col5 = "zzzzzzzz";
		string mn_interm4_col9 = "zzzzzzzz";
		for (int mi_i = mi_trie0.first; mi_i <= mi_trie0.second; ++mi_i) {
			const auto &mi_off = mi_offsets[mi_i];
			auto x0 = mi_movie_id[mi_off];
			auto interm4_trie1 = find_range(interm4_offsets, interm4_col1, x0, interm4_trie0);
			if (interm4_trie1.first != -1) {
				for (int interm4_i = interm4_trie1.first; interm4_i <= interm4_trie1.second; ++interm4_i) {
					const auto &interm4_off = interm4_offsets[interm4_i];
					mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
					mn_interm4_col5 = min(mn_interm4_col5, interm4_col5[interm4_off]);
					mn_interm4_col9 = min(mn_interm4_col9, interm4_col9[interm4_off]);
				}
			}
		}
		timer.StoreElapsedTime(11);

		if (z == 0)
			cout << mn_interm4_col4 << " | " << mn_interm4_col5 << " | " << mn_interm4_col9 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 6; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 6; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 6] << " ms" << endl;
}
