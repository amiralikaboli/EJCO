#include <iostream>
#include <limits>
#include "load/22d.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22d/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22d/mi_idx.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22d/kt.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22d/it2.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22d/cn.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22d/k.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22d/mi.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22d/it1.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto t_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(t_trie0, t_id, t_kind_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id, mi_idx_info_type_id);
		auto kt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(kt_trie0, kt_id);
		auto it2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it2_trie0, it2_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_col3;
		vector<string> interm0_col4;
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (mi_idx_trie0.contains(x0)) {
				auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
				for (const auto &[x1, t_trie2]: t_trie1) {
					if (kt_trie0.contains(x1)) {
						auto &kt_trie1 = kt_trie0.at(x1);
						for (const auto &[x2, mi_idx_trie2]: mi_idx_trie1) {
							if (it2_trie0.contains(x2)) {
								auto &it2_trie1 = it2_trie0.at(x2);
								for (const auto &t_off: t_trie2) {
									for (const auto &mi_idx_off: mi_idx_trie2) {
										interm0_col0.push_back(t_id[t_off]);
										interm0_col1.push_back(t_kind_id[t_off]);
										interm0_col2.push_back(t_title[t_off]);
										interm0_col3.push_back(mi_idx_info_type_id[mi_idx_off]);
										interm0_col4.push_back(mi_idx_info[mi_idx_off]);
									}
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(mc_trie0, mc_company_id, mc_company_type_id, mc_movie_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto ct_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ct_trie0, ct_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<int> interm1_col2;
		vector<string> interm1_col3;
		vector<int> interm1_col4;
		vector<string> interm1_col5;
		vector<int> interm1_col6;
		vector<string> interm1_col7;
		for (const auto &[x0, mc_trie1]: mc_trie0) {
			if (cn_trie0.contains(x0)) {
				auto &cn_trie1 = cn_trie0.at(x0);
				for (const auto &[x1, mc_trie2]: mc_trie1) {
					if (ct_trie0.contains(x1)) {
						auto &ct_trie1 = ct_trie0.at(x1);
						for (const auto &[x2, mc_trie3]: mc_trie2) {
							if (interm0_trie0.contains(x2)) {
								auto &interm0_trie1 = interm0_trie0.at(x2);
								for (const auto &mc_off: mc_trie3) {
									for (const auto &cn_off: cn_trie1) {
										for (const auto &interm0_off: interm0_trie1) {
											interm1_col0.push_back(mc_company_id[mc_off]);
											interm1_col1.push_back(mc_company_type_id[mc_off]);
											interm1_col2.push_back(mc_movie_id[mc_off]);
											interm1_col3.push_back(cn_name[cn_off]);
											interm1_col4.push_back(interm0_col1[interm0_off]);
											interm1_col5.push_back(interm0_col2[interm0_off]);
											interm1_col6.push_back(interm0_col3[interm0_off]);
											interm1_col7.push_back(interm0_col4[interm0_off]);
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

		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col2);
		timer.StoreElapsedTime(4);

		vector<int> interm2_col0;
		vector<int> interm2_col1;
		vector<int> interm2_col2;
		vector<int> interm2_col3;
		vector<string> interm2_col4;
		vector<int> interm2_col5;
		vector<string> interm2_col6;
		vector<int> interm2_col7;
		vector<string> interm2_col8;
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (k_trie0.contains(x0)) {
				auto &k_trie1 = k_trie0.at(x0);
				for (const auto &[x1, mk_trie2]: mk_trie1) {
					if (interm1_trie0.contains(x1)) {
						auto &interm1_trie1 = interm1_trie0.at(x1);
						for (const auto &mk_off: mk_trie2) {
							for (const auto &interm1_off: interm1_trie1) {
								interm2_col0.push_back(mk_keyword_id[mk_off]);
								interm2_col1.push_back(mk_movie_id[mk_off]);
								interm2_col2.push_back(interm1_col0[interm1_off]);
								interm2_col3.push_back(interm1_col1[interm1_off]);
								interm2_col4.push_back(interm1_col3[interm1_off]);
								interm2_col5.push_back(interm1_col4[interm1_off]);
								interm2_col6.push_back(interm1_col5[interm1_off]);
								interm2_col7.push_back(interm1_col6[interm1_off]);
								interm2_col8.push_back(interm1_col7[interm1_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mi_trie0, mi_info_type_id, mi_movie_id);
		auto it1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it1_trie0, it1_id);
		auto interm2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm2_trie0, interm2_col1);
		timer.StoreElapsedTime(6);

		int mn_interm2_col0 = numeric_limits<int>::max();
		int mn_interm2_col2 = numeric_limits<int>::max();
		int mn_interm2_col3 = numeric_limits<int>::max();
		string mn_interm2_col4 = "zzzzzzzz";
		int mn_interm2_col5 = numeric_limits<int>::max();
		string mn_interm2_col6 = "zzzzzzzz";
		int mn_interm2_col7 = numeric_limits<int>::max();
		string mn_interm2_col8 = "zzzzzzzz";
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (it1_trie0.contains(x0)) {
				auto &it1_trie1 = it1_trie0.at(x0);
				for (const auto &[x1, mi_trie2]: mi_trie1) {
					if (interm2_trie0.contains(x1)) {
						auto &interm2_trie1 = interm2_trie0.at(x1);
						for (const auto &interm2_off: interm2_trie1) {
							mn_interm2_col0 = min(mn_interm2_col0, interm2_col0[interm2_off]);
							mn_interm2_col2 = min(mn_interm2_col2, interm2_col2[interm2_off]);
							mn_interm2_col3 = min(mn_interm2_col3, interm2_col3[interm2_off]);
							mn_interm2_col4 = min(mn_interm2_col4, interm2_col4[interm2_off]);
							mn_interm2_col5 = min(mn_interm2_col5, interm2_col5[interm2_off]);
							mn_interm2_col6 = min(mn_interm2_col6, interm2_col6[interm2_off]);
							mn_interm2_col7 = min(mn_interm2_col7, interm2_col7[interm2_off]);
							mn_interm2_col8 = min(mn_interm2_col8, interm2_col8[interm2_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(7);

		if (z == 0)
			cout << mn_interm2_col0 << " | " << mn_interm2_col2 << " | " << mn_interm2_col3 << " | " << mn_interm2_col4 << " | " << mn_interm2_col5 << " | " << mn_interm2_col6 << " | " << mn_interm2_col7 << " | " << mn_interm2_col8 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 4 * 2; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 4; i += 2)
		cout << tm[i + 1] - tm[i] << " + " << tm[i + 2] - tm[i + 1] << " = " << tm[i + 2] - tm[i] << " ms" << endl;
	cout << tm[8] << " ms" << endl;
}
