#include <iostream>
#include <limits>
#include "load/16a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16a/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16a/k.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16a/cn.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		build_trie(k_offsets, k_id);
		build_trie(t_offsets, t_id);
		build_trie(mc_offsets, mc_movie_id);
		build_trie(cn_offsets, cn_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_col3;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_keyword_id[mk_off];
			auto k_trie1 = find_range(k_offsets, k_id, x0, k_trie0);
			if (k_trie1.first != -1) {
				auto x1 = mk_movie_id[mk_off];
				auto t_trie1 = find_range(t_offsets, t_id, x1, t_trie0);
				auto mc_trie1 = find_range(mc_offsets, mc_movie_id, x1, mc_trie0);
				if (t_trie1.first != -1 && mc_trie1.first != -1) {
					for (int mc_i = mc_trie1.first; mc_i <= mc_trie1.second; ++mc_i) {
						const auto &mc_off = mc_offsets[mc_i];
						auto x2 = mc_company_id[mc_off];
						auto cn_trie1 = find_range(cn_offsets, cn_id, x2, cn_trie0);
						if (cn_trie1.first != -1) {
							for (int t_i = t_trie1.first; t_i <= t_trie1.second; ++t_i) {
								const auto &t_off = t_offsets[t_i];
								interm0_col0.push_back(mk_movie_id[mk_off]);
								interm0_col1.push_back(mk_keyword_id[mk_off]);
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

		pair<int, int> ci_trie0 = {0, ci_offsets.size() - 1};
		pair<int, int> n_trie0 = {0, n_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> an_trie0 = {0, an_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col0);
		build_trie(an_offsets, an_person_id);
		build_trie(n_offsets, n_id);
		timer.StoreElapsedTime(2);

		string mn_interm0_col2 = "zzzzzzzz";
		string mn_an_name = "zzzzzzzz";
		for (int ci_i = ci_trie0.first; ci_i <= ci_trie0.second; ++ci_i) {
			const auto &ci_off = ci_offsets[ci_i];
			auto x0 = ci_movie_id[ci_off];
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x0, interm0_trie0);
			if (interm0_trie1.first != -1) {
				auto x1 = ci_person_id[ci_off];
				auto an_trie1 = find_range(an_offsets, an_person_id, x1, an_trie0);
				auto n_trie1 = find_range(n_offsets, n_id, x1, n_trie0);
				if (an_trie1.first != -1 && n_trie1.first != -1) {
					for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
						const auto &interm0_off = interm0_offsets[interm0_i];
						mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
					}
					for (int an_i = an_trie1.first; an_i <= an_trie1.second; ++an_i) {
						const auto &an_off = an_offsets[an_i];
						mn_an_name = min(mn_an_name, an_name[an_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_interm0_col2 << " | " << mn_an_name << endl;
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
