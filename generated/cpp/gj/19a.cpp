#include <iostream>
#include <limits>
#include "load/19a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/mi.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/mc.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/it.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/cn.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/n.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/ci.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/rt.csv");
	load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_id);
		auto it_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it_trie0, it_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_col3;
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (t_trie0.contains(x0) && mc_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				auto &mc_trie1 = mc_trie0.at(x0);
				for (const auto &[x1, mi_trie2]: mi_trie1) {
					if (it_trie0.contains(x1)) {
						auto &it_trie1 = it_trie0.at(x1);
						for (const auto &[x2, mc_trie2]: mc_trie1) {
							if (cn_trie0.contains(x2)) {
								auto &cn_trie1 = cn_trie0.at(x2);
								for (const auto &mi_off: mi_trie2) {
									for (const auto &t_off: t_trie1) {
										for (const auto &mc_off: mc_trie2) {
											interm0_col0.push_back(mi_movie_id[mi_off]);
											interm0_col1.push_back(mi_info_type_id[mi_off]);
											interm0_col2.push_back(t_title[t_off]);
											interm0_col3.push_back(mc_company_id[mc_off]);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto an_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an_trie0, an_person_id);
		vector<int> interm1_col0;
		vector<string> interm1_col1;
		for (const auto &[x0, n_trie1]: n_trie0) {
			if (an_trie0.contains(x0)) {
				auto &an_trie1 = an_trie0.at(x0);
				for (const auto &n_off: n_trie1) {
					interm1_col0.push_back(n_id[n_off]);
					interm1_col1.push_back(n_name[n_off]);
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>>();
		build_trie_bool(ci_trie0, ci_role_id, ci_person_role_id, ci_person_id, ci_movie_id);
		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(rt_trie0, rt_id);
		auto chn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(chn_trie0, chn_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col0);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		string mn_interm1_col1 = "zzzzzzzz";
		string mn_interm0_col2 = "zzzzzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (rt_trie0.contains(x0)) {
				auto &rt_trie1 = rt_trie0.at(x0);
				for (const auto &[x1, ci_trie2]: ci_trie1) {
					if (chn_trie0.contains(x1)) {
						auto &chn_trie1 = chn_trie0.at(x1);
						for (const auto &[x2, ci_trie3]: ci_trie2) {
							if (interm1_trie0.contains(x2)) {
								auto &interm1_trie1 = interm1_trie0.at(x2);
								for (const auto &[x3, ci_trie4]: ci_trie3) {
									if (interm0_trie0.contains(x3)) {
										auto &interm0_trie1 = interm0_trie0.at(x3);
										for (const auto &interm1_off: interm1_trie1) {
											mn_interm1_col1 = min(mn_interm1_col1, interm1_col1[interm1_off]);
										}
										for (const auto &interm0_off: interm0_trie1) {
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
		timer.StoreElapsedTime(2);

		if (z == 0)
			cout << mn_interm1_col1 << " | " << mn_interm0_col2 << endl;
		cerr << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 3; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 3; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[3] << " ms" << endl;
}
