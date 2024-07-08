#include <iostream>
#include <limits>
#include "load/8c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8c/cn.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n1("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8c/rt.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_a1("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
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
		pair<int, int> n1_trie0 = {0, n1_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> rt_trie0 = {0, rt_offsets.size() - 1};
		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> a1_trie0 = {0, a1_offsets.size() - 1};
		build_trie(rt_offsets, rt_id);
		build_trie(a1_offsets, a1_person_id);
		build_trie(interm0_offsets, interm0_col1);
		build_trie(t_offsets, t_id);
		build_trie(n1_offsets, n1_id);
		timer.StoreElapsedTime(2);

		string mn_t_title = "zzzzzzzz";
		string mn_a1_name = "zzzzzzzz";
		for (int ci_i = ci_trie0.first; ci_i <= ci_trie0.second; ++ci_i) {
			const auto &ci_off = ci_offsets[ci_i];
			auto x0 = ci_role_id[ci_off];
			auto rt_trie1 = find_range(rt_offsets, rt_id, x0, rt_trie0);
			if (rt_trie1.first != -1) {
				auto x1 = ci_person_id[ci_off];
				auto a1_trie1 = find_range(a1_offsets, a1_person_id, x1, a1_trie0);
				if (a1_trie1.first != -1) {
					auto x2 = ci_movie_id[ci_off];
					auto interm0_trie1 = find_range(interm0_offsets, interm0_col1, x2, interm0_trie0);
					auto t_trie1 = find_range(t_offsets, t_id, x2, t_trie0);
					if (interm0_trie1.first != -1 && t_trie1.first != -1) {
						auto n1_trie1 = find_range(n1_offsets, n1_id, x1, n1_trie0);
						if (n1_trie1.first != -1) {
							for (int t_i = t_trie1.first; t_i <= t_trie1.second; ++t_i) {
								const auto &t_off = t_offsets[t_i];
								mn_t_title = min(mn_t_title, t_title[t_off]);
							}
							for (int a1_i = a1_trie1.first; a1_i <= a1_trie1.second; ++a1_i) {
								const auto &a1_off = a1_offsets[a1_i];
								mn_a1_name = min(mn_a1_name, a1_name[a1_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_t_title << " | " << mn_a1_name << endl;
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
