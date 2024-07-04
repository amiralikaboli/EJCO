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
		int cnt;
		timer.Reset();

		auto it_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it_trie0, it_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mc_trie0, mc_movie_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_col3;
		vector<int> interm0_offsets;
		cnt = 0;
		for (const auto &mi_off: mi_offsets) {
			auto x0 = mi_info_type_id[mi_off];
			if (it_trie0.contains(x0)) {
				auto &it_trie1 = it_trie0.at(x0);
				auto x1 = mi_movie_id[mi_off];
				if (t_trie0.contains(x1) && mc_trie0.contains(x1)) {
					auto &t_trie1 = t_trie0.at(x1);
					auto &mc_trie1 = mc_trie0.at(x1);
					for (const auto &mc_off: mc_trie1) {
						auto x2 = mc_company_id[mc_off];
						if (cn_trie0.contains(x2)) {
							auto &cn_trie1 = cn_trie0.at(x2);
							for (const auto &t_off: t_trie1) {
								interm0_col0.push_back(mi_movie_id[mi_off]);
								interm0_col1.push_back(mi_info_type_id[mi_off]);
								interm0_col2.push_back(t_title[t_off]);
								interm0_col3.push_back(mc_company_id[mc_off]);
								interm0_offsets.push_back(cnt++);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto an_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(an_trie0, an_person_id);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<string> interm1_col1;
		vector<int> interm1_offsets;
		cnt = 0;
		for (const auto &n_off: n_offsets) {
			auto x0 = n_id[n_off];
			if (an_trie0.contains(x0)) {
				auto &an_trie1 = an_trie0.at(x0);
				interm1_col0.push_back(n_id[n_off]);
				interm1_col1.push_back(n_name[n_off]);
				interm1_offsets.push_back(cnt++);
			}
		}
		timer.StoreElapsedTime(3);

		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(rt_trie0, rt_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col0);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		auto chn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(chn_trie0, chn_id);
		timer.StoreElapsedTime(4);

		string mn_interm1_col1 = "zzzzzzzz";
		string mn_interm0_col2 = "zzzzzzzz";
		for (const auto &ci_off: ci_offsets) {
			auto x0 = ci_role_id[ci_off];
			if (rt_trie0.contains(x0)) {
				auto &rt_trie1 = rt_trie0.at(x0);
				auto x1 = ci_person_id[ci_off];
				if (interm1_trie0.contains(x1)) {
					auto &interm1_trie1 = interm1_trie0.at(x1);
					auto x2 = ci_movie_id[ci_off];
					if (interm0_trie0.contains(x2)) {
						auto &interm0_trie1 = interm0_trie0.at(x2);
						auto x3 = ci_person_role_id[ci_off];
						if (chn_trie0.contains(x3)) {
							auto &chn_trie1 = chn_trie0.at(x3);
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
		timer.StoreElapsedTime(5);

		if (z == 0)
			cout << mn_interm1_col1 << " | " << mn_interm0_col2 << endl;
		cerr << "*" << " " << flush;
	}
	cerr << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 3; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 3; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 3] << " ms" << endl;
}
