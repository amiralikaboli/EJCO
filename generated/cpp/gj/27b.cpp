#include <iostream>
#include <limits>
#include "load/27b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27b/lt.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27b/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27b/cct2.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27b/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27b/mc.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27b/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27b/cn.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27b/k.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27b/mi.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ml_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ml_trie0, ml_link_type_id);
		auto lt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(lt_trie0, lt_id);
		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		for (const auto &[x0, ml_trie1]: ml_trie0) {
			if (lt_trie0.contains(x0)) {
				auto &lt_trie1 = lt_trie0.at(x0);
				for (const auto &ml_off: ml_trie1) {
					for (const auto &lt_off: lt_trie1) {
						interm0_col0.push_back(ml_link_type_id[ml_off]);
						interm0_col1.push_back(ml_movie_id[ml_off]);
						interm0_col2.push_back(lt_link[lt_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto cc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(cc_trie0, cc_subject_id, cc_status_id, cc_movie_id);
		auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cct1_trie0, cct1_id);
		auto cct2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cct2_trie0, cct2_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col1);
		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<int> interm1_col2;
		vector<string> interm1_col4;
		for (const auto &[x0, cc_trie1]: cc_trie0) {
			if (cct1_trie0.contains(x0)) {
				auto &cct1_trie1 = cct1_trie0.at(x0);
				for (const auto &[x1, cc_trie2]: cc_trie1) {
					if (cct2_trie0.contains(x1)) {
						auto &cct2_trie1 = cct2_trie0.at(x1);
						for (const auto &[x2, cc_trie3]: cc_trie2) {
							if (interm0_trie0.contains(x2)) {
								auto &interm0_trie1 = interm0_trie0.at(x2);
								for (const auto &cc_off: cc_trie3) {
									for (const auto &interm0_off: interm0_trie1) {
										interm1_col0.push_back(cc_subject_id[cc_off]);
										interm1_col1.push_back(cc_status_id[cc_off]);
										interm1_col2.push_back(cc_movie_id[cc_off]);
										interm1_col4.push_back(interm0_col2[interm0_off]);
									}
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col2);
		vector<int> interm2_col0;
		vector<string> interm2_col1;
		vector<string> interm2_col5;
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (interm1_trie0.contains(x0)) {
				auto &interm1_trie1 = interm1_trie0.at(x0);
				for (const auto &t_off: t_trie1) {
					for (const auto &interm1_off: interm1_trie1) {
						interm2_col0.push_back(t_id[t_off]);
						interm2_col1.push_back(t_title[t_off]);
						interm2_col5.push_back(interm1_col4[interm1_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(2);

		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(mc_trie0, mc_company_type_id, mc_company_id, mc_movie_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto interm2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm2_trie0, interm2_col0);
		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<int> interm3_col2;
		vector<string> interm3_col3;
		vector<string> interm3_col4;
		vector<string> interm3_col8;
		for (const auto &[x0, mc_trie1]: mc_trie0) {
			if (ct_trie0.contains(x0)) {
				auto &ct_trie1 = ct_trie0.at(x0);
				for (const auto &[x1, mc_trie2]: mc_trie1) {
					if (cn_trie0.contains(x1)) {
						auto &cn_trie1 = cn_trie0.at(x1);
						for (const auto &[x2, mc_trie3]: mc_trie2) {
							if (interm2_trie0.contains(x2)) {
								auto &interm2_trie1 = interm2_trie0.at(x2);
								for (const auto &mc_off: mc_trie3) {
									for (const auto &cn_off: cn_trie1) {
										for (const auto &interm2_off: interm2_trie1) {
											interm3_col0.push_back(mc_company_type_id[mc_off]);
											interm3_col1.push_back(mc_company_id[mc_off]);
											interm3_col2.push_back(mc_movie_id[mc_off]);
											interm3_col3.push_back(cn_name[cn_off]);
											interm3_col4.push_back(interm2_col1[interm2_off]);
											interm3_col8.push_back(interm2_col5[interm2_off]);
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
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		auto interm3_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm3_trie0, interm3_col2);
		vector<int> interm4_col0;
		vector<int> interm4_col1;
		vector<string> interm4_col4;
		vector<string> interm4_col5;
		vector<string> interm4_col9;
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (k_trie0.contains(x0)) {
				auto &k_trie1 = k_trie0.at(x0);
				for (const auto &[x1, mk_trie2]: mk_trie1) {
					if (interm3_trie0.contains(x1)) {
						auto &interm3_trie1 = interm3_trie0.at(x1);
						for (const auto &mk_off: mk_trie2) {
							for (const auto &interm3_off: interm3_trie1) {
								interm4_col0.push_back(mk_keyword_id[mk_off]);
								interm4_col1.push_back(mk_movie_id[mk_off]);
								interm4_col4.push_back(interm3_col3[interm3_off]);
								interm4_col5.push_back(interm3_col4[interm3_off]);
								interm4_col9.push_back(interm3_col8[interm3_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(4);

		auto mi_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(mi_trie0, mi_movie_id);
		auto interm4_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm4_trie0, interm4_col1);
		string mn_interm4_col4 = "zzzzzzzz";
		string mn_interm4_col5 = "zzzzzzzz";
		string mn_interm4_col9 = "zzzzzzzz";
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (interm4_trie0.contains(x0)) {
				auto &interm4_trie1 = interm4_trie0.at(x0);
				for (const auto &interm4_off: interm4_trie1) {
					mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
					mn_interm4_col5 = min(mn_interm4_col5, interm4_col5[interm4_off]);
					mn_interm4_col9 = min(mn_interm4_col9, interm4_col9[interm4_off]);
				}
			}
		}
		timer.StoreElapsedTime(5);

		if (z == 0)
			cout << mn_interm4_col4 << " | " << mn_interm4_col5 << " | " << mn_interm4_col9 << endl;
		cerr << "*" << " " << flush;
	}
	cerr << endl;

	vector<double> tm{0};
	for (int i = 0; i < 6; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 6; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[6] << " ms" << endl;
}
