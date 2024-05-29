#include <iostream>
#include <limits>
#include "load/10a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10a/t.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10a/cn.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10a/ci.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10a/rt.csv");
	load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_type_id, mc_company_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto ct_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_col2;
		vector<string> interm0_col3;
		for (const auto &[x0, mc_trie1]: mc_trie0) {
			if (t_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				for (const auto &[x1, mc_trie2]: mc_trie1) {
					if (ct_trie0.contains(x1)) {
						auto &ct_trie1 = ct_trie0.at(x1);
						for (const auto &[x2, mc_trie3]: mc_trie2) {
							if (cn_trie0.contains(x2)) {
								auto &cn_trie1 = cn_trie0.at(x2);
								for (const auto &mc_off: mc_trie3) {
									for (const auto &t_off: t_trie1) {
										interm0_col0.push_back(mc_movie_id[mc_off]);
										interm0_col1.push_back(mc_company_type_id[mc_off]);
										interm0_col2.push_back(mc_company_id[mc_off]);
										interm0_col3.push_back(t_title[t_off]);
									}
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(ci_trie0, ci_role_id, ci_movie_id, ci_person_role_id);
		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(rt_trie0, rt_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		auto chn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(chn_trie0, chn_id);
		timer.StoreElapsedTime(2);

		int mn_interm0_col1 = numeric_limits<int>::max();
		int mn_interm0_col2 = numeric_limits<int>::max();
		string mn_interm0_col3 = "zzzzzzzz";
		string mn_chn_name = "zzzzzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (rt_trie0.contains(x0)) {
				auto &rt_trie1 = rt_trie0.at(x0);
				for (const auto &[x1, ci_trie2]: ci_trie1) {
					if (interm0_trie0.contains(x1)) {
						auto &interm0_trie1 = interm0_trie0.at(x1);
						for (const auto &[x2, ci_trie3]: ci_trie2) {
							if (chn_trie0.contains(x2)) {
								auto &chn_trie1 = chn_trie0.at(x2);
								for (const auto &interm0_off: interm0_trie1) {
									mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
									mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
									mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
								}
								for (const auto &chn_off: chn_trie1) {
									mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_interm0_col1 << " | " << mn_interm0_col2 << " | " << mn_interm0_col3 << " | " << mn_chn_name << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 2; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 2; i += 2)
		cout << tm[i + 1] - tm[i] << " | " << tm[i + 2] - tm[i + 1] << " ms" << endl;
	cout << tm[4] << " ms" << endl;
}
