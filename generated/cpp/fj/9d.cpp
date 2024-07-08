#include <iostream>
#include <limits>
#include "load/9d.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9d/cn.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9d/ci.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9d/n.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9d/rt.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		build_trie(cn_offsets, cn_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int mc_i = mc_trie0.first; mc_i <= mc_trie0.second; ++mc_i) {
			const auto &mc_off = mc_offsets[mc_i];
			auto x0 = mc_company_id[mc_off];
			auto cn_trie1 = find_range(cn_offsets, cn_id, x0, cn_trie0);
			if (cn_trie1.first != -1) {
				interm0_col0.push_back(mc_company_id[mc_off]);
				interm0_col1.push_back(mc_movie_id[mc_off]);
				interm0_offsets.push_back(cnt++);
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> ci_trie0 = {0, ci_offsets.size() - 1};
		pair<int, int> n_trie0 = {0, n_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> rt_trie0 = {0, rt_offsets.size() - 1};
		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> chn_trie0 = {0, chn_offsets.size() - 1};
		pair<int, int> an_trie0 = {0, an_offsets.size() - 1};
		build_trie(rt_offsets, rt_id);
		build_trie(an_offsets, an_person_id);
		build_trie(n_offsets, n_id);
		build_trie(interm0_offsets, interm0_col1);
		build_trie(t_offsets, t_id);
		build_trie(chn_offsets, chn_id);
		timer.StoreElapsedTime(2);

		string mn_n_name = "zzzzzzzz";
		string mn_t_title = "zzzzzzzz";
		string mn_chn_name = "zzzzzzzz";
		string mn_an_name = "zzzzzzzz";
		for (int ci_i = ci_trie0.first; ci_i <= ci_trie0.second; ++ci_i) {
			const auto &ci_off = ci_offsets[ci_i];
			auto x0 = ci_role_id[ci_off];
			auto rt_trie1 = find_range(rt_offsets, rt_id, x0, rt_trie0);
			if (rt_trie1.first != -1) {
				auto x1 = ci_person_id[ci_off];
				auto an_trie1 = find_range(an_offsets, an_person_id, x1, an_trie0);
				auto n_trie1 = find_range(n_offsets, n_id, x1, n_trie0);
				if (an_trie1.first != -1 && n_trie1.first != -1) {
					auto x2 = ci_movie_id[ci_off];
					auto interm0_trie1 = find_range(interm0_offsets, interm0_col1, x2, interm0_trie0);
					auto t_trie1 = find_range(t_offsets, t_id, x2, t_trie0);
					if (interm0_trie1.first != -1 && t_trie1.first != -1) {
						auto x3 = ci_person_role_id[ci_off];
						auto chn_trie1 = find_range(chn_offsets, chn_id, x3, chn_trie0);
						if (chn_trie1.first != -1) {
							for (int n_i = n_trie1.first; n_i <= n_trie1.second; ++n_i) {
								const auto &n_off = n_offsets[n_i];
								mn_n_name = min(mn_n_name, n_name[n_off]);
							}
							for (int t_i = t_trie1.first; t_i <= t_trie1.second; ++t_i) {
								const auto &t_off = t_offsets[t_i];
								mn_t_title = min(mn_t_title, t_title[t_off]);
							}
							for (int chn_i = chn_trie1.first; chn_i <= chn_trie1.second; ++chn_i) {
								const auto &chn_off = chn_offsets[chn_i];
								mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
							}
							for (int an_i = an_trie1.first; an_i <= an_trie1.second; ++an_i) {
								const auto &an_off = an_offsets[an_i];
								mn_an_name = min(mn_an_name, an_name[an_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_n_name << " | " << mn_t_title << " | " << mn_chn_name << " | " << mn_an_name << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 2; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 2; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 2] << " ms" << endl;
}
