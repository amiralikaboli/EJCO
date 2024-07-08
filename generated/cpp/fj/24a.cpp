#include <iostream>
#include <limits>
#include "load/24a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/t.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/mi.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/k.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/it.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/cn.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/n.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/ci.csv");
	load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/rt.csv");
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
		pair<int, int> it_trie0 = {0, it_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col0);
		build_trie(mc_offsets, mc_movie_id);
		build_trie(k_offsets, k_id);
		build_trie(it_offsets, it_id);
		build_trie(cn_offsets, cn_id);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<int> interm1_col2;
		vector<string> interm1_col3;
		vector<int> interm1_col4;
		vector<int> interm1_offsets;
		cnt = 0;
		for (int mi_i = mi_trie0.first; mi_i <= mi_trie0.second; ++mi_i) {
			const auto &mi_off = mi_offsets[mi_i];
			auto x0 = mi_movie_id[mi_off];
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x0, interm0_trie0);
			auto mc_trie1 = find_range(mc_offsets, mc_movie_id, x0, mc_trie0);
			if (interm0_trie1.first != -1 && mc_trie1.first != -1) {
				for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
					const auto &interm0_off = interm0_offsets[interm0_i];
					auto x1 = interm0_col1[interm0_off];
					auto k_trie1 = find_range(k_offsets, k_id, x1, k_trie0);
					if (k_trie1.first != -1) {
						auto x2 = mi_info_type_id[mi_off];
						auto it_trie1 = find_range(it_offsets, it_id, x2, it_trie0);
						if (it_trie1.first != -1) {
							for (int mc_i = mc_trie1.first; mc_i <= mc_trie1.second; ++mc_i) {
								const auto &mc_off = mc_offsets[mc_i];
								auto x3 = mc_company_id[mc_off];
								auto cn_trie1 = find_range(cn_offsets, cn_id, x3, cn_trie0);
								if (cn_trie1.first != -1) {
									interm1_col0.push_back(mi_movie_id[mi_off]);
									interm1_col1.push_back(mi_info_type_id[mi_off]);
									interm1_col2.push_back(interm0_col1[interm0_off]);
									interm1_col3.push_back(interm0_col2[interm0_off]);
									interm1_col4.push_back(mc_company_id[mc_off]);
									interm1_offsets.push_back(cnt++);
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		pair<int, int> n_trie0 = {0, n_offsets.size() - 1};
		pair<int, int> an_trie0 = {0, an_offsets.size() - 1};
		build_trie(an_offsets, an_person_id);
		timer.StoreElapsedTime(4);

		vector<int> interm2_col0;
		vector<string> interm2_col1;
		vector<int> interm2_offsets;
		cnt = 0;
		for (int n_i = n_trie0.first; n_i <= n_trie0.second; ++n_i) {
			const auto &n_off = n_offsets[n_i];
			auto x0 = n_id[n_off];
			auto an_trie1 = find_range(an_offsets, an_person_id, x0, an_trie0);
			if (an_trie1.first != -1) {
				interm2_col0.push_back(n_id[n_off]);
				interm2_col1.push_back(n_name[n_off]);
				interm2_offsets.push_back(cnt++);
			}
		}
		timer.StoreElapsedTime(5);

		pair<int, int> ci_trie0 = {0, ci_offsets.size() - 1};
		pair<int, int> chn_trie0 = {0, chn_offsets.size() - 1};
		pair<int, int> rt_trie0 = {0, rt_offsets.size() - 1};
		pair<int, int> interm2_trie0 = {0, interm2_offsets.size() - 1};
		pair<int, int> interm1_trie0 = {0, interm1_offsets.size() - 1};
		build_trie(rt_offsets, rt_id);
		build_trie(interm1_offsets, interm1_col0);
		build_trie(interm2_offsets, interm2_col0);
		build_trie(chn_offsets, chn_id);
		timer.StoreElapsedTime(6);

		string mn_chn_name = "zzzzzzzz";
		string mn_interm2_col1 = "zzzzzzzz";
		string mn_interm1_col3 = "zzzzzzzz";
		for (int ci_i = ci_trie0.first; ci_i <= ci_trie0.second; ++ci_i) {
			const auto &ci_off = ci_offsets[ci_i];
			auto x0 = ci_role_id[ci_off];
			auto rt_trie1 = find_range(rt_offsets, rt_id, x0, rt_trie0);
			if (rt_trie1.first != -1) {
				auto x1 = ci_movie_id[ci_off];
				auto interm1_trie1 = find_range(interm1_offsets, interm1_col0, x1, interm1_trie0);
				if (interm1_trie1.first != -1) {
					auto x2 = ci_person_id[ci_off];
					auto interm2_trie1 = find_range(interm2_offsets, interm2_col0, x2, interm2_trie0);
					if (interm2_trie1.first != -1) {
						auto x3 = ci_person_role_id[ci_off];
						auto chn_trie1 = find_range(chn_offsets, chn_id, x3, chn_trie0);
						if (chn_trie1.first != -1) {
							for (int chn_i = chn_trie1.first; chn_i <= chn_trie1.second; ++chn_i) {
								const auto &chn_off = chn_offsets[chn_i];
								mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
							}
							for (int interm2_i = interm2_trie1.first; interm2_i <= interm2_trie1.second; ++interm2_i) {
								const auto &interm2_off = interm2_offsets[interm2_i];
								mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
							}
							for (int interm1_i = interm1_trie1.first; interm1_i <= interm1_trie1.second; ++interm1_i) {
								const auto &interm1_off = interm1_offsets[interm1_i];
								mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(7);

		if (z == 0)
			cout << mn_chn_name << " | " << mn_interm2_col1 << " | " << mn_interm1_col3 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 4; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 4; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 4] << " ms" << endl;
}
