#include <iostream>
#include <limits>
#include "load/29b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/cct2.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/cn.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/k.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/mi.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/it.csv");
	load_pi("/Users/s2522996/Documents/free-join/data/imdb_csv/person_info.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	load_it3("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/it3.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/n.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/ci.csv");
	load_chn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/chn.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29b/rt.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> cc_trie0 = {0, cc_offsets.size() - 1};
		pair<int, int> cct1_trie0 = {0, cct1_offsets.size() - 1};
		pair<int, int> cct2_trie0 = {0, cct2_offsets.size() - 1};
		build_trie(cct1_offsets, cct1_id);
		build_trie(cct2_offsets, cct2_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int cc_i = cc_trie0.first; cc_i <= cc_trie0.second; ++cc_i) {
			const auto &cc_off = cc_offsets[cc_i];
			auto x0 = cc_subject_id[cc_off];
			auto cct1_trie1 = find_range(cct1_offsets, cct1_id, x0, cct1_trie0);
			if (cct1_trie1.first != -1) {
				auto x1 = cc_status_id[cc_off];
				auto cct2_trie1 = find_range(cct2_offsets, cct2_id, x1, cct2_trie0);
				if (cct2_trie1.first != -1) {
					interm0_col0.push_back(cc_subject_id[cc_off]);
					interm0_col1.push_back(cc_status_id[cc_off]);
					interm0_col2.push_back(cc_movie_id[cc_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col2);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<string> interm1_col1;
		vector<int> interm1_offsets;
		cnt = 0;
		for (int t_i = t_trie0.first; t_i <= t_trie0.second; ++t_i) {
			const auto &t_off = t_offsets[t_i];
			auto x0 = t_id[t_off];
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col2, x0, interm0_trie0);
			if (interm0_trie1.first != -1) {
				interm1_col0.push_back(t_id[t_off]);
				interm1_col1.push_back(t_title[t_off]);
				interm1_offsets.push_back(cnt++);
			}
		}
		timer.StoreElapsedTime(3);

		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		pair<int, int> interm1_trie0 = {0, interm1_offsets.size() - 1};
		build_trie(interm1_offsets, interm1_col0);
		build_trie(cn_offsets, cn_id);
		timer.StoreElapsedTime(4);

		vector<int> interm2_col0;
		vector<int> interm2_col1;
		vector<string> interm2_col2;
		vector<int> interm2_offsets;
		cnt = 0;
		for (int mc_i = mc_trie0.first; mc_i <= mc_trie0.second; ++mc_i) {
			const auto &mc_off = mc_offsets[mc_i];
			auto x0 = mc_movie_id[mc_off];
			auto interm1_trie1 = find_range(interm1_offsets, interm1_col0, x0, interm1_trie0);
			if (interm1_trie1.first != -1) {
				auto x1 = mc_company_id[mc_off];
				auto cn_trie1 = find_range(cn_offsets, cn_id, x1, cn_trie0);
				if (cn_trie1.first != -1) {
					for (int interm1_i = interm1_trie1.first; interm1_i <= interm1_trie1.second; ++interm1_i) {
						const auto &interm1_off = interm1_offsets[interm1_i];
						interm2_col0.push_back(mc_company_id[mc_off]);
						interm2_col1.push_back(mc_movie_id[mc_off]);
						interm2_col2.push_back(interm1_col1[interm1_off]);
						interm2_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		pair<int, int> interm2_trie0 = {0, interm2_offsets.size() - 1};
		build_trie(k_offsets, k_id);
		build_trie(interm2_offsets, interm2_col1);
		timer.StoreElapsedTime(6);

		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<string> interm3_col3;
		vector<int> interm3_offsets;
		cnt = 0;
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_keyword_id[mk_off];
			auto k_trie1 = find_range(k_offsets, k_id, x0, k_trie0);
			if (k_trie1.first != -1) {
				auto x1 = mk_movie_id[mk_off];
				auto interm2_trie1 = find_range(interm2_offsets, interm2_col1, x1, interm2_trie0);
				if (interm2_trie1.first != -1) {
					for (int interm2_i = interm2_trie1.first; interm2_i <= interm2_trie1.second; ++interm2_i) {
						const auto &interm2_off = interm2_offsets[interm2_i];
						interm3_col0.push_back(mk_keyword_id[mk_off]);
						interm3_col1.push_back(mk_movie_id[mk_off]);
						interm3_col3.push_back(interm2_col2[interm2_off]);
						interm3_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(7);

		pair<int, int> mi_trie0 = {0, mi_offsets.size() - 1};
		pair<int, int> it_trie0 = {0, it_offsets.size() - 1};
		pair<int, int> interm3_trie0 = {0, interm3_offsets.size() - 1};
		build_trie(it_offsets, it_id);
		build_trie(interm3_offsets, interm3_col1);
		timer.StoreElapsedTime(8);

		vector<int> interm4_col0;
		vector<int> interm4_col1;
		vector<string> interm4_col4;
		vector<int> interm4_offsets;
		cnt = 0;
		for (int mi_i = mi_trie0.first; mi_i <= mi_trie0.second; ++mi_i) {
			const auto &mi_off = mi_offsets[mi_i];
			auto x0 = mi_info_type_id[mi_off];
			auto it_trie1 = find_range(it_offsets, it_id, x0, it_trie0);
			if (it_trie1.first != -1) {
				auto x1 = mi_movie_id[mi_off];
				auto interm3_trie1 = find_range(interm3_offsets, interm3_col1, x1, interm3_trie0);
				if (interm3_trie1.first != -1) {
					for (int interm3_i = interm3_trie1.first; interm3_i <= interm3_trie1.second; ++interm3_i) {
						const auto &interm3_off = interm3_offsets[interm3_i];
						interm4_col0.push_back(mi_info_type_id[mi_off]);
						interm4_col1.push_back(mi_movie_id[mi_off]);
						interm4_col4.push_back(interm3_col3[interm3_off]);
						interm4_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(9);

		pair<int, int> pi_trie0 = {0, pi_offsets.size() - 1};
		pair<int, int> an_trie0 = {0, an_offsets.size() - 1};
		pair<int, int> it3_trie0 = {0, it3_offsets.size() - 1};
		build_trie(it3_offsets, it3_id);
		build_trie(an_offsets, an_person_id);
		timer.StoreElapsedTime(10);

		vector<int> interm5_col0;
		vector<int> interm5_col1;
		vector<int> interm5_offsets;
		cnt = 0;
		for (int pi_i = pi_trie0.first; pi_i <= pi_trie0.second; ++pi_i) {
			const auto &pi_off = pi_offsets[pi_i];
			auto x0 = pi_info_type_id[pi_off];
			auto it3_trie1 = find_range(it3_offsets, it3_id, x0, it3_trie0);
			if (it3_trie1.first != -1) {
				auto x1 = pi_person_id[pi_off];
				auto an_trie1 = find_range(an_offsets, an_person_id, x1, an_trie0);
				if (an_trie1.first != -1) {
					interm5_col0.push_back(pi_person_id[pi_off]);
					interm5_col1.push_back(pi_info_type_id[pi_off]);
					interm5_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(11);

		pair<int, int> n_trie0 = {0, n_offsets.size() - 1};
		pair<int, int> interm5_trie0 = {0, interm5_offsets.size() - 1};
		build_trie(interm5_offsets, interm5_col0);
		timer.StoreElapsedTime(12);

		vector<int> interm6_col0;
		vector<string> interm6_col1;
		vector<int> interm6_offsets;
		cnt = 0;
		for (int n_i = n_trie0.first; n_i <= n_trie0.second; ++n_i) {
			const auto &n_off = n_offsets[n_i];
			auto x0 = n_id[n_off];
			auto interm5_trie1 = find_range(interm5_offsets, interm5_col0, x0, interm5_trie0);
			if (interm5_trie1.first != -1) {
				interm6_col0.push_back(n_id[n_off]);
				interm6_col1.push_back(n_name[n_off]);
				interm6_offsets.push_back(cnt++);
			}
		}
		timer.StoreElapsedTime(13);

		pair<int, int> ci_trie0 = {0, ci_offsets.size() - 1};
		pair<int, int> chn_trie0 = {0, chn_offsets.size() - 1};
		pair<int, int> rt_trie0 = {0, rt_offsets.size() - 1};
		pair<int, int> interm6_trie0 = {0, interm6_offsets.size() - 1};
		pair<int, int> interm4_trie0 = {0, interm4_offsets.size() - 1};
		build_trie(chn_offsets, chn_id);
		build_trie(rt_offsets, rt_id);
		build_trie(interm4_offsets, interm4_col1);
		build_trie(interm6_offsets, interm6_col0);
		timer.StoreElapsedTime(14);

		string mn_chn_name = "zzzzzzzz";
		string mn_interm6_col1 = "zzzzzzzz";
		string mn_interm4_col4 = "zzzzzzzz";
		for (int ci_i = ci_trie0.first; ci_i <= ci_trie0.second; ++ci_i) {
			const auto &ci_off = ci_offsets[ci_i];
			auto x0 = ci_person_role_id[ci_off];
			auto chn_trie1 = find_range(chn_offsets, chn_id, x0, chn_trie0);
			if (chn_trie1.first != -1) {
				auto x1 = ci_role_id[ci_off];
				auto rt_trie1 = find_range(rt_offsets, rt_id, x1, rt_trie0);
				if (rt_trie1.first != -1) {
					auto x2 = ci_movie_id[ci_off];
					auto interm4_trie1 = find_range(interm4_offsets, interm4_col1, x2, interm4_trie0);
					if (interm4_trie1.first != -1) {
						auto x3 = ci_person_id[ci_off];
						auto interm6_trie1 = find_range(interm6_offsets, interm6_col0, x3, interm6_trie0);
						if (interm6_trie1.first != -1) {
							for (int chn_i = chn_trie1.first; chn_i <= chn_trie1.second; ++chn_i) {
								const auto &chn_off = chn_offsets[chn_i];
								mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
							}
							for (int interm6_i = interm6_trie1.first; interm6_i <= interm6_trie1.second; ++interm6_i) {
								const auto &interm6_off = interm6_offsets[interm6_i];
								mn_interm6_col1 = min(mn_interm6_col1, interm6_col1[interm6_off]);
							}
							for (int interm4_i = interm4_trie1.first; interm4_i <= interm4_trie1.second; ++interm4_i) {
								const auto &interm4_off = interm4_offsets[interm4_i];
								mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(15);

		if (z == 0)
			cout << mn_chn_name << " | " << mn_interm6_col1 << " | " << mn_interm4_col4 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 8; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 8; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 8] << " ms" << endl;
}
