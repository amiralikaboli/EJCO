#include <iostream>
#include <limits>
#include "load/29a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/cct2.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/cn.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/k.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/mi.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/it.csv");
	load_pi("/Users/s2522996/Documents/free-join/data/imdb_csv/person_info.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	load_it3("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/it3.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/n.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/ci.csv");
	load_chn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/chn.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29a/rt.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto cc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(cc_trie0, cc_subject_id, cc_status_id);
		auto cct1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cct1_trie0, cct1_id);
		auto cct2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cct2_trie0, cct2_id);
		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_col2;
		for (const auto &[x0, cc_trie1]: cc_trie0) {
			if (cct1_trie0.contains(x0)) {
				auto &cct1_trie1 = cct1_trie0.at(x0);
				for (const auto &[x1, cc_trie2]: cc_trie1) {
					if (cct2_trie0.contains(x1)) {
						auto &cct2_trie1 = cct2_trie0.at(x1);
						for (const auto &cc_off: cc_trie2) {
							interm0_col0.push_back(cc_subject_id[cc_off]);
							interm0_col1.push_back(cc_status_id[cc_off]);
							interm0_col2.push_back(cc_movie_id[cc_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col2);
		vector<int> interm1_col0;
		vector<string> interm1_col1;
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (interm0_trie0.contains(x0)) {
				auto &interm0_trie1 = interm0_trie0.at(x0);
				for (const auto &t_off: t_trie1) {
					interm1_col0.push_back(t_id[t_off]);
					interm1_col1.push_back(t_title[t_off]);
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_company_id, mc_movie_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col0);
		vector<int> interm2_col0;
		vector<int> interm2_col1;
		vector<string> interm2_col2;
		for (const auto &[x0, mc_trie1]: mc_trie0) {
			if (cn_trie0.contains(x0)) {
				auto &cn_trie1 = cn_trie0.at(x0);
				for (const auto &[x1, mc_trie2]: mc_trie1) {
					if (interm1_trie0.contains(x1)) {
						auto &interm1_trie1 = interm1_trie0.at(x1);
						for (const auto &mc_off: mc_trie2) {
							for (const auto &interm1_off: interm1_trie1) {
								interm2_col0.push_back(mc_company_id[mc_off]);
								interm2_col1.push_back(mc_movie_id[mc_off]);
								interm2_col2.push_back(interm1_col1[interm1_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(2);

		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto interm2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm2_trie0, interm2_col1);
		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<string> interm3_col3;
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (k_trie0.contains(x0)) {
				auto &k_trie1 = k_trie0.at(x0);
				for (const auto &[x1, mk_trie2]: mk_trie1) {
					if (interm2_trie0.contains(x1)) {
						auto &interm2_trie1 = interm2_trie0.at(x1);
						for (const auto &mk_off: mk_trie2) {
							for (const auto &interm2_off: interm2_trie1) {
								interm3_col0.push_back(mk_keyword_id[mk_off]);
								interm3_col1.push_back(mk_movie_id[mk_off]);
								interm3_col3.push_back(interm2_col2[interm2_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_info_type_id, mi_movie_id);
		auto it_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it_trie0, it_id);
		auto interm3_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm3_trie0, interm3_col1);
		vector<int> interm4_col0;
		vector<int> interm4_col1;
		vector<string> interm4_col4;
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (it_trie0.contains(x0)) {
				auto &it_trie1 = it_trie0.at(x0);
				for (const auto &[x1, mi_trie2]: mi_trie1) {
					if (interm3_trie0.contains(x1)) {
						auto &interm3_trie1 = interm3_trie0.at(x1);
						for (const auto &mi_off: mi_trie2) {
							for (const auto &interm3_off: interm3_trie1) {
								interm4_col0.push_back(mi_info_type_id[mi_off]);
								interm4_col1.push_back(mi_movie_id[mi_off]);
								interm4_col4.push_back(interm3_col3[interm3_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(4);

		auto pi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(pi_trie0, pi_person_id, pi_info_type_id);
		auto an_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an_trie0, an_person_id);
		auto it3_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it3_trie0, it3_id);
		vector<int> interm5_col0;
		vector<int> interm5_col1;
		for (const auto &[x0, pi_trie1]: pi_trie0) {
			if (an_trie0.contains(x0)) {
				auto &an_trie1 = an_trie0.at(x0);
				for (const auto &[x1, pi_trie2]: pi_trie1) {
					if (it3_trie0.contains(x1)) {
						auto &it3_trie1 = it3_trie0.at(x1);
						for (const auto &pi_off: pi_trie2) {
							interm5_col0.push_back(pi_person_id[pi_off]);
							interm5_col1.push_back(pi_info_type_id[pi_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto interm5_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm5_trie0, interm5_col0);
		vector<int> interm6_col0;
		vector<string> interm6_col1;
		for (const auto &[x0, n_trie1]: n_trie0) {
			if (interm5_trie0.contains(x0)) {
				auto &interm5_trie1 = interm5_trie0.at(x0);
				for (const auto &n_off: n_trie1) {
					interm6_col0.push_back(n_id[n_off]);
					interm6_col1.push_back(n_name[n_off]);
				}
			}
		}
		timer.StoreElapsedTime(6);

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>>();
		build_trie_bool(ci_trie0, ci_person_role_id, ci_role_id, ci_person_id, ci_movie_id);
		auto chn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(chn_trie0, chn_id);
		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(rt_trie0, rt_id);
		auto interm6_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm6_trie0, interm6_col0);
		auto interm4_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm4_trie0, interm4_col1);
		string mn_chn_name = "zzzzzzzz";
		string mn_interm6_col1 = "zzzzzzzz";
		string mn_interm4_col4 = "zzzzzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (chn_trie0.contains(x0)) {
				auto &chn_trie1 = chn_trie0.at(x0);
				for (const auto &[x1, ci_trie2]: ci_trie1) {
					if (rt_trie0.contains(x1)) {
						auto &rt_trie1 = rt_trie0.at(x1);
						for (const auto &[x2, ci_trie3]: ci_trie2) {
							if (interm6_trie0.contains(x2)) {
								auto &interm6_trie1 = interm6_trie0.at(x2);
								for (const auto &[x3, ci_trie4]: ci_trie3) {
									if (interm4_trie0.contains(x3)) {
										auto &interm4_trie1 = interm4_trie0.at(x3);
										for (const auto &chn_off: chn_trie1) {
											mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
										}
										for (const auto &interm6_off: interm6_trie1) {
											mn_interm6_col1 = min(mn_interm6_col1, interm6_col1[interm6_off]);
										}
										for (const auto &interm4_off: interm4_trie1) {
											mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(7);

		if (z == 0)
			cout << mn_chn_name << " | " << mn_interm6_col1 << " | " << mn_interm4_col4 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 8; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 8; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[8] << " ms" << endl;
}
