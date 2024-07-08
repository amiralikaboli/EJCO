#include <iostream>
#include <limits>
#include "load/33a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33a/lt.csv");
	load_mi_idx1("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33a/it1.csv");
	load_mi_idx2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33a/mi_idx2.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33a/it2.csv");
	load_t1("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_kt1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33a/kt1.csv");
	load_t2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33a/t2.csv");
	load_kt2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33a/kt2.csv");
	load_mc1("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33a/cn1.csv");
	load_mc2("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn2("/Users/s2522996/Documents/free-join/data/imdb_csv/company_name.csv");
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
		vector<int> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int ml_i = ml_trie0.first; ml_i <= ml_trie0.second; ++ml_i) {
			const auto &ml_off = ml_offsets[ml_i];
			auto x0 = ml_link_type_id[ml_off];
			auto lt_trie1 = find_range(lt_offsets, lt_id, x0, lt_trie0);
			if (lt_trie1.first != -1) {
				interm0_col0.push_back(ml_link_type_id[ml_off]);
				interm0_col1.push_back(ml_movie_id[ml_off]);
				interm0_col2.push_back(ml_linked_movie_id[ml_off]);
				interm0_offsets.push_back(cnt++);
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> mi_idx1_trie0 = {0, mi_idx1_offsets.size() - 1};
		pair<int, int> it1_trie0 = {0, it1_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		build_trie(it1_offsets, it1_id);
		build_trie(interm0_offsets, interm0_col1);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<string> interm1_col2;
		vector<int> interm1_col4;
		vector<int> interm1_offsets;
		cnt = 0;
		for (int mi_idx1_i = mi_idx1_trie0.first; mi_idx1_i <= mi_idx1_trie0.second; ++mi_idx1_i) {
			const auto &mi_idx1_off = mi_idx1_offsets[mi_idx1_i];
			auto x0 = mi_idx1_info_type_id[mi_idx1_off];
			auto it1_trie1 = find_range(it1_offsets, it1_id, x0, it1_trie0);
			if (it1_trie1.first != -1) {
				auto x1 = mi_idx1_movie_id[mi_idx1_off];
				auto interm0_trie1 = find_range(interm0_offsets, interm0_col1, x1, interm0_trie0);
				if (interm0_trie1.first != -1) {
					for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
						const auto &interm0_off = interm0_offsets[interm0_i];
						interm1_col0.push_back(mi_idx1_info_type_id[mi_idx1_off]);
						interm1_col1.push_back(mi_idx1_movie_id[mi_idx1_off]);
						interm1_col2.push_back(mi_idx1_info[mi_idx1_off]);
						interm1_col4.push_back(interm0_col2[interm0_off]);
						interm1_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		pair<int, int> mi_idx2_trie0 = {0, mi_idx2_offsets.size() - 1};
		pair<int, int> it2_trie0 = {0, it2_offsets.size() - 1};
		pair<int, int> interm1_trie0 = {0, interm1_offsets.size() - 1};
		build_trie(it2_offsets, it2_id);
		build_trie(interm1_offsets, interm1_col4);
		timer.StoreElapsedTime(4);

		vector<int> interm2_col0;
		vector<int> interm2_col1;
		vector<string> interm2_col2;
		vector<int> interm2_col4;
		vector<string> interm2_col5;
		vector<int> interm2_offsets;
		cnt = 0;
		for (int mi_idx2_i = mi_idx2_trie0.first; mi_idx2_i <= mi_idx2_trie0.second; ++mi_idx2_i) {
			const auto &mi_idx2_off = mi_idx2_offsets[mi_idx2_i];
			auto x0 = mi_idx2_info_type_id[mi_idx2_off];
			auto it2_trie1 = find_range(it2_offsets, it2_id, x0, it2_trie0);
			if (it2_trie1.first != -1) {
				auto x1 = mi_idx2_movie_id[mi_idx2_off];
				auto interm1_trie1 = find_range(interm1_offsets, interm1_col4, x1, interm1_trie0);
				if (interm1_trie1.first != -1) {
					for (int interm1_i = interm1_trie1.first; interm1_i <= interm1_trie1.second; ++interm1_i) {
						const auto &interm1_off = interm1_offsets[interm1_i];
						interm2_col0.push_back(mi_idx2_info_type_id[mi_idx2_off]);
						interm2_col1.push_back(mi_idx2_movie_id[mi_idx2_off]);
						interm2_col2.push_back(mi_idx2_info[mi_idx2_off]);
						interm2_col4.push_back(interm1_col1[interm1_off]);
						interm2_col5.push_back(interm1_col2[interm1_off]);
						interm2_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		pair<int, int> t1_trie0 = {0, t1_offsets.size() - 1};
		pair<int, int> kt1_trie0 = {0, kt1_offsets.size() - 1};
		pair<int, int> interm2_trie0 = {0, interm2_offsets.size() - 1};
		build_trie(kt1_offsets, kt1_id);
		build_trie(interm2_offsets, interm2_col4);
		timer.StoreElapsedTime(6);

		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<string> interm3_col2;
		vector<int> interm3_col4;
		vector<string> interm3_col5;
		vector<string> interm3_col7;
		vector<int> interm3_offsets;
		cnt = 0;
		for (int t1_i = t1_trie0.first; t1_i <= t1_trie0.second; ++t1_i) {
			const auto &t1_off = t1_offsets[t1_i];
			auto x0 = t1_kind_id[t1_off];
			auto kt1_trie1 = find_range(kt1_offsets, kt1_id, x0, kt1_trie0);
			if (kt1_trie1.first != -1) {
				auto x1 = t1_id[t1_off];
				auto interm2_trie1 = find_range(interm2_offsets, interm2_col4, x1, interm2_trie0);
				if (interm2_trie1.first != -1) {
					for (int interm2_i = interm2_trie1.first; interm2_i <= interm2_trie1.second; ++interm2_i) {
						const auto &interm2_off = interm2_offsets[interm2_i];
						interm3_col0.push_back(t1_kind_id[t1_off]);
						interm3_col1.push_back(t1_id[t1_off]);
						interm3_col2.push_back(t1_title[t1_off]);
						interm3_col4.push_back(interm2_col1[interm2_off]);
						interm3_col5.push_back(interm2_col2[interm2_off]);
						interm3_col7.push_back(interm2_col5[interm2_off]);
						interm3_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(7);

		pair<int, int> t2_trie0 = {0, t2_offsets.size() - 1};
		pair<int, int> kt2_trie0 = {0, kt2_offsets.size() - 1};
		pair<int, int> interm3_trie0 = {0, interm3_offsets.size() - 1};
		build_trie(kt2_offsets, kt2_id);
		build_trie(interm3_offsets, interm3_col4);
		timer.StoreElapsedTime(8);

		vector<int> interm4_col0;
		vector<int> interm4_col1;
		vector<string> interm4_col2;
		vector<int> interm4_col4;
		vector<string> interm4_col5;
		vector<string> interm4_col7;
		vector<string> interm4_col9;
		vector<int> interm4_offsets;
		cnt = 0;
		for (int t2_i = t2_trie0.first; t2_i <= t2_trie0.second; ++t2_i) {
			const auto &t2_off = t2_offsets[t2_i];
			auto x0 = t2_kind_id[t2_off];
			auto kt2_trie1 = find_range(kt2_offsets, kt2_id, x0, kt2_trie0);
			if (kt2_trie1.first != -1) {
				auto x1 = t2_id[t2_off];
				auto interm3_trie1 = find_range(interm3_offsets, interm3_col4, x1, interm3_trie0);
				if (interm3_trie1.first != -1) {
					for (int interm3_i = interm3_trie1.first; interm3_i <= interm3_trie1.second; ++interm3_i) {
						const auto &interm3_off = interm3_offsets[interm3_i];
						interm4_col0.push_back(t2_kind_id[t2_off]);
						interm4_col1.push_back(t2_id[t2_off]);
						interm4_col2.push_back(t2_title[t2_off]);
						interm4_col4.push_back(interm3_col1[interm3_off]);
						interm4_col5.push_back(interm3_col2[interm3_off]);
						interm4_col7.push_back(interm3_col5[interm3_off]);
						interm4_col9.push_back(interm3_col7[interm3_off]);
						interm4_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(9);

		pair<int, int> mc1_trie0 = {0, mc1_offsets.size() - 1};
		pair<int, int> cn1_trie0 = {0, cn1_offsets.size() - 1};
		pair<int, int> interm4_trie0 = {0, interm4_offsets.size() - 1};
		build_trie(interm4_offsets, interm4_col4);
		build_trie(cn1_offsets, cn1_id);
		timer.StoreElapsedTime(10);

		vector<int> interm5_col0;
		vector<int> interm5_col1;
		vector<string> interm5_col2;
		vector<int> interm5_col4;
		vector<string> interm5_col5;
		vector<string> interm5_col7;
		vector<string> interm5_col9;
		vector<string> interm5_col11;
		vector<int> interm5_offsets;
		cnt = 0;
		for (int mc1_i = mc1_trie0.first; mc1_i <= mc1_trie0.second; ++mc1_i) {
			const auto &mc1_off = mc1_offsets[mc1_i];
			auto x0 = mc1_movie_id[mc1_off];
			auto interm4_trie1 = find_range(interm4_offsets, interm4_col4, x0, interm4_trie0);
			if (interm4_trie1.first != -1) {
				auto x1 = mc1_company_id[mc1_off];
				auto cn1_trie1 = find_range(cn1_offsets, cn1_id, x1, cn1_trie0);
				if (cn1_trie1.first != -1) {
					for (int cn1_i = cn1_trie1.first; cn1_i <= cn1_trie1.second; ++cn1_i) {
						const auto &cn1_off = cn1_offsets[cn1_i];
						for (int interm4_i = interm4_trie1.first; interm4_i <= interm4_trie1.second; ++interm4_i) {
							const auto &interm4_off = interm4_offsets[interm4_i];
							interm5_col0.push_back(mc1_company_id[mc1_off]);
							interm5_col1.push_back(mc1_movie_id[mc1_off]);
							interm5_col2.push_back(cn1_name[cn1_off]);
							interm5_col4.push_back(interm4_col1[interm4_off]);
							interm5_col5.push_back(interm4_col2[interm4_off]);
							interm5_col7.push_back(interm4_col5[interm4_off]);
							interm5_col9.push_back(interm4_col7[interm4_off]);
							interm5_col11.push_back(interm4_col9[interm4_off]);
							interm5_offsets.push_back(cnt++);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(11);

		pair<int, int> mc2_trie0 = {0, mc2_offsets.size() - 1};
		pair<int, int> cn2_trie0 = {0, cn2_offsets.size() - 1};
		pair<int, int> interm5_trie0 = {0, interm5_offsets.size() - 1};
		build_trie(interm5_offsets, interm5_col4);
		build_trie(cn2_offsets, cn2_id);
		timer.StoreElapsedTime(12);

		string mn_cn2_name = "zzzzzzzz";
		string mn_interm5_col2 = "zzzzzzzz";
		string mn_interm5_col5 = "zzzzzzzz";
		string mn_interm5_col7 = "zzzzzzzz";
		string mn_interm5_col9 = "zzzzzzzz";
		string mn_interm5_col11 = "zzzzzzzz";
		for (int mc2_i = mc2_trie0.first; mc2_i <= mc2_trie0.second; ++mc2_i) {
			const auto &mc2_off = mc2_offsets[mc2_i];
			auto x0 = mc2_movie_id[mc2_off];
			auto interm5_trie1 = find_range(interm5_offsets, interm5_col4, x0, interm5_trie0);
			if (interm5_trie1.first != -1) {
				auto x1 = mc2_company_id[mc2_off];
				auto cn2_trie1 = find_range(cn2_offsets, cn2_id, x1, cn2_trie0);
				if (cn2_trie1.first != -1) {
					for (int cn2_i = cn2_trie1.first; cn2_i <= cn2_trie1.second; ++cn2_i) {
						const auto &cn2_off = cn2_offsets[cn2_i];
						mn_cn2_name = min(mn_cn2_name, cn2_name[cn2_off]);
					}
					for (int interm5_i = interm5_trie1.first; interm5_i <= interm5_trie1.second; ++interm5_i) {
						const auto &interm5_off = interm5_offsets[interm5_i];
						mn_interm5_col2 = min(mn_interm5_col2, interm5_col2[interm5_off]);
						mn_interm5_col5 = min(mn_interm5_col5, interm5_col5[interm5_off]);
						mn_interm5_col7 = min(mn_interm5_col7, interm5_col7[interm5_off]);
						mn_interm5_col9 = min(mn_interm5_col9, interm5_col9[interm5_off]);
						mn_interm5_col11 = min(mn_interm5_col11, interm5_col11[interm5_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(13);

		if (z == 0)
			cout << mn_cn2_name << " | " << mn_interm5_col2 << " | " << mn_interm5_col5 << " | " << mn_interm5_col7 << " | " << mn_interm5_col9 << " | " << mn_interm5_col11 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 7; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 7; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 7] << " ms" << endl;
}
